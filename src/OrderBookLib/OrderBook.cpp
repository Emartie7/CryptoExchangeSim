/*  
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/**
 * @file OrderBook.cpp
 * @author Edward Martinez
 * @brief Source file for functionality related to order book class.
 * @version 0.1
 * @date 2024-06-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************//**
 *  Includes
 ***********************************************/
#include "OrderBook.h"
#include <map>
#include <algorithm>
#include <stdexcept>
/********************************************//**
 *  Method Implementations
 ***********************************************/
/**
 * @brief Constructor
 * @param filename Path to csv file containing order data set.
 */
OrderBook::OrderBook(std::string filename)
{
    this->orders = CsvReader::readCSV(filename);
    if(this->orders.size() == 0)
    {
        throw std::runtime_error(std::string("Failed to read data for OrderBook."));
    }
}

/**
 * @brief Searches this->orders for all unique product types (e.g. "BTC/DOGE") and returns a vector containing this info.
 */
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string,bool> prodMap;

    for(const OrderBookEntry& e: orders)
    {
        prodMap[e._product] = true;
    }
    
    for(const auto &e : prodMap)
    {
        products.push_back(e.first);
    }
    return products;
}
/**
 * @brief Gets a vector of OrderBookEntry objects matching the specified filters (type, product, time window).
 * @param type Filter on this OrderBookType.
 * @param product Filter on this product. 
 * @param timestamp Filter on this time window.
 */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> OrdersFiltered;
    for(const OrderBookEntry &entry : orders)
    {
        if((entry._OrderType == type   )&&
           (entry._product   == product)&&
           (entry._timestamp == timestamp))
        {
            OrdersFiltered.push_back(entry);
        }
    }
    return OrdersFiltered;
}
/**
 * @brief Returns high price from a vector of OrderBookEntry objects.
 * @see getOrders()
 * @param OrdersSub Vector of OrderBookEntry of matching product type.
 */
double OrderBook::getHighPrice(std::vector<OrderBookEntry> &OrdersSub)
{
    double max = OrdersSub[0]._price;
    for(int i = 1; i < OrdersSub.size(); i++)
    {
        if(OrdersSub[i]._price > max) max = OrdersSub[i]._price;
    }
    return max;
}
/**
 * @brief Returns low price from a vector of OrderBookEntry objects.
 * @param OrdersSub Vector of OrderBookEntry of matching product type.
 */
double OrderBook::getLowPrice(std::vector<OrderBookEntry> &OrdersSub)
{
    double min = OrdersSub[0]._price;
    for(int i = 1; i < OrdersSub.size(); i++)
    {
        if(OrdersSub[i]._price < min) min = OrdersSub[i]._price;
    }
    return min;
}

/**
 * @brief Returns price spread for a given set of order book products.
 * @param OrdersSub Vector of OrderBookEntry of matching product type.
 */
double OrderBook::getSpread(std::vector<OrderBookEntry>& OrdersSub)
{
    double max = OrderBook::getHighPrice(OrdersSub);
    double min = OrderBook::getLowPrice(OrdersSub);
    double spread = max - min;
    return spread;
}

std::string OrderBook::getEarliestTime()
{
    std::string first_timestamp = this->orders[0]._timestamp; //Get first timestamp in entry list

    for(OrderBookEntry &e : this->orders)
    {
        if(e._timestamp < first_timestamp) first_timestamp = e._timestamp;
    }
    return first_timestamp;
}

std::string OrderBook::getNextTime(const std::string & timestamp)
{
    std::string next_timestamp = "";
    for(OrderBookEntry &e : orders)
    {
        if(e._timestamp > timestamp) 
        {
            next_timestamp = e._timestamp;
            break;
        }
    }

    if( next_timestamp == "") next_timestamp = getEarliestTime();
    return next_timestamp;
}

/**
 * @brief Add an OrderBookEntry to the orderbook.
 * 
 * Appends new OBE to orders vector then performs a sort based on simulation timestamp values.
 */
void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    std::sort(orders.begin(),orders.end(),OrderBookEntry::compareByTimestamp);
}

/**
 * @brief Match bid OBEs to ask OBEs for a specified timeframe.
 * 
 * @param product Product to match
 * @param timestamp Timeframe in which to perform the matching.
 * 
 * Limitations, assumptions and restrictions:
 * 1. Lowest priced ask is processed first.
 * 2. The highest bid that matches the current ask is given priority over any lower bids that also match.
 * 3. Sales will be processed at the ask price, even if the matching bid is higher.
 * 4. Partial salse are allowed, and will sell the largest possible amount.
 * 5. Partially matched bids or asks can be re-processed and matched against further bids or asks.
 */
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,product,timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,product,timestamp);
    std::vector<OrderBookEntry> sales;

    for(OrderBookEntry cAsk:asks)
    {
        for(OrderBookEntry cBid:bids)
        {
            if(cBid._price >= cAsk._price)
            {
                OrderBookEntry sale = OrderBookEntry{timestamp,
                                                     product,
                                                     OrderBookType::ask,
                                                     0.0,
                                                     0.0};
                sale._price = cAsk._price;

                //Both bid and ask are completely cleared.
                if(cBid._amount == cAsk._amount)
                {
                    sale._amount = cAsk._amount;
                    sales.push_back(sale);

                    cBid._amount = 0; //This bid can do no more work
                    break;
                }
                //Bid completely clears ask, some bid remains.
                if(cBid._amount > cAsk._amount)
                {
                    sale._amount = cAsk._amount;
                    sales.push_back(sale);
                    cBid._amount = cBid._amount - sale._amount; //Update bid amount for future possible sales.
                    break;
                }
                //Bid partially clears ask.
                if(cBid._amount < cAsk._amount)
                {
                    sale._amount = cBid._amount;
                    sales.push_back(sale);
                    cAsk._amount = cAsk._amount - cBid._amount; //Update ask amount for future possible sales.
                    cBid._amount = 0; //This bid can do no more work
                    continue;
                }
            }//end if(cBid.price >= ask.price)

        } //end for(OrderBookEntry cBid:bids)

    } //end for(OrderBookEntry cAsk:asks)
    return sales;
}
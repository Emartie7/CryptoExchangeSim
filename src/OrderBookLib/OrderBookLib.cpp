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
 * @file OrderBookLib.cpp
 * @author Edward Martinez
 * @brief Source code for implementation of functionality related to order book entries.
 * @version 0.1
 * @date 2024-06-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/********************************************//**
 *  Includes
 ***********************************************/
#include "OrderBookLib.h"
#include "iostream"

OrderBookEntry::OrderBookEntry(std::string timestamp,std::string product,OrderBookType OrderType,double price, double amount)
: _timestamp(timestamp),
  _product(product),
  _OrderType(OrderType),
  _price(price),
  _amount(amount)
{
}
/********************************************//**
 *  Local Functions
 ***********************************************/
OrderBookType OrderBookEntry::stringToObeType(const std::string& s)
{
    if("ask" == s)      return OrderBookType::ask;
    else if("bid" == s) return OrderBookType::bid;
    else                return OrderBookType::unknown;
}

void printEntryPrices(std::vector<OrderBookEntry>& entries)
{
    for(OrderBookEntry& entry : entries)
    {
        std::cout << entry._product << " price: " << entry._price << std::endl;
    }
}

double computeHighPrice(std::vector<OrderBookEntry>& entries)
{
    double priceMax = 0.0;
    for(OrderBookEntry& entry : entries)
    {
        if(entry._price > priceMax)
        {
            priceMax = entry._price;
        }
    }
    return priceMax;
}

double computeLowPrice(std::vector<OrderBookEntry>& entries)
{
    double priceMin = 0.0;
    bool firstEntry = true;
    for(OrderBookEntry& entry : entries)
    {
        if(firstEntry)
        {
            priceMin = entry._price;
            firstEntry = false;
        }
        else if(priceMin > entry._price)
        {
            priceMin = entry._price;
        }
    }
    return priceMin;
}

double averagePrice(std::vector<OrderBookEntry>& entries)
{
    double sum = 0.0;
    for(const OrderBookEntry& entry : entries)
    {
        sum += entry._price;
    }
    return sum/(entries.size());
}

void countOrderTypes(std::vector<OrderBookEntry>& entries)
{
    unsigned int bid = 0;
    unsigned int ask = 0;
    for(const OrderBookEntry& entry : entries)
    {
        switch(entry._OrderType)
        {
            case OrderBookType::ask:
                ask++;
                break;
            case OrderBookType::bid:
                bid++;
                break;
            default:
                break; //Do nothing for now
        }
    }
    std::cout << "   Number of asks: " << ask << std::endl
              << "   Number of bids: " << bid << std::endl;
}
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
/** @cond STDINCLUDES */
#include <iostream>
/** @endcond */
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
/**
 * @brief Returns OrderBookType representation of a given string.
 * 
 * @param s String representation of OrderBookType (i.e. "Bid" or "Ask")
 */
OrderBookType OrderBookEntry::stringToObeType(const std::string& s)
{
    if("ask" == s)      return OrderBookType::ask;
    else if("bid" == s) return OrderBookType::bid;
    else                return OrderBookType::unknown;
}

/**
 * @brief Compares two orderbook entries. 
 * 
 * Returns true if the first OBE has an earlier timestamp than the second.
 * Assumes timestamp values are purely numerical and can be compared in this manner.
 * @see OrderBook::insertOrder()
 */
bool OrderBookEntry::compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2)
{
    return e1._timestamp < e2._timestamp;
}

/**
 * @brief Compares two orderbook entries. 
 * 
 * Returns true if the first OBE has a lower price than the second.
 */
bool OrderBookEntry::compareByPriceAsc(OrderBookEntry & e1,OrderBookEntry & e2)
{
    return e1._price < e2._price;
}

/**
 * @brief Compares two orderbook entries. 
 * 
 * Returns true if the first OBE has a higher price than the second.
 */
bool OrderBookEntry::compareByPriceDesc(OrderBookEntry & e1,OrderBookEntry & e2)
{
    return e1._price > e2._price;
}

/**
 * @brief Generates a OrderBookEntry object.
 * 
 * Takes a vector of strings and converts types to return a new OBE.
 * @param tokens Vector containing OBE attributes as strings.
 */
OrderBookEntry OrderBookEntry::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    try
    {
        //OrderBook typecast
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch(const std::exception& e)
    {
        std::cout << "CsvReader::stringsToOBE - Error in string to OBE type conversion." << std::endl;
        std::cout << "   " << e.what() << std::endl;
        throw;
    }
    OrderBookEntry obe{tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToObeType(tokens[2]),
                       price,
                       amount};
    return obe;
}

/**
 * @brief Generates a OrderBookEntry object.
 * 
 * Takes string args. and converts types to return a new OBE.
 * @param priceString Order price as a string
 * @param amountString Order amount as a string
 * @param timestamp Timestamp as a string
 * @param product Product type (i.e. "BTC/ETH" as a string
 * @param orderType Bid or Ask
 */
OrderBookEntry OrderBookEntry::stringsToOBE(std::string priceString,
                                    std::string amountString,
                                    std::string timestamp,
                                    std::string product,
                                    OrderBookType orderType)
{
    double price, amount;
    try 
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }catch(const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl;
        throw; // throw up to the calling function
    }
    OrderBookEntry obe{timestamp,
                       product,
                       orderType,
                       price,
                       amount
    };
    return obe;   
}
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
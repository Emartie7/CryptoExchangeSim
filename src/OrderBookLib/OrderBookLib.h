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
 * @file OrderBookLib.h
 * @author Edward Martinez
 * @brief Header file for functionality related to order book entries.
 * @version 0.1
 * @date 2024-06-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
/********************************************//**
 *  Includes
 ***********************************************/
/** @cond STDINCLUDES */
#include <string>
#include <vector>
/** @endcond */
/********************************************//**
 *  Class Definitions
 ***********************************************/
enum class OrderBookType:char {bid,ask,unknown,asksale,bidsale};

/*! @class OrderBookEntry
    @brief Class for an entry of order book data.
*/
class OrderBookEntry
{
    public:
        std::string _timestamp;
        std::string _product;
        OrderBookType _OrderType;
        double _price;
        double _amount;
        std::string username = "dataset";
        OrderBookEntry(std::string timestamp,std::string product,OrderBookType OrderType,double price, double amount);
        static OrderBookType stringToObeType(const std::string& s);
        static bool compareByTimestamp(const OrderBookEntry &e1, const OrderBookEntry &e2);
        static bool compareByPriceAsc(OrderBookEntry & e1,OrderBookEntry & e2);
        static bool compareByPriceDesc(OrderBookEntry & e1,OrderBookEntry & e2);
};
/********************************************//**
 *  Function Prototypes
 ***********************************************/
void printEntryPrices(std::vector<OrderBookEntry>& entries);
double computeHighPrice(std::vector<OrderBookEntry>& entries);
double computeLowPrice(std::vector<OrderBookEntry>& entries);
double averagePrice(std::vector<OrderBookEntry>& entries);
void countOrderTypes(std::vector<OrderBookEntry>& entries);
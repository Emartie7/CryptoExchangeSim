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
 * @file OrderBook.h
 * @author Edward Martinez
 * @brief Header file for functionality related to order book class.
 * @version 0.1
 * @date 2024-06-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
/********************************************//**
 *  Includes
 ***********************************************/
#include "../OrderBookLib/OrderBookLib.h"
#include "../CsvReader/CsvReader.h"
#include <string>
#include <vector>

/********************************************//**
 *  Class Definitions
 ***********************************************/
/*! @class OrderBook
    @brief Class for exchange orderbook data.

    Serves as a wrapper for handling orderbook data entries and performing statistical analyses.
*/
class OrderBook
{
    public:
        OrderBook(std::string filename);
        std::vector<std::string> getKnownProducts();
        std::vector<OrderBookEntry> getOrders(OrderBookType type,
        std::string product,
        std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& OrdersSub);
        static double getLowPrice(std::vector<OrderBookEntry>& OrdersSub);
        static double getSpread(std::vector<OrderBookEntry>& OrdersSub);
        std::string getEarliestTime();
        std::string getNextTime(const std::string & timestamp);
        void insertOrder(OrderBookEntry &order);

    private:
        std::vector<OrderBookEntry> orders;
};
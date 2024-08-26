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
 * @file CsvReader.h
 * @author Edward Martinez
 * @brief Source code for reading data sets from CSV files.
 * @version 0.1
 * @date 2024-06-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
/********************************************//**
 *  Includes
 ***********************************************/
#include "../OrderBookLib/OrderBookLib.h"
/** @cond */
#include <vector>
#include <string>
/** @endcond */
/********************************************//**
 *  Class Prototypes
 ***********************************************/
/*! @class CsvReader
    @brief Class for reading OrderBookEntry objects from CSV files.
*/
class CsvReader
{
    public:
        CsvReader();
        static std::vector<OrderBookEntry> readCSV(std::string csvFileName);
        static std::vector<std::string> tokenise(std::string lineIn,char separator);
};
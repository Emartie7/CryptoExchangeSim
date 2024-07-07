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
 * @file UserMenuIF.h
 * @author Edward Martinez
 * @brief Source file for processing user selections made in the MerkleRex menu.
 * @version 0.1
 * @date 2024-05-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/********************************************//**
 *  Includes
 ***********************************************/
#pragma once

#include <vector>
#include "OrderBookLib.h"
#include "OrderBook.h"
/********************************************//**
 *  Defines
 ***********************************************/

/********************************************//**
 *  Local Params
 ***********************************************/

/********************************************//**
 *  Class definitions
 ***********************************************/
/*! @class MerkelMain
    @brief Class for currency exchange application.

    Implements the terminal-based UI for orderbook and exchange I/O.
*/
class MerkelMain
{
    public:
        MerkelMain(std::string filename);
        void init();
    private:
        void loadOrderBook();
        void printHelp();
        void printExchangeStats();
        void enterAsk();
        void makeBid();
        void printWallet();
        void processNext();
        void processUserOption(int selection);
        int getUserOption();
        void printMenu();
        std::string currentTime;
        OrderBook orderBook;
};
/********************************************//**
 *  Function Prototypes
 ***********************************************/

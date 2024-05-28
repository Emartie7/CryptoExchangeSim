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
#include <iostream>
#include <map>
#include <string>
#include <sstream>

/********************************************//**
 *  Defines
 ***********************************************/

/********************************************//**
 *  Local Params
 ***********************************************/

/********************************************//**
 *  Local functions
 ***********************************************/
void printHelp()
{
    std::cout << "Help is on the way" << std::endl;
}
void printExchangeStats()
{
    std::cout << "Market looks good" << std::endl;
}
void makeOffer()
{
    std::cout << "Make an offer: " << std::endl;
}
void makeBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}
void printWallet()
{
    std::cout << "Your wallet has: " << std::endl;
}
void processNext()
{
   std::cout << "Make your next selection." << std::endl; 
}
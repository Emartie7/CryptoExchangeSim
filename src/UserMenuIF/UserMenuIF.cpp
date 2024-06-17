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
#include "UserMenuIF.h"
#include "CsvReader.h"
/********************************************//**
 *  Defines
 ***********************************************/

/********************************************//**
 *  Local Params
 ***********************************************/

/********************************************//**
 *  Function Implementations
 ***********************************************/

/***************************************************************************//**
 * printMenu(void)
 *
 * Print menu options to terminal.
 *
 * @param none Nothing yet
 ******************************************************************************/
void MerkelMain::printMenu()
{
    /* 
    //1 Print help
    //2 print exchange stats
    //3 make an offer
    //4 make a bid
    //5 print wallet
    //6 continue 
    //7 Exit program
    */
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Make an offer" << std::endl;
    std::cout << "4: Make a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "7: Exit" << std::endl;
    std::cout << "=================================" << std::endl;
}

/***************************************************************************//**
 * int getUserOption(void)
 *
 * Get user input from terminal and perform validation checks.
 * 
 * Limitations,assumptions & restrictions:
 * 1. Only integer-type inputs are valid.
 * 2. Valid range integer value is 1-7
 *
 * @param none Nothing yet
 ******************************************************************************/
int MerkelMain::getUserOption()
{
    std::string strIn;
    int userOption = 0;
    int ret        = -1;

    std::cout << "Type in 1-6" << std::endl;
    getline(std::cin,strIn);

    std::stringstream str(strIn);
    str >> userOption;

    if(!str)
    {
        std::cout << "   ERROR: Invalid input type." << std::endl;
    }
    else if((userOption > 0) && (userOption < 8))
    {
        std::cout << "   You chose: " << userOption << std::endl;
        ret = userOption;
    }
    else std::cout << "   WARNING: Input out of range. Make another selection." << std::endl;

    return ret;
}

/***************************************************************************//**
 * void processUserOption(int)
 *
 * Take action based on user input.
 * 
 * Limitations,assumptions & restrictions:
 * 1. Assumes input has already been validated (see 'getUserOption()')
 * 2. Assumes input map arg. has been initialized with pointers to valid functions.
 * 3. Assumes functions in input map require no inputs and ignores any return values (for now).
 *
 * @param none Nothing yet
 ******************************************************************************/
void MerkelMain::processUserOption(int selection)
{
    // void (*optFunc) () = mFuncs[selection];
    // optFunc();
    switch(selection)
    {
        case 1:
            this->printHelp();
            break;
        case 2:
            this->printExchangeStats();
            break;
        case 3:
            this->makeOffer();
            break;
        case 4:
            this->makeBid();
            break;
        case 5:
            this->printWallet();
            break;
        case 6:
            this->processNext();
            break;
        default:
            break;

    }
    std::cout << std::endl;
}

void MerkelMain::loadOrderBook()
{
    orders = CsvReader::readCSV("DataSets/OrderBook_Example.csv");
}

void MerkelMain::printHelp()
{
    std::cout << "Help is on the way" << std::endl;
}
void MerkelMain::printExchangeStats()
{
    double max,min = 0;
    double avg = 0.0;
    std::cout << "Market Information:" << std::endl;
    max = computeHighPrice(orders);
    min = computeLowPrice(orders);
    avg = averagePrice(orders);
        std::cout << "   Max price is: " << max << std::endl
                  << "   Low price is: " << min << std::endl
                  << "   Avg price is: " << avg << std::endl;
    countOrderTypes(orders);
}
void MerkelMain::makeOffer()
{
    std::cout << "Make an offer: " << std::endl;
}
void MerkelMain::makeBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}
void MerkelMain::printWallet()
{
    std::cout << "Your wallet has: " << std::endl;
}
void MerkelMain::processNext()
{
   std::cout << "Make your next selection." << std::endl; 
}

void MerkelMain::init()
{
    loadOrderBook();
    
    int option = 0;

    while(true)
    { 
        this->printMenu();
        option = this->getUserOption();

        if(option == 7) break; //Exit program
        else if(option > 0) this->processUserOption(option);
    }
}
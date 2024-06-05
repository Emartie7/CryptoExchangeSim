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
 * @file main.cpp
 * @author Edward Martinez
 * @brief Entry point for currency exchange simulator.
 * @version 0.1
 * @date 2024-05-16
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
#include <vector>
#include "UserMenuIF.h"
#include "OrderBookLib.h"
/********************************************//**
 *  Defines
 ***********************************************/

/********************************************//**
 *  Local Params
 ***********************************************/

/********************************************//**
 *  Local functions
 ***********************************************/


/***************************************************************************//**
 * printMenu(void)
 *
 * Print menu options to terminal.
 *
 * @param none Nothing yet
 ******************************************************************************/
void printMenu()
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
int getUserOption()
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
void processUserOption(std::map<int,void(*)()> mFuncs, int selection)
{
    void (*optFunc) () = mFuncs[selection];
    optFunc();
    std::cout << std::endl;
}

void MerkleRexMain(void)
{
    std::map<int,void(*)()> menuFuncs;
    int option = 0;

    menuFuncs[1] = printHelp;
    menuFuncs[2] = printExchangeStats;
    menuFuncs[3] = makeOffer;
    menuFuncs[4] = makeBid;
    menuFuncs[5] = printWallet;
    menuFuncs[6] = processNext;

    while(true)
    { 
        printMenu();
        option = getUserOption();

        if(option == 7) break; //Exit program
        else if(option > 0) processUserOption(menuFuncs,option);
    }
}

void classesFunc(void)
{
    std::vector<OrderBookEntry> entries;
    double max,min = 0.0;
    entries.push_back(OrderBookEntry{"2020/03/17 17:01:24.884492","BTC/USDT",OrderBookType::ask,5.750,0.00575});
    entries.push_back(OrderBookEntry{"2020/03/17 17:01:24.884492","ETH/BTC",OrderBookType::bid,0.02186299,0.1});
    entries.push_back(OrderBookEntry{"2020/03/17 17:01:55.120438","DOGE/BTC",OrderBookType::bid,0.0000003,29468687.918283});
    entries.push_back(OrderBookEntry{"2020/03/17 17:01:55.120438","DOGE/BTC",OrderBookType::ask,0.00000031,11905712.11186});
    entries.push_back(OrderBookEntry{"2020/03/17 17:01:55.120438","ETH/USDT",OrderBookType::bid,117.2971325,6.0});

    printEntryPrices(entries);
    max = computeHighPrice(entries);
    min = computeLowPrice(entries);

    std::cout << "Max price is: " << max << std::endl
              << "Low price is: " << min << std::endl;
}

/***************************************************************************//**
 * Main(void)
 *
 * Present user with an interactive menu. Always returns 0
 *
 * @param none Nothing yet
 ******************************************************************************/
int main(void)
{
    // classesFunc();
    MerkleRexMain();
    return 0;
}
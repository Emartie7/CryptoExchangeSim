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
 * @file UserMenuIF.cpp
 * @author Edward Martinez
 * @brief Source file for processing user selections made in the MerkleRex menu.
 * @version 0.1
 * @date 2024-05-28
 * 
 * @copyright Copyright (c) 2024
 * 
 * The MerkelMain class acts as the main engine for the currency exchange simulator.
 * 
 * Assumptions, Restrictions and limitations:
 * 1. Limited to a single input dataset.
 * 2. Data set must be specified upon initialization.
 * 
 */
/********************************************//**
 *  Includes
 ***********************************************/
#include "UserMenuIF.h"
#include "CsvReader.h"
#include "OrderBookLib.h"
/** @cond STDINCLUDES */
#include <iostream>
#include <map>
#include <string>
#include <sstream>
/** @endcond */
/********************************************//**
 *  Defines
 ***********************************************/
#define USER_BIDASK_NTOKENS 3
/********************************************//**
 *  Local Params
 ***********************************************/

/********************************************//**
 *  Function Implementations
 ***********************************************/
/**
 * @brief Constructor for MerkelMain.
 * 
 * @param filename Path to csv file containing order data set.
 */
MerkelMain::MerkelMain(std::string filename)
{
    try
    {
        this->orderBook = OrderBook{filename};
        this->state = MerkelState::READY;
    }
    catch(const std::exception& e)
    {
        this->state = MerkelState::WAITING;
        std::cout << "MerkelMain - Warning: failed to initialize MerkelMain data set." << std::endl;
        // throw;
    }
}


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
    std::cout << "The current time is: " << currentTime << std::endl;
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Make an ask" << std::endl;
    std::cout << "4: Make a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Go to next timeframe" << std::endl;
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
 * @return User selection
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
    switch(selection)
    {
        case 1:
            this->printHelp();
            break;
        case 2:
            this->printExchangeStats();
            break;
        case 3:
            this->enterAsk();
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

/**
 * @brief Prints exchange help message.
 */
void MerkelMain::printHelp()
{
    std::cout << "Help is on the way" << std::endl;
}

/**
 * @brief Prints summary information about the currencies and orders available on the exchange.
 */
void MerkelMain::printExchangeStats()
{
    double max,min = 0;
    double avg = 0.0;
    // std::string currentTime = "2020/03/17 17:01:24.884492";
    std::cout << "Market Information:" << std::endl;
    for(const std::string & prod : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << prod << std::endl;
        std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookType::ask, prod, currentTime);
        std::vector<OrderBookEntry> entriesBids = orderBook.getOrders(OrderBookType::bid, prod, currentTime);

        std::cout << "   Asks seen: " << entriesAsk.size() << std::endl
                  << "   Max ask  : " << orderBook.getHighPrice(entriesAsk) << std::endl
                  << "   Min ask  : " << orderBook.getLowPrice(entriesAsk) << std::endl 
                  << "   Spread   : " << orderBook.getSpread(entriesAsk) << std::endl << std::endl;

        std::cout << "   Bids seen: " << entriesBids.size() << std::endl
                  << "   Max Bid  : " << orderBook.getHighPrice(entriesBids) << std::endl
                  << "   Min Bid  : " << orderBook.getLowPrice(entriesBids) << std::endl
                  << "   Spread   : " << orderBook.getSpread(entriesBids) << std::endl << std::endl;
    }
}

/**
 * @brief Generate an Ask to be added to the orderbook.
 * 
 * Prompts user for input to generate an OrderBookEntry object which is added to orderbook at the current time.
 * Ask must be in the format: "BTC/ETH,200,5" where:
 * BTC -> product we are offering for sale
 * ETH -> product we are requesting
 * 200 -> amount of requested product (i.e. ETH) we are asking for
 * 5   -> amount of sale product (i.e. BTC) we are offering for the requested product
 */
void MerkelMain::enterAsk()
{
    std::string askStr;
    
    std::cout << "Make an ask - enter the amount: product, price, amount. E.g: ETH/BTC,200,0.5" << std::endl;

    std::getline(std::cin, askStr);
    std::cout << "   You entered: " << askStr << std::endl;
    std::vector<std::string> tokens = CsvReader::tokenise(askStr,',');

    if(tokens.size() != USER_BIDASK_NTOKENS)
    {
        std::cout << "MerkelMain::enterAsk - Not enough tokens in user input." << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = OrderBookEntry::stringsToOBE(tokens[1],
                                                        tokens[2],
                                                        currentTime,
                                                        tokens[0],
                                                        OrderBookType::ask);
            obe.username = "simuser";

            if(this->wallet.canFulfillOrder(obe))
            {
                std::cout << "   MerkelMain::enterAsk - Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "   MerkelMain::enterAsk - Insufficient funds to process order." << std::endl;
            }
            
        }
        catch(const std::exception &e)
        {
            std::cout << "MerkelMain::enterAsk - Error in converting string inputs to OBE." << std::endl;
            std::cout << "   Exception:" << e.what() << std::endl;
        }
    }
}

/**
 * @brief Generate an Bid to be added to the orderbook.
 * 
 * Prompts user for input to generate an OrderBookEntry object which is added to orderbook at the current time.
 * Bid must be in the format: "DOGE/BTC,0.25,5" where:
 * DOGE -> product we want to buy
 * BTC  -> product we are offering
 * 0.25 -> Offered price (i.e [BTC price]/[DOGE price])
 * 5    -> Amount of product we want to buy (i.e. how much DOGE we want to buy.)
 */
void MerkelMain::makeBid()
{
    std::string askStr;
    
    std::cout << "Make a bid - enter the amount: product, price, amount. E.g: ETH/BTC,200,0.5" << std::endl;

    std::getline(std::cin, askStr);
    std::cout << "   You entered: " << askStr << std::endl;
    std::vector<std::string> tokens = CsvReader::tokenise(askStr,',');
    
    if(tokens.size() != USER_BIDASK_NTOKENS)
    {
        std::cout << "MerkelMain::makeBid - WARNING: User input contains incorrect number of tokens." << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = OrderBookEntry::stringsToOBE(tokens[1],
                                                        tokens[2],
                                                        currentTime,
                                                        tokens[0],
                                                        OrderBookType::bid);
            obe.username = "simuser";
            if(this->wallet.canFulfillOrder(obe))
            {
                std::cout << "   MerkelMain::makeBid - Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "   MerkelMain::makeBid - Insufficient funds to process order." << std::endl;
            }
        }
        catch(const std::exception &e)
        {
            std::cout << "MerkelMain::makeBid - Error in converting string inputs to OBE." << std::endl;
            std::cout << "   Exception:" << e.what() << std::endl;
        }
    }
}

/**
 * @brief Prints contents of wallet to console.
 */
void MerkelMain::printWallet()
{
    std::cout << "Your wallet has " << this->wallet.getWalletLen() << " currencies" << std::endl;
    std::cout << this->wallet << std::endl;
}
void MerkelMain::processNext()
{
   std::cout << "Going to next time step." << std::endl;

   for(std::string &p : orderBook.getKnownProducts())
   {
        std::cout << "Matching bids/asks for : " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p,currentTime);
        std::cout << "Sales: "<< sales.size() << std::endl;
        for(OrderBookEntry & sale : sales)
        {
            std::cout << "   Sale price: " << sale._price << " amount " << sale._amount << std::endl;
            //Verification that user wallet can support sale is performed when bid/ask is added 
            //to orderbook. This could be changed . . .
            if(("simuser" == sale.username))
            {
                this->wallet.processSale(sale);
            }
        }
   }
   currentTime = orderBook.getNextTime(currentTime); 
}
/**
 * @brief Public method for viewing current time in simulation.
 */
std::string MerkelMain::getCurrentTime()
{
    return this->currentTime;
}

/**
 * @brief Public method for obtaining a copy of the current orders in simulation.
 */
OrderBook MerkelMain::getOrders()
{
    return this->orderBook;
}

/**
 * @brief Public method for viewing current state of the exchange sim.
 */
MerkelState MerkelMain::getCurrentState()
{
    return this->state;
}

/**
 * @brief Executes the main loop for the MerkelMain exchange sim.
 */
void MerkelMain::run()
{
    int option = 0;
    while(true)
    { 
        this->printMenu();
        option = this->getUserOption();

        if(option == 7) break; //Exit program
        else if(option > 0) this->processUserOption(option);
    }
}

/**
 * @brief Initialize and run MerkelMain exchange simulator.
 * 
 * Verifies that orderbook data has been properly loaded. 
 * Adds an initial amount of currency to the users wallet to 
 * allow trading.
 * 
 * Allows user to specify whether application should be started in 
 * "debug" mode, which will initialize application class and underlying
 * wallet, but NOT enter the main loop (i.e. user input will not be 
 * acepted from terminal).
 * 
 * @param debug Boolean flag to indicate whether application should run in debug mode.
 */
void MerkelMain::init(bool debug)
{
    std::string initProd = "BTC";
    double initAmt       = 10.0f;
    this->wallet.insertCurrency("BTC",10);
    if((MerkelState::READY == this->state))
    {
        currentTime = orderBook.getEarliestTime();
    }
    if((MerkelState::READY == this->state) && (!debug))
    {
        std::cout << "Initializing MerkelMain . . ." << std::endl;
        
        this->state = MerkelState::RUN;
        this->run();
        this->state = MerkelState::READY;
    }
}
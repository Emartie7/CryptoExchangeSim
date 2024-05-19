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

/********************************************//**
 *  Defines
 ***********************************************/

/********************************************//**
 *  Local Params
 ***********************************************/


/***************************************************************************//**
 * Main(void)
 *
 * Present user with an interactive menu. Always returns 0
 *
 * @param none Nothing yet
 ******************************************************************************/
int main(void)
{
    int userOption = 0;
    /* 
    //1 Print help
    //2 print exchange stats
    //3 make an offer
    //4 make a bid
    //5 print wallet
    //6 continue 
    //7 Exit program
    */
    while(true)
    {
        
        std::cout << "1: Print help" << std::endl;
        std::cout << "2: Print exchange stats" << std::endl;
        std::cout << "3: Make an offer" << std::endl;
        std::cout << "4: Make a bid" << std::endl;
        std::cout << "5: Print wallet" << std::endl;
        std::cout << "6: Continue" << std::endl;
        std::cout << "7: Exit" << std::endl;
        std::cout << "=================================" << std::endl;

        std::cout << "Type in 1-6" << std::endl;
        std::cin >>userOption;
        std::cout << "You chose: " << userOption << std::endl;

        if(userOption==7) break; //Exit while loop upon user request

        switch(userOption)
        {
            case 1:
                std::cout << "Help is on the way" << std::endl;
                break;
            case 2:
                std::cout << "Market looks good" << std::endl;
                break;
            case 3:
                std::cout << "Make an offer: " << std::endl;
                break;
            case 4:
                std::cout << "Make a bid - enter the amount" << std::endl;
                break;
            case 5:
                std::cout << "Your wallet has: " << std::endl;
                break;
            case 6:
                std::cout << "Make another selection!" << std::endl;
                break;
            default: std::cout << "WARNING: Invalid input, enter 1-6" << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
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
#include "UserMenuIF.h"

/********************************************//**
 *  Defines
 ***********************************************/
#define FNAME_DATA_NOMINAL "DataSets/OrderBook_Example.csv"
/********************************************//**
 *  Local Params
 ***********************************************/

/********************************************//**
 *  Class defines
 ***********************************************/

/********************************************//**
 *  Local functions
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
    MerkelMain app{FNAME_DATA_NOMINAL};
    app.init();
    return 0;
}
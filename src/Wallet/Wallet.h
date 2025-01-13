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
 * @file Wallet.h
 * @author Edward Martinez
 * @brief Interface for simulator wallet.
 * @version 0.1
 * @date 2024-07-15
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
#include <map>
#include <OrderBookLib.h>
/** @endcond */

/********************************************//**
 *  Class Definitions
 ***********************************************/
/*! @class Wallet
    @brief Class for currency exchange wallet.

    Serves as a wrapper for storing and handling currencies to be traded on the exchange.
*/
class Wallet
{
    public:
        Wallet();
        void insertCurrency(std::string type, double amount);
        bool removeCurrency(std::string type, double amount);
        bool containsCurrency(std::string type,double amount);
        std::string toString();
        bool canFulfillOrder(const OrderBookEntry & order);
        friend std::ostream & operator<<(std::ostream & os,Wallet & wallet);
        void processSale(OrderBookEntry & sale);
        int getWalletLen();
    private:
        std::map<std::string, double> currencies;
};
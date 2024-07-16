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
 * @file Wallet.cpp
 * @author Edward Martinez
 * @brief Header file for functionality related to currency wallet.
 * @version 0.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************//**
 *  Includes
 ***********************************************/
#include <iostream>
#include <string>
#include "Wallet.h"
#include <stdexcept>

/**
 * @brief Constructor for Wallet class.
 */
Wallet::Wallet()
{
    
}

/**
 * @brief Adds currency to Wallet.
 * @param type Currency type (ETH, BTC, etc.) to be added.
 * @param amount Amount of currency to be added. Must be non-negative.
 */
void Wallet::insertCurrency(std::string type, double amount)
{
    if(amount >= 0)
    {
        if(0 != this->currencies.count(type))
        {
            this->currencies[type] += 0;
        }
        else
        {
            this->currencies[type] = amount;
        }
    }
    else
    {
        throw std::runtime_error(std::string("Wallet::insertCurrency - Received negative currency amount."));
    }
}

/**
 * @brief Removes currency from Wallet.
 * @param type Currency type (ETH, BTC, etc.) to be removed.
 * @param amount Amount of currency to be removed. Must be non-negative.
 * @return TRUE if removal operation is successful.
 *         FALSE if removal operation fails or currency DNE in wallet in specified amount.
 */
bool Wallet::removeCurrency(std::string type, double amount)
{
    try
    {
        if(this->containsCurrency(type,amount))
        {
            this->currencies[type] -= amount;
            return true;
        }
    }
    catch(const std::exception & e)
    {
        std::cout << "Wallet::removeCurrency - Exception while removing currency." << std::endl;
        std::cout << e.what() << std::endl;
    }
    return false;
}

/**
 * @brief Determines whether currency exists in wallet in the specified amount.
 * @param type Currency type (ETH, BTC, etc.) searched.
 * @param amount Amount of currency to be found.
 * @return TRUE amount of currency exists in wallet.
 *         FALSE if currency DNE in wallet in specified amount.
 */
bool Wallet::containsCurrency(std::string type, double amount)
{
    if(amount < 0)
    {
        throw std::runtime_error(std::string("Wallet::containsCurrency - Received negative currency amount."));
    }

    if(this->currencies.count(type) > 0) //We have this type of currency
    {
        if(this->currencies[type] >= amount) return true; //Return true if we have at least the specified amount
    }
    return false;
}

/**
 * @brief Prints Wallet contents to console.
 */
std::string Wallet::toString()
{
    std::string s;

    for(std::pair <std::string, double> pair : this->currencies)
    {
        std::string currency = pair.first;
        double amount        = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

std::ostream & operator << (std::ostream &os, Wallet & wallet)

{
    os << wallet.toString();
    return os;
}
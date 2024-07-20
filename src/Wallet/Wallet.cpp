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
#include "CsvReader.h"
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
        // std::cout << "Wallet::insertCurrency - Adding " << amount << " of " << type << " to wallet." << std::endl;
        if(0 != this->currencies.count(type))
        {
            this->currencies[type] += 0;
        }
        else
        {
            // std::cout << "   Wallet::insertCurrency - Adding new currency to wallet" << std::endl;
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

/**
 * @brief Determines whether wallet can satisfy the transaction described by an OBE.
 * 
 * An ask of product type "ETH/BTC" means the user is selling ETH for BTC - has first, wants second
 * A bid of product  type "ETH/BTC" means the user is buying ETH for BTC - has second, wants first
 * Only intended to operate on "bid" or "sale" OBE types.
 * @param order OBE describing the ask/sale.
 * @return TRUE transaction can be performed with the available funds in wallet.
 *         FALSE if not.
 */
bool Wallet::canFulfillOrder(const OrderBookEntry & order)
{
    //Split a string "ETH/BTC" into a vector ["ETH","BTC"]
    std::vector <std::string> products = CsvReader::tokenise(order._product,'/');

    //This is the product user has and needs to verify.
    std::string tradeProd;

    //Transaction amount
    double amount = 0.0f; 

    if(OrderBookType::ask == order._OrderType)
    {
        amount = order._amount;
        tradeProd = products[0];
    }
    else if(OrderBookType::bid == order._OrderType)
    {
        amount = order._amount * order._price; //Calculate how much of the product we need.
        tradeProd = products[1];
    }
    else
    {
        std::cout << "Wallet::canFulfillOrder - Warning: unsupported OBE order type." << std::endl;
        return false;
    }
    std::cout << "Wallet::canFulfillOrder - checking wallet for " << amount << " " << tradeProd << std::endl;
    return this->containsCurrency(tradeProd,amount);
}

int Wallet::getWalletLen()
{
    return this->currencies.size();
}

void Wallet::processSale(OrderBookEntry & sale)
{
    std::vector<std::string> currs = CsvReader::tokenise(sale._product,'/');
    if(OrderBookType::asksale == sale._OrderType)
    {
        double outGoingAmount = sale._amount;
        double incomingAmount = sale._amount * sale._price;
        std::string outGoingCurrency = currs[0];
        std::string incomingCurrency = currs[1];

        this->currencies[incomingCurrency] += incomingAmount;
        this->currencies[outGoingCurrency] -= outGoingAmount;
    }
    else if(OrderBookType::bidsale == sale._OrderType)
    {
        double outGoingAmount = sale._amount * sale._price;
        double incomingAmount = sale._amount;
        std::string outGoingCurrency = currs[1];
        std::string incomingCurrency = currs[0];

        this->currencies[incomingCurrency] += incomingAmount;
        this->currencies[outGoingCurrency] -= outGoingAmount;
    }
    else
    {
        std::cout << "Wallet::processSale - ERROR: attempting to process unsupported sale type." << std::endl;
        throw std::runtime_error(std::string("Wallet::processSale - attempting to process unsupported sale type."));
    }
}
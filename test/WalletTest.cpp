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
 * @file WalletTest.cpp
 * @author Edward Martinez
 * @brief Unit test case definition for Wallet class.
 * @version 0.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/********************************************//**
 *  Includes
 ***********************************************/
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/OrderBookLib/OrderBookLib.h"
#include "../src/OrderBookLib/OrderBook.h"
#include "../src/UserMenuIF/UserMenuIF.h"
#include "../src/Wallet/Wallet.h"
/**
 * @brief Test fixture for ADDING currency to Wallet
 */
class WalletAdditionTests : public testing::Test
{
    protected:

    WalletAdditionTests()
    {
        wallet01.insertCurrency(prod,amount);
    }
    Wallet wallet01{};
    std::string prod  = "BTC";
    double amount = 1.5;
};

/**
 * @brief Test fixture for REMOVING currency to Wallet
 */
class WalletSubtractionTests : public testing::Test
{
    protected:

    WalletSubtractionTests()
    {
        wallet02.insertCurrency(prod,amount);
    }
    Wallet wallet02{};
    std::string prod  = "BTC";
    double amount = 10;
};
/**********************************************************
 *  Currency addition tests
 **********************************************************/
/**
 *  Check that the balance == what we put in
 */
TEST_F(WalletAdditionTests,TestCase_01)
{
    EXPECT_THAT(wallet01.containsCurrency(prod,amount),true);
}

/**
 *  Check that the product == what we put in
 */
TEST_F(WalletAdditionTests,TestCase_02)
{
    EXPECT_THAT(wallet01.containsCurrency("BTC",amount),true);
}

/**
 *  Check wallet print
 */
TEST_F(WalletAdditionTests,TestCase_03)
{
    EXPECT_THAT(wallet01.toString(),testing::StartsWith("BTC"));
}

/**********************************************************
 *  Currency removal tests
 **********************************************************/

/**
 *  Check that the balance != original amount following a removal
 */
TEST_F(WalletSubtractionTests,TestCase_01)
{
    double balance = amount;
    double amountRem = 4.5;
    wallet02.removeCurrency(prod,amountRem);
    EXPECT_THAT(wallet02.containsCurrency(prod,balance),false);
}

/**
 *  Check that the balance is what is expected after a removal
 */
TEST_F(WalletSubtractionTests,TestCase_02)
{
    double amountRem = 4.5;
    double balance = amount - amountRem;
    wallet02.removeCurrency(prod,amountRem);
    EXPECT_THAT(wallet02.containsCurrency(prod,balance),true);
}

/**
 *  Remove all of the balance of a currency
 */
TEST_F(WalletSubtractionTests,TestCase_03)
{
    double amountRem = amount;
    wallet02.removeCurrency(prod,amountRem);
    EXPECT_THAT(wallet02.containsCurrency(prod,0.0f),true);
}

/**
 *  Remove a currency that DNE
 */
TEST_F(WalletSubtractionTests,TestCase_04)
{
    double amountRem = 1.0;
    std::string prodRem = "ETH";
    EXPECT_THAT(wallet02.removeCurrency(prodRem,amountRem),false);
}

/**
 *  Remove more than we have
 */
TEST_F(WalletSubtractionTests,TestCase_05)
{
    double amountRem = amount + 1.0f;
    
    EXPECT_THAT(wallet02.removeCurrency(prod,amountRem),false);
}
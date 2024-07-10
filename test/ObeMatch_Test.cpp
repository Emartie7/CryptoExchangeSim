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
 * @file ObeMatch_Test.cpp
 * @author Edward Martinez
 * @brief Unit test case definition for OrderBook::matchAsksToBids().
 * @version 0.1
 * @date 2024-07-08
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

/********************************************//**
 *  Defines
 ***********************************************/
#define TESTCASE_01_FNAME "DataSets/MatchTest_01.csv"
#define TESTCASE_02_FNAME "DataSets/MatchTest_02.csv"
#define TESTCASE_03_FNAME "DataSets/MatchTest_03.csv"
#define TESTCASE_04_FNAME "DataSets/MatchTest_04.csv"
/********************************************//**
 *  GTest Fixtures
 ***********************************************/

/**
 *  Bid/Asks matching test fixture
 */
class MatchingTest : public testing::Test
{
    protected:

    MatchingTest()
    {
        TC01_sim.init(true);
        TC02_sim.init(true);
        TC03_sim.init(true);
        TC04_sim.init(true);
    }
    MerkelMain TC01_sim{TESTCASE_01_FNAME};
    MerkelMain TC02_sim{TESTCASE_02_FNAME};
    MerkelMain TC03_sim{TESTCASE_03_FNAME};
    MerkelMain TC04_sim{TESTCASE_04_FNAME};
};

TEST_F(MatchingTest,TestCase_01)
{
    std::string prod  = "ETH/BTC";
    std::string time  = TC01_sim.getCurrentTime();
    OrderBook data    = TC01_sim.getOrders();

    EXPECT_THAT(data.matchAsksToBids(prod,time).size(),testing::Eq(1));
}

TEST_F(MatchingTest,TestCase_02)
{
    std::string prod  = "ETH/BTC";
    std::string time  = TC02_sim.getCurrentTime();
    OrderBook data    = TC02_sim.getOrders();
    std::vector<OrderBookEntry> TC02_sales = data.matchAsksToBids(prod,time);
    EXPECT_THAT(TC02_sales.size(),testing::Eq(1)); //Verify that only one sale was made

    EXPECT_LT(TC02_sales[0]._amount,1.0); //Verify that sale amount was less than ask amount (1.0).
}

TEST_F(MatchingTest,TestCase_03)
{
    std::string prod  = "ETH/BTC";
    std::string time  = TC03_sim.getCurrentTime();
    OrderBook data    = TC03_sim.getOrders();
    std::vector<OrderBookEntry> TC03_sales = data.matchAsksToBids(prod,time);
    EXPECT_THAT(TC03_sales.size(),testing::Eq(3)); //Verify expected # of sales

    EXPECT_THAT(TC03_sales[0]._amount,testing::Eq(0.25)); //Verify that first sale made (highest bid) is the expected amount
    EXPECT_THAT(TC03_sales[1]._amount,testing::Eq(0.5));  //Verify that second sale made is the expected amount
    EXPECT_THAT(TC03_sales[2]._amount,testing::Eq(0.25)); //Verify that third sale made is the expected amount
}

TEST_F(MatchingTest,TestCase_04)
{
    std::string prod  = "ETH/BTC";
    std::string time  = TC03_sim.getCurrentTime();
    OrderBook data    = TC03_sim.getOrders();
    std::vector<OrderBookEntry> TC03_sales = data.matchAsksToBids(prod,time);
    EXPECT_THAT(TC03_sales.size(),testing::Eq(3)); //Verify expected # of sales

    //Verify that if bid is higher than ask, sale is made at the lower of the two (ask).
    EXPECT_THAT(TC03_sales[0]._price,testing::Eq(0.021873));
    EXPECT_THAT(TC03_sales[1]._price,testing::Eq(0.021873));
    EXPECT_THAT(TC03_sales[2]._price,testing::Eq(0.021873));
}

TEST_F(MatchingTest,TestCase_05)
{
    std::string prod  = "ETH/BTC";
    std::string time  = TC04_sim.getCurrentTime();
    OrderBook data    = TC04_sim.getOrders();
    std::vector<OrderBookEntry> TC04_sales = data.matchAsksToBids(prod,time);
    EXPECT_THAT(TC04_sales.size(),testing::Eq(1)); //Verify expected # of sales

    EXPECT_THAT(TC04_sales[0]._price,testing::Eq(0.021873)); //Verify that first sale made (highest bid) is the expected amount
}


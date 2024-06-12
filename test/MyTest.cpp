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
 * @file MyTest.cpp
 * @author Edward Martinez
 * @brief Unit test case definition for OrderBookLib.
 * @version 0.1
 * @date 2024-06-11
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

/********************************************//**
 *  GTest Fixtures
 ***********************************************/

/**
 *  Tokenise test fixture
 */
class TokeniseTest : public testing::Test
{
  protected:
  /**
   * @brief A constructor
   * Initializes a vector of strings to test the tokenise function in "OrderBookLib.h"
   */
  TokeniseTest()
  {
    StrIn.push_back("I,Have,Four,Tokens"); //Expect 4
    StrIn.push_back("Ihavenotokens");      //Expect 1
    StrIn.push_back(",beginwithtoken");    //Expect 1
    StrIn.push_back("endwithtoken,");      //Expect 1
    StrIn.push_back(",,,,,,,,,,,");        //Expect 0
  }
  /**
   * Protected string vector.
   */
  std::vector <std::string> StrIn;

};
/**
 * @brief Tests a "nominal" tokenisation operation.
 */
TEST_F(TokeniseTest,len_nominal)
{
  EXPECT_THAT(tokenise(StrIn[0],',').size(),testing::Eq(4));
}

/**
 * @brief Tests a tokenisation operation where no delimiters are present.
 */
TEST_F(TokeniseTest,len_NoDelim)
{
  EXPECT_THAT(tokenise(StrIn[1],',').size(),testing::Eq(1));
}

/**
 * @brief Tests a tokenisation operation where only delimiters are present.
 */
TEST_F(TokeniseTest,len_OnlyDelim)
{
  EXPECT_THAT(tokenise(StrIn[4],',').size(),testing::Eq(0));
}
/**
 * @brief Tests a tokenisation operation where delimiter is present at the beginning of input string.
 */
TEST_F(TokeniseTest,len_DelimStart)
{
  EXPECT_THAT(tokenise(StrIn[2],',').size(),testing::Eq(1));
}

/**
 * @brief Tests a tokenisation operation where delimiter is present at the end of input string.
 */
TEST_F(TokeniseTest,len_DelimEnd)
{
  EXPECT_THAT(tokenise(StrIn[3],',').size(),testing::Eq(1));
}


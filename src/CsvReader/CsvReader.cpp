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
 * @file CsvReader.h
 * @author Edward Martinez
 * @brief Source code for reading data sets from CSV files.
 * @version 0.1
 * @date 2024-06-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/********************************************//**
 *  Includes
 ***********************************************/
#include "CsvReader.h"
#include <iostream>
#include <fstream>
#include <vector>
/********************************************//**
 *  Defines
 ***********************************************/
#define ORDERBOOK_ENT_NTOKENS 5

/********************************************//**
 *  Class Implementations
 ***********************************************/
CsvReader::CsvReader()
{

}

std::vector<OrderBookEntry> CsvReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;
    

    std::vector<std::string> tokens;
    std::string csvDataFileName{csvFilename};
    std::ifstream csvFile{csvDataFileName};
    std::string line;
    unsigned int stats = 0;
    int nLines = 0;
    int nErr = 0;

    if(csvFile.is_open())
    {
        // std::cout << "Opened File: " << csvDataFileName << std::endl;
        while(std::getline(csvFile,line))
        {
            tokens = tokenise(line,',');
            if(ORDERBOOK_ENT_NTOKENS != tokens.size())

            {
                std::cout << "CsvReader::readCSV - Bad line, not enough tokens." << std::endl;
                nErr++;
                continue;
            }

            try
            {
                entries.push_back(stringsToOBE(tokens));
                nLines++;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }       
        // std::cout << std::endl << std::endl << "Summary of lines processed: " << std::endl;
        // std::cout << "   Tokenised line count: " << entries.size() << std::endl;
        // std::cout << "   Invalid line count: " << nErr << std::endl;
        csvFile.close(); 
    }
    else std::cout << "CsvReader::readCSV - Error opening file " << csvDataFileName << std::endl;

    return entries;
}

std::vector<std::string> CsvReader::tokenise(std::string lineIn, char separator)
{
    std::vector<std::string> tokens;
    std::string Token;
    int start, end;

    start = lineIn.find_first_not_of(separator,0);

    do
    {
        end = lineIn.find_first_of(separator,start);
        if (start == lineIn.length() or (start == end))
            break;
        if(end >= 0)
        {
            Token = lineIn.substr(start, end - start); //Slice from current start idx to next delimiter
        }
        else
        {
            Token = lineIn.substr(start,lineIn.length()-start); //Get the remainder of the line
        }
        tokens.push_back(Token);
        start = end + 1;
    } while (end > 0);
    
    return tokens;
}
/**
 * @brief Generates a OrderBookEntry object.
 * 
 * Takes a vector of strings and converts types to return a new OBE.
 * @param tokens Vector containing OBE attributes as strings.
 */
OrderBookEntry CsvReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;
    try
    {
        //OrderBook typecast
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch(const std::exception& e)
    {
        std::cout << "CsvReader::stringsToOBE - Error in string to OBE type conversion." << std::endl;
        std::cout << "   " << e.what() << std::endl;
        throw;
    }
    OrderBookEntry obe{tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToObeType(tokens[2]),
                       price,
                       amount};
    return obe;
}

/**
 * @brief Generates a OrderBookEntry object.
 * 
 * Takes string args. and converts types to return a new OBE.
 * @param priceString Order price as a string
 * @param amountString Order amount as a string
 * @param timestamp Timestamp as a string
 * @param product Product type (i.e. "BTC/ETH" as a string
 * @param orderType Bid or Ask
 */
OrderBookEntry CsvReader::stringsToOBE(std::string priceString,
                                    std::string amountString,
                                    std::string timestamp,
                                    std::string product,
                                    OrderBookType orderType)
{
    double price, amount;
    try 
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }catch(const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl;
        throw; // throw up to the calling function
    }
    OrderBookEntry obe{timestamp,
                       product,
                       orderType,
                       price,
                       amount
    };
    return obe;   
}
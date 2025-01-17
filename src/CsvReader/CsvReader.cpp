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
 * @file CsvReader.cpp
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
/** @cond */
#include <iostream>
#include <fstream>
#include <vector>
/** @endcond */
/********************************************//**
 *  Defines
 ***********************************************/
#define ORDERBOOK_ENT_NTOKENS 5

/********************************************//**
 *  Class Implementations
 ***********************************************/
/**
 * @brief CSV reader constructor.
 */
CsvReader::CsvReader()
{

}

/**
 * @brief Reads a CSV file containing orderbook entry data into a vector.
 * 
 * Uses an input file stream to read a CSV file. Each line is tokenised into
 * orderbook entry objects. If the line does not contain the required amount of tokens
 * as specified by ORDERBOOK_ENT_NTOKENS, the line is skipped.
 * 
 * @see OrderBookEntry class for the expected data and its format.
 * @param csvFilename path to CSV file to be used as input.
 * @return A vector of orderbook entry objects read in from file.
 */
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
                nErr++;
                continue;
            }

            try
            {
                entries.push_back(OrderBookEntry::stringsToOBE(tokens));
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

/**
 * @brief Tokenises input string into sub-components as separated by the input char.
 * 
 * Slices input string into components, delimited by the input 'separator'. 
 * 
 * @param lineIn String to be tokenised
 * @param separator Delimiter for string slicing operations.
 * @return A vector containing the sliced componenets of the input string.
 */
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
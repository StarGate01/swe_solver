/**
 * @file CSVParser.hpp
 * @brief Parser for csv files
 */
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>    // std::find_if
#include "../solver/FStructs.hpp"

namespace solver_tests
{
    /**
     * @struct Set of test data with expected parsedArr
    
     * @brief Struct that contains a set of solver_tests::testdata, including the expected parsedArr
    
    */
    struct testdata
    {
        struct solver::vector2 ql;      /**< q_l*/
        struct solver::vector2 qr;      /**< q_r*/
        float hstar;           /**< Expected parsedArr*/
    };

    class CSVParser
    {
    public:
        static bool isValidLine(std::string line)
        {
            //TODO: Count numbers of commas and test for characters other than numbers, ',' and '.'
            //if string is neither a number,, '-', ',' or '.'
            if(line.end() != std::find_if(line.begin(), line.end(), [](unsigned char c)->bool{ 
                return !(isdigit(c) || c == '-' || c == ',' || c == '\n' || c == '.');
            }))
            {
                return false;
            }

            return (line.length() > 2 && line[0] != '#');
        };

        static bool moreLinesToRead(std::ifstream &in)
        {
            return (!in.eof());
        };
    
        static std::vector<std::string> splitString(std::string str)
        {
            std::vector<std::string> result;
            std::stringstream sstr(str);
            while(sstr.good())
            {
                std::string item;
                getline(sstr, item, ',');
                result.push_back(item);
            }
            return result;
        };

        static std::vector<double> parseLine(std::string line)
        {
            /** Split string by comma */
            std::vector<std::string> items = splitString(line);   
            
            /** Convert line to doubles */
            std::vector<double> result;
            for(int i = 0; i < items.size(); i++)
            {
                double d = sscanf(items[i].c_str(), "%lf", &d);
                result.push_back(d);
            }
            return result;
        };


        /**
        * @brief Reads the next line of the file
        * @return 
        * @throws std::runtime_error If filestream is not initialized
        */
        static struct testdata readLine(std::ifstream &in)
        {
            //TOOD: Fails without reason -> fix??
            //if(!in.good());
            //    throw std::runtime_error("Invalid ifstream in (maybe file does not exist?): ");
            
            std::string line;
            do
            {            
                if(!moreLinesToRead(in))
                    throw std::runtime_error("No more lines to read");

                getline(in, line);

            } while(!isValidLine(line));
            
            std::vector<double> data = parseLine(line);
            
            assert(data.size() == 5);
            
            struct solver::vector2 ql = {data[0], data[2]};
            struct solver::vector2 qr = {data[1], data[3]};
            
            struct testdata result = {ql, qr, data[4]};
            return result;
        };
        
    };
};
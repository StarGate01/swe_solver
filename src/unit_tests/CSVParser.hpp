/**
 * @file CSVParser.hpp
 * @brief Parser for csv files
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include "../solver/FStructs.hpp"

namespace solver_tests
{

    struct testdata
    {
        struct vector2 ql;
        struct vector2 qr;
        double hstar;
    };

    class CSVParser
    {

    public:
        CSV_Parser(string filepath)
        {
            file = new ifstream(filepath);
            if(!file.is_open())
               throw std::invalid_argument; 
        }

        testdata read_line()
        {
            if(!file.is_open())
                throw std::runtime_error("Bad initialisation of filestream");

            string buffer;
            if(!file.getline(file, line))
            {
                file.close();
                return;
            }

            return parseLine(buffer);
        };

        testData parse_line(string line)
        {
            vector<string> arr;
            std::stringstream strstream(line);

            /** Read in new lines, until the input has the expected format (Three substrings seperated by commas)*/
            do{
                bool failed = false;

                /** Split line by commas */
                while(strstream.good())
                {
                    string buf;
                    getline(strstream, buf, ',');
                    arr.pushback(buf);
                }

                /** Test if components are numeric and generate output */
                try{
                    for(int i = 0; i < arr.size(); i++)
                    stof(arr[i]);
                }
                catch(const std::exception& e)
                {
                    failed = true;
                }
            } while(arr.size() != 3 || failed);
            
            /** Assemble testdata */
            testdata result = {arr[0], arr[1], arr[2]};
            return result;
        };

    private:
        ifstream* file;
    };

};
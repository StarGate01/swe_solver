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

    /**
     * @struct Set of test data with expected result
     * @brief Struct that contains a set of solver_tests::testdata, including the expected result
    */
    struct testdata
    {
        struct vector2 ql;      /**< q_l*/
        struct vector2 qr;      /**< q_r*/
        double hstar;           /**< Expected result*/
    };

    class CSVParser
    {

    public:
        /**
         * @brief Constructor, that initializes the filestream for reading
         * @param filepath Path of th.csv file
         * @throws std::invalid_argument If path is invalid or file can not be opened
        */
        CSV_Parser(string filepath)
        {
            /** Create new filestream */
            file = new ifstream(filepath);

            /** Throw exception, if file cannot be opened*/
            if(!file.is_open())
               throw std::invalid_argument; 
        }

        /**
         * @brief Reads the next line of the file
         * @return If the file contains at least one line to read, returns the next line as solver_tests::testdata object; else returns NULL
         * @throws std::runtime_error If filestream is not initialized
        */
        testdata read_line()
        {
            /** Check if filestream is open*/
            if(!file.is_open())
                throw std::runtime_error("Bad initialisation of filestream");

            /** Read one line or close, if end of file is reached */
            string buffer;
            if(!file.getline(file, line))
            {
                file.close();
                return NULL;
            }
            return parseLine(buffer);
        };

        /**
         * @brief Parse string of text, consisting of three float numbers and seperated by commas, and returns them as solver_tests::testdata object
         * @param line Line of text to be parsed
         * @return Set of test data, if parsing was successful. Otherwise NULL
        */
        testdata parse_line(string line)
        {
            /** Initialize variables*/
            vector<string> arr;
            std::stringstream strstream(line);

            /** Read in new lines, until the input has the expected format (Three substrings seperated by commas)*/
            do{
                bool failed = false;

                /** Split line by commas */
                if(strstream.good())
                {
                    string buf;
                    getline(strstream, buf, ',');
                    arr.pushback(buf);
                    /** Test if components can be parsed as floats and generate output */
                    try{
                        for(int i = 0; i < arr.size(); i++)
                        stof(arr[i]);
                    }
                    catch(const std::exception& e)
                    {
                        /** Do not accept line as valid, when an element could not be parsed */
                        failed = true;
                    }
                }
                else
                {
                    return NULL;
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
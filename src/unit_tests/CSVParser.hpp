/**
 * @file CSVParser.hpp
 * @brief Parser for csv files
 */
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "../solver/FStructs.hpp"

namespace solver_tests
{
    /**
     * @brief Struct that contains a set of test data including the expected result
    */
    struct testdata
    {
        struct solver::vector2 ql;      /**< q_l*/
        struct solver::vector2 qr;      /**< q_r*/
        float hstar;           /**< Expected parsedArr*/
    };
    
    /**
     * @brief Special interpreter for .csv files
     * 
     * This interpreter for .csv files can only be used for files, contain data in a special format, where every line is of the form:
     *  hLeft,hRight,huLeft,huRight,hStar.
     *  Each line is returned as a solver_tests::testdata struct with the equivalent parameters set appropriatelly.
     */
    class CSVParser
    {
    private:
        /**
         * @brief Determines if a string is a valid data line in a csv file
         * 
         * A line is considered valid, if it consists of digits (0 to 9), commas, dots, minus and line breaks
         * 
         * @param line String to be tested
         * 
         * @return True, if line is considered valid. Otherwise false
        */
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
        
        /**
         * @brief Splits string at commas
         * 
         * The slices are kept in order of their occurence
         * 
         * @param String to be sliced
         * 
         * @return std:vector<std::string>, where every slice is stored in a string respectively.
        */
        static std::vector<std::string> splitString(std::string str)
        {
            /**Create output vector and std::stringstream for string processing*/
            std::vector<std::string> result;
            std::stringstream sstr(str);

            /** While there is more data to read: read string until a comma occures or the end of the string is reached*/
            while(sstr.good())
            {
                std::string item;
                getline(sstr, item, ',');
                result.push_back(item);
            }
            return result;
        };

        /**
         * @brief Parses a string and returns std::vector<double> of the parsed data
         * 
         * @param line Line of data to be parsed
         * 
         * @return std::vector<double> of parsed data
        */
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
        
    public:
        /**
         * @brief Determines whether there are more lines to be read in a std::ifstream
         * 
         * Checks if end of file (eof) is reached. If not, it is assumed that there is more content to read
         * 
         * @param in Stream to be checked
         * 
         * @return True, if more lines exist. Otherwise false
        */
        static bool moreLinesToRead(std::ifstream &in)
        {
            return (!in.eof());
        };

        /**
        * @brief Reads the next line of a filestream
        *
        * This is the main method of this parser
        '
        * @return solver_test::testdata with the parsed line of data
        *
        * @throws std::runtime_error If filestream is not initialized, otherwise corrupt or if file format is invalid
        */
        static struct testdata readLine(std::ifstream &in)
        {
            /**
             * Test if filestream contains more lines to read and read lines,
             *  until a valid line of data is found
             */
            std::string line;
            do
            {            
                if(!moreLinesToRead(in))
                    throw std::runtime_error("No more lines to read");

                /** Read line*/
                getline(in, line);

            } while(!isValidLine(line));
            
            /** Parse line */
            std::vector<double> data = parseLine(line);
            
            /** Assert line as the appropriate amount of entries */
            if(data.size() != 5)
                throw std::runtime_error("Invalid file format. Aborting!");
            
            /** Assemble return solver_test::testdata struct */
            struct solver::vector2 ql = {data[0], data[2]};
            struct solver::vector2 qr = {data[1], data[3]};
            struct testdata result = {ql, qr, float(data[4])};

            return result;
        };
    };
};
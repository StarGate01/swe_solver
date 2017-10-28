/**
 * @file CSVParser.hpp
 * @brief Parser for csv files
 */
#include <fstream>
#include <vector>
#include <string>
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
        /**
        * @brief Reads the next line of the file
        * @return 
        * @throws std::runtime_error If filestream is not initialized
        */
        static std::string readLine(std::ifstream &in)
        {
            if(in.fail())
                throw std::runtime_error("Invalid ifstream in (maybe file does not exist?)");
            
            std::string line;
            getline(in, line);
            /*
            std::vector<std::string> data = parseLine("blasd");
            struct testdata test;
            return test;
            */
            return line;
        };

    private:

        static bool isValidLine(std::string line)
        {
            //TODO: Implement
            return true;
        }
        static std::vector<std::string> parseLine(std::string line)
        {
            std::vector<std::string> result;
            return result;
        }
    };
};
    // public:
    //     /**
    //      * @brief Constructor, that initializes the filestream for reading
    //      * @param filepath Path of th.csv file
    //      * @throws std::invalid_argument If path is invalid or file can not be opened
    //     */
    //     CSVParser::CSV_Parser(std::string filepath)
    //     {
    //         /** Create new filestream */
    //         std::ifstream file = new std::ifstream(filepath);

    //         /** Throw exception, if file cannot be opened*/
    //         if(!file.is_open())
    //            throw std::invalid_argument("File path invalid"); 
    //     };

    //     /**
    //      * @brief Reads the next line of the file
    //      * @return If the file contains at least one line to read, returns the next line as solver_tests::testdata object; else returns NULL
    //      * @throws std::runtime_error If filestream is not initialized
    //     */
    //     struct testdata read_line(void)
    //     {
    //         /** Check if filestream is open*/
    //         if(!file.is_open())
    //             throw std::runtime_error("Bad initialisation of filestream");

    //         /** Read one line or close, if end of file is reached */
    //         std::string buffer;
    //         if(!file.getline(buffer, file))
    //         {
    //             file.close();
    //             throw std::runtime_error("End of file");
    //         }
    //         return parse_line(buffer);
    //     };

    //     /**
    //      * @brief Parse string of text, consisting of three float numbers and seperated by commas, and returns them as solver_tests::testdata object
    //      * @param line Line of text to be parsed
    //      * @return Set of test data, if parsing was successful. Otherwise NULL
    //     */
    //     struct testdata parse_line(std::string line)
    //     {
    //         /** Initialize variables*/
    //         std::vector<std::string> arr(5);
    //         std::vector<float> parsedArr(5);
    //         std::stringstream strstream(line);

    //         /** Read in new lines, until the input has the expected format (Five substrings seperated by commas)*/
    //         bool failed = false;
    //         do{

    //             /** Split line by commas */
    //             if(strstream.good())
    //             {
    //                 std::string buf;
    //                 getline(strstream, buf, ',');
    //                 arr.pushback(buf);
    //                 /** Test if components can be parsed as floats and generate output */
    //                 try{
    //                     for(int i = 0; i < arr.size(); i++)
    //                         parsedArr[i] = std::atof(arr[i]);
    //                 }
    //                 catch(const std::exception& e)
    //                 {
    //                     /** Do not accept line as valid, when an element could not be parsed */
    //                     failed = true;
    //                 }
    //             }
    //             else
    //             {
    //                 throw std::runtime_error("End of file");
    //             }
    //         } while(arr.size() != 5 || failed);
            
    //         /** Convert numbers*/

    //         /** Assemble testdata */
    //         struct vector2 ql = {parsedArr[0], parsedArr[1]};
    //         struct vector2 qr = {parsedArr[2], parsedArr[3]};
    //         struct testdata parsedArr_struct = {ql, qr, parsedArr[4]};
    //         return parsedArr_struct;
    //     };

    // private:
    //     std::ifstream file;
    // };
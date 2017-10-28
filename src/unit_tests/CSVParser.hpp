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
            
            struct solver::vector2 ql = {data[0], data[1]};
            struct solver::vector2 qr = {data[2], data[3]};
            
            struct testdata result = {ql, qr, data[5]};
            return result;
        };
        
        static bool moreLinesToRead(std::ifstream &in)
        {
            return !(in && in.peek() == EOF);
        };
        
//    private:
        static bool isValidLine(std::string line)
        {
            //TODO: Count numbers of commas and test for characters other than numbers, ',' and '.'
            return (line.length() > 2 && line[0] != '#');
        };

        static std::vector<std::string>> splitString(std::string str, std::string delimiter)
        {
            std::vector<std::string> result;
            std::stringstream sstr(str);

            while(ss.good())
            {
                std::string item;
                getline(sstr, item, ',');
                result.push_back(item);
            }
            return result;
        };

        static std::vector<std::double> parseLine(std::string line)
        {
            std::cout << std::endl << "Parsing: " + line << std::endl;
            
            /** Split string by comma */
            std::vector<std::string> items = splitString(line);

            /** Convert line to doubles */
            std::vector<double> result;
            for(int i = 0; i < items.size(); i++)
            {
                result.push_back(std::atof(items[i]));
            }
            return result;
        };
    };
};
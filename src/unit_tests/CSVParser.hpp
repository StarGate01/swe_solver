/**
 * @file CSVParser.hpp
 * @brief Parser for csv files
 */

#include <string>
#include <vector>
#include <fstream>
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

        static vector<testData> parse_file(string path)
        {
            //TODO: Init vector
            vector<testData> data;
        
            std::ifstream file;
            //Todo: Catch exception
        
            file.open(path);
            if(file.is_open())
            {
                string line;
                while(getline(file, line))
                {
                    parseLine(line);
                    data.push_back(parse_line(line));
                }
                file.close();

                return data;
            }
            raise invalid_argument;
        };

    private:

        static testData parse_line(string line)
        {
            
            /** Split line by commas */
            
            /** Test if components are numeric */
        
            /** Assemble */
            testData data;
            return data;
        };

    };

};
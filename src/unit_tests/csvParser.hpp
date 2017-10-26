/**
 * @brief Parser for csv files
*/

#include <string>
#include <vector>
#include <fstream>
#include "../solver/FStructs.hpp"

namespace solver_tests
{
    class csvParser;
}

struct testData
{
    struct qvector ql;
    struct qvector qr;
    double hstar;
};

class csvParser
{
public:
    static vector<testData> parseFile(string path)
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
                data.push_back(parseLine(line));
            }
            file.close();

            return data;
        }
            raise invalid_argument;
    };

private:
    static testData parseLine(string line)
    {
        
        /** Split line by commas */
        
        /** Test if components are numeric */
    
        /** Assemble */
        testData data;
        return data;
    };
}
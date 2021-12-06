#include <sstream>
#include <algorithm>

#include "stringutils/stringutils.hpp"

bool StringUtils::isNumber(const std::string& str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

std::vector<std::string> StringUtils::Split(std::string str, char separator)
{
    std::string temp;
    std::stringstream ss(str);
    std::vector<std::string> splitList;
    while(std::getline(ss, temp, separator))
    {
        splitList.push_back(temp);
    }

    return splitList;
}
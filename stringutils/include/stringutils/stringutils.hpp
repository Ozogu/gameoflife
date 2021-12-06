#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
    bool isNumber(const std::string& str);
    std::vector<std::string> Split(std::string str, char separator);
}

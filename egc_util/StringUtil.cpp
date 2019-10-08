//
// Created by Brendan Berg on 2019-10-08.
//

#include <egc_util/StringUtil.hpp>


std::vector<std::string> egc::StringUtil::Split (const std::string& string, char delimiter)
{
    std::vector<std::string> parsed;

    std::size_t previous = 0, current = string.find(delimiter);
    while (current != std::string::npos)
    {
        parsed.push_back(string.substr(previous, current - previous));
        previous = current + 1;
        current = string.find(delimiter, previous);
    }
    parsed.push_back(string.substr(previous, current - previous));

    return parsed;
}

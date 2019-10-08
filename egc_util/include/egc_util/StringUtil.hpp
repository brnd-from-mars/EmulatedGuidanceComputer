//
// Created by Brendan Berg on 2019-10-08.
//

#ifndef EMULATEDGUIDANCECOMPUTER_STRINGUTIL_HPP
#define EMULATEDGUIDANCECOMPUTER_STRINGUTIL_HPP

#include <string>
#include <vector>


namespace egc
{

    class StringUtil
    {
    public:

        static std::vector<std::string> Split (const std::string& string, char delimiter);


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_STRINGUTIL_HPP

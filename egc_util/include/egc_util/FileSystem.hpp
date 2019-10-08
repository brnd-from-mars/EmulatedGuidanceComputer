//
// Created by Brendan Berg on 2019-10-08.
//

#ifndef EMULATEDGUIDANCECOMPUTER_FILESYSTEM_HPP
#define EMULATEDGUIDANCECOMPUTER_FILESYSTEM_HPP

#include <string>


namespace egc
{

    class FileSystem
    {
    public:

        static bool CheckDirectory (const std::string& directoryPath);

        static bool CheckDirectoryPath (const std::string& directoryPath);


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_FILESYSTEM_HPP

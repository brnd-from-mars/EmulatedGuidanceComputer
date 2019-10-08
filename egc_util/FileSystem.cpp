//
// Created by Brendan Berg on 2019-10-08.
//

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <egc_util/FileSystem.hpp>


bool egc::FileSystem::CheckDirectory (const std::string& directoryPath)
{
    struct stat directoryStat {};
    auto error = stat(directoryPath.c_str(), &directoryStat);

    if (error)
    {
        mode_t mode = 0755;
        mkdir(directoryPath.c_str(), mode);

        return false;
    }

    return true;
}


bool egc::FileSystem::CheckDirectoryPath (const std::string& directoryPath)
{
    std::string reconstructedPath;
    bool last = true;

    std::size_t previous = 0, current = directoryPath.find('/');
    while (current != std::string::npos)
    {
        reconstructedPath += directoryPath.substr(previous, current - previous) + "/";
        last = CheckDirectory(reconstructedPath);

        previous = current + 1;
        current = directoryPath.find('/', previous);
    }

    return last;
}
//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_emulator/Emulator.hpp>


int main (int argc, char* argv[])
{
    egc::Emulator emulator;

    if (argc > 1)
    {
        auto filePath = std::string(argv[1]);
        emulator.OpenCommandFile(filePath);
    }

    while (emulator.Update());

    return 0;
}

//
// Created by Brendan Berg on 2019-10-08.
//

#ifndef EMULATEDGUIDANCECOMPUTER_EMULATOR_HPP
#define EMULATEDGUIDANCECOMPUTER_EMULATOR_HPP

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <egc_memory/Memory.hpp>
#include <egc_sequencer/Sequencer.hpp>


namespace egc
{

    class Emulator
    {
    public:

        Emulator ();

        ~Emulator ();

        void OpenCommandFile (const std::string& filePath);

        bool ExecuteCommand (const std::string& commandString);

        bool Update ();

    private:

        void Emulation (const std::vector<std::string>& command);

        void Mem (const std::vector<std::string>& command);

        std::shared_ptr<egc::Memory> m_Memory;

        std::shared_ptr<egc::Sequencer> m_Sequencer;

        std::ifstream m_CommandFile;

        bool m_CommandFileMode;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_EMULATOR_HPP

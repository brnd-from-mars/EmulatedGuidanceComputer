//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_MEMORY_HPP
#define EMULATEDGUIDANCECOMPUTER_MEMORY_HPP

#include <string>

#include "ErasableMemory.hpp"
#include "FixedMemory.hpp"


namespace egc
{

    class Memory
    {
    public:

        // TODO: Add io channel member when implemented
        explicit Memory (const std::string& directoryPath, bool create = false);

        void Write (unsigned short address, unsigned short word);

        // TODO: replace parameter with FEB look-up
        unsigned short Read (unsigned short address, unsigned short feb = 0);

        void SaveToFile ();

        void LoadFromFile ();


    private:

        egc::ErasableMemory m_ErasableMemory;

        egc::FixedMemory m_FixedMemory;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_MEMORY_HPP

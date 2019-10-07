//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_FIXEDMEMORY_HPP
#define EMULATEDGUIDANCECOMPUTER_FIXEDMEMORY_HPP

#include <memory>
#include <vector>

#include "ErasableMemory.hpp"

#include "FixedMemoryBank.hpp"


namespace egc
{

    class FixedMemory
    {
    public:

        // TODO: Add io channel member when implemented
        explicit FixedMemory (ErasableMemory& erasableMemory);

        unsigned short Read (unsigned short cpuAddress, unsigned short feb);


    private:

        unsigned short CPUAddressToBank (unsigned short cpuAddress, unsigned short feb);

        unsigned short CPUAddressToPhysicalAddress (unsigned short bank, unsigned short cpuAddress);

        egc::ErasableMemory& m_ErasableMemory;

        std::vector<std::unique_ptr<egc::FixedMemoryBank>> m_Banks;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_FIXEDMEMORY_HPP

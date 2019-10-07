//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORY_HPP
#define EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORY_HPP

#include <memory>
#include <vector>

#include "ErasableMemoryBank.hpp"
#include "ErasableMemoryBankZero.hpp"


namespace egc
{

    class ErasableMemory
    {
    public:

        ErasableMemory ();

        void Write (unsigned short cpuAddress, unsigned short word);

        unsigned short Read (unsigned short cpuAddress);

        unsigned short GetSwitchedErasableBank ();

        unsigned short GetSwitchedFixedBank (unsigned short feb);


    private:

        unsigned short CPUAddressToBank (unsigned short cpuAddress);

        unsigned short CPUAddressToPhysicalAddress (unsigned short bank, unsigned short cpuAddress);

        std::vector<std::unique_ptr<egc::ErasableMemoryBank>> m_Banks;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORY_HPP

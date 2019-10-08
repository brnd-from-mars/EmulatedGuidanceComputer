//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_FIXEDMEMORYBANK_HPP
#define EMULATEDGUIDANCECOMPUTER_FIXEDMEMORYBANK_HPP

#include "MemoryBank.hpp"


namespace egc
{

    class FixedMemoryBank : public MemoryBank
    {
    public:

        explicit FixedMemoryBank (unsigned short bankNumber, const std::string& directoryPath, bool create = false);

        unsigned short Read (unsigned short physicalAddress);


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_FIXEDMEMORYBANK_HPP

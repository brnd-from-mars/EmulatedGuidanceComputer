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

        explicit FixedMemoryBank (unsigned short bankNumber);

        unsigned short Read (unsigned short physicalAddress);


    private:

        unsigned short m_BankNumber;
    };

}


#endif //EMULATEDGUIDANCECOMPUTER_FIXEDMEMORYBANK_HPP

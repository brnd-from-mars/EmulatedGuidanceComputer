//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORYBANK_HPP
#define EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORYBANK_HPP

#include "MemoryBank.hpp"


namespace egc
{

    class ErasableMemoryBank : public MemoryBank
    {
    public:

        explicit ErasableMemoryBank (unsigned short bankNumber, const std::string& directoryPath, bool create = false);

        virtual void Write (unsigned short physicalAddress, unsigned short word);

        virtual unsigned short Read (unsigned short physicalAddress);


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORYBANK_HPP

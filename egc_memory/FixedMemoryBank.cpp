//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/FixedMemoryBank.hpp>


egc::FixedMemoryBank::FixedMemoryBank (unsigned short bankNumber, const std::string& directoryPath, bool create)
    : MemoryBank(bankNumber, 010000u + 02000u * bankNumber, 02000u, directoryPath, create)
{ }


unsigned short egc::FixedMemoryBank::Read (unsigned short physicalAddress)
{
    return GetWord(physicalAddress) & 077777u;
}

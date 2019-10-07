//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/ErasableMemoryBank.hpp>


egc::ErasableMemoryBank::ErasableMemoryBank (unsigned short bankNumber)
    : MemoryBank(0400 * bankNumber, 0400), m_BankNumber(bankNumber)
{ }


void egc::ErasableMemoryBank::Write (unsigned short physicalAddress, unsigned short word)
{
    SetWord(physicalAddress, word);
}


unsigned short egc::ErasableMemoryBank::Read (unsigned short physicalAddress)
{
    return GetWord(physicalAddress) & 077777u;
}

//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/FixedMemoryBank.hpp>


egc::FixedMemoryBank::FixedMemoryBank (unsigned short bankNumber)
    : MemoryBank(010000u + 02000u * bankNumber, 02000u), m_BankNumber(bankNumber)
{ }


unsigned short egc::FixedMemoryBank::Read (unsigned short physicalAddress)
{
    return GetWord(physicalAddress) & 077777u;
}

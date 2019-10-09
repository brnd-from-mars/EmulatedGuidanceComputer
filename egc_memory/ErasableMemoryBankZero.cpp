//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/ErasableMemoryBankZero.hpp>


egc::ErasableMemoryBankZero::ErasableMemoryBankZero (const std::string& directoryPath, bool create)
    : ErasableMemoryBank(0, directoryPath, create)
{
    if (create)
    {
        Write(00005u, 004000u);
        SaveToFile();
    }
}


void egc::ErasableMemoryBankZero::Write (unsigned short physicalAddress, unsigned short word)
{
    // TODO: Extend list of special cases
    switch (physicalAddress)
    {
        case 00003u:
            ErasableMemoryBank::Write(physicalAddress, word & 003400u);
            UpdateBBankRegister();
            break;
        case 00004u:
            ErasableMemoryBank::Write(physicalAddress, word & 076000u);
            UpdateBBankRegister();
            break;
        case 00006u:
            ErasableMemoryBank::Write(physicalAddress, word & 076007u);
            UpdateEBankRegister();
            UpdateFBankRegister();
            break;
        case 00007u:
            break;
        case 00020u:
            word = ((word & 077776u) >> 1u) | ((word & 000001u) << 14u);
            ErasableMemoryBank::Write(physicalAddress, word);
            break;
        case 00021u:
            word = ((word & 077776u) >> 1u) | (word & 040000u);
            ErasableMemoryBank::Write(physicalAddress, word);
            break;
        case 00022u:
            word = ((word & 037777u) << 1u) | ((word & 040000u) >> 14u);
            ErasableMemoryBank::Write(physicalAddress, word);
            break;
        case 00023u:
            word = (word & 037600u) >> 7u;
            ErasableMemoryBank::Write(physicalAddress, word);
            break;
        default:
            ErasableMemoryBank::Write(physicalAddress, word);
            break;
    }
}


void egc::ErasableMemoryBankZero::UpdateEBankRegister ()
{
    auto bbank = ErasableMemoryBank::Read(00006u);
    ErasableMemoryBank::Write(00003u, (bbank & 000007u) << 8u);
}


void egc::ErasableMemoryBankZero::UpdateFBankRegister ()
{
    auto bbank = ErasableMemoryBank::Read(00006u);
    ErasableMemoryBank::Write(00004u, bbank & 076000u);
}


void egc::ErasableMemoryBankZero::UpdateBBankRegister ()
{
    auto ebank = ErasableMemoryBank::Read(00003u) >> 8u;
    auto fbank = ErasableMemoryBank::Read(00004u);
    ErasableMemoryBank::Write(00006u, (ebank | fbank) & 076007u);
}

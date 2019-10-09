//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_util/FileSystem.hpp>

#include <egc_memory/ErasableMemory.hpp>


egc::ErasableMemory::ErasableMemory (const std::string& directoryPath, bool create)
    : m_AccumulatorOverflow(000000u), m_ExtendFlag(000000u)
{
    m_Banks.reserve(010);
    auto path = directoryPath + std::string("erasable/");
    FileSystem::CheckDirectoryPath(path);

    m_Banks.push_back(std::make_unique<ErasableMemoryBankZero>(path, create));
    for (unsigned short bank = 001; bank < 010; ++bank)
    {
        m_Banks.push_back(std::make_unique<ErasableMemoryBank>(bank, path, create));
    }
}


void egc::ErasableMemory::Write (unsigned short cpuAddress, unsigned short word)
{
    auto bank = CPUAddressToBank(cpuAddress);
    auto physicalAddress = CPUAddressToPhysicalAddress(bank, cpuAddress);
    m_Banks[bank]->Write(physicalAddress, word);

    if (physicalAddress == 0000000u)
    {
        m_AccumulatorOverflow = 000000u;
    }
}


unsigned short egc::ErasableMemory::Read (unsigned short cpuAddress)
{
    auto bank = CPUAddressToBank(cpuAddress);
    auto physicalAddress = CPUAddressToPhysicalAddress(bank, cpuAddress);
    return m_Banks[bank]->Read(physicalAddress);
}


void egc::ErasableMemory::SetAccumulatorOverflow (unsigned short overflow)
{
    m_AccumulatorOverflow = overflow;
}


unsigned short egc::ErasableMemory::GetAccumulatorOverflow ()
{
    return m_AccumulatorOverflow;
}


void egc::ErasableMemory::SetExtendFlag ()
{
    m_ExtendFlag = 000001u;
}


void egc::ErasableMemory::ResetExtendFlag ()
{
    m_ExtendFlag = 000000u;
}


unsigned short egc::ErasableMemory::GetExtendFlag ()
{
    return m_ExtendFlag;
}


unsigned short egc::ErasableMemory::GetSwitchedErasableBank ()
{
    return m_Banks[000u]->Read(00003u) >> 8u & 000007u;
}


unsigned short egc::ErasableMemory::GetSwitchedFixedBank (unsigned short feb)
{
    unsigned short bank =  m_Banks[000u]->Read(00004u) >> 10u & 000037u;
    if (feb == 1u && 030u <= bank && bank < 040u)
    {
        bank += 010u;
    }
    return bank;
}


void egc::ErasableMemory::SaveToFile ()
{
    for (auto& bank : m_Banks)
    {
        bank->SaveToFile();
    }
}


void egc::ErasableMemory::LoadFromFile ()
{
    for (auto& bank : m_Banks)
    {
        bank->LoadFromFile();
    }
}


unsigned short egc::ErasableMemory::CPUAddressToBank (unsigned short cpuAddress)
{
    if (cpuAddress < 00400u)
    {
        return 000u;
    }
    else if (cpuAddress < 01000u)
    {
        return 001u;
    }
    else if (cpuAddress < 01400u)
    {
        return 002u;
    }
    else
    {
        return GetSwitchedErasableBank();
    }

    // TODO: Add error log
    // address out of bounds
}


unsigned short egc::ErasableMemory::CPUAddressToPhysicalAddress (unsigned short bank, unsigned short cpuAddress)
{
    if (cpuAddress < 01400)
    {
        return cpuAddress;
    }
    else
    {
        return cpuAddress + bank * 0400 - 01400;
    }
}

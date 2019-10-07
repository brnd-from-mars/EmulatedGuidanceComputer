//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/FixedMemory.hpp>


egc::FixedMemory::FixedMemory (egc::ErasableMemory& erasableMemory)
    : m_ErasableMemory(erasableMemory)
{
    m_Banks.reserve(044);

    for (unsigned short bank = 000; bank < 044; ++bank)
    {
        m_Banks.push_back(std::make_unique<FixedMemoryBank>(bank));
    }
}


unsigned short egc::FixedMemory::Read (unsigned short cpuAddress, unsigned short feb)
{
    auto bank = CPUAddressToBank(cpuAddress, feb);
    auto physicalAddress = CPUAddressToPhysicalAddress(bank, cpuAddress);
    return m_Banks[bank]->Read(physicalAddress);
}


unsigned short egc::FixedMemory::CPUAddressToBank (unsigned short cpuAddress, unsigned short feb)
{
    if (cpuAddress >= 06000u)
    {
        return 003u;
    }
    else if (cpuAddress >= 04000u)
    {
        return 002u;
    }
    else
    {
        return m_ErasableMemory.GetSwitchedFixedBank(feb);
    }

    // TODO: Add error log
    // address out of bounds
}


unsigned short egc::FixedMemory::CPUAddressToPhysicalAddress (unsigned short bank, unsigned short cpuAddress)
{
    if (cpuAddress >= 04000u)
    {
        return cpuAddress + 010000u;
    }
    else
    {
        return cpuAddress + bank * 02000u + 006000u;
    }

    // TODO: Add error log
    // address out of bounds
}

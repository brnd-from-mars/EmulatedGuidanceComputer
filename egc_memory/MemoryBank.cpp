//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/MemoryBank.hpp>


egc::MemoryBank::MemoryBank (unsigned short physicalLowAddress, unsigned short size)
    : m_PhysicalLowAddress(physicalLowAddress), m_Size(size)
{
    m_Data.resize(m_Size, 0);
}


void egc::MemoryBank::SetWord (unsigned short physicalAddress, unsigned short word)
{
    auto localAddress = PhysicalToLocalAddress(physicalAddress);

    if (localAddress.has_value())
    {
        m_Data[localAddress.value()] = word;
    }
    else
    {
        // TODO: Add error log
        // address out of bounds
    }
}


unsigned short egc::MemoryBank::GetWord (unsigned short physicalAddress)
{
    auto localAddress = PhysicalToLocalAddress(physicalAddress);

    if (localAddress.has_value())
    {
        return m_Data[localAddress.value()];
    }
    else
    {
        // TODO: Add error log
        // address out of bounds
        return 000000;
    }
}


std::optional<unsigned short> egc::MemoryBank::PhysicalToLocalAddress (unsigned short physicalAddress)
{
    auto localAddress = physicalAddress - m_PhysicalLowAddress;

    // if address is out of bounds
    if (m_PhysicalLowAddress > physicalAddress || m_Size < localAddress) {
        return std::nullopt;
    }

    return localAddress;
}

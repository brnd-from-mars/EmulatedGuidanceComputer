//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/Memory.hpp>


egc::Memory::Memory ()
    : m_FixedMemory(m_ErasableMemory)
{ }


void egc::Memory::Write (unsigned short address, unsigned short word)
{
    if (address < 02000)
    {
        m_ErasableMemory.Write(address, word);
    }

    // TODO: Add error log
    // address out of bounds
}


unsigned short egc::Memory::Read (unsigned short address, unsigned short feb)
{
    if (address < 02000)
    {
        return m_ErasableMemory.Read(address);
    }
    else
    {
        return m_FixedMemory.Read(address, feb);
    }

    // TODO: Add error log
    // address out of bounds
}

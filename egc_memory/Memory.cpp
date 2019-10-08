//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/Memory.hpp>


egc::Memory::Memory (const std::string& directoryPath, bool create)
    : m_ErasableMemory(directoryPath, create), m_FixedMemory(m_ErasableMemory, directoryPath, create)
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


void egc::Memory::SaveToFile ()
{
    m_ErasableMemory.SaveToFile();
    m_FixedMemory.SaveToFile();
}


void egc::Memory::LoadFromFile ()
{
    m_ErasableMemory.LoadFromFile();
    m_FixedMemory.LoadFromFile();
}

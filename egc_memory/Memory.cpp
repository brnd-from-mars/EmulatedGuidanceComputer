//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_memory/Memory.hpp>


egc::Memory::Memory (const std::string& directoryPath, bool create)
    : m_ErasableMemory(directoryPath, create), m_FixedMemory(m_ErasableMemory, directoryPath, create)
{ }


void egc::Memory::Write (unsigned short address, unsigned short word)
{
    if (address < 02000u)
    {
        m_ErasableMemory.Write(address, word);
    }

    // TODO: Add error log
    // address out of bounds
}


unsigned short egc::Memory::Read (unsigned short address, unsigned short feb)
{
    if (address < 02000u)
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


void egc::Memory::SetAccumulatorOverflow (unsigned short overflow)
{
    m_ErasableMemory.SetAccumulatorOverflow(overflow);
}


unsigned short egc::Memory::GetAccumulatorOverflow ()
{
    return m_ErasableMemory.GetAccumulatorOverflow();
}


void egc::Memory::SetExtendFlag ()
{
    m_ErasableMemory.SetExtendFlag();
}


void egc::Memory::ResetExtendFlag ()
{
    m_ErasableMemory.ResetExtendFlag();
}


unsigned short egc::Memory::GetExtendFlag ()
{
    return m_ErasableMemory.GetExtendFlag();
}


void egc::Memory::SetIndex (unsigned short index)
{
    m_ErasableMemory.SetIndex(index);
}


unsigned short egc::Memory::ResetIndex ()
{
    return m_ErasableMemory.ResetIndex();
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

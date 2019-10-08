//
// Created by Brendan Berg on 2019-10-07.
//

#include <fstream>

#include <egc_memory/MemoryBank.hpp>


egc::MemoryBank::MemoryBank (unsigned short bankNumber, unsigned short physicalLowAddress, unsigned short size,
                             const std::string& directoryPath, bool create)
    : m_BankNumber(bankNumber), m_PhysicalLowAddress(physicalLowAddress), m_Size(size)
{
    m_Data.resize(m_Size, 0);

    m_FilePath = directoryPath + std::string("bank") + std::to_string(m_BankNumber) + std::string(".dat");

    if (create)
    {
        SaveToFile();
    }
    else
    {
        LoadFromFile();
    }
}


void egc::MemoryBank::SaveToFile ()
{
    std::ofstream file(m_FilePath, std::fstream::binary);

    auto data = reinterpret_cast<char *>(m_Data.data());
    file.seekp(0);
    file.write(data, sizeof(unsigned short) * m_Size);

    file.close();
}


void egc::MemoryBank::LoadFromFile ()
{
    std::fstream file(m_FilePath, std::fstream::binary | std::fstream::in);

    unsigned short size = 0u;

    {
        auto begin = file.tellg();
        file.seekg(0, std::ios::end);
        size = std::min(static_cast<unsigned short>(file.tellg() - begin),
                        static_cast<unsigned short>(sizeof(unsigned short) * m_Size));
    }

    auto data = reinterpret_cast<char *>(m_Data.data());
    file.seekg(0);
    file.read(data, size);

    file.close();
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


std::string egc::MemoryBank::GenerateFilePath (const std::string& directoryPath)
{
    return directoryPath + std::string("bank") + std::to_string(m_BankNumber) + std::string(".dat");
}

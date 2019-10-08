//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_MEMORYBANK_HPP
#define EMULATEDGUIDANCECOMPUTER_MEMORYBANK_HPP

#include <vector>
#include <optional>
#include <string>


namespace egc
{

    class MemoryBank
    {
    public:

        MemoryBank (unsigned short bankNumber, unsigned short physicalLowAddress, unsigned short size,
                    const std::string& directoryPath, bool create = false);

        void SaveToFile ();

        void LoadFromFile ();


    protected:

        void SetWord (unsigned short physicalAddress, unsigned short word);

        unsigned short GetWord (unsigned short physicalAddress);

        unsigned short m_BankNumber;


    private:

        std::optional<unsigned short> PhysicalToLocalAddress (unsigned short physicalAddress);

        std::string GenerateFilePath(const std::string& directoryPath);

        unsigned short m_PhysicalLowAddress;

        unsigned short m_Size;

        std::vector<unsigned short> m_Data;

        std::string m_FilePath;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_MEMORYBANK_HPP

//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_MEMORYBANK_HPP
#define EMULATEDGUIDANCECOMPUTER_MEMORYBANK_HPP

#include <vector>
#include <optional>


namespace egc
{

    class MemoryBank
    {
    public:

        MemoryBank (unsigned short physicalLowAddress, unsigned short size);


    protected:

        void SetWord (unsigned short physicalAddress, unsigned short word);

        unsigned short GetWord (unsigned short physicalAddress);


    private:

        std::optional<unsigned short> PhysicalToLocalAddress (unsigned short physicalAddress);

        unsigned short m_PhysicalLowAddress;

        unsigned short m_Size;

        std::vector<unsigned short> m_Data;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_MEMORYBANK_HPP

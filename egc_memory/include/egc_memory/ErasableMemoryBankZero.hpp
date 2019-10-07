//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORYBANKZERO_HPP
#define EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORYBANKZERO_HPP

#include "ErasableMemoryBank.hpp"


namespace egc
{

    class ErasableMemoryBankZero : public ErasableMemoryBank
    {
    public:

        ErasableMemoryBankZero ();

        void Write (unsigned short physicalAddress, unsigned short word) override;


    private:

        void UpdateEBankRegister ();

        void UpdateFBankRegister ();

        void UpdateBBankRegister ();


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_ERASABLEMEMORYBANKZERO_HPP

//
// Created by Brendan Berg on 2019-10-07.
//

#ifndef EMULATEDGUIDANCECOMPUTER_SEQUENCER_HPP
#define EMULATEDGUIDANCECOMPUTER_SEQUENCER_HPP

#include <memory>

#include <egc_memory/Memory.hpp>


namespace egc
{

    class Sequencer
    {
    public:

        explicit Sequencer (std::shared_ptr<Memory> memory);

        void Step ();


    private:

        void StepUnextended (unsigned short instruction);

        void StepExtended (unsigned short instruction);

        static std::pair<unsigned short, unsigned short> AddWords (unsigned short a, unsigned short b);

        void AD (unsigned short instruction);

        void ADS (unsigned short instruction);

        void AUG (unsigned short instruction);

        void BZF (unsigned short instruction);

        void BZMF (unsigned short instruction);

        void CA (unsigned short instruction);

        void CCS (unsigned short instruction);

        void CS (unsigned short instruction);

        void DAS (unsigned short instruction);

        void DCA (unsigned short instruction);

        void DCS (unsigned short instruction);

        void DIM (unsigned short instruction);

        void DV (unsigned short instruction);

        void DXCH (unsigned short instruction);

        void EXTEND (unsigned short instruction);

        void INCR (unsigned short instruction);

        void INDEX (unsigned short instruction);

        void INDEXE (unsigned short instruction);

        void INHINT (unsigned short instruction);

        void LXCH (unsigned short instruction);

        void MASK (unsigned short instruction);

        void MP (unsigned short instruction);

        void MSU (unsigned short instruction);

        void QXCH (unsigned short instruction);

        void RELINT (unsigned short instruction);

        void SU (unsigned short instruction);

        void TC (unsigned short instruction);

        void TCF (unsigned short instruction);

        void TS (unsigned short instruction);

        void XCH (unsigned short instruction);

        std::shared_ptr<egc::Memory> m_Memory;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_SEQUENCER_HPP

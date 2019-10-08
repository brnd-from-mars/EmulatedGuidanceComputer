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

        std::shared_ptr<egc::Memory> m_Memory;


    };

}


#endif //EMULATEDGUIDANCECOMPUTER_SEQUENCER_HPP

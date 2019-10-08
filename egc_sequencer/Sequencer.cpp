//
// Created by Brendan Berg on 2019-10-07.
//

#include <egc_sequencer/Sequencer.hpp>


egc::Sequencer::Sequencer (std::shared_ptr<egc::Memory> memory)
    : m_Memory(std::move(memory))
{ }


void egc::Sequencer::Step ()
{
    auto z = m_Memory->Read(00005u) & 007777u;
    auto instruction = m_Memory->Read(z) & 077777u;
    m_Memory->Write(00005u, z + 000001u);

    // execute instruction
}

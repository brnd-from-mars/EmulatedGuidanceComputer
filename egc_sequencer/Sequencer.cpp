//
// Created by Brendan Berg on 2019-10-07.
//


#include <egc_sequencer/Sequencer.hpp>


egc::Sequencer::Sequencer (std::shared_ptr<egc::Memory> memory)
    : m_Memory(std::move(memory))
{ }


void egc::Sequencer::Step ()
{
    unsigned short z = m_Memory->Read(00005u) & 007777u;
    unsigned short instruction = m_Memory->Read(z) & 077777u;
    m_Memory->Write(00005u, z + 000001u);

    unsigned short opcode = instruction & 070000u;
    unsigned short quartercode = instruction & 006000u;

    switch (opcode)
    {
        case 020000u:
            switch (quartercode)
            {
                case 006000u:
                    ADS(instruction);
                    break;
                default:
                    break;
            }
        case 050000u:
            switch (quartercode)
            {
                case 004000u:
                    TS(instruction);
                    break;
                default:
                    break;
            }
            break;
        case 060000u:
            AD(instruction);
            break;
        default:
            break;
    }
}


std::pair<unsigned short, unsigned short> egc::Sequencer::AddWords (unsigned short a, unsigned short b)
{
    unsigned short signA = a & 040000u;
    unsigned short signB = b & 040000u;

    unsigned short result = a + b;
    unsigned short overflow = 000000;
    unsigned short carry = (result & 0100000u) >> 15;
    result &= 077777u;
    result += carry;

    unsigned short signResult = (result & 040000u);
    if (signA == signB && signA != signResult)
    {
        if (signA == 040000u)
        {
            overflow = 077776u;
        }
        else
        {
            overflow = 000001u;
        }
    }

    result &= 077777u;

    return std::make_pair(result, overflow);
}


void egc::Sequencer::AD (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(00000u);

    auto [result, overflow] = AddWords(a, mk);

    m_Memory->Write(k, mk);
    m_Memory->Write(00000u, result);

    m_Memory->SetAccumulatorOverflow(overflow);
}


void egc::Sequencer::ADS (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(00000u);

    auto [result, overflow] = AddWords(a, mk);

    m_Memory->Write(k, result);
    m_Memory->Write(00000u, result);

    m_Memory->SetAccumulatorOverflow(overflow);
}


void egc::Sequencer::TS (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    auto a = m_Memory->Read(00000u);

    // TODO: Proper overflow handling

    m_Memory->Write(k, a);
    m_Memory->Write(00000u, a);
}

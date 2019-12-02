//
// Created by Brendan Berg on 2019-10-07.
//


#include <egc_sequencer/Sequencer.hpp>

#include <iostream>


egc::Sequencer::Sequencer (std::shared_ptr<egc::Memory> memory)
    : m_Memory(std::move(memory))
{ }


void egc::Sequencer::Step ()
{
    unsigned short z = m_Memory->Read(00005u) & 007777u;
    unsigned short instruction = (m_Memory->Read(z) + m_Memory->ResetIndex()) & 077777u;
    m_Memory->Write(00005u, z + 000001u);

    unsigned short isExtended = m_Memory->GetExtendFlag();
    m_Memory->ResetExtendFlag();

    if (isExtended)
    {
        StepExtended(instruction);
    }
    else
    {
        StepUnextended(instruction);
    }
}


void egc::Sequencer::StepUnextended (unsigned short instruction)
{
    unsigned short opcode = instruction & 070000u;
    unsigned short quartercode = instruction & 006000u;

    switch (opcode)
    {
        case 000000u:
            if (instruction == 000003u)
            {
                RELINT(instruction);
            }
            else if (instruction == 000004u)
            {
                INHINT(instruction);
            }
            else if (instruction == 000006u)
            {
                EXTEND(instruction);
            }
            else
            {
                TC(instruction);
            }
            break;
        case 010000u:
            if (quartercode == 000000u)
            {
                CCS(instruction);
            }
            else
            {
                TCF(instruction);
            }
            break;
        case 020000u:
            switch (quartercode)
            {
                case 000000u:
                    DAS(instruction);
                    break;
                case 002000u:
                    LXCH(instruction);
                    break;
                case 004000u:
                    INCR(instruction);
                    break;
                case 006000u:
                    ADS(instruction);
                    break;
                default:
                    break;
            }
            break;
        case 030000u:
            CA(instruction);
            break;
        case 040000u:
            CS(instruction);
            break;
        case 050000u:
            switch (quartercode)
            {
                case 000000u:
                    INDEX(instruction);
                    break;
                case 002000u:
                    DXCH(instruction);
                    break;
                case 004000u:
                    TS(instruction);
                    break;
                case 006000u:
                    XCH(instruction);
                    break;
                default:
                    break;
            }
            break;
        case 060000u:
            AD(instruction);
            break;
        case 070000u:
            MASK(instruction);
            break;
        default:
            break;
    }
}


void egc::Sequencer::StepExtended (unsigned short instruction)
{
    unsigned short opcode = instruction & 070000u;
    unsigned short quartercode = instruction & 006000u;

    switch (opcode)
    {
        case 010000u:
            if (quartercode == 000000u)
            {
                DV(instruction);
            }
            else
            {
                BZF(instruction);
            }
            break;
        case 020000u:
            switch (quartercode)
            {
                case 000000u:
                    MSU(instruction);
                    break;
                case 002000u:
                    QXCH(instruction);
                    break;
                case 004000u:
                    AUG(instruction);
                    break;
                case 006000u:
                    DIM(instruction);
                    break;
                default:
                    break;
            }
            break;
        case 030000u:
            DCA(instruction);
            break;
        case 040000u:
            DCS(instruction);
            break;
        case 050000u:
            INDEXE(instruction);
            break;
        case 060000u:
            if (quartercode == 000000u)
            {
                SU(instruction);
            }
            else
            {
                BZMF(instruction);
            }
            break;
        case 070000u:
            MP(instruction);
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
        result &= 037777u;
        result |= signA;

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

    if (result == 000000u)
    {
        result = 077777u;
    }

    return std::make_pair(result, overflow);
}


void egc::Sequencer::AD (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "AD" << " " << std::oct << k << std::dec << std::endl;

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

    std::cout << "ADS" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(00000u);

    auto [result, overflow] = AddWords(a, mk);

    m_Memory->Write(k, result);
    m_Memory->Write(00000u, result);

    m_Memory->SetAccumulatorOverflow(overflow);
}


void egc::Sequencer::AUG (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "AUG" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);

    unsigned short sign = mk & 040000u;

    if (sign == 040000u)
    {
        mk = AddWords(mk, 077776u).first;
    }
    else
    {
        mk = AddWords(mk, 000001u).first;
    }

    m_Memory->Write(k, mk);
}


void egc::Sequencer::BZF (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "BZF" << " " << std::oct << k << std::dec << std::endl;

    auto a = m_Memory->Read(000000u);

    if (a == 000000u || a == 077777u)
    {
        m_Memory->Write(00005u, k);
    }

    m_Memory->Write(00000u, a);
}


void egc::Sequencer::BZMF (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "BZMF" << " " << std::oct << k << std::dec << std::endl;

    auto a = m_Memory->Read(000000u);

    if (a == 000000u || a & 040000u)
    {
        m_Memory->Write(00005u, k);
    }

    m_Memory->Write(00000u, a);
}


void egc::Sequencer::CA (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "CA" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);

    m_Memory->Write(k, mk);
    m_Memory->Write(00000u, mk);
}


void egc::Sequencer::CCS (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "CCS" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);

    auto dim = mk;
    if (dim & 040000u)
    {
        dim = ~dim & 077777u;
    }
    if (dim != 000000u)
    {
        dim -=000001u;
    }

    m_Memory->Write(000000u, dim);
    m_Memory->Write(k, mk);

    if (mk & 040000u)
    {
        if (mk == 077777u)
        {
            m_Memory->Write(000005u, m_Memory->Read(000005u) + 3);
        }
        else
        {
            m_Memory->Write(000005u, m_Memory->Read(000005u) + 2);
        }
    }
    else
    {
        if (mk == 000000u)
        {
            m_Memory->Write(000005u, m_Memory->Read(000005u) + 1);
        }
    }
}


void egc::Sequencer::CS (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "CS" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);

    m_Memory->Write(k, mk);
    m_Memory->Write(00000u, ~mk & 077777u);
}


void egc::Sequencer::DAS (unsigned short instruction)
{
    unsigned short k = (instruction & 001777u) - 000001u;

    std::cout << "DAS" << " " << std::oct << k << std::dec << std::endl;

    auto mkLow = m_Memory->Read(k + 00001u);
    auto mkHigh = m_Memory->Read(k);
    auto l = m_Memory->Read(00001u);
    auto a = m_Memory->Read(00000u);

    auto [resultLow, interflow] = AddWords(l, mkLow);
    auto [resultHigh, overflow] = AddWords(AddWords(a, mkHigh).first, interflow);

    m_Memory->Write(k + 00001u, resultLow);
    m_Memory->Write(k, resultHigh);
    m_Memory->Write(00001u, 000000u);
    m_Memory->Write(00000u, overflow);
}


void egc::Sequencer::DCA (unsigned short instruction)
{
    unsigned short k = (instruction & 001777u) - 000001u;

    std::cout << "DCA" << " " << std::oct << k << std::dec << std::endl;

    auto mkLow = m_Memory->Read(k + 00001u);
    auto mkHigh = m_Memory->Read(k);

    m_Memory->Write(k + 00001u, mkLow);
    m_Memory->Write(k, mkHigh);
    m_Memory->Write(00001u, mkLow);
    m_Memory->Write(00000u, mkHigh);
}


void egc::Sequencer::DCS (unsigned short instruction)
{
    unsigned short k = (instruction & 001777u) - 000001u;

    std::cout << "DCS" << " " << std::oct << k << std::dec << std::endl;

    auto mkLow = m_Memory->Read(k + 00001u);
    auto mkHigh = m_Memory->Read(k);

    m_Memory->Write(k + 00001u, mkLow);
    m_Memory->Write(k, mkHigh);
    m_Memory->Write(00001u, ~mkLow & 077777u);
    m_Memory->Write(00000u, ~mkHigh & 077777u);
}


void egc::Sequencer::DIM (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "DIM" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);

    if (mk != 000000u && mk != 077777u)
    {
        unsigned short sign = mk & 040000u;

        if (sign == 040000u)
        {
            mk = AddWords(mk, 000001u).first;
        }
        else
        {
            mk = AddWords(mk, 077776u).first;
        }
    }

    m_Memory->Write(k, mk);
}


void egc::Sequencer::DV (unsigned short instruction)
{
    std::cout << "DV is currently not implemented" << std::endl;
}


void egc::Sequencer::DXCH (unsigned short instruction)
{
    unsigned short k = (instruction & 001777u) - 000001u;

    std::cout << "DXCH" << " " << std::oct << k << std::dec << std::endl;

    auto mkLow = m_Memory->Read(k + 00001u);
    auto mkHigh = m_Memory->Read(k);
    auto l = m_Memory->Read(00001u);
    auto a = m_Memory->Read(00000u);

    m_Memory->Write(k + 00001u, l);
    m_Memory->Write(k, a);
    m_Memory->Write(00001u, mkLow);
    m_Memory->Write(00000u, mkHigh);
}


void egc::Sequencer::EXTEND (unsigned short instruction)
{
    std::cout << "EXTEND" << std::endl;

    m_Memory->SetExtendFlag();
}


void egc::Sequencer::INCR (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "INCR" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);

    unsigned short sign = mk & 040000u;

    if (mk == 077777u)
    {
        mk = 000001u;
    }
    else
    {
        mk = AddWords(mk, 000001u).first;
    }

    m_Memory->Write(k, mk);
}


void egc::Sequencer::INDEX (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "INDEX" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    m_Memory->SetIndex(mk);

    m_Memory->Write(k, mk);
}


void egc::Sequencer::INDEXE (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "INDEXE" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    m_Memory->SetIndex(mk);

    m_Memory->Write(k, mk);

    m_Memory->SetExtendFlag();
}


void egc::Sequencer::INHINT (unsigned short instruction)
{
    std::cout << "INHINT is currently not implemented" << std::endl;
}


void egc::Sequencer::LXCH (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "LXCH" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto l = m_Memory->Read(00001u);

    m_Memory->Write(k, l);
    m_Memory->Write(00001u, mk);
}


void egc::Sequencer::MASK (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "MASK" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(00000u);

    unsigned short result = mk & a;

    m_Memory->Write(k, mk);
    m_Memory->Write(00000u, result);
}


void egc::Sequencer::MP (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "MP" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(00000u);

    auto digitsMk = mk & 037777u;
    auto digitsA = a & 037777u;

    auto signMk = mk & 040000u;
    auto signA = a & 040000u;

    if (signMk)
    {
        digitsMk = ~digitsMk & 037777u;
    }

    if (signA)
    {
        digitsA = ~digitsA & 037777u;
    }


    unsigned int result = 00000000000u;

    for (unsigned short i = 0u; i < 14u; ++i)
    {
        if (digitsA & (1u << i))
        {
            result += (static_cast<unsigned int>(digitsMk) << i);
        }
    }

    unsigned short resultLow = result & 00000037777u;
    unsigned short resultHigh = (result & 01777740000u) >> 14u;

    if (result == 00000000000u)
    {
        if ((a == 000000u || a == 077777u) && !(mk == 00000u || mk == 07777u) && signA != signMk)
        {
            resultLow = 077777u;
            resultHigh = 077777u;
        }
    }
    else
    {
        if (signMk != signA)
        {
            resultLow = ~resultLow & 077777u;
            resultHigh = ~resultHigh & 077777u;
        }
    }

    m_Memory->Write(k, mk);
    m_Memory->Write(00001u, resultLow);
    m_Memory->Write(00000u, resultHigh);
}


void egc::Sequencer::MSU (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "MSU" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(00000u);

    auto digitsMk = static_cast<short>(mk & 037777u);
    auto digitsA = static_cast<short>(a & 037777u);

    auto signMk = mk & 040000u;
    auto signA = a & 040000u;

    if (signMk)
    {
        digitsMk *= -1;
    }
    if (signA)
    {
        digitsA *= -1;
    }

    auto resultTwoComplement = digitsMk - digitsA;

    unsigned short result;

    if (resultTwoComplement > 0)
    {
        result = static_cast<unsigned short>(resultTwoComplement) & 037777u;
    }
    else
    {
        result = static_cast<unsigned short>(resultTwoComplement) & 077777u - 000001u;
    }

    m_Memory->Write(k, mk);
    m_Memory->Write(a, result);
}


void egc::Sequencer::QXCH (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "QXCH" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto q = m_Memory->Read(000002u);

    m_Memory->Write(k, q);
    m_Memory->Write(00002u, mk);
}


void egc::Sequencer::RELINT (unsigned short instruction)
{
    std::cout << "RELINT is currently not implemented" << std::endl;
}


void egc::Sequencer::SU (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "SU" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(00000u);

    auto [result, overflow] = AddWords(a, ~mk & 077777u);

    m_Memory->Write(k, mk);
    m_Memory->Write(00000u, result);

    m_Memory->SetAccumulatorOverflow(overflow);
}


void egc::Sequencer::TC (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "TC" << " " << std::oct << k << std::dec << std::endl;

    if (k != 00002u) // RETURN
    {
        auto z = m_Memory->Read(00005u);
        m_Memory->Write(00002u, z);
    }

    m_Memory->Write(00005u, k);
}


void egc::Sequencer::TCF (unsigned short instruction)
{
    unsigned short k = instruction & 007777u;

    std::cout << "TCF" << " " << std::oct << k << std::dec << std::endl;

    m_Memory->Write(000005u, k);
}


void egc::Sequencer::TS (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "TS" << " " << std::oct << k << std::dec << std::endl;

    if (k == 000000u) // OVSK
    {
        auto overflow = m_Memory->GetAccumulatorOverflow();

        if (overflow)
        {
            m_Memory->Write(00005u, m_Memory->Read(00005u) + 000001u);
        }
    }
    else
    {
        auto a = m_Memory->Read(00000u);

        auto overflow = m_Memory->GetAccumulatorOverflow();

        m_Memory->Write(k, a);

        if (overflow)
        {
            m_Memory->Write(00000u, overflow);
            m_Memory->Write(00005u, m_Memory->Read(00005u) + 000001u);
        }
        else
        {
            m_Memory->Write(00000u, a);
        }
    }
}


void egc::Sequencer::XCH (unsigned short instruction)
{
    unsigned short k = instruction & 001777u;

    std::cout << "XCH" << " " << std::oct << k << std::dec << std::endl;

    auto mk = m_Memory->Read(k);
    auto a = m_Memory->Read(000000u);

    m_Memory->Write(k, a);
    m_Memory->Write(00000u, mk);
}

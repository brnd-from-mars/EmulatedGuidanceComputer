//
// Created by Brendan Berg on 2019-10-08.
//

#include <iostream>
#include <string>
#include <vector>

#include <egc_util/FileSystem.hpp>
#include <egc_util/StringUtil.hpp>

#include <egc_emulator/Emulator.hpp>


#define CHECK_COMMAND_SIZE(X) if (command.size() < X)\
{\
    return;\
}

#define GET_USHORT_COMMAND(X) static_cast<unsigned int>(std::stoi(command[X], nullptr, 8))


egc::Emulator::Emulator ()
    : m_CommandFileMode(false)
{ }


egc::Emulator::~Emulator ()
{
    m_CommandFile.close();
}


void egc::Emulator::OpenCommandFile (const std::string& filePath)
{
    m_CommandFile.open(filePath);
    m_CommandFileMode = true;
}


bool egc::Emulator::ExecuteCommand (const std::string& commandString)
{
    auto command = StringUtil::Split(commandString, ' ');

    if (command.empty())
    {
        return true;
    }

    if (command[0] == std::string("exit"))
    {
        return false;
    }
    else if (command[0] == std::string("emulation"))
    {
        Emulation(command);
    }
    else if (command[0] == std::string("step"))
    {
        Step(command);
    }
    else if (command[0] == std::string("mem"))
    {
        Mem(command);
    }

    return true;
}


bool egc::Emulator::Update ()
{
    std::string commandString;

    if (m_CommandFileMode)
    {
        if (std::getline(m_CommandFile, commandString))
        {
            std::cout << "$ " << commandString << std::endl;
        }
        else
        {
            m_CommandFileMode = false;
        }
    }
    else
    {
        std::cout << "$ " << std::flush;
        std::getline(std::cin, commandString);
    }


    return ExecuteCommand(commandString);
}


void egc::Emulator::Emulation (const std::vector<std::string>& command)
{
    CHECK_COMMAND_SIZE(2)

    if (command[1] == std::string("init"))
    {
        CHECK_COMMAND_SIZE(3)

        if (m_Memory)
        {
            // TODO: Add error log
            return;
        }

        auto directoryPath = command[2];

        bool newInstance = !FileSystem::CheckDirectoryPath(directoryPath);
        m_Memory = std::make_shared<Memory>(directoryPath, newInstance);
        m_Sequencer = std::make_shared<Sequencer>(m_Memory);
    }
    else if (command[1] == std::string("close"))
    {
        if (m_Memory)
        {
            m_Memory.reset();
            m_Sequencer.reset();
        }
    }
    else if (command[1] == std::string("save"))
    {
        if (m_Memory)
        {
            m_Memory->SaveToFile();
        }
    }
    else if (command[1] == std::string("reload"))
    {
        if (m_Memory)
        {
            m_Memory->LoadFromFile();
        }
    }
}


void egc::Emulator::Step (const std::vector<std::string>& command)
{
    unsigned short steps = 1;

    if (command.size() > 1)
    {
        steps = GET_USHORT_COMMAND(1);
    }

    if (m_Memory)
    {
        for (unsigned short i = 0; i < steps; ++i)
        {
            m_Sequencer->Step();
        }
    }
}


void egc::Emulator::Mem (const std::vector<std::string>& command)
{
    CHECK_COMMAND_SIZE(2)

    if (command[1] == std::string("read"))
    {
        CHECK_COMMAND_SIZE(3)

        auto address = GET_USHORT_COMMAND(2);

        if (m_Memory)
        {
            std::cout << std::oct << address << ": " << m_Memory->Read(address) << std::dec << std::endl;
        }
    }
    else if (command[1] == std::string("write"))
    {
        CHECK_COMMAND_SIZE(4)

        auto address = GET_USHORT_COMMAND(2);
        auto word = GET_USHORT_COMMAND(3);

        if (m_Memory)
        {
            m_Memory->Write(address, word);
            std::cout << std::oct << address << ": " << m_Memory->Read(address) << std::dec << std::endl;
        }
    }
    else if (command[1] == std::string("reg"))
    {
        if (m_Memory)
        {
            std::cout << std::oct << "    A: " << m_Memory->Read(00000u) << std::dec << std::endl;
            std::cout << std::oct << "    L: " << m_Memory->Read(00001u) << std::dec << std::endl;
            std::cout << std::oct << "    Q: " << m_Memory->Read(00002u) << std::dec << std::endl;
            std::cout << std::oct << "EBANK: " << m_Memory->Read(00003u) << std::dec << std::endl;
            std::cout << std::oct << "FBANK: " << m_Memory->Read(00004u) << std::dec << std::endl;
            std::cout << std::oct << "    Z: " << m_Memory->Read(00005u) << std::dec << std::endl;
        }
    }
    else if (command[1] == std::string("rng"))
    {
        CHECK_COMMAND_SIZE(4)

        auto lowAddress = GET_USHORT_COMMAND(2);
        auto number = GET_USHORT_COMMAND(3);

        if (m_Memory)
        {
            for (unsigned short i = 0; i < number; ++i)
            {
                auto address = lowAddress + i;
                std::cout << std::oct << address << ": " << m_Memory->Read(address) << std::dec << std::endl;
            }
        }
    }
}

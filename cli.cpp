#include "cli.hpp"

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <algorithm>

namespace cli
{

Cli::Cli(const std::string& prompt) : m_prompt(prompt)
{
    caseSensitive = false;
}

Cli::~Cli()
{
}

void Cli::add(const std::string& cmd, const std::string& hint, std::function<void()> callback)
{
    m_mapCallbacks.insert({ cmd, callback });
}

void Cli::run()
{
    printPrompt();

    std::string cmd;
    std::getline(stream, cmd);

    if (!caseSensitive)
    {
        cmd = toLower(cmd);
    }

    auto it = m_mapCallbacks.find(cmd);
    if (it != m_mapCallbacks.end())
    {
        (it->second)();
    } else
    {
        std::cout << "Unrecognized command. Type 'help' to list available commands." << std::endl;
    }
}

void Cli::prompt(const std::string& prompt)
{
    m_prompt = prompt;
}

std::string Cli::toLower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char ch){ return std::tolower(ch); });
    return str;
}

void Cli::printPrompt()
{
    std::cout << "[" << m_prompt << "]# ";
}

void Cli::printHelp()
{
    std::cout << "Available commands:\n";
    for (const auto &it: m_mapCallbacks)
    {
        std::cout << 
    }
}

} // namespace Cli

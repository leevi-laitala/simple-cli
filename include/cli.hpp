#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <iomanip>

namespace cli
{

class Cli
{
public:
    Cli(const Cli&) = delete;

    Cli(const std::string& prompt)
        : m_prompt(prompt), m_quit(false) {}
    
    ~Cli() {}

    void add(const std::string& cmd, const std::string& hint, std::function<void()> callback)
    {
        m_mapCallbacks.insert({ cmd, { hint, callback } });
    }
    
    void run()
    {
        while (!m_quit)
        {
            printPrompt();
    
            std::string cmd;
            std::getline(std::cin, cmd);
    
            if (!caseSensitive)
            {
                cmd = toLower(cmd);
            }
    
            auto it = m_mapCallbacks.find(cmd);
            if (it != m_mapCallbacks.end())
            {
                (it->second.second)();
            } else
            {
                std::cout << "Unrecognized command. Type 'help' to list available commands."
                    << std::endl;
            }
        }
    }

    void quit()
    {
        m_quit = true;
    }

    void printHelp()
    {
        // Find out lenght of the string of the longest command
        size_t command_maxlen = 0;
        for (const auto &it : m_mapCallbacks)
        {
            if (it.first.length() > command_maxlen)
            {
                command_maxlen = it.first.length();
            }
        }

        std::cout << "Available commands:\n";
        for (const auto &it: m_mapCallbacks)
        {
            std::cout << "  " << std::left << std::setw(command_maxlen + 4) << it.first
                << it.second.first << "\n";
        }
    }
    
    void prompt(const std::string& prompt)
    {
        m_prompt = prompt;
    }

private:
    std::string toLower(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char ch){ return std::tolower(ch); });
        return str;
    }

    void printPrompt()
    {
        std::cout << "[" << m_prompt << "]$ ";
    }


public:
    bool caseSensitive;

private:
    std::unordered_map<std::string, std::pair<std::string, std::function<void()>>> m_mapCallbacks;
    std::string m_prompt;

    bool m_quit;
};

} // namespace cli

#endif // CLI_HPP

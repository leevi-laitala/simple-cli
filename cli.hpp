#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>

namespace cli
{

class Cli
{
public:
    Cli(const Cli&) = delete;

    Cli(const std::string& prompt)
        : m_prompt(prompt) {}
    ~Cli() {}

    void add(const std::string& cmd, const std::string& hint, std::function<void()> callback)
    {
        m_mapCallbacks.insert({ cmd, callback });
    }
    
    template<typename T>
    void add(const std::string& cmd, const std::string& hint, T callback)
    {
        m_mapCallbacks.insert({ cmd, callback });
    }

    void run()
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
            (it->second)();
        } else
        {
            std::cout << "Unrecognized command. Type 'help' to list available commands." << std::endl;
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
        std::cout << "[" << m_prompt << "]# ";
    }

    void printHelp()
    {
        std::cout << "Available commands:\n";
        //for (const auto &it: m_mapCallbacks)
        //{
        //    std::cout << 
        //}
    }

public:
    bool caseSensitive;

private:
    std::unordered_map<std::string, std::function<void()>> m_mapCallbacks;
    std::string m_prompt;
};

}

#endif // CLI_HPP

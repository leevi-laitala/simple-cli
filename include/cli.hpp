#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <utility>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace cli
{

template <typename ... Args> struct Select;

template <typename P, typename ... Args>
struct Select<P, Args...>
{
    template <typename F, typename Iter>
    static void execute(const F& f, Iter first, Iter last)
    {
        try {
            const P p = boost::lexical_cast<typename std::decay<P>::type>(*first);
            auto g = [&](auto ... pars){ f(p, pars...); };
            Select<Args...>::execute(g, std::next(first), last);
        } catch (boost::bad_lexical_cast& c)
        {
            std::cout << "prööt" << std::endl;
            return;
        }
    }
};

template <>
struct Select<>
{
    template <typename F, typename Iter>
    static void execute(const F& f, Iter first, Iter last)
    {
        // silence the unused warning in release mode when assert is disabled
        static_cast<void>(first);
        static_cast<void>(last);
        
        f();
    }
};

class Command
{
public:
    virtual void execute(std::vector<std::string> cmdWithArgs) = 0;
};

template<typename Func, typename ...Args>
class VaCommand : public Command
{
public:
    VaCommand(const std::string& name, Func func)
        : m_name(name), m_function(func) {}

    void execute(std::vector<std::string> cmdWithArgs) override
    {
        auto g = [&](auto ... args){ m_function(args ...); };
        Select<Args...>::execute(g, std::next(cmdWithArgs.begin()), cmdWithArgs.end());
    }
private:
    std::string m_name;
    Func m_function;
};

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
    
    template<typename T, typename R, typename ...Args>
    void addNew(const std::string& cmd, T& function, R (T::*)(Args ...) const)
    {
        m_mapNew.insert({ cmd, std::make_unique<VaCommand<T, Args ...>>(cmd, function) });
    }

    template<typename T>
    void addNew(const std::string& cmd, T function)
    {
        addNew(cmd, function, &T::operator());
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

            std::vector<std::string> cmdWithArgs;
            boost::split(cmdWithArgs, cmd, boost::is_any_of(" "), boost::token_compress_on);

            auto it = m_mapNew.find(cmdWithArgs[0]);
            if (it != m_mapNew.end())
            {
                std::cout << "found!" << std::endl;
                it->second->execute(cmdWithArgs);
            }
    
            //auto it = m_mapCallbacks.find(cmd);
            //if (it != m_mapCallbacks.end())
            //{
            //    (it->second.second)();
            //} else
            //{
            //    std::cout << "Unrecognized command. Type 'help' to list available commands."
            //        << std::endl;
            //}
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
    std::unordered_map<std::string, std::unique_ptr<Command>> m_mapNew;
    std::string m_prompt;

    bool m_quit;

};


} // namespace cli

#endif // CLI_HPP

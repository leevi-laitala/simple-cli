#include "cli.hpp"

#include <iostream>
#include <functional>

int main(int argc, const char* argv[])
{
    cli::Cli cli("beba");
    
    bool exit = false;

    cli.add("test", "Test command", [](){ std::cout << "Joo" << std::endl; });
    cli.add("jofa", "Test command", [](int a, int b){ std::cout << a + b << std::endl; });
    cli.add("quit", "Exits application", [&](){ exit = true; });
    
    while (!exit)
    {
        cli.run();
    }

    return 0;
}


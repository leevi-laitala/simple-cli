#include "include/cli.hpp"

#include <iostream>
#include <functional>

int main(int argc, const char* argv[])
{
    cli::Cli cli(argv[0]);
    
    cli.add("test", "Test command", [](){ std::cout << "Joo\n"; });
    //cli.add("jofa", "Test command", [](int a, int b){ std::cout << a + b << std::endl; });
    cli.add("exit", "Exits application", [&](){ cli.quit(); });
    
    cli.run();

    return 0;
}


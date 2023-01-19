#include "include/cli.hpp"

#include <iostream>
#include <functional>
#include <string>

int main(int argc, const char* argv[])
{
    cli::Cli cli(argv[0]);

    std::string kakkeli = "";
    
    cli.add("test", "Test command", [](){ std::cout << "Joo\n"; });
    cli.addNew("jofa", [](int a, int b){ std::cout << a + b << std::endl; });
    cli.addNew("print", [&](std::string str){ kakkeli = str; std::cout << kakkeli << std::endl; });
    cli.add("help", "Prints help", [&](){ cli.printHelp(); });
    cli.add("exit", "Exits application", [&](){ cli.quit(); });
    
    cli.run();

    return 0;
}


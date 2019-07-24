#include <iostream>
#include <string>

#include "interpreter.h"

int main()
{
    Interpreter interpretator;
    std::string line;


    while(true)
    {
        std::cout << "$ ";
        getline(std::cin, line);

        if (line == std::string("quit"))
            return 0;

        if (line == std::string(""));
        else std::cout << "> " << interpretator.translate(line) << std::endl << std::endl;
    }
}

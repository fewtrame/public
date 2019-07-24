#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "instruction.h"
#include "lexer.h"

class Interpreter
{
public:
    Interpreter();

    std::string translate(std::string);

    ~Interpreter();

private:
    void formInstructions();
    std::string calculate();
    void showTable() const;

private:
    Lexer _lexer;
    std::unordered_map<std::string, Instruction *> _instructions;
    std::vector<std::pair<std::string, std::string> > _table;
    std::vector<std::pair<std::string, std::string> >::const_reverse_iterator _iter;
};

#endif // INTERPRETER_H

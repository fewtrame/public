#include "interpreter.h"

#include <stack>

Interpreter::Interpreter()
{
    formInstructions();
}

std::string Interpreter::translate(std::string line)
{
    _table.clear();
    _lexer.analize(line, _table);
    _iter = _table.crbegin();

    return calculate();
}

void Interpreter::formInstructions()
{
    _instructions.emplace("add", new InstructionAdd);
    _instructions.emplace("sub", new InstructionSub);
    _instructions.emplace("mul", new InstructionMul);
    _instructions.emplace("concat", new InstructionConcat);

}

Interpreter::~Interpreter()
{
    for(auto &p : _instructions) {
        delete p.second;
    }
}

std::string Interpreter::calculate()
{
    std::stack<std::string> stack;

    while(_iter < _table.crend()) {
        if(_iter->first == ")") {
            _iter++;
            stack.push(calculate());
            _iter++;
        }
        else if (_iter->first == "(") {
            _iter++;
        }
        else if (_iter->second != "KEYWORD") {
            stack.push(_iter->first);
            _iter++;
        }
        else {
            return _instructions.find(_iter->first)->second->operator()(stack);
        }
    }
    throw std::runtime_error("Syntax Error");
}

void Interpreter::showTable() const
{
    std::vector<std::pair<std::string, std::string> >::const_iterator iter;
    for(iter = _table.begin(); iter < _table.end(); iter++) {
       std::cout << iter->first << " " << iter->second << std::endl;
    }
}













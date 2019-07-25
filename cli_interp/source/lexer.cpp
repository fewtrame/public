#include "lexer.h"

bool Lexer::analize(std::string line, std::list<std::pair<std::string, std::string> >& table)
{
    _line = line;
    _iter = _line.begin();

    for (; _iter < _line.end() + 1; _iter++) {
        inputSignal(*_iter);
        if (isFinalState()) {
            std::string str = getStateName();
            if (str[0] == 'F') {
                str += std::string(1, *_iter) + std::string(" at position ") + std::to_string(_iter - _line.begin() + 1);
                table.push_back(std::pair<std::string, std::string>(" ", str));
                resetState();
                return false;
            }
            table.push_back(std::pair<std::string, std::string>(getLexem(), getStateName()));
            resetState();
        }
    }

    resetState();
    return true;
}

void Lexer::inputSignal(char symbol)
{
    _lexem.push_back(symbol);

    if (isalpha(symbol)) {
        if (isupper(symbol))
            this->upperIn();
        else
            this->lowerIn();
    }
    else if (isdigit(symbol)) {
        this->digitIn();
    }
    else if (isspace(symbol)) {
        this->spaceIn();
    }
    else if (symbol == 0) {
        this->endofIn();
    }
    else if (symbol == 45) {
        this->minusIn();
    }
    else if (symbol == 34) {
        this->quoteIn();
    }
    else if (symbol > 39 && symbol < 42) {
        this->brackIn();
    }
    else {
        this->otherIn();
    }
}


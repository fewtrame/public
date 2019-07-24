#include "lexer.h"

void Lexer::analize(std::string line, std::vector<std::pair<std::string, std::string> >& table)
{
    _line = line;
    _iter = _line.begin();

    for (; _iter < _line.end() + 1; _iter++) {
        inputSignal(*_iter);
        if (isFinalState()) {
            table.push_back(std::pair<std::string, std::string>(getLexem(), getStateName()));
            resetState();
        }
    }

    resetState();
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
    else if (isspace(symbol) || symbol == 0) {
        this->spaceIn();
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


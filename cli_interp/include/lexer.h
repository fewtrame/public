#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <list>

#include "instruction.h"
#include "state.h"

class Lexer
{
private:
    State *_state;
    std::string _line;
    std::string _lexem;
    std::string::iterator _iter;

public:
    Lexer() { _state = new WaitSymbol; }
    ~Lexer() { delete _state; }

    bool analize(std::string, std::list<std::pair<std::string, std::string> >&);
    void inputSignal(char);
    void backIterator()                 { _iter--; _lexem.pop_back(); }
    char getLastSymbol() const          { return *_lexem.end(); }
    void removeLastSymbol()             { _lexem.pop_back(); }

    void resetState()                   { delete _state; _lexem.clear(); _state = new WaitSymbol; }
    void setState(State *state)         { delete _state; _state = state; }
    bool isFinalState() const           { return _state->isFinal(); }

    std::string getLexem() const        {return _lexem; }
    std::string getStateName() const    { return _state->getName(); }

public:
    void endofIn() { _state->endofIn(this); }
    void digitIn() { _state->digitIn(this); }     // [0-9]
    void lowerIn() { _state->lowerIn(this); }     // [a-z]
    void spaceIn() { _state->spaceIn(this); }     // [\st]
    void quoteIn() { _state->quoteIn(this); }     // [ " ]
    void brackIn() { _state->brackIn(this); }     // [(|)]
    void otherIn() { _state->otherIn(this); }     // [oth]
    void upperIn() { _state->upperIn(this); }     // [A-Z]
    void minusIn() { _state->minusIn(this); }     // [ - ]
};

#endif // LEXER_H

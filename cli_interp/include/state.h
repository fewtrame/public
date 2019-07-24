#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <iostream>

class Lexer;

class State
{
private:
    std::string _name;
    bool        _final;

public:
    State(const std::string& name, const bool& final) : _name(name), _final(final) { }

    std::string getName() const { return _name; }
    bool        isFinal() const { return _final; }

public:
    virtual void digitIn(Lexer *) {}
    virtual void lowerIn(Lexer *) {}
    virtual void spaceIn(Lexer *) {}
    virtual void quoteIn(Lexer *) {}
    virtual void brackIn(Lexer *) {}
    virtual void otherIn(Lexer *) {}
    virtual void minusIn(Lexer *) {}
    virtual void upperIn(Lexer *) {}

    virtual ~State();
};

class WaitSymbol : public State
{
public:
    WaitSymbol() : State(std::string("WaitSymbol"), false) { }

    virtual void spaceIn(Lexer *);
    virtual void digitIn(Lexer *);
    virtual void lowerIn(Lexer *);
    virtual void quoteIn(Lexer *);
    virtual void brackIn(Lexer *);
    virtual void otherIn(Lexer *);
    virtual void minusIn(Lexer *);
    virtual void upperIn(Lexer *);

    virtual ~WaitSymbol() {}
};

class FormString : public State
{
public:
    FormString() : State(std::string("FormString"), false) { }

    virtual void quoteIn(Lexer *);

    virtual ~FormString() {}
};

class FormKeyword : public State
{
public:
    FormKeyword() : State(std::string("FormKeyword"), false) { }

    virtual void digitIn(Lexer *);
    virtual void spaceIn(Lexer *);
    virtual void quoteIn(Lexer *);
    virtual void brackIn(Lexer *);
    virtual void otherIn(Lexer *);
    virtual void minusIn(Lexer *);
    virtual void upperIn(Lexer *);

    virtual ~FormKeyword() {}

private:
    bool isKeyword(std::string);
};

class ReceivedMinus : public State
{
public:
    ReceivedMinus() : State(std::string("ReceivedMinus"), false) { }

    virtual void digitIn(Lexer *);
    virtual void lowerIn(Lexer *);
    virtual void spaceIn(Lexer *);
    virtual void quoteIn(Lexer *);
    virtual void brackIn(Lexer *);
    virtual void otherIn(Lexer *);
    virtual void minusIn(Lexer *);
    virtual void upperIn(Lexer *);

    virtual ~ReceivedMinus() {}
};

class FormDigit : public State
{
public:
    FormDigit() : State(std::string("FormDigit"), false) { }

    virtual void lowerIn(Lexer *);
    virtual void spaceIn(Lexer *);
    virtual void quoteIn(Lexer *);
    virtual void brackIn(Lexer *);
    virtual void otherIn(Lexer *);
    virtual void minusIn(Lexer *);
    virtual void upperIn(Lexer *);

    virtual ~FormDigit() {}
};

class FormLiteral : public State
{
public:
    FormLiteral() : State(std::string("FormLiteral"), false) { }

    virtual void digitIn(Lexer *);
    virtual void spaceIn(Lexer *);
    virtual void quoteIn(Lexer *);
    virtual void brackIn(Lexer *);
    virtual void otherIn(Lexer *);
    virtual void minusIn(Lexer *);

    virtual ~FormLiteral() {}
};

// Необходимо проверять Keyword {add mul sub concat}
class FoundLiteral: public State
{
public:
    FoundLiteral() : State(std::string("LITERAL"), true) { }

    virtual ~FoundLiteral() {}
};

class FoundString: public State
{
public:
    FoundString() : State(std::string("STRING"), true) { }

    virtual ~FoundString() {}
};

class FoundKeyword: public State
{
public:
    FoundKeyword() : State(std::string("KEYWORD"), true) { }

    virtual ~FoundKeyword() {}
};

class FoundDigit: public State
{
public:
    FoundDigit() : State(std::string("DIGIT"), true) { }

    virtual ~FoundDigit() {}
};

class FoundDelimeter: public State
{
public:
    FoundDelimeter() : State(std::string("DELIMETER"), true) { }

    virtual ~FoundDelimeter() {}
};

class LexicalError: public State
{
public:
    LexicalError() : State(std::string("ERROR"), true) { }

    virtual ~LexicalError() {}
};

#endif // STATE_H

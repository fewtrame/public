#include "state.h"
#include "lexer.h"
#include <iostream>

State::~State() {};

/*WaitSymbol*/
void WaitSymbol::spaceIn(Lexer * lexer) { lexer->removeLastSymbol();
                                          lexer->setState(new WaitSymbol); delete this; }
void WaitSymbol::digitIn(Lexer * lexer) { lexer->setState(new FormDigit); delete this; }
void WaitSymbol::lowerIn(Lexer * lexer) { lexer->setState(new FormKeyword); delete this; }
void WaitSymbol::quoteIn(Lexer * lexer) { lexer->setState(new FormString); delete this; }
void WaitSymbol::brackIn(Lexer * lexer) { lexer->setState(new FoundDelimeter); delete this; }
void WaitSymbol::otherIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void WaitSymbol::minusIn(Lexer * lexer) { lexer->setState(new ReceivedMinus); delete this; }
void WaitSymbol::upperIn(Lexer * lexer) { lexer->setState(new FormLiteral); delete this; }

/*FormDigit*/
void FormDigit::lowerIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormDigit::spaceIn(Lexer * lexer) { lexer->removeLastSymbol();
                                         lexer->setState(new FoundDigit); delete this; }
void FormDigit::quoteIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormDigit::brackIn(Lexer * lexer) { lexer->backIterator();
                                         lexer->setState(new FoundDigit); delete this; }
void FormDigit::otherIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormDigit::minusIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormDigit::upperIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }

/*FormLiteral*/
void FormLiteral::digitIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormLiteral::spaceIn(Lexer * lexer) { lexer->removeLastSymbol();
                                           lexer->setState(new FoundLiteral); delete this; }
void FormLiteral::quoteIn(Lexer * lexer) { throw std::runtime_error("Lexical Error");  }
void FormLiteral::brackIn(Lexer * lexer) { lexer->backIterator();
                                           lexer->setState(new FoundLiteral); delete this; }
void FormLiteral::otherIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormLiteral::minusIn(Lexer * lexer) { lexer->setState(new LexicalError); delete this; }

/*FormString*/
void FormString::quoteIn(Lexer * lexer) { lexer->setState(new FoundString); delete this; }

/*FormKeyword*/
void FormKeyword::digitIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormKeyword::quoteIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormKeyword::brackIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormKeyword::otherIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormKeyword::minusIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormKeyword::upperIn(Lexer * lexer) { throw std::runtime_error("Lexical Error"); }
void FormKeyword::spaceIn(Lexer * lexer)
{
    lexer->removeLastSymbol();
    std::string lexem = lexer->getLexem();
    if(isKeyword(lexem))
        lexer->setState(new FoundKeyword);
    else
        lexer->setState(new FoundLiteral);
    delete this;
}
bool FormKeyword::isKeyword(std::string lexem)
{
    std::vector<std::string>::iterator iter = Keywords.begin();
    for (; iter < Keywords.end(); iter++) {
        if(*iter == lexem) {
            return true;
        }
    }
    return false;
}
/*ReceivedMinus*/
void ReceivedMinus::digitIn(Lexer * lexer) { lexer->setState(new FormDigit); delete this; }
void ReceivedMinus::lowerIn(Lexer * lexer) { lexer->setState(new FormLiteral); delete this; }
void ReceivedMinus::spaceIn(Lexer * lexer) { lexer->setState(new LexicalError); delete this; }
void ReceivedMinus::quoteIn(Lexer * lexer) { lexer->setState(new LexicalError); delete this; }
void ReceivedMinus::brackIn(Lexer * lexer) { lexer->setState(new LexicalError); delete this; }
void ReceivedMinus::otherIn(Lexer * lexer) { lexer->setState(new LexicalError); delete this; }
void ReceivedMinus::minusIn(Lexer * lexer) { lexer->setState(new LexicalError); delete this; }
void ReceivedMinus::upperIn(Lexer * lexer) { lexer->setState(new FormLiteral); delete this; }

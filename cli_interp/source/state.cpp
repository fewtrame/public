#include "state.h"
#include "lexer.h"
#include <iostream>

State::~State() { };

/*WaitSymbol*/
void WaitSymbol::spaceIn(Lexer * lexer) { lexer->removeLastSymbol();
                                          lexer->setState(new WaitSymbol); ; }
void WaitSymbol::digitIn(Lexer * lexer) { lexer->setState(new FormDigit); ; }
void WaitSymbol::lowerIn(Lexer * lexer) { lexer->setState(new FormKeyword); ; }
void WaitSymbol::quoteIn(Lexer * lexer) { lexer->setState(new FormString); ; }
void WaitSymbol::brackIn(Lexer * lexer) { lexer->setState(new FoundDelimeter); ; }
void WaitSymbol::minusIn(Lexer * lexer) { lexer->setState(new ReceivedMinus); ; }
void WaitSymbol::upperIn(Lexer * lexer) { lexer->setState(new FormLiteral); ; }
void WaitSymbol::otherIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: wrong symbol ")); ; }

/*FormString*/
void FormString::quoteIn(Lexer * lexer) { lexer->setState(new FoundString); ; }
void FormString::endofIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: string need second \""));}

/*FormDigit*/
void FormDigit::spaceIn(Lexer * lexer) { lexer->removeLastSymbol();
                                         lexer->setState(new FoundDigit); ; }
void FormDigit::brackIn(Lexer * lexer) { lexer->backIterator();
                                         lexer->setState(new FoundDigit); ; }
void FormDigit::quoteIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [0-9] expected, but found ")); ;  }
void FormDigit::lowerIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [0-9] expected, but found ")); ;  }
void FormDigit::otherIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [0-9] expected, but found ")); ;  }
void FormDigit::minusIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [0-9] expected, but found ")); ;  }
void FormDigit::upperIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [0-9] expected, but found ")); ;  }

/*FormLiteral*/
void FormLiteral::spaceIn(Lexer * lexer) { lexer->removeLastSymbol();
                                           lexer->setState(new FoundLiteral); ; }
void FormLiteral::brackIn(Lexer * lexer) { lexer->backIterator();
                                           lexer->setState(new FoundLiteral); ; }
void FormLiteral::quoteIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ; }
void FormLiteral::digitIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ; }
void FormLiteral::otherIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ; }
void FormLiteral::minusIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ; }

/*FormKeyword*/
void FormKeyword::digitIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ;}
void FormKeyword::quoteIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ;}
void FormKeyword::brackIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ;}
void FormKeyword::otherIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ;}
void FormKeyword::minusIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ;}
void FormKeyword::upperIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: [aA-zZ] expected, but found ")); ;}
void FormKeyword::spaceIn(Lexer * lexer)
{
    lexer->removeLastSymbol();
    std::string lexem = lexer->getLexem();
    if(isKeyword(lexem))
        lexer->setState(new FoundKeyword);
    else
        lexer->setState(new FoundLiteral);
    ;
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
void ReceivedMinus::digitIn(Lexer * lexer) { lexer->setState(new FormDigit); ; }
void ReceivedMinus::lowerIn(Lexer * lexer) { lexer->setState(new FormLiteral); ; }
void ReceivedMinus::spaceIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: single -")); ; }
void ReceivedMinus::quoteIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: wrong combination -")); ; }
void ReceivedMinus::brackIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: wrong combination -")); ; }
void ReceivedMinus::otherIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: wrong combination -")); ; }
void ReceivedMinus::minusIn(Lexer * lexer) { lexer->setState(new LexicalError("Failure: double -")); ; }
void ReceivedMinus::upperIn(Lexer * lexer) { lexer->setState(new FormLiteral); }

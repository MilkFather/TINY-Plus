#ifndef __TINY_SYNTAX_H__
#define __TINY_SYNTAX_H__

struct Program;

#include <string>
#include "lex/lexical.h"
#include "syntax/syntaxgenerator.h"

using namespace std;

class Syntax {
private:
    Lex* lex;
    Program* syntaxroot;
    Token TokOnHold;

public:
    Syntax(): lex(nullptr), syntaxroot(nullptr){};
    void AssignLex(Lex* _lex);
    void Parse();
    Program* SyntaxTreeRoot() const;

    Token PeekToken() const;
    void ConsumeToken();
    string LaTeX() const;
};

#endif
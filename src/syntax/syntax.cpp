#include "syntax/syntax.h"
#include "lex/lexdef.h"
#include "tinyexception.h"

using namespace std;

void Syntax::AssignLex(Lex* _lex) {
    this->lex = _lex;
    if (this->syntaxroot != nullptr) {
        delete syntaxroot;
    }
}

void Syntax::Parse() {
    if (this->syntaxroot != nullptr) {
        delete syntaxroot;
    }
    TokOnHold = this->lex->GetNextToken();
    if ((this->syntaxroot = MatchProgram(*this)) == nullptr) {
        throw SyntaxException(this->TokOnHold.t_Line.l_File, this->TokOnHold.t_Line.l_Row, this->TokOnHold.t_Line.l_Col, (this->TokOnHold.t_Kind == TYPE_EOF ? "END OF FILE" : this->TokOnHold.t_Content));
    }
}

Program* Syntax::SyntaxTreeRoot() const {
    return this->syntaxroot;
}

Token Syntax::PeekToken() const {
    return this->TokOnHold;
}

void Syntax::ConsumeToken() {
    this->TokOnHold = this->lex->GetNextToken();
}

string Syntax::LaTeX() const {
    string s = "\\begin{forest}\n";
    if (this->syntaxroot == nullptr) {
        s = s + "[ Program ]";
    } else {
        s = s + this->syntaxroot->LaTeX();
    }
    s = s + "\n\\end{forest}";
    return s;
}

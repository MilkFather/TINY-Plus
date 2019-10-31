#include "lex/lexical.h"
#include "lex/lexdef.h"
#include "lex/lexstate.h"
#include <cstdio>
#include <cstring>
#include <sys/errno.h>
#include "tinyexception.h"

Lex::Lex() {
    this->m_Fileopen = false;
    this->m_Filename = "";
}

Lex::Lex(const string fn) {
    this->m_Fileopen = false;
    this->m_Filename = "";
    this->AssignFile(fn);
}

Lex::~Lex() {
    if (this->m_Fileopen) {
        fclose(this->m_Filehandle);
    }
    this->m_Fileopen = false;
}

bool Lex::AssignFile(const string fn) {
    if ((this->m_Filehandle = fopen(fn.c_str(), "r")) == nullptr) {
        this->m_Fileopen = false;
        throw IOException(fn, strerror(errno));
        return false;
    } else {
        this->m_Fileopen = true;
        this->m_Filename = fn;
        this->m_CurrentState = STATE_INIT;
        this->m_OnHold = "";
        this->m_CurrentLine = 1;
        this->m_CurrentCol = 1;
        this->m_LastLineLength = -1;
        this->m_FileInit = true;
        return true;
    }
}

void Lex::Consume() {
    this->m_OnHold += this->m_PeekHold;
    if (this->m_PeekHold == '\n') {
        this->m_LastLineLength = this->m_CurrentCol;
        this->m_CurrentLine += 1;
        this->m_CurrentCol = 1;
    } else {
        this->m_CurrentCol += 1;
    }
    this->m_PeekHold = fgetc(this->m_Filehandle);
}

void Lex::GenerateToken(int TokenType) {
    if (this->m_OnHold == "IF" || this->m_OnHold == "ELSE" || this->m_OnHold == "WRITE" || this->m_OnHold == "READ" || this->m_OnHold == "RETURN" || this->m_OnHold == "BEGIN" || this->m_OnHold == "END" || this->m_OnHold == "MAIN" || this->m_OnHold == "INT" || this->m_OnHold == "REAL" || this->m_OnHold == "WHILE") {
        TokenType = TYPE_KEYWORD;
    }
    if (TokenType == TYPE_STRING) {
        this->m_OnHold.pop_back();
        this->m_OnHold.erase(this->m_OnHold.begin());
    }
    
    this->m_NewTok = true;
    LineInfo li;
    li.l_File = this->m_Filename;
    li.l_Row = this->m_CurrentLine;
    li.l_Col = ((this->m_CurrentCol == 1) ? this->m_LastLineLength : this->m_CurrentCol - 1);
    this->m_Tokenbuf.t_Content = this->m_OnHold;
    this->m_Tokenbuf.t_Kind = TokenType;
    this->m_Tokenbuf.t_Line = li;
    this->Clear();
}

void Lex::Clear() {
    this->m_OnHold = "";
}

char Lex::Peek() {
    return this->m_PeekHold;
}

void Lex::Revert(const char c) {
    ungetc(this->m_PeekHold, this->m_Filehandle); // POSIX states that only one-letter rewind is guranteed. Good luck we only need one-letter rewinds.
    this->m_PeekHold = c;
    if (c == '\n' || this->m_CurrentCol == 1) {
        this->m_CurrentLine -= 1;
        this->m_CurrentCol = this->m_LastLineLength;
    } else {
        this->m_CurrentCol -= 1;
    }
}

void Lex::Refuse() {
    throw LexicalException(this->m_Filename, this->m_CurrentLine, this->m_CurrentCol, this->m_PeekHold);
}

bool InitOrAccepting(int State) {
    for (int i = 0; i < 17; i++) {
        if (State == TerminatingStates[i]) {
            return true;
        }
    }
    return false;
}

Token Lex::GetNextToken() {
    if (this->m_Fileopen == false) {
        throw IOException();
    }
    if (this->m_FileInit == true) {
        this->m_FileInit = false;
        this->m_PeekHold = fgetc(this->m_Filehandle);
    }
    if (this->m_PeekHold == EOF) {
        Token tok;
        LineInfo li;
        tok.t_Kind = TYPE_EOF;
        tok.t_Content = "";
        li.l_Row = this->m_CurrentLine;
        li.l_File = this->m_Filename;
        li.l_Col = this->m_CurrentCol;
        tok.t_Line = li;
        return tok;
    }
    this->m_NewTok = false;
    while (this->m_NewTok == false && this->m_PeekHold != EOF) {
        this->m_CurrentState = StateMachine[this->m_CurrentState](*this);
    }
    if (this->m_NewTok == false) {
        // encounter EOF before a new token
        if (!InitOrAccepting(this->m_CurrentState)) {
            this->Refuse();
        }
        if (!(this->m_CurrentState == STATE_INIT)) {
            this->m_CurrentState = StateMachine[this->m_CurrentState](*this);
        }
        if (this->m_NewTok == false) {  // Return an EOF token
            Token tok;
            LineInfo li;
            tok.t_Kind = TYPE_EOF;
            tok.t_Content = "";
            li.l_Row = this->m_CurrentLine;
            li.l_File = this->m_Filename;
            li.l_Col = this->m_CurrentCol;
            tok.t_Line = li;
            return tok;
        }
    }
    return this->m_Tokenbuf;
}

#ifndef __TINY_LEXICAL_H__
#define __TINY_LEXICAL_H__

#include <string>
#include <cstdio>

using namespace std;

/** 
 * LineInfo saves the token's position info. 
 * Note that there is no character count inside a line, because this information is only useful in lexical parsing.
 */
struct LineInfo {
    int l_Row;              // The line number
    int l_Col;              // The column number
    string l_File;          // The name of the source file
};

/** 
 * Token is used in grammar parsing.
 */
struct Token {
    int t_Kind;             // Token kind
    string t_Content;       // Token content, represented in std::string, even if it may represent a number
    LineInfo t_Line;        // The line information of the token
};

/**
 * Lex is the main lexical parser.
 * It is used by grammar parsing module.
 */
class Lex {
private:
    bool m_Fileopen;
    string m_Filename;
    FILE *m_Filehandle;

    string m_OnHold;
    char m_PeekHold;
    int m_CurrentState;

    int m_CurrentLine;
    int m_CurrentCol;
    int m_LastLineLength;

    bool m_FileInit;
    bool m_NewTok;
    Token m_Tokenbuf;

public:
    Lex();
    Lex(const string fn);
    ~Lex();

    bool AssignFile(const string fn);

    void Consume();
    void GenerateToken(int TokenType);
    void Clear();
    char Peek();
    void Revert(const char c);
    void Refuse();

    Token GetNextToken();
};

#endif
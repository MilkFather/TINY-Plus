#ifndef __TINY_SYNTAX_GENERATOR__
#define __TINY_SYNTAX_GENERATOR__

class Syntax;

#include "syntax/syntax.h"
#include "lex/lexical.h"
#include <string>

using namespace std;

#pragma mark Forward declarations of nonterminals
// Forward declarations of all non-terminals
// High-level program structures
struct Program;                  // Program                  ->      MethodDecl MethodDecls
struct MethodDecl;               // MethodDecl               ->      Type OptionalMain "Id" "(" OptionalFormalParams ")" Block
struct MethodDecls;              // MethodDecls              ->      MethodDecl MethodDecls | e
struct OptionalMain;             // OptionalMain             ->      "MAIN" | e
struct OptionalFormalParams;     // OptionalFormalParams     ->      FormalParams | e
struct FormalParams;             // FormalParams             ->      FormalParam AfterFormalParams
struct FormalParam;              // FormalParam              ->      Type "Id"
struct AfterFormalParams;        // AfterFormalParams        ->      "," FormalParams | e
struct Type;                     // Type                     ->      "INT" | "REAL"

// Statements
struct Block;                    // Block                    ->      "BEGIN" Statements "END"
struct Statement;                // Statement                ->      Block | LocalVarDecl | AssignStmt | ReturnStmt | IfStmt | WriteStmt | ReadStmt | WhileStmt
struct Statements;               // Statements               ->      Statement Statements | e
struct LocalVarDecl;             // LocalVarDecl             ->      "INT" "Id" ";" | "REAL" "Id" ";"
struct AssignStmt;               // AssignStmt               ->      "Id" ":=" Expression ";"
struct ReturnStmt;               // ReturnStmt               ->      "RETURN" Expression ";"
struct IfStmt;                   // IfStmt                   ->      "IF" "(" BoolExpression ")" Statement OptionalElseStmt
struct OptionalElseStmt;         // OptionalElseStmt         ->      "ELSE" Statement | e
struct WriteStmt;                // WriteStmt                ->      "WRITE" "(" Expression "," "STRING" ")" ";"
struct ReadStmt;                 // ReadStmt                 ->      "READ" "(" "Id" "," "STRING" ")" ";"
struct WhileStmt;                // WhileStmt                ->      "WHILE" "(" BoolExpression ")" Statement

// Expressions
struct Expression;               // Expression               ->      MultiplicativeExpr MultiplicativeExprs
struct MultiplicativeExpr;       // MultiplicativeExpr       ->      PrimaryExpr PrimaryExprs
struct MultiplicativeExprs;      // MultiplicativeExprs      ->      "+" MultiplicativeExpr MultiplicativeExprs | "-" MultiplicativeExpr MultiplicativeExprs | e
struct PrimaryExpr;              // PrimaryExpr              ->      "Num" | "Id" OptionalActualParams | "(" Expression ")"
struct PrimaryExprs;             // PrimaryExprs             ->      "*" PrimaryExpr PrimaryExprs | "/" PrimaryExpr PrimaryExprs | e
struct BoolExpression;           // BoolExpression           ->      Expression AfterBoolExpression
struct AfterBoolExpression;      // AfterBoolExpression      ->      "==" Expression | "!=" Expression | "<" Expression | ">" Expression | "<=" Expression | ">=" Expression
struct OptionalActualParams;     // OptionalActualParams     ->      "(" ActualParams ")" | e
struct ActualParams;             // ActualParams             ->      Expression AfterActualParams | e
struct AfterActualParams;        // AfterActualParams        ->      "," Expression AfterActualParams | e

#pragma mark Formal declarations and generators of nonterminals
// Formal declarations and generators of all non-terminals
// High-level program structures
struct Program {
    MethodDecl* _MethodDecl;
    MethodDecls* _MethodDecls;
    Program(): _MethodDecl(nullptr), _MethodDecls(nullptr){};
    ~Program();
    string LaTeX() const;
};
Program* MatchProgram(Syntax &syn);

struct MethodDecl {
    Type* _Type;
    OptionalMain* _OptionalMain;
    Token* _IdToken;
    Token* _LeftParenthesisToken;
    OptionalFormalParams* _OptionalFormalParams;
    Token* _RightParenthesisToken;
    Block* _Block;
    MethodDecl(): _Type(nullptr), _OptionalMain(nullptr), _IdToken(nullptr), _LeftParenthesisToken(nullptr), _OptionalFormalParams(nullptr), _RightParenthesisToken(nullptr), _Block(nullptr){};
    ~MethodDecl();
    string LaTeX() const;
};
MethodDecl* MatchMethodDecl(Syntax &syn);

struct MethodDecls {
    int selector;  // 0 or 1
    MethodDecl* _MethodDecl;
    MethodDecls* _MethodDecls;
    MethodDecls(): _MethodDecl(nullptr), _MethodDecls(nullptr){};
    ~MethodDecls();
    string LaTeX() const;
};
MethodDecls* MatchMethodDecls(Syntax &syn);

struct OptionalMain {
    int selector;  // 0 or 1
    Token* _MainToken;
    OptionalMain(): _MainToken(nullptr) {};
    ~OptionalMain();
    string LaTeX() const;
};
OptionalMain* MatchOptionalMain(Syntax &syn);

struct OptionalFormalParams {
    int selector;
    FormalParams* _FormalParams;
    OptionalFormalParams(): _FormalParams(nullptr){};
    ~OptionalFormalParams();
    string LaTeX() const;
};
OptionalFormalParams* MatchOptionalFormalParams(Syntax &syn);

struct FormalParams {
    FormalParam* _FormalParam;
    AfterFormalParams* _AfterFormalParams;
    FormalParams(): _FormalParam(nullptr), _AfterFormalParams(nullptr){};
    ~FormalParams();
    string LaTeX() const;
};
FormalParams* MatchFormalParams(Syntax &syn);

struct FormalParam {
    Type* _Type;
    Token* _IdToken;
    FormalParam(): _Type(nullptr), _IdToken(nullptr){};
    ~FormalParam();
    string LaTeX() const;
};
FormalParam* MatchFormalParam(Syntax &syn);

struct AfterFormalParams {
    int selector;  // 0 or 1
    Token* _CommaToken;
    FormalParams* _FormalParams;
    AfterFormalParams(): _CommaToken(nullptr), _FormalParams(nullptr){};
    ~AfterFormalParams();
    string LaTeX() const;
};
AfterFormalParams* MatchAfterFormalParams(Syntax &syn);

struct Type {
    int selector;  // 0 or 1
    Token* _TypeToken;
    Type(): _TypeToken(nullptr){};
    ~Type();
    string LaTeX() const;
};
Type* MatchType(Syntax &syn);

// Statements
struct Block {
    Token* _BeginToken;
    Statements* _Statements;
    Token* _EndToken;
    Block(): _BeginToken(nullptr), _Statements(nullptr), _EndToken(nullptr){};
    ~Block();
    string LaTeX() const;
};
Block* MatchBlock(Syntax &syn);

struct Statement {
    int selector;  // 0, 1, 2, 3, 4, 5, 6
    Block* _Block;
    LocalVarDecl* _LocalVarDecl;
    AssignStmt* _AssignStmt;
    ReturnStmt* _ReturnStmt;
    IfStmt* _IfStmt;
    WriteStmt* _WriteStmt;
    ReadStmt* _ReadStmt;
    WhileStmt* _WhileStmt;
    Statement(): _Block(nullptr), _LocalVarDecl(nullptr), _AssignStmt(nullptr), _ReturnStmt(nullptr), _IfStmt(nullptr), _WriteStmt(nullptr), _ReadStmt(nullptr), _WhileStmt(nullptr){};
    ~Statement();
    string LaTeX() const;
};
Statement* MatchStatement(Syntax &syn);

struct Statements {
    int selector;  // 0 or 1
    Statement* _Statement;
    Statements* _Statements;
    Statements(): _Statement(nullptr), _Statements(nullptr){};
    ~Statements();
    string LaTeX() const;
};
Statements* MatchStatements(Syntax &syn);

struct LocalVarDecl {
    int selector; // 0 or 1
    Token* _TypeToken;
    Token* _IdToken;
    Token* _SemicolonToken;
    LocalVarDecl(): _TypeToken(nullptr), _IdToken(nullptr), _SemicolonToken(nullptr){};
    ~LocalVarDecl();
    string LaTeX() const;
};
LocalVarDecl* MatchLocalVarDecl(Syntax &syn);

struct AssignStmt {
    Token* _IdToken;
    Token* _AssignToken;
    Expression* _Expression;
    Token* _SemicolonToken;
    AssignStmt(): _IdToken(nullptr), _AssignToken(nullptr), _Expression(nullptr), _SemicolonToken(nullptr){};
    ~AssignStmt();
    string LaTeX() const;
};
AssignStmt* MatchAssignStmt(Syntax &syn);

struct ReturnStmt {
    Token* _ReturnToken;
    Expression* _Expression;
    Token* _SemicolonToken;
    ReturnStmt(): _ReturnToken(nullptr), _Expression(nullptr), _SemicolonToken(nullptr){};
    ~ReturnStmt();
    string LaTeX() const;
};
ReturnStmt* MatchReturnStmt(Syntax &syn);

struct IfStmt {
    Token* _IfToken;
    Token* _LeftParenthesisToken;
    BoolExpression* _BoolExpression;
    Token* _RightParenthesisToken;
    Statement* _Statement;
    OptionalElseStmt* _OptionalElseStmt;
    IfStmt(): _IfToken(nullptr), _LeftParenthesisToken(nullptr), _BoolExpression(nullptr), _RightParenthesisToken(nullptr), _Statement(nullptr), _OptionalElseStmt(nullptr){};
    ~IfStmt();
    string LaTeX() const;
};
IfStmt* MatchIfStmt(Syntax &syn);

struct OptionalElseStmt {
    int selector;  // 0 or 1
    Token* _ElseToken;
    Statement* _Statement;
    OptionalElseStmt(): _ElseToken(nullptr), _Statement(nullptr){};
    ~OptionalElseStmt();
    string LaTeX() const;
};
OptionalElseStmt* MatchOptionalElseStmt(Syntax &syn);

struct WriteStmt {
    Token* _WriteToken;
    Token* _LeftParenthesisToken;
    Expression* _Expression;
    Token* _CommaToken;
    Token* _StringToken;
    Token* _RightParenthesisToken;
    Token* _SemicolonToken;
    WriteStmt(): _WriteToken(nullptr), _LeftParenthesisToken(nullptr), _Expression(nullptr), _CommaToken(nullptr), _StringToken(nullptr), _RightParenthesisToken(nullptr), _SemicolonToken(nullptr){};
    ~WriteStmt();
    string LaTeX() const;
};
WriteStmt* MatchWriteStmt(Syntax &syn);

struct ReadStmt {
    Token* _WriteToken;
    Token* _LeftParenthesisToken;
    Token* _IdToken;
    Token* _CommaToken;
    Token* _StringToken;
    Token* _RightParenthesisToken;
    Token* _SemicolonToken;
    ReadStmt(): _WriteToken(nullptr), _LeftParenthesisToken(nullptr), _IdToken(nullptr), _CommaToken(nullptr), _StringToken(nullptr), _RightParenthesisToken(nullptr), _SemicolonToken(nullptr){};
    ~ReadStmt();
    string LaTeX() const;
};
ReadStmt* MatchReadStmt(Syntax &syn);

struct WhileStmt {
    Token* _WhileToken;
    Token* _LeftParenthesisToken;
    BoolExpression* _BoolExpression;
    Token* _RightParenthesisToken;
    Statement* _Statement;
    WhileStmt(): _WhileToken(nullptr), _LeftParenthesisToken(nullptr), _BoolExpression(nullptr), _RightParenthesisToken(nullptr), _Statement(nullptr){};
    ~WhileStmt();
    string LaTeX() const;
};
WhileStmt* MatchWhileStmt(Syntax &syn);

// Expressions
struct Expression {
    MultiplicativeExpr* _MultiplicativeExpr;
    MultiplicativeExprs* _MultiplicativeExprs;
    Expression(): _MultiplicativeExpr(nullptr), _MultiplicativeExprs(nullptr){};
    ~Expression();
    string LaTeX() const;
};
Expression* MatchExpression(Syntax &syn);

struct MultiplicativeExpr {
    PrimaryExpr* _PrimaryExpr;
    PrimaryExprs* _PrimaryExprs;
    MultiplicativeExpr(): _PrimaryExpr(nullptr), _PrimaryExprs(nullptr){};
    ~MultiplicativeExpr();
    string LaTeX() const;
};
MultiplicativeExpr* MatchMultiplicativeExpr(Syntax &syn);

struct MultiplicativeExprs {
    int selector;  // 0, 1, 2
    Token* _OperationToken;
    MultiplicativeExpr* _MultiplicativeExpr;
    MultiplicativeExprs* _MultiplicativeExprs;
    MultiplicativeExprs(): _OperationToken(nullptr), _MultiplicativeExpr(nullptr), _MultiplicativeExprs(nullptr){};
    ~MultiplicativeExprs();
    string LaTeX() const;
};
MultiplicativeExprs* MatchMultiplicativeExprs(Syntax &syn);

struct PrimaryExpr {
    int selector;  // 0, 1, 2
    Token* _HeadToken;  // 0: "Num", 1: "Id", 2: "("
    OptionalActualParams* _OptionalActualParams;    // Only in 1
    Expression* _Expression;    // Only in 2
    Token* _RightParenthesisToken;  // Only in 2
    PrimaryExpr(): _HeadToken(nullptr), _OptionalActualParams(nullptr), _Expression(nullptr), _RightParenthesisToken(nullptr){};
    ~PrimaryExpr();
    string LaTeX() const;
};
PrimaryExpr* MatchPrimaryExpr(Syntax &syn);

struct PrimaryExprs {
    int selector;  // 0, 1, 2
    Token* _OperationToken;
    PrimaryExpr* _PrimaryExpr;
    PrimaryExprs* _PrimaryExprs;
    PrimaryExprs(): _OperationToken(nullptr), _PrimaryExpr(nullptr), _PrimaryExprs(nullptr){};
    ~PrimaryExprs();
    string LaTeX() const;
};
PrimaryExprs* MatchPrimaryExprs(Syntax &syn);

struct BoolExpression {
    Expression* _Expression;
    AfterBoolExpression* _AfterBoolExpression;
    BoolExpression(): _Expression(nullptr), _AfterBoolExpression(nullptr){};
    ~BoolExpression();
    string LaTeX() const;
};
BoolExpression* MatchBoolExpression(Syntax &syn);

struct AfterBoolExpression {
    int selector;  // 0, 1, 2, 3, 4, 5
    Token* _CompareToken;
    Expression* _Expression;
    AfterBoolExpression(): _CompareToken(nullptr), _Expression(nullptr){};
    ~AfterBoolExpression();
    string LaTeX() const;
};
AfterBoolExpression* MatchAfterBoolExpression(Syntax &syn);

struct OptionalActualParams {
    int selector;  // 0 or 1
    Token* _LeftParenthesisToken;
    ActualParams* _ActualParams;
    Token* _RightParenthesisToken;
    OptionalActualParams(): _LeftParenthesisToken(nullptr), _ActualParams(nullptr), _RightParenthesisToken(nullptr){};
    ~OptionalActualParams();
    string LaTeX() const;
};
OptionalActualParams* MatchOptionalActualParams(Syntax &syn);

struct ActualParams {
    int selector;  // 0 or 1
    Expression* _Expression;
    AfterActualParams* _AfterActualParams;
    ActualParams(): _Expression(nullptr), _AfterActualParams(nullptr){};
    ~ActualParams();
    string LaTeX() const;
};
ActualParams* MatchActualParams(Syntax &syn);

struct AfterActualParams {
    int selector;  // 0 or 1
    Token* _CommaToken;
    Expression* _Expression;
    AfterActualParams* _AfterActualParams;
    AfterActualParams(): _CommaToken(nullptr), _Expression(nullptr), _AfterActualParams(nullptr){};
    ~AfterActualParams();
    string LaTeX() const;
};
AfterActualParams* MatchAfterActualParams(Syntax &syn);

#pragma mark Formal generators of Terminals
// Formal generators of Terminals
Token* MatchToken(const int TokenType, Syntax &syn);
Token* MatchKeywordToken(const char* Keyword, Syntax &syn);

bool PeekMatchToken(const int TokenType, Syntax &syn);
bool PeekMatchKeywordToken(const char* Keyword, Syntax &syn);

#pragma mark Print utility
string PrintToken(const Token *tok);

#endif

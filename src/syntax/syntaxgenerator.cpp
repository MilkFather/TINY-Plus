#include "syntax/syntaxgenerator.h"
#include "lex/lexdef.h"
#include <string>

using namespace std;

#pragma mark Program
Program::~Program() {
    if (this->_MethodDecl != nullptr) delete this->_MethodDecl;
    if (this->_MethodDecls != nullptr) delete this->_MethodDecls;
}

string Program::LaTeX() const {
    string s;
    s = "[ Program " + _MethodDecl->LaTeX() + " " + _MethodDecls->LaTeX() + " ]";
    return s;
}

Program* MatchProgram(Syntax &syn) {
    Program* temp = new Program;
    if ((temp->_MethodDecl = MatchMethodDecl(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_MethodDecls = MatchMethodDecls(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark MethodDecl
MethodDecl::~MethodDecl() {
    if (this->_Type != nullptr) delete this->_Type;
    if (this->_OptionalMain != nullptr) delete this->_OptionalMain;
    if (this->_IdToken != nullptr) delete this->_IdToken;
    if (this->_LeftParenthesisToken != nullptr) delete this->_LeftParenthesisToken;
    if (this->_OptionalFormalParams != nullptr) delete this->_OptionalFormalParams;
    if (this->_RightParenthesisToken != nullptr) delete this->_RightParenthesisToken;
    if (this->_Block != nullptr) delete this->_Block;
}

string MethodDecl::LaTeX() const {
    string s;
    s = "[ MethodDecl " + _Type->LaTeX() + " " + _OptionalMain->LaTeX() + " " + PrintToken(_IdToken) + " " + PrintToken(_LeftParenthesisToken) + " " + _OptionalFormalParams->LaTeX() + " " + PrintToken(_RightParenthesisToken) + " " + _Block->LaTeX() + " ]";
    return s;
}

MethodDecl* MatchMethodDecl(Syntax &syn) {
    MethodDecl* temp = new MethodDecl;
    if ((temp->_Type = MatchType(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_OptionalMain = MatchOptionalMain(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_IdToken = MatchToken(TYPE_IDENTIFIER, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_LeftParenthesisToken = MatchToken(TYPE_LEFT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_OptionalFormalParams = MatchOptionalFormalParams(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_RightParenthesisToken = MatchToken(TYPE_RIGHT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_Block = MatchBlock(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark MethodDecls
MethodDecls::~MethodDecls() {
    if (this->_MethodDecl != nullptr) delete this->_MethodDecl;
    if (this->_MethodDecls != nullptr) delete this->_MethodDecls;
}

string MethodDecls::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ MethodDecls " + _MethodDecl->LaTeX() + " " + _MethodDecls->LaTeX() + " ]";
    } else {
        s = "[ MethodDecls [ $\\epsilon$ ] ]";
    }
    return s;
}

MethodDecls* MatchMethodDecls(Syntax &syn) {
    MethodDecls* temp = new MethodDecls;
    if (PeekMatchKeywordToken("INT", syn) || PeekMatchKeywordToken("REAL", syn)) {
        temp->selector = 0;
        if ((temp->_MethodDecl = MatchMethodDecl(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_MethodDecls = MatchMethodDecls(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_EOF, syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark OptionalMain
OptionalMain::~OptionalMain() {
    if (this->_MainToken != nullptr) delete this->_MainToken;
}

string OptionalMain::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ OptionalMain " + PrintToken(_MainToken) + " ]";
    } else {
        s = "[ OptionalMain [ $\\epsilon$ ] ]";
    }
    return s;
}

OptionalMain* MatchOptionalMain(Syntax &syn) {
    OptionalMain* temp = new OptionalMain;
    if (PeekMatchKeywordToken("MAIN", syn)) {
        temp->selector = 0;
        if ((temp->_MainToken = MatchKeywordToken("MAIN", syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_IDENTIFIER, syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark OptionalFormalParams
OptionalFormalParams::~OptionalFormalParams() {
    if (this->_FormalParams != nullptr) delete this->_FormalParams;
}

string OptionalFormalParams::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ OptionalFormalParams " + _FormalParams->LaTeX() + " ]";
    } else {
        s = "[ OptionalFormalParams [ $\\epsilon$ ] ]";
    }
    return s;
}

OptionalFormalParams* MatchOptionalFormalParams(Syntax &syn) {
    OptionalFormalParams* temp = new OptionalFormalParams;
    if (PeekMatchKeywordToken("INT", syn) || PeekMatchKeywordToken("REAL", syn)) {
        temp->selector = 0;
        if ((temp->_FormalParams = MatchFormalParams(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_RIGHT_PARENTHESIS, syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark FormalParams
FormalParams::~FormalParams() {
    if (this->_FormalParam != nullptr) delete this->_FormalParam;
    if (this->_AfterFormalParams != nullptr) delete this->_AfterFormalParams;
}

string FormalParams::LaTeX() const {
    string s;
    s = "[ FormalParams " + _FormalParam->LaTeX() + " " + _AfterFormalParams->LaTeX() + " ]";
    return s;
}

FormalParams* MatchFormalParams(Syntax &syn) {
    FormalParams* temp = new FormalParams;
    if ((temp->_FormalParam = MatchFormalParam(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_AfterFormalParams = MatchAfterFormalParams(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark FormalParam
FormalParam::~FormalParam() {
    if (this->_Type != nullptr) delete this->_Type;
    if (this->_IdToken != nullptr) delete this->_IdToken;
}

string FormalParam::LaTeX() const {
    string s;
    s = "[ FormalParam " + _Type->LaTeX() + " " + PrintToken(_IdToken) + " ]";
    return s;
}

FormalParam* MatchFormalParam(Syntax &syn) {
    FormalParam* temp = new FormalParam;
    if ((temp->_Type = MatchType(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_IdToken = MatchToken(TYPE_IDENTIFIER, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark AfterFormalParams
AfterFormalParams::~AfterFormalParams() {
    if (this->_CommaToken != nullptr) delete this->_CommaToken;
    if (this->_FormalParams != nullptr) delete this->_FormalParams;
}

string AfterFormalParams::LaTeX() const {
    string s;
    if (this->selector == 0) {
        s = "[ AfterFormalParams " + PrintToken(_CommaToken) + " " + _FormalParams->LaTeX() + " ]";
    } else {
        s = "[ AfterFormalParams [ $\\epsilon$ ] ]";
    }
    return s;
}

AfterFormalParams* MatchAfterFormalParams(Syntax &syn) {
    AfterFormalParams* temp = new AfterFormalParams;
    if (PeekMatchToken(TYPE_COMMA, syn)) {
        temp->selector = 0;
        if ((temp->_CommaToken = MatchToken(TYPE_COMMA, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_FormalParams = MatchFormalParams(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_RIGHT_PARENTHESIS, syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark Type
Type::~Type() {
    if (this->_TypeToken != nullptr) delete this->_TypeToken;
}

string Type::LaTeX() const {
    string s;
    s = "[ Type " + PrintToken(_TypeToken) + " ]";
    return s;
}

Type* MatchType(Syntax &syn) {
    Type* temp = new Type;
    if (PeekMatchKeywordToken("INT", syn)) {
        temp->selector = 0;
        if ((temp->_TypeToken = MatchKeywordToken("INT", syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("REAL", syn)) {
        temp->selector = 1;
        if ((temp->_TypeToken = MatchKeywordToken("REAL", syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark Block
Block::~Block() {
    if (this->_BeginToken != nullptr) delete this->_BeginToken;
    if (this->_Statements != nullptr) delete this->_Statements;
    if (this->_EndToken != nullptr) delete this->_EndToken;
}

string Block::LaTeX() const {
    string s;
    s = "[ Block " + PrintToken(_BeginToken) + " " + _Statements->LaTeX() + " " + PrintToken(_EndToken) + " ]";
    return s;
}

Block* MatchBlock(Syntax &syn) {
    Block* temp = new Block;
    if ((temp->_BeginToken = MatchKeywordToken("BEGIN", syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_Statements = MatchStatements(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_EndToken = MatchKeywordToken("END", syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark Statement
Statement::~Statement() {
    if (this->_Block != nullptr) delete this->_Block;
    if (this->_LocalVarDecl != nullptr) delete this->_LocalVarDecl;
    if (this->_AssignStmt != nullptr) delete this->_AssignStmt;
    if (this->_ReturnStmt != nullptr) delete this->_ReturnStmt;
    if (this->_IfStmt != nullptr) delete this->_IfStmt;
    if (this->_WriteStmt != nullptr) delete this->_WriteStmt;
    if (this->_ReadStmt != nullptr) delete this->_ReadStmt;
}

string Statement::LaTeX() const {
    string s;
    switch (selector) {
        case 0:
            s = "[ Statement " + _Block->LaTeX() + " ]";
            break;
        case 1:
            s = "[ Statement " + _LocalVarDecl->LaTeX() + " ]";
            break;
        case 2:
            s = "[ Statement " + _AssignStmt->LaTeX() + " ]";
            break;
        case 3:
            s = "[ Statement " + _ReturnStmt->LaTeX() + " ]";
            break;
        case 4:
            s = "[ Statement " + _IfStmt->LaTeX() + " ]";
            break;
        case 5:
            s = "[ Statement " + _WriteStmt->LaTeX() + " ]";
            break;
        case 6:
            s = "[ Statement " + _ReadStmt->LaTeX() + " ]";
            break;
        case 7:
            s = "[ Statement " + _WhileStmt->LaTeX() + " ]";
            break;
        default:
            break;
    }
    return s;
}

Statement* MatchStatement(Syntax &syn) {
    Statement* temp = new Statement;
    if (PeekMatchKeywordToken("BEGIN", syn)) {
        temp->selector = 0;
        if ((temp->_Block = MatchBlock(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("INT", syn) || PeekMatchKeywordToken("REAL", syn)) {
        temp->selector = 1;
        if ((temp->_LocalVarDecl = MatchLocalVarDecl(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_IDENTIFIER, syn)) {
        temp->selector = 2;
        if ((temp->_AssignStmt = MatchAssignStmt(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("RETURN", syn)) {
        temp->selector = 3;
        if ((temp->_ReturnStmt = MatchReturnStmt(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("IF", syn)) {
        temp->selector = 4;
        if ((temp->_IfStmt = MatchIfStmt(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("WRITE", syn)) {
        temp->selector = 5;
        if ((temp->_WriteStmt = MatchWriteStmt(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("READ", syn)) {
        temp->selector = 6;
        if ((temp->_ReadStmt = MatchReadStmt(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("WHILE", syn)) {
        temp->selector = 7;
        if ((temp->_WhileStmt = MatchWhileStmt(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark Statements
Statements::~Statements() {
    if (this->_Statement != nullptr) delete this->_Statement;
    if (this->_Statements != nullptr) delete this->_Statements;
}

string Statements::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ Statements " + _Statement->LaTeX() + " " + _Statements->LaTeX() + " ]";
    } else {
        s = "[ Statements [ $\\epsilon$ ] ]";
    }
    return s;
}

Statements* MatchStatements(Syntax &syn) {
    Statements* temp = new Statements;
    if (PeekMatchKeywordToken("BEGIN", syn) || PeekMatchKeywordToken("INT", syn) || PeekMatchKeywordToken("REAL", syn) || PeekMatchToken(TYPE_IDENTIFIER, syn) || PeekMatchKeywordToken("RETURN", syn) || PeekMatchKeywordToken("IF", syn) || PeekMatchKeywordToken("WRITE", syn) || PeekMatchKeywordToken("READ", syn) || PeekMatchKeywordToken("WHILE", syn)) {
        temp->selector = 0;
        if ((temp->_Statement = MatchStatement(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_Statements = MatchStatements(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("END", syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark LocalVarDecl
LocalVarDecl::~LocalVarDecl() {
    if (this->_TypeToken != nullptr) delete this->_TypeToken;
    if (this->_IdToken != nullptr) delete this->_IdToken;
    if (this->_SemicolonToken != nullptr) delete this->_SemicolonToken;
}

string LocalVarDecl::LaTeX() const {
    string s;
    s = "[ LocalVarDecl " + PrintToken(_TypeToken) + " " + PrintToken(_IdToken) + " " + PrintToken(_SemicolonToken) + " ]";
    return s;
}

LocalVarDecl* MatchLocalVarDecl(Syntax &syn) {
    LocalVarDecl* temp = new LocalVarDecl;
    if (PeekMatchKeywordToken("INT", syn)) {
        temp->selector = 0;
        if ((temp->_TypeToken = MatchKeywordToken("INT", syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("REAL", syn)) {
        temp->selector = 1;
        if ((temp->_TypeToken = MatchKeywordToken("REAL", syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    }
    if ((temp->_IdToken = MatchToken(TYPE_IDENTIFIER, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_SemicolonToken = MatchToken(TYPE_SEMICOLON, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark AssignStmt
AssignStmt::~AssignStmt() {
    if (this->_IdToken != nullptr) delete this->_IdToken;
    if (this->_AssignToken != nullptr) delete this->_AssignToken;
    if (this->_Expression != nullptr) delete this->_Expression;
    if (this->_SemicolonToken != nullptr) delete this->_SemicolonToken;
}

string AssignStmt::LaTeX() const {
    string s;
    s = "[ AssignStmt " + PrintToken(_IdToken) + " " + PrintToken(_AssignToken) + " " + _Expression->LaTeX() + " " + PrintToken(_SemicolonToken) + " ]";
    return s;
}

AssignStmt* MatchAssignStmt(Syntax &syn) {
    AssignStmt* temp = new AssignStmt;
    if ((temp->_IdToken = MatchToken(TYPE_IDENTIFIER, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_AssignToken = MatchToken(TYPE_ASSIGN, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_SemicolonToken = MatchToken(TYPE_SEMICOLON, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark ReturnStmt
ReturnStmt::~ReturnStmt() {
    if (this->_ReturnToken != nullptr) delete this->_ReturnToken;
    if (this->_Expression != nullptr) delete this->_Expression;
    if (this->_SemicolonToken != nullptr) delete this->_SemicolonToken;
}

string ReturnStmt::LaTeX() const {
    string s;
    s = "[ ReturnStmt " + PrintToken(_ReturnToken) + " " + _Expression->LaTeX() + " " + PrintToken(_SemicolonToken) + " ]";
    return s;
}

ReturnStmt* MatchReturnStmt(Syntax &syn) {
    ReturnStmt* temp = new ReturnStmt;
    if ((temp->_ReturnToken = MatchKeywordToken("RETURN", syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_SemicolonToken = MatchToken(TYPE_SEMICOLON, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark IfStmt
IfStmt::~IfStmt() {
    if (this->_IfToken != nullptr) delete this->_IfToken;
    if (this->_LeftParenthesisToken != nullptr) delete this->_LeftParenthesisToken;
    if (this->_BoolExpression != nullptr) delete this->_BoolExpression;
    if (this->_RightParenthesisToken != nullptr) delete this->_RightParenthesisToken;
    if (this->_Statement != nullptr) delete this->_Statement;
    if (this->_OptionalElseStmt != nullptr) delete this->_OptionalElseStmt;
}

string IfStmt::LaTeX() const {
    string s;
    s = "[ IfStmt " + PrintToken(_IfToken) + " " + PrintToken(_LeftParenthesisToken) + " " + _BoolExpression->LaTeX() + " " + PrintToken(_RightParenthesisToken) + " " + _Statement->LaTeX() + " " + _OptionalElseStmt->LaTeX() + " ]";
    return s;
}

IfStmt* MatchIfStmt(Syntax &syn) {
    IfStmt* temp = new IfStmt;
    if ((temp->_IfToken = MatchKeywordToken("IF", syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_LeftParenthesisToken = MatchToken(TYPE_LEFT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_BoolExpression = MatchBoolExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_RightParenthesisToken = MatchToken(TYPE_RIGHT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_Statement = MatchStatement(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_OptionalElseStmt = MatchOptionalElseStmt(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark OptionalElseStmt
OptionalElseStmt::~OptionalElseStmt() {
    if (this->_ElseToken != nullptr) delete this->_ElseToken;
    if (this->_Statement != nullptr) delete this->_Statement;
}

string OptionalElseStmt::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ OptionalElseStmt " + PrintToken(_ElseToken) + " " + _Statement->LaTeX() + " ]";
    } else {
        s = "[ OptionalElseStmt [ $\\epsilon$ ] ]";
    }
    return s;
}

OptionalElseStmt* MatchOptionalElseStmt(Syntax &syn) {
    OptionalElseStmt* temp = new OptionalElseStmt;
    if (PeekMatchKeywordToken("ELSE", syn)) {
        temp->selector = 0;
        if ((temp->_ElseToken = MatchKeywordToken("ELSE", syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_Statement = MatchStatement(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchKeywordToken("BEGIN", syn) || PeekMatchKeywordToken("INT", syn) || PeekMatchKeywordToken("REAL", syn) || PeekMatchToken(TYPE_IDENTIFIER, syn) || PeekMatchKeywordToken("RETURN", syn) || PeekMatchKeywordToken("IF", syn) || PeekMatchKeywordToken("WRITE", syn) || PeekMatchKeywordToken("READ", syn) || PeekMatchKeywordToken("END", syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark WriteStmt
WriteStmt::~WriteStmt() {
    if (this->_WriteToken != nullptr) delete this->_WriteToken;
    if (this->_LeftParenthesisToken != nullptr) delete this->_LeftParenthesisToken;
    if (this->_Expression != nullptr) delete this->_Expression;
    if (this->_CommaToken != nullptr) delete this->_CommaToken;
    if (this->_StringToken != nullptr) delete this->_StringToken;
    if (this->_RightParenthesisToken != nullptr) delete this->_RightParenthesisToken;
    if (this->_SemicolonToken != nullptr) delete this->_SemicolonToken;
}

string WriteStmt::LaTeX() const {
    string s;
    s = "[ WriteStmt " + PrintToken(_WriteToken) + " " + PrintToken(_LeftParenthesisToken) + " " + _Expression->LaTeX() + " " + PrintToken(_CommaToken) + " " + PrintToken(_StringToken) + " " + PrintToken(_RightParenthesisToken) + " " + PrintToken(_SemicolonToken) + " ]";
    return s;
}

WriteStmt* MatchWriteStmt(Syntax &syn) {
    WriteStmt* temp = new WriteStmt;
    if ((temp->_WriteToken = MatchKeywordToken("WRITE", syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_LeftParenthesisToken = MatchToken(TYPE_LEFT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_CommaToken = MatchToken(TYPE_COMMA, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_StringToken = MatchToken(TYPE_STRING, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_RightParenthesisToken = MatchToken(TYPE_RIGHT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_SemicolonToken = MatchToken(TYPE_SEMICOLON, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark ReadStmt
ReadStmt::~ReadStmt() {
    if (this->_WriteToken != nullptr) delete this->_WriteToken;
    if (this->_LeftParenthesisToken != nullptr) delete this->_LeftParenthesisToken;
    if (this->_IdToken != nullptr) delete this->_IdToken;
    if (this->_CommaToken != nullptr) delete this->_CommaToken;
    if (this->_StringToken != nullptr) delete this->_StringToken;
    if (this->_RightParenthesisToken != nullptr) delete this->_RightParenthesisToken;
    if (this->_SemicolonToken != nullptr) delete this->_SemicolonToken;
}

string ReadStmt::LaTeX() const {
    string s;
    s = "[ ReadStmt " + PrintToken(_WriteToken) + " " + PrintToken(_LeftParenthesisToken) + " " + PrintToken(_IdToken) + " " + PrintToken(_CommaToken) + " " + PrintToken(_StringToken) + " " + PrintToken(_RightParenthesisToken) + " " + PrintToken(_SemicolonToken) + " ]";
    return s;
}

ReadStmt* MatchReadStmt(Syntax &syn) {
    ReadStmt* temp = new ReadStmt;
    if ((temp->_WriteToken = MatchKeywordToken("READ", syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_LeftParenthesisToken = MatchToken(TYPE_LEFT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_IdToken = MatchToken(TYPE_IDENTIFIER, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_CommaToken = MatchToken(TYPE_COMMA, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_StringToken = MatchToken(TYPE_STRING, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_RightParenthesisToken = MatchToken(TYPE_RIGHT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_SemicolonToken = MatchToken(TYPE_SEMICOLON, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark WhileStmt
WhileStmt::~WhileStmt() {
    if (this->_WhileToken != nullptr) delete this->_WhileToken;
    if (this->_LeftParenthesisToken != nullptr) delete this->_LeftParenthesisToken;
    if (this->_BoolExpression != nullptr) delete this->_BoolExpression;
    if (this->_RightParenthesisToken != nullptr) delete this->_RightParenthesisToken;
    if (this->_Statement != nullptr) delete this->_Statement;
}

string WhileStmt::LaTeX() const {
    string s;
    s = "[ WhileStmt " + PrintToken(_WhileToken) + " " + PrintToken(_LeftParenthesisToken) + " " + _BoolExpression->LaTeX() + " " + PrintToken(_RightParenthesisToken) + " " + _Statement->LaTeX() + " ]";
    return s;
}

WhileStmt* MatchWhileStmt(Syntax &syn) {
    WhileStmt* temp = new WhileStmt;
    if ((temp->_WhileToken = MatchKeywordToken("WHILE", syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_LeftParenthesisToken = MatchToken(TYPE_LEFT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_BoolExpression = MatchBoolExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_RightParenthesisToken = MatchToken(TYPE_RIGHT_PARENTHESIS, syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_Statement = MatchStatement(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark Expression
Expression::~Expression() {
    if (this->_MultiplicativeExpr != nullptr) delete this->_MultiplicativeExpr;
    if (this->_MultiplicativeExprs != nullptr) delete this->_MultiplicativeExprs;
}

string Expression::LaTeX() const {
    string s;
    s = "[ Expression " + _MultiplicativeExpr->LaTeX() + " " + _MultiplicativeExprs->LaTeX() + " ]";
    return s;
}

Expression* MatchExpression(Syntax &syn) {
    Expression* temp = new Expression;
    if ((temp->_MultiplicativeExpr = MatchMultiplicativeExpr(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_MultiplicativeExprs = MatchMultiplicativeExprs(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark MultiplicativeExpr
MultiplicativeExpr::~MultiplicativeExpr() {
    if (this->_PrimaryExpr != nullptr) delete this->_PrimaryExpr;
    if (this->_PrimaryExprs != nullptr) delete this->_PrimaryExprs;
}

string MultiplicativeExpr::LaTeX() const {
    string s;
    s = "[ MultiplicativeExpr " + _PrimaryExpr->LaTeX() + " " + _PrimaryExprs->LaTeX() + " ]";
    return s;
}

MultiplicativeExpr* MatchMultiplicativeExpr(Syntax &syn) {
    MultiplicativeExpr* temp = new MultiplicativeExpr;
    if ((temp->_PrimaryExpr = MatchPrimaryExpr(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_PrimaryExprs = MatchPrimaryExprs(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark MultiplicativeExprs
MultiplicativeExprs::~MultiplicativeExprs() {
    if (this->_OperationToken != nullptr) delete this->_OperationToken;
    if (this->_MultiplicativeExpr != nullptr) delete this->_MultiplicativeExpr;
    if (this->_MultiplicativeExprs != nullptr) delete this->_MultiplicativeExprs;
}

string MultiplicativeExprs::LaTeX() const {
    string s;
    switch (selector) {
        case 0:
        case 1:
            s = "[ MultiplicativeExprs " + PrintToken(_OperationToken) + " " + _MultiplicativeExpr->LaTeX() + " " + _MultiplicativeExprs->LaTeX() + " ]";
            break;
        case 2:
            s = "[ MultiplicativeExprs [ $\\epsilon$ ] ]";
            break;
        default:
            break;
    }
    return s;
}

MultiplicativeExprs* MatchMultiplicativeExprs(Syntax &syn) {
    MultiplicativeExprs* temp = new MultiplicativeExprs;
    if (PeekMatchToken(TYPE_PLUS, syn)) {
        temp->selector = 0;
        if ((temp->_OperationToken = MatchToken(TYPE_PLUS, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_MultiplicativeExpr = MatchMultiplicativeExpr(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_MultiplicativeExprs = MatchMultiplicativeExprs(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_MINUS, syn)) {
        temp->selector = 1;
        if ((temp->_OperationToken = MatchToken(TYPE_MINUS, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_MultiplicativeExpr = MatchMultiplicativeExpr(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_MultiplicativeExprs = MatchMultiplicativeExprs(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_SEMICOLON, syn) || PeekMatchToken(TYPE_COMMA, syn) || PeekMatchToken(TYPE_RIGHT_PARENTHESIS, syn) || PeekMatchToken(TYPE_EQUAL, syn) || PeekMatchToken(TYPE_NOTEQUAL, syn) || PeekMatchToken(TYPE_LESS, syn) || PeekMatchToken(TYPE_LEQ, syn) || PeekMatchToken(TYPE_GREATER, syn) || PeekMatchToken(TYPE_GEQ, syn)) {
        temp->selector = 2;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark PrimaryExpr
PrimaryExpr::~PrimaryExpr() {
    if (this->_HeadToken != nullptr) delete this->_HeadToken;
    if (this->_OptionalActualParams != nullptr) delete this->_OptionalActualParams;
    if (this->_Expression != nullptr) delete this->_Expression;
    if (this->_RightParenthesisToken != nullptr) delete this->_RightParenthesisToken;
}

string PrimaryExpr::LaTeX() const {
    string s;
    switch (selector) {
        case 0:
            s = "[ PrimaryExpr " + PrintToken(_HeadToken) + " ]";
            break;
        case 1:
            s = "[ PrimaryExpr " + PrintToken(_HeadToken) + " " + _OptionalActualParams->LaTeX() + " ]";
            break;
        case 2:
            s = "[ PrimaryExpr " + PrintToken(_HeadToken) + " " + _Expression->LaTeX() + " " + PrintToken(_RightParenthesisToken) + " ]";
            break;
    }
    return s;
}

PrimaryExpr* MatchPrimaryExpr(Syntax &syn) {
    PrimaryExpr* temp = new PrimaryExpr;
    if (PeekMatchToken(TYPE_NUMBER, syn)) {
        temp->selector = 0;
        if ((temp->_HeadToken = MatchToken(TYPE_NUMBER, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_IDENTIFIER, syn)) {
        temp->selector = 1;
        if ((temp->_HeadToken = MatchToken(TYPE_IDENTIFIER, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_OptionalActualParams = MatchOptionalActualParams(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_LEFT_PARENTHESIS, syn)) {
        temp->selector = 2;
        if ((temp->_HeadToken = MatchToken(TYPE_LEFT_PARENTHESIS, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_RightParenthesisToken = MatchToken(TYPE_RIGHT_PARENTHESIS, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark PrimaryExprs
PrimaryExprs::~PrimaryExprs() {
    if (this->_OperationToken != nullptr) delete this->_OperationToken;
    if (this->_PrimaryExpr != nullptr) delete this->_PrimaryExpr;
    if (this->_PrimaryExprs != nullptr) delete this->_PrimaryExprs;
}

string PrimaryExprs::LaTeX() const {
    string s;
    switch (selector) {
        case 0:
        case 1:
            s = "[ PrimaryExprs " + PrintToken(_OperationToken) + " " + _PrimaryExpr->LaTeX() + " " + _PrimaryExprs->LaTeX() + " ]";
            break;
        case 2:
            s = "[ PrimaryExprs [ $\\epsilon$ ] ]";
            break;
        default:
            break;
    }
    return s;
}

PrimaryExprs* MatchPrimaryExprs(Syntax &syn) {
    PrimaryExprs* temp = new PrimaryExprs;
    if (PeekMatchToken(TYPE_MULTIPLY, syn)) {
        temp->selector = 0;
        if ((temp->_OperationToken = MatchToken(TYPE_MULTIPLY, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_PrimaryExpr = MatchPrimaryExpr(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_PrimaryExprs = MatchPrimaryExprs(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_DIVIDE, syn)) {
        temp->selector = 1;
        if ((temp->_OperationToken = MatchToken(TYPE_DIVIDE, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_PrimaryExpr = MatchPrimaryExpr(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_PrimaryExprs = MatchPrimaryExprs(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_PLUS, syn) || PeekMatchToken(TYPE_MINUS, syn) || PeekMatchToken(TYPE_SEMICOLON, syn) || PeekMatchToken(TYPE_COMMA, syn) || PeekMatchToken(TYPE_RIGHT_PARENTHESIS, syn) || PeekMatchToken(TYPE_EQUAL, syn) || PeekMatchToken(TYPE_NOTEQUAL, syn) || PeekMatchToken(TYPE_LESS, syn) || PeekMatchToken(TYPE_LEQ, syn) || PeekMatchToken(TYPE_GREATER, syn) || PeekMatchToken(TYPE_GEQ, syn)) {
        temp->selector = 2;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark BoolExpression
BoolExpression::~BoolExpression() {
    if (this->_Expression != nullptr) delete this->_Expression;
    if (this->_AfterBoolExpression != nullptr) delete this->_AfterBoolExpression;
}

string BoolExpression::LaTeX() const {
    string s;
    s = "[ BoolExpression " + _Expression->LaTeX() + " " + _AfterBoolExpression->LaTeX() + " ]";
    return s;
}

BoolExpression* MatchBoolExpression(Syntax &syn) {
    BoolExpression* temp = new BoolExpression;
    if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    if ((temp->_AfterBoolExpression = MatchAfterBoolExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark AfterBoolExpression
AfterBoolExpression::~AfterBoolExpression() {
    if (this->_CompareToken != nullptr) delete this->_CompareToken;
    if (this->_Expression != nullptr) delete this->_Expression;
}

string AfterBoolExpression::LaTeX() const {
    string s;
    s = "[ AfterBoolExpression " + PrintToken(_CompareToken) + " " + _Expression->LaTeX() + " ]";
    return s;
}

AfterBoolExpression* MatchAfterBoolExpression(Syntax &syn) {
    AfterBoolExpression* temp = new AfterBoolExpression;
    if (PeekMatchToken(TYPE_EQUAL, syn)) {
        temp->selector = 0;
        if ((temp->_CompareToken = MatchToken(TYPE_EQUAL, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_NOTEQUAL, syn)) {
        temp->selector = 1;
        if ((temp->_CompareToken = MatchToken(TYPE_NOTEQUAL, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_LESS, syn)) {
        temp->selector = 2;
        if ((temp->_CompareToken = MatchToken(TYPE_LESS, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_LEQ, syn)) {
        temp->selector = 3;
        if ((temp->_CompareToken = MatchToken(TYPE_LEQ, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_GREATER, syn)) {
        temp->selector = 4;
        if ((temp->_CompareToken = MatchToken(TYPE_GREATER, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_GEQ, syn)) {
        temp->selector = 5;
        if ((temp->_CompareToken = MatchToken(TYPE_GEQ, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    }
    if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark OptionalActualParams
OptionalActualParams::~OptionalActualParams() {
    if (this->_LeftParenthesisToken != nullptr) delete this->_LeftParenthesisToken;
    if (this->_ActualParams != nullptr) delete this->_ActualParams;
    if (this->_RightParenthesisToken != nullptr) delete this->_RightParenthesisToken;
}

string OptionalActualParams::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ OptionalActualParams " + PrintToken(_LeftParenthesisToken) + " " + _ActualParams->LaTeX() + " " + PrintToken(_RightParenthesisToken) + " ]";
    } else {
        s = "[ OptionalActualParams [ $\\epsilon$ ] ]";
    }
    return s;
}

OptionalActualParams* MatchOptionalActualParams(Syntax &syn) {
    OptionalActualParams* temp = new OptionalActualParams;
    if (PeekMatchToken(TYPE_LEFT_PARENTHESIS, syn)) {
        temp->selector = 0;
        if ((temp->_LeftParenthesisToken = MatchToken(TYPE_LEFT_PARENTHESIS, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_ActualParams = MatchActualParams(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_RightParenthesisToken = MatchToken(TYPE_RIGHT_PARENTHESIS, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_MULTIPLY, syn) || PeekMatchToken(TYPE_DIVIDE, syn) || PeekMatchToken(TYPE_PLUS, syn) || PeekMatchToken(TYPE_MINUS, syn) || PeekMatchToken(TYPE_SEMICOLON, syn) || PeekMatchToken(TYPE_COMMA, syn) || PeekMatchToken(TYPE_RIGHT_PARENTHESIS, syn) || PeekMatchToken(TYPE_EQUAL, syn) || PeekMatchToken(TYPE_NOTEQUAL, syn) || PeekMatchToken(TYPE_LESS, syn) || PeekMatchToken(TYPE_LEQ, syn) || PeekMatchToken(TYPE_GREATER, syn) || PeekMatchToken(TYPE_GEQ, syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark ActualParams
ActualParams::~ActualParams() {
    if (this->_Expression != nullptr) delete this->_Expression;
    if (this->_AfterActualParams != nullptr) delete this->_AfterActualParams;
}

string ActualParams::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ ActualParams " + _Expression->LaTeX() + " " + _AfterActualParams->LaTeX() + " ]";
    } else {
        s = "[ ActualParams [ $\\epsilon$ ] ]";
    }
    return s;
}

ActualParams* MatchActualParams(Syntax &syn) {
    ActualParams* temp = new ActualParams;
    if (PeekMatchToken(TYPE_NUMBER, syn) || PeekMatchToken(TYPE_IDENTIFIER, syn) || PeekMatchToken(TYPE_LEFT_PARENTHESIS, syn)) {
        temp->selector = 0;
        if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_AfterActualParams = MatchAfterActualParams(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_RIGHT_PARENTHESIS, syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark AfterActualParams
AfterActualParams::~AfterActualParams() {
    if (this->_CommaToken != nullptr) delete this->_CommaToken;
    if (this->_Expression != nullptr) delete this->_Expression;
    if (this->_AfterActualParams != nullptr) delete this->_AfterActualParams;
}

string AfterActualParams::LaTeX() const {
    string s;
    if (selector == 0) {
        s = "[ AfterActualParams " + PrintToken(_CommaToken) + " " + _Expression->LaTeX() + " " + _AfterActualParams->LaTeX() + " ]";
    } else {
        s = "[ AfterActualParams [ $\\epsilon$ ] ]";
    }
    return s;
}

AfterActualParams* MatchAfterActualParams(Syntax &syn) {
    AfterActualParams* temp = new AfterActualParams;
    if (PeekMatchToken(TYPE_COMMA, syn)) {
        temp->selector = 0;
        if ((temp->_CommaToken = MatchToken(TYPE_COMMA, syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_Expression = MatchExpression(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
        if ((temp->_AfterActualParams = MatchAfterActualParams(syn)) == nullptr) {
            delete temp;
            return nullptr;
        }
    } else if (PeekMatchToken(TYPE_RIGHT_PARENTHESIS, syn)) {
        temp->selector = 1;
    } else {
        delete temp;
        return nullptr;
    }
    return temp;
}

#pragma mark Miscellaneous
Token* MatchToken(const int TokenType, Syntax &syn) {
    if (PeekMatchToken(TokenType, syn)) {
        Token* temp = new Token;
        *temp = syn.PeekToken();
        syn.ConsumeToken();
        return temp;
    } else {
        return nullptr;
    }
}

Token* MatchKeywordToken(const char* Keyword, Syntax &syn) {
    if (PeekMatchKeywordToken(Keyword, syn)) {
        Token* temp = new Token;
        *temp = syn.PeekToken();
        syn.ConsumeToken();
        return temp;
    } else {
        return nullptr;
    }
}

bool PeekMatchToken(const int TokenType, Syntax &syn) {
    return syn.PeekToken().t_Kind == TokenType;
}

bool PeekMatchKeywordToken(const char* Keyword, Syntax &syn) {
    return syn.PeekToken().t_Kind == TYPE_KEYWORD && syn.PeekToken().t_Content == Keyword;
}

string PrintToken(const Token *tok) {
    string s = "[ ";
    switch (tok->t_Kind) {
        case TYPE_IDENTIFIER:
            s = s + "Id [{" + tok->t_Content + "}]";
            break;
        case TYPE_NUMBER:
            s = s + "Num [{" + tok->t_Content + "}]";
            break;
        case TYPE_STRING:
            s = s + "Str [{" + tok->t_Content + "}]";
            break;
        default:
            s = s + "{" + tok->t_Content + "}";
            break;
    }
    s = s + " ]";
    return s;
}

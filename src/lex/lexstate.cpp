#include "lex/lexstate.h"
#include "lex/lexdef.h"

int TerminatingStates[21] = {STATE_INIT, STATE_SEMICOLON_ACCEPT, STATE_COMMA_ACCEPT, STATE_LEFT_PARENTHESIS_ACCEPT, STATE_RIGHT_PARENTHESIS_ACCEPT, STATE_PLUS_ACCEPT, STATE_MINUS_ACCEPT, STATE_MULTIPLY_ACCEPT, STATE_DIVIDE_ACCEPT, STATE_COMMENT_ACCEPT, STATE_ASSIGN_ACCEPT, STATE_EQUAL_ACCEPT, STATE_NOTEQUAL_ACCEPT, STATE_IDENTIFIER_ACCEPT, STATE_NUMBER_INTEGER_ACCEPT, STATE_NUMBER_FRACTIONAL_ACCEPT, STATE_STRING_ACCEPT, STATE_GREATER_ACCEPT, STATE_GEQ_ACCEPT, STATE_LESS_ACCEPT, STATE_LEQ_ACCEPT};

// STATE_INIT
int State0(Lex &sender) {
    char c = sender.Peek();
    if (c == ' ' || c == '\t' || c == '\n' || c == '\0') {
        sender.Consume();
        sender.Clear();
        return STATE_INIT;
    } else if (c == ';') {
        return STATE_SEMICOLON_0;
    } else if (c == ',') {
        return STATE_COMMA_0;
    } else if (c == '(') {
        return STATE_LEFT_PARENTHESIS_0;
    } else if (c == ')') {
        return STATE_RIGHT_PARENTHESIS_0;
    } else if (c == '+') {
        return STATE_PLUS_0;
    } else if (c == '-') {
        return STATE_MINUS_0;
    } else if (c == '*') {
        return STATE_MULTIPLY_0;
    } else if (c == '/') {
        return STATE_DIVIDE_0;
    } else if (c == ':') {
        return STATE_ASSIGN_0;
    } else if (c == '=') {
        return STATE_EQUAL_0;
    } else if (c == '!') {
        return STATE_NOTEQUAL_0;
    } else if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
        return STATE_IDENTIFIER_0;
    } else if ('0' <= c && c <= '9') {
        return STATE_NUMBER_0;
    } else if (c == '\"') {
        return STATE_STRING_0;
    } else if (c == '<') {
        return STATE_LESS_0;
    } else if (c == '>') {
        return STATE_GREATER_0;
    } else if (c == EOF) {
        return STATE_INIT;
    } else {
        sender.Refuse();
        return STATE_UNKNOWN;
    }
} 

// STATE_SEMICOLON_0
int State1(Lex &sender) {
    sender.Consume();
    return STATE_SEMICOLON_ACCEPT;
}

// STATE_SEMICOLON_ACCEPT
int State2(Lex &sender) {
    sender.GenerateToken(TYPE_SEMICOLON);
    return STATE_INIT;
}

// STATE_COMMA_0
int State3(Lex &sender) {
    sender.Consume();
    return STATE_COMMA_ACCEPT;
}

// STATE_COMMA_ACCEPT
int State4(Lex &sender) {
    sender.GenerateToken(TYPE_COMMA);
    return STATE_INIT;
}

// STATE_LEFT_PARENTHESIS_0
int State5(Lex &sender) {
    sender.Consume();
    return STATE_LEFT_PARENTHESIS_ACCEPT;
}

// STATE_LEFT_PARENTHESIS_ACCEPT
int State6(Lex &sender) {
    sender.GenerateToken(TYPE_LEFT_PARENTHESIS);
    return STATE_INIT;
}

// STATE_RIGHT_PARENTHESIS_0
int State7(Lex &sender) {
    sender.Consume();
    return STATE_RIGHT_PARENTHESIS_ACCEPT;
}

// STATE_RIGHT_PARENTHESIS_ACCEPT
int State8(Lex &sender) {
    sender.GenerateToken(TYPE_RIGHT_PARENTHESIS);
    return STATE_INIT;
}

// STATE_PLUS_0
int State9(Lex &sender) {
    sender.Consume();
    return STATE_PLUS_ACCEPT;
}

// STATE_PLUS_ACCEPT
int State10(Lex &sender) {
    sender.GenerateToken(TYPE_PLUS);
    return STATE_INIT;
}

// STATE_MINUS_0
int State11(Lex &sender) {
    sender.Consume();
    return STATE_MINUS_ACCEPT;
}

// STATE_MINUS_ACCEPT
int State12(Lex &sender) {
    sender.GenerateToken(TYPE_MINUS);
    return STATE_INIT;
}

// STATE_MULTIPLY_0
int State13(Lex &sender) {
    sender.Consume();
    return STATE_MULTIPLY_ACCEPT;
}

// STATE_MULTIPLY_ACCEPT
int State14(Lex &sender) {
    sender.GenerateToken(TYPE_MULTIPLY);
    return STATE_INIT;
}

// STATE_DIVIDE_0
int State15(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '*') {
        return STATE_COMMENT_1;
    } else {
        return STATE_DIVIDE_ACCEPT;
    }
}

// STATE_DIVIDE_ACCEPT
int State16(Lex &sender) {
    sender.GenerateToken(TYPE_DIVIDE);
    return STATE_INIT;
}

// STATE_COMMENT_1
int State17(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '*') {
        return STATE_COMMENT_2;
    } else {
        sender.Revert('*');
        return STATE_DIVIDE_ACCEPT;
    }
}

// STATE_COMMENT_2
int State18(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '*') {
        return STATE_COMMENT_3;
    } else {
        return STATE_COMMENT_2;
    }
}

// STATE_COMMENT_3
int State19(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '*') {
        return STATE_COMMENT_4;
    } else {
        return STATE_COMMENT_2;
    }
}

// STATE_COMMENT_4
int State20(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '/') {
        return STATE_COMMENT_5;
    } else {
        return STATE_COMMENT_2;
    }
}

// STATE_COMMENT_5
int State21(Lex &sender) {
    sender.Consume();
    return STATE_COMMENT_ACCEPT;
}

// STATE_COMMENT_ACCEPT
int State22(Lex &sender) {
    sender.Clear();
    return STATE_INIT;
}

// STATE_ASSIGN_0
int State23(Lex &sender) {
    sender.Consume();
    if (sender.Peek() == '=') {
        return STATE_ASSIGN_1;
    } else {
        sender.Refuse();
        return STATE_UNKNOWN;
    }
}

// STATE_ASSIGN_1
int State24(Lex &sender) {
    sender.Consume();
    return STATE_ASSIGN_ACCEPT;
}

// STATE_ASSIGN_ACCEPT
int State25(Lex &sender) {
    sender.GenerateToken(TYPE_ASSIGN);
    return STATE_INIT;
}

// STATE_EQUAL_0
int State26(Lex &sender) {
    sender.Consume();
    if (sender.Peek() == '=') {
        return STATE_EQUAL_1;
    } else {
        sender.Refuse();
        return STATE_UNKNOWN;
    }
}

// STATE_EQUAL_1
int State27(Lex &sender) {
    sender.Consume();
    return STATE_EQUAL_ACCEPT;
}

// STATE_EQUAL_ACCEPT
int State28(Lex &sender) {
    sender.GenerateToken(TYPE_EQUAL);
    return STATE_INIT;
}

// STATE_NOTEQUAL_0
int State29(Lex &sender) {
    sender.Consume();
    if (sender.Peek() == '=') {
        return STATE_NOTEQUAL_1;
    } else {
        sender.Refuse();
        return STATE_UNKNOWN;
    }
}

// STATE_NOTEQUAL_1
int State30(Lex &sender) {
    sender.Consume();
    return STATE_NOTEQUAL_ACCEPT;
}

// STATE_NOTEQUAL_ACCEPT
int State31(Lex &sender) {
    sender.GenerateToken(TYPE_NOTEQUAL);
    return STATE_INIT;
}

// STATE_IDENTIFIER_0
int State32(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
        return STATE_IDENTIFIER_0;
    } else {
        return STATE_IDENTIFIER_ACCEPT;
    }
}

// STATE_IDENTIFIER_ACCEPT
int State33(Lex &sender) {
    sender.GenerateToken(TYPE_IDENTIFIER);
    return STATE_INIT;
}

// STATE_NUMBER_0
int State34(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if ('0' <= c && c <= '9') {
        return STATE_NUMBER_0;
    } else if (c == '.') {
        return STATE_NUMBER_1;
    } else {
        return STATE_NUMBER_INTEGER_ACCEPT;
    }
}

// STATE_NUMBER_INTEGER_ACCEPT
int State35(Lex &sender) {
    sender.GenerateToken(TYPE_NUMBER);
    return STATE_INIT;
}

// STATE_NUMBER_1
int State36(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if ('0' <= c && c <= '9') {
        return STATE_NUMBER_2;
    } else {
        sender.Refuse();
        return STATE_UNKNOWN;
    }
}

// STATE_NUMBER_2
int State37(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if ('0' <= c && c <= '9') {
        return STATE_NUMBER_2;
    } else {
        return STATE_NUMBER_FRACTIONAL_ACCEPT;
    }
}

// STATE_NUMBER_FRACTIONAL_ACCEPT
int State38(Lex &sender) {
    sender.GenerateToken(TYPE_NUMBER);
    return STATE_INIT;
}

// STATE_STRING_0
int State39(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '\\') {
        return STATE_STRING_1;
    } else if (c == '\n') {
        sender.Refuse();
        return STATE_UNKNOWN;
    } else if (c == '\"') {
        return STATE_STRING_2;
    } else {
        return STATE_STRING_0;
    }
}

// STATE_STRING_1
int State40(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '\"' || c == '\'' || c == '?' || c == '\\' || c == 'a' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == 'v' || c == '0') {
        return STATE_STRING_0;
    } else {
        sender.Refuse();
        return STATE_UNKNOWN;
    }
}

// STATE_STRING_2
int State41(Lex &sender) {
    sender.Consume();
    return STATE_STRING_ACCEPT;
}

// STATE_STRING_ACCEPT
int State42(Lex &sender) {
    sender.GenerateToken(TYPE_STRING);
    return STATE_INIT;
}

// STATE_LESS_0
int State43(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '=') {
        return STATE_LEQ_1;
    } else {
        return STATE_LESS_ACCEPT;
    }
}

// STATE_LESS_ACCEPT
int State44(Lex &sender) {
    sender.GenerateToken(TYPE_LESS);
    return STATE_INIT;
}

// STATE_LEQ_1
int State45(Lex &sender) {
    sender.Consume();
    return STATE_LEQ_ACCEPT;
}

// STATE_LEQ_ACCEPT
int State46(Lex &sender) {
    sender.GenerateToken(TYPE_LEQ);
    return STATE_INIT;
}

// STATE_GREATER_0
int State47(Lex &sender) {
    sender.Consume();
    char c = sender.Peek();
    if (c == '=') {
        return STATE_GEQ_1;
    } else {
        return STATE_GREATER_ACCEPT;
    }
}

// STATE_GREATER_ACCEPT
int State48(Lex &sender) {
    sender.GenerateToken(TYPE_GREATER);
    return STATE_INIT;
}

// STATE_GEQ_1
int State49(Lex &sender) {
    sender.Consume();
    return STATE_GEQ_ACCEPT;
}

// STATE_GEQ_ACCEPT
int State50(Lex &sender) {
    sender.GenerateToken(TYPE_GEQ);
    return STATE_INIT;
}

int (*StateMachine[51]) (Lex &sender) = {
    State0, State1, State2, State3, State4, State5, State6, State7, State8, State9,
    State10, State11, State12, State13, State14, State15, State16, State17, State18, State19,
    State20, State21, State22, State23, State24, State25, State26, State27, State28, State29,
    State30, State31, State32, State33, State34, State35, State36, State37, State38, State39,
    State40, State41, State42, State43, State44, State45, State46, State47, State48, State49,
    State50
};
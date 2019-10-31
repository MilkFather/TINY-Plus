#ifndef __TINY_LEXDEF_H__
#define __TINY_LEXDEF_H__

#define TYPE_UNKNOWN                -1      // Unknown, initialized as this
#define TYPE_COMMENT                -2      // Comment, should not output to syntax parser
#define TYPE_EOF                    -100    // End of file

#define TYPE_KEYWORD                0       // IF ELSE WRITE READ RETURN BEGIN END MAIN INT REAL WHILE
#define TYPE_SEMICOLON              1       // ;
#define TYPE_COMMA                  2       // ,
#define TYPE_LEFT_PARENTHESIS       3       // (
#define TYPE_RIGHT_PARENTHESIS      4       // )
#define TYPE_PLUS                   5       // +
#define TYPE_MINUS                  6       // -
#define TYPE_MULTIPLY               7       // *
#define TYPE_DIVIDE                 8       // /
#define TYPE_ASSIGN                 9       // :=
#define TYPE_EQUAL                  10      // ==
#define TYPE_NOTEQUAL               11      // !=
#define TYPE_IDENTIFIER             12      // [a-zA-Z]([0-9a-zA-Z])*, except for keywords
#define TYPE_NUMBER                 13      // ([0-9])* | ([0-9])*.([0-9])([0-9])*
#define TYPE_STRING                 14      // ""
#define TYPE_GREATER                15      // >
#define TYPE_LESS                   16      // <
#define TYPE_GEQ                    17      // >=
#define TYPE_LEQ                    18      // <=

#define STATE_UNKNOWN                           -1
#define STATE_INIT                              0
#define STATE_SEMICOLON_0                       1
#define STATE_SEMICOLON_ACCEPT                  2
#define STATE_COMMA_0                           3
#define STATE_COMMA_ACCEPT                      4
#define STATE_LEFT_PARENTHESIS_0                5
#define STATE_LEFT_PARENTHESIS_ACCEPT           6
#define STATE_RIGHT_PARENTHESIS_0               7
#define STATE_RIGHT_PARENTHESIS_ACCEPT          8
#define STATE_PLUS_0                            9
#define STATE_PLUS_ACCEPT                       10
#define STATE_MINUS_0                           11
#define STATE_MINUS_ACCEPT                      12
#define STATE_MULTIPLY_0                        13
#define STATE_MULTIPLY_ACCEPT                   14
#define STATE_DIVIDE_0                          15
#define STATE_DIVIDE_ACCEPT                     16
#define STATE_COMMENT_1                         17
#define STATE_COMMENT_2                         18
#define STATE_COMMENT_3                         19
#define STATE_COMMENT_4                         20
#define STATE_COMMENT_5                         21
#define STATE_COMMENT_ACCEPT                    22
#define STATE_ASSIGN_0                          23
#define STATE_ASSIGN_1                          24
#define STATE_ASSIGN_ACCEPT                     25
#define STATE_EQUAL_0                           26
#define STATE_EQUAL_1                           27
#define STATE_EQUAL_ACCEPT                      28
#define STATE_NOTEQUAL_0                        29
#define STATE_NOTEQUAL_1                        30
#define STATE_NOTEQUAL_ACCEPT                   31
#define STATE_IDENTIFIER_0                      32
#define STATE_IDENTIFIER_ACCEPT                 33
#define STATE_NUMBER_0                          34
#define STATE_NUMBER_INTEGER_ACCEPT             35
#define STATE_NUMBER_1                          36
#define STATE_NUMBER_2                          37
#define STATE_NUMBER_FRACTIONAL_ACCEPT          38
#define STATE_STRING_0                          39
#define STATE_STRING_1                          40
#define STATE_STRING_2                          41
#define STATE_STRING_ACCEPT                     42
#define STATE_LESS_0                            43
#define STATE_LESS_ACCEPT                       44
#define STATE_LEQ_1                             45
#define STATE_LEQ_ACCEPT                        46
#define STATE_GREATER_0                         47
#define STATE_GREATER_ACCEPT                    48
#define STATE_GEQ_1                             49
#define STATE_GEQ_ACCEPT                        50

#endif
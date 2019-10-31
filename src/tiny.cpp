#include <exception>
#include <cstdio>
#include "tinyexception.h"
#include "lex/lexical.h"
#include "syntax/syntax.h"

#define bold(s) ("\033[1m" s "\033[0m")
#define redbold(s) ("\033[1;31m" s "\033[0m")
#define greenbold(s) ("\033[1;32m" s "\033[0m")

using namespace std;

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf(redbold("No input file.\n"));
        exit(-1);
    }
    try {
        Lex lex(argv[1]);
        Syntax syntax;
        syntax.AssignLex(&lex);
        syntax.Parse();
        printf("%s\n", syntax.LaTeX().c_str());
    } catch (const LexicalException &e) {
        printf("%s: %s\n", redbold("Lexical Error"), e.what());
        exit(-2);
    } catch (const SyntaxException &e) {
        printf("%s: %s\n", redbold("Syntax Error"), e.what());
        exit(-3);
    } catch (const exception &e) {
        printf("%s: %s\n", redbold("General Error"), e.what());
        exit(-4);
    }
    printf(greenbold("Pass.\n"));
    return 0;
}
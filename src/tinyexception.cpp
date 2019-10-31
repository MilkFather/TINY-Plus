#include "tinyexception.h"
#include <string>
#include <cstring>

using namespace std;

IOException::IOException() {
    this->msg = new char[50];
    strcpy(this->msg, "No file open");
}

IOException::IOException(string _fn, const char* _strerr) {
    this->msg = new char[_fn.length() + strlen(_strerr) + 100];
    sprintf(this->msg, "IO exception with %s, %s", _fn.c_str(), _strerr);
}

IOException::~IOException() {
    delete [] this->msg;
}

const char* IOException::what() const noexcept {
    return this->msg;
}

string EscapeCharacter(const char c) {
    string s;
    if (c == '\n') s = "NEWLINE";
    else if (c == '\t') s = "TAB";
    else if (c == ' ') s = "SPACE";
    else if (c == '\0') s = "NUL";
    else if (c == EOF) s = "End of File";
    else s = c;
    return s;
}

LexicalException::LexicalException(string _fn, int _line, int _col, char _c) {
    this->msg = new char[_fn.length() + 150];
    sprintf(this->msg, "Unexpected \"%s\" in file \"%s\", at line %d column %d", EscapeCharacter(_c).c_str(), _fn.c_str(), _line, _col);
}

LexicalException::~LexicalException() {
    delete [] this->msg;
}

const char* LexicalException::what() const noexcept {
    return this->msg;
}  

SyntaxException::SyntaxException(string _fn, int _line, int _col, string _tokcontent) {
    this->msg = new char[_fn.length() + 150 + _tokcontent.length()];
    sprintf(this->msg, "Unexpected \"%s\" in file \"%s\", at line %d column %d", _tokcontent.c_str(), _fn.c_str(), _line, _col);
}

SyntaxException::~SyntaxException() {
    delete [] this->msg;
}

const char* SyntaxException::what() const noexcept {
    return this->msg;
}
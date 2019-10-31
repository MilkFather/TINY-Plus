#ifndef __TINY_EXCEPTION_H__
#define __TINY_EXCEPTION_H__

#include <string>
#include <exception>

using namespace std;

class IOException: public exception {
private:
    char* msg;
public:
    IOException();
    IOException(string _fn, const char* _strerr);
    ~IOException();
    const char* what() const noexcept;
};

class LexicalException: public exception {
private:
    char *msg;
public:
    LexicalException(string _fn, int _line, int _col, char _c);
    ~LexicalException();
    const char* what() const noexcept;
};

class SyntaxException: public exception {
private:
    char *msg;
public:
    SyntaxException(string _fn, int _line, int _col, string _tokcontent);
    ~SyntaxException();
    const char* what() const noexcept;
};


#endif
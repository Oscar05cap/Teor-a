#ifndef AFD_EXCEPTIONS_H
#define AFD_EXCEPTIONS_H

#include <stdexcept>

class InvalidStateException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidSymbolException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class NonDeterministicException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class IncompleteAutomatonException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidFormatException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

#endif

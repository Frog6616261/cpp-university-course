#include <cctype>
#include <stdexcept>
#include <string>

#pragma once

class LexerError : public std::runtime_error {
public:
    explicit LexerError(const std::string& message)
        : std::runtime_error(message) {}
};

class ParserError : public std::runtime_error {
public:
    explicit ParserError(const std::string& message)
        : std::runtime_error(message) {}
};

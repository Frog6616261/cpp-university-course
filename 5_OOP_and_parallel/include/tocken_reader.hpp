#pragma once

#include <string>
#include <vector>

#include "tocken.hpp"

class TokenReader {
private:
    std::string source;
    std::size_t position = 0;

    int line = 1;
    int column = 1;

public:
    explicit TokenReader(std::string sourceCode);

    std::vector<Token> readAllTokens();

private:
    bool isAtEnd() const;

    char peek() const;
    char peekNext() const;
    char advance();

    void skipWhitespace();

    Token readIdentifierOrKeyword();
    Token readNumber();
    Token readString();
};
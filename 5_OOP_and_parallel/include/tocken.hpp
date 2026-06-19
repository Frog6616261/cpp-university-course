#include <cctype>
#include <string>


#pragma once
enum class TokenType {
    KeywordStart,
    KeywordEnd,
    KeywordPrint,
    KeywordFilePrint,
    KeywordCalc,
    KeywordLoop,

    Identifier,
    Number,
    String,

    Plus,
    Minus,
    Star,
    Slash,

    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,

    Semicolon,
    Comma,

    EndOfFile
};

struct Token {
    TokenType type;
    std::string text;
    int line;
    int column;
};

std::string tokenTypeToString(TokenType type);


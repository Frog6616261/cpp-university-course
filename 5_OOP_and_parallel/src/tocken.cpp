#include "tocken.hpp"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KeywordStart:
            return "KeywordStart";

        case TokenType::KeywordEnd:
            return "KeywordEnd";

        case TokenType::KeywordPrint:
            return "KeywordPrint";

        case TokenType::KeywordFilePrint:
            return "KeywordFilePrint";

        case TokenType::KeywordCalc:
            return "KeywordCalc";

        case TokenType::KeywordLoop:
            return "KeywordLoop";

        case TokenType::Identifier:
            return "Identifier";

        case TokenType::Number:
            return "Number";

        case TokenType::String:
            return "String";

        case TokenType::Plus:
            return "Plus";

        case TokenType::Minus:
            return "Minus";

        case TokenType::Star:
            return "Star";

        case TokenType::Slash:
            return "Slash";

        case TokenType::LeftParen:
            return "LeftParen";

        case TokenType::RightParen:
            return "RightParen";

        case TokenType::LeftBrace:
            return "LeftBrace";

        case TokenType::RightBrace:
            return "RightBrace";

        case TokenType::Semicolon:
            return "Semicolon";

        case TokenType::Comma:
            return "Comma";

        case TokenType::EndOfFile:
            return "EndOfFile";
    }

    return "Unknown";
};
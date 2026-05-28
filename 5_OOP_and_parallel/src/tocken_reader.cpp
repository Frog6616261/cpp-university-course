#include "tocken_reader.hpp"

#include <cctype>
#include <utility>

#include "exceptions.hpp"

TokenReader::TokenReader(std::string sourceCode)
    : source(std::move(sourceCode)) {}

std::vector<Token> TokenReader::readAllTokens() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();

        if (isAtEnd()) {
            break;
        }

        char current = peek();

        if (std::isalpha(static_cast<unsigned char>(current)) || current == '_') {
            tokens.push_back(readIdentifierOrKeyword());
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(current)) || current == '.') {
            tokens.push_back(readNumber());
            continue;
        }

        if (current == '"') {
            tokens.push_back(readString());
            continue;
        }

        int tokenLine = line;
        int tokenColumn = column;

        switch (current) {
            case '+':
                advance();
                tokens.push_back({TokenType::Plus, "+", tokenLine, tokenColumn});
                break;

            case '-':
                advance();
                tokens.push_back({TokenType::Minus, "-", tokenLine, tokenColumn});
                break;

            case '*':
                advance();
                tokens.push_back({TokenType::Star, "*", tokenLine, tokenColumn});
                break;

            case '/':
                advance();
                tokens.push_back({TokenType::Slash, "/", tokenLine, tokenColumn});
                break;

            case '(':
                advance();
                tokens.push_back({TokenType::LeftParen, "(", tokenLine, tokenColumn});
                break;

            case ')':
                advance();
                tokens.push_back({TokenType::RightParen, ")", tokenLine, tokenColumn});
                break;

            case '{':
                advance();
                tokens.push_back({TokenType::LeftBrace, "{", tokenLine, tokenColumn});
                break;

            case '}':
                advance();
                tokens.push_back({TokenType::RightBrace, "}", tokenLine, tokenColumn});
                break;

            case ';':
                advance();
                tokens.push_back({TokenType::Semicolon, ";", tokenLine, tokenColumn});
                break;

            case ',':
                advance();
                tokens.push_back({TokenType::Comma, ",", tokenLine, tokenColumn});
                break;

            default:
                throw LexerError(
                    "Неизвестный символ '" +
                    std::string(1, current) +
                    "' в строке " +
                    std::to_string(line) +
                    ", колонка " +
                    std::to_string(column)
                );
        }
    }

    tokens.push_back({TokenType::EndOfFile, "", line, column});

    return tokens;
}

bool TokenReader::isAtEnd() const {
    return position >= source.size();
}

char TokenReader::peek() const {
    if (isAtEnd()) {
        return '\0';
    }

    return source[position];
}

char TokenReader::peekNext() const {
    if (position + 1 >= source.size()) {
        return '\0';
    }

    return source[position + 1];
}

char TokenReader::advance() {
    char current = source[position++];

    if (current == '\n') {
        ++line;
        column = 1;
    } else {
        ++column;
    }

    return current;
}

void TokenReader::skipWhitespace() {
    while (!isAtEnd()) {
        char current = peek();

        if (
            current == ' ' ||
            current == '\t' ||
            current == '\r' ||
            current == '\n'
        ) {
            advance();
        } else {
            break;
        }
    }
}

Token TokenReader::readIdentifierOrKeyword() {
    int tokenLine = line;
    int tokenColumn = column;

    std::string text;

    while (
        !isAtEnd() &&
        (
            std::isalnum(static_cast<unsigned char>(peek())) ||
            peek() == '_'
        )
    ) {
        text += advance();
    }

    if (text == "start") {
        return {TokenType::KeywordStart, text, tokenLine, tokenColumn};
    }

    if (text == "end") {
        return {TokenType::KeywordEnd, text, tokenLine, tokenColumn};
    }

    if (text == "print") {
        return {TokenType::KeywordPrint, text, tokenLine, tokenColumn};
    }

    if (text == "file_print") {
        return {TokenType::KeywordFilePrint, text, tokenLine, tokenColumn};
    }

    if (text == "calc") {
        return {TokenType::KeywordCalc, text, tokenLine, tokenColumn};
    }

    if (text == "loop") {
        return {TokenType::KeywordLoop, text, tokenLine, tokenColumn};
    }

    return {TokenType::Identifier, text, tokenLine, tokenColumn};
}

Token TokenReader::readNumber() {
    int tokenLine = line;
    int tokenColumn = column;

    std::string text;
    bool hasDot = false;

    if (peek() == '.' && !std::isdigit(static_cast<unsigned char>(peekNext()))) {
        throw LexerError(
            "Некорректное число в строке " +
            std::to_string(line) +
            ", колонка " +
            std::to_string(column)
        );
    }

    while (
        !isAtEnd() &&
        (
            std::isdigit(static_cast<unsigned char>(peek())) ||
            peek() == '.'
        )
    ) {
        if (peek() == '.') {
            if (hasDot) {
                throw LexerError(
                    "В числе не может быть больше одной точки. Строка " +
                    std::to_string(line) +
                    ", колонка " +
                    std::to_string(column)
                );
            }

            hasDot = true;
        }

        text += advance();
    }

    return {TokenType::Number, text, tokenLine, tokenColumn};
}

Token TokenReader::readString() {
    int tokenLine = line;
    int tokenColumn = column;

    advance();

    std::string text;

    while (!isAtEnd()) {
        char current = advance();

        if (current == '"') {
            return {TokenType::String, text, tokenLine, tokenColumn};
        }

        if (current == '\n') {
            throw LexerError(
                "Строка в кавычках не закрыта. Начало строки: " +
                std::to_string(tokenLine) +
                ", колонка " +
                std::to_string(tokenColumn)
            );
        }

        if (current == '\\') {
            if (isAtEnd()) {
                break;
            }

            char escaped = advance();

            switch (escaped) {
                case 'n':
                    text += '\n';
                    break;

                case 't':
                    text += '\t';
                    break;

                case '"':
                    text += '"';
                    break;

                case '\\':
                    text += '\\';
                    break;

                default:
                    text += escaped;
                    break;
            }
        } else {
            text += current;
        }
    }

    throw LexerError(
        "Строка в кавычках не закрыта. Начало строки: " +
        std::to_string(tokenLine) +
        ", колонка " +
        std::to_string(tokenColumn)
    );
}
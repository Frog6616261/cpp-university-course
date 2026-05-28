#include "parcer.hpp"

#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens) {}

std::vector<std::unique_ptr<Command>> Parser::parseProgram() {
    consume(
        TokenType::KeywordStart,
        "Программа должна начинаться с ключевого слова start"
    );

    consume(
        TokenType::Semicolon,
        "После start ожидался символ ';'"
    );

    std::vector<std::unique_ptr<Command>> commands = parseCommandList();

    consume(
        TokenType::KeywordEnd,
        "Ожидалось ключевое слово end"
    );

    consume(
        TokenType::Semicolon,
        "После end ожидался символ ';'"
    );

    consume(
        TokenType::EndOfFile,
        "После end; не должно быть лишних токенов"
    );

    return commands;
}

const Token& Parser::peek() const {
    return tokens[position];
}

const Token& Parser::previous() const {
    return tokens[position - 1];
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::EndOfFile;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) {
        return type == TokenType::EndOfFile;
    }

    return peek().type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        ++position;
        return true;
    }

    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        return tokens[position++];
    }

    throw error(message);
}

ParserError Parser::error(const std::string& message) const {
    const Token& token = peek();

    return ParserError(
        message +
        ". Найден токен '" +
        token.text +
        "' типа " +
        tokenTypeToString(token.type) +
        " в строке " +
        std::to_string(token.line) +
        ", колонка " +
        std::to_string(token.column)
    );
}

std::vector<std::unique_ptr<Command>> Parser::parseCommandList() {
    std::vector<std::unique_ptr<Command>> commands;

    while (
        !check(TokenType::KeywordEnd) &&
        !check(TokenType::RightBrace) &&
        !check(TokenType::EndOfFile)
    ) {
        std::unique_ptr<Command> command = parseCommand();

        commands.push_back(std::move(command));

        consume(
            TokenType::Semicolon,
            "После команды ожидался символ ';'"
        );
    }

    return commands;
}

std::unique_ptr<Command> Parser::parseCommand() {
    if (match(TokenType::KeywordPrint)) {
        return parsePrintCommand();
    }

    if (match(TokenType::KeywordFilePrint)) {
        return parseFilePrintCommand();
    }

    if (match(TokenType::KeywordCalc)) {
        return parseCalcCommand();
    }

    if (match(TokenType::KeywordLoop)) {
        return parseLoopCommand();
    }

    throw error("Ожидалась команда: print, file_print, calc или loop");
}

std::unique_ptr<Command> Parser::parsePrintCommand() {
    consume(
        TokenType::LeftParen,
        "После print ожидался символ '('"
    );

    PrintableValue value = parsePrintableArgument();

    consume(
        TokenType::RightParen,
        "После аргумента print ожидался символ ')'"
    );

    return std::make_unique<PrintCommand>(
        std::move(value)
    );
}

std::unique_ptr<Command> Parser::parseFilePrintCommand() {
    consume(
        TokenType::LeftParen,
        "После file_print ожидался символ '('"
    );

    Token filenameToken = consume(
        TokenType::String,
        "Первый аргумент file_print должен быть строкой с именем файла"
    );

    consume(
        TokenType::Comma,
        "После имени файла в file_print ожидалась запятая ','"
    );

    PrintableValue value = parsePrintableArgument();

    consume(
        TokenType::RightParen,
        "После аргументов file_print ожидался символ ')'"
    );

    return std::make_unique<FilePrintCommand>(
        filenameToken.text,
        std::move(value)
    );
}

std::unique_ptr<Command> Parser::parseCalcCommand() {
    std::unique_ptr<Expression> expression = parseSimpleExpression(true);

    return std::make_unique<CalcCommand>(
        std::move(expression)
    );
}

std::unique_ptr<Command> Parser::parseLoopCommand() {
    consume(
        TokenType::LeftParen,
        "После loop ожидался символ '('"
    );

    Token countToken = consume(
        TokenType::Number,
        "В loop ожидалось число повторений"
    );

    int count = parseLoopCount(countToken);

    consume(
        TokenType::RightParen,
        "После количества повторений loop ожидался символ ')'"
    );

    consume(
        TokenType::LeftBrace,
        "После loop(...) ожидался символ '{'"
    );

    std::vector<std::unique_ptr<Command>> body = parseCommandList();

    consume(
        TokenType::RightBrace,
        "После тела loop ожидался символ '}'"
    );

    return std::make_unique<LoopCommand>(
        count,
        std::move(body)
    );
}

PrintableValue Parser::parsePrintableArgument() {
    if (check(TokenType::String)) {
        Token stringToken = consume(
            TokenType::String,
            "Ожидалась строка"
        );

        return PrintableValue::fromString(stringToken.text);
    }

    std::unique_ptr<Expression> expression = parseSimpleExpression(false);

    return PrintableValue::fromExpression(
        std::move(expression)
    );
}

std::unique_ptr<Expression> Parser::parseSimpleExpression(
    bool requireBinaryOperation
) {
    Token leftToken = consume(
        TokenType::Number,
        "В выражении ожидалось число"
    );

    double leftValue = std::stod(leftToken.text);

    std::unique_ptr<Expression> leftExpression =
        std::make_unique<NumberExpression>(leftValue);

    if (
        check(TokenType::Plus) ||
        check(TokenType::Minus) ||
        check(TokenType::Star) ||
        check(TokenType::Slash)
    ) {
        ArithmeticOperation operation = parseArithmeticOperator();

        Token rightToken = consume(
            TokenType::Number,
            "После арифметического оператора ожидалось число"
        );

        double rightValue = std::stod(rightToken.text);

        std::unique_ptr<Expression> rightExpression =
            std::make_unique<NumberExpression>(rightValue);

        return std::make_unique<BinaryExpression>(
            std::move(leftExpression),
            operation,
            std::move(rightExpression)
        );
    }

    if (requireBinaryOperation) {
        throw error("В calc ожидалось выражение вида: число оператор число");
    }

    return leftExpression;
}

ArithmeticOperation Parser::parseArithmeticOperator() {
    if (match(TokenType::Plus)) {
        return ArithmeticOperation::Add;
    }

    if (match(TokenType::Minus)) {
        return ArithmeticOperation::Subtract;
    }

    if (match(TokenType::Star)) {
        return ArithmeticOperation::Multiply;
    }

    if (match(TokenType::Slash)) {
        return ArithmeticOperation::Divide;
    }

    throw error("Ожидался арифметический оператор: +, -, *, /");
}

int Parser::parseLoopCount(const Token& token) const {
    if (token.text.find('.') != std::string::npos) {
        throw ParserError(
            "Количество повторений в loop должно быть целым числом. Строка " +
            std::to_string(token.line) +
            ", колонка " +
            std::to_string(token.column)
        );
    }

    int count = std::stoi(token.text);

    if (count < 0) {
        throw ParserError(
            "Количество повторений в loop не может быть отрицательным. Строка " +
            std::to_string(token.line) +
            ", колонка " +
            std::to_string(token.column)
        );
    }

    return count;
}
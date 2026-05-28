#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "command.hpp"
#include "exceptions.hpp"
#include "tocken_reader.hpp"
#include "tocken.hpp"

#include "loop.hpp"
#include "calc.hpp"
#include "print.hpp"
#include "file_print.hpp"

class Parser {
private:
    const std::vector<Token>& tokens;
    std::size_t position = 0;

public:
    explicit Parser(const std::vector<Token>& tokens);

    std::vector<std::unique_ptr<Command>> parseProgram();

private:
    const Token& peek() const;
    const Token& previous() const;

    bool isAtEnd() const;
    bool check(TokenType type) const;
    bool match(TokenType type);

    Token consume(TokenType type, const std::string& message);

    ParserError error(const std::string& message) const;

    std::vector<std::unique_ptr<Command>> parseCommandList();
    std::unique_ptr<Command> parseCommand();

    std::unique_ptr<Command> parsePrintCommand();
    std::unique_ptr<Command> parseFilePrintCommand();
    std::unique_ptr<Command> parseCalcCommand();
    std::unique_ptr<Command> parseLoopCommand();

    PrintableValue parsePrintableArgument();

    std::unique_ptr<Expression> parseSimpleExpression(bool requireBinaryOperation);
    ArithmeticOperation parseArithmeticOperator();

    int parseLoopCount(const Token& token) const;
};
#include "command.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

// =========================
// Utils
// =========================

namespace {

std::string formatDouble(double value) {
    if (std::abs(value) < 1e-12) {
        value = 0.0;
    }

    std::ostringstream out;
    out << std::setprecision(12) << value;

    return out.str();
}

} // namespace

std::string arithmeticOperationToString(ArithmeticOperation operation) {
    switch (operation) {
        case ArithmeticOperation::Add:
            return "+";

        case ArithmeticOperation::Subtract:
            return "-";

        case ArithmeticOperation::Multiply:
            return "*";

        case ArithmeticOperation::Divide:
            return "/";
    }

    return "?";
}

// =========================
// ExecutionContext
// =========================

void ExecutionContext::print(const std::string& text) const {
    if (consoleMutex != nullptr) {
        std::lock_guard<std::mutex> lock(*consoleMutex);

        std::cout << "[line " << lineNumber << "] "
                  << text
                  << std::endl;
    } else {
        std::cout << "[line " << lineNumber << "] "
                  << text
                  << std::endl;
    }
}

void ExecutionContext::filePrint(
    const std::string& filename,
    const std::string& text
) const {
    if (fileMutex != nullptr) {
        std::lock_guard<std::mutex> lock(*fileMutex);

        std::ofstream file(filename, std::ios::app);

        if (!file) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        file << text << std::endl;
    } else {
        std::ofstream file(filename, std::ios::app);

        if (!file) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        file << text << std::endl;
    }
}

// =========================
// NumberExpression
// =========================

NumberExpression::NumberExpression(double value)
    : value_(value) {}

double NumberExpression::evaluate() const {
    return value_;
}

std::string NumberExpression::debugString() const {
    return formatDouble(value_);
}

// =========================
// BinaryExpression
// =========================

BinaryExpression::BinaryExpression(
    std::unique_ptr<Expression> left,
    ArithmeticOperation operation,
    std::unique_ptr<Expression> right
)
    : left_(std::move(left)),
      operation_(operation),
      right_(std::move(right)) {}

double BinaryExpression::evaluate() const {
    double leftValue = left_->evaluate();
    double rightValue = right_->evaluate();

    switch (operation_) {
        case ArithmeticOperation::Add:
            return leftValue + rightValue;

        case ArithmeticOperation::Subtract:
            return leftValue - rightValue;

        case ArithmeticOperation::Multiply:
            return leftValue * rightValue;

        case ArithmeticOperation::Divide:
            if (rightValue == 0.0) {
                throw std::runtime_error("Division by zero");
            }

            return leftValue / rightValue;
    }

    throw std::runtime_error("Unknown arithmetic operation");
}

std::string BinaryExpression::debugString() const {
    return "(" +
           left_->debugString() +
           " " +
           arithmeticOperationToString(operation_) +
           " " +
           right_->debugString() +
           ")";
}

// =========================
// PrintableValue
// =========================

PrintableValue PrintableValue::fromString(std::string value) {
    return PrintableValue(std::move(value));
}

PrintableValue PrintableValue::fromExpression(
    std::unique_ptr<Expression> expression
) {
    return PrintableValue(std::move(expression));
}

PrintableValue::PrintableValue(std::string value)
    : type_(Type::String),
      stringValue_(std::move(value)),
      expression_(nullptr) {}

PrintableValue::PrintableValue(
    std::unique_ptr<Expression> expression
)
    : type_(Type::Expression),
      stringValue_(),
      expression_(std::move(expression)) {
    if (expression_ == nullptr) {
        throw std::invalid_argument("Printable expression cannot be nullptr");
    }
}

PrintableValue::Type PrintableValue::type() const {
    return type_;
}

std::string PrintableValue::toString() const {
    if (type_ == Type::String) {
        return stringValue_;
    }

    return formatDouble(expression_->evaluate());
}

std::string PrintableValue::debugString() const {
    if (type_ == Type::String) {
        return "\"" + stringValue_ + "\"";
    }

    return expression_->debugString();
}







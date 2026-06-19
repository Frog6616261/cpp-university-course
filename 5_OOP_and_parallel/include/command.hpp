#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

enum class ArithmeticOperation {
    Add,
    Subtract,
    Multiply,
    Divide
};

std::string arithmeticOperationToString(ArithmeticOperation operation);

// =========================
// ExecutionContext
// =========================

struct ExecutionContext {
    int lineNumber = 0;

    std::mutex* consoleMutex = nullptr;
    std::mutex* fileMutex = nullptr;

    void print(const std::string& text) const;
    void filePrint(const std::string& filename, const std::string& text) const;
};

// =========================
// Expression
// =========================

class Expression {
public:
    virtual ~Expression() = default;

    virtual double evaluate() const = 0;
    virtual std::string debugString() const = 0;
};

class NumberExpression final : public Expression {
private:
    double value_;

public:
    explicit NumberExpression(double value);

    double evaluate() const override;
    std::string debugString() const override;
};

class BinaryExpression final : public Expression {
private:
    std::unique_ptr<Expression> left_;
    ArithmeticOperation operation_;
    std::unique_ptr<Expression> right_;

public:
    BinaryExpression(
        std::unique_ptr<Expression> left,
        ArithmeticOperation operation,
        std::unique_ptr<Expression> right
    );

    double evaluate() const override;
    std::string debugString() const override;
};

// =========================
// PrintableValue
// =========================

class PrintableValue {
public:
    enum class Type {
        String,
        Expression
    };

private:
    Type type_;
    std::string stringValue_;
    std::unique_ptr<Expression> expression_;

public:
    static PrintableValue fromString(std::string value);

    static PrintableValue fromExpression(
        std::unique_ptr<Expression> expression
    );

    PrintableValue(const PrintableValue&) = delete;
    PrintableValue& operator=(const PrintableValue&) = delete;

    PrintableValue(PrintableValue&& other) noexcept = default;
    PrintableValue& operator=(PrintableValue&& other) noexcept = default;

    Type type() const;

    std::string toString() const;
    std::string debugString() const;

private:
    explicit PrintableValue(std::string value);

    explicit PrintableValue(
        std::unique_ptr<Expression> expression
    );
};

// =========================
// Command
// =========================

class Command {
public:
    virtual ~Command() = default;

    virtual void execute(const ExecutionContext& context) const = 0;
    virtual std::string debugString() const = 0;
};








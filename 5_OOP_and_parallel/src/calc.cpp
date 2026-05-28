#include "calc.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>


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

// =========================
// CalcCommand
// =========================

CalcCommand::CalcCommand(
    std::unique_ptr<Expression> expression
)
    : expression_(std::move(expression)) {
    if (expression_ == nullptr) {
        throw std::invalid_argument("Calc expression cannot be nullptr");
    }
}

void CalcCommand::execute(const ExecutionContext& context) const {
    double result = expression_->evaluate();

    context.print(
        "calc " +
        expression_->debugString() +
        " = " +
        formatDouble(result)
    );
}

std::string CalcCommand::debugString() const {
    return "calc " + expression_->debugString();
}
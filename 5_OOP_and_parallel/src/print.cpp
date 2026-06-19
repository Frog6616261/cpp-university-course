#include "print.hpp"




// =========================
// PrintCommand
// =========================

PrintCommand::PrintCommand(PrintableValue value)
    : value_(std::move(value)) {}

void PrintCommand::execute(const ExecutionContext& context) const {
    context.print(value_.toString());
}

std::string PrintCommand::debugString() const {
    return "print(" + value_.debugString() + ")";
}

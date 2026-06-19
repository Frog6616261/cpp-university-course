#include "loop.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>



LoopCommand::LoopCommand(
    int count,
    std::vector<std::unique_ptr<Command>> commands
)
    : count_(count),
      commands_(std::move(commands)) {
    if (count_ < 0) {
        throw std::invalid_argument("Loop count cannot be negative");
    }
}

void LoopCommand::execute(const ExecutionContext& context) const {
    for (int i = 0; i < count_; ++i) {
        context.print(
            "loop iteration " +
            std::to_string(i + 1) +
            " / " +
            std::to_string(count_)
        );

        for (const auto& command : commands_) {
            command->execute(context);
        }
    }
}

std::string LoopCommand::debugString() const {
    std::string result =
        "loop(" +
        std::to_string(count_) +
        ") {\n";

    for (const auto& command : commands_) {
        result += "    ";
        result += command->debugString();
        result += ";\n";
    }

    result += "}";

    return result;
}
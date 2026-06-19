#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "command.hpp"




class PrintCommand final : public Command {
private:
    PrintableValue value_;

public:
    explicit PrintCommand(PrintableValue value);

    void execute(const ExecutionContext& context) const override;
    std::string debugString() const override;
};
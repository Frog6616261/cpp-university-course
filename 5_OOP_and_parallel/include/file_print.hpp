#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "command.hpp"


class FilePrintCommand final : public Command {
private:
    std::string filename_;
    PrintableValue value_;

public:
    FilePrintCommand(
        std::string filename,
        PrintableValue value
    );

    void execute(const ExecutionContext& context) const override;
    std::string debugString() const override;
};
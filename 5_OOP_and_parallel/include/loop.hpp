#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "command.hpp"


class LoopCommand final : public Command {
private:
    int count_;
    std::vector<std::unique_ptr<Command>> commands_;

public:
    LoopCommand(
        int count,
        std::vector<std::unique_ptr<Command>> commands
    );

    void execute(const ExecutionContext& context) const override;
    std::string debugString() const override;
};
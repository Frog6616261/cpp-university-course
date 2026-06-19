#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "command.hpp"


class CalcCommand final : public Command {
private:
    std::unique_ptr<Expression> expression_;

public:
    explicit CalcCommand(
        std::unique_ptr<Expression> expression
    );

    void execute(const ExecutionContext& context) const override;
    std::string debugString() const override;
};
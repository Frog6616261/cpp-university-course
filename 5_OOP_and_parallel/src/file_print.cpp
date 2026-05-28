#include "file_print.hpp"

// =========================
// FilePrintCommand
// =========================

FilePrintCommand::FilePrintCommand(
    std::string filename,
    PrintableValue value
)
    : filename_(std::move(filename)),
      value_(std::move(value)) {}

void FilePrintCommand::execute(const ExecutionContext& context) const {
    context.filePrint(filename_, value_.toString());

    context.print(
        "file_print: written to file \"" + filename_ + "\""
    );
}

std::string FilePrintCommand::debugString() const {
    return "file_print(\"" +
           filename_ +
           "\", " +
           value_.debugString() +
           ")";
}
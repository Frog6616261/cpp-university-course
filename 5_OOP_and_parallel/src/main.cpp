// #include "command.hpp"
// #include "tocken.hpp"
// #include "tocken_reader.hpp"
// #include "exceptions.hpp"
// #include "parcer.hpp"
// #include "loop.hpp"
// #include "calc.hpp"
// #include "print.hpp"
// #include "file_print.hpp"

// #include <iostream>
// #include <memory>
// #include <mutex>
// #include <vector>
// #include <cctype>
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <stdexcept>
// #include <string>



// int main() {
//     std::mutex consoleMutex;
//     std::mutex fileMutex;

//     ExecutionContext context;
//     context.lineNumber = 1;
//     context.consoleMutex = &consoleMutex;
//     context.fileMutex = &fileMutex;

//     std::vector<std::unique_ptr<Command>> commands;

//     commands.push_back(
//         std::make_unique<PrintCommand>(
//             PrintableValue::fromString("5 + 4")
//         )
//     );

//     commands.push_back(
//         std::make_unique<PrintCommand>(
//             PrintableValue::fromExpression(
//                 std::make_unique<BinaryExpression>(
//                     std::make_unique<NumberExpression>(5.0),
//                     ArithmeticOperation::Add,
//                     std::make_unique<NumberExpression>(4.0)
//                 )
//             )
//         )
//     );

//     commands.push_back(
//         std::make_unique<FilePrintCommand>(
//             "result.txt",
//             PrintableValue::fromString("hello file")
//         )
//     );

//     commands.push_back(
//         std::make_unique<CalcCommand>(
//             std::make_unique<BinaryExpression>(
//                 std::make_unique<NumberExpression>(10.0),
//                 ArithmeticOperation::Multiply,
//                 std::make_unique<NumberExpression>(3.0)
//             )
//         )
//     );

//     std::vector<std::unique_ptr<Command>> loopBody;

//     loopBody.push_back(
//         std::make_unique<PrintCommand>(
//             PrintableValue::fromString("inside loop")
//         )
//     );

//     loopBody.push_back(
//         std::make_unique<CalcCommand>(
//             std::make_unique<BinaryExpression>(
//                 std::make_unique<NumberExpression>(1.0),
//                 ArithmeticOperation::Add,
//                 std::make_unique<NumberExpression>(1.0)
//             )
//         )
//     );

//     commands.push_back(
//         std::make_unique<LoopCommand>(
//             3,
//             std::move(loopBody)
//         )
//     );

//     for (const auto& command : commands) {
//         std::cout << "DEBUG: " << command->debugString() << std::endl;
//         command->execute(context);
//     }

//     return 0;
// }



// std::string readFileToString(const std::string& filename) {
//     std::ifstream file(filename);

//     if (!file) {
//         throw std::runtime_error("Не удалось открыть файл: " + filename);
//     }

//     std::ostringstream buffer;
//     buffer << file.rdbuf();

//     return buffer.str();
// }

// void printTokens(const std::vector<Token>& tokens) {
//     std::cout << "TOKENS:" << std::endl;

//     for (const Token& token : tokens) {
//         std::cout
//             << "line=" << token.line
//             << ", column=" << token.column
//             << ", type=" << tokenTypeToString(token.type)
//             << ", text=\"" << token.text << "\""
//             << std::endl;
//     }
// }

// // =========================
// // main
// // =========================

// int main(int argc, char* argv[]) {
//     try {
//         std::string sourceCode;

//         if (argc >= 2) {
//             sourceCode = readFileToString(argv[1]);
//         } else {
//             sourceCode = R"(
// start;

// print("5 + 4");
// print(5 + 5);

// file_print("result.txt", "hello");
// file_print("result.txt", 10 + 20);

// calc 5.0 + 6.0;
// calc 1 * 3;
// calc 1 - 4;
// calc 2 / 3.78;

// loop(3) {
//     print("inside loop");
//     print(1 + 1);
//     calc 1 + 1;
//     file_print("result.txt", "loop text");
// };

// end;
// )";
//         }

//         TokenReader tokenReader(sourceCode);

//         std::vector<Token> tokens = tokenReader.readAllTokens();

//         // Удобное место для breakpoint в дебаггере.
//         // Здесь можно открыть vector<Token> tokens и посмотреть все найденные токены.
//         printTokens(tokens);

//         Parser parser(tokens);

//         parser.parseProgram();

//         std::cout << std::endl;
//         std::cout << "Синтаксис программы корректный." << std::endl;
//     } catch (const LexerError& error) {
//         std::cerr << "Ошибка лексического анализа: " << error.what() << std::endl;
//         return 1;
//     } catch (const ParserError& error) {
//         std::cerr << "Ошибка парсинга: " << error.what() << std::endl;
//         return 1;
//     } catch (const std::exception& error) {
//         std::cerr << "Ошибка: " << error.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }



// #include "command.hpp"
// #include "tocken.hpp"
// #include "tocken_reader.hpp"
// #include "exceptions.hpp"
// #include "parcer.hpp"
// #include "loop.hpp"
// #include "calc.hpp"
// #include "print.hpp"
// #include "file_print.hpp"

// #include <iostream>
// #include <memory>
// #include <mutex>
// #include <vector>
// #include <cctype>
// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <stdexcept>
// #include <string>



// int main() {
//     std::mutex consoleMutex;
//     std::mutex fileMutex;

//     ExecutionContext context;
//     context.lineNumber = 1;
//     context.consoleMutex = &consoleMutex;
//     context.fileMutex = &fileMutex;

//     std::vector<std::unique_ptr<Command>> commands;

//     commands.push_back(
//         std::make_unique<PrintCommand>(
//             PrintableValue::fromString("5 + 4")
//         )
//     );

//     commands.push_back(
//         std::make_unique<PrintCommand>(
//             PrintableValue::fromExpression(
//                 std::make_unique<BinaryExpression>(
//                     std::make_unique<NumberExpression>(5.0),
//                     ArithmeticOperation::Add,
//                     std::make_unique<NumberExpression>(4.0)
//                 )
//             )
//         )
//     );

//     commands.push_back(
//         std::make_unique<FilePrintCommand>(
//             "result.txt",
//             PrintableValue::fromString("hello file")
//         )
//     );

//     commands.push_back(
//         std::make_unique<CalcCommand>(
//             std::make_unique<BinaryExpression>(
//                 std::make_unique<NumberExpression>(10.0),
//                 ArithmeticOperation::Multiply,
//                 std::make_unique<NumberExpression>(3.0)
//             )
//         )
//     );

//     std::vector<std::unique_ptr<Command>> loopBody;

//     loopBody.push_back(
//         std::make_unique<PrintCommand>(
//             PrintableValue::fromString("inside loop")
//         )
//     );

//     loopBody.push_back(
//         std::make_unique<CalcCommand>(
//             std::make_unique<BinaryExpression>(
//                 std::make_unique<NumberExpression>(1.0),
//                 ArithmeticOperation::Add,
//                 std::make_unique<NumberExpression>(1.0)
//             )
//         )
//     );

//     commands.push_back(
//         std::make_unique<LoopCommand>(
//             3,
//             std::move(loopBody)
//         )
//     );

//     for (const auto& command : commands) {
//         std::cout << "DEBUG: " << command->debugString() << std::endl;
//         command->execute(context);
//     }

//     return 0;
// }


#include "command.hpp"
#include "tocken.hpp"
#include "tocken_reader.hpp"
#include "exceptions.hpp"
#include "parcer.hpp"
#include "loop.hpp"
#include "calc.hpp"
#include "print.hpp"
#include "file_print.hpp"

#include <cctype>
#include <stdexcept>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Cannot open source file: " + filename);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void printCommandsDebug(
    const std::vector<std::unique_ptr<Command>>& commands
) {
    std::cout << "Parsed commands:" << std::endl;

    for (std::size_t i = 0; i < commands.size(); ++i) {
        std::cout << i + 1
                  << ". "
                  << commands[i]->debugString()
                  << std::endl;
    }

    std::cout << std::endl;
}

void executeCommands(
    const std::vector<std::unique_ptr<Command>>& commands,
    const ExecutionContext& context
) {
    for (const auto& command : commands) {
        command->execute(context);
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
            std::cerr << "Example: " << argv[0] << " program.txt" << std::endl;
            return 1;
        }

        const std::string filename = argv[1];

        std::cout << "Source file: " << filename << std::endl;

        std::string sourceCode = readFileToString(filename);

        TokenReader tokenReader(sourceCode);
        std::vector<Token> tokens = tokenReader.readAllTokens();

        Parser parser(tokens);
        std::vector<std::unique_ptr<Command>> commands = parser.parseProgram();

        printCommandsDebug(commands);

        std::mutex consoleMutex;
        std::mutex fileMutex;

        ExecutionContext context;
        context.lineNumber = 1;
        context.consoleMutex = &consoleMutex;
        context.fileMutex = &fileMutex;

        std::cout << "Program started." << std::endl;

        auto startTime = std::chrono::steady_clock::now();

        executeCommands(commands, context);

        auto finishTime = std::chrono::steady_clock::now();

        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(
                finishTime - startTime
            ).count();

        double milliseconds = microseconds / 1000.0;
        double seconds = microseconds / 1000000.0;

        std::cout << "Program finished." << std::endl;

        std::cout << "Execution time: "
                  << microseconds
                  << " microseconds"
                  << std::endl;

        std::cout << "Execution time: "
                  << milliseconds
                  << " milliseconds"
                  << std::endl;

        std::cout << "Execution time: "
                  << seconds
                  << " seconds"
                  << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}
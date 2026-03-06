#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

int main() {
    // Set correctly dir
    std::filesystem::path directory = "./";  
    std::filesystem::path filePath = directory / "output.log";

    // Ceate dirctory
    if (!std::filesystem::exists(directory)) {
        std::cerr << "There are't directory!" << std::endl;
        return 1;
    }

    // is output.log exist?
    if (std::filesystem::exists(filePath)) {
        std::cout << "File output.log exist\n";

        if (std::filesystem::remove(filePath)) {
            std::cout << "Complete deleted\n";
        } else {
            std::cout << "Error with deleted\n";
        }
    }


    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Open the fle in append mode
    std::ofstream outFile(filePath, std::ios::app);

    if (!outFile) {
        std::cerr << "Openning's error!" << std::endl;
        return 1;
    }

    outFile << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << std::endl;

    outFile.close();

    std::cout << "Data completly write into output.log in current folder" << filePath << std::endl;
    return 0;
}
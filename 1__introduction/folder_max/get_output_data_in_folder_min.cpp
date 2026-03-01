#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

int main() {
    // Укажи нужную директорию
    std::filesystem::path directory = "../folder_min";  
    std::filesystem::path filePath = directory / "output.log";

    // Создаем директорию, если она не существует
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }

    // Получаем текущее время
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Открываем файл в режиме добавления (append)
    std::ofstream outFile(filePath, std::ios::app);

    if (!outFile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    outFile << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << std::endl;

    outFile.close();

    std::cout << "Дата и время успешно записаны в " << filePath << std::endl;
    return 0;
}
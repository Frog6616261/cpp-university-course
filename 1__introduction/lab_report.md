# Introduction

## 1. Operating Systems Lab Work
Working with the OS, File System, Access Permissions, and File Execution

## 1.1

Create two directories in /usr/local/: folder_max, older_min

```
cd /usr/local
mkdir folder_max folder_min
```

## 1.2

Create two user groups: group_max, group_min
```
sudo groupadd group_max
sudo groupadd group_min
```

## 1.3

Create two users: user_max_1, user_min_1
```
sudo useradd -M user_max_1
sudo passwd user_max_1

sudo useradd -M user_max_1
sudo passwd user_max_1
```

## 1.4

Configure access permissions as follows:

Users belonging to the *_max group must have full access (read, write, execute) to both *_max and *_min directories.

Users belonging to the *_min group must have full access only to the *_min directory.
```
sudo usermod -aG group_max user_max_1                      
sudo usermod -aG group_max user_min_1

sudo usermod -aG group_min user_min_1

sudo chown :group_max folder_max          
sudo chown :group_min folder_min

sudo chmod 777 folder_max                              
sudo chmod 777 folder_min
```

## 1.5

Create and execute (by a user from the corresponding category) a script in the `folder_max` directory that writes the current date and time to a file named output.log located in the same directory.


```
cd folder_max
nano get_output_data_in_folder_max_by_user_max.cpp
```

```cpp
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

    std::cout << "Data completly write into output.log in folder_max by user_max " << filePath << std::endl;
    return 0;
}
```
```
g++ -Wall -Wextra -Wpedantic get_output_data_in_folder_max_by_user_max.cpp -o get_output_data_in_folder_max_by_user_max

sudo chown user_max_1:group_max get_output_data_in_folder_max_by_user_max
sudo chmod 770 get_output_data_in_folder_max_by_user_max

su - user_max_1
./get_output_data_in_folder_max_by_user_max
```

### Result
```bash
Complete deleted
Data completly write into output.log in folder_max by user_max "./output.log"
```

## 1.6

Create and execute (by a user from the corresponding category) a script in the `folder_max` directory that writes the current date and time to a file named output.log located in the `*_min directory`.

## 1.7

Execute (by a *_min user) a script located in the folder_max directory that writes the current date and time to a file named output.log in the *_min directory.

## 1.8

Create and execute (by a user from the corresponding category) a script in the folder_min directory that writes the current date and time to a file named output.log in the *_max directory.

## 1.9

Display the list of access permissions for the *_min and *_max directories, as well as for all files and subdirectories contained within them.
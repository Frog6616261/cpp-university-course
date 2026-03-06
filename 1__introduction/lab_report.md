# Introduction

## 1. Operating Systems Lab Work
Working with the OS, File System, Access Permissions, and File Execution

### 1.1

Create two directories in /usr/local/: folder_max, older_min

```
cd /usr/local
mkdir folder_max folder_min
```

### 1.2

Create two user groups: group_max, group_min
```
sudo groupadd group_max
sudo groupadd group_min
```

### 1.3

Create two users: user_max_1, user_min_1
```
sudo useradd -M user_max_1
sudo passwd user_max_1

sudo useradd -M user_max_1
sudo passwd user_max_1
```

### 1.4

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

### 1.5

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
```bash
g++ -Wall -Wextra -Wpedantic get_output_data_in_folder_max_by_user_max.cpp -o get_output_data_in_folder_max_by_user_max

sudo chown user_max_1:group_max get_output_data_in_folder_max_by_user_max
sudo chmod 770 get_output_data_in_folder_max_by_user_max

su - user_max_1
./get_output_data_in_folder_max_by_user_max
```

#### Result
```bash
Complete deleted
Data completly write into output.log in folder_max by user_max "./output.log"
```

### 1.6

Create and execute (by a user from the corresponding category) a script in the `folder_max` directory that writes the current date and time to a file named output.log located in the `*_min directory`.


```bash
nano get_output_data_in_folder_min_by_user_max.cpp
```
```cpp
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

int main() {
    // Set correctly dir
    std::filesystem::path directory = "../folder_min";  
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

    std::cout << "Data completly write into output.log in folder_min by user_max " << filePath << std::endl;
    return 0;
}
```
```bash
g++ -Wall -Wextra -Wpedantic get_output_data_in_folder_min_by_user_max.cpp -o get_output_data_in_folder_min_by_user_max

sudo chown user_max_1:group_max get_output_data_in_folder_min_by_user_max
sudo chmod 770 get_output_data_in_folder_min_by_user_max

./get_output_data_in_folder_max_by_user_max
```

#### Result
```bash
File output.log exist
Complete deleted
Data completly write into output.log in folder_min by user_max "../folder_min/output.log
```


### 1.7

Execute (by a `*_min user`) a script located in the folder_max directory that writes the current date and time to a file named output.log in the `*_min` directory.
```bash
su - user_min_1
su: warning: cannot change directory to /home/user_min_1: No such file or directory
$ ./get_output_data_in_folder_min_by_user_max
-sh: 1: ./get_output_data_in_folder_min_by_user_max: Permission denied
```

#### Change owners

```bash
sudo chown :group_min get_output_data_in_folder_min_by_user_max   
su - user_min_1
./get_output_data_in_folder_min_by_user_max
```
#### Result

```bash
File output.log exist
Complete deleted
Data completly write into output.log in folder_min by user_max "../folder_min/output.log"
```

### 1.8

Create and execute (by a user from the corresponding category) a script in the `folder_min` directory that writes the current date and time to a file named output.log in the `*_max` directory.

```bash
cd ../folder_min
nano get_output_data_in_folder_max_by_user_min.cpp
```

```cpp
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>

int main() {
    // Set correctly dir
    std::filesystem::path directory = "../folder_max";  
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

    std::cout << "Data completly write into output.log in folder_max by user_min " << filePath << std::endl;
    return 0;
}
```

```bash
g++ -Wall -Wextra -Wpedantic get_output_data_in_folder_max_by_user_min.cpp -o get_output_data_in_folder_max_by_user_min 
sudo chown user_min_1:group_min get_output_data_in_folder_max_by_user_min 
chmod 770 get_output_data_in_folder_max_by_user_min
su - user_min_1
./get_output_data_in_folder_max_by_user_min 
```

#### Result

```bash
File output.log exist
Complete deleted
Data completly write into output.log in folder_max by user_min "../folder_max/output.log"
```

### 1.9

Display the list of access permissions for the `*_min` and `*_max` directories, as well as for all files and subdirectories contained within them.


#### Access permissions list for directories
```bash
ls -l
drwxrwxrwx 2 maker group_max 4096 Mar  5 22:55 folder_max
drwxrwxrwx 2 maker group_min 4096 Mar  5 22:41 folder_min
```

#### Access permissions list for folder_max
```bash
cd folder_max
ls -l
-rwxrwxr-x 1 user_max_1 user_max_1 40144 Mar  1 19:01 get_output_data_in_folder_max_by_user_max
-rw-rw-r-- 1 maker      maker       1273 Mar  1 19:02 get_output_data_in_folder_max_by_user_max.cpp
-rwxrwx--- 1 user_max_1 group_min  40144 Mar  5 10:22 get_output_data_in_folder_min_by_user_max
-rw-rw-r-- 1 maker      maker       1284 Mar  5 10:20 get_output_data_in_folder_min_by_user_max.cpp
-rw-rw-r-- 1 user_min_1 user_min_1    20 Mar  5 22:55 output.log
```

#### Access permissions list for folder_min
```bash
cd ../folder_min
ls -l
-rwxrwx--- 1 user_min_1 group_min  40144 Mar  5 22:41 get_output_data_in_folder_max_by_user_min
-rw-rw-r-- 1 maker      maker       1284 Mar  5 21:39 get_output_data_in_folder_max_by_user_min.cpp
-rw-rw-r-- 1 user_min_1 user_min_1    20 Mar  5 20:55 output.log
```

## 2. DOCKER Container

### 2.0 Install Docker

For installing *Docke Engene* on Ubuntu Nobe see this https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository

### 2.1 Write script

```bash
mkdir my_docker_images && cd my_docker_images
mkdir docker_output_data && cd docker_output_data
nano write_current_data.cpp
```

#### Script
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

    std::cout << "Data completly write into output.log in current folder" << filePath << std::endl;
    return 0;
}
```
#### Write DockerFile
```bash
nano Dockerfile
```

```dockerfile
FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y g++ nano

WORKDIR /app

COPY write_current_data.cpp .

RUN g++ -std=c++17 -Wall -Wpedantic -Wextra write_current_data.cpp -o write_current_data

CMD ["./write_current_data"]
```

### 2.3 Build docker container

```bash
docker build -t docker_write_data .
docker run docker_write_data:latest 
```

#### Result
```bash
Data completly write into output.log in current folder"./output.log"
```

#### docker attach
For open started docker, you need:
```bash
docker run -it docker_write_data:latest bash
```

### 2.4 Execute script

```bash
docker run -it docker_write_data:latest bash
./write_current_data
```

#### Result
```bash
Data completly write into output.log in current folder"./output.log"
```

### 2.5 Output all users into console

```bash
docker run -it docker_write_data:latest bash
cut -d: -f1 /etc/passwd
```

#### Result
```bash
root
daemon
bin
sys
sync
games
man
lp
mail
news
uucp
proxy
www-data
backup
list
irc
_apt
nobody
ubuntu
```

## 3 GIT/GitHub

### 3.1 Create repository

#### Create repo on GitHub
I'm create repo on GitHub https://github.com/Frog6616261/cpp-university-course

#### Create repo on lokal mashine and link
```bash
git init
git add .
git commit -m "init commit"
git remote add origin git@github.com:Frog6616261/cpp-university-course.git
git push origin master
```





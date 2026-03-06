FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y g++ nano

WORKDIR /app

COPY write_current_data.cpp .

RUN g++ -std=c++17 -Wall -Wpedantic -Wextra write_current_data.cpp -o write_current_data

CMD ["./write_current_data"]
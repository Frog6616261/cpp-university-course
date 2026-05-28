#include <iostream>
#include <chrono>
#include <iomanip>
#include <unistd.h>
#include <sys/wait.h>

using lluint = unsigned long long;
using Clock = std::chrono::steady_clock;

struct Result
{
    lluint value;
    double time_sec;
};

lluint f1(lluint x, uint numb_iteration)
{
    volatile lluint res = 0;
    for (uint i = 0; i < numb_iteration; ++i)
    {
        res += x * x - x * x + x * 4 - x * 5 + x + x;;
    }

    return res;
}

lluint f2(lluint x, uint numb_iteration)
{
    volatile lluint res = 0;
    for (uint i = 0; i < numb_iteration; ++i)
    {
        res += x + x; 
    }
    return res;
}


lluint START_VAL = 1;


void run_processes(int iterations)
{
    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    auto total_start = Clock::now();

    pid_t pid1 = fork();

    if (pid1 == 0)
    {
        close(pipe1[0]);

        auto start = Clock::now();

        Result result;
        result.value = f1(START_VAL, iterations);

        auto end = Clock::now();
        result.time_sec = std::chrono::duration<double>(end - start).count();

        write(pipe1[1], &result, sizeof(result));
        close(pipe1[1]);

        _exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 == 0)
    {
        close(pipe2[0]);

        auto start = Clock::now();

        Result result;
        result.value = f2(START_VAL,iterations);

        auto end = Clock::now();
        result.time_sec = std::chrono::duration<double>(end - start).count();

        write(pipe2[1], &result, sizeof(result));
        close(pipe2[1]);

        _exit(0);
    }

    close(pipe1[1]);
    close(pipe2[1]);

    Result result1;
    Result result2;

    read(pipe1[0], &result1, sizeof(result1));
    read(pipe2[0], &result2, sizeof(result2));

    close(pipe1[0]);
    close(pipe2[0]);

    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);

    auto start3 = Clock::now();

    lluint result3 = result1.value + result2.value - result1.value;

    auto end3 = Clock::now();
    double time3 = std::chrono::duration<double>(end3 - start3).count();

    auto total_end = Clock::now();
    double total_time = std::chrono::duration<double>(total_end - total_start).count();

    std::cout << std::fixed << std::setprecision(9);

    std::cout << "PROCESS, iterations: " << iterations << '\n';
    std::cout << "Formula 1 time: " << result1.time_sec << " sec\n";
    std::cout << "Formula 2 time: " << result2.time_sec << " sec\n";
    std::cout << "Formula 3 time: " << time3 << " sec\n";
    std::cout << "Total time:     " << total_time << " sec\n";

    std::cout << "Result 1:       " << result1.value << '\n';
    std::cout << "Result 2:       " << result2.value << '\n';
    std::cout << "Result 3:       " << result3 << '\n';

    std::cout << "----------------------------------\n";
}

int main()
{
    run_processes(10'000);
    run_processes(100'000);

    return 0;
}
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

using lluint = long long unsigned int;


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




int main()
{
    lluint start_val = 1;

    lluint result1 = 0;
    lluint result2 = 0;
    lluint result3 = 0;

    std::chrono::nanoseconds duration1;
    std::chrono::nanoseconds duration2;
    std::chrono::nanoseconds total_time;



    std::chrono::high_resolution_clock::time_point total_start = std::chrono::high_resolution_clock::now();

    std::thread t1([&]() {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        result1  = f1(start_val, 10'000);

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    });

    std::thread t2([&]() {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        result2  = f2(start_val, 10'000);

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    });

    t1.join();
    t2.join();


    result3 = result1 + result2 - result1;

    std::chrono::high_resolution_clock::time_point total_end = std::chrono::high_resolution_clock::now();
    total_time = std::chrono::duration_cast<std::chrono::nanoseconds>(total_end - total_start);

    std::cout << std::fixed << std::setprecision(9);

    std::cout << "Numb iteration: " << "10'000" << '\n';
    std::cout << "Formula 1 time: " << duration1.count() << " nanosec" << '\n';
    std::cout << "Formula 2 time: " << duration2.count() << " nanosec" << '\n';
    std::cout << "Total time:     " << total_time.count() << " nanosec" << '\n';
    std::cout << "Result 1:       " << result1 << '\n';
    std::cout << "Result 2:       " << result2 << '\n';
    std::cout << "Result 3:       " << result3 << '\n';
    std::cout << "----------------------------------" << '\n';



    total_start = std::chrono::high_resolution_clock::now();

    std::thread t3([&]() {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        result1  = f1(start_val, 100'000);

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    });

    std::thread t4([&]() {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        result2  = f2(start_val, 100'000);

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    });

    t3.join();
    t4.join();


    result3 = result1 + result2 - result1;

    total_end = std::chrono::high_resolution_clock::now();
    total_time = std::chrono::duration_cast<std::chrono::nanoseconds>(total_end - total_start);

    std::cout << std::fixed << std::setprecision(9);

    std::cout << "Numb iteration: " << "100'000" << '\n';
    std::cout << "Formula 1 time: " << duration1.count() << " nanosec" << '\n';
    std::cout << "Formula 2 time: " << duration2.count() << " nanosec" << '\n';
    std::cout << "Total time:     " << total_time.count() << " nanosec" << '\n';
    std::cout << "Result 1:       " << result1 << '\n';
    std::cout << "Result 2:       " << result2 << '\n';
    std::cout << "Result 3:       " << result3 << '\n';
    std::cout << "----------------------------------" << '\n';

    return 0;
}
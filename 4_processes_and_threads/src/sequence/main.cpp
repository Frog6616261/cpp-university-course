#include <cmath>
#include <iostream>
#include <cstring>
#include <chrono>

using lluint = long long unsigned int;

lluint f_1(lluint x, uint numb_iteration)
{
    lluint res = 0;

    for (uint i = 0; i < numb_iteration; ++i)
    {
        res += x*x - x*x + x*4 - x*5 + x + x; 
    }
    return res;
}


lluint f_2(lluint x, uint numb_iteration)
{
    lluint res = 0;

    for (uint i = 0; i < numb_iteration; ++i)
    {
        res += x + x; 
    }

    return res; 
}


int main() {

    lluint start_val = 1;

    lluint res1;
    lluint res2;
    lluint res3;


    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res1 = f_1(start_val, 10'000);
    res2 = f_2(start_val, 10'000);

    res3 = res1 + res2 - res1;

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Time: " << duration.count() << " nanoseconds " << "  result: " << res3 << "  Numb iteration: " << "10'000" << std::endl;


    start = std::chrono::high_resolution_clock::now();

    res1 = f_1(start_val, 100'000);
    res2 = f_2(start_val, 100'000);

    res3 = res1 + res2 - res1;

    end = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Time: " << duration.count() << " nanoseconds " << "  result: " << res3 << "  Numb iteration: " << "100'000" << std::endl;

    
    return 0;
}
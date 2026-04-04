#include <cmath>
#include <cstddef>
#include <iostream>
#include <math.h>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <string>


uint MAX_INT_NUMBERS[] = {7, 4, 6, 3, 8, 4, 7, 4, 1, 2};


double solve_equation(double x){

    return std::pow(x, 2.0) - std::pow(x, 2.0) + std::pow(x, 4.0) - std::pow(x, 5.0) + x + x;
}


int main(int argc, char* argv[]) {

    uint numb_iterations = 0;

    if (argc == 1) return 0; // nothing input

    if (argc != 2) {
        std::cerr << "Error: no input provided\n";
        std::cerr << "Usage: ./program <iterations>\n";
        return 1;
    }

    size_t sz_symb = std::strlen(argv[1]);
 
    // max unsigned int 2 147 483 647
    if (sz_symb > 10){
        std::cerr << "Error: too big number for uint\n";
        return 1;
    }

    uint symbol;
    char symbol_char;
    
    for (size_t i = 0; i < sz_symb; ++i){

        symbol_char = (argv[1])[i];
        
        //is number check
        if (symbol_char < 48 && 57 < symbol_char){
            std::cerr << "Error: input not a number\n";
            return 1;
        } 

        symbol = static_cast<uint>((argv[1])[i]) - 48; // char -> uint , (-48) for this

        uint cur_power = (sz_symb - 1) - i;

        //max in check
        if ((sz_symb == 10) && (MAX_INT_NUMBERS[cur_power] < symbol)){
            std::cerr << "Error: too big number for uint\n";
            return 1;
        }
        
        numb_iterations += symbol * std::pow(10u, cur_power); 
    }

    start_func_iter:

    // solve result and count time
    double result = 0;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    for (uint i = 0; i < numb_iterations; ++i){
        result = solve_equation(result);
    }

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Time: " << duration.count() << " nanoseconds\n" <<
     "Func result: " << std::fixed << std::setprecision(16) << result << std::endl;

    char answer;
    std::cout << "Run again?(y/n): ";
    std::cin >> answer;

    answer = std::tolower(static_cast<unsigned char>(answer));

    if (answer == 'y') {
        goto start_func_iter;
    }
    
    return 0;
}
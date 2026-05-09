#include <iostream>
#include <string>


double sum(double a, double b){
    return a + b;
}

double mult(double a, double b){
    return a * b;
}

double minus(double a, double b){
    return a - b;
}

double power(double base, uint power) {
    double result = 1;

    for (uint i = 0; i < power; ++i) {
        result = mult(result,base);
    }

    return result;
}

enum calc_operators {
    PLUS,
    MINUS,
    MULT,
    POWER,
    NO_OPERATORS
};

calc_operators parse_operator(const std::string& str){
    if (str == "+") return PLUS;
    if (str == "-") return MINUS;
    if (str == "*") return MULT;
    if (str == "^") return POWER;

    return NO_OPERATORS;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: calc <num1 double> <op: \"+\", \"-\", \"*\", \"^\"> <num2 double>\n";
        return 1;
    }

    double a = std::stod(argv[1]);
    std::string op = argv[2];
    double b = std::stod(argv[3]);

    double result = 0;

    calc_operators cur_operator = parse_operator(op);

    switch (cur_operator) {
        case PLUS:
            result = sum(a, b);
            break;
        case MINUS:
            result = minus(a, b);
            break; 
        case MULT:
            result = mult(a, b);
            break; 
        case POWER:
            result = power(a, b);
            break; 
        
        default:
            std::cout << "Not correct operator" << result << std::endl;
            return -1;
            break;    
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}
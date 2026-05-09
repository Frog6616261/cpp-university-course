# Laboratory Work #3  
## C++ & UNIX: CLI / FUNCTION / LOOP / RECURSION

---

# 1. Task Description

The objective of this laboratory work was to study basic algorithmic constructions in C++ and apply them in command-line applications. The work also demonstrates the efficiency of recursive algorithms.

The laboratory work consisted of two main tasks:

## 1.1 CLI Calculator

Develop a command-line calculator application named `CALC` that accepts three arguments:

- first operand;
- arithmetic operator;
- second operand.

Supported operators:

- `+`
- `-`
- `*`
- `^`

The implementation had to use only:

- functions;
- conditions;
- loops;
- arithmetic operations.

---

## 1.2 Tower of Hanoi

Implement the classical Tower of Hanoi problem using recursion.

Requirements:

- move all disks from the source tower to the destination tower;
- obey the Tower of Hanoi rules;
- store the resulting sequence of moves;
- print the full sequence to the console.

The implementation also included a brute-force recursive search for arbitrary tower configurations.

---

# 2. Code Description

## 2.1 CLI Calculator

The calculator application was implemented as a command-line utility that parses input arguments and performs arithmetic operations.

### Implemented Functions

The following arithmetic functions were implemented:

```cpp
double sum(double a, double b);
double minus(double a, double b);
double mult(double a, double b);
double power(double base, uint power);
```

The `power()` function computes exponentiation using iterative multiplication inside a loop.

---

### Operator Parsing

An enumeration was introduced to represent supported operators:

```cpp
enum calc_operators {
    PLUS,
    MINUS,
    MULT,
    POWER,
    NO_OPERATORS
};
```

The function:

```cpp
calc_operators parse_operator(const std::string& str);
```

converts a string operator into the corresponding enumeration value.

---

### Command Line Interface

The program accepts arguments in the following format:

```bash
calc <number1> <operator> <number2>
```

Example:

```bash
calc 2 ^ 5
```

The application validates the number of arguments, converts string values into floating-point numbers using `std::stod`, and executes the requested operation using a `switch` statement.

---

# 2.2 Tower of Hanoi

The second program implements the Tower of Hanoi problem using recursion and stack-based tower representation.

---

## Towers Representation

A structure named `Towers` was implemented:

```cpp
struct Towers
```

The structure contains:

- number of towers;
- number of disks;
- vector of stacks representing towers.

Initialization places all disks onto the first tower.

---

## Recursive Hanoi Algorithm

The classical recursive algorithm was implemented in the function:

```cpp
void hanoi(uint n, uint from, uint to, uint temp, way_stack& way);
```

Algorithm steps:

1. Move `n - 1` disks to the temporary tower.
2. Move the largest disk to the destination tower.
3. Move `n - 1` disks from the temporary tower to the destination tower.

The resulting sequence of moves is stored in:

```cpp
using way_stack = std::vector<std::pair<uint, uint>>;
```

Each pair represents a move:

```cpp
(from_tower, to_tower)
```

---

## Brute Force Recursive Search

An additional recursive brute-force algorithm was implemented:

```cpp
void search_hanonian_bruforce(...)
```

The algorithm:

- recursively explores all valid moves;
- checks stack constraints;
- stores the shortest valid solution;
- avoids invalid reverse moves.

The maximum recursion depth is limited by:

```cpp
MAX_ITER
```

to reduce unnecessary recursive calls.

---

## Program Execution

The application accepts command-line arguments:

```bash
towers <number_of_plates> <number_of_towers>
```

Example:

```bash
towers 3 3
```

The resulting sequence of moves is printed to the console.

---

# 3. Conclusion

During this laboratory work, command-line applications in C++ were implemented using:

- functions;
- loops;
- conditions;
- recursion;
- stacks;
- vectors;
- recursive search algorithms.

The work demonstrated practical usage of recursion through the Tower of Hanoi problem and introduced basic CLI program architecture in C++.
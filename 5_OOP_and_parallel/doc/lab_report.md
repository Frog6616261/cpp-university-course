# Lab Work #5
# C++ & UNIX — C++ OOP / Parallel Programming

## Goal

The goal of this lab work is to introduce the student to object-oriented programming in C++ by designing and implementing a simple interpreted mini-language.

The student must create the syntax of a personal mini-language for parallel programming, implement its parsing, and execute the parsed commands.

## Task

### C++ Parallel Language

Create a programming language that supports the following commands:

- count-controlled loop;
- console output;
- file output in append mode;
- arithmetic operations:
  - addition: `+`
  - subtraction: `-`
  - multiplication: `*`
  - division: `/`

A count-controlled loop must be able to contain any other supported command, including another loop.

The implementation must use object-oriented programming principles for representing and executing language commands.

## Program Requirements

The program must implement the following steps:

### 1. Text Input of Commands

The program reads commands from standard input.

Each new input line is treated as a separate command set.

Example:

```txt
print("Hello")
print(5 + 5)
loop(3) { print("Loop") }
```

### 2. End of Input

The program continues reading commands until the user enters a special command.

For this project, the input-ending command is:

```txt
run
```

After `run` is entered, the program stops reading input and starts executing the entered command sets.

### 3. Parallel Execution

Each input line must be executed in a separate thread.

The command sets must be executed in parallel.

The program should print information about when each thread starts and finishes.

Example:

```txt
[Line 1] Thread started
[Line 2] Thread started
[Line 1] Thread finished
[Line 2] Thread finished
```

## Mini-Language Documentation

## Supported Commands

| Command | Description |
|---|---|
| `print(...)` | Prints a string or expression result to the console |
| `file_print(...)` | Writes a string or expression result to a file in append mode |
| `calc(...)` | Calculates an arithmetic expression |
| `loop(...) { ... }` | Repeats a block of commands a fixed number of times |

## `print`

Prints text or the result of an arithmetic expression to the console.

### Syntax

```txt
print("text")
print(expression)
```

### Examples

```txt
print("Hello, world!")
print(5 + 5)
print(10 * 2 - 3)
```

## `file_print`

Writes text or the result of an arithmetic expression to a file.

If the file does not exist, it is created in the program execution directory.

The output is written in append mode.

### Syntax

```txt
file_print("filename.txt", "text")
file_print("filename.txt", expression)
```

### Examples

```txt
file_print("output.txt", "Hello from file")
file_print("output.txt", 5 + 5)
```

## `calc`

Calculates an arithmetic expression.

### Syntax

```txt
calc(expression)
```

### Examples

```txt
calc(5 + 5)
calc(10 - 3)
calc(4 * 6)
calc(20 / 5)
```

The `calc` command can be used inside other commands:

```txt
print(calc(5 + 5))
file_print("result.txt", calc(10 * 2))
```

## `loop`

Repeats a block of commands a fixed number of times.

The loop body can contain any supported command.

### Syntax

```txt
loop(count) {
    command1
    command2
}
```

### Example

```txt
loop(3) {
    print("Hello")
}
```

### Nested Loop Example

```txt
loop(2) {
    print("Outer loop")

    loop(3) {
        print("Inner loop")
    }
}
```

## Object-Oriented Design

The program should use a common base command interface and separate command classes for different operations.

Possible command classes:

- `Command`
- `PrintCommand`
- `FilePrintCommand`
- `CalcCommand`
- `LoopCommand`

Each command class should implement its own execution logic.

## Lexical Analysis

Before parsing, the input text must be split into tokens.

Possible token types:

| Token Type | Example |
|---|---|
| Identifier | `print`, `file_print`, `loop`, `calc` |
| Number | `10`, `25`, `3.14` |
| String literal | `"Hello"` |
| Operator | `+`, `-`, `*`, `/` |
| Parentheses | `(`, `)` |
| Braces | `{`, `}` |
| Comma | `,` |
| End command | `run` |

## Parser

The parser receives tokens and builds command objects.

The parser must recognize:

- console output commands;
- file output commands;
- calculation commands;
- loops;
- arithmetic expressions.

## Execution Flow

The general program flow is:

1. Read input lines from the user.
2. Stop reading when the user enters `run`.
3. Tokenize each input line.
4. Parse tokens into command objects.
5. Start one thread for each input line.
6. Execute the parsed command set inside its thread.
7. Wait until all threads finish.

## Example Input

```txt
print("Start")
print(5 + 5)
file_print("output.txt", "Writing to file")
loop(3) { print("Inside loop") }
run
```

## Expected Result

As a result of this lab work, the program must:

- implement a custom mini-language;
- support parsing and execution of commands;
- support arithmetic expressions;
- support console output;
- support file output in append mode;
- support count-controlled loops;
- support nested commands inside loops;
- execute each input line in a separate thread;
- use object-oriented programming principles.
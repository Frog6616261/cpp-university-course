# C++ BUILD / IF / LOOP, PYTHON

## Task 1 — C++ Expression Program

### Goal
Develop and compile a C++ program that evaluates a mathematical expression multiple times and measures execution time.

### Requirements
- Build output must be stored in the `build/` directory.
- The `build/` directory must be added to `.gitignore`.

### Program Behavior
- Read an integer `n` from standard input — number of iterations.
- If the input is not a valid number → terminate the program.

### Computation
- For each iteration, compute the expression:

  $x^2 - x^2 + x \cdot 4 - x \cdot 5 + x + x$

### Structure
- Implement the expression in a separate function.
- Call this function repeatedly from `main()` using a loop.

### Timing
- Measure total execution time for `n` iterations.

### Additional Behavior
- After execution, prompt user to rerun the program.
- If user declines → terminate program.

---

## Task 2 — Python Expression Program

### Goal
Develop a Python 3 program with identical functionality to the C++ version.

### Requirements
- Store compiled/intermediate results in `build/`.
- Add `build/` to `.gitignore`.

### Program Behavior
- Read integer `n` from input.
- If input is invalid → terminate.

### Computation
- Evaluate the same expression:

  $x^2 - x^2 + x \cdot 4 - x \cdot 5 + x + x$

### Structure
- Place computation in a separate function.
- Call it iteratively from `main`.

### Timing
- Measure total execution time for `n` evaluations.

### Additional Behavior
- Allow repeated execution via user prompt.

---

## Task 3 — Repository & Version Control

### Goal
Store results and organize version control workflow.

### Requirements
- Save all code and outputs in a Git repository.
- Add a report to the `doc/` directory.

### Branching Strategy
- All commits must go through the `dev` branch.

### Deployment
- Provide scripts to:
  - Promote changes from `dev` → `stg` → `prd`
  - Roll back to the current revision state (including uncommitted changes and new files)

### Scripts
- Place all scripts in the repository root.



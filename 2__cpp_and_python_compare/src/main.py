import time


def calculate(x: float) -> float:
    return x ** 2 - x ** 2 + x * 4 - x * 5 + x + x


def read_iterations():
    user_input = input("Enter number of iterations: ").strip()

    if user_input == "":
        return None

    if not user_input.isdigit():
        return None

    return int(user_input)


def run_calculations(iterations: int) -> None:
    x = 10.0

    start_time = time.perf_counter()

    result = 0.0
    for _ in range(iterations):
        result = calculate(x)

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time

    print(f"Result: {result}")
    print(f"Execution time: {elapsed_time:.10f} seconds")


def main():
    while True:
        iterations = read_iterations()

        if iterations is None:
            print("Input is not a valid non-negative integer. Program finished.")
            break

        run_calculations(iterations)

        answer = input("Run again? (y/n): ").strip().lower()
        if answer != "y":
            print("Program finished.")
            break


if __name__ == "__main__":
    main()
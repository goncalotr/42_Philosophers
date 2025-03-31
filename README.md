# 42 Philosophers Project

This repository is dedicated to my school 42 philosophers project.
This project simulates the classic "Dining Philosophers" problem using concurrency concepts.

## Overview

This simulation involves a number of philosophers sitting around a table with a shared bowl of spaghetti and a limited number of forks. Each philosopher needs two forks to eat. The goal is to implement a solution that allows all philosophers to eat without encountering deadlocks or starvation.

## Project Usage

You can try this project out by cloning the repository,
and following the next steps.

Clone the repository:
```bash
git clone github.com
```

Enter the cloned repository:

```bash
cd 42_Philosophers/Philosophers
```

Compile the project using the Makefile

```bash
make
```

Run the program:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```

#### Arguments
- `number_of_philosophers`: The number of philosophers (and forks).

- `time_to_die` (ms): Time a philosopher can go without eating before dying.

- `time_to_eat` (ms): Time it takes for a philosopher to eat.

- `time_to_sleep` (ms): Time a philosopher spends sleeping.

- `number_of_times_each_philosopher_must_eat` **(optional)**: Simulation ends when all philosophers have eaten this many times.

## Reference

## Other

- This project follows the code style required by norminette.
- Norminette is checked using github actions.
- Makefile is used to compile the project.
Its compiled with `cc` with the flags `-Wall` `-Wextra` `-Werror`.
The makefile includes the standard rules: `all`, `clean`, `fclean`, and `re`.
- Libft is not authorized.

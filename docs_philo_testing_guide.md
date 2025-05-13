# Philosophers Testing Guide

This guide outlines various tests to ensure the correctness, robustness, and efficiency of the Philosophers project implementation.

## Program Testing

Testing the program with various inputs is crucial to cover different scenarios.

**Arguments:**
1.  `number_of_philosophers`
2.  `time_to_die` (ms)
3.  `time_to_eat` (ms)
4.  `time_to_sleep` (ms)
5.  `[number_of_times_each_philosopher_must_eat]` (optional)


Test with various inputs:
- Subject examples: 4 410 200 200, 5 800 200 200, 5 800 200 200 7
- Edge cases: 1 800 200 200, 2 100 10 10, 4 310 200 100 (potential death)
- Large numbers (within reason): 200 800 200 200

**General Checks for All Tests:**
- Timestamps should be accurate (in ms, increasing order).
- Output format should match the subject requirements (e.g., `timestamp_in_ms X has taken a fork`).
- Only one death message should be printed if a philosopher dies.
- The simulation should stop immediately after a death is detected.
- No output should occur after a death message (except potentially program cleanup messages if you added any).
- If the optional meal count is provided, the program should terminate cleanly after all philosophers have eaten the specified number of times, without any deaths (unless times make it impossible).

### Simple Scenarios

#### Scenario 1

```bash
./philo 1 800 200 200
```

- Description: 1 philosopher with `time_to_die` of 800ms, `time_to_eat` of 200ms, `time_to_sleep` of 200ms.
- Expected Behavior: The philosopher needs two forks to eat but only one is available (its own). It cannot eat and should die after exactly 800ms (+/- small margin for timing inaccuracies, typically within 10ms). The output should be 800 1 died (or similar, adjusted for exact timing).

#### Scenario 2

```bash
./philo 5 800 200 200
```

- Description: 5 philosophers, `time_to_die` = 800 ms, `time_to_eat` = 200 ms, `time_to_sleep` = 200 ms. This is a standard "happy path".
- Expected Behavior: No philosopher should die. The time_to_die is double the time_to_eat + time_to_sleep, providing ample time even with moderate waiting for forks. The simulation should run indefinitely (or until manually stopped) with philosophers cycling through thinking, eating, and sleeping states.

#### Scenario 3

```bash
 ./philo 5 800 200 200 7
```

- Description: Same as above, but with the optional argument: each philosopher must eat 7 times.
- Expected Behavior: No philosopher should die. The simulation should run until each of the 5 philosophers has completed its 7th meal. The program should then terminate cleanly without any death message. All meal counts should be reached.

#### Scenario 4

```bash
./philo 4 410 200 200
```

- Description: 4 philosophers, `time_to_die` = 410ms, `time_to_eat` = 200 ms, `time_to_sleep` = 200 ms. `time_to_die` is very close to `time_to_eat` + `time_to_sleep` (400ms).
- Expected Behavior: No philosopher should die. This tests the efficiency of the scheduling and fork acquisition. Any significant delay (> 10ms) for a philosopher waiting for forks after sleeping could cause death, so the implementation must be reasonably performant and fair.

#### Scenario 5

```bash
./philo 4 310 200 100
```

- Description: 4 philosophers, `time_to_die` = 310 ms, `time_to_eat` = 200 ms, `time_to_sleep` = 100 ms. `time_to_die` is barely larger than `time_to_eat` + `time_to_sleep` (300ms).

- Expected Behavior: At least one philosopher is expected to die. The time buffer (10ms) is extremely small. After eating (200ms) and sleeping (100ms), a philosopher has almost no time left before time_to_die (measured from the start of the last meal) expires. Waiting for forks will likely cause death. The simulation must stop immediately after the first death, reporting the correct philosopher and a timestamp close to their expected death time (e.g., `start_of_last_meal_time` + 310 ms).

### Bad Usage (Error Handling)

#### Scenario 1

```bash
./philo
```

- Description: No program arguments provided.
- Expected Behavior: Error message indicating too few arguments. Program should exit with a non-zero status code. No simulation should start.

#### Scenario 2

```bash
./philo 1 2 3
```

- Description: Too few program arguments (4 required, 5 optional).
- Expected Behavior: Error message indicating too few arguments. Program should exit with a non-zero status code. No simulation should start.

#### Scenario 3

```bash
./philo 1 2 3 4 5 6
```

- Description: Too many program arguments (max 5 allowed).
- Expected Behavior: Error message indicating too many arguments. Program should exit with a non-zero status code. No simulation should start.

#### Scenario 4

```bash
./philo five 800 200 200
```
- Description: Non-numeric value for number_of_philosophers.
- Expected Behavior: Error message indicating invalid input (e.g., "Error: Arguments must be positive integers"). Program should exit with a non-zero status code.

#### Scenario 5

```bash
./philo 5 -800 200 200
```

- Description: Negative value for `time_to_die`.
- Expected Behavior: Error message indicating invalid input (e.g., "Error: Time arguments must be non-negative integers"). Program should exit with a non-zero status code.

#### Scenario 6

```bash
./philo 0 800 200 200
```

- Description: Zero philosophers specified.
- Expected Behavior: Error message indicating invalid input (e.g., "Error: Number of philosophers must be greater than 0"). Program should exit with a non-zero status code.

#### Scenario 7

```bash
./philo 5 800 200 200 0
```

- Description: Optional meal count is zero.
- Expected Behavior: The program should start and terminate immediately and cleanly, as no meals need to be eaten. No philosopher should perform any action (eat, sleep, think).

### Edge Cases & Stress Tests

#### Scenario 1

```bash
./philo 2 100 200 200
```

- Description: 2 philosophers where `time_to_eat` > `time_to_die`.
- Expected Behavior: Both philosophers should attempt to eat, but neither can complete a meal before time_to_die expires. Both should die relatively quickly (around 100ms). The program must detect and report the first death accurately (timestamp +/- 10ms) and terminate immediately.

#### Scenario 2

```bash
./philo 200 800 200 200
```

- Description: Large number of philosophers (200). Tests concurrency handling, potential for slowdowns due to mutex contention, and fairness.
- Expected Behavior: No philosopher should die, as `time_to_die` is generous. The simulation should run without deadlocking or crashing. Monitor for excessive CPU usage or slowdowns compared to smaller numbers of philosophers. (Adding an optional meal count, e.g., ./philo 200 800 200 200 5, is useful to check if it terminates correctly under load).

#### Template

```bash
./philo <N> <T_die> <T_eat> <T_sleep> [meals]
```

- Description: General template. Experiment with various combinations, especially where T_die is close to T_eat + T_sleep or T_eat * 2 (if they might have to wait for forks for a full cycle). Pay close attention to the death time accuracy (should be within ~10ms of the expected time).

## Thread Safety & Leak Testing

Use dedicated tools to detect subtle threading issues (data races, deadlocks) and memory leaks. Compile with -g to include debug symbols for more informative reports.

Compilation Flags:
- Use `-pthread` for thread library linking.
- Use `-g` for debug symbols.

Tools:

1. Valgrind (Memcheck): Detects memory leaks and invalid memory access.

	```bash
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo 5 800 200 200
	```

	- Purpose: Ensure no memory allocated (e.g., for threads, mutexes, philosopher data) is leaked.
	- Expected: No leaks are possible or definitely lost.

2. Valgrind (Helgrind): Detects potential deadlocks and data races related to mutex usage and thread ordering.

	```bash
	valgrind --tool=helgrind ./philo 5 800 200 200
	```

	- Purpose: Identify issues like improper mutex locking/unlocking, potential race conditions where data is accessed without adequate protection, and lock order inversions that could lead to deadlocks.
	- Expected: No errors reported. Helgrind can sometimes report false positives, but all reports should be investigated.

3. Valgrind (DRD): Another tool for detecting data races and lock contention issues. May find different issues than Helgrind.

	```bash
	valgrind --tool=drd ./philo 5 800 200 200
	```

	- Purpose: Alternative or supplement to Helgrind for finding threading errors.
	- Expected: No errors reported.

4. Thread Sanitizer (TSan): Compile-time instrumentation to detect data races and deadlocks at runtime. Often faster than Valgrind tools but requires recompilation.

	```bash
	# Compile with TSan enabled
	gcc -g -pthread -fsanitize=thread your_files.c -o philo_tsan
	# Run the instrumented executable
	./philo_tsan 5 800 200 200
	```

	- Purpose: Detect data races (accessing shared memory without proper locking) during execution.
	- Expected: No data race warnings printed to stderr during execution.

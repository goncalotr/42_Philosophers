# Philosophers Testing Guide

## Program Testing

Test with various inputs:
- Subject examples: 4 410 200 200, 5 800 200 200, 5 800 200 200 7
- Edge cases: 1 800 200 200, 2 100 10 10, 4 310 200 100 (potential death)
- Large numbers (within reason): 200 800 200 200

Limitations
### Simple Scenarios


```bash
./philo 1 1000 200 200
```

- Description: 1 philosopher with `time_to_die` of 1000 ms while `time_to_eat` is 200 ms and `time_to_sleep` is 200 ms
- Expected Behavior: Philospher should die after 1000 ms because there aren't 2 forks to allow eating.

```bash
./philo 5 800 200 200
```

- Description: There are 5 philosophers, and each has a time_to_die of 800 ms, time_to_eat of 200 ms, and time_to_sleep of 200 ms.
- Expected Behavior: No philosopher should die. They should continuously take turns eating and sleeping.

```bash
 ./philo 5 800 200 200 7
```

```bash
./philo 4 410 200 200
```

```bash
./philo 4 310 200 100
```


### Bad Usage

```bash
./philo 5 800 200 200 5
```
- Description: Too many program arguments
- Expected Behavior: Error - Too many arguments

```bash
./philo
```
- Description: No program arguments
- Expected Behavior: Error - Too few arguments

### Edge Cases

```shell
./philo 2 <various times>
```

- Description: Use 2 philosophers with different time_to_die, time_to_eat, and time_to_sleep values to test edge cases.
- Expected Behavior: Test for accurate death timing. A death delayed by more than 10 ms is unacceptable in these tests.

## Leak Testing

Valgrind and sanitize
- **leak-check==**: Run valgrind `--leak-check=full` for memory leaks 
- **Helgrind**: Run with valgrind `--tool=helgrind` to check for potential deadlocks and race conditions related to mutex usage.
- **DRD**: Run with valgrind `--tool=drd` for another perspective on data races.
- **FSanitise**: Compile with `-fsanitize=thread` to detect threading problems while running.

# Bonus Testing

## 1 Invalid Arguments

```bash
./philo_bonus (not enough args)
./philo_bonus 1 2 3 4 5 6 (too many args)
./philo_bonus -1 800 200 200 (negative philos)
./philo_bonus 5 800 -200 200 (negative time)
./philo_bonus 5 800 200 200 0 (zero meals)
./philo_bonus a 800 200 200 (non-numeric arg)
```

## 2 Death Case (No meal limit):

```bash
./philo_bonus 1 800 200 200
```
Expected: The philosopher should take one fork, wait, and die at ~800ms.

```bash
./philo_bonus 4 310 200 100
```
Expected: A philosopher should die at ~310ms. The simulation must stop immediately after the first death message. No other messages should appear after "died".

```bash
./philo_bonus 5 800 200 200
```
Expected: No one should die. The simulation runs "forever" (until you stop it with Ctrl+C). This tests for deadlocks. If your program freezes, you have a deadlock.

## 3 Meal Completion Case:

```bash
./philo_bonus 5 800 200 200 7
```
Expected: The simulation should stop after every philosopher has eaten 7 times. No death message should appear. The output should be clean.

```bash
./philo_bonus 4 410 200 200 10
```
Expected: The simulation should stop after every philosopher has eaten 10 times. No one should die.

## 4 Edge Case - The "Death Squeeze":

```bash
./philo_bonus 2 400 200 200
```
This is a tight timing. time_to_die is exactly time_to_eat + time_to_sleep. They should just barely survive.

```bash
./philo_bonus 2 399 200 200
```
Expected: A philosopher will likely die. This tests the accuracy of your timing.

## 5 High Contention Test:

```bash
./philo_bonus 200 800 200 200
```
Expected: The simulation runs without deadlock or excessive, immediate deaths. This tests the performance and correctness of your semaphore-based solution under load.

# Philosophers Project Test List

## I. Argument Validation & Error Handling

*   **Invalid Number of Arguments:**
    *   `./philo` (too few)
    *   `./philo 1 200 100` (too few)
    *   `./philo 1 200 100 100 5 6` (too many)
    *   **Expected:** Error message, non-zero exit status. No simulation starts.
*   **Non-Numeric Arguments:**
    *   `./philo one 200 100 100`
    *   `./philo 5 200 food 100`
    *   `./philo 5 200 100 100 five`
    *   **Expected:** Error message, non-zero exit status. No simulation starts.
*   **Negative or Zero Values (where not allowed):**
    *   `./philo 0 200 100 100` (num_philosophers)
    *   `./philo -5 200 100 100` (num_philosophers)
    *   `./philo 5 0 100 100` (time_to_die)
    *   `./philo 5 -200 100 100` (time_to_die)
    *   `./philo 5 200 0 100` (time_to_eat)
    *   `./philo 5 200 -100 100` (time_to_eat)
    *   `./philo 5 200 100 0` (time_to_sleep)
    *   `./philo 5 200 100 -100` (time_to_sleep)
    *   `./philo 5 200 100 100 0` (num_meals - special case, should stop immediately or run until death if not handled as "all ate")
    *   `./philo 5 200 100 100 -5` (num_meals)
    *   **Expected:** Error message for invalid critical values, non-zero exit status. For `num_meals = 0`, simulation might end immediately stating all have eaten, or run until death if that's the only end condition. (Subject implies if `num_meals` is present, simulation stops when all eat *that many* times. `0` meals means they've all eaten "enough" from the start).
*   **Number of Philosophers Exceeding `PHILO_MAX` (if you have such a limit, e.g., 200):**
    *   `./philo 201 TTD TTE TTS`
    *   **Expected:** Error message, non-zero exit status.
*   **Very Large Valid Values (Check for overflow if not using `long` appropriately):**
    *   `./philo 5 2147483647 200 200` (Max int for TTD)
    *   **Expected:** Program should handle large (but valid `size_t`/`long`) times gracefully. Focus is on correct behavior, not necessarily instant death with huge TTD.

## II. Simulation Logic & Rules (No `num_meals` argument)

*   **One Philosopher:**
    *   `./philo 1 800 200 200`
    *   **Expected:** Philosopher takes one fork, waits `time_to_die`, then dies. Output: `0 1 has taken a fork`, then `800 1 died`. (Order of logs for taking fork and dying must be correct, death log within 10ms of actual death).
*   **Multiple Philosophers - Death Scenario:**
    *   `./philo 4 410 200 200`
    *   `./philo 5 800 200 200`
    *   **Expected:** Simulation runs until one philosopher dies. All other philosophers should stop their actions (no new logs after a death is announced, except possibly for threads cleaning up if they were mid-action). Only one death message.
*   **Multiple Philosophers - Specific Cases:**
    *   `./philo 2 300 100 100`
    *   **Expected:** Test deadlock avoidance. They should be able to eat. One should die.
    *   `./philo 3 300 100 100`
    *   **Expected:** Test deadlock avoidance. One should die.
*   **No philosopher should starve if they can eat:**
    *   `./philo 4 1000 100 100` (Long enough TTD for everyone to eat multiple times)
    *   **Expected:** Philosophers should cycle through eat/sleep/think. One will eventually die due to timing.
*   **Time Accuracy (Hard to test precisely without external tools, but observe):**
    *   Philo eating for `time_to_eat`, sleeping for `time_to_sleep`.
    *   Death occurs close to `time_to_die` after the last meal.
    *   Death message within 10ms of actual death.

## III. Simulation Logic & Rules (With `num_meals` argument)

*   **All Philosophers Eat Enough Times:**
    *   `./philo 5 800 200 200 7` (Ensure TTD is long enough not to cause premature death)
    *   **Expected:** Simulation stops after *each* of the 5 philosophers has eaten 7 times. No death message. The last log should be an eating/sleeping/thinking state, not "died".
*   **One Philosopher, `num_meals` Specified:**
    *   `./philo 1 800 200 200 5`
    *   **Expected:** The philosopher cannot eat (needs two forks). Will take one fork, wait `time_to_die`, then die. The `num_meals` condition won't be met.
*   **`num_meals = 0`:**
    *   `./philo 5 800 200 200 0`
    *   **Expected:** Simulation should stop immediately, as the condition (0 meals) is met by all philosophers from the start. No activity logs.
*   **Death Before All Eat Enough (`num_meals` is high, TTD is short):**
    *   `./philo 4 410 200 200 100`
    *   **Expected:** One philosopher dies before all can eat 100 times. Simulation stops on death.

## IV. Output Formatting & Thread Safety

*   **Correct Log Format:**
    *   `timestamp_in_ms X has taken a fork`
    *   `timestamp_in_ms X is eating`
    *   `timestamp_in_ms X is sleeping`
    *   `timestamp_in_ms X is thinking`
    *   `timestamp_in_ms X died`
    *   **Expected:** All output lines must strictly follow this format. Timestamp should be ms from simulation start. X is philo ID (1 to N).
*   **No Overlapping Messages (Visual Inspection & `tsan`):**
    *   Run with various numbers of philosophers.
    *   **Expected:** Output lines should be complete and not interleaved. The `write_lock` mutex should ensure this.
*   **No Data Races (`-fsanitize=thread`):**
    *   Compile with `TSAN_FLAGS = -fsanitize=thread -g`.
    *   Run various scenarios: `make tsan ARGS="4 410 200 200"`, `make tsan ARGS="5 800 200 200 7"`.
    *   **Expected:** No data race warnings from ThreadSanitizer.
*   **Death Message Timing:**
    *   **Expected:** The "died" message must appear within 10ms of the calculated death time. This is hard to verify perfectly without precise logging *inside* your death check, but observe relative timestamps.

## V. Resource Management & Makefile

*   **No Memory Leaks (`valgrind --leak-check=full`):**
    *   Run various scenarios: `make memcheck ARGS="4 410 200 200"`, `make memcheck ARGS="5 800 200 200 7"`.
    *   **Expected:** No memory leaks reported by Valgrind. All heap-allocated memory must be freed.
*   **Makefile Rules:**
    *   `make` or `make all` (compiles `$(NAME)`)
    *   `make clean` (removes object files)
    *   `make fclean` (removes object files and `$(NAME)`)
    *   `make re` (fclean + all)
    *   **Expected:** All rules work as described in Common Instructions. No unnecessary relinking.
*   **Compiler Flags:**
    *   **Expected:** Uses `cc` with `-Wall -Wextra -Werror -pthread`.

## VI. Specific Deadlock Prevention

*   **Odd/Even ID Fork Grabbing or Fork Address Ordering:**
    *   Your strategy to prevent deadlocks (e.g., even-ID philosophers pick up right fork first, odd-ID pick up left, or always picking up the fork with the lower memory address/index first).
    *   Test with 2, 3, 4, 5 philosophers with times that *could* lead to deadlock if not handled.
    *   Example: `./philo 2 100 30 30` (TTD is short, they need to eat fast or die)
    *   **Expected:** Philosophers should successfully acquire forks and eat without deadlocking. If TTD is too short, one will die, but not due to a program-level deadlock.

## VII. Edge Cases & Stress Tests

*   **Very Short Times (e.g., 1ms for TTD, TTE, TTS):**
    *   `./philo 5 60 10 10` (Quick deaths or rapid eating if `num_meals` is also small)
    *   `./philo 2 10 1 1 1000`
    *   **Expected:** Program should not crash. Behavior should be consistent with the timings, likely leading to quick deaths or quick completion if `num_meals` is small.
*   **Max Philosophers (as per `PHILO_MAX` or a reasonable high number like 200):**
    *   `./philo 200 1000 200 200` (Monitor for performance, races, correct death)
    *   `./philo 200 1000 200 200 3` (Monitor for completion)
    *   **Expected:** Program should handle many threads without crashing. Performance might degrade, but correctness is key.

## General Notes for Testing:

*   **Redirect Output:** For long runs or to analyze logs, redirect output: `./philo <args> > output.log`.
*   **Use a Test Script:** Consider a simple shell script to run multiple test cases automatically.
*   **Peer Evaluation:** Use these tests (and any others you think of) during peer evaluations.
*   **Norminette:** Ensure all code passes `norminette` checks.
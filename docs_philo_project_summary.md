# Philosophers Project Summary

This document provides a simple overview of the key concepts involved in the 42 Philosophers project.

## 1. The Problem: Dining Philosophers

- **Setup:** Several philosophers sit around a circular table. Between each pair of philosophers is a single fork. In the center is a shared bowl of spaghetti.
- **Actions:** Philosophers cycle through three states:
	1. **Thinking:** Pondering life's mysteries.
	2. **Eating:** Needs **two** forks (left and right) to eat spaghetti.
	3. **Sleeping:** Resting after eating.
- **Goal:** Design a system where philosophers can eat without problems.
- **Challenge:** Limited forks create competition and potential issues.

## 2. Concurrency & Threads (Mandatory Part)

- **Concurrency:** Multiple actions happening seemingly at the same time. Think of each philosopher as an independent worker.
- **Threads:** In the mandatory part, each philosopher is represented by a separate **thread**. A thread is like a lightweight process that can run alongside other threads within the same program. They share the program's memory.

## 3. Shared Resources

- These are things multiple threads need to access. In this project, the main shared resources are:
	- **Forks:** Each fork is shared between two philosophers.
	- **Global State:** Any shared variable indicating if the simulation should stop (like a `dead_flag`).
	- **Standard Output (Console):** Multiple threads might try to print log messages at the same time.

## 4. The Big Problem: Race Conditions (Specifically Data Races)

- **What is a Race Condition?** A situation where the outcome of a computation depends on the unpredictable timing of concurrent events (how threads interleave).

- **What is a Data Race?** This is a *specific type* of race condition and the one you **must avoid** in Philosophers. A data race occurs when:
	1.  **Two or more threads** access the **same memory location** concurrently.
	2.  **At least one** of the accesses is a **write** operation.
	3.  There is **no synchronization mechanism** (like a mutex) protecting that memory access.

- **Analogy:** Imagine two people trying to write *different numbers* in the *exact same small box* on a piece of paper *at the exact same time* without coordinating. What number ends up in the box? Maybe one overwrites the other? Maybe the result is a garbled mix? The outcome is unpredictable and likely wrong.

- **Why are Data Races BAD?**
	- **Undefined Behavior:** The C standard says data races lead to undefined behavior. This means *anything* can happen: crashes, incorrect calculations, corrupted data, results that change randomly each time you run the program, or seemingly working correctly only to fail later.
	- **Debugging Nightmare:** Problems caused by data races are often intermittent and hard to reproduce.
- **Example in Philosophers:**
	- If two philosophers try to update a shared variable like `meals_eaten_total` without protection.
	- If the monitoring thread reads a philosopher's `last_meal_time` while the philosopher thread is simultaneously updating it.
	- If you don't protect the `dead_flag` when multiple threads might check or set it.

## 5. The Solution: Synchronization & Mutexes

- **Synchronization:** Coordinating the actions of multiple threads to ensure they access shared resources safely.

- **Mutex (Mutual Exclusion):** The primary tool for synchronization in the mandatory part.
	- Think of a mutex as a **lock** or a **talking stick**. Only the thread currently holding the mutex (the lock) is allowed to access the specific shared resource it protects.
	- **`pthread_mutex_lock()`:** A thread tries to acquire the lock. If the lock is available, the thread takes it and proceeds. If another thread already holds the lock, this thread *waits* (blocks) until the lock is released.
	- **`pthread_mutex_unlock()`:** The thread that holds the lock releases it, allowing another waiting thread (if any) to acquire it.

- **How Mutexes Prevent Data Races:** By ensuring only one thread can access/modify a specific piece of shared data at any given time, mutexes eliminate the "simultaneous access with a write" condition that defines a data race.

- **In Philosophers:**
	- Each **fork** needs its own mutex. A philosopher must lock *both* their left and right fork mutexes before eating.
	- The shared `dead_flag` needs a mutex.
	- Accessing/modifying a philosopher's `last_meal_time` or `meals_eaten` count (if checked by a monitor thread) needs a mutex.
	- Printing to the console should use a "write lock" mutex to prevent garbled output.

## 6. Other Critical Problems to Avoid

- **Deadlock:** A situation where two or more threads are stuck waiting for each other indefinitely.
	- *Classic Example:* Every philosopher picks up their left fork and waits forever for the right fork (which is held by their neighbor, who is also waiting).
	- *Prevention:* Careful ordering of resource acquisition (e.g., lock forks in a specific order, maybe odd philosophers lock left-then-right, even philosophers lock right-then-left).

- **Starvation:** A situation where a thread is perpetually denied access to necessary resources and cannot make progress.
	- *Example:* One philosopher might just be unlucky and always find one of their needed forks already taken whenever they try to eat, potentially exceeding their `time_to_die`.
	- *Prevention:* Fair locking strategies, ensuring the simulation logic doesn't inherently disadvantage certain philosophers.

## 7. Time Management & Logging

- **`gettimeofday()`:** Used to get the current time (usually converted to milliseconds).

- **Tracking Time:** Essential for:
	- Calculating timestamps for logs.
	- Checking if `time_since_last_meal > time_to_die`.
	- Implementing `time_to_eat` and `time_to_sleep` delays (often using `usleep` or a custom precise sleep function).

- **Logging:** Output must match the specific format required by the subject, and printing must be protected by a mutex (`write_lock`) to avoid garbled output.

## Summary

The core goal is to simulate the dining philosophers using threads, ensuring **no data races** occur by correctly using **mutexes** to protect shared resources (forks, state variables, output). You must also design your locking strategy carefully to prevent **deadlocks** and ensure the simulation logic prevents **starvation**, all while adhering to the timing and logging requirements.

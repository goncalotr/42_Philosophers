# Core Concurrency Concepts

This document provides a general explanation of fundamental concepts and potential problems encountered in concurrent programming.

## 1. Concurrency vs. Parallelism

- **Concurrency:** Dealing with multiple tasks *logically* active at the same time. These tasks might be interleaved on a single CPU core or run truly in parallel on multiple cores. The focus is on managing shared resources and coordinating execution.

- **Parallelism:** Executing multiple tasks *simultaneously*, typically requiring multiple CPU cores. It's a way to achieve concurrency and speed up computation.

## 2. Threads and Processes

- **Process:** An independent program running in its own memory space. Processes typically don't share memory directly and communicate via Inter-Process Communication (IPC) mechanisms (pipes, sockets, shared memory segments, etc.).
- **Thread:** A "lightweight process" that runs within the context of a parent process. Multiple threads within the same process share the same memory space (global variables, heap), making data sharing easy but also requiring careful synchronization.

## 3. Shared Resources

- Any piece of data, memory, or hardware component that can be accessed by multiple concurrent threads or processes. Examples include:
	- Global variables
	- Static variables
	- Objects allocated on the heap
	- Files
	- Network connections
	- Hardware devices (like printers or sensors)
	- Standard output (console)

## 4. Race Conditions

- **Definition:** A situation where the correctness or outcome of a program depends on the unpredictable relative timing or interleaving of operations performed by multiple concurrent threads or processes. The result varies depending on "who wins the race" to access or modify a resource.

- **Types:** Data races are a common *type* of race condition, but other types exist where the *order* of operations matters, even if they don't involve simultaneous conflicting memory access (e.g., check-then-act problems).
- **Example (Check-Then-Act):**
	1.  Thread A checks if a file exists.
	2.  Thread B deletes the file *before* Thread A tries to open it.
	3.  Thread A tries to open the file, assuming it exists based on its earlier check, leading to an error.

## 5. Data Races

- **Definition:** A data race occurs specifically when **all** of the following conditions are met:
	1. **Multiple Threads/Processes:** Two or more concurrent execution units access the **same memory location**.
	2. **Conflicting Access:** At least one of the accesses is a **write** operation (modification).
	3. **No Synchronization:** There is **no mechanism** (like a mutex) coordinating these accesses to ensure they happen sequentially or safely.

- **Consequences:** Leads to **Undefined Behavior** in languages like C and C++. The program might crash, produce incorrect results, corrupt data, or behave unpredictably. Data races are notoriously difficult to debug because they often depend on timing and may not occur consistently.

- **Example:**
	* Thread A: `counter = counter + 1;`
	* Thread B: `counter = counter + 1;`
	* If `counter` is initially 0, the final result *should* be 2. However, without synchronization, both threads might read 0, both calculate 1, and both write 1 back, resulting in a final value of 1 instead of 2.

## 6. Synchronization Primitives

Synchronization Primitives are used to control access to shared resources and coordinate thread/process execution:

- **Mutex (Mutual Exclusion):** A lock ensuring only one thread can execute a specific "critical section" of code or access a specific resource at a time. Prevents data races by serializing access.
- **Semaphore:** A counter used to control access to a pool of resources. Threads "wait" (decrement) on the semaphore to acquire a resource permit and "post" (increment) to release it. Can be used for mutual exclusion (binary semaphore, count=1) or managing limited resources (counting semaphore, count > 1).
- **Condition Variable:** Allows threads to wait efficiently until a specific condition becomes true. Used in conjunction with a mutex to avoid busy-waiting (constantly checking a condition in a loop).
- **Atomic Operations:** Hardware-level instructions that perform simple operations (like read, write, increment, compare-and-swap) on a memory location indivisibly. Faster than mutexes for simple operations but more complex to use for compound actions.
- **Monitors:** Higher-level synchronization constructs (common in languages like Java) that bundle data with the mutex and condition variables needed to protect it.

## 7. Deadlock

- **Definition:** A situation where two or more threads/processes are blocked indefinitely, each waiting for a resource held by another thread in the cycle.

- **Conditions for Deadlock (Coffman Conditions):** All four must typically hold:
	1.  **Mutual Exclusion:** Resources are held in a non-shareable mode (only one process/thread can use it at a time).
	2.  **Hold and Wait:** A process/thread holds at least one resource and is waiting to acquire additional resources held by others.
	3.  **No Preemption:** Resources cannot be forcibly taken away from the process/thread holding them; they must be released voluntarily.
	4.  **Circular Wait:** A set of waiting processes/threads {T0, T1, ..., Tn} exists such that T0 is waiting for a resource held by T1, T1 is waiting for a resource held by T2, ..., Tn is waiting for a resource held by T0.

- **Prevention/Avoidance:** Break one of the Coffman conditions (e.g., acquire locks in a consistent global order to prevent circular wait, use timeouts, acquire all needed locks at once if possible).

## 8. Starvation (or Livelock)

- **Starvation:** A situation where a process or thread is perpetually denied access to necessary resources, preventing it from making progress, even though the system as a whole might be active. Often caused by unfair scheduling or resource allocation policies.

- **Livelock:** A situation where processes or threads are actively changing state or responding to each other, but none are making useful progress towards their goal. They are busy but effectively stuck.
	- *Example:* Two people trying to pass in a narrow hallway keep stepping aside in the same direction simultaneously, preventing either from passing.

# Philosophers Testing Guide

## Program Testing

Test with various inputs:
- Subject examples: 4 410 200 200, 5 800 200 200, 5 800 200 200 7
- Edge cases: 1 800 200 200, 2 100 10 10, 4 310 200 100 (potential death)
- Large numbers (within reason): 200 800 200 200

### Simple Scenarios

### Wrong Usage

### Edge Cases

## Leak Testing

Valgrind and sanitize
- **leak-check==**: Run valgrind `--leak-check=full` for memory leaks 
- **Helgrind**: Run with valgrind `--tool=helgrind` to check for potential deadlocks and race conditions related to mutex usage.
- **DRD**: Run with valgrind `--tool=drd` for another perspective on data races.
- **FSanitise**: Compile with `-fsanitize=thread` to detect threading problems while running.

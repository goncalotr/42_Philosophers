# 42 Philosophers Testing

## Running

```sh
make

./philo x x x x 
```

Check makefile not relinking by using 2 times. Where the following message should be displayed:

```sh

```

## Leak Testing

```sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -fsanitize=thread ./philo...
```

Valgrind Arguments
- `--leak-check=full`
- `--show-leak-kinds=all`
- `--track-origins=yes`
- `-fsanitize=thread` - the most relevant flag specifically for this project

## User Tests






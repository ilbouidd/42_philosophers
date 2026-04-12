*This project has been created as part of the 42 curriculum by ilbouidd*
# 42_Philosophers

# Description
Philosophers is an 42 School project that simulates the classic "dining philosophers" problem. The goal is to manage concurrency and synchronization between multiple threads in C, avoiding deadlocks and data races.

Dining Problem: 
Two(or more)philosophers sit at a round table. Between each philosopher is a fork, and in the center, a large bowl of spaghetti. A philosopher must pick up two forks (their left and right ones) to eat. Once satisfied, they put the forks down and go back to thinking or sleeping.

#### Critical rules:

    A philosopher must never starve (time limit without eating).

    Avoid deadlocks (all philosophers blocked waiting).

    Respect timings: thinking, eating, sleeping.
# Instructions

#### Compilation and Usage:

```bash
make

./philo 5 800 200 200
./philo 5 800 200 200 7
```

Example of output :

```text
0 1  has taken a fork
0 1  is eating
0 1  is sleeping
0 1  is thinking
```

# Resources

## Important Function:
```text
pthread_create: create a thread, divide the main thread. Different from fork that duplicates. 

```

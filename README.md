# Philosophers

A program that simulates a resolution of the dining philosophers' problem, created by Edsger Wybe Dijkstra in 1965 AD.
    Copyright (C) 2024  Federico Porciello

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

Contact: fporciel@student.42roma.it

From [Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem):

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present form.

This program implements a possible solution to this problem, for any number of threads.
This is a simulation that can be started by entering the parameters that define the specific application of the problem: it will produce a dinner of virtually infinite duration if the parameters are reasonable and a dinner of virtually limited
duration depending on the unreasonable parameters entered.

## Introduction

This problem, originally formulated by Edsger Dijkstra in 1965, is a classic synchronization challenge which involves a set of philosophers seated around a circular table with a bowl of spaghetti in the center. Each philosopher has a fork to their
left and right, but since each philosopher requires two forks to eat, they must navigate a protocol that prevents deadlock (where no philosopher can eat due to a circular wait condition) and starvation (where a philosopher is indefinitely denied
access to forks).
The metaphor of the Dining Philosophers problem extends deeply into both philosophical inquiry and the practical concerns of threading and process synchronization in computer science. Philosophically, it mirrors existential dilemmas of resource
sharing, competition, and the balance between individual needs and communal harmony. In computer science, it exemplifies the challenges of designing systems that efficiently and fairly manage limited resources among competing processes or threads.

The following C language tools are used in the program:

* **[Threading](https://en.wikipedia.org/wiki/Thread_(computing))**: The program uses the POSIX thread library (pthreads) to create parallel execution paths within the program. Each philosopher is implemented as a separate thread, symbolizing
their independent thought and action cycles.
* **[Mutexes](https://en.wikipedia.org/wiki/Lock_(computer_science))**: Short for "mutual exclusion," mutexes are used to prevent simultaneous access to a resource or a state by multiple threads of execution. In this project, POSIX mutexes ensure
that no more than one philosopher hold the same fork at the same time and to prevent output overlap.

The Dining Philosophers problem can be seen as an allegory for the allocation of resources within a society. It raises questions about ownership, communal resources versus individual needs, and the mechanisms of distribution. The mutexes represent
the control and regulation of resources, ensuring equitable access and preventing the monopolization of what is essentially a communal good.

### Implementation details

`pthread_create` is used to spawn threads representing each philosopher. Each thread simulates the philosopher's actions - thinking, picking up forks, eating, and putting down forks.
Before starting the threads, a mutex is initialized for each fork. This is crucial for preventing two philosophers from accessing the same fork simultaneously.
The lifecycle of a philosopher is implemented as a loop that represents cycles of thinking, attempting to pick up forks (locking the corresponding mutexes), eating, then releasing the forks (unlocking the mutexes).
To prevent deadlock and starvation, the basic approach chosen is the philosopher picking up the lower-numbered fork first, with some extensions.
To gracefully terminate the program, synchronization criteria are adopted, and there is the possibility to stop the simulation after a certain number of meals by introducing a certain input.

`pthread_create(&thread, NULL, philosopher_routine, &philosopher_id);` is the prototype used for thread creation, where `philosopher_routine` is the function each thread will execute, simulating the philosopher's actions.
`pthread_mutex_lock(&fork_mutex);` and `pthread_mutex_unlock(&fork_mutex);` for acquiring and releasing forks.

### Minimal considerations

The formal semantics of this code involve the principles of concurrent execution and resource allocation. The `pthread_create` function encapsulates the creation of a concurrent execution path, while `pthread_mutex_lock` and `pthread_mutex_unlock`
represent the exclusive access control to shared resources.
The mutexes ensure that the shared resources (forks) are not accessed by more than one thread at a time, analogous to the principle of mutual exclusivity observed in certain physical systems. The timing of operations, critical in avoiding
deadlocks and starvation, parallels concepts of synchronization and temporal coordination in physical interactions.

## Project Status

**General Status**: The program is at an early stage of development.

Friday 9 February 2024:

- The Wiki has now a home page, a license section and part of an introduction about main topics.
- Now a directory stores studies about some coding practices and notions to adopt in the project. In particular, a study about data races and a study about mutexes.

Saturday 10 February 2024:

- Established some milestones and general concepts about input checking and compilation.
- Added a Makefile, a header and a C file.

Sunday 11 February 2024:

- Completed the input checking functions, apart from some bugs.
- Updated the header to include useful headers for testing and some other contents for testing.

Monday 12 February 2024:

- Solved the bugs in the input checking functions.
- Updated the Makefile to run basic rules and make the program work. Updated the header file to define the source for POSIX extensions and include the pthread.h header.

Wednsday 14 February 2024:

- Added informations about the algorithm and about deadlock and starvation to the Wiki.

Thursday 15 February 2024:

- Updated the Wiki with explanations.
- Written some macros and variables representing the main resources of the program.

Friday 16 February 2024:

- Added the initializer of the timers and written part of the timer's routine.
- Fixed some bugs and inconsistencies.

Saturday 17 February 2024:

- Reviewed the code paths of the timer's routine.

Sunday 18 February 2024:

- Completed the timer.

Monday 19 February 2024:

- Concept development completed: started a preliminar debugging phase.

## Contributing

Contributions through forks are welcome.

## Acknowledgments

Thanks to the 42 Network for the learning experience related to the development of this program.

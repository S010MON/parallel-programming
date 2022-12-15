# OpenMP

Breaks code into multiple threads
```c
#pragma omp parallel
{
	// parallel code goes here
}

```


## Variable Scoping
OpenMP has a *private-list* and *shared-list* in the Parallel Region. General default is shared for Parallel Region, firstprivate for Tasks

### Private
Set `x` as a variable that is shared between all threads within the block
```c
int x;
#pragma omp task shared(x)
{
	// parallel code goes here
}
```


Set `b` as  private variable, where it has a copy for every thread (i.e. is just like `c`)
```c
int a, b;
#pragma omp parallel shared(a) private(b)
{
	int c;
}
```

- Non-static variables local to Parallel Regions are private
- Static variables are shared by default.
- Loop control variables on for-constructs are private
- `firstprivate` = Initialization with Master‘s value
- `lastprivate` = Value of last loop iteration is written back to Master


## The Barrier Construct
Threads wait until all threads of the current Team have reached the barrier
```c
#pragma omp barrier
```


## Internal Control Variables
The following variables are (some) of the variables available through OpenMP
```c
OMP_NUM_THREADS
OMP_NUM_TEAMS
```
They can be accessed using standard getters:
```c
omp_get_thread_num();
omp_get_num_threads();
omp_get_num_teams();
omp_get_wtime();
```

## Loop Parallelisation

This code has no loop dependencies, so it is paralleliseable
```c
#pragma omp parallel for
for ( i=0 ; i<100 ; i++ )
{
	a[i] = b[i] + c[i];
}
```

In this code, the calculation for `a[i]` depends on `a[i-1]` which means it cannot be parallelised in the case that `a[i-1]` has not been executed before `a[i]`
```c
#pragma omp parallel for
for ( i=1 ; i<100 ; i++ )
{
	a[i] = a[i] + a[i-1];
}
```

### Reductions
The reduction(+:a) means to sum all of the a values shared across the threads to
```c
int a = 0;

#pragma omp parallel
#pragma omp for reduction(+:a)
for (int i=0; i<100; i++)
{
	a+=i;
}
```

Possible reduction operations (with initialisation value):
```
+ (0),
* (1),
- (0),
& (~0),
| (0),
&& (1),
|| (0),
^ (0),
min (least number),
max (largest number)
```

## Syncronisation
A Critical Region is executed by all threads, but by only one thread simultaneously (Mutual Exclusion).
```c
#pragma omp critical (name)
{
	... structured block ...
}
```

```c
#pragma omp task wait
```

## The Single Construct
The single construct specifies that the enclosed structured block is executed by only on thread of the team.
```c
#pragma omp single[clause]
... structured block ...
```

## The Master Construct
The master construct specifies that the enclosed structured block is executed only by the master thread of a team. Note: The master construct is no worksharing construct and does not contain an implicit barrier at the end.
```c
#pragma omp master[clause]
... structured block ...
```

## The Sections Construct
The sections construct contains a set of structured blocks that are to be distributed among and executed by the team of threads.
```c
#pragma omp sections [clause]
{
	#pragma omp section
	... structured block ...
	#pragma omp section
	... structured block ...
...
}
```
Could be used for parallising multiple options (left/right branches of a binary tree)
```c
#pragma omp parallel sections
{
	#pragma omp section
	if (tree->left) 
		traverse(tree->left);
	
	#pragma omp section
	if (tree->right)
		traverse(tree->right);
} // end omp parallel
```

## The Ordered Construct
Allows a structured block to be executed within a parallel loop in sequential
order. In addition, an `ordered` clause has to be added to the `for` construct which any
ordered construct may occur (can be used to enfore order on printing data for example).  May also help to determine whether there is a data race.
```c
#pragma omp parallel for ordered
for (i=0 ; i<10 ; i++)
{
	...
	#pragma omp ordered
	{
		...
	}
	...
}
```

## Scheduling
### Static Scheduling
Breaks the work between all the threads before they are started (default setting
```c
#pragma omp ... schedule(static)
```

### Dynamic Scheduling
Provides only one (by default) process to each thread, and once complete they request a new task.  This adds lots of communication overhead but allows processes to be scheduled very dynamically
```c
#pragma omp ... schedule(dynamic)
```

### Guided
Sets a package size of n operations, where n is defined by OpenMP, and allocates each thread packages of n operations as they become available
```c
#pragma omp ... schedule(guided)
```

# MPI
http://www.open-mpi.org/

## Hello World Example
```c
#include <stdio.h>
#include <stdlib.h>

/*
* gcc -o hello hello.c
* ./hello
* mpiexec -np 3 ./hello
*/
int main(int argc, char* argv[])
{
	int MPI_Init(&argc, &argv)
	MPI_Comm_size(MPI_COMM_WORLD,&procCount);
	
	printf("Start[%d]/[%d]: Hello World\n",procRank,procCount
	
	int MPI_Finalize()
	return EXIT_SUCCESS;
}
```

## Process Handling

## Message Handling

## Data Handling

## IO Handling





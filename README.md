# OpenMP

Breaks code into multiple threads
```c
#pragma omp parallel
{
	...
}

```


## Variables

Set `x` as a variable that is shared between all threads within the block
```c
int x;
#pragma omp task shared(x)
{
	...
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


```c
#pragma omp task wait
```

```c
#pragma omp single
```


Creates a barrier between the above code to ensure it is finished?
```c
#pragma omp barrier
```

int CompareAndSwap(int *ptr, int expected, int new)
{
	int actual = *ptr;
	if (actual == expected)
		*ptr = new;
	return actual;
}

typedef struct lock_t {
	int flag;
} lock_t;

void init(lock_t *lock)
{
	// 0 -> lock is available, 1 -> held
	lock->flag = 0;
}

void lock(lock_t *lock)
{
	while (CompareAndSwap(&lock->flag, 0, 1) == 1)
		; // spin-wait (do nothing)
}

void unlock(lock_t *lock)
{
	lock->flag = 0;
}

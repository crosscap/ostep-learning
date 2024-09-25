int LoadLinked(int *ptr)
{
	return *ptr;
}

int StoreConditional(int *ptr, int value)
{
	if ("no one has updated *ptr scince the LoadLinked to this address") {
		*ptr = value;
		return 1; // success
	} else {
		return 0; // failed to update
	}
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
	while (1) {
		while (LoadLinked(&lock->flag) == 1)
			; // spin until it's zero
		if (StoreConditional(&lock->flag, 1) == 1)
			return; // if set-it-to-1 was success: all done
			        // otherwise: try it all over again
	}
	// equal to:
	// while (LoadLinked(&lock->flag) || !StoreConditional(&lock->flag, 1))
	// 	; // spin
}

void unlock(lock_t *lock)
{
	lock->flag = 0;
}

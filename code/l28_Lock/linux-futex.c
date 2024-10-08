void mutex_lock(int *mutex)
{
	int v;
	// Bit 31 was clear, we got the mutex (fastpath)
	if (atomic_bit_test_set(mutex, 31) == 0)
		return;
	atomic_increment(mutex);
	while (1) {
		if (atomic_bit_test_set(mutex, 31) == 0) {
			atomic_decrement(mutex);
			return;
		}
		// Have to waitFirst to make sure futex value
		// we are monitoring is negative (locked).
		v = *mutex;
		if (v >= 0)
			continue;
		futex_wait(mutex, v);
	}
}

void mutex_unlock(int *mutex)
{
	// Adding 0x80000000 to counter results in 0 if and
	// only if there are not other interested threads
	if (atomic_add_zero(mutex, 0x80000000))
		return;

	// There are other threads waiting for this mutex,
	// wake one of them up.
	futex_wake(mutex);
}

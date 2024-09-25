int flag;

void yield();

int TestAndSet(int *old_ptr, int new)
{
	int old = *old_ptr;
	*old_ptr = new;
	return old;
}

void init()
{
	flag = 0;
}

void lock()
{
	while (TestAndSet(&flag, 1) == 1)
		yield(); // give up the CPU
}

void unlock()
{
	flag = 0;
}

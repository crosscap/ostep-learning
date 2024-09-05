struct node_t
{
	int tickets;
	struct node_t *next;
};

int choose_a_process(int totaltickets, struct node_t *head)
{
	// counter: used to track if we've found the winner yet
	int counter = 0;

	// winner: use some call to a random number generator to
	//         get a value, between 0 and the total # of tickets
	int winner = getrandom(0, totaltickets);

	// current: use this to walk through the list of jobs
	struct node_t *current = head;

	// loop until the sum of ticket values is > the winner
	while (current)
	{
		counter = counter + current->tickets;
		if (counter > winner)
			break;
		current = current->next;
	}
	// 'current' is the winner: schedule it...

	return 0;
}

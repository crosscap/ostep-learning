typedef unsigned int size_t;
typedef size_t off_t;

struct aiocb {
	int aio_fildes;         // File descriptor
	off_t aio_offset;       // File offset
	volatile void *aio_buf; // Location of buffer
	size_t aio_nbytes;      // Length of transfer
};

int aio_read(struct aiocb *aiocbp);
int aio_error(const struct aiocb *aiocbp);

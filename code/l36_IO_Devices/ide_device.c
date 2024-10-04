#include "../include/common_threads.h"

// just make compiler can work you should find the right value for these functions
#define IDE_BSY 7
#define IDE_DRDY 6
#define B_DIRTY 6
#define B_VALID 7
#define IDE_CMD_WRITE 0x30
#define IDE_CMD_READ 0x20

int inb(int port);

pthread_mutex_t ide_lock = PTHREAD_MUTEX_INITIALIZER;

struct buf {
	int flags;
	unsigned int dev;
	unsigned int sector;
	struct buf *qnext;
	unsigned char data[512];
};

struct buf *ide_queue;

static int ide_wait_ready()
{
	int r;
	while (((r = inb(0x1f7)) & IDE_BSY) || !(r & IDE_DRDY))
		; // loop until drive isn't busy
}

static void ide_start_request(struct buf *b) {
	ide_wait_ready();
	outb(0x3f6, 0); // generate interrupt
	outb(0x1f2, 1); // how many sectors?
	outb(0x1f3, b->sector & 0xff); // LBA goes here ...
	outb(0x1f4, (b->sector >> 8) & 0xff); // ... and here
	outb(0x1f5, (b->sector >> 16) & 0xff); // ... and here!
	outb(0x1f6, 0xe0 | ((b->dev&1)<<4) | ((b->sector>>24)&0x0f));
	if(b->flags & B_DIRTY){
		outb(0x1f7, IDE_CMD_WRITE); // this is a WRITE
		outsl(0x1f0, b->data, 512/4); // transfer data too!
	} else {
		outb(0x1f7, IDE_CMD_READ); // this is a READ (no data)
	}
}

void ide_rw(struct buf *b)
{
	acquire(&ide_lock);
	struct buf **pp;

	for (pp = &ide_queue; *pp; pp=&(*pp)->qnext)
		; // walk queue
	*pp = b; // add request to end
	if (ide_queue == b) // if q is empty
		ide_start_request(b); // send req to disk
	while ((b->flags & (B_VALID|B_DIRTY)) != B_VALID)
		sleep(b, &ide_lock); // wait for completion
	release(&ide_lock);
}

void ide_intr()
{
	struct buf *b;
	acquire(&ide_lock);
	if (!(b->flags & B_DIRTY) && ide_wait_ready() >= 0)
		insl(0x1f0, b->data, 512/4); // if READ: get data
	b->flags |= B_VALID;
	b->flags &= ~B_DIRTY;
	wakeup(b); // wake waiting process
	if ((ide_queue = b->qnext) != 0) // start next request
		ide_start_request(ide_queue); // (if one exists)
	release(&ide_lock);
}

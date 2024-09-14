#include <stdlib.h>
#include <stdio.h>

#define VPN_MASK    0x30
#define OFFSET_MASK 0x1f
#define SHIFT       5

int pageTableBaseRegister = 1000;
typedef struct {
	int valid;
	int protect_bits;
	int page_frame_num;
} PTE;

int access_memory(int);
PTE access_memory_PTE(int);
int can_access(int);

int
page_translate(int virtual_address)
{
	int offset, phy_addr, to_register;
	int virtual_page_num = (virtual_address & VPN_MASK) << SHIFT;
	int PTE_addr = pageTableBaseRegister + virtual_page_num * (sizeof(PTE));
	PTE page_table_entry = access_memory_PTE(PTE_addr);
	if (!page_table_entry.valid) {
		fprintf(stderr, "SEGMENTATION_FAULT\n");
		exit(1);
	} else if (!can_access(page_table_entry.protect_bits)) {
		fprintf(stderr, "PROTECTION_FAULT\n");
		exit(1);
	} else {
		offset = virtual_address & OFFSET_MASK;
		phy_addr = (page_table_entry.page_frame_num << SHIFT) | offset;
		to_register = access_memory(phy_addr);
		return to_register;
	}
}
#include "lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
int main()
{
	unsigned char *disk_addresses = malloc(sizeof(char) * DISK_MEMORY);
	unsigned char *addresses = malloc(sizeof(char) * PHYSICAL_MEMORY);
	struct map_t *tlb;
	tlb = map_create();
	set_up_physical_memory(addresses);
	printf("%c\n", disk_addresses[0]);
	set_up_disk_memory(disk_addresses);
	add_extra_entry(addresses);
	start_system(addresses, disk_addresses, tlb);
	memset(disk_addresses, 0, DISK_MEMORY);
	memset(addresses, 0, PHYSICAL_MEMORY);

	free(disk_addresses);
	free(addresses);
	return 0;
}

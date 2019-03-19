// #include "lib/map_lib.h"

#include "lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memset */
int main()
{
	unsigned char *disk_addresses = malloc(sizeof(char) * DISK_MEMORY);
	unsigned char *addresses = malloc(sizeof(char) * PHYSICAL_MEMORY);
	struct map_t *tlb;
	tlb = map_create();
 map_set(tlb,"One","Won");
   map_set(tlb,"Two","Too");
   map_set(tlb,"Four","-");
      printf("%s %s\n","Fore",map_get(tlb,"Four"));

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

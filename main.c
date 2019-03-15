#include "lib/functions.h"
#include <stdio.h>

int main(){

	unsigned char * addresses = set_up_physical_memory();
	unsigned char * disk_addresses = set_up_disk_memory();
	add_extra_entry(addresses);
	start_system(addresses,disk_addresses);
	return 0;
}

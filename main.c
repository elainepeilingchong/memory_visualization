#include "lib/functions.h"
#include <stdio.h>

int main(){

	char * addresses = set_up_memory();
	start_system(addresses);
	return 0;
}

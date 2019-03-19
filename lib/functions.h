#ifndef FUNCTIONS_H
#define FUNCTIONS_H
// #define MAP_LIB_H

//define constant
#define BITMASK_LSB 0x1
#define BITMASK_MSB 0x80
#define OFFSET_BITS 8
#define PAGE_SIZE 256
#define MAX_BYTES 20480
#define MIN_BYTES 2048
#define PHYSICAL_MEMORY 65536
#define DISK_MEMORY 20480
#define SYS_BITS 16

typedef enum {
    false,
    true } bool;
typedef enum {
    LOW_ORDER_MASK,
    HIGH_ORDER_MASK
} mask_type;

struct map_t {
   struct map_t *nxt;
   char *name;
   char *value;
} ;

struct map_t *map_create();
void map_set(struct map_t *m, char *name, char *value);
char *map_get(struct map_t *m, char *name);


void set_up_physical_memory(unsigned char *addresses);
int calculateBitsRequired(void);
void start_system(unsigned char *addresses,unsigned char *disk_addresses,struct map_t *tlb);
void add_extra_entry(unsigned char *addresses);
void set_up_disk_memory(unsigned char *disk_addresses);
// void swap(char *addresses, char *disk_addresses);
void swap_replace(unsigned char  *addresses, unsigned char *disk_addresses, unsigned char pfn,unsigned char vpn );
void swap_empty(unsigned char *addresses, unsigned char *disk_addresses, unsigned char pfn,unsigned char vpn );


#endif 


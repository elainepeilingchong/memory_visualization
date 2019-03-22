#ifndef FUNCTIONS_H
#define FUNCTIONS_H
// #define MAP_LIB_H

//define constant

#define OFFSET_BITS 8
#define OFFSET_MASK 0x00FF
#define PAGE_SIZE 256
#define TOTAL_PAGE_NUMBER 256
#define MAX_BYTES 20480
#define MIN_BYTES 2048
#define PHYSICAL_MEMORY 65536
#define DISK_MEMORY 2048
#define SYS_BITS 16
// NUL
#define INITIAL_VALUE 0x00
// #define nullptr ((void*)0)

//FAULT
#define PAGE_FAULT "Page Fault Exception!!"
#define PROTECTION_FAULT "Protection Fault Exception!!"
#define SEGMENTATION_FAULT "Segmentation Fault Exception!!"
#define OUT_OF_BOUND_FAULT "Out of Bound Exception!!"


//MASK
#define PRESENT_BIT_MASK 0x01
#define VALID_BIT_SHIFT 1
#define ADDRESS_SHIFT 8
#define TRUE_BIT 0x01
#define FALSE_BIT 0x00

typedef enum
{
    false,
    true
} bool;

struct map_t
{
    struct map_t *nxt;
    char *name;
    char *value;
};

struct map_t *map_create();
void map_set(struct map_t *m, char *name, char *value);
char *map_get(struct map_t *m, char *name);

void set_up_physical_memory(unsigned char *addresses);
void set_up_disk_memory(unsigned char *disk_addresses);
void start_system(unsigned char *addresses, unsigned char *disk_addresses, struct map_t *tlb);
void add_extra_entry(unsigned char *addresses);
// void swap_replace(unsigned char *addresses, unsigned char *disk_addresses, unsigned char pfn, unsigned char vpn);
void swap_empty(unsigned char *addresses, unsigned char *disk_addresses, unsigned char pfn, unsigned char vpn);
void raise_exception(char *fault);
void print_separator();

#endif

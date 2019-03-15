#ifndef functions_h
#define functions_h

//define constant
#define BITMASK_LSB 0x1
#define BITMASK_MSB 0x80
#define OFFSET_BITS 8
#define PAGE_SIZE 256
#define MAX_BYTES 20480
#define MIN_BYTES 2048
#define ADDEESSABLE_MEMORY 65536
#define SYS_BITS 16

typedef enum {
    false,
    true } bool;
typedef enum {
    LOW_ORDER_MASK,
    HIGH_ORDER_MASK
} mask_type;
char * set_up_memory();
int calculateBitsRequired(void);
void start_system(char *addresses);


#endif 


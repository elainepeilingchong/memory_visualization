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
    LOW_ORDER_MASK,
    HIGH_ORDER_MASK
} mask_type;
typedef unsigned char  bit_t;
typedef unsigned short addr_t;

addr_t create_mask(bit_t, mask_type);

//declare functions
int calculateBitsRequired(void);

#endif 


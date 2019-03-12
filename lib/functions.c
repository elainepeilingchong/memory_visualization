#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
addr_t create_mask(bit_t bits, mask_type type) {
    addr_t mask   = 0;
    addr_t masker = type == LOW_ORDER_MASK? BITMASK_LSB: BITMASK_MSB;
    for (bit_t i = 0; i < bits; ++i) {
        mask |= masker;
        if (type == LOW_ORDER_MASK) {
            masker <<= 1;
        } else {
            masker >>= 1;
        }
    }
    
    return mask;
}
int calculateBitsRequired()
{
    int pageSizeBit = (int)(log((double)PAGE_SIZE) / log((double)2));
    return SYS_BITS - pageSizeBit;
}
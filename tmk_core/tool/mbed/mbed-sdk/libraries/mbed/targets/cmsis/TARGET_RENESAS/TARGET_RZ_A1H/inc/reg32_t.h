#ifndef __REG32_T
#define __REG32_T

union reg32_t {
    volatile uint32_t UINT32;
    volatile uint16_t UINT16[2];
    volatile uint8_t  UINT8[4];
};


#endif


#include <stdint.h>

typedef union {
    uint8_t reg[8];
} paw3204_all_reg;

uint8_t read_pid_paw3204();
void    init_paw3204();
int     read_paw3204(uint8_t *stat, int8_t *x, int8_t *y);
void    read_all_paw3204(paw3204_all_reg *dat);

#include "sf68.h"

void matrix_init_kb(void)
{
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    matrix_init_user();
}
void matrix_scan_kb(void)
{
    matrix_scan_user();
}

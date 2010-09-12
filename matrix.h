#include <stdbool.h>

extern uint8_t *matrix;
extern uint8_t *matrix_prev;

void matrix_init(void);
uint8_t matrix_scan(void);
bool matrix_is_modified(void);
bool matrix_has_ghost(void);
bool matrix_has_ghost_in_row(uint8_t row);

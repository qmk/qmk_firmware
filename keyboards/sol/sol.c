#include "sol.h"

#if defined(RGB_MATRIX_ENABLE)
uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) {
  if (row == 4 && column == 5) {
    led_i[0] = 33;
    return 1;
  } else if (row == 4 && column == 6) {
    led_i[0] = 34;
    return 1;
  } else if (row == 10 && column == 5) {
    led_i[0] = 68;
    return 1;
  } else if (row == 10 && column == 6) {
    led_i[0] = 69;
    return 1;
  }
  return 0;
}
#endif

#include "laptreus.h"

void matrix_init_kb() {
  // auto detect output on init
  #ifdef MODULE_ADAFRUIT_BLE
    uint8_t output = auto_detect_output();
    if (output == OUTPUT_USB) {
      set_output(OUTPUT_USB);
    } else {
      set_output(OUTPUT_BLUETOOTH);
    }
  #endif
}

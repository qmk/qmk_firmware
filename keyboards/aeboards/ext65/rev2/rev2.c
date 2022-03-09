#include "rev2.h"

// Tested and verified working on ext65rev2
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }

#ifdef OLED_ENABLE
void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
  SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_SPI2_DMA_RMP);
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // rotates the display 90 degrees
}

#else

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  // Set our LED pins as output
  setPinOutput(B4);
  setPinOutput(B3);
  setPinOutput(A15);
  setPinOutput(A14);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B4, led_state.num_lock);
        writePin(B3, led_state.caps_lock);
        writePin(A15, led_state.scroll_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case 1:
        writePinHigh(A14);
        break;
      default: //  for any other layers, or the default layer
        writePinLow(A14);
        break;
      }
    return layer_state_set_user(state);
}
#endif

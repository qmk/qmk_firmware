// Copyright 2025 Jakob Linke
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef ENCODER_ENABLE
static bool encoder_pins_are_initialized = false;  // Whether custom initialization ran.
static pin_t encoders_pad_a_l[] = ENCODER_A_PINS;
static pin_t encoders_pad_b_l[] = ENCODER_B_PINS;
static pin_t encoders_pad_a_r[] = ENCODER_A_PINS_RIGHT;
static pin_t encoders_pad_b_r[] = ENCODER_B_PINS_RIGHT;
static pin_t* encoders_pad_a = NULL;
static pin_t* encoders_pad_b = NULL;

// This function overrides the weak implementation in the core code.
void encoder_wait_pullup_charge(void) {
  wait_us(10);  // QMK is conservative and waits 100us.
}

// We use external pullups and thus have to implement custom initialization.
// This function overrides the weak implementation in the core code.
void encoder_quadrature_init_pin(uint8_t index, bool pad_b) {
  if (!encoder_pins_are_initialized) {
    // We cannot hook in earlier than this, so do side initialization here.
    static_assert(sizeof(encoders_pad_a_l) / sizeof(encoders_pad_a_l[0]) == 1);
    static_assert(sizeof(encoders_pad_b_l) / sizeof(encoders_pad_b_l[0]) == 1);
    static_assert(sizeof(encoders_pad_a_r) / sizeof(encoders_pad_a_r[0]) == 1);
    static_assert(sizeof(encoders_pad_b_r) / sizeof(encoders_pad_b_r[0]) == 1);
    encoders_pad_a = is_keyboard_left() ? encoders_pad_a_l : encoders_pad_a_r;
    encoders_pad_b = is_keyboard_left() ? encoders_pad_b_l : encoders_pad_b_r;
    encoder_pins_are_initialized = true;
  }
  assert(index == 0);
  pin_t pin = pad_b ? encoders_pad_b[index] : encoders_pad_a[index];
  assert(pin != NO_PIN);
  gpio_set_pin_input(pin);  // No pullup.
}

// Optimize by reading both pins at once.
// This function overrides the weak implementation in the core code.
void encoder_driver_task(void) {
  extern void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state);
  static const int i = 0;
  pin_t pin_a = encoders_pad_a[i];
  pin_t pin_b = encoders_pad_b[i];
  // Read both pins at the same time since they are on the same port.
  assert(PAL_PORT(pin_a) == PAL_PORT(pin_b));
  ioportmask_t port_state = palReadPort(PAL_PORT(pin_a));
  uint8_t pin_a_state, pin_b_state;
  pin_a_state = (port_state >> PAL_PAD(pin_a)) & 1;
  pin_b_state = (port_state >> PAL_PAD(pin_b)) & 1;
  encoder_quadrature_handle_read(i, pin_a_state, pin_b_state);
}
#endif

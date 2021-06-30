# Custom Userspace Function handlers

Specifically QMK works by using customized handlers for everything. This allows for multiple levels of customization. 

`matrix_scan` calls `matrix_scan_quantum`, which calls `matrix_scan_kb`, which calls `matrix_scan_user`. 
`process_record` calls a bunch of stuff, but eventually calls `process_record_kb` which calls `process_record_user`
The same goes for `matrix_init`, `layer_state_set`, `led_set`, and a few other functions.  

All (most) `_user` functions are handled here, in the userspace instead.  To allow keyboard specific configuration, I've created `_keymap` functions that can be called by the keymap.c files instead.

This allows for keyboard specific configuration while maintaining the ability to customize the board.

My [Ergodox EZ Keymap](https://github.com/qmk/qmk_firmware/blob/master/layouts/community/ergodox/drashna/keymap.c) is a good example of this, as it uses the LEDs as modifier indicators.

But for a list: 

```c
__attribute__ ((weak))
void matrix_init_keymap(void) {}

void matrix_init_user(void) {
  matrix_init_keymap();
}

__attribute__((weak))
void keyboard_post_init_keymap(void){ }

void keyboard_post_init_user(void){
    keyboard_post_init_keymap();
}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
  matrix_scan_keymap();
}


__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_keymap(keycode, record);
}


__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user (layer_state_t state) {
  return layer_state_set_keymap (state);
}


__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

void led_set_user(uint8_t usb_led) {
   led_set_keymap(usb_led);
}


__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
    suspend_power_down_keymap();
}


__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
  suspend_wakeup_init_keymap();
}


__attribute__ ((weak))
void shutdown_keymap(void) {}

void shutdown_user (void) {
  shutdown_keymap();
}

__attribute__ ((weak))
void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
  eeconfig_init_keymap();
}
```

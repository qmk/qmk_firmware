#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern void adafruit_ble_task(void);
extern bool adafruit_ble_send_keys(uint8_t hid_modifier_mask, uint8_t *keys, uint8_t nkeys);
extern bool adafruit_ble_is_connected(void);
extern bool adafruit_ble_send_consumer_key(uint16_t keycode, int hold_duration);

#ifdef MOUSE_ENABLE
extern bool adafruit_ble_send_mouse_move(int8_t x, int8_t y, int8_t scroll, int8_t pan, uint8_t buttons);
#endif

#ifdef __cplusplus
}
#endif

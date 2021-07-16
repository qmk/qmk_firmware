
#pragma once
#include <stdint.h>
#include "apidef.h"
#include "action.h"
#include "quantum_keycodes.h"

bool bmp_config_overwrite(bmp_api_config_t const *const config_on_storage,
                          bmp_api_config_t *const       keyboard_config);
void bmp_mode_transition_check(void);
void bmp_keyboard_task(void);
void bmp_init(void);

const bmp_api_config_t default_config;

const char *bmp_get_version_info();
bool        is_safe_mode();

void bmp_via_receive_cb(uint8_t *data, uint8_t length,
                        int (*raw_hid_send)(const uint8_t *data,
                                            uint8_t        length));

void eeprom_get_buffer_addr(
    uint8_t **buf,
    uint32_t *len);  // eeprom emulation for ble micro pro

bool process_record_user_bmp(uint16_t keycode, keyrecord_t *record);

bool get_ble_enabled();
void set_ble_enabled(bool enabled);
bool get_usb_enabled();
void set_usb_enabled(bool enabled);
void select_ble(void);
void select_usb(void);
bool is_ble_connected();
bool is_usb_connected();

extern int sleep_enter_counter;
extern int reset_counter;
void bmp_enter_sleep();
void bmp_before_sleep();


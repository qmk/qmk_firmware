
#pragma once
#include <stdint.h>
#include "apidef.h"
#include "action.h"
#include "quantum_keycodes.h"

void bmp_keyboard_task(void);
void bmp_init(void);

const char* bmp_get_version_info();
bool        is_safe_mode();

void eeprom_get_buffer_addr(uint8_t **buf, uint32_t *len); // eeprom emulation for blem

bool process_record_user_bmp(uint16_t keycode, keyrecord_t *record);

bool get_ble_enabled();
void set_ble_enabled(bool enabled);
bool get_usb_enabled();
void set_usb_enabled(bool enabled);


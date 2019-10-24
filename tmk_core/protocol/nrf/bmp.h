
#pragma once
#include <stdint.h>
#include "apidef.h"
#include "action.h"
#include "quantum_keycodes.h"

void bmp_keyboard_task(void);
void bmp_init(void);
bmp_error_t msc_write_callback(const uint8_t* dat, uint32_t len);

void eeprom_get_buffer_addr(uint8_t **buf, uint32_t *len);
int load_eeprom_emulation_file();
int save_eeprom_emulation_file();

int load_tapping_term_file();
int save_tapping_term_file();

int load_ex_keycode_file();
int save_ex_keycode_file();

bool process_record_user_bmp(uint16_t keycode, keyrecord_t *record);

bool get_ble_enabled();
void set_ble_enabled(bool enabled);
bool get_usb_enabled();
void set_usb_enabled(bool enabled);

uint32_t keymaps_len();

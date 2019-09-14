
#pragma once
#include <stdint.h>
#include "apidef.h"
#include "action.h"
#include "quantum_keycodes.h"

typedef struct {
  uint16_t start_kc;
  uint16_t end_kc;
  const char* key_strings;
} key_string_map_t;

enum bmp_custom_keycodes {
    BLE_DIS = SAFE_RANGE, /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    ADV_ID5,              /* Start advertising to PeerID 5        */
    ADV_ID6,              /* Start advertising to PeerID 6        */
    ADV_ID7,              /* Start advertising to PeerID 7        */
    AD_WO_L,              /* Start advertising without whitelist  */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    DEL_ID5,              /* Delete bonding of PeerID 5           */
    DEL_ID6,              /* Delete bonding of PeerID 6           */
    DEL_ID7,              /* Delete bonding of PeerID 7           */
    DELBNDS,              /* Delete all bonding                   */
    ENT_DFU,              /* Start bootloader                     */
    ENT_WEB,              /* Start web configurator               */
    ENT_SLP,              /* Deep sleep mode                      */
    BATT_LV,              /* Display battery level in milli volts */
    BMP_SAFE_RANGE        /* End of custom kecode                 */
};

void bmp_keyboard_task(void);
void bmp_init(void);
bmp_error_t msc_write_callback(const uint8_t* dat, uint32_t len);

void eeprom_get_buffer_addr(uint8_t **buf, uint32_t *len);
int load_eeprom_emulation_file();
int save_eeprom_emulation_file();

int load_tapping_term_file();
int save_tapping_term_file();

bool process_record_user_bmp(uint16_t keycode, keyrecord_t *record);

bool get_ble_enabled();
void set_ble_enabled(bool enabled);
bool get_usb_enabled();
void set_usb_enabled(bool enabled);

uint32_t keymaps_len();

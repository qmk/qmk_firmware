#include "ch.h"
#include "hal.h"
#include "annepro2.h"
#include "annepro2_ble.h"

static const SerialConfig ledUartConfig = {
  .speed = 115200,
};

static const SerialConfig bleUartConfig = {
  .speed = 115200,
};

static uint8_t ledMcuWakeup[11] = {
    0x7b, 0x10, 0x43, 0x10, 0x03, 0x00, 0x00, 0x7d, 0x02, 0x01, 0x02
};


uint16_t annepro2LedMatrix[MATRIX_ROWS * MATRIX_COLS] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void OVERRIDE keyboard_pre_init_kb(void) {
}

void OVERRIDE keyboard_post_init_kb(void) {
    // Start LED UART
    sdStart(&SD0, &ledUartConfig);
    sdWrite(&SD0, ledMcuWakeup, 11);

    // Start BLE UART
    sdStart(&SD1, &bleUartConfig);
    annepro2_ble_startup();

    keyboard_post_init_user();
}

void OVERRIDE matrix_init_kb(void) {
    matrix_init_user();
}

/*!
 * @returns false   processing for this keycode has been completed.
 */
bool OVERRIDE process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_AP2_BT1:
                annepro2_ble_broadcast(0);
                return false;
            case KC_AP2_BT2:
                annepro2_ble_broadcast(1);
                return false;
            case KC_AP2_BT3:
                annepro2_ble_broadcast(2);
                return false;
            case KC_AP2_BT4:
                annepro2_ble_broadcast(3);
                return false;
            case KC_AP2_USB:
                annepro2_ble_disconnect();
                return false;
            case KC_AP2_BT_UNPAIR:
                annepro2_ble_unpair();
                return false;
            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}

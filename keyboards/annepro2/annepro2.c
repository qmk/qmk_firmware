#include "ch.h"
#include "hal.h"
#include "annepro2.h"
#include "annepro2_ble.h"
#include "spi_master.h"
#include "qmk_ap2_led.h"

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
#if HAL_USE_SPI == TRUE
    spi_init();
#endif
}

void OVERRIDE keyboard_post_init_kb(void) {
    // Start LED UART
    sdStart(&SD0, &ledUartConfig);
    sdWrite(&SD0, ledMcuWakeup, 11);

    // wait to receive response from wakeup
    wait_ms(15);

    // loop to clear out receive buffer from shine wakeup
    while(!sdGetWouldBlock(&SD0))
        sdGet(&SD0);

    // Start BLE UART
    sdStart(&SD1, &bleUartConfig);
    annepro2_ble_startup();

    // Give the send uart thread some time to
    // send out the queue before we read back
    wait_ms(5);

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

            case KC_AP_LED_OFF:
                annepro2LedPrevProfile();
                annepro2LedDisable();
                break;

            case KC_AP_LED_ON:
                annepro2LedNextProfile();
                annepro2LedEnable();
                break;

            case KC_AP_LED_NEXT_PROFILE:
                annepro2LedNextProfile();
                break;

            case KC_AP_LED_PREV_PROFILE:
               annepro2LedPrevProfile();
                break;


            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}

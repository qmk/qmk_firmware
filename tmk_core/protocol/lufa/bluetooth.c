#include "bluetooth.h"

#ifdef MODULE_ADAFRUIT_BLE
#    include "adafruit_ble.h"
#else
#    include "bluetooth_classic.h"
#endif

bool bluetooth_is_connected(void) {
#ifdef MODULE_ADAFRUIT_BLE
    return adafruit_ble_is_connected();
#endif

    return true;  // should check if BT is connected here
}

void bluetooth_unpair() {
#ifdef MODULE_ADAFRUIT_BLE
    adafruit_ble_unpair();
#endif
}

void bluetooth_task(void) {
#ifdef MODULE_ADAFRUIT_BLE
    adafruit_ble_task();
#else
    bluetooth_classic_task();
#endif
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    if (!bluetooth_is_connected()) return;

#ifdef MODULE_ADAFRUIT_BLE
    adafruit_ble_send_keyboard(report);
#else
    bluetooth_classic_send_keyboard(report);
#endif
}

void bluetooth_send_consumer(uint16_t data, int hold_duration) {
    if (!bluetooth_is_connected()) return;

#ifdef MODULE_ADAFRUIT_BLE
    adafruit_ble_send_consumer(data, 0);
#elif MODULE_RN42
    bluetooth_classic_send_consumer(data, 0);
#endif
}

#ifdef MOUSE_ENABLE
void bluetooth_send_mouse(report_mouse_t *report) {
    if (!bluetooth_is_connected()) return;

#    ifdef MODULE_ADAFRUIT_BLE
    adafruit_ble_send_mouse(report);
#    else
    bluetooth_classic_send_mouse(report);
#    endif
}
#endif

#ifdef BLUETOOTH_BATTERY_ENABLE
uint8_t bluetooth_get_battery_level(void) { return bluetooth_get_battery_level_user(); }

__attribute__((weak)) uint8_t bluetooth_get_battery_level_user() { return 100; }
#endif

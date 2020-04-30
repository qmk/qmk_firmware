#include "BLE.h"
#include "lufa.h"
#include "print.h"

#ifdef MODULE_ADAFRUIT_BLE_UART
#    include "BluefruitLE_UART.h"
#elif MODULE_ADAFRUIT_BLE_SPI
// TODO
#endif

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#ifdef MOUSE_ENABLE
#    include "report.h"
#endif

#ifdef AdafruitBleBattery
#    include "BLEBattery.h"
#endif

#ifdef MODULE_ADAFRUIT_BLE_UART
static BluefruitLE_UART ble;
#elif MODULE_ADAFRUIT_BLE_SPI
// TODO
#endif

#ifdef AdafruitBleBattery
BLEBattery battery(ble);
#endif

static struct {
    bool    is_connected;
    bool    configured;
    int32_t connectable;
    uint8_t USB_DeviceState;
} state;

void connected(void) { state.is_connected = true; }

void disconnected(void) { state.is_connected = false; }

bool adafruit_ble_is_connected(void) { return state.is_connected; }

// we don't want bt enabled if we're using usb output. this is super annoying on
// phones, for example, when they will not show the on screen keyboard if a bt
// keyboard is connected.
bool set_connectable(bool v) {
    if (!!v == !!state.connectable) return true;
    state.connectable = v ? 1 : 0;
    return ble.atcommand(F("AT+GAPCONNECTABLE"), state.connectable);
}

bool ble_init() {
    state.configured      = false;
    state.is_connected    = false;
    state.connectable     = 1;
    state.USB_DeviceState = -1;

#ifdef MODULE_ADAFRUIT_BLE_UART
    if (!ble.begin(AdafruitBleBaud, AdafruitBleVerbose)) {
        return false;
    }
#elif MODULE_ADAFRUIT_BLE_SPI
// TODO
#endif

    if (!ble.echo(false)) return false;
    if (!ble.atcommand(F("AT+GAPINTERVALS"), "10,30,,")) return false;
    if (!ble.atcommand(F("AT+GAPDEVNAME"), STR(PRODUCT))) return false;
    if (!ble.atcommand(F("AT+BLEHIDEN"), 1)) return false;
    if (!ble.atcommand(F("AT+BLEPOWERLEVEL"), -12)) return false;

#ifdef AdafruitBleBattery
    if (!battery.begin(false)) return false;
#else
    // this setting persists across resets, so if we had the battery service
    // enabled, it will stay enabled even ifndef AdafruitBleBattery, so we
    // forcibly disable it here.
    if (!ble.atcommand(F("AT+BLEBATTEN=0"))) return false;
#endif

    if (!ble.reset()) return false;

    ble.setConnectCallback(connected);
    ble.setDisconnectCallback(disconnected);

    state.configured = true;
    return true;
}

#ifdef RGBLIGHT_ENABLE
void rgb_update() {
    if (USB_DeviceState == state.USB_DeviceState) return;

    state.USB_DeviceState = USB_DeviceState;

    switch (USB_DeviceState) {
        case DEVICE_STATE_Configured:
            // if rgb showed a solid, non-animated, color when the cord was
            // removed, since it doesn't need any timers, it won't turn on when
            // the cord is plugged back in. we'll fix that here.
            rgblight_restore_from_eeprom();
            break;
        default:
            // rgb already turns off when the cord is removed, since it loses
            // its required 5v, but qmk thinks it's still running. let's just
            // stop that.
            rgblight_disable_noeeprom();
    }
}
#endif

void adafruit_ble_task() {
    if (!state.configured && !ble_init()) return;

    // ensure bt is only available when not connected to usb
    set_connectable(USB_DeviceState != DEVICE_STATE_Configured);

#ifdef RGBLIGHT_ENABLE
    rgb_update();
#endif

    ble.update(200);

#ifdef AdafruitBleBattery
    // if you have a way of reading the battery level using analog inputs, you
    // can use that value as a percentage (uint8_t) here to update the bt
    // battery service value
    //
    // uint8_t percent = 50;
    // battery.update(percent);
#endif
}

bool adafruit_ble_send_keys(uint8_t hid_modifier_mask, uint8_t* keys, uint8_t nkeys) {
    char cmdbuf[48];
    char fmtbuf[64];

    strcpy_P(fmtbuf, PSTR("AT+BLEKEYBOARDCODE=%02x-00-%02x-%02x-%02x-%02x-%02x-%02x"));

    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, hid_modifier_mask, keys[0], nkeys >= 1 ? keys[1] : 0, nkeys >= 2 ? keys[2] : 0, nkeys >= 3 ? keys[3] : 0, nkeys >= 4 ? keys[4] : 0, nkeys >= 5 ? keys[5] : 0);

    return ble.atcommand(cmdbuf);
}

bool adafruit_ble_send_consumer_key(uint16_t keycode, int hold_duration) {
    char cmdbuf[48];
    char fmtbuf[64];

    strcpy_P(fmtbuf, PSTR("AT+BLEHIDCONTROLKEY=0x%04x"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, keycode);
    return ble.atcommand(cmdbuf);
}

#ifdef MOUSE_ENABLE
bool adafruit_ble_send_mouse_move(int8_t x, int8_t y, int8_t scroll, int8_t pan, uint8_t buttons) {
    char cmdbuf[48];
    char fmtbuf[64];

    strcpy_P(fmtbuf, PSTR("AT+BLEHIDMOUSEMOVE=%d,%d,%d,%d"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, x, y, scroll, pan);
    if (!ble.atcommand(cmdbuf)) {
        return false;
    }

    strcpy_P(cmdbuf, PSTR("AT+BLEHIDMOUSEBUTTON="));
    if (buttons & MOUSE_BTN1) strcat(cmdbuf, "L");
    if (buttons & MOUSE_BTN2) strcat(cmdbuf, "R");
    if (buttons & MOUSE_BTN3) strcat(cmdbuf, "M");
    if (buttons == 0) strcat(cmdbuf, "0");
    return ble.atcommand(cmdbuf);
}
#endif

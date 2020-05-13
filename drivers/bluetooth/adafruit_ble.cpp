#include "BLE.h"
#include "debug.h"
#include "outputselect.h"
#include "host_driver.h"
#include "bluetooth.h"

#ifdef MODULE_ADAFRUIT_BLE_UART
#    include "BluefruitLE_UART.h"
#elif MODULE_ADAFRUIT_BLE_SPI
#    include "BluefruitLE_SPI.h"
#endif

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#ifdef MOUSE_ENABLE
#    include "report.h"
#endif

#ifdef BLUETOOTH_BATTERY_ENABLE
#    include "BLEBattery.h"
#endif

#ifdef MODULE_ADAFRUIT_BLE_UART
static BluefruitLE_UART ble;
#elif MODULE_ADAFRUIT_BLE_SPI
static BluefruitLE_SPI ble;
#endif

#ifdef BLUETOOTH_BATTERY_ENABLE
BLEBattery battery(ble);
#endif

static struct {
    bool    is_connected;
    bool    configured;
    int32_t connectable;
    uint8_t USB_DeviceState;
} state;

void connected(void) {
    dprintf("adafruit ble connected\n");
    state.is_connected = true;
}

void disconnected(void) {
    dprintf("adafruit ble disconnected\n");
    state.is_connected = false;
}

bool bluetooth_is_connected(void) { return state.is_connected; }

bool reset() {
    if (!ble.reset(true)) return false;

    ble.setConnectCallback(connected);
    ble.setDisconnectCallback(disconnected);

    // This only works in SPIFRIEND firmware > 0.6.7, which is why
    // we check for this conditionally here.
    // Note that at the time of writing, HID reports only work correctly
    // with Apple products on firmware version 0.6.7!
    // https://forums.adafruit.com/viewtopic.php?f=8&t=104052
    if (!ble.usingEvents()) state.is_connected = true;

    return true;
}

// we don't want bt enabled if we're using usb output. this is super annoying on
// phones, for example, when they will not show the on screen keyboard if a bt
// keyboard is connected.
bool set_connectable(bool v) {
    if (state.connectable != -1 && !!v == !!state.connectable) return true;
    state.connectable = v ? 1 : 0;
    return ble.atcommand(F("AT+GAPCONNECTABLE"), state.connectable);
}

bool ble_init() {
    state.configured      = false;
    state.is_connected    = false;
    state.connectable     = -1;
    state.USB_DeviceState = -1;

    if (!ble.begin()) return false;

    if (!ble.echo(false)) return false;
    ble.atcommand(F("AT+GAPINTERVALS"), "10,30,,");
    if (!ble.atcommand(F("AT+GAPDEVNAME"), STR(PRODUCT))) return false;
    if (!ble.atcommand(F("AT+BLEHIDEN"), 1)) return false;
    ble.atcommand(F("AT+BLEPOWERLEVEL"), -12);

#ifdef BLUETOOTH_BATTERY_ENABLE
    if (!battery.begin(false)) return false;
#else
    // this setting persists across resets, so if we had the battery service
    // enabled, it will stay enabled even ifndef BLUETOOTH_BATTERY_ENABLE, so we
    // forcibly disable it here.
    ble.atcommand(F("AT+BLEBATTEN=0"));
#endif

    if (!reset()) return false;

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

void bluetooth_task() {
    if (!state.configured && !ble_init()) return;

    switch (where_to_send()) {
        case OUTPUT_NONE:
            if (output_auto()) {
                // if bluetooth is disconnected, where_to_send returns
                // OUTPUT_NONE but if the desired output is OUTPUT_AUTO then we
                // must make it possible to connect if usb is not connected
                set_connectable(USB_DeviceState != DEVICE_STATE_Configured);
                break;
            }

            set_connectable(false);
            break;
        case OUTPUT_USB:
            set_connectable(false);
            break;
        case OUTPUT_BLUETOOTH:
        case OUTPUT_USB_AND_BT:
            set_connectable(true);
            break;
    }

#ifdef RGBLIGHT_ENABLE
    rgb_update();
#endif

    ble.update(200);

#ifdef BLUETOOTH_BATTERY_ENABLE
    battery.update(bluetooth_get_battery_level());
#endif
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    char cmdbuf[48];
    char fmtbuf[64];

    uint8_t *     keys  = report->keys;
    const uint8_t nkeys = sizeof(keys);

    strcpy_P(fmtbuf, PSTR("AT+BLEKEYBOARDCODE=%02x-00-%02x-%02x-%02x-%02x-%02x-%02x"));

    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, report->mods, keys[0], nkeys >= 1 ? keys[1] : 0, nkeys >= 2 ? keys[2] : 0, nkeys >= 3 ? keys[3] : 0, nkeys >= 4 ? keys[4] : 0, nkeys >= 5 ? keys[5] : 0);

    ble.atcommand(cmdbuf);
}

void bluetooth_send_consumer(uint16_t keycode) {
    char cmdbuf[48];
    char fmtbuf[64];

    strcpy_P(fmtbuf, PSTR("AT+BLEHIDCONTROLKEY=0x%04x"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, keycode);
    ble.atcommand(cmdbuf);
}

#ifdef MOUSE_ENABLE
void bluetooth_send_mouse(report_mouse_t *report) {
    char cmdbuf[48];
    char fmtbuf[64];

    strcpy_P(fmtbuf, PSTR("AT+BLEHIDMOUSEMOVE=%d,%d,%d,%d"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, report->x, report->y, report->v, report->h);
    if (!ble.atcommand(cmdbuf)) {
        return;
    }

    strcpy_P(cmdbuf, PSTR("AT+BLEHIDMOUSEBUTTON="));
    if (report->buttons & MOUSE_BTN1) strcat(cmdbuf, "L");
    if (report->buttons & MOUSE_BTN2) strcat(cmdbuf, "R");
    if (report->buttons & MOUSE_BTN3) strcat(cmdbuf, "M");
    if (report->buttons == 0) strcat(cmdbuf, "0");
    ble.atcommand(cmdbuf);
}
#endif

void bluetooth_unpair(void) {
    set_connectable(false);
    if (!ble.atcommand(F("AT+GAPDELBONDS"))) return;
    reset();  // trigger a reset and reconfigure callbacks
}

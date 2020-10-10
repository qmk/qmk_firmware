#include "adafruit_ble.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include "host.h"
#include "protocol/serial.h"
#include "debug.h"
#include "timer.h"

#define TIMEOUT 100
#define ConnectionUpdateInterval 1000 /* milliseconds */

static struct {
    bool is_connected;
    bool initialized;
    bool configured;

    // #ifdef SAMPLE_BATTERY
    //     uint16_t last_battery_update;
    //     uint32_t vbat;
    // #endif
    uint16_t last_connection_update;
} state;

static bool ble51_init(void) {
    state.initialized  = false;
    state.configured   = false;
    state.is_connected = false;

    serial_init();

    state.initialized = true;
    return state.initialized;
}

static void ble51_gets(char *resp, uint16_t resplen, uint16_t timeout) {
    uint16_t t = timer_read();
    uint8_t  i = 0;
    int16_t  c;
    memset(resp, 0, resplen);
    while (i < resplen && timer_elapsed(t) < timeout) {
        if ((c = serial_recv2()) != -1) {
            if ((char)c == '\r') continue;
            if ((char)c == '\n') break;
            resp[i++] = c;
        }
    }
    resp[i] = '\0';
}

static bool ble51_get_ok(uint16_t timeout) {
    char ok[32];
    ble51_gets(ok, sizeof(ok), timeout);
    if (memcmp(ok, "OK", 2) == 0) {
        return true;
    }
    return false;
}

static void ble51_puts(const char *s) {
    while (*s) serial_send(*s++);
}

static bool at_command(const char *cmd, char *resp, uint16_t resplen) {
    dprint("Sending AT command: ");
    dprintf("%s\n", cmd);
    ble51_puts(cmd);
    ble51_puts("\n");
    if (resplen) {
        ble51_gets(resp, resplen, TIMEOUT);
        dprintf("Response: %s\n", resp);
        if (memcmp(resp, "ERROR", 5) == 0) {
            return false;
        }
        if (memcmp(resp, "OK", 2) == 0) {
            return true;
        }
    }
    return ble51_get_ok(TIMEOUT);
}

static bool at_command_P(const char *cmd, char *resp, uint16_t resplen) {
    char *cmdbuf = (char *)alloca(strlen_P(cmd) + 1);
    strcpy_P(cmdbuf, cmd);
    return at_command(cmdbuf, resp, resplen);
}

bool adafruit_ble_enable_keyboard(void) {
    char resbuf[128];

    if (!state.initialized && !ble51_init()) {
        return false;
    }

    state.configured = false;

    // Disable command echo
    static const char kEcho[] PROGMEM = "ATE=0";
    // Make the advertised name match the keyboard
    static const char kGapDevName[] PROGMEM = "AT+GAPDEVNAME=" STR(PRODUCT);
    // Turn on keyboard support
    static const char kHidEnOn[] PROGMEM = "AT+BLEHIDEN=1";

    // Adjust intervals to improve latency.  This causes the "central"
    // system (computer/tablet) to poll us every 10-30 ms.  We can't
    // set a smaller value than 10ms, and 30ms seems to be the natural
    // processing time on my macbook.  Keeping it constrained to that
    // feels reasonable to type to.
    static const char kGapIntervals[] PROGMEM = "AT+GAPINTERVALS=10,30,,";

    // Reset the device so that it picks up the above changes
    static const char kATZ[] PROGMEM = "ATZ";

    // Turn down the power level a bit
    static const char  kPower[] PROGMEM             = "AT+BLEPOWERLEVEL=-12";
    static PGM_P const configure_commands[] PROGMEM = {
        kEcho, kGapIntervals, kGapDevName, kHidEnOn, kPower, kATZ,
    };

    uint8_t i;
    for (i = 0; i < sizeof(configure_commands) / sizeof(configure_commands[0]); ++i) {
        PGM_P cmd;
        memcpy_P(&cmd, configure_commands + i, sizeof(cmd));

        if (!at_command_P(cmd, resbuf, sizeof(resbuf))) {
            dprintf("failed BLE command: %S: %s\n", cmd, resbuf);
            goto fail;
        }
    }

    state.configured = true;

    // Check connection status in a little while; allow the ATZ time
    // to kick in.
    state.last_connection_update = timer_read();
fail:
    return state.configured;
}

bool adafruit_ble_is_connected() { return state.is_connected; }

static void set_connected(bool connected) {
    if (connected != state.is_connected) {
        if (connected) {
            dprint("****** BLE CONNECT!!!!\n");
        } else {
            dprint("****** BLE DISCONNECT!!!!\n");
        }
        state.is_connected = connected;
    }
}

void adafruit_ble_task(void) {
    char resbuf[48];

    if (!state.configured && !adafruit_ble_enable_keyboard()) {
        return;
    }
    if (timer_elapsed(state.last_connection_update) > ConnectionUpdateInterval) {
        static const char kGetConn[] PROGMEM = "AT+GAPGETCONN";
        state.last_connection_update         = timer_read();

        if (at_command_P(kGetConn, resbuf, sizeof(resbuf))) {
            set_connected(atoi(resbuf));
        }
    }
}

bool adafruit_ble_send_keys(uint8_t hid_modifier_mask, uint8_t *keys, uint8_t nkeys) {
    if (!state.configured || !state.is_connected) {
        return false;
    }
    char cmdbuf[48];
    char fmtbuf[64];
    strcpy_P(fmtbuf, PSTR("AT+BLEKEYBOARDCODE=%02x-00-%02x-%02x-%02x-%02x-%02x-%02x"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, hid_modifier_mask, keys[0], nkeys >= 1 ? keys[1] : 0, nkeys >= 2 ? keys[2] : 0, nkeys >= 3 ? keys[3] : 0, nkeys >= 4 ? keys[4] : 0, nkeys >= 5 ? keys[5] : 0);
    return at_command(cmdbuf, NULL, 0);
}

bool adafruit_ble_send_consumer_key(uint16_t keycode, int hold_duration) {
    if (!state.configured || !state.is_connected) {
        return false;
    }
    char cmdbuf[48];
    char fmtbuf[64];
    strcpy_P(fmtbuf, PSTR("AT+BLEHIDCONTROLKEY=%d"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, keycode);
    return at_command(cmdbuf, NULL, 0);
}

#ifdef MOUSE_ENABLE
bool adafruit_ble_send_mouse_move(int8_t x, int8_t y, int8_t scroll, int8_t pan, uint8_t buttons) {
    if (!state.configured || !state.is_connected) {
        return false;
    }
    char cmdbuf[48];
    char fmtbuf[64];
    strcpy_P(fmtbuf, PSTR("AT+BLEHIDMOUSEMOVE=%d,%d,%d,%d"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, x, y, scroll, pan);
    if (!at_command(cmdbuf, NULL, 0)) {
        return false;
    }
    strcpy_P(fmtbuf, PSTR("AT+BLEHIDMOUSEBUTTON=%d"));
    snprintf(cmdbuf, sizeof(cmdbuf), fmtbuf, buttons);
    return at_command(cmdbuf, NULL, 0);
}
#endif

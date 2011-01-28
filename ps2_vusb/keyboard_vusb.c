#include "usbdrv.h"
#include "usb_keycodes.h"
#include "keyboard.h"
#include "print.h"

static report_t report0;
static report_t report1;
static report_t *report = &report0;
static report_t *report_prev = &report1;

void report_send(void)
{
    if (usbInterruptIsReady()){
        usbSetInterrupt((void *)report, sizeof(*report));
    }
}

report_t *report_get(void)
{
    return report;
}

uint8_t report_mods(void)
{
    return report->mods;
}

uint8_t *report_keys(void)
{
    return report->keys;
}

bool report_has_key(void)
{
    for (int i = 0; i < REPORT_KEYS; i++) {
        if (report->keys[i])
            return true;
    }
    return false;
}

void report_add_mod(uint8_t mod)
{
    report->mods |= mod;
}

void report_add_key(uint8_t code)
{
    int8_t i = 0;
    int8_t empty = -1;
    for (; i < REPORT_KEYS; i++) {
        if (report_prev->keys[i] == code) {
            report->keys[i] = code;
            break;
        }
        if (empty == -1 && report_prev->keys[i] == KB_NO && report->keys[i] == KB_NO) {
            empty = i;
        }
    }
    if (i == REPORT_KEYS && empty != -1) {
        report->keys[empty] = code;
    }
}

void report_add_code(uint8_t code)
{
    if (IS_MOD(code)) {
        report_add_mod(code);
    } else {
        report_add_key(code);
    }
}

void report_swap(void)
{
    report_t *tmp = report_prev;
    report_prev = report;
    report = tmp;
}

void report_clear(void)
{
    report->mods = 0;
    for (int8_t i = 0; i < REPORT_KEYS; i++) {
        report->keys[i] = 0;
    }
}


static uchar    idleRate;   /* repeat rate for keyboards, never used for mice */
usbMsgLen_t usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;

    print("Setup: ");
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        print("CLASS: ");
        phex(rq->bRequest);
        if(rq->bRequest == USBRQ_HID_GET_REPORT){
            print("GET_REPORT");
            /* we only have one report type, so don't look at wValue */
            usbMsgPtr = (void *)report;
            return sizeof(*report);
        }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            print("GET_IDLE: ");
            phex(idleRate);
            usbMsgPtr = &idleRate;
            return 1;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
            print("SET_IDLE: ");
            phex(idleRate);
        }
        print("\n");
    }else{
        print("VENDOR\n");
        /* no vendor specific requests implemented */
    }
    return 0;   /* default for not implemented requests: return no data back to host */
}


PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    0x05, 0x01,          // Usage Page (Generic Desktop),
    0x09, 0x06,          // Usage (Keyboard),
    0xA1, 0x01,          // Collection (Application),
    0x75, 0x01,          //   Report Size (1),
    0x95, 0x08,          //   Report Count (8),
    0x05, 0x07,          //   Usage Page (Key Codes),
    0x19, 0xE0,          //   Usage Minimum (224),
    0x29, 0xE7,          //   Usage Maximum (231),
    0x15, 0x00,          //   Logical Minimum (0),
    0x25, 0x01,          //   Logical Maximum (1),
    0x81, 0x02,          //   Input (Data, Variable, Absolute), ;Modifier byte
    0x95, 0x01,          //   Report Count (1),
    0x75, 0x08,          //   Report Size (8),
    0x81, 0x03,          //   Input (Constant),                 ;Reserved byte
    0x95, 0x05,          //   Report Count (5),
    0x75, 0x01,          //   Report Size (1),
    0x05, 0x08,          //   Usage Page (LEDs),
    0x19, 0x01,          //   Usage Minimum (1),
    0x29, 0x05,          //   Usage Maximum (5),
    0x91, 0x02,          //   Output (Data, Variable, Absolute), ;LED report
    0x95, 0x01,          //   Report Count (1),
    0x75, 0x03,          //   Report Size (3),
    0x91, 0x03,          //   Output (Constant),                 ;LED report padding
    0x95, 0x06,          //   Report Count (6),
    0x75, 0x08,          //   Report Size (8),
    0x15, 0x00,          //   Logical Minimum (0),
    0x25, 0xFF,          //   Logical Maximum(255),
    0x05, 0x07,          //   Usage Page (Key Codes),
    0x19, 0x00,          //   Usage Minimum (0),
    0x29, 0xFF,          //   Usage Maximum (255),
    0x81, 0x00,          //   Input (Data, Array),
    0xc0                 // End Collection
};

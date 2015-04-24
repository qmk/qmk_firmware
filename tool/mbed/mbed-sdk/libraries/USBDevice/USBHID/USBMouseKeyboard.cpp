/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "stdint.h"
#include "USBMouseKeyboard.h"

typedef struct {
    unsigned char usage;
    unsigned char modifier;
} KEYMAP;

#ifdef US_KEYBOARD
/* US keyboard (as HID standard) */
#define KEYMAP_SIZE (152)
const KEYMAP keymap[KEYMAP_SIZE] = {
    {0, 0},             /* NUL */
    {0, 0},             /* SOH */
    {0, 0},             /* STX */
    {0, 0},             /* ETX */
    {0, 0},             /* EOT */
    {0, 0},             /* ENQ */
    {0, 0},             /* ACK */
    {0, 0},             /* BEL */
    {0x2a, 0},          /* BS  */  /* Keyboard Delete (Backspace) */
    {0x2b, 0},          /* TAB */  /* Keyboard Tab */
    {0x28, 0},          /* LF  */  /* Keyboard Return (Enter) */
    {0, 0},             /* VT  */
    {0, 0},             /* FF  */
    {0, 0},             /* CR  */
    {0, 0},             /* SO  */
    {0, 0},             /* SI  */
    {0, 0},             /* DEL */
    {0, 0},             /* DC1 */
    {0, 0},             /* DC2 */
    {0, 0},             /* DC3 */
    {0, 0},             /* DC4 */
    {0, 0},             /* NAK */
    {0, 0},             /* SYN */
    {0, 0},             /* ETB */
    {0, 0},             /* CAN */
    {0, 0},             /* EM  */
    {0, 0},             /* SUB */
    {0, 0},             /* ESC */
    {0, 0},             /* FS  */
    {0, 0},             /* GS  */
    {0, 0},             /* RS  */
    {0, 0},             /* US  */
    {0x2c, 0},          /*   */
    {0x1e, KEY_SHIFT},      /* ! */
    {0x34, KEY_SHIFT},      /* " */
    {0x20, KEY_SHIFT},      /* # */
    {0x21, KEY_SHIFT},      /* $ */
    {0x22, KEY_SHIFT},      /* % */
    {0x24, KEY_SHIFT},      /* & */
    {0x34, 0},          /* ' */
    {0x26, KEY_SHIFT},      /* ( */
    {0x27, KEY_SHIFT},      /* ) */
    {0x25, KEY_SHIFT},      /* * */
    {0x2e, KEY_SHIFT},      /* + */
    {0x36, 0},          /* , */
    {0x2d, 0},          /* - */
    {0x37, 0},          /* . */
    {0x38, 0},          /* / */
    {0x27, 0},          /* 0 */
    {0x1e, 0},          /* 1 */
    {0x1f, 0},          /* 2 */
    {0x20, 0},          /* 3 */
    {0x21, 0},          /* 4 */
    {0x22, 0},          /* 5 */
    {0x23, 0},          /* 6 */
    {0x24, 0},          /* 7 */
    {0x25, 0},          /* 8 */
    {0x26, 0},          /* 9 */
    {0x33, KEY_SHIFT},      /* : */
    {0x33, 0},          /* ; */
    {0x36, KEY_SHIFT},      /* < */
    {0x2e, 0},          /* = */
    {0x37, KEY_SHIFT},      /* > */
    {0x38, KEY_SHIFT},      /* ? */
    {0x1f, KEY_SHIFT},      /* @ */
    {0x04, KEY_SHIFT},      /* A */
    {0x05, KEY_SHIFT},      /* B */
    {0x06, KEY_SHIFT},      /* C */
    {0x07, KEY_SHIFT},      /* D */
    {0x08, KEY_SHIFT},      /* E */
    {0x09, KEY_SHIFT},      /* F */
    {0x0a, KEY_SHIFT},      /* G */
    {0x0b, KEY_SHIFT},      /* H */
    {0x0c, KEY_SHIFT},      /* I */
    {0x0d, KEY_SHIFT},      /* J */
    {0x0e, KEY_SHIFT},      /* K */
    {0x0f, KEY_SHIFT},      /* L */
    {0x10, KEY_SHIFT},      /* M */
    {0x11, KEY_SHIFT},      /* N */
    {0x12, KEY_SHIFT},      /* O */
    {0x13, KEY_SHIFT},      /* P */
    {0x14, KEY_SHIFT},      /* Q */
    {0x15, KEY_SHIFT},      /* R */
    {0x16, KEY_SHIFT},      /* S */
    {0x17, KEY_SHIFT},      /* T */
    {0x18, KEY_SHIFT},      /* U */
    {0x19, KEY_SHIFT},      /* V */
    {0x1a, KEY_SHIFT},      /* W */
    {0x1b, KEY_SHIFT},      /* X */
    {0x1c, KEY_SHIFT},      /* Y */
    {0x1d, KEY_SHIFT},      /* Z */
    {0x2f, 0},          /* [ */
    {0x31, 0},          /* \ */
    {0x30, 0},          /* ] */
    {0x23, KEY_SHIFT},      /* ^ */
    {0x2d, KEY_SHIFT},      /* _ */
    {0x35, 0},          /* ` */
    {0x04, 0},          /* a */
    {0x05, 0},          /* b */
    {0x06, 0},          /* c */
    {0x07, 0},          /* d */
    {0x08, 0},          /* e */
    {0x09, 0},          /* f */
    {0x0a, 0},          /* g */
    {0x0b, 0},          /* h */
    {0x0c, 0},          /* i */
    {0x0d, 0},          /* j */
    {0x0e, 0},          /* k */
    {0x0f, 0},          /* l */
    {0x10, 0},          /* m */
    {0x11, 0},          /* n */
    {0x12, 0},          /* o */
    {0x13, 0},          /* p */
    {0x14, 0},          /* q */
    {0x15, 0},          /* r */
    {0x16, 0},          /* s */
    {0x17, 0},          /* t */
    {0x18, 0},          /* u */
    {0x19, 0},          /* v */
    {0x1a, 0},          /* w */
    {0x1b, 0},          /* x */
    {0x1c, 0},          /* y */
    {0x1d, 0},          /* z */
    {0x2f, KEY_SHIFT},      /* { */
    {0x31, KEY_SHIFT},      /* | */
    {0x30, KEY_SHIFT},      /* } */
    {0x35, KEY_SHIFT},      /* ~ */
    {0,0},              /* DEL */

    {0x3a, 0},          /* F1 */
    {0x3b, 0},          /* F2 */
    {0x3c, 0},          /* F3 */
    {0x3d, 0},          /* F4 */
    {0x3e, 0},          /* F5 */
    {0x3f, 0},          /* F6 */
    {0x40, 0},          /* F7 */
    {0x41, 0},          /* F8 */
    {0x42, 0},          /* F9 */
    {0x43, 0},          /* F10 */
    {0x44, 0},          /* F11 */
    {0x45, 0},          /* F12 */

    {0x46, 0},          /* PRINT_SCREEN */
    {0x47, 0},          /* SCROLL_LOCK */
    {0x39, 0},          /* CAPS_LOCK */
    {0x53, 0},          /* NUM_LOCK */
    {0x49, 0},          /* INSERT */
    {0x4a, 0},          /* HOME */
    {0x4b, 0},          /* PAGE_UP */
    {0x4e, 0},          /* PAGE_DOWN */

    {0x4f, 0},          /* RIGHT_ARROW */
    {0x50, 0},          /* LEFT_ARROW */
    {0x51, 0},          /* DOWN_ARROW */
    {0x52, 0},          /* UP_ARROW */
};

#else
/* UK keyboard */
#define KEYMAP_SIZE (152)
const KEYMAP keymap[KEYMAP_SIZE] = {
    {0, 0},             /* NUL */
    {0, 0},             /* SOH */
    {0, 0},             /* STX */
    {0, 0},             /* ETX */
    {0, 0},             /* EOT */
    {0, 0},             /* ENQ */
    {0, 0},             /* ACK */
    {0, 0},             /* BEL */
    {0x2a, 0},          /* BS  */  /* Keyboard Delete (Backspace) */
    {0x2b, 0},          /* TAB */  /* Keyboard Tab */
    {0x28, 0},          /* LF  */  /* Keyboard Return (Enter) */
    {0, 0},             /* VT  */
    {0, 0},             /* FF  */
    {0, 0},             /* CR  */
    {0, 0},             /* SO  */
    {0, 0},             /* SI  */
    {0, 0},             /* DEL */
    {0, 0},             /* DC1 */
    {0, 0},             /* DC2 */
    {0, 0},             /* DC3 */
    {0, 0},             /* DC4 */
    {0, 0},             /* NAK */
    {0, 0},             /* SYN */
    {0, 0},             /* ETB */
    {0, 0},             /* CAN */
    {0, 0},             /* EM  */
    {0, 0},             /* SUB */
    {0, 0},             /* ESC */
    {0, 0},             /* FS  */
    {0, 0},             /* GS  */
    {0, 0},             /* RS  */
    {0, 0},             /* US  */
    {0x2c, 0},          /*   */
    {0x1e, KEY_SHIFT},      /* ! */
    {0x1f, KEY_SHIFT},      /* " */
    {0x32, 0},          /* # */
    {0x21, KEY_SHIFT},      /* $ */
    {0x22, KEY_SHIFT},      /* % */
    {0x24, KEY_SHIFT},      /* & */
    {0x34, 0},          /* ' */
    {0x26, KEY_SHIFT},      /* ( */
    {0x27, KEY_SHIFT},      /* ) */
    {0x25, KEY_SHIFT},      /* * */
    {0x2e, KEY_SHIFT},      /* + */
    {0x36, 0},          /* , */
    {0x2d, 0},          /* - */
    {0x37, 0},          /* . */
    {0x38, 0},          /* / */
    {0x27, 0},          /* 0 */
    {0x1e, 0},          /* 1 */
    {0x1f, 0},          /* 2 */
    {0x20, 0},          /* 3 */
    {0x21, 0},          /* 4 */
    {0x22, 0},          /* 5 */
    {0x23, 0},          /* 6 */
    {0x24, 0},          /* 7 */
    {0x25, 0},          /* 8 */
    {0x26, 0},          /* 9 */
    {0x33, KEY_SHIFT},      /* : */
    {0x33, 0},          /* ; */
    {0x36, KEY_SHIFT},      /* < */
    {0x2e, 0},          /* = */
    {0x37, KEY_SHIFT},      /* > */
    {0x38, KEY_SHIFT},      /* ? */
    {0x34, KEY_SHIFT},      /* @ */
    {0x04, KEY_SHIFT},      /* A */
    {0x05, KEY_SHIFT},      /* B */
    {0x06, KEY_SHIFT},      /* C */
    {0x07, KEY_SHIFT},      /* D */
    {0x08, KEY_SHIFT},      /* E */
    {0x09, KEY_SHIFT},      /* F */
    {0x0a, KEY_SHIFT},      /* G */
    {0x0b, KEY_SHIFT},      /* H */
    {0x0c, KEY_SHIFT},      /* I */
    {0x0d, KEY_SHIFT},      /* J */
    {0x0e, KEY_SHIFT},      /* K */
    {0x0f, KEY_SHIFT},      /* L */
    {0x10, KEY_SHIFT},      /* M */
    {0x11, KEY_SHIFT},      /* N */
    {0x12, KEY_SHIFT},      /* O */
    {0x13, KEY_SHIFT},      /* P */
    {0x14, KEY_SHIFT},      /* Q */
    {0x15, KEY_SHIFT},      /* R */
    {0x16, KEY_SHIFT},      /* S */
    {0x17, KEY_SHIFT},      /* T */
    {0x18, KEY_SHIFT},      /* U */
    {0x19, KEY_SHIFT},      /* V */
    {0x1a, KEY_SHIFT},      /* W */
    {0x1b, KEY_SHIFT},      /* X */
    {0x1c, KEY_SHIFT},      /* Y */
    {0x1d, KEY_SHIFT},      /* Z */
    {0x2f, 0},          /* [ */
    {0x64, 0},          /* \ */
    {0x30, 0},          /* ] */
    {0x23, KEY_SHIFT},      /* ^ */
    {0x2d, KEY_SHIFT},      /* _ */
    {0x35, 0},          /* ` */
    {0x04, 0},          /* a */
    {0x05, 0},          /* b */
    {0x06, 0},          /* c */
    {0x07, 0},          /* d */
    {0x08, 0},          /* e */
    {0x09, 0},          /* f */
    {0x0a, 0},          /* g */
    {0x0b, 0},          /* h */
    {0x0c, 0},          /* i */
    {0x0d, 0},          /* j */
    {0x0e, 0},          /* k */
    {0x0f, 0},          /* l */
    {0x10, 0},          /* m */
    {0x11, 0},          /* n */
    {0x12, 0},          /* o */
    {0x13, 0},          /* p */
    {0x14, 0},          /* q */
    {0x15, 0},          /* r */
    {0x16, 0},          /* s */
    {0x17, 0},          /* t */
    {0x18, 0},          /* u */
    {0x19, 0},          /* v */
    {0x1a, 0},          /* w */
    {0x1b, 0},          /* x */
    {0x1c, 0},          /* y */
    {0x1d, 0},          /* z */
    {0x2f, KEY_SHIFT},      /* { */
    {0x64, KEY_SHIFT},      /* | */
    {0x30, KEY_SHIFT},      /* } */
    {0x32, KEY_SHIFT},      /* ~ */
    {0,0},             /* DEL */

    {0x3a, 0},          /* F1 */
    {0x3b, 0},          /* F2 */
    {0x3c, 0},          /* F3 */
    {0x3d, 0},          /* F4 */
    {0x3e, 0},          /* F5 */
    {0x3f, 0},          /* F6 */
    {0x40, 0},          /* F7 */
    {0x41, 0},          /* F8 */
    {0x42, 0},          /* F9 */
    {0x43, 0},          /* F10 */
    {0x44, 0},          /* F11 */
    {0x45, 0},          /* F12 */

    {0x46, 0},          /* PRINT_SCREEN */
    {0x47, 0},          /* SCROLL_LOCK */
    {0x39, 0},          /* CAPS_LOCK */
    {0x53, 0},          /* NUM_LOCK */
    {0x49, 0},          /* INSERT */
    {0x4a, 0},          /* HOME */
    {0x4b, 0},          /* PAGE_UP */
    {0x4e, 0},          /* PAGE_DOWN */

    {0x4f, 0},          /* RIGHT_ARROW */
    {0x50, 0},          /* LEFT_ARROW */
    {0x51, 0},          /* DOWN_ARROW */
    {0x52, 0},          /* UP_ARROW */
};
#endif


uint8_t * USBMouseKeyboard::reportDesc() {
    if (mouse_type == REL_MOUSE) {
        static uint8_t reportDescriptor[] = {
                // Keyboard
                USAGE_PAGE(1),      0x01,
                USAGE(1),           0x06,
                COLLECTION(1),      0x01,
                REPORT_ID(1),       REPORT_ID_KEYBOARD,
                USAGE_PAGE(1),      0x07,
                USAGE_MINIMUM(1),       0xE0,
                USAGE_MAXIMUM(1),       0xE7,
                LOGICAL_MINIMUM(1),     0x00,
                LOGICAL_MAXIMUM(1),     0x01,
                REPORT_SIZE(1),     0x01,
                REPORT_COUNT(1),    0x08,
                INPUT(1),           0x02,
                REPORT_COUNT(1),    0x01,
                REPORT_SIZE(1),     0x08,
                INPUT(1),           0x01,
                REPORT_COUNT(1),    0x05,
                REPORT_SIZE(1),     0x01,
                USAGE_PAGE(1),      0x08,
                USAGE_MINIMUM(1),       0x01,
                USAGE_MAXIMUM(1),       0x05,
                OUTPUT(1),          0x02,
                REPORT_COUNT(1),    0x01,
                REPORT_SIZE(1),     0x03,
                OUTPUT(1),          0x01,
                REPORT_COUNT(1),    0x06,
                REPORT_SIZE(1),     0x08,
                LOGICAL_MINIMUM(1),     0x00,
                LOGICAL_MAXIMUM(2),     0xff, 0x00,
                USAGE_PAGE(1),      0x07,
                USAGE_MINIMUM(1),       0x00,
                USAGE_MAXIMUM(2),       0xff, 0x00,
                INPUT(1),           0x00,
                END_COLLECTION(0),

                // Mouse
                USAGE_PAGE(1),      0x01,           // Generic Desktop
                USAGE(1),           0x02,           // Mouse
                COLLECTION(1),      0x01,           // Application
                USAGE(1),           0x01,           // Pointer
                COLLECTION(1),      0x00,           // Physical
                REPORT_ID(1),       REPORT_ID_MOUSE,
                REPORT_COUNT(1),    0x03,
                REPORT_SIZE(1),     0x01,
                USAGE_PAGE(1),      0x09,           // Buttons
                USAGE_MINIMUM(1),       0x1,
                USAGE_MAXIMUM(1),       0x3,
                LOGICAL_MINIMUM(1),     0x00,
                LOGICAL_MAXIMUM(1),     0x01,
                INPUT(1),           0x02,
                REPORT_COUNT(1),    0x01,
                REPORT_SIZE(1),     0x05,
                INPUT(1),           0x01,
                REPORT_COUNT(1),    0x03,
                REPORT_SIZE(1),     0x08,
                USAGE_PAGE(1),      0x01,
                USAGE(1),           0x30,           // X
                USAGE(1),           0x31,           // Y
                USAGE(1),           0x38,           // scroll
                LOGICAL_MINIMUM(1),     0x81,
                LOGICAL_MAXIMUM(1),     0x7f,
                INPUT(1),           0x06,
                END_COLLECTION(0),
                END_COLLECTION(0),


                // Media Control
                USAGE_PAGE(1), 0x0C,
                USAGE(1), 0x01,
                COLLECTION(1), 0x01,
                REPORT_ID(1), REPORT_ID_VOLUME,
                USAGE_PAGE(1), 0x0C,
                LOGICAL_MINIMUM(1), 0x00,
                LOGICAL_MAXIMUM(1), 0x01,
                REPORT_SIZE(1), 0x01,
                REPORT_COUNT(1), 0x07,
                USAGE(1), 0xB5,             // Next Track
                USAGE(1), 0xB6,             // Previous Track
                USAGE(1), 0xB7,             // Stop
                USAGE(1), 0xCD,             // Play / Pause
                USAGE(1), 0xE2,             // Mute
                USAGE(1), 0xE9,             // Volume Up
                USAGE(1), 0xEA,             // Volume Down
                INPUT(1), 0x02,             // Input (Data, Variable, Absolute)
                REPORT_COUNT(1), 0x01,
                INPUT(1), 0x01,
                END_COLLECTION(0),
        };
        reportLength = sizeof(reportDescriptor);
        return reportDescriptor;
    } else if (mouse_type == ABS_MOUSE) {
        static uint8_t reportDescriptor[] = {

                // Keyboard
                USAGE_PAGE(1),      0x01,
                USAGE(1),           0x06,
                COLLECTION(1),      0x01,
                REPORT_ID(1),       REPORT_ID_KEYBOARD,
                USAGE_PAGE(1),      0x07,
                USAGE_MINIMUM(1),       0xE0,
                USAGE_MAXIMUM(1),       0xE7,
                LOGICAL_MINIMUM(1),     0x00,
                LOGICAL_MAXIMUM(1),     0x01,
                REPORT_SIZE(1),     0x01,
                REPORT_COUNT(1),    0x08,
                INPUT(1),           0x02,
                REPORT_COUNT(1),    0x01,
                REPORT_SIZE(1),     0x08,
                INPUT(1),           0x01,
                REPORT_COUNT(1),    0x05,
                REPORT_SIZE(1),     0x01,
                USAGE_PAGE(1),      0x08,
                USAGE_MINIMUM(1),       0x01,
                USAGE_MAXIMUM(1),       0x05,
                OUTPUT(1),          0x02,
                REPORT_COUNT(1),    0x01,
                REPORT_SIZE(1),     0x03,
                OUTPUT(1),          0x01,
                REPORT_COUNT(1),    0x06,
                REPORT_SIZE(1),     0x08,
                LOGICAL_MINIMUM(1),     0x00,
                LOGICAL_MAXIMUM(2),     0xff, 0x00,
                USAGE_PAGE(1),      0x07,
                USAGE_MINIMUM(1),       0x00,
                USAGE_MAXIMUM(2),       0xff, 0x00,
                INPUT(1),           0x00,
                END_COLLECTION(0),

                // Mouse
                USAGE_PAGE(1), 0x01,               // Generic Desktop
                USAGE(1), 0x02,                    // Mouse
                COLLECTION(1), 0x01,               // Application
                USAGE(1), 0x01,                    // Pointer
                COLLECTION(1), 0x00,               // Physical
                REPORT_ID(1),       REPORT_ID_MOUSE,

                USAGE_PAGE(1), 0x01,                // Generic Desktop
                USAGE(1), 0x30,                     // X
                USAGE(1), 0x31,                     // Y
                LOGICAL_MINIMUM(1), 0x00,           // 0
                LOGICAL_MAXIMUM(2), 0xff, 0x7f,     // 32767
                REPORT_SIZE(1), 0x10,
                REPORT_COUNT(1), 0x02,
                INPUT(1), 0x02,                     // Data, Variable, Absolute

                USAGE_PAGE(1), 0x01,                // Generic Desktop
                USAGE(1), 0x38,                     // scroll
                LOGICAL_MINIMUM(1), 0x81,           // -127
                LOGICAL_MAXIMUM(1), 0x7f,           // 127
                REPORT_SIZE(1), 0x08,
                REPORT_COUNT(1), 0x01,
                INPUT(1), 0x06,                     // Data, Variable, Relative

                USAGE_PAGE(1), 0x09,                // Buttons
                USAGE_MINIMUM(1), 0x01,
                USAGE_MAXIMUM(1), 0x03,
                LOGICAL_MINIMUM(1), 0x00,           // 0
                LOGICAL_MAXIMUM(1), 0x01,           // 1
                REPORT_COUNT(1), 0x03,
                REPORT_SIZE(1), 0x01,
                INPUT(1), 0x02,                     // Data, Variable, Absolute
                REPORT_COUNT(1), 0x01,
                REPORT_SIZE(1), 0x05,
                INPUT(1), 0x01,                     // Constant

                END_COLLECTION(0),
                END_COLLECTION(0),

                // Media Control
                USAGE_PAGE(1), 0x0C,
                USAGE(1), 0x01,
                COLLECTION(1), 0x01,
                REPORT_ID(1), REPORT_ID_VOLUME,
                USAGE_PAGE(1), 0x0C,
                LOGICAL_MINIMUM(1), 0x00,
                LOGICAL_MAXIMUM(1), 0x01,
                REPORT_SIZE(1), 0x01,
                REPORT_COUNT(1), 0x07,
                USAGE(1), 0xB5,             // Next Track
                USAGE(1), 0xB6,             // Previous Track
                USAGE(1), 0xB7,             // Stop
                USAGE(1), 0xCD,             // Play / Pause
                USAGE(1), 0xE2,             // Mute
                USAGE(1), 0xE9,             // Volume Up
                USAGE(1), 0xEA,             // Volume Down
                INPUT(1), 0x02,             // Input (Data, Variable, Absolute)
                REPORT_COUNT(1), 0x01,
                INPUT(1), 0x01,
                END_COLLECTION(0),
        };
        reportLength = sizeof(reportDescriptor);
        return reportDescriptor;
    }

    return NULL;
}

bool USBMouseKeyboard::EPINT_OUT_callback() {
    uint32_t bytesRead = 0;
    uint8_t led[65];
    USBDevice::readEP(EPINT_OUT, led, &bytesRead, MAX_HID_REPORT_SIZE);

    // we take led[1] because led[0] is the report ID
    lock_status = led[1] & 0x07;

    // We activate the endpoint to be able to recceive data
    if (!readStart(EPINT_OUT, MAX_HID_REPORT_SIZE))
        return false;
    return true;
}

uint8_t USBMouseKeyboard::lockStatus() {
    return lock_status;
}

bool USBMouseKeyboard::update(int16_t x, int16_t y, uint8_t button, int8_t z) {
    switch (mouse_type) {
    case REL_MOUSE:
        while (x > 127) {
            if (!mouseSend(127, 0, button, z)) return false;
            x = x - 127;
        }
        while (x < -128) {
            if (!mouseSend(-128, 0, button, z)) return false;
            x = x + 128;
        }
        while (y > 127) {
            if (!mouseSend(0, 127, button, z)) return false;
            y = y - 127;
        }
        while (y < -128) {
            if (!mouseSend(0, -128, button, z)) return false;
            y = y + 128;
        }
        return mouseSend(x, y, button, z);
    case ABS_MOUSE:
        HID_REPORT report;

        report.data[0] = REPORT_ID_MOUSE;
        report.data[1] = x & 0xff;
        report.data[2] = (x >> 8) & 0xff;
        report.data[3] = y & 0xff;
        report.data[4] = (y >> 8) & 0xff;
        report.data[5] = -z;
        report.data[6] = button & 0x07;

        report.length = 7;

        return send(&report);
    default:
        return false;
    }
}

bool USBMouseKeyboard::mouseSend(int8_t x, int8_t y, uint8_t buttons, int8_t z) {
    HID_REPORT report;
    report.data[0] = REPORT_ID_MOUSE;
    report.data[1] = buttons & 0x07;
    report.data[2] = x;
    report.data[3] = y;
    report.data[4] = -z; // >0 to scroll down, <0 to scroll up

    report.length = 5;

    return send(&report);
}

bool USBMouseKeyboard::move(int16_t x, int16_t y) {
    return update(x, y, button, 0);
}

bool USBMouseKeyboard::scroll(int8_t z) {
    return update(0, 0, button, z);
}

bool USBMouseKeyboard::doubleClick() {
    if (!click(MOUSE_LEFT))
        return false;
    wait(0.1);
    return click(MOUSE_LEFT);
}

bool USBMouseKeyboard::click(uint8_t button) {
    if (!update(0, 0, button, 0))
        return false;
    wait(0.01);
    return update(0, 0, 0, 0);
}

bool USBMouseKeyboard::press(uint8_t button_) {
    button = button_ & 0x07;
    return update(0, 0, button, 0);
}

bool USBMouseKeyboard::release(uint8_t button_) {
    button = (button & (~button_)) & 0x07;
    return update(0, 0, button, 0);
}

int USBMouseKeyboard::_putc(int c) {
    return keyCode(c, keymap[c].modifier);
}

bool USBMouseKeyboard::keyCode(uint8_t key, uint8_t modifier) {
    // Send a simulated keyboard keypress. Returns true if successful.

    HID_REPORT report;

    report.data[0] = REPORT_ID_KEYBOARD;
    report.data[1] = modifier;
    report.data[2] = 0;
    report.data[3] = keymap[key].usage;
    report.data[4] = 0;
    report.data[5] = 0;
    report.data[6] = 0;
    report.data[7] = 0;
    report.data[8] = 0;

    report.length = 9;

    if (!send(&report)) {
        return false;
    }

    report.data[1] = 0;
    report.data[3] = 0;

    if (!send(&report)) {
        return false;
    }

    return true;

}


bool USBMouseKeyboard::mediaControl(MEDIA_KEY key) {
    HID_REPORT report;

    report.data[0] = REPORT_ID_VOLUME;
    report.data[1] = (1 << key) & 0x7f;

    report.length = 2;

    send(&report);

    report.data[0] = REPORT_ID_VOLUME;
    report.data[1] = 0;

    report.length = 2;

    return send(&report);
}

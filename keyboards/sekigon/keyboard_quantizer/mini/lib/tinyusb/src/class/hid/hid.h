/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

/** \ingroup group_class
 *  \defgroup ClassDriver_HID Human Interface Device (HID)
 *  @{ */

#ifndef _TUSB_HID_H_
#define _TUSB_HID_H_

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// Common Definitions
//--------------------------------------------------------------------+
/** \defgroup ClassDriver_HID_Common Common Definitions
 *  @{ */

/// USB HID Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength;         /**< Numeric expression that is the total size of the HID descriptor */
  uint8_t  bDescriptorType; /**< Constant name specifying type of HID descriptor. */

  uint16_t bcdHID;          /**< Numeric expression identifying the HID Class Specification release */
  uint8_t  bCountryCode;    /**< Numeric expression identifying country code of the localized hardware.  */
  uint8_t  bNumDescriptors; /**< Numeric expression specifying the number of class descriptors */

  uint8_t  bReportType;     /**< Type of HID class report. */
  uint16_t wReportLength;   /**< the total size of the Report descriptor. */
} tusb_hid_descriptor_hid_t;

/// HID Subclass
typedef enum
{
  HID_SUBCLASS_NONE = 0, ///< No Subclass
  HID_SUBCLASS_BOOT = 1  ///< Boot Interface Subclass
}hid_subclass_enum_t;

/// HID Interface Protocol
typedef enum
{
  HID_ITF_PROTOCOL_NONE     = 0, ///< None
  HID_ITF_PROTOCOL_KEYBOARD = 1, ///< Keyboard
  HID_ITF_PROTOCOL_MOUSE    = 2  ///< Mouse
}hid_interface_protocol_enum_t;

/// HID Descriptor Type
typedef enum
{
  HID_DESC_TYPE_HID      = 0x21, ///< HID Descriptor
  HID_DESC_TYPE_REPORT   = 0x22, ///< Report Descriptor
  HID_DESC_TYPE_PHYSICAL = 0x23  ///< Physical Descriptor
}hid_descriptor_enum_t;

/// HID Request Report Type
typedef enum
{
  HID_REPORT_TYPE_INVALID = 0,
  HID_REPORT_TYPE_INPUT,      ///< Input
  HID_REPORT_TYPE_OUTPUT,     ///< Output
  HID_REPORT_TYPE_FEATURE     ///< Feature
}hid_report_type_t;

/// HID Class Specific Control Request
typedef enum
{
  HID_REQ_CONTROL_GET_REPORT   = 0x01, ///< Get Report
  HID_REQ_CONTROL_GET_IDLE     = 0x02, ///< Get Idle
  HID_REQ_CONTROL_GET_PROTOCOL = 0x03, ///< Get Protocol
  HID_REQ_CONTROL_SET_REPORT   = 0x09, ///< Set Report
  HID_REQ_CONTROL_SET_IDLE     = 0x0a, ///< Set Idle
  HID_REQ_CONTROL_SET_PROTOCOL = 0x0b  ///< Set Protocol
}hid_request_enum_t;

/// HID Local Code
typedef enum
{
  HID_LOCAL_NotSupported = 0   , ///< NotSupported
  HID_LOCAL_Arabic             , ///< Arabic
  HID_LOCAL_Belgian            , ///< Belgian
  HID_LOCAL_Canadian_Bilingual , ///< Canadian_Bilingual
  HID_LOCAL_Canadian_French    , ///< Canadian_French
  HID_LOCAL_Czech_Republic     , ///< Czech_Republic
  HID_LOCAL_Danish             , ///< Danish
  HID_LOCAL_Finnish            , ///< Finnish
  HID_LOCAL_French             , ///< French
  HID_LOCAL_German             , ///< German
  HID_LOCAL_Greek              , ///< Greek
  HID_LOCAL_Hebrew             , ///< Hebrew
  HID_LOCAL_Hungary            , ///< Hungary
  HID_LOCAL_International      , ///< International
  HID_LOCAL_Italian            , ///< Italian
  HID_LOCAL_Japan_Katakana     , ///< Japan_Katakana
  HID_LOCAL_Korean             , ///< Korean
  HID_LOCAL_Latin_American     , ///< Latin_American
  HID_LOCAL_Netherlands_Dutch  , ///< Netherlands/Dutch
  HID_LOCAL_Norwegian          , ///< Norwegian
  HID_LOCAL_Persian_Farsi      , ///< Persian (Farsi)
  HID_LOCAL_Poland             , ///< Poland
  HID_LOCAL_Portuguese         , ///< Portuguese
  HID_LOCAL_Russia             , ///< Russia
  HID_LOCAL_Slovakia           , ///< Slovakia
  HID_LOCAL_Spanish            , ///< Spanish
  HID_LOCAL_Swedish            , ///< Swedish
  HID_LOCAL_Swiss_French       , ///< Swiss/French
  HID_LOCAL_Swiss_German       , ///< Swiss/German
  HID_LOCAL_Switzerland        , ///< Switzerland
  HID_LOCAL_Taiwan             , ///< Taiwan
  HID_LOCAL_Turkish_Q          , ///< Turkish-Q
  HID_LOCAL_UK                 , ///< UK
  HID_LOCAL_US                 , ///< US
  HID_LOCAL_Yugoslavia         , ///< Yugoslavia
  HID_LOCAL_Turkish_F            ///< Turkish-F
} hid_local_enum_t;

// HID protocol value used by GetProtocol / SetProtocol
typedef enum
{
  HID_PROTOCOL_BOOT = 0,
  HID_PROTOCOL_REPORT = 1
} hid_protocol_mode_enum_t;

/** @} */

//--------------------------------------------------------------------+
// GAMEPAD
//--------------------------------------------------------------------+
/** \addtogroup ClassDriver_HID_Gamepad Gamepad
 *  @{ */

/* From https://www.kernel.org/doc/html/latest/input/gamepad.html
          ____________________________              __
         / [__ZL__]          [__ZR__] \               |
        / [__ TL __]        [__ TR __] \              | Front Triggers
     __/________________________________\__         __|
    /                                  _   \          |
   /      /\           __             (N)   \         |
  /       ||      __  |MO|  __     _       _ \        | Main Pad
 |    <===DP===> |SE|      |ST|   (W) -|- (E) |       |
  \       ||    ___          ___       _     /        |
  /\      \/   /   \        /   \     (S)   /\      __|
 /  \________ | LS  | ____ |  RS | ________/  \       |
|         /  \ \___/ /    \ \___/ /  \         |      | Control Sticks
|        /    \_____/      \_____/    \        |    __|
|       /                              \       |
 \_____/                                \_____/

     |________|______|    |______|___________|
       D-Pad    Left       Right   Action Pad
               Stick       Stick

                 |_____________|
                    Menu Pad

  Most gamepads have the following features:
  - Action-Pad 4 buttons in diamonds-shape (on the right side) NORTH, SOUTH, WEST and EAST.
  - D-Pad (Direction-pad) 4 buttons (on the left side) that point up, down, left and right.
  - Menu-Pad Different constellations, but most-times 2 buttons: SELECT - START.
  - Analog-Sticks provide freely moveable sticks to control directions, Analog-sticks may also
  provide a digital button if you press them.
  - Triggers are located on the upper-side of the pad in vertical direction. The upper buttons
  are normally named Left- and Right-Triggers, the lower buttons Z-Left and Z-Right.
  - Rumble Many devices provide force-feedback features. But are mostly just simple rumble motors.
 */

/// HID Gamepad Protocol Report.
typedef struct TU_ATTR_PACKED
{
  int8_t  x;         ///< Delta x  movement of left analog-stick
  int8_t  y;         ///< Delta y  movement of left analog-stick
  int8_t  z;         ///< Delta z  movement of right analog-joystick
  int8_t  rz;        ///< Delta Rz movement of right analog-joystick
  int8_t  rx;        ///< Delta Rx movement of analog left trigger
  int8_t  ry;        ///< Delta Ry movement of analog right trigger
  uint8_t hat;       ///< Buttons mask for currently pressed buttons in the DPad/hat
  uint32_t buttons;  ///< Buttons mask for currently pressed buttons
}hid_gamepad_report_t;

/// Standard Gamepad Buttons Bitmap
typedef enum
{
  GAMEPAD_BUTTON_0  = TU_BIT(0),
  GAMEPAD_BUTTON_1  = TU_BIT(1),
  GAMEPAD_BUTTON_2  = TU_BIT(2),
  GAMEPAD_BUTTON_3  = TU_BIT(3),
  GAMEPAD_BUTTON_4  = TU_BIT(4),
  GAMEPAD_BUTTON_5  = TU_BIT(5),
  GAMEPAD_BUTTON_6  = TU_BIT(6),
  GAMEPAD_BUTTON_7  = TU_BIT(7),
  GAMEPAD_BUTTON_8  = TU_BIT(8),
  GAMEPAD_BUTTON_9  = TU_BIT(9),
  GAMEPAD_BUTTON_10 = TU_BIT(10),
  GAMEPAD_BUTTON_11 = TU_BIT(11),
  GAMEPAD_BUTTON_12 = TU_BIT(12),
  GAMEPAD_BUTTON_13 = TU_BIT(13),
  GAMEPAD_BUTTON_14 = TU_BIT(14),
  GAMEPAD_BUTTON_15 = TU_BIT(15),
  GAMEPAD_BUTTON_16 = TU_BIT(16),
  GAMEPAD_BUTTON_17 = TU_BIT(17),
  GAMEPAD_BUTTON_18 = TU_BIT(18),
  GAMEPAD_BUTTON_19 = TU_BIT(19),
  GAMEPAD_BUTTON_20 = TU_BIT(20),
  GAMEPAD_BUTTON_21 = TU_BIT(21),
  GAMEPAD_BUTTON_22 = TU_BIT(22),
  GAMEPAD_BUTTON_23 = TU_BIT(23),
  GAMEPAD_BUTTON_24 = TU_BIT(24),
  GAMEPAD_BUTTON_25 = TU_BIT(25),
  GAMEPAD_BUTTON_26 = TU_BIT(26),
  GAMEPAD_BUTTON_27 = TU_BIT(27),
  GAMEPAD_BUTTON_28 = TU_BIT(28),
  GAMEPAD_BUTTON_29 = TU_BIT(29),
  GAMEPAD_BUTTON_30 = TU_BIT(30),
  GAMEPAD_BUTTON_31 = TU_BIT(31),
}hid_gamepad_button_bm_t;

/// Standard Gamepad Buttons Naming from Linux input event codes
/// https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
#define GAMEPAD_BUTTON_A       GAMEPAD_BUTTON_0
#define GAMEPAD_BUTTON_SOUTH   GAMEPAD_BUTTON_0

#define GAMEPAD_BUTTON_B       GAMEPAD_BUTTON_1
#define GAMEPAD_BUTTON_EAST    GAMEPAD_BUTTON_1

#define GAMEPAD_BUTTON_C       GAMEPAD_BUTTON_2

#define GAMEPAD_BUTTON_X       GAMEPAD_BUTTON_3
#define GAMEPAD_BUTTON_NORTH   GAMEPAD_BUTTON_3

#define GAMEPAD_BUTTON_Y       GAMEPAD_BUTTON_4
#define GAMEPAD_BUTTON_WEST    GAMEPAD_BUTTON_4

#define GAMEPAD_BUTTON_Z       GAMEPAD_BUTTON_5
#define GAMEPAD_BUTTON_TL      GAMEPAD_BUTTON_6
#define GAMEPAD_BUTTON_TR      GAMEPAD_BUTTON_7
#define GAMEPAD_BUTTON_TL2     GAMEPAD_BUTTON_8
#define GAMEPAD_BUTTON_TR2     GAMEPAD_BUTTON_9
#define GAMEPAD_BUTTON_SELECT  GAMEPAD_BUTTON_10
#define GAMEPAD_BUTTON_START   GAMEPAD_BUTTON_11
#define GAMEPAD_BUTTON_MODE    GAMEPAD_BUTTON_12
#define GAMEPAD_BUTTON_THUMBL  GAMEPAD_BUTTON_13
#define GAMEPAD_BUTTON_THUMBR  GAMEPAD_BUTTON_14

/// Standard Gamepad HAT/DPAD Buttons (from Linux input event codes)
typedef enum
{
  GAMEPAD_HAT_CENTERED   = 0,  ///< DPAD_CENTERED
  GAMEPAD_HAT_UP         = 1,  ///< DPAD_UP
  GAMEPAD_HAT_UP_RIGHT   = 2,  ///< DPAD_UP_RIGHT
  GAMEPAD_HAT_RIGHT      = 3,  ///< DPAD_RIGHT
  GAMEPAD_HAT_DOWN_RIGHT = 4,  ///< DPAD_DOWN_RIGHT
  GAMEPAD_HAT_DOWN       = 5,  ///< DPAD_DOWN
  GAMEPAD_HAT_DOWN_LEFT  = 6,  ///< DPAD_DOWN_LEFT
  GAMEPAD_HAT_LEFT       = 7,  ///< DPAD_LEFT
  GAMEPAD_HAT_UP_LEFT    = 8,  ///< DPAD_UP_LEFT
}hid_gamepad_hat_t;

/// @}

//--------------------------------------------------------------------+
// MOUSE
//--------------------------------------------------------------------+
/** \addtogroup ClassDriver_HID_Mouse Mouse
 *  @{ */

/// Standard HID Boot Protocol Mouse Report.
typedef struct TU_ATTR_PACKED
{
  uint8_t buttons; /**< buttons mask for currently pressed buttons in the mouse. */
  int8_t  x;       /**< Current delta x movement of the mouse. */
  int8_t  y;       /**< Current delta y movement on the mouse. */
  int8_t  wheel;   /**< Current delta wheel movement on the mouse. */
  int8_t  pan;     // using AC Pan
} hid_mouse_report_t;

/// Standard Mouse Buttons Bitmap
typedef enum
{
  MOUSE_BUTTON_LEFT     = TU_BIT(0), ///< Left button
  MOUSE_BUTTON_RIGHT    = TU_BIT(1), ///< Right button
  MOUSE_BUTTON_MIDDLE   = TU_BIT(2), ///< Middle button
  MOUSE_BUTTON_BACKWARD = TU_BIT(3), ///< Backward button,
  MOUSE_BUTTON_FORWARD  = TU_BIT(4), ///< Forward button,
}hid_mouse_button_bm_t;

/// @}

//--------------------------------------------------------------------+
// Keyboard
//--------------------------------------------------------------------+
/** \addtogroup ClassDriver_HID_Keyboard Keyboard
 *  @{ */

/// Standard HID Boot Protocol Keyboard Report.
typedef struct TU_ATTR_PACKED
{
  uint8_t modifier;   /**< Keyboard modifier (KEYBOARD_MODIFIER_* masks). */
  uint8_t reserved;   /**< Reserved for OEM use, always set to 0. */
  uint8_t keycode[6]; /**< Key codes of the currently pressed keys. */
} hid_keyboard_report_t;

/// Keyboard modifier codes bitmap
typedef enum
{
  KEYBOARD_MODIFIER_LEFTCTRL   = TU_BIT(0), ///< Left Control
  KEYBOARD_MODIFIER_LEFTSHIFT  = TU_BIT(1), ///< Left Shift
  KEYBOARD_MODIFIER_LEFTALT    = TU_BIT(2), ///< Left Alt
  KEYBOARD_MODIFIER_LEFTGUI    = TU_BIT(3), ///< Left Window
  KEYBOARD_MODIFIER_RIGHTCTRL  = TU_BIT(4), ///< Right Control
  KEYBOARD_MODIFIER_RIGHTSHIFT = TU_BIT(5), ///< Right Shift
  KEYBOARD_MODIFIER_RIGHTALT   = TU_BIT(6), ///< Right Alt
  KEYBOARD_MODIFIER_RIGHTGUI   = TU_BIT(7)  ///< Right Window
}hid_keyboard_modifier_bm_t;

typedef enum
{
  KEYBOARD_LED_NUMLOCK    = TU_BIT(0), ///< Num Lock LED
  KEYBOARD_LED_CAPSLOCK   = TU_BIT(1), ///< Caps Lock LED
  KEYBOARD_LED_SCROLLLOCK = TU_BIT(2), ///< Scroll Lock LED
  KEYBOARD_LED_COMPOSE    = TU_BIT(3), ///< Composition Mode
  KEYBOARD_LED_KANA       = TU_BIT(4) ///< Kana mode
}hid_keyboard_led_bm_t;

/// @}

//--------------------------------------------------------------------+
// HID KEYCODE
//--------------------------------------------------------------------+
#define HID_KEY_NONE                      0x00
#define HID_KEY_A                         0x04
#define HID_KEY_B                         0x05
#define HID_KEY_C                         0x06
#define HID_KEY_D                         0x07
#define HID_KEY_E                         0x08
#define HID_KEY_F                         0x09
#define HID_KEY_G                         0x0A
#define HID_KEY_H                         0x0B
#define HID_KEY_I                         0x0C
#define HID_KEY_J                         0x0D
#define HID_KEY_K                         0x0E
#define HID_KEY_L                         0x0F
#define HID_KEY_M                         0x10
#define HID_KEY_N                         0x11
#define HID_KEY_O                         0x12
#define HID_KEY_P                         0x13
#define HID_KEY_Q                         0x14
#define HID_KEY_R                         0x15
#define HID_KEY_S                         0x16
#define HID_KEY_T                         0x17
#define HID_KEY_U                         0x18
#define HID_KEY_V                         0x19
#define HID_KEY_W                         0x1A
#define HID_KEY_X                         0x1B
#define HID_KEY_Y                         0x1C
#define HID_KEY_Z                         0x1D
#define HID_KEY_1                         0x1E
#define HID_KEY_2                         0x1F
#define HID_KEY_3                         0x20
#define HID_KEY_4                         0x21
#define HID_KEY_5                         0x22
#define HID_KEY_6                         0x23
#define HID_KEY_7                         0x24
#define HID_KEY_8                         0x25
#define HID_KEY_9                         0x26
#define HID_KEY_0                         0x27
#define HID_KEY_ENTER                     0x28
#define HID_KEY_ESCAPE                    0x29
#define HID_KEY_BACKSPACE                 0x2A
#define HID_KEY_TAB                       0x2B
#define HID_KEY_SPACE                     0x2C
#define HID_KEY_MINUS                     0x2D
#define HID_KEY_EQUAL                     0x2E
#define HID_KEY_BRACKET_LEFT              0x2F
#define HID_KEY_BRACKET_RIGHT             0x30
#define HID_KEY_BACKSLASH                 0x31
#define HID_KEY_EUROPE_1                  0x32
#define HID_KEY_SEMICOLON                 0x33
#define HID_KEY_APOSTROPHE                0x34
#define HID_KEY_GRAVE                     0x35
#define HID_KEY_COMMA                     0x36
#define HID_KEY_PERIOD                    0x37
#define HID_KEY_SLASH                     0x38
#define HID_KEY_CAPS_LOCK                 0x39
#define HID_KEY_F1                        0x3A
#define HID_KEY_F2                        0x3B
#define HID_KEY_F3                        0x3C
#define HID_KEY_F4                        0x3D
#define HID_KEY_F5                        0x3E
#define HID_KEY_F6                        0x3F
#define HID_KEY_F7                        0x40
#define HID_KEY_F8                        0x41
#define HID_KEY_F9                        0x42
#define HID_KEY_F10                       0x43
#define HID_KEY_F11                       0x44
#define HID_KEY_F12                       0x45
#define HID_KEY_PRINT_SCREEN              0x46
#define HID_KEY_SCROLL_LOCK               0x47
#define HID_KEY_PAUSE                     0x48
#define HID_KEY_INSERT                    0x49
#define HID_KEY_HOME                      0x4A
#define HID_KEY_PAGE_UP                   0x4B
#define HID_KEY_DELETE                    0x4C
#define HID_KEY_END                       0x4D
#define HID_KEY_PAGE_DOWN                 0x4E
#define HID_KEY_ARROW_RIGHT               0x4F
#define HID_KEY_ARROW_LEFT                0x50
#define HID_KEY_ARROW_DOWN                0x51
#define HID_KEY_ARROW_UP                  0x52
#define HID_KEY_NUM_LOCK                  0x53
#define HID_KEY_KEYPAD_DIVIDE             0x54
#define HID_KEY_KEYPAD_MULTIPLY           0x55
#define HID_KEY_KEYPAD_SUBTRACT           0x56
#define HID_KEY_KEYPAD_ADD                0x57
#define HID_KEY_KEYPAD_ENTER              0x58
#define HID_KEY_KEYPAD_1                  0x59
#define HID_KEY_KEYPAD_2                  0x5A
#define HID_KEY_KEYPAD_3                  0x5B
#define HID_KEY_KEYPAD_4                  0x5C
#define HID_KEY_KEYPAD_5                  0x5D
#define HID_KEY_KEYPAD_6                  0x5E
#define HID_KEY_KEYPAD_7                  0x5F
#define HID_KEY_KEYPAD_8                  0x60
#define HID_KEY_KEYPAD_9                  0x61
#define HID_KEY_KEYPAD_0                  0x62
#define HID_KEY_KEYPAD_DECIMAL            0x63
#define HID_KEY_EUROPE_2                  0x64
#define HID_KEY_APPLICATION               0x65
#define HID_KEY_POWER                     0x66
#define HID_KEY_KEYPAD_EQUAL              0x67
#define HID_KEY_F13                       0x68
#define HID_KEY_F14                       0x69
#define HID_KEY_F15                       0x6A
#define HID_KEY_F16                       0x6B
#define HID_KEY_F17                       0x6C
#define HID_KEY_F18                       0x6D
#define HID_KEY_F19                       0x6E
#define HID_KEY_F20                       0x6F
#define HID_KEY_F21                       0x70
#define HID_KEY_F22                       0x71
#define HID_KEY_F23                       0x72
#define HID_KEY_F24                       0x73
#define HID_KEY_EXECUTE                   0x74
#define HID_KEY_HELP                      0x75
#define HID_KEY_MENU                      0x76
#define HID_KEY_SELECT                    0x77
#define HID_KEY_STOP                      0x78
#define HID_KEY_AGAIN                     0x79
#define HID_KEY_UNDO                      0x7A
#define HID_KEY_CUT                       0x7B
#define HID_KEY_COPY                      0x7C
#define HID_KEY_PASTE                     0x7D
#define HID_KEY_FIND                      0x7E
#define HID_KEY_MUTE                      0x7F
#define HID_KEY_VOLUME_UP                 0x80
#define HID_KEY_VOLUME_DOWN               0x81
#define HID_KEY_LOCKING_CAPS_LOCK         0x82
#define HID_KEY_LOCKING_NUM_LOCK          0x83
#define HID_KEY_LOCKING_SCROLL_LOCK       0x84
#define HID_KEY_KEYPAD_COMMA              0x85
#define HID_KEY_KEYPAD_EQUAL_SIGN         0x86
#define HID_KEY_KANJI1                    0x87
#define HID_KEY_KANJI2                    0x88
#define HID_KEY_KANJI3                    0x89
#define HID_KEY_KANJI4                    0x8A
#define HID_KEY_KANJI5                    0x8B
#define HID_KEY_KANJI6                    0x8C
#define HID_KEY_KANJI7                    0x8D
#define HID_KEY_KANJI8                    0x8E
#define HID_KEY_KANJI9                    0x8F
#define HID_KEY_LANG1                     0x90
#define HID_KEY_LANG2                     0x91
#define HID_KEY_LANG3                     0x92
#define HID_KEY_LANG4                     0x93
#define HID_KEY_LANG5                     0x94
#define HID_KEY_LANG6                     0x95
#define HID_KEY_LANG7                     0x96
#define HID_KEY_LANG8                     0x97
#define HID_KEY_LANG9                     0x98
#define HID_KEY_ALTERNATE_ERASE           0x99
#define HID_KEY_SYSREQ_ATTENTION          0x9A
#define HID_KEY_CANCEL                    0x9B
#define HID_KEY_CLEAR                     0x9C
#define HID_KEY_PRIOR                     0x9D
#define HID_KEY_RETURN                    0x9E
#define HID_KEY_SEPARATOR                 0x9F
#define HID_KEY_OUT                       0xA0
#define HID_KEY_OPER                      0xA1
#define HID_KEY_CLEAR_AGAIN               0xA2
#define HID_KEY_CRSEL_PROPS               0xA3
#define HID_KEY_EXSEL                     0xA4
// RESERVED					                      0xA5-DF
#define HID_KEY_CONTROL_LEFT              0xE0
#define HID_KEY_SHIFT_LEFT                0xE1
#define HID_KEY_ALT_LEFT                  0xE2
#define HID_KEY_GUI_LEFT                  0xE3
#define HID_KEY_CONTROL_RIGHT             0xE4
#define HID_KEY_SHIFT_RIGHT               0xE5
#define HID_KEY_ALT_RIGHT                 0xE6
#define HID_KEY_GUI_RIGHT                 0xE7


//--------------------------------------------------------------------+
// REPORT DESCRIPTOR
//--------------------------------------------------------------------+

//------------- ITEM & TAG -------------//
#define HID_REPORT_DATA_0(data)
#define HID_REPORT_DATA_1(data) , data
#define HID_REPORT_DATA_2(data) , U16_TO_U8S_LE(data)
#define HID_REPORT_DATA_3(data) , U32_TO_U8S_LE(data)

#define HID_REPORT_ITEM(data, tag, type, size) \
  (((tag) << 4) | ((type) << 2) | (size)) HID_REPORT_DATA_##size(data)

// Report Item Types
enum {
  RI_TYPE_MAIN   = 0,
  RI_TYPE_GLOBAL = 1,
  RI_TYPE_LOCAL  = 2
};

//------------- Main Items - HID 1.11 section 6.2.2.4 -------------//

// Report Item Main group
enum {
  RI_MAIN_INPUT          = 8,
  RI_MAIN_OUTPUT         = 9,
  RI_MAIN_COLLECTION     = 10,
  RI_MAIN_FEATURE        = 11,
  RI_MAIN_COLLECTION_END = 12
};

#define HID_INPUT(x)           HID_REPORT_ITEM(x, RI_MAIN_INPUT         , RI_TYPE_MAIN, 1)
#define HID_OUTPUT(x)          HID_REPORT_ITEM(x, RI_MAIN_OUTPUT        , RI_TYPE_MAIN, 1)
#define HID_COLLECTION(x)      HID_REPORT_ITEM(x, RI_MAIN_COLLECTION    , RI_TYPE_MAIN, 1)
#define HID_FEATURE(x)         HID_REPORT_ITEM(x, RI_MAIN_FEATURE       , RI_TYPE_MAIN, 1)
#define HID_COLLECTION_END     HID_REPORT_ITEM(x, RI_MAIN_COLLECTION_END, RI_TYPE_MAIN, 0)

//------------- Input, Output, Feature - HID 1.11 section 6.2.2.5 -------------//
#define HID_DATA             (0<<0)
#define HID_CONSTANT         (1<<0)

#define HID_ARRAY            (0<<1)
#define HID_VARIABLE         (1<<1)

#define HID_ABSOLUTE         (0<<2)
#define HID_RELATIVE         (1<<2)

#define HID_WRAP_NO          (0<<3)
#define HID_WRAP             (1<<3)

#define HID_LINEAR           (0<<4)
#define HID_NONLINEAR        (1<<4)

#define HID_PREFERRED_STATE  (0<<5)
#define HID_PREFERRED_NO     (1<<5)

#define HID_NO_NULL_POSITION (0<<6)
#define HID_NULL_STATE       (1<<6)

#define HID_NON_VOLATILE     (0<<7)
#define HID_VOLATILE         (1<<7)

#define HID_BITFIELD         (0<<8)
#define HID_BUFFERED_BYTES   (1<<8)

//------------- Collection Item - HID 1.11 section 6.2.2.6 -------------//
enum {
  HID_COLLECTION_PHYSICAL = 0,
  HID_COLLECTION_APPLICATION,
  HID_COLLECTION_LOGICAL,
  HID_COLLECTION_REPORT,
  HID_COLLECTION_NAMED_ARRAY,
  HID_COLLECTION_USAGE_SWITCH,
  HID_COLLECTION_USAGE_MODIFIER
};

//------------- Global Items - HID 1.11 section 6.2.2.7 -------------//

// Report Item Global group
enum {
  RI_GLOBAL_USAGE_PAGE    = 0,
  RI_GLOBAL_LOGICAL_MIN   = 1,
  RI_GLOBAL_LOGICAL_MAX   = 2,
  RI_GLOBAL_PHYSICAL_MIN  = 3,
  RI_GLOBAL_PHYSICAL_MAX  = 4,
  RI_GLOBAL_UNIT_EXPONENT = 5,
  RI_GLOBAL_UNIT          = 6,
  RI_GLOBAL_REPORT_SIZE   = 7,
  RI_GLOBAL_REPORT_ID     = 8,
  RI_GLOBAL_REPORT_COUNT  = 9,
  RI_GLOBAL_PUSH          = 10,
  RI_GLOBAL_POP           = 11
};

#define HID_USAGE_PAGE(x)         HID_REPORT_ITEM(x, RI_GLOBAL_USAGE_PAGE, RI_TYPE_GLOBAL, 1)
#define HID_USAGE_PAGE_N(x, n)    HID_REPORT_ITEM(x, RI_GLOBAL_USAGE_PAGE, RI_TYPE_GLOBAL, n)

#define HID_LOGICAL_MIN(x)        HID_REPORT_ITEM(x, RI_GLOBAL_LOGICAL_MIN, RI_TYPE_GLOBAL, 1)
#define HID_LOGICAL_MIN_N(x, n)   HID_REPORT_ITEM(x, RI_GLOBAL_LOGICAL_MIN, RI_TYPE_GLOBAL, n)

#define HID_LOGICAL_MAX(x)        HID_REPORT_ITEM(x, RI_GLOBAL_LOGICAL_MAX, RI_TYPE_GLOBAL, 1)
#define HID_LOGICAL_MAX_N(x, n)   HID_REPORT_ITEM(x, RI_GLOBAL_LOGICAL_MAX, RI_TYPE_GLOBAL, n)

#define HID_PHYSICAL_MIN(x)       HID_REPORT_ITEM(x, RI_GLOBAL_PHYSICAL_MIN, RI_TYPE_GLOBAL, 1)
#define HID_PHYSICAL_MIN_N(x, n)  HID_REPORT_ITEM(x, RI_GLOBAL_PHYSICAL_MIN, RI_TYPE_GLOBAL, n)

#define HID_PHYSICAL_MAX(x)       HID_REPORT_ITEM(x, RI_GLOBAL_PHYSICAL_MAX, RI_TYPE_GLOBAL, 1)
#define HID_PHYSICAL_MAX_N(x, n)  HID_REPORT_ITEM(x, RI_GLOBAL_PHYSICAL_MAX, RI_TYPE_GLOBAL, n)

#define HID_UNIT_EXPONENT(x)      HID_REPORT_ITEM(x, RI_GLOBAL_UNIT_EXPONENT, RI_TYPE_GLOBAL, 1)
#define HID_UNIT_EXPONENT_N(x, n) HID_REPORT_ITEM(x, RI_GLOBAL_UNIT_EXPONENT, RI_TYPE_GLOBAL, n)

#define HID_UNIT(x)               HID_REPORT_ITEM(x, RI_GLOBAL_UNIT, RI_TYPE_GLOBAL, 1)
#define HID_UNIT_N(x, n)          HID_REPORT_ITEM(x, RI_GLOBAL_UNIT, RI_TYPE_GLOBAL, n)

#define HID_REPORT_SIZE(x)        HID_REPORT_ITEM(x, RI_GLOBAL_REPORT_SIZE, RI_TYPE_GLOBAL, 1)
#define HID_REPORT_SIZE_N(x, n)   HID_REPORT_ITEM(x, RI_GLOBAL_REPORT_SIZE, RI_TYPE_GLOBAL, n)

#define HID_REPORT_ID(x)          HID_REPORT_ITEM(x, RI_GLOBAL_REPORT_ID, RI_TYPE_GLOBAL, 1),
#define HID_REPORT_ID_N(x, n)     HID_REPORT_ITEM(x, RI_GLOBAL_REPORT_ID, RI_TYPE_GLOBAL, n),

#define HID_REPORT_COUNT(x)       HID_REPORT_ITEM(x, RI_GLOBAL_REPORT_COUNT, RI_TYPE_GLOBAL, 1)
#define HID_REPORT_COUNT_N(x, n)  HID_REPORT_ITEM(x, RI_GLOBAL_REPORT_COUNT, RI_TYPE_GLOBAL, n)

#define HID_PUSH                  HID_REPORT_ITEM(x, RI_GLOBAL_PUSH, RI_TYPE_GLOBAL, 0)
#define HID_POP                   HID_REPORT_ITEM(x, RI_GLOBAL_POP, RI_TYPE_GLOBAL, 0)

//------------- LOCAL ITEMS 6.2.2.8 -------------//

enum {
  RI_LOCAL_USAGE            = 0,
  RI_LOCAL_USAGE_MIN        = 1,
  RI_LOCAL_USAGE_MAX        = 2,
  RI_LOCAL_DESIGNATOR_INDEX = 3,
  RI_LOCAL_DESIGNATOR_MIN   = 4,
  RI_LOCAL_DESIGNATOR_MAX   = 5,
  // 6 is reserved
  RI_LOCAL_STRING_INDEX     = 7,
  RI_LOCAL_STRING_MIN       = 8,
  RI_LOCAL_STRING_MAX       = 9,
  RI_LOCAL_DELIMITER        = 10,
};

#define HID_USAGE(x)              HID_REPORT_ITEM(x, RI_LOCAL_USAGE, RI_TYPE_LOCAL, 1)
#define HID_USAGE_N(x, n)         HID_REPORT_ITEM(x, RI_LOCAL_USAGE, RI_TYPE_LOCAL, n)

#define HID_USAGE_MIN(x)          HID_REPORT_ITEM(x, RI_LOCAL_USAGE_MIN, RI_TYPE_LOCAL, 1)
#define HID_USAGE_MIN_N(x, n)     HID_REPORT_ITEM(x, RI_LOCAL_USAGE_MIN, RI_TYPE_LOCAL, n)

#define HID_USAGE_MAX(x)          HID_REPORT_ITEM(x, RI_LOCAL_USAGE_MAX, RI_TYPE_LOCAL, 1)
#define HID_USAGE_MAX_N(x, n)     HID_REPORT_ITEM(x, RI_LOCAL_USAGE_MAX, RI_TYPE_LOCAL, n)

//--------------------------------------------------------------------+
// Usage Table
//--------------------------------------------------------------------+

/// HID Usage Table - Table 1: Usage Page Summary
enum {
  HID_USAGE_PAGE_DESKTOP         = 0x01,
  HID_USAGE_PAGE_SIMULATE        = 0x02,
  HID_USAGE_PAGE_VIRTUAL_REALITY = 0x03,
  HID_USAGE_PAGE_SPORT           = 0x04,
  HID_USAGE_PAGE_GAME            = 0x05,
  HID_USAGE_PAGE_GENERIC_DEVICE  = 0x06,
  HID_USAGE_PAGE_KEYBOARD        = 0x07,
  HID_USAGE_PAGE_LED             = 0x08,
  HID_USAGE_PAGE_BUTTON          = 0x09,
  HID_USAGE_PAGE_ORDINAL         = 0x0a,
  HID_USAGE_PAGE_TELEPHONY       = 0x0b,
  HID_USAGE_PAGE_CONSUMER        = 0x0c,
  HID_USAGE_PAGE_DIGITIZER       = 0x0d,
  HID_USAGE_PAGE_PID             = 0x0f,
  HID_USAGE_PAGE_UNICODE         = 0x10,
  HID_USAGE_PAGE_ALPHA_DISPLAY   = 0x14,
  HID_USAGE_PAGE_MEDICAL         = 0x40,
  HID_USAGE_PAGE_MONITOR         = 0x80, //0x80 - 0x83
  HID_USAGE_PAGE_POWER           = 0x84, // 0x084 - 0x87
  HID_USAGE_PAGE_BARCODE_SCANNER = 0x8c,
  HID_USAGE_PAGE_SCALE           = 0x8d,
  HID_USAGE_PAGE_MSR             = 0x8e,
  HID_USAGE_PAGE_CAMERA          = 0x90,
  HID_USAGE_PAGE_ARCADE          = 0x91,
  HID_USAGE_PAGE_FIDO            = 0xF1D0, // FIDO alliance HID usage page
  HID_USAGE_PAGE_VENDOR          = 0xFF00 // 0xFF00 - 0xFFFF
};

/// HID Usage Table - Table 6: Generic Desktop Page
enum {
  HID_USAGE_DESKTOP_POINTER                               = 0x01,
  HID_USAGE_DESKTOP_MOUSE                                 = 0x02,
  HID_USAGE_DESKTOP_JOYSTICK                              = 0x04,
  HID_USAGE_DESKTOP_GAMEPAD                               = 0x05,
  HID_USAGE_DESKTOP_KEYBOARD                              = 0x06,
  HID_USAGE_DESKTOP_KEYPAD                                = 0x07,
  HID_USAGE_DESKTOP_MULTI_AXIS_CONTROLLER                 = 0x08,
  HID_USAGE_DESKTOP_TABLET_PC_SYSTEM                      = 0x09,
  HID_USAGE_DESKTOP_X                                     = 0x30,
  HID_USAGE_DESKTOP_Y                                     = 0x31,
  HID_USAGE_DESKTOP_Z                                     = 0x32,
  HID_USAGE_DESKTOP_RX                                    = 0x33,
  HID_USAGE_DESKTOP_RY                                    = 0x34,
  HID_USAGE_DESKTOP_RZ                                    = 0x35,
  HID_USAGE_DESKTOP_SLIDER                                = 0x36,
  HID_USAGE_DESKTOP_DIAL                                  = 0x37,
  HID_USAGE_DESKTOP_WHEEL                                 = 0x38,
  HID_USAGE_DESKTOP_HAT_SWITCH                            = 0x39,
  HID_USAGE_DESKTOP_COUNTED_BUFFER                        = 0x3a,
  HID_USAGE_DESKTOP_BYTE_COUNT                            = 0x3b,
  HID_USAGE_DESKTOP_MOTION_WAKEUP                         = 0x3c,
  HID_USAGE_DESKTOP_START                                 = 0x3d,
  HID_USAGE_DESKTOP_SELECT                                = 0x3e,
  HID_USAGE_DESKTOP_VX                                    = 0x40,
  HID_USAGE_DESKTOP_VY                                    = 0x41,
  HID_USAGE_DESKTOP_VZ                                    = 0x42,
  HID_USAGE_DESKTOP_VBRX                                  = 0x43,
  HID_USAGE_DESKTOP_VBRY                                  = 0x44,
  HID_USAGE_DESKTOP_VBRZ                                  = 0x45,
  HID_USAGE_DESKTOP_VNO                                   = 0x46,
  HID_USAGE_DESKTOP_FEATURE_NOTIFICATION                  = 0x47,
  HID_USAGE_DESKTOP_RESOLUTION_MULTIPLIER                 = 0x48,
  HID_USAGE_DESKTOP_SYSTEM_CONTROL                        = 0x80,
  HID_USAGE_DESKTOP_SYSTEM_POWER_DOWN                     = 0x81,
  HID_USAGE_DESKTOP_SYSTEM_SLEEP                          = 0x82,
  HID_USAGE_DESKTOP_SYSTEM_WAKE_UP                        = 0x83,
  HID_USAGE_DESKTOP_SYSTEM_CONTEXT_MENU                   = 0x84,
  HID_USAGE_DESKTOP_SYSTEM_MAIN_MENU                      = 0x85,
  HID_USAGE_DESKTOP_SYSTEM_APP_MENU                       = 0x86,
  HID_USAGE_DESKTOP_SYSTEM_MENU_HELP                      = 0x87,
  HID_USAGE_DESKTOP_SYSTEM_MENU_EXIT                      = 0x88,
  HID_USAGE_DESKTOP_SYSTEM_MENU_SELECT                    = 0x89,
  HID_USAGE_DESKTOP_SYSTEM_MENU_RIGHT                     = 0x8A,
  HID_USAGE_DESKTOP_SYSTEM_MENU_LEFT                      = 0x8B,
  HID_USAGE_DESKTOP_SYSTEM_MENU_UP                        = 0x8C,
  HID_USAGE_DESKTOP_SYSTEM_MENU_DOWN                      = 0x8D,
  HID_USAGE_DESKTOP_SYSTEM_COLD_RESTART                   = 0x8E,
  HID_USAGE_DESKTOP_SYSTEM_WARM_RESTART                   = 0x8F,
  HID_USAGE_DESKTOP_DPAD_UP                               = 0x90,
  HID_USAGE_DESKTOP_DPAD_DOWN                             = 0x91,
  HID_USAGE_DESKTOP_DPAD_RIGHT                            = 0x92,
  HID_USAGE_DESKTOP_DPAD_LEFT                             = 0x93,
  HID_USAGE_DESKTOP_SYSTEM_DOCK                           = 0xA0,
  HID_USAGE_DESKTOP_SYSTEM_UNDOCK                         = 0xA1,
  HID_USAGE_DESKTOP_SYSTEM_SETUP                          = 0xA2,
  HID_USAGE_DESKTOP_SYSTEM_BREAK                          = 0xA3,
  HID_USAGE_DESKTOP_SYSTEM_DEBUGGER_BREAK                 = 0xA4,
  HID_USAGE_DESKTOP_APPLICATION_BREAK                     = 0xA5,
  HID_USAGE_DESKTOP_APPLICATION_DEBUGGER_BREAK            = 0xA6,
  HID_USAGE_DESKTOP_SYSTEM_SPEAKER_MUTE                   = 0xA7,
  HID_USAGE_DESKTOP_SYSTEM_HIBERNATE                      = 0xA8,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_INVERT                 = 0xB0,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_INTERNAL               = 0xB1,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_EXTERNAL               = 0xB2,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_BOTH                   = 0xB3,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_DUAL                   = 0xB4,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_TOGGLE_INT_EXT         = 0xB5,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_SWAP_PRIMARY_SECONDARY = 0xB6,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_LCD_AUTOSCALE          = 0xB7
};


/// HID Usage Table: Consumer Page (0x0C)
/// Only contains controls that supported by Windows (whole list is too long)
enum
{
  // Generic Control
  HID_USAGE_CONSUMER_CONTROL                           = 0x0001,

  // Power Control
  HID_USAGE_CONSUMER_POWER                             = 0x0030,
  HID_USAGE_CONSUMER_RESET                             = 0x0031,
  HID_USAGE_CONSUMER_SLEEP                             = 0x0032,

  // Screen Brightness
  HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT              = 0x006F,
  HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT              = 0x0070,

  // These HID usages operate only on mobile systems (battery powered) and
  // require Windows 8 (build 8302 or greater).
  HID_USAGE_CONSUMER_WIRELESS_RADIO_CONTROLS           = 0x000C,
  HID_USAGE_CONSUMER_WIRELESS_RADIO_BUTTONS            = 0x00C6,
  HID_USAGE_CONSUMER_WIRELESS_RADIO_LED                = 0x00C7,
  HID_USAGE_CONSUMER_WIRELESS_RADIO_SLIDER_SWITCH      = 0x00C8,

  // Media Control
  HID_USAGE_CONSUMER_PLAY_PAUSE                        = 0x00CD,
  HID_USAGE_CONSUMER_SCAN_NEXT                         = 0x00B5,
  HID_USAGE_CONSUMER_SCAN_PREVIOUS                     = 0x00B6,
  HID_USAGE_CONSUMER_STOP                              = 0x00B7,
  HID_USAGE_CONSUMER_VOLUME                            = 0x00E0,
  HID_USAGE_CONSUMER_MUTE                              = 0x00E2,
  HID_USAGE_CONSUMER_BASS                              = 0x00E3,
  HID_USAGE_CONSUMER_TREBLE                            = 0x00E4,
  HID_USAGE_CONSUMER_BASS_BOOST                        = 0x00E5,
  HID_USAGE_CONSUMER_VOLUME_INCREMENT                  = 0x00E9,
  HID_USAGE_CONSUMER_VOLUME_DECREMENT                  = 0x00EA,
  HID_USAGE_CONSUMER_BASS_INCREMENT                    = 0x0152,
  HID_USAGE_CONSUMER_BASS_DECREMENT                    = 0x0153,
  HID_USAGE_CONSUMER_TREBLE_INCREMENT                  = 0x0154,
  HID_USAGE_CONSUMER_TREBLE_DECREMENT                  = 0x0155,

  // Application Launcher
  HID_USAGE_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION = 0x0183,
  HID_USAGE_CONSUMER_AL_EMAIL_READER                   = 0x018A,
  HID_USAGE_CONSUMER_AL_CALCULATOR                     = 0x0192,
  HID_USAGE_CONSUMER_AL_LOCAL_BROWSER                  = 0x0194,

  // Browser/Explorer Specific
  HID_USAGE_CONSUMER_AC_SEARCH                         = 0x0221,
  HID_USAGE_CONSUMER_AC_HOME                           = 0x0223,
  HID_USAGE_CONSUMER_AC_BACK                           = 0x0224,
  HID_USAGE_CONSUMER_AC_FORWARD                        = 0x0225,
  HID_USAGE_CONSUMER_AC_STOP                           = 0x0226,
  HID_USAGE_CONSUMER_AC_REFRESH                        = 0x0227,
  HID_USAGE_CONSUMER_AC_BOOKMARKS                      = 0x022A,

  // Mouse Horizontal scroll
  HID_USAGE_CONSUMER_AC_PAN                            = 0x0238,
};

/// HID Usage Table: FIDO Alliance Page (0xF1D0)
enum
{
  HID_USAGE_FIDO_U2FHID   = 0x01, // U2FHID usage for top-level collection
  HID_USAGE_FIDO_DATA_IN  = 0x20, // Raw IN data report
  HID_USAGE_FIDO_DATA_OUT = 0x21  // Raw OUT data report
};

/*--------------------------------------------------------------------
 * ASCII to KEYCODE Conversion
 *  Expand to array of [128][2] (shift, keycode)
 *
 * Usage: example to convert input chr into keyboard report (modifier + keycode)
 *
 *  uint8_t const conv_table[128][2] =  { HID_ASCII_TO_KEYCODE };
 *
 *  uint8_t keycode[6] = { 0 };
 *  uint8_t modifier   = 0;
 *
 *  if ( conv_table[chr][0] ) modifier = KEYBOARD_MODIFIER_LEFTSHIFT;
 *  keycode[0] = conv_table[chr][1];
 *  tud_hid_keyboard_report(report_id, modifier, keycode);
 *
 *--------------------------------------------------------------------*/
#define HID_ASCII_TO_KEYCODE \
    {0, 0                     }, /* 0x00 Null      */ \
    {0, 0                     }, /* 0x01           */ \
    {0, 0                     }, /* 0x02           */ \
    {0, 0                     }, /* 0x03           */ \
    {0, 0                     }, /* 0x04           */ \
    {0, 0                     }, /* 0x05           */ \
    {0, 0                     }, /* 0x06           */ \
    {0, 0                     }, /* 0x07           */ \
    {0, HID_KEY_BACKSPACE     }, /* 0x08 Backspace */ \
    {0, HID_KEY_TAB           }, /* 0x09 Tab       */ \
    {0, HID_KEY_ENTER         }, /* 0x0A Line Feed */ \
    {0, 0                     }, /* 0x0B           */ \
    {0, 0                     }, /* 0x0C           */ \
    {0, HID_KEY_ENTER         }, /* 0x0D CR        */ \
    {0, 0                     }, /* 0x0E           */ \
    {0, 0                     }, /* 0x0F           */ \
    {0, 0                     }, /* 0x10           */ \
    {0, 0                     }, /* 0x11           */ \
    {0, 0                     }, /* 0x12           */ \
    {0, 0                     }, /* 0x13           */ \
    {0, 0                     }, /* 0x14           */ \
    {0, 0                     }, /* 0x15           */ \
    {0, 0                     }, /* 0x16           */ \
    {0, 0                     }, /* 0x17           */ \
    {0, 0                     }, /* 0x18           */ \
    {0, 0                     }, /* 0x19           */ \
    {0, 0                     }, /* 0x1A           */ \
    {0, HID_KEY_ESCAPE        }, /* 0x1B Escape    */ \
    {0, 0                     }, /* 0x1C           */ \
    {0, 0                     }, /* 0x1D           */ \
    {0, 0                     }, /* 0x1E           */ \
    {0, 0                     }, /* 0x1F           */ \
                                                      \
    {0, HID_KEY_SPACE         }, /* 0x20           */ \
    {1, HID_KEY_1             }, /* 0x21 !         */ \
    {1, HID_KEY_APOSTROPHE    }, /* 0x22 "         */ \
    {1, HID_KEY_3             }, /* 0x23 #         */ \
    {1, HID_KEY_4             }, /* 0x24 $         */ \
    {1, HID_KEY_5             }, /* 0x25 %         */ \
    {1, HID_KEY_7             }, /* 0x26 &         */ \
    {0, HID_KEY_APOSTROPHE    }, /* 0x27 '         */ \
    {1, HID_KEY_9             }, /* 0x28 (         */ \
    {1, HID_KEY_0             }, /* 0x29 )         */ \
    {1, HID_KEY_8             }, /* 0x2A *         */ \
    {1, HID_KEY_EQUAL         }, /* 0x2B +         */ \
    {0, HID_KEY_COMMA         }, /* 0x2C ,         */ \
    {0, HID_KEY_MINUS         }, /* 0x2D -         */ \
    {0, HID_KEY_PERIOD        }, /* 0x2E .         */ \
    {0, HID_KEY_SLASH         }, /* 0x2F /         */ \
    {0, HID_KEY_0             }, /* 0x30 0         */ \
    {0, HID_KEY_1             }, /* 0x31 1         */ \
    {0, HID_KEY_2             }, /* 0x32 2         */ \
    {0, HID_KEY_3             }, /* 0x33 3         */ \
    {0, HID_KEY_4             }, /* 0x34 4         */ \
    {0, HID_KEY_5             }, /* 0x35 5         */ \
    {0, HID_KEY_6             }, /* 0x36 6         */ \
    {0, HID_KEY_7             }, /* 0x37 7         */ \
    {0, HID_KEY_8             }, /* 0x38 8         */ \
    {0, HID_KEY_9             }, /* 0x39 9         */ \
    {1, HID_KEY_SEMICOLON     }, /* 0x3A :         */ \
    {0, HID_KEY_SEMICOLON     }, /* 0x3B ;         */ \
    {1, HID_KEY_COMMA         }, /* 0x3C <         */ \
    {0, HID_KEY_EQUAL         }, /* 0x3D =         */ \
    {1, HID_KEY_PERIOD        }, /* 0x3E >         */ \
    {1, HID_KEY_SLASH         }, /* 0x3F ?         */ \
                                                      \
    {1, HID_KEY_2             }, /* 0x40 @         */ \
    {1, HID_KEY_A             }, /* 0x41 A         */ \
    {1, HID_KEY_B             }, /* 0x42 B         */ \
    {1, HID_KEY_C             }, /* 0x43 C         */ \
    {1, HID_KEY_D             }, /* 0x44 D         */ \
    {1, HID_KEY_E             }, /* 0x45 E         */ \
    {1, HID_KEY_F             }, /* 0x46 F         */ \
    {1, HID_KEY_G             }, /* 0x47 G         */ \
    {1, HID_KEY_H             }, /* 0x48 H         */ \
    {1, HID_KEY_I             }, /* 0x49 I         */ \
    {1, HID_KEY_J             }, /* 0x4A J         */ \
    {1, HID_KEY_K             }, /* 0x4B K         */ \
    {1, HID_KEY_L             }, /* 0x4C L         */ \
    {1, HID_KEY_M             }, /* 0x4D M         */ \
    {1, HID_KEY_N             }, /* 0x4E N         */ \
    {1, HID_KEY_O             }, /* 0x4F O         */ \
    {1, HID_KEY_P             }, /* 0x50 P         */ \
    {1, HID_KEY_Q             }, /* 0x51 Q         */ \
    {1, HID_KEY_R             }, /* 0x52 R         */ \
    {1, HID_KEY_S             }, /* 0x53 S         */ \
    {1, HID_KEY_T             }, /* 0x55 T         */ \
    {1, HID_KEY_U             }, /* 0x55 U         */ \
    {1, HID_KEY_V             }, /* 0x56 V         */ \
    {1, HID_KEY_W             }, /* 0x57 W         */ \
    {1, HID_KEY_X             }, /* 0x58 X         */ \
    {1, HID_KEY_Y             }, /* 0x59 Y         */ \
    {1, HID_KEY_Z             }, /* 0x5A Z         */ \
    {0, HID_KEY_BRACKET_LEFT  }, /* 0x5B [         */ \
    {0, HID_KEY_BACKSLASH     }, /* 0x5C '\'       */ \
    {0, HID_KEY_BRACKET_RIGHT }, /* 0x5D ]         */ \
    {1, HID_KEY_6             }, /* 0x5E ^         */ \
    {1, HID_KEY_MINUS         }, /* 0x5F _         */ \
                                                      \
    {0, HID_KEY_GRAVE         }, /* 0x60 `         */ \
    {0, HID_KEY_A             }, /* 0x61 a         */ \
    {0, HID_KEY_B             }, /* 0x62 b         */ \
    {0, HID_KEY_C             }, /* 0x63 c         */ \
    {0, HID_KEY_D             }, /* 0x66 d         */ \
    {0, HID_KEY_E             }, /* 0x65 e         */ \
    {0, HID_KEY_F             }, /* 0x66 f         */ \
    {0, HID_KEY_G             }, /* 0x67 g         */ \
    {0, HID_KEY_H             }, /* 0x68 h         */ \
    {0, HID_KEY_I             }, /* 0x69 i         */ \
    {0, HID_KEY_J             }, /* 0x6A j         */ \
    {0, HID_KEY_K             }, /* 0x6B k         */ \
    {0, HID_KEY_L             }, /* 0x6C l         */ \
    {0, HID_KEY_M             }, /* 0x6D m         */ \
    {0, HID_KEY_N             }, /* 0x6E n         */ \
    {0, HID_KEY_O             }, /* 0x6F o         */ \
    {0, HID_KEY_P             }, /* 0x70 p         */ \
    {0, HID_KEY_Q             }, /* 0x71 q         */ \
    {0, HID_KEY_R             }, /* 0x72 r         */ \
    {0, HID_KEY_S             }, /* 0x73 s         */ \
    {0, HID_KEY_T             }, /* 0x75 t         */ \
    {0, HID_KEY_U             }, /* 0x75 u         */ \
    {0, HID_KEY_V             }, /* 0x76 v         */ \
    {0, HID_KEY_W             }, /* 0x77 w         */ \
    {0, HID_KEY_X             }, /* 0x78 x         */ \
    {0, HID_KEY_Y             }, /* 0x79 y         */ \
    {0, HID_KEY_Z             }, /* 0x7A z         */ \
    {1, HID_KEY_BRACKET_LEFT  }, /* 0x7B {         */ \
    {1, HID_KEY_BACKSLASH     }, /* 0x7C |         */ \
    {1, HID_KEY_BRACKET_RIGHT }, /* 0x7D }         */ \
    {1, HID_KEY_GRAVE         }, /* 0x7E ~         */ \
    {0, HID_KEY_DELETE        }  /* 0x7F Delete    */ \

/*--------------------------------------------------------------------
 * KEYCODE to Ascii Conversion
 *  Expand to array of [128][2] (ascii without shift, ascii with shift)
 *
 * Usage: example to convert ascii from keycode (key) and shift modifier (shift).
 * Here we assume key < 128 ( printable )
 *
 *  uint8_t const conv_table[128][2] =  { HID_KEYCODE_TO_ASCII };
 *  char ch = shift ? conv_table[chr][1] : conv_table[chr][0];
 *
 *--------------------------------------------------------------------*/
#define HID_KEYCODE_TO_ASCII    \
    {0     , 0      }, /* 0x00 */ \
    {0     , 0      }, /* 0x01 */ \
    {0     , 0      }, /* 0x02 */ \
    {0     , 0      }, /* 0x03 */ \
    {'a'   , 'A'    }, /* 0x04 */ \
    {'b'   , 'B'    }, /* 0x05 */ \
    {'c'   , 'C'    }, /* 0x06 */ \
    {'d'   , 'D'    }, /* 0x07 */ \
    {'e'   , 'E'    }, /* 0x08 */ \
    {'f'   , 'F'    }, /* 0x09 */ \
    {'g'   , 'G'    }, /* 0x0a */ \
    {'h'   , 'H'    }, /* 0x0b */ \
    {'i'   , 'I'    }, /* 0x0c */ \
    {'j'   , 'J'    }, /* 0x0d */ \
    {'k'   , 'K'    }, /* 0x0e */ \
    {'l'   , 'L'    }, /* 0x0f */ \
    {'m'   , 'M'    }, /* 0x10 */ \
    {'n'   , 'N'    }, /* 0x11 */ \
    {'o'   , 'O'    }, /* 0x12 */ \
    {'p'   , 'P'    }, /* 0x13 */ \
    {'q'   , 'Q'    }, /* 0x14 */ \
    {'r'   , 'R'    }, /* 0x15 */ \
    {'s'   , 'S'    }, /* 0x16 */ \
    {'t'   , 'T'    }, /* 0x17 */ \
    {'u'   , 'U'    }, /* 0x18 */ \
    {'v'   , 'V'    }, /* 0x19 */ \
    {'w'   , 'W'    }, /* 0x1a */ \
    {'x'   , 'X'    }, /* 0x1b */ \
    {'y'   , 'Y'    }, /* 0x1c */ \
    {'z'   , 'Z'    }, /* 0x1d */ \
    {'1'   , '!'    }, /* 0x1e */ \
    {'2'   , '@'    }, /* 0x1f */ \
    {'3'   , '#'    }, /* 0x20 */ \
    {'4'   , '$'    }, /* 0x21 */ \
    {'5'   , '%'    }, /* 0x22 */ \
    {'6'   , '^'    }, /* 0x23 */ \
    {'7'   , '&'    }, /* 0x24 */ \
    {'8'   , '*'    }, /* 0x25 */ \
    {'9'   , '('    }, /* 0x26 */ \
    {'0'   , ')'    }, /* 0x27 */ \
    {'\r'  , '\r'   }, /* 0x28 */ \
    {'\x1b', '\x1b' }, /* 0x29 */ \
    {'\b'  , '\b'   }, /* 0x2a */ \
    {'\t'  , '\t'   }, /* 0x2b */ \
    {' '   , ' '    }, /* 0x2c */ \
    {'-'   , '_'    }, /* 0x2d */ \
    {'='   , '+'    }, /* 0x2e */ \
    {'['   , '{'    }, /* 0x2f */ \
    {']'   , '}'    }, /* 0x30 */ \
    {'\\'  , '|'    }, /* 0x31 */ \
    {'#'   , '~'    }, /* 0x32 */ \
    {';'   , ':'    }, /* 0x33 */ \
    {'\''  , '\"'   }, /* 0x34 */ \
    {'`'   , '~'    }, /* 0x35 */ \
    {','   , '<'    }, /* 0x36 */ \
    {'.'   , '>'    }, /* 0x37 */ \
    {'/'   , '?'    }, /* 0x38 */ \
                                  \
    {0     , 0      }, /* 0x39 */ \
    {0     , 0      }, /* 0x3a */ \
    {0     , 0      }, /* 0x3b */ \
    {0     , 0      }, /* 0x3c */ \
    {0     , 0      }, /* 0x3d */ \
    {0     , 0      }, /* 0x3e */ \
    {0     , 0      }, /* 0x3f */ \
    {0     , 0      }, /* 0x40 */ \
    {0     , 0      }, /* 0x41 */ \
    {0     , 0      }, /* 0x42 */ \
    {0     , 0      }, /* 0x43 */ \
    {0     , 0      }, /* 0x44 */ \
    {0     , 0      }, /* 0x45 */ \
    {0     , 0      }, /* 0x46 */ \
    {0     , 0      }, /* 0x47 */ \
    {0     , 0      }, /* 0x48 */ \
    {0     , 0      }, /* 0x49 */ \
    {0     , 0      }, /* 0x4a */ \
    {0     , 0      }, /* 0x4b */ \
    {0     , 0      }, /* 0x4c */ \
    {0     , 0      }, /* 0x4d */ \
    {0     , 0      }, /* 0x4e */ \
    {0     , 0      }, /* 0x4f */ \
    {0     , 0      }, /* 0x50 */ \
    {0     , 0      }, /* 0x51 */ \
    {0     , 0      }, /* 0x52 */ \
    {0     , 0      }, /* 0x53 */ \
                                  \
    {'/'   , '/'    }, /* 0x54 */ \
    {'*'   , '*'    }, /* 0x55 */ \
    {'-'   , '-'    }, /* 0x56 */ \
    {'+'   , '+'    }, /* 0x57 */ \
    {'\r'  , '\r'   }, /* 0x58 */ \
    {'1'   , 0      }, /* 0x59 */ \
    {'2'   , 0      }, /* 0x5a */ \
    {'3'   , 0      }, /* 0x5b */ \
    {'4'   , 0      }, /* 0x5c */ \
    {'5'   , '5'    }, /* 0x5d */ \
    {'6'   , 0      }, /* 0x5e */ \
    {'7'   , 0      }, /* 0x5f */ \
    {'8'   , 0      }, /* 0x60 */ \
    {'9'   , 0      }, /* 0x61 */ \
    {'0'   , 0      }, /* 0x62 */ \
    {'.'   , 0      }, /* 0x63 */ \
    {0     , 0      }, /* 0x64 */ \
    {0     , 0      }, /* 0x65 */ \
    {0     , 0      }, /* 0x66 */ \
    {'='   , '='    }, /* 0x67 */ \


#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_HID_H__ */

/// @}

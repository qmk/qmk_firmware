#include "keycode_lookup.h"
#include "print.h"

char* translate_keycode_to_string(uint8_t code)
{
    uint8_t arr_index = 0;
    static char unknown[] = "UNKNOWN";

    //uprintf("Clicked code: %d\n", code);

    if((code <= 0xBE) )
    {
        arr_index = code;
    }
    else if((code >= 0xC0) && (code <= 0xE7) )
    {
        arr_index = code - 0x01;
    }
    else if((code >= 0xF0) && (code <= 0xFF))
    {
        arr_index = code - 0x09;
    }
    else
    {
        return unknown;
    }

    return keycode_to_string_array[arr_index];
}

char keycode_to_string_array [] [24] =
{
    "KC_NO",
    "KC_ROLL_OVER",
    "KC_POST_FAIL",
    "KC_UNDEFINED",
    "KC_A",
    "KC_B",
    "KC_C",
    "KC_D",
    "KC_E",
    "KC_F",
    "KC_G",
    "KC_H",
    "KC_I",
    "KC_J",
    "KC_K",
    "KC_L",
    "KC_M",
    "KC_N",
    "KC_O",
    "KC_P",
    "KC_Q",
    "KC_R",
    "KC_S",
    "KC_T",
    "KC_U",
    "KC_V",
    "KC_W",
    "KC_X",
    "KC_Y",
    "KC_Z",
    "KC_1",
    "KC_2",
    "KC_3",
    "KC_4",
    "KC_5",
    "KC_6",
    "KC_7",
    "KC_8",
    "KC_9",
    "KC_0",
    "KC_ENTER",
    "KC_ESCAPE",
    "KC_BSPACE",
    "KC_TAB",
    "KC_SPACE",
    "KC_MINUS",
    "KC_EQUAL",
    "KC_LBRACKET",
    "KC_RBRACKET",
    "KC_BSLASH",
    "KC_NONUS_HASH",
    "KC_SCOLON",
    "KC_QUOTE",
    "KC_GRAVE",
    "KC_COMMA",
    "KC_DOT",
    "KC_SLASH",
    "KC_CAPSLOCK",
    "KC_F1",
    "KC_F2",
    "KC_F3",
    "KC_F4",
    "KC_F5",
    "KC_F6",
    "KC_F7",
    "KC_F8",
    "KC_F9",
    "KC_F10",
    "KC_F11",
    "KC_F12",
    "KC_PSCREEN",
    "KC_SCROLLLOCK",
    "KC_PAUSE",
    "KC_INSERT",
    "KC_HOME",
    "KC_PGUP",
    "KC_DELETE",
    "KC_END",
    "KC_PGDOWN",
    "KC_RIGHT",
    "KC_LEFT",
    "KC_DOWN",
    "KC_UP",
    "KC_NUMLOCK",
    "KC_KP_SLASH",
    "KC_KP_ASTERISK",
    "KC_KP_MINUS",
    "KC_KP_PLUS",
    "KC_KP_ENTER",
    "KC_KP_1",
    "KC_KP_2",
    "KC_KP_3",
    "KC_KP_4",
    "KC_KP_5",
    "KC_KP_6",
    "KC_KP_7",
    "KC_KP_8",
    "KC_KP_9",
    "KC_KP_0",
    "KC_KP_DOT",
    "KC_NONUS_BSLASH",
    "KC_APPLICATION",
    "KC_POWER",
    "KC_KP_EQUAL",
    "KC_F13",
    "KC_F14",
    "KC_F15",
    "KC_F16",
    "KC_F17",
    "KC_F18",
    "KC_F19",
    "KC_F20",
    "KC_F21",
    "KC_F22",
    "KC_F23",
    "KC_F24",
    "KC_EXECUTE",
    "KC_HELP",
    "KC_MENU",
    "KC_SELECT",
    "KC_STOP",
    "KC_AGAIN",
    "KC_UNDO",
    "KC_CUT",
    "KC_COPY",
    "KC_PASTE",
    "KC_FIND",
    "KC__MUTE",
    "KC__VOLUP",
    "KC__VOLDOWN",
    "KC_LOCKING_CAPS",
    "KC_LOCKING_NUM",
    "KC_LOCKING_SCROLL",
    "KC_KP_COMMA",
    "KC_KP_EQUAL_AS400",
    "KC_INT1",
    "KC_INT2",
    "KC_INT3",
    "KC_INT4",
    "KC_INT5",
    "KC_INT6",
    "KC_INT7",
    "KC_INT8",
    "KC_INT9",
    "KC_LANG1",
    "KC_LANG2",
    "KC_LANG3",
    "KC_LANG4",
    "KC_LANG5",
    "KC_LANG6",
    "KC_LANG7",
    "KC_LANG8",
    "KC_LANG9",
    "KC_ALT_ERASE",
    "KC_SYSREQ",
    "KC_CANCEL",
    "KC_CLEAR",
    "KC_PRIOR",
    "KC_RETURN",
    "KC_SEPARATOR",
    "KC_OUT",
    "KC_OPER",
    "KC_CLEAR_AGAIN",
    "KC_CRSEL",
    "KC_EXSEL", // = 0xA4

    /* Generic Desktop Page */
    "KC_SYSTEM_POWER", //= 0xA5,
    "KC_SYSTEM_SLEEP",
    "KC_SYSTEM_WAKE", // = 0xA7

    /* Consumer Page */
    "KC_AUDIO_MUTE", // = 0xA8
    "KC_AUDIO_VOL_UP",
    "KC_AUDIO_VOL_DOWN",
    "KC_MEDIA_NEXT_TRACK",
    "KC_MEDIA_PREV_TRACK",
    "KC_MEDIA_STOP",
    "KC_MEDIA_PLAY_PAUSE",
    "KC_MEDIA_SELECT",
    "KC_MEDIA_EJECT",  // 0xB0
    "KC_MAIL",
    "KC_CALCULATOR",
    "KC_MY_COMPUTER",
    "KC_WWW_SEARCH",
    "KC_WWW_HOME",
    "KC_WWW_BACK",
    "KC_WWW_FORWARD",
    "KC_WWW_STOP",
    "KC_WWW_REFRESH",
    "KC_WWW_FAVORITES",
    "KC_MEDIA_FAST_FORWARD",
    "KC_MEDIA_REWIND",
    "KC_BRIGHTNESS_UP",
    "KC_BRIGHTNESS_DOWN", // = 0xBE

    /* Fn Keys */
    "KC_FN0", //= 0xC0,
    "KC_FN1",
    "KC_FN2",
    "KC_FN3",
    "KC_FN4",
    "KC_FN5",
    "KC_FN6",
    "KC_FN7",
    "KC_FN8",
    "KC_FN9",
    "KC_FN10",
    "KC_FN11",
    "KC_FN12",
    "KC_FN13",
    "KC_FN14",
    "KC_FN15",
    "KC_FN16",  // 0xD0
    "KC_FN17",
    "KC_FN18",
    "KC_FN19",
    "KC_FN20",
    "KC_FN21",
    "KC_FN22",
    "KC_FN23",
    "KC_FN24",
    "KC_FN25",
    "KC_FN26",
    "KC_FN27",
    "KC_FN28",
    "KC_FN29",
    "KC_FN30",
    "KC_FN31", // 0xDF

    "KC_LCTRL",  // = 0xE0,
    "KC_LSHIFT",
    "KC_LALT",
    "KC_LGUI",
    "KC_RCTRL",
    "KC_RSHIFT",
    "KC_RALT",
    "KC_RGUI", // = 0xE7

    /* Mouse Buttons */
    "KC_MS_UP", // = 0xF0,
    "KC_MS_DOWN",
    "KC_MS_LEFT",
    "KC_MS_RIGHT",
    "KC_MS_BTN1",
    "KC_MS_BTN2",
    "KC_MS_BTN3",
    "KC_MS_BTN4",
    "KC_MS_BTN5", // 0xF8

    /* Mouse Wheel */
    "KC_MS_WH_UP", // 0xF9
    "KC_MS_WH_DOWN",
    "KC_MS_WH_LEFT",
    "KC_MS_WH_RIGHT", // 0xFC

    /* Acceleration */
    "KC_MS_ACCEL0", // 0xFD
    "KC_MS_ACCEL1",
    "KC_MS_ACCEL2", // 0xFF
};

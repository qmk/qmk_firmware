#pragma once

enum signalrgb_commands
{
    GET_QMK_VERSION = 0x21,
    GET_PROTOCOL_VERSION = 0x22,
    GET_UNIQUE_IDENTIFIER = 0x23,
    STREAM_RGB_DATA = 0x24,
    SET_SIGNALRGB_MODE_ENABLE = 0x25,
    SET_SIGNALRGB_MODE_DISABLE = 0x26,
    GET_TOTAL_LEDS = 0x27,
    GET_FIRMWARE_TYPE = 0x28,
};

enum signalrgb_responses
{
    PROTOCOL_VERSION_BYTE_1 = 1,
    PROTOCOL_VERSION_BYTE_2 = 0,
    PROTOCOL_VERSION_BYTE_3 = 5,
    DEVICE_UNIQUE_IDENTIFIER_BYTE_1 = 0,
    DEVICE_UNIQUE_IDENTIFIER_BYTE_2 = 0,
    DEVICE_UNIQUE_IDENTIFIER_BYTE_3 = 0,
    FIRMWARE_TYPE_BYTE = 2,
    DEVICE_ERROR_LED_BOUNDS = 253,
    DEVICE_ERROR_LED_COUNT = 254 
};

void get_qmk_version(void);
void get_signalrgb_protocol_version(void);
void get_unique_identifier(void);
void led_streaming(uint8_t *data);
void signalrgb_mode_enable(void);
void signalrgb_mode_disable(void);
void get_total_leds(void);

//Changelogs for Firmware Versions------------------------------------
//V1.0.1 added detection for the total number of LEDs a board has. Plugins need a rewrite to make use of this change. Rewritten plugins will not function with older firmware.
//V1.0.2 added another detection byte for which fork of SignalRGB firmware device is running. This means we can keep overlap Unique Identifiers between Sonix and Mainline.
//V1.0.3 unifies the command IDs between Mainline, Sonix, and VIA. All commands have a 0x20 offset now.
//V1.0.4 improves detection handling, and has a complete rewrite of the plugins. Also merges Mainline and VIA branches. VIA Branch is deprecated.
//V1.0.5 adds support for RGBLight and adds proper bounds checking for leds to ensure we don't crash the firmware.

/*
DEVICE, DEVICE_UNIQUE_IDENTIFIER_BYTE_1,DEVICE_UNIQUE_IDENTIFIER_BYTE_2,DEVICE_UNIQUE_IDENTIFIER_BYTE_3
gmmk/pro/rev1/ansi:default                  0 0 5
gmmk/pro/rev2/ansi:default                  0 0 5
gmmk/pro/rev1/iso:default                   0 0 6
gmmk/pro/rev2/iso:default                   0 0 6
gmmk/gmmk2/p65/ansi:default                 0 0 7
gmmk/gmmk2/p65/iso:default                  0 0 8
gmmk/gmmk2/p96/ansi:default                 0 0 9
gmmk/gmmk2/p96/iso:default                  0 0 10
redragon/k530:default                       0 1 1
redragon/k552/rev1:ansi                     0 1 2
redragon/k552/rev1:iso                      0 1 2
redragon/k552/rev2:default                  0 1 2
redragon/k552/rev2:abnt2                    0 1 2
redragon/k556:default                       0 1 3
redragon/k580:default                       0 1 4
redragon/k582:default                       0 1 3
redragon/k630:default                       0 1 5
*/
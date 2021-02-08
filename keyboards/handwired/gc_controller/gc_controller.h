#include "quantum.h"

typedef enum {
    SWITCH_Y       = 0x01,
    SWITCH_B       = 0x02,
    SWITCH_A       = 0x04,
    SWITCH_X       = 0x08,
    SWITCH_L       = 0x10,
    SWITCH_R       = 0x20,
    SWITCH_ZL      = 0x40,
    SWITCH_ZR      = 0x80,
    SWITCH_MINUS   = 0x100,
    SWITCH_PLUS    = 0x200,
    SWITCH_LCLICK  = 0x400,
    SWITCH_RCLICK  = 0x800,
    SWITCH_HOME    = 0x1000,
    SWITCH_CAPTURE = 0x2000,
} SwitchButtons_t;

typedef enum {
    GAMECUBE_A      = 0b0000000000000001,
    GAMECUBE_B      = 0b0000000000000010,
    GAMECUBE_X      = 0b0000000000000100,
    GAMECUBE_Y      = 0b0000000000001000,
    GAMECUBE_START  = 0b0000000000010000,
    GAMECUBE_LEFT   = 0b0000000100000000,
    GAMECUBE_RIGHT  = 0b0000001000000000,
    GAMECUBE_DOWN   = 0b0000010000000000,
    GAMECUBE_UP     = 0b0000100000000000,
    GAMECUBE_Z      = 0b0001000000000000,
    GAMECUBE_R      = 0b0010000000000000,
    GAMECUBE_L      = 0b0100000000000000,
} GamecubeButtons_t;

#define HAT_TOP          0x00
#define HAT_TOP_RIGHT    0x01
#define HAT_RIGHT        0x02
#define HAT_BOTTOM_RIGHT 0x03
#define HAT_BOTTOM       0x04
#define HAT_BOTTOM_LEFT  0x05
#define HAT_LEFT         0x06
#define HAT_TOP_LEFT     0x07
#define HAT_CENTER       0x08

#define STICK_MIN      0
#define STICK_CENTER 128
#define STICK_MAX    255

#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "version.h"
#include "process_records.h"
#include "unicode.h"

enum userspace_layers {
    _QWERTY = 0,
    _RAISE,
};

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,
    LOD,
    RUPA,
    U_FRACT,
    U_MONOS,
    U_SCRPT,
};

typedef struct font_t {
    uint32_t upper_alpha;
    uint32_t lower_alpha;
    uint32_t zero_glyph;
} font_t;

font_t fraktu_bold;
font_t monosp_bold;
font_t script_bold;

bool script_mode_translate(font_t *translator, bool is_shifted, uint32_t keycode);

#define RAISE   MO(_RAISE)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_RALT OSM(MOD_RALT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)

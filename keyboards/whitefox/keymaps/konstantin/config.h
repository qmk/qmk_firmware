#pragma once

#define LAYER_FN
#define LAYER_NUMPAD

#undef  IS_COMMAND
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RCTL)))

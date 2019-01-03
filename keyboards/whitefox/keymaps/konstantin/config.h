#pragma once

#undef  IS_COMMAND
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RCTL)))

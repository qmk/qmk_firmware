#pragma once

/* Pins for custom per-row LEDs. Should be changed to use named pins. */
#define LED_ROW_PINS { 8, 9, 10, 11 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    false \
)

#ifndef BOOTMAGIC_H
#define BOOTMAGIC_H


#ifndef BOOTMAGIC_KEY_SKIP
#define BOOTMAGIC_KEY_SKIP              KC_ESC
#endif

/* eeprom clear */
#ifndef BOOTMAGIC_KEY_EEPROM_CLEAR
#define BOOTMAGIC_KEY_EEPROM_CLEAR      KC_BSPACE
#endif

/* kick up bootloader */
#ifndef BOOTMAGIC_KEY_BOOTLOADER
#define BOOTMAGIC_KEY_BOOTLOADER        KC_B
#endif

/* debug enable */
#define BOOTMAGIC_KEY_DEBUG_ENABLE      KC_D
#define BOOTMAGIC_KEY_DEBUG_MATRIX      KC_X
#define BOOTMAGIC_KEY_DEBUG_KEYBOARD    KC_K
#define BOOTMAGIC_KEY_DEBUG_MOUSE       KC_M

/*
 * keymap config
 */
#define BOOTMAGIC_KEY_SWAP_CONTROL_CPASLOCK     KC_LCTRL
#define BOOTMAGIC_KEY_CAPSLOCK_TO_CONTROL       KC_CAPSLOCK
#define BOOTMAGIC_KEY_SWAP_LALT_LGUI            KC_LALT
#define BOOTMAGIC_KEY_SWAP_RALT_RGUI            KC_RALT
#define BOOTMAGIC_KEY_NO_GUI                    KC_LGUI
#define BOOTMAGIC_KEY_SWAP_GRAVE_ESC            KC_GRAVE
#define BOOTMAGIC_KEY_SWAP_BACKSLASH_BACKSPACE  KC_BSLASH


/*
 * change default layer
 */
#define BOOTMAGIC_KEY_DEFAULT_LAYER_0   KC_0
#define BOOTMAGIC_KEY_DEFAULT_LAYER_1   KC_1
#define BOOTMAGIC_KEY_DEFAULT_LAYER_2   KC_2
#define BOOTMAGIC_KEY_DEFAULT_LAYER_3   KC_3


void bootmagic(void);
bool bootmagic_scan_keycode(uint8_t keycode);

#endif

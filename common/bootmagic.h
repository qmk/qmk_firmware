#ifndef BOOTMAGIC_H
#define BOOTMAGIC_H


#ifndef BOOTMAGIC_IS_ENABLED
#define BOOTMAGIC_IS_ENABLED()          true
#endif

/* kick up bootloader */
#ifndef BOOTMAGIC_BOOTLOADER_KEY
#define BOOTMAGIC_BOOTLOADER_KEY        KC_B
#endif
/* debug enable */
#ifndef BOOTMAGIC_DEBUG_ENABLE_KEY
#define BOOTMAGIC_DEBUG_ENABLE_KEY      KC_D
#endif
/* eeprom clear */
#ifndef BOOTMAGIC_EEPROM_CLEAR_KEY
#define BOOTMAGIC_EEPROM_CLEAR_KEY      KC_BSPACE
#endif

/*
 * key configure
 */
/* swap control and capslock */
#ifndef BOOTMAGIC_SWAP_CONTROL_CPASLOCK
#define BOOTMAGIC_SWAP_CONTROL_CPASLOCK     KC_LCTRL
#endif
/* capslock to control */
#ifndef BOOTMAGIC_CAPSLOCK_TO_CONTROL
#define BOOTMAGIC_CAPSLOCK_TO_CONTROL       KC_CAPSLOCK
#endif
/* swap alt and gui */
#ifndef BOOTMAGIC_SWAP_LALT_LGUI
#define BOOTMAGIC_SWAP_LALT_LGUI            KC_LALT
#endif
/* swap alt and gui */
#ifndef BOOTMAGIC_SWAP_RALT_RGUI
#define BOOTMAGIC_SWAP_RALT_RGUI            KC_RALT
#endif
/* no gui */
#ifndef BOOTMAGIC_NO_GUI
#define BOOTMAGIC_NO_GUI                    KC_LGUI
#endif
/* swap esc and grave */
#ifndef BOOTMAGIC_SWAP_GRAVE_ESC
#define BOOTMAGIC_SWAP_GRAVE_ESC            KC_GRAVE
#endif
/* swap backslash and backspace */
#ifndef BOOTMAGIC_SWAP_BACKSLASH_BACKSPACE
#define BOOTMAGIC_SWAP_BACKSLASH_BACKSPACE  KC_BSLASH
#endif


/*
 * change default layer
 */
#ifndef BOOTMAGIC_DEFAULT_LAYER_0_KEY
#define BOOTMAGIC_DEFAULT_LAYER_0_KEY   KC_0
#endif
#ifndef BOOTMAGIC_DEFAULT_LAYER_1_KEY
#define BOOTMAGIC_DEFAULT_LAYER_1_KEY   KC_1
#endif
#ifndef BOOTMAGIC_DEFAULT_LAYER_2_KEY
#define BOOTMAGIC_DEFAULT_LAYER_2_KEY   KC_2
#endif
#ifndef BOOTMAGIC_DEFAULT_LAYER_3_KEY
#define BOOTMAGIC_DEFAULT_LAYER_3_KEY   KC_3
#endif


void bootmagic(void);
bool bootmagic_scan_keycode(uint8_t keycode);

#endif

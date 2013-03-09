#ifndef BOOTMAGIC_H
#define BOOTMAGIC_H


#ifndef BOOTMAGIC_IS_ENABLE
#define BOOTMAGIC_IS_ENABLE()           true
#endif

/* bootloader */
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

/* change default layer */
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

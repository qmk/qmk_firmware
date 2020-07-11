#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "eeconfig.h"
#include "action_layer.h"

#ifdef STM32_EEPROM_ENABLE
#    include "hal.h"
#    include "eeprom_stm32.h"
#endif

#if defined(EEPROM_DRIVER)
#    include "eeprom_driver.h"
#endif

#if defined(HAPTIC_ENABLE)
#    include "haptic.h"
#endif

/** \brief eeconfig enable
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void eeconfig_init_user(void) {
    // Reset user EEPROM value to blank, rather than to a set value
    eeconfig_update_user(0);
}

__attribute__((weak)) void eeconfig_init_kb(void) {
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);

    eeconfig_init_user();
}

/*
 * FIXME: needs doc
 */
void eeconfig_init_quantum(void) {
#ifdef STM32_EEPROM_ENABLE
    EEPROM_Erase();
#endif
#if defined(EEPROM_DRIVER)
    eeprom_driver_erase();
#endif
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
    eeprom_update_byte(EECONFIG_DEBUG, 0);
    eeprom_update_byte(EECONFIG_DEFAULT_LAYER, 0);
    default_layer_state = 0;
    eeprom_update_byte(EECONFIG_KEYMAP_LOWER_BYTE, 0);
    eeprom_update_byte(EECONFIG_KEYMAP_UPPER_BYTE, 0);
    eeprom_update_byte(EECONFIG_MOUSEKEY_ACCEL, 0);
    eeprom_update_byte(EECONFIG_BACKLIGHT, 0);
    eeprom_update_byte(EECONFIG_AUDIO, 0xFF);  // On by default
    eeprom_update_dword(EECONFIG_RGBLIGHT, 0);
    eeprom_update_byte(EECONFIG_STENOMODE, 0);
    eeprom_update_dword(EECONFIG_HAPTIC, 0);
    eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
    eeprom_update_dword(EECONFIG_RGB_MATRIX, 0);
    eeprom_update_byte(EECONFIG_RGB_MATRIX_SPEED, 0);

    // TODO: Remove once ARM has a way to configure EECONFIG_HANDEDNESS
    //        within the emulated eeprom via dfu-util or another tool
#if defined INIT_EE_HANDS_LEFT
#    pragma message "Faking EE_HANDS for left hand"
    eeprom_update_byte(EECONFIG_HANDEDNESS, 1);
#elif defined INIT_EE_HANDS_RIGHT
#    pragma message "Faking EE_HANDS for right hand"
    eeprom_update_byte(EECONFIG_HANDEDNESS, 0);
#endif

#if defined(HAPTIC_ENABLE)
    haptic_reset();
#else
    // this is used in case haptic is disabled, but we still want sane defaults
    // in the haptic configuration eeprom. All zero will trigger a haptic_reset
    // when a haptic-enabled firmware is loaded onto the keyboard.
    eeprom_update_dword(EECONFIG_HAPTIC, 0);
#endif

    eeconfig_init_kb();
}

/** \brief eeconfig initialization
 *
 * FIXME: needs doc
 */
void eeconfig_init(void) { eeconfig_init_quantum(); }

/** \brief eeconfig enable
 *
 * FIXME: needs doc
 */
void eeconfig_enable(void) { eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER); }

/** \brief eeconfig disable
 *
 * FIXME: needs doc
 */
void eeconfig_disable(void) {
#ifdef STM32_EEPROM_ENABLE
    EEPROM_Erase();
#endif
#if defined(EEPROM_DRIVER)
    eeprom_driver_erase();
#endif
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER_OFF);
}

/** \brief eeconfig is enabled
 *
 * FIXME: needs doc
 */
bool eeconfig_is_enabled(void) { return (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER); }

/** \brief eeconfig is disabled
 *
 * FIXME: needs doc
 */
bool eeconfig_is_disabled(void) { return (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER_OFF); }

/** \brief eeconfig read debug
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_debug(void) { return eeprom_read_byte(EECONFIG_DEBUG); }
/** \brief eeconfig update debug
 *
 * FIXME: needs doc
 */
void eeconfig_update_debug(uint8_t val) { eeprom_update_byte(EECONFIG_DEBUG, val); }

/** \brief eeconfig read default layer
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_default_layer(void) { return eeprom_read_byte(EECONFIG_DEFAULT_LAYER); }
/** \brief eeconfig update default layer
 *
 * FIXME: needs doc
 */
void eeconfig_update_default_layer(uint8_t val) { eeprom_update_byte(EECONFIG_DEFAULT_LAYER, val); }

/** \brief eeconfig read keymap
 *
 * FIXME: needs doc
 */
uint16_t eeconfig_read_keymap(void) { return (eeprom_read_byte(EECONFIG_KEYMAP_LOWER_BYTE) | (eeprom_read_byte(EECONFIG_KEYMAP_UPPER_BYTE) << 8)); }
/** \brief eeconfig update keymap
 *
 * FIXME: needs doc
 */
void eeconfig_update_keymap(uint16_t val) {
    eeprom_update_byte(EECONFIG_KEYMAP_LOWER_BYTE, val & 0xFF);
    eeprom_update_byte(EECONFIG_KEYMAP_UPPER_BYTE, (val >> 8) & 0xFF);
}

/** \brief eeconfig read backlight
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_backlight(void) { return eeprom_read_byte(EECONFIG_BACKLIGHT); }
/** \brief eeconfig update backlight
 *
 * FIXME: needs doc
 */
void eeconfig_update_backlight(uint8_t val) { eeprom_update_byte(EECONFIG_BACKLIGHT, val); }

/** \brief eeconfig read audio
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_audio(void) { return eeprom_read_byte(EECONFIG_AUDIO); }
/** \brief eeconfig update audio
 *
 * FIXME: needs doc
 */
void eeconfig_update_audio(uint8_t val) { eeprom_update_byte(EECONFIG_AUDIO, val); }

/** \brief eeconfig read kb
 *
 * FIXME: needs doc
 */
uint32_t eeconfig_read_kb(void) { return eeprom_read_dword(EECONFIG_KEYBOARD); }
/** \brief eeconfig update kb
 *
 * FIXME: needs doc
 */
void eeconfig_update_kb(uint32_t val) { eeprom_update_dword(EECONFIG_KEYBOARD, val); }

/** \brief eeconfig read user
 *
 * FIXME: needs doc
 */
uint32_t eeconfig_read_user(void) { return eeprom_read_dword(EECONFIG_USER); }
/** \brief eeconfig update user
 *
 * FIXME: needs doc
 */
void eeconfig_update_user(uint32_t val) { eeprom_update_dword(EECONFIG_USER, val); }

/** \brief eeconfig read haptic
 *
 * FIXME: needs doc
 */
uint32_t eeconfig_read_haptic(void) { return eeprom_read_dword(EECONFIG_HAPTIC); }
/** \brief eeconfig update haptic
 *
 * FIXME: needs doc
 */
void eeconfig_update_haptic(uint32_t val) { eeprom_update_dword(EECONFIG_HAPTIC, val); }

/** \brief eeconfig read split handedness
 *
 * FIXME: needs doc
 */
bool eeconfig_read_handedness(void) { return !!eeprom_read_byte(EECONFIG_HANDEDNESS); }
/** \brief eeconfig update split handedness
 *
 * FIXME: needs doc
 */
void eeconfig_update_handedness(bool val) { eeprom_update_byte(EECONFIG_HANDEDNESS, !!val); }

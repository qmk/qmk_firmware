#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "eeconfig.h"

#ifdef STM32F303xC
#include "hal.h"
#include "eeprom_stm32.h"
#endif

/** \brief eeconfig initialization
 *
 * FIXME: needs doc
 */
void eeconfig_init(void)
{
#ifdef STM32F303xC
    EEPROM_format();
#endif
    eeprom_update_word(EECONFIG_MAGIC,          EECONFIG_MAGIC_NUMBER);
    eeprom_update_byte(EECONFIG_DEBUG,          0);
    eeprom_update_byte(EECONFIG_DEFAULT_LAYER,  0);
    eeprom_update_byte(EECONFIG_KEYMAP,         0);
    eeprom_update_byte(EECONFIG_MOUSEKEY_ACCEL, 0);
#ifdef BACKLIGHT_ENABLE
    eeprom_update_byte(EECONFIG_BACKLIGHT,      0);
#endif
#ifdef AUDIO_ENABLE
    eeprom_update_byte(EECONFIG_AUDIO,             0xFF); // On by default
#endif
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    eeprom_update_dword(EECONFIG_RGBLIGHT,      0);
#endif
#ifdef STENO_ENABLE
    eeprom_update_byte(EECONFIG_STENOMODE,      0);
#endif
}

/** \brief eeconfig enable
 *
 * FIXME: needs doc
 */
void eeconfig_enable(void)
{
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
}

/** \brief eeconfig disable
 *
 * FIXME: needs doc
 */
void eeconfig_disable(void)
{
#ifdef STM32F303xC
    EEPROM_format();
#endif
    eeprom_update_word(EECONFIG_MAGIC, 0xFFFF);
}

/** \brief eeconfig is enabled
 *
 * FIXME: needs doc
 */
bool eeconfig_is_enabled(void)
{
    return (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER);
}

/** \brief eeconfig read debug
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_debug(void)      { return eeprom_read_byte(EECONFIG_DEBUG); }
/** \brief eeconfig update debug
 *
 * FIXME: needs doc
 */
void eeconfig_update_debug(uint8_t val) { eeprom_update_byte(EECONFIG_DEBUG, val); }

/** \brief eeconfig read default layer
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_default_layer(void)      { return eeprom_read_byte(EECONFIG_DEFAULT_LAYER); }
/** \brief eeconfig update default layer
 *
 * FIXME: needs doc
 */
void eeconfig_update_default_layer(uint8_t val) { eeprom_update_byte(EECONFIG_DEFAULT_LAYER, val); }

/** \brief eeconfig read keymap
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_keymap(void)      { return eeprom_read_byte(EECONFIG_KEYMAP); }
/** \brief eeconfig update keymap
 *
 * FIXME: needs doc
 */
void eeconfig_update_keymap(uint8_t val) { eeprom_update_byte(EECONFIG_KEYMAP, val); }

#ifdef BACKLIGHT_ENABLE
/** \brief eeconfig read backlight
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_backlight(void)      { return eeprom_read_byte(EECONFIG_BACKLIGHT); }
/** \brief eeconfig update backlight
 *
 * FIXME: needs doc
 */
void eeconfig_update_backlight(uint8_t val) { eeprom_update_byte(EECONFIG_BACKLIGHT, val); }
#endif

#ifdef AUDIO_ENABLE
/** \brief eeconfig read audio
 *
 * FIXME: needs doc
 */
uint8_t eeconfig_read_audio(void)      { return eeprom_read_byte(EECONFIG_AUDIO); }
/** \brief eeconfig update audio
 *
 * FIXME: needs doc
 */
void eeconfig_update_audio(uint8_t val) { eeprom_update_byte(EECONFIG_AUDIO, val); }
#endif

#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "eeconfig.h"

void eeconfig_init(void)
{
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
#ifdef RGBLIGHT_ENABLE
    eeprom_update_dword(EECONFIG_RGBLIGHT,      0);
#endif
}

void eeconfig_enable(void)
{
    eeprom_update_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
}

void eeconfig_disable(void)
{
    eeprom_update_word(EECONFIG_MAGIC, 0xFFFF);
}

bool eeconfig_is_enabled(void)
{
    return (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER);
}

uint8_t eeconfig_read_debug(void)      { return eeprom_read_byte(EECONFIG_DEBUG); }
void eeconfig_update_debug(uint8_t val) { eeprom_update_byte(EECONFIG_DEBUG, val); }

uint8_t eeconfig_read_default_layer(void)      { return eeprom_read_byte(EECONFIG_DEFAULT_LAYER); }
void eeconfig_update_default_layer(uint8_t val) { eeprom_update_byte(EECONFIG_DEFAULT_LAYER, val); }

uint8_t eeconfig_read_keymap(void)      { return eeprom_read_byte(EECONFIG_KEYMAP); }
void eeconfig_update_keymap(uint8_t val) { eeprom_update_byte(EECONFIG_KEYMAP, val); }

#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void)      { return eeprom_read_byte(EECONFIG_BACKLIGHT); }
void eeconfig_update_backlight(uint8_t val) { eeprom_update_byte(EECONFIG_BACKLIGHT, val); }
#endif

#ifdef AUDIO_ENABLE
uint8_t eeconfig_read_audio(void)      { return eeprom_read_byte(EECONFIG_AUDIO); }
void eeconfig_update_audio(uint8_t val) { eeprom_update_byte(EECONFIG_AUDIO, val); }
#endif

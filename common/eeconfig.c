#include <stdint.h>
#include <stdbool.h>
#include <avr/eeprom.h>
#include "eeconfig.h"


void eeconfig_init(void)
{
    eeprom_write_word(EECONFIG_MAGIC,          EECONFIG_MAGIC_NUMBER);
    eeprom_write_byte(EECONFIG_DEBUG,          0);
    eeprom_write_byte(EECONFIG_DEFAULT_LAYER,  0);
    eeprom_write_byte(EECONFIG_KEYCONF,        0);
    eeprom_write_byte(EECONFIG_MOUSEKEY_ACCEL, 0);
}

void eeconfig_enable(void)
{
    eeprom_write_word(EECONFIG_MAGIC, EECONFIG_MAGIC_NUMBER);
}

void eeconfig_disable(void)
{
    eeprom_write_word(EECONFIG_MAGIC, 0xFFFF);
}

bool eeconfig_is_enabled(void)
{
    return EECONFIG_IS_ENABLED() && (eeprom_read_word(EECONFIG_MAGIC) == EECONFIG_MAGIC_NUMBER);
}

uint8_t eeconfig_read_debug(void)      { return eeprom_read_byte(EECONFIG_DEBUG); }
void eeconfig_write_debug(uint8_t val) { eeprom_write_byte(EECONFIG_DEBUG, val); }

uint8_t eeconfig_read_defalt_layer(void)      { return eeprom_read_byte(EECONFIG_DEFAULT_LAYER); }
void eeconfig_write_defalt_layer(uint8_t val) { eeprom_write_byte(EECONFIG_DEFAULT_LAYER, val); }

uint8_t eeconfig_read_keyconf(void)      { return eeprom_read_byte(EECONFIG_KEYCONF); }
void eeconfig_write_keyconf(uint8_t val) { eeprom_write_byte(EECONFIG_KEYCONF, val); }

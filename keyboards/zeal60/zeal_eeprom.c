#include "zeal_eeprom.h"
#include "tmk_core/common/eeprom.h"

bool eeprom_is_valid(void)
{
	return (eeprom_read_word(EEPROM_MAGIC_ADDR) == EEPROM_MAGIC &&
			eeprom_read_byte(EEPROM_VERSION_ADDR) == EEPROM_VERSION);
}

void eeprom_set_valid(bool valid)
{
	eeprom_update_word(EEPROM_MAGIC_ADDR, valid ? EEPROM_MAGIC : 0xFFFF);
	eeprom_update_byte(EEPROM_VERSION_ADDR, valid ? EEPROM_VERSION : 0xFF);
}

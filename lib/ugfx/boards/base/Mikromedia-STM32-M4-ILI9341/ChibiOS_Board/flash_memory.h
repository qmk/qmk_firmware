void flash_sector_erase(gU32 sector);
void flash_read(gU32 address, gMemSize bytes, gU8 *out);
void flash_write(gU32 address, gMemSize bytes, const gU8 *data);
bool flash_tp_calibrated(void);
void flash_tp_calibration_save(gU16 instance, const gU8 *calbuf, gMemSize sz);
const char *flash_tp_calibration_load(gU16 instance);

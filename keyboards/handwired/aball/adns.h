
void adns_begin(void);

void adns_end(void);

void adns_write(uint8_t reg_addr, uint8_t data);

uint8_t adns_read(uint8_t reg_addr);

void pointing_device_init(void);

int16_t convertDeltaToInt(uint8_t high, uint8_t low);

void readSensor(void);

void pointing_device_task(void);

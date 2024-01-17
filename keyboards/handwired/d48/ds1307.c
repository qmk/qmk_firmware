#include "ds1307.h"
#include "i2c_master.h"

void ds1307_set_time(uint8_t h, uint8_t m, uint8_t s) {
    uint8_t data[] = {
        ((s % 10) | ((s / 10) << 4)) & 0x7F,
        ((m % 10) | ((m / 10) << 4)) & 0x7F,
        ((h % 10) | ((h / 10) << 4)) & 0x3F,
        0, 0, 0, 0, 0
    }; // 24-hour mode
    i2c_write_register(DS1307_ADDR, 0, data, 8, 100);
}

void ds1307_get_time(uint8_t *h, uint8_t *m, uint8_t *s) {
    uint8_t data[3];
    i2c_read_register(DS1307_ADDR, 0, data, 3, 100);
    i2c_stop();
    *s = (data[0] & 0b1111) + ((data[0] & 0b1110000) >> 4) * 10;
    *m = (data[1] & 0b1111) + ((data[1] & 0b1110000) >> 4) * 10;
    *h = (data[2] & 0b1111) + ((data[2] & 0b0110000) >> 4) * 10;
}

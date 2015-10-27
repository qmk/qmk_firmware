#include "TMP102.h"

#define TEMP_REG_ADDR 0x00

TMP102::TMP102(PinName sda, PinName scl, int addr) : m_i2c(sda, scl), m_addr(addr) {
    m_i2c.frequency(400000);
}
TMP102::~TMP102() { }

float TMP102::read() {
    const char tempRegAddr = TEMP_REG_ADDR;

    m_i2c.write(m_addr, &tempRegAddr, 1);

    char reg[2] = {0,0};
    m_i2c.read(m_addr, reg, 2);

    unsigned short res = (reg[0] << 4) | (reg[1] >> 4);

    float temp =  (float) ((float)res * 0.0625);

    return temp;
}

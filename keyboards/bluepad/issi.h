#ifndef ISSI_H
#define ISSI_H

void issi_init(void);
// uint8_t readRegister8(uint8_t bank, uint8_t reg);
void activateLED(uint8_t matrix, uint8_t cy, uint8_t cx, uint8_t pwm);
void writeRegister8(uint8_t frame, uint8_t reg, uint8_t data);

#endif
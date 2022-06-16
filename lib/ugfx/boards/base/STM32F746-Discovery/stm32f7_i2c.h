#pragma once

#include "stm32f7xx.h"
#include "gfx.h"

gBool i2cInit(I2C_TypeDef* i2c);

void i2cSend(I2C_TypeDef* i2c, gU8 slaveAddr, gU8* data, gU16 length);
void i2cSendByte(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 data);
void i2cWriteReg(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 regAddr, gU8 value);

void i2cRead(I2C_TypeDef* i2c, gU8 slaveAddr, gU8* data, gU16 length);
gU8 i2cReadByte(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 regAddr);
gU16 i2cReadWord(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 regAddr);

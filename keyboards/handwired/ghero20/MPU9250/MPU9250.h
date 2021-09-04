#pragma once

#ifndef MPU9250_H
#define MPU9250_H

#include "MPU9250RegisterMap.h"
#include "i2c_master.h"

#endif

enum Axis {
    x,
    y,
    z,
    kAxis,
};

typedef int16_t mpu_data_t;

#define MPU9250_ADDR    (0x68 << 1)
#define I2C_TIMEOUT     1000
#define MPU_POLLRATE    50

#ifndef MPU_ANGLE_SENS
    #define MPU_ANGLE_SENS 60
#endif

#ifndef MPU_SPEED_SENS
    #define MPU_SPEED_SENS -700
#endif


i2c_status_t mpu_readAccel(int16_t* read);
i2c_status_t mpu_readGyro(int16_t* read);
i2c_status_t mpu_readAccelGyro(int16_t* read);

extern i2c_status_t update_accel_gyro(void);
extern int16_t mpu_readTemp(void);
extern void initMPU9250(void);

extern float getAcc(const uint8_t i);
extern float getGyro(const uint8_t i);
extern int16_t getAccScaled(const uint8_t i, const uint8_t o);
extern int16_t getGyroScaled(const uint8_t i, const uint8_t o);
extern mpu_data_t getAccRaw(const uint8_t i);
extern mpu_data_t getGyroRaw(const uint8_t i);

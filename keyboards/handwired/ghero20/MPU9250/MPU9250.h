/* Copyright 2021 bryan065
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "MPU9250RegisterMap.h"
#include "i2c_master.h"

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

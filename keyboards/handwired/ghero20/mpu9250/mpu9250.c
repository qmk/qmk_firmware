/* Copyright 2021 bryan065 / hideakitai
 *
 * https://github.com/hideakitai/MPU9250
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

#include "mpu9250.h"
#include "wait.h"

uint8_t send_data;

float acc_resolution  = 0.f;                // scale resolutions per LSB for the sensors
float gyro_resolution = 0.f;                // scale resolutions per LSB for the sensors
float mag_resolution  = 0.f;                // scale resolutions per LSB for the sensors

float Acc[kAxis], Gyro[kAxis];

i2c_status_t update_accel_gyro(void) {
    int16_t data[7];        // used to read all 14 bytes at once from the MPU9250 accel/gyro
    i2c_status_t status = mpu_readAccelGyro(data);

    if (status == I2C_STATUS_SUCCESS) {
        // Now we'll calculate the accleration value into actual g's
        Acc[x] = (float)data[0] * acc_resolution;  // get actual g value, this depends on scale being set
        Acc[y] = (float)data[1] * acc_resolution;
        Acc[z] = (float)data[2] * acc_resolution;

        // Calculate the gyro value into actual degrees per second
        Gyro[x] = (float)data[4] * gyro_resolution;  // get actual gyro value, this depends on scale being set
        Gyro[y] = (float)data[5] * gyro_resolution;
        Gyro[z] = (float)data[6] * gyro_resolution;
    };

    return status;
}

i2c_status_t mpu_readAccel(int16_t* read) {
    uint8_t data[6];
    i2c_status_t status = i2c_readReg(MPU9250_ADDR,ACCEL_XOUT_H,data,sizeof(data),I2C_TIMEOUT);

    if (status == I2C_STATUS_SUCCESS) {
        read[0] = ((int16_t)data[0]<<8) | (int16_t)data[1];
        read[1] = ((int16_t)data[2]<<8) | (int16_t)data[3];
        read[2] = ((int16_t)data[4]<<8) | (int16_t)data[5];
    };

    return status;
}

i2c_status_t mpu_readGyro(int16_t* read) {
    uint8_t data[6];
    i2c_status_t status = i2c_readReg(MPU9250_ADDR,GYRO_XOUT_H,data,sizeof(data),I2C_TIMEOUT);        // Read 8-bit / 1-byte of data from register
                                                                                                      // save to data array of 2 bytes (16-bit data register)
    if (status == I2C_STATUS_SUCCESS) {
        read[0] = ((int16_t)data[0]<<8) | (int16_t)data[1];
        read[1] = ((int16_t)data[2]<<8) | (int16_t)data[3];
        read[2] = ((int16_t)data[4]<<8) | (int16_t)data[5];
    };

    return status;
}

i2c_status_t mpu_readAccelGyro(int16_t* read) {
    uint8_t data[14];
    i2c_status_t status = i2c_readReg(MPU9250_ADDR,ACCEL_XOUT_H,data,sizeof(data),I2C_TIMEOUT);    // Read the 14 raw data registers into data array

    if (status == I2C_STATUS_SUCCESS) {
        read[0] = ((int16_t)data[0]<<8) | (int16_t)data[1];
        read[1] = ((int16_t)data[2]<<8) | (int16_t)data[3];
        read[2] = ((int16_t)data[4]<<8) | (int16_t)data[5];
        read[3] = ((int16_t)data[6]<<8) | (int16_t)data[7];
        read[4] = ((int16_t)data[8]<<8) | (int16_t)data[9];
        read[5] = ((int16_t)data[10]<<8) | (int16_t)data[11];
        read[6] = ((int16_t)data[12]<<8) | (int16_t)data[13];
    };

    return status;
}

int16_t mpu_readTemp(void) {
    uint8_t data[2];
    i2c_readReg(MPU9250_ADDR,TEMP_OUT_H,data,sizeof(data),I2C_TIMEOUT);
    return (data[0]<<8|data[1])/334+21;;
}

void initMPU9250(void) {
    acc_resolution = 16.0 / 32768.0;
    gyro_resolution = 2000.0 / 32768.0;

    // reset device
    send_data = 0x80;
    i2c_writeReg(MPU9250_ADDR, PWR_MGMT_1, &send_data, 1, I2C_TIMEOUT);  // Write a one to bit 7 reset bit; toggle reset device
    _delay_ms(100);

    // wake up device
    send_data = 0x00;
    i2c_writeReg(MPU9250_ADDR, PWR_MGMT_1, &send_data, 1, I2C_TIMEOUT);  // Clear sleep mode bit (6), enable all sensors
    _delay_ms(100);

    // get stable time source
    send_data = 0x01;
    i2c_writeReg(MPU9250_ADDR, PWR_MGMT_1, &send_data, 1, I2C_TIMEOUT);  // Auto select clock source to be PLL gyroscope reference if ready else
    _delay_ms(200);

    // Configure Gyro and Thermometer
    send_data = 0x03;
    i2c_writeReg(MPU9250_ADDR, MPU_CONFIG, &send_data, 1, I2C_TIMEOUT);

    // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
    send_data = 0x04;
    i2c_writeReg(MPU9250_ADDR, SMPLRT_DIV, &send_data, 1, I2C_TIMEOUT);  // Use a 200 Hz rate; a rate consistent with the filter update rate

    // Set gyroscope full scale range
    // Range selects FS_SEL and GFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
    uint8_t c[1];
    i2c_readReg(MPU9250_ADDR, GYRO_CONFIG, c, 1, I2C_TIMEOUT);      // get current GYRO_CONFIG register value
    c[0] = c[0] & ~0xE0;                                            // Clear self-test bits [7:5]
    c[0] = c[0] & ~0x03;                                            // Clear Fchoice bits [1:0]
    c[0] = c[0] & ~0x18;                                            // Clear GYRO_FS_SEL bits [4:3]
    c[0] = c[0] | (0x03 << 3);                                      // Set full scale range for the gyro
    c[0] = c[0] | 0x03;                                             // Set Fchoice for the gyro
    i2c_writeReg(MPU9250_ADDR, GYRO_CONFIG, c, 1, I2C_TIMEOUT);     // Write new GYRO_CONFIG value to register

    // Set accelerometer full-scale range configuration
    i2c_readReg(MPU9250_ADDR, ACCEL_CONFIG, c, 1, I2C_TIMEOUT);     // get current ACCEL_CONFIG register value
    c[0] = c[0] & ~0xE0;                                            // Clear self-test bits [7:5]
    c[0] = c[0] & ~0x18;                                            // Clear ACCEL_FS_SEL bits [4:3]
    c[0] = c[0] | (0x03 << 3);                                      // Set full scale range for the accelerometer
    i2c_writeReg(MPU9250_ADDR, ACCEL_CONFIG, c, 1, I2C_TIMEOUT);    // Write new ACCEL_CONFIG register value

    // Set accelerometer sample rate configuration
    // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
    // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
    i2c_readReg(MPU9250_ADDR, ACCEL_CONFIG2, c, 1, I2C_TIMEOUT);    // get current ACCEL_CONFIG2 register value
    c[0] = c[0] & ~0x0F;                                            // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
    c[0] = c[0] | (~(0x01 << 3) & 0x08);                            // Set accel_fchoice_b to 1
    c[0] = c[0] | (0x03 & 0x07);                                    // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
    i2c_writeReg(MPU9250_ADDR, ACCEL_CONFIG2, c, 1, I2C_TIMEOUT);   // Write new ACCEL_CONFIG2 register value

    // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
    // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

    // Configure Interrupts and Bypass Enable
    // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
    // clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips
    // can join the I2C bus and all can be controlled by the Arduino as master
    send_data = 0x22;
    i2c_writeReg(MPU9250_ADDR, INT_PIN_CFG, &send_data, 1, I2C_TIMEOUT);
    send_data = 0x01;
    i2c_writeReg(MPU9250_ADDR, INT_ENABLE, &send_data, 1, I2C_TIMEOUT);
    _delay_ms(100);
}

// get accel and gyro data as float
float getAcc(const uint8_t i) {
    return (i < 3) ? Acc[i] : 0.f;
}


float getGyro(const uint8_t i) {
    return (i < 3) ? Gyro[i] : 0.f;
}

// Get scaled raw data as int16 instead of float
int16_t getAccScaled(const uint8_t i, const uint8_t o) {
    if (i >= 3) {return 0;};

    int16_t data;
    float scale;
    scale = Acc[i] * o;
    data = (int16_t)scale;

    return data;
}

int16_t getGyroScaled(const uint8_t i, const uint8_t o) {
    if (i >= 3) {return 0;};

    int16_t data;
    float scale;
    scale = Gyro[i] * o;
    data = (int16_t)scale;

    return data;
}

// Get Raw accel and gyro data
mpu_data_t getAccRaw(const uint8_t i) {
    mpu_data_t raw[3];
    if (i < 3) {
        mpu_readAccel(raw);
        return raw[i];
    }
    else {
        return 0;
    };
}


mpu_data_t getGyroRaw(const uint8_t i) {
    mpu_data_t raw[3];
    if (i < 3) {
        mpu_readGyro(raw);
        return raw[i];
    }
    else {
        return 0;
    };
}

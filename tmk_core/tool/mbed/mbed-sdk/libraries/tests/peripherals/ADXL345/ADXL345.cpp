/**
 * @author Aaron Berk
 *
 * @section LICENSE
 *
 * Copyright (c) 2010 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * ADXL345, triple axis, digital interface, accelerometer.
 *
 * Datasheet:
 *
 * http://www.analog.com/static/imported-files/data_sheets/ADXL345.pdf
 */

/**
 * Includes
 */
#include "ADXL345.h"

ADXL345::ADXL345(PinName mosi,
                 PinName miso,
                 PinName sck,
                 PinName cs) : spi_(mosi, miso, sck), nCS_(cs) {

    //2MHz, allowing us to use the fastest data rates.
    spi_.frequency(2000000);
    spi_.format(8,3);

    nCS_ = 1;

    wait_us(500);

}

int ADXL345::getDevId(void) {

    return oneByteRead(ADXL345_DEVID_REG);

}

int ADXL345::getTapThreshold(void) {

    return oneByteRead(ADXL345_THRESH_TAP_REG);

}

void ADXL345::setTapThreshold(int threshold) {

    oneByteWrite(ADXL345_THRESH_TAP_REG, threshold);

}

int ADXL345::getOffset(int axis) {

    int address = 0;

    if (axis == ADXL345_X) {
        address = ADXL345_OFSX_REG;
    } else if (axis == ADXL345_Y) {
        address = ADXL345_OFSY_REG;
    } else if (axis == ADXL345_Z) {
        address = ADXL345_OFSZ_REG;
    }

    return oneByteRead(address);

}

void ADXL345::setOffset(int axis, char offset) {

    int address = 0;

    if (axis == ADXL345_X) {
        address = ADXL345_OFSX_REG;
    } else if (axis == ADXL345_Y) {
        address = ADXL345_OFSY_REG;
    } else if (axis == ADXL345_Z) {
        address = ADXL345_OFSZ_REG;
    }

    return oneByteWrite(address, offset);

}

int ADXL345::getTapDuration(void) {

    return oneByteRead(ADXL345_DUR_REG)*625;

}

void ADXL345::setTapDuration(int duration_us) {

    int tapDuration = duration_us / 625;

    oneByteWrite(ADXL345_DUR_REG, tapDuration);

}

float ADXL345::getTapLatency(void) {

    return oneByteRead(ADXL345_LATENT_REG)*1.25;

}

void ADXL345::setTapLatency(int latency_ms) {

    int tapLatency = latency_ms / 1.25;

    oneByteWrite(ADXL345_LATENT_REG, tapLatency);

}

float ADXL345::getWindowTime(void) {

    return oneByteRead(ADXL345_WINDOW_REG)*1.25;

}

void ADXL345::setWindowTime(int window_ms) {

    int windowTime = window_ms / 1.25;

    oneByteWrite(ADXL345_WINDOW_REG, windowTime);

}

int ADXL345::getActivityThreshold(void) {

    return oneByteRead(ADXL345_THRESH_ACT_REG);

}

void ADXL345::setActivityThreshold(int threshold) {

    oneByteWrite(ADXL345_THRESH_ACT_REG, threshold);

}

int ADXL345::getInactivityThreshold(void) {

    return oneByteRead(ADXL345_THRESH_INACT_REG);

}

void ADXL345::setInactivityThreshold(int threshold) {

    return oneByteWrite(ADXL345_THRESH_INACT_REG, threshold);

}

int ADXL345::getTimeInactivity(void) {

    return oneByteRead(ADXL345_TIME_INACT_REG);

}

void ADXL345::setTimeInactivity(int timeInactivity) {

    oneByteWrite(ADXL345_TIME_INACT_REG, timeInactivity);

}

int ADXL345::getActivityInactivityControl(void) {

    return oneByteRead(ADXL345_ACT_INACT_CTL_REG);

}

void ADXL345::setActivityInactivityControl(int settings) {

    oneByteWrite(ADXL345_ACT_INACT_CTL_REG, settings);

}

int ADXL345::getFreefallThreshold(void) {

    return oneByteRead(ADXL345_THRESH_FF_REG);

}

void ADXL345::setFreefallThreshold(int threshold) {

    oneByteWrite(ADXL345_THRESH_FF_REG, threshold);

}

int ADXL345::getFreefallTime(void) {

    return oneByteRead(ADXL345_TIME_FF_REG)*5;

}

void ADXL345::setFreefallTime(int freefallTime_ms) {

    int freefallTime = freefallTime_ms / 5;

    oneByteWrite(ADXL345_TIME_FF_REG, freefallTime);

}

int ADXL345::getTapAxisControl(void) {

    return oneByteRead(ADXL345_TAP_AXES_REG);

}

void ADXL345::setTapAxisControl(int settings) {

    oneByteWrite(ADXL345_TAP_AXES_REG, settings);

}

int ADXL345::getTapSource(void) {

    return oneByteRead(ADXL345_ACT_TAP_STATUS_REG);

}

void ADXL345::setPowerMode(char mode) {

    //Get the current register contents, so we don't clobber the rate value.
    char registerContents = oneByteRead(ADXL345_BW_RATE_REG);

    registerContents = (mode << 4) | registerContents;

    oneByteWrite(ADXL345_BW_RATE_REG, registerContents);

}

int ADXL345::getPowerControl(void) {

    return oneByteRead(ADXL345_POWER_CTL_REG);

}

void ADXL345::setPowerControl(int settings) {

    oneByteWrite(ADXL345_POWER_CTL_REG, settings);

}

int ADXL345::getInterruptEnableControl(void) {

    return oneByteRead(ADXL345_INT_ENABLE_REG);

}

void ADXL345::setInterruptEnableControl(int settings) {

    oneByteWrite(ADXL345_INT_ENABLE_REG, settings);

}

int ADXL345::getInterruptMappingControl(void) {

    return oneByteRead(ADXL345_INT_MAP_REG);

}

void ADXL345::setInterruptMappingControl(int settings) {

    oneByteWrite(ADXL345_INT_MAP_REG, settings);

}

int ADXL345::getInterruptSource(void){

    return oneByteRead(ADXL345_INT_SOURCE_REG);

}

int ADXL345::getDataFormatControl(void){

    return oneByteRead(ADXL345_DATA_FORMAT_REG);

}

void ADXL345::setDataFormatControl(int settings){

    oneByteWrite(ADXL345_DATA_FORMAT_REG, settings);

}

void ADXL345::setDataRate(int rate) {

    //Get the current register contents, so we don't clobber the power bit.
    char registerContents = oneByteRead(ADXL345_BW_RATE_REG);

    registerContents &= 0x10;
    registerContents |= rate;

    oneByteWrite(ADXL345_BW_RATE_REG, registerContents);

}

void ADXL345::getOutput(int* readings){

    char buffer[6];

    multiByteRead(ADXL345_DATAX0_REG, buffer, 6);

    readings[0] = (int)buffer[1] << 8 | (int)buffer[0];
    readings[1] = (int)buffer[3] << 8 | (int)buffer[2];
    readings[2] = (int)buffer[5] << 8 | (int)buffer[4];

}

int ADXL345::getFifoControl(void){

    return oneByteRead(ADXL345_FIFO_CTL);

}

void ADXL345::setFifoControl(int settings){

    oneByteWrite(ADXL345_FIFO_STATUS, settings);

}

int ADXL345::getFifoStatus(void){

    return oneByteRead(ADXL345_FIFO_STATUS);

}

int ADXL345::oneByteRead(int address) {

    int tx = (ADXL345_SPI_READ | (address & 0x3F));
    int rx = 0;

    nCS_ = 0;
    //Send address to read from.
    spi_.write(tx);
    //Read back contents of address.
    rx = spi_.write(0x00);
    nCS_ = 1;

    return rx;

}

void ADXL345::oneByteWrite(int address, char data) {

    int tx = (ADXL345_SPI_WRITE | (address & 0x3F));

    nCS_ = 0;
    //Send address to write to.
    spi_.write(tx);
    //Send data to be written.
    spi_.write(data);
    nCS_ = 1;

}

void ADXL345::multiByteRead(int startAddress, char* buffer, int size) {

    int tx = (ADXL345_SPI_READ | ADXL345_MULTI_BYTE | (startAddress & 0x3F));

    nCS_ = 0;
    //Send address to start reading from.
    spi_.write(tx);

    for (int i = 0; i < size; i++) {
        buffer[i] = spi_.write(0x00);
    }

    nCS_ = 1;

}

void ADXL345::multiByteWrite(int startAddress, char* buffer, int size) {

    int tx = (ADXL345_SPI_WRITE | ADXL345_MULTI_BYTE | (startAddress & 0x3F));

    nCS_ = 0;
    //Send address to start reading from.
    spi_.write(tx);

    for (int i = 0; i < size; i++) {
        buffer[i] = spi_.write(0x00);
    }

    nCS_ = 1;

}

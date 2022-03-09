#include "paw3204.h"
#include "wait.h"
#include "debug.h"
#include "gpio.h"

uint8_t datatogglestate;
#define REG_PID1 0x00
#define REG_PID2 0x01
#define REG_STAT 0x02
#define REG_X 0x03
#define REG_Y 0x04

#define REG_SETUP 0x06
#define REG_IMGQUAL 0x07
#define REG_IMGREC 0x0E
#define REG_IMGTRASH 0x0D

void PAW3204_init(void) {
    setPinOutput(PAW3204_SCLK);    // setclockpin to outpu
    setPinInputHigh(PAW3204_DATA); // set datapin input high

    PAW3204_write_reg(REG_SETUP, 0x86); // reset sensor and set 1600cpi
    wait_us(5);

    PAW3204_read_reg(0x00); // read id
    PAW3204_read_reg(0x01); // read id2
    // PAW3204_write_reg(REG_SETUP,0x06);  // dont reset sensor and set cpi 1600
    PAW3204_write_reg(REG_IMGTRASH, 0x32); // write image trashhold
}

uint8_t PAW3204_serial_read(void) {
    setPinInput(PAW3204_DATA);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        writePinLow(PAW3204_SCLK);
        wait_us(1);

        byte = (byte << 1) | readPin(PAW3204_DATA);

        writePinHigh(PAW3204_SCLK);
        wait_us(1);
    }

    return byte;
}

void PAW3204_serial_write(uint8_t data) {
    datatogglestate = readPin(PAW3204_DATA);
    if (datatogglestate == 1) {
        writePinLow(PAW3204_DATA);
    } else {
        writePinLow(PAW3204_DATA);
    }
    setPinOutput(PAW3204_DATA);

    for (int8_t b = 7; b >= 0; b--) {
        writePinLow(PAW3204_SCLK);
        if (data & (1 << b))
            writePinHigh(PAW3204_DATA);
        else
            writePinLow(PAW3204_DATA);
        // wait_us(2);
        writePinHigh(PAW3204_SCLK);
    }

    wait_us(4);
}

int8_t convert_twoscomp(uint8_t data) {
    if ((data & 0x80) == 0x80)
        return -128 + (data & 0x7F);
    else
        return data;
}

report_paw3204_t PAW3204_read(void) {
    report_paw3204_t data;
    uint8_t          pid  = read_pid_paw3204();
    uint8_t          stat = PAW3204_read_reg(REG_STAT);
    if (pid == 0x30 && (stat == 0x84 || stat == 0x86)) {
        data.x = convert_twoscomp(PAW3204_read_reg(REG_X));
        data.y = convert_twoscomp(PAW3204_read_reg(REG_Y));
    }

    return data;
}

void PAW3204_write_reg(uint8_t reg_addr, uint8_t data) {
    PAW3204_serial_write(0b10000000 | reg_addr);
    PAW3204_serial_write(data);
}

uint8_t PAW3204_read_reg(uint8_t reg_addr) {
    // adns5050_cs_select();
    // togglePin(PAW3204_DATA);
    // wait_us(1);

    // setPinOutput(PAW3204_DATA);

    PAW3204_serial_write(reg_addr);

    // We don't need a minimum tSRAD here. That's because a 4ms wait time is
    // already included in adns5050_serial_write(), so we're good.
    // See page 10 and 15 of the ADNS spec sheet.
    wait_us(5);
    // setPinInputHigh(PAW3204_DATA);
    uint8_t byte = PAW3204_serial_read();

    // tSRW & tSRR. See page 15 of the ADNS spec sheet.
    // Technically, this is only necessary if the next operation is an SDIO
    // read or write. This is not guaranteed to be the case.
    // Honestly, this wait could probably be removed.
    // wait_us(1);

    // adns5050_cs_deselect();

    return byte;
}

uint8_t read_pid_paw3204(void) {
    uint8_t byte = PAW3204_read_reg(REG_PID1);
    return byte;

#ifdef ISSI_ENABLE

#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <util/twi.h>
#include "issi.h"
#include "print.h"
#include "TWIlib.h"

#define ISSI_ADDR_DEFAULT 0xE8

#define ISSI_REG_CONFIG 0x00
#define ISSI_REG_CONFIG_PICTUREMODE 0x00
#define ISSI_REG_CONFIG_AUTOPLAYMODE 0x08

#define ISSI_CONF_PICTUREMODE 0x00
#define ISSI_CONF_AUTOFRAMEMODE 0x04
#define ISSI_CONF_AUDIOMODE 0x08

#define ISSI_REG_PICTUREFRAME 0x01

#define ISSI_REG_SHUTDOWN 0x0A
#define ISSI_REG_AUDIOSYNC 0x06

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_BANK_FUNCTIONREG 0x0B // helpfully called 'page nine'
uint8_t control[8][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
};
ISSIDeviceStruct *issi_devices[4] = {0, 0, 0, 0};

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define I2C_WRITE 0
#define F_SCL 400000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

uint8_t i2c_start(uint8_t address)
{
    // reset TWI control register
    TWCR = 0;
    // transmit START condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    // wait for end of transmission
    while( !(TWCR & (1<<TWINT)) );

    // check if the start condition was successfully transmitted
    if((TWSR & 0xF8) != TW_START){ return 1; }

    // load slave address into data register
    TWDR = address;
    // start transmission of address
    TWCR = (1<<TWINT) | (1<<TWEN);
    // wait for end of transmission
    while( !(TWCR & (1<<TWINT)) );

    // check if the device has acknowledged the READ / WRITE mode
    uint8_t twst = TW_STATUS & 0xF8;
    if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

    return 0;
}

uint8_t i2c_write(uint8_t data)
{
    // load data into data register
    TWDR = data;
    // start transmission of data
    TWCR = (1 << TWINT) | (1 << TWEN);
    // wait for end of transmission
    while (!(TWCR & (1 << TWINT)))
        ;

    if ((TWSR & 0xF8) != TW_MT_DATA_ACK) {
        return 1;
    }
    return 0;
}

uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length)
{
    TWBR = (uint8_t)TWBR_val;
    if (i2c_start(address | I2C_WRITE))
        return 1;
    for (uint16_t i = 0; i < length; i++) {
        if (i2c_write(data[i]))
            return 1;
    }
    // transmit STOP condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    return 0;
}

void setFrame(uint8_t device, uint8_t frame)
{
    static uint8_t current_frame = -1;
    if(current_frame != frame){
        uint8_t payload[] = {
            ISSI_ADDR_DEFAULT | device << 1,
            ISSI_COMMANDREGISTER,
            frame
        };
        TWITransmitData(payload, sizeof(payload), 0, 1);
    }
    // static uint8_t current_frame = 0xFF;
    // if(current_frame == frame){
    //     // return;
    // }
    // uint8_t payload[2] = { ISSI_COMMANDREGISTER, frame };
    // i2c_transmit(ISSI_ADDR_DEFAULT | device << 1, payload, 2);
    // current_frame = frame;
}

void writeRegister8(uint8_t device, uint8_t frame, uint8_t reg, uint8_t data)
{
    // Set the frame
    setFrame(device, frame);

    // Write to the register
    uint8_t payload[] = {
        ISSI_ADDR_DEFAULT | device << 1,
        reg,
        data
    };
    TWITransmitData(payload, sizeof(payload), 0, 1);
}

// void activateLED(uint8_t matrix, uint8_t cx, uint8_t cy, uint8_t pwm)
// {
//     xprintf("activeLED: %02X %02X %02X %02X\n", matrix, cy, cx, pwm);
//     uint8_t x = cx - 1;  // funciton takes 1 based counts, but we need 0...
//     uint8_t y = cy - 1;  // creating them once for less confusion
//     if(pwm == 0){
//         cbi(control[matrix][y], x);
//     }else{
//         sbi(control[matrix][y], x);
//     }
//     uint8_t device = (matrix & 0x06) >> 1;
//     uint8_t control_reg = (y << 1) | (matrix & 0x01);
//     uint8_t pwm_reg = 0;
//     switch(matrix & 0x01){
//         case 0:
//             pwm_reg = 0x24;
//             break;
//         case 1:
//             pwm_reg = 0x2C;
//             break;
//     }
//     pwm_reg += (y << 4) + x;
//     xprintf("  device: %02X\n", device);
//     xprintf("  control: %02X %02X\n", control_reg, control[matrix][y]);
//     xprintf("  pwm:     %02X %02X\n", pwm_reg, pwm);
//     writeRegister8(device, 0, control_reg, control[matrix][y]);
//     writeRegister8(device, 0, control_reg + 0x12, control[matrix][y]);
//     writeRegister8(device, 0, pwm_reg, pwm);
// }

void activateLED(uint8_t matrix, uint8_t cx, uint8_t cy, uint8_t pwm)
{
    uint8_t device_addr = (matrix & 0x06) >> 1;
    ISSIDeviceStruct *device = issi_devices[device_addr];
    if(device == 0){
        return;
    }
    // xprintf("activeLED: %02X %02X %02X %02X\n", matrix, cy, cx, pwm);
    uint8_t x = cx - 1;  // funciton takes 1 based counts, but we need 0...
    uint8_t y = cy - 1;  // creating them once for less confusion
    uint8_t control_reg = (y << 1) | (matrix & 0x01);
    if(pwm == 0){
        cbi(device->led_ctrl[control_reg], x);
        cbi(device->led_blink_ctrl[control_reg], x);
     }else{
        sbi(device->led_ctrl[control_reg], x);
        sbi(device->led_blink_ctrl[control_reg], x);
    }
    uint8_t pwm_reg = 0;
    switch(matrix & 0x01){
        case 0:
            pwm_reg = 0x00;
            break;
        case 1:
            pwm_reg = 0x08;
            break;
    }
    pwm_reg += (y << 4) + x;
    // xprintf("  device_addr: %02X\n", device_addr);
    // xprintf("  control: %02X %02X\n", control_reg, control[matrix][y]);
    // xprintf("  pwm:     %02X %02X\n", pwm_reg, pwm);
    // writeRegister8(device_addr, 0, control_reg, control[matrix][y]);
    device->led_pwm[pwm_reg] = pwm;
    device->led_dirty = 1;

    // writeRegister8(device_addr, 0, control_reg + 0x12, control[matrix][y]);
    // writeRegister8(device_addr, 0, pwm_reg, pwm);
}

void update_issi(uint8_t device_addr, uint8_t blocking)
{
    // This seems to take about 6ms
    ISSIDeviceStruct *device = issi_devices[device_addr];
    if(device != 0){
        if(device->fn_dirty){
            device->fn_dirty = 0;
            setFrame(device_addr, ISSI_BANK_FUNCTIONREG);
            TWITransmitData(&device->fn_device_addr, sizeof(device->fn_registers) + 2, 0, 1);
        }
        if(device->led_dirty){
            device->led_dirty = 0;
            setFrame(device_addr, 0);
            TWITransmitData(&device->led_device_addr, 0xB6, 0, blocking);
        }
    }
}

void issi_init(void)
{
    // Set LED_EN/SDB high to enable the chip
    xprintf("Enabing SDB on pin: %d\n", LED_EN_PIN);
    _SFR_IO8((LED_EN_PIN >> 4) + 1) &= ~_BV(LED_EN_PIN & 0xF); // IN
    _SFR_IO8((LED_EN_PIN >> 4) + 2) |=  _BV(LED_EN_PIN & 0xF); // HI
    TWIInit();
    for(uint8_t device_addr = 0; device_addr < 4; device_addr++){
        xprintf("ISSI Init device: %d\n", device_addr);
        // If this device has been previously allocated, free it
        if(issi_devices[device_addr] != 0){
            free(issi_devices[device_addr]);
        }
        // Try to shutdown the device, if this fails skip this device
        writeRegister8(device_addr, ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x00);
        while (!isTWIReady()){_delay_us(1);}
        if(TWIInfo.errorCode != 0xFF){
            xprintf("ISSI init failed %d %02X %02X\n", device_addr, TWIInfo.mode, TWIInfo.errorCode);
            continue;
        }
        // Allocate the device structure - calloc zeros it for us
        ISSIDeviceStruct *device = (ISSIDeviceStruct *)calloc(sizeof(ISSIDeviceStruct) * 2, 1);
        issi_devices[device_addr] = device;
        device->fn_device_addr = ISSI_ADDR_DEFAULT | device_addr << 1;
        device->fn_register_addr = 0;
        device->led_device_addr = ISSI_ADDR_DEFAULT | device_addr << 1;
        device->led_register_addr = 0;
        // set dirty bits so that all of the buffered data is written out
        device->fn_dirty = 1;
        device->led_dirty = 1;
        update_issi(device_addr, 1);
        // Set the function register to picture mode
        // device->fn_reg[ISSI_REG_CONFIG] = ISSI_REG_CONFIG_PICTUREMODE;
        writeRegister8(device_addr, ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x01);
    }

    // Shutdown and set all registers to 0
    // writeRegister8(device_addr, ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x00);
    // for(uint8_t bank = 0; bank <= 7; bank++){
    //     for (uint8_t reg = 0x00; reg <= 0xB3; reg++) {
    //         writeRegister8(device_addr, bank, reg, 0x00);
    //     }
    // }
    // for (uint8_t reg = 0; reg <= 0x0C; reg++) {
    //     writeRegister8(device_addr, ISSI_BANK_FUNCTIONREG, reg, 0x00);
    // }
    // writeRegister8(device_addr, ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_PICTUREMODE);
    // writeRegister8(device_addr, ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x01);
    // picture mode
    // writeRegister8(ISSI_BANK_FUNCTIONREG, 0x01, 0x01);

    //Enable blink
    // writeRegister8(ISSI_BANK_FUNCTIONREG, 0x05, 0x48B);

    //Enable Breath

}

#endif

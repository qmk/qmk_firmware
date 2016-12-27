#ifdef ISSI_ENABLE
#ifndef ISSI_H
#define ISSI_H

typedef struct ISSIDeviceStruct{
    uint8_t fn_dirty;       // function registers need to be resent
    uint8_t fn_device_addr;
    uint8_t fn_register_addr;
    uint8_t fn_registers[13];
    uint8_t led_dirty;      // LED data has changed and needs to be resent
    uint8_t led_device_addr;
    uint8_t led_register_addr;
    uint8_t led_ctrl[18];
    uint8_t led_blink_ctrl[18];
    uint8_t led_pwm[144];
}ISSIDeviceStruct;

extern ISSIDeviceStruct *issi_devices[];

// Low level commands- 'device' is the 2-bit i2c id.
void issi_init(void);
void set_shutdown(uint8_t device, uint8_t shutdown);
void writeRegister8(uint8_t device, uint8_t frame, uint8_t reg, uint8_t data);

// Higher level, no device is given, but it is calculated from 'matrix'
// Each device has 2 blocks, max of 4 devices:
//  Device  |   Block   =   Matrix
//    0           A           0
//    0           B           1
//    1           A           2
//    1           B           3
//    2           A           4
//    2           B           5
//    3           A           6
//    3           B           7
void activateLED(uint8_t matrix, uint8_t cx, uint8_t cy, uint8_t pwm);
void update_issi(uint8_t device_addr, uint8_t blocking);

#endif
#endif
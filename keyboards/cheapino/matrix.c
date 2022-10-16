#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "i2c_master.h"
#include <print.h>


bool i2c_initialized = 0;
i2c_status_t i2c_status;
#define LED_COUNT 4
const uint8_t leds[LED_COUNT] = {GP7,GP8,GP15,GP14};
bool led_status[LED_COUNT] = {true,true,true,true};
uint8_t _buf;

 /* matrix state(1:on, 0:off) */
 //static matrix_row_t matrix[MATRIX_ROWS];  // debounced values

// The PCF857 addresses are explained on page 9 here:
// https://www.ti.com/lit/ds/symlink/pcf8574.pdf
// On the Cheapino, A0-A2 are grounded for a 0 value
// In arduino, PCF857 address is 0x20, but thats without
// the read/write bit at the end, so including that(unset)
// the address is here 0x20 << 1 = 0b01000000
//uint16_t i2c_timeout = 1250;
#define I2C_ADDR       0b01000000
#define I2C_ADDR_WRITE 0b01000000
#define I2C_ADDR_READ  0b01000001
//#define I2C_TIMEOUT 1000

void toggle_leds(void) {
    for (int i = 0; i < LED_COUNT; i++)
    {
        writePin(leds[i], led_status[i] ? 1 : 0);
    }
}
void matrix_init_custom(void) {
     //setPinOutput(GP6);
     //writePinHigh(GP6);
     printf("Init Cheapino!\n");

     if (i2c_initialized == 0) {
         i2c_init();
         i2c_initialized = true;
         wait_ms(I2C_TIMEOUT);
     }
    for (int i=0; i<LED_COUNT; i++)
    {
        setPinOutput(leds[i]);
    }
    toggle_leds();
         wait_ms(500);
    for (int i=0; i<LED_COUNT; i++)
    {
        led_status[i] = false;
        toggle_leds();
        wait_ms(400);
    }
     matrix_init_user();
}


bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    printf("Scan Cheapino!");

    //i2c_status = i2c_start(I2C_ADDR_WRITE);
    //led_status[0] = i2c_status == I2C_STATUS_SUCCESS;
    // Set col0 pin high
    _buf = 0b11111110;
    uint8_t buf[]   = {0b11111110};
    i2c_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), 200);
    //led_status[0] = i2c_status == I2C_STATUS_SUCCESS;
    //i2c_stop();
    toggle_leds();
    // Read if row 0 or row 1 are high
    //i2c_status = i2c_start(I2C_ADDR_READ, I2C_TIMEOUT);
    i2c_status = i2c_receive(I2C_ADDR_READ, &_buf, 1, I2C_TIMEOUT);
    //toggle_leds();
    //led_status[1] = i2c_status == I2C_STATUS_SUCCESS;
    led_status[0] = ! (_buf & 0b00000010);
    led_status[1] = ! (_buf & 0b00001000);

    // Set col1 pin high
    _buf = 0b11111011;
    i2c_status = i2c_transmit(I2C_ADDR_WRITE, &_buf, 1, I2C_TIMEOUT);
    //led_status[2] = i2c_status == I2C_STATUS_SUCCESS;
    //toggle_leds();
    // Read if row 0 or row 1 are high
    i2c_status = i2c_receive(I2C_ADDR_READ, &_buf, 1, I2C_TIMEOUT);
    //led_status[3] = i2c_status == I2C_STATUS_SUCCESS;
    //i2c_stop();
    led_status[2] = ! (_buf & 0b00000010);
    led_status[3] = ! (_buf & 0b00001000);

    // update leds
    toggle_leds();

    return changed;
 }




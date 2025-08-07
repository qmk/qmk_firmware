#include "ergodox_stm32.h"
#include "i2c_master.h"

extern inline void ergodox_board_led_1_on(void);
extern inline void ergodox_board_led_2_on(void);
extern inline void ergodox_board_led_3_on(void);
extern inline void ergodox_board_led_1_off(void);
extern inline void ergodox_board_led_2_off(void);
extern inline void ergodox_board_led_3_off(void);
extern inline void ergodox_led_all_off(void);

volatile int mcp23017_status = 0x20;
uint8_t i2c_initializied = 0;

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
}

void bootloader_jump(void) {
    // This board doesn't use the "standard" stm32duino bootloader, and is resident in memory at the base location. All we can do here is reset.
    NVIC_SystemReset();
}

void matrix_init_kb(void)
{
    // Init LED Ports
    palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL); // LED 1
    palSetPadMode(GPIOA, 9, PAL_MODE_OUTPUT_PUSHPULL); // LED 2
    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL); // LED 3

    ergodox_blink_all_leds();

    matrix_init_user();
}

void ergodox_blink_all_leds(void)
{
    ergodox_led_all_off();
    // ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_board_led_1_on();
    wait_ms(50);
    ergodox_board_led_2_on();
    wait_ms(50);
    ergodox_board_led_3_on();
    wait_ms(50);
    ergodox_board_led_1_off();
    wait_ms(50);
    ergodox_board_led_2_off();
    wait_ms(50);
    ergodox_board_led_3_off();
}

uint8_t init_mcp23017(void) {
    if (!i2c_initializied) {
        i2c_init();
        i2c_initializied = 1;
    }

    uint8_t data[2];
    data[0] = 0x0;
    data[1] = 0b00111111;
    mcp23017_status = i2c_write_register(I2C_ADDR, I2C_IODIRA, data, 2, 50000);
    if (mcp23017_status) goto out;
    data[0] = 0xFFU;
    mcp23017_status = i2c_write_register(I2C_ADDR, I2C_GPIOA, data, 1, 5000);
    if (mcp23017_status) goto out;
    mcp23017_status = i2c_write_register(I2C_ADDR, I2C_GPPUB, data+1, 1, 2);
    if (mcp23017_status) goto out;

 out:
    return mcp23017_status;
    // i2c_read_register(I2C_ADDR, );
}


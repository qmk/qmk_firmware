#ifdef UART_RGB_ENABLE
#include "uart_rgb.h"
#include "print.h"

static uint8_t mode_id  = 1;
const uint8_t MODE_MAX = 15;

static uint8_t color_id  = 1;
const uint8_t COLOR_MAX = 9;

static uint8_t reduce_id  = 1;
static uint8_t toggle_flag = 0;
const uint8_t REDUCE_MAX = 10;

void uart_rgb_init(void) {

    // 16M 9600
    DDRD  |= _BV(PD3);
    UBRR1H = 0;
    UBRR1L = 103;

    UCSR1A &= ~_BV(U2X1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
    UCSR1B |= _BV(TXEN1);
}

bool uart_rgb_send_is_ready(void) {
    return ((UCSR1A & (1 << UDRE1)) ? true : false);
}

void uart_rgb_send_byte(uint8_t byte_data) {
    while (!(uart_rgb_send_is_ready()));

    UDR1 = byte_data;
}

void uart_rgb_on(void){
    uart_rgb_send_byte(0x16);
}


void uart_rgb_off(void) {
    uart_rgb_send_byte(0x26);
}


void uart_rgb_toggle(void) {
    toggle_flag ^= 0b1;
    uint8_t cmd = (toggle_flag + 1 << 4) + 6;
    uart_rgb_send_byte(cmd);
}


void uart_rgb_level_increase(void){
    if ( mode_id < MODE_MAX){
        mode_id ++;
    }
    uint8_t cmd = (mode_id << 4) + 3;
    uart_rgb_send_byte(cmd);
}

void uart_rgb_level_decrease(void){
    if ( mode_id > 1){
        mode_id --;
    }
    uint8_t cmd = (mode_id << 4) + 3;
    uart_rgb_send_byte(cmd);
}

void uart_rgb_colorset_increase(void){
    if ( color_id < COLOR_MAX){
        color_id ++;
    }
    uint8_t cmd = (color_id << 4) + 2;
    uart_rgb_send_byte(cmd);
}

void uart_rgb_colorset_decrease(void){
    if ( color_id > 1){
        color_id --;
    }
    uint8_t cmd = (color_id << 4) + 2;
    uart_rgb_send_byte(cmd);
}
#endif

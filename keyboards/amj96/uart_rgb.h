#ifdef UART_RGB_ENABLE
#include <LUFA/Drivers/Peripheral/Serial.h>

#define UART_RGB_ON 0x0000
#define UART_RGB_OFF 0x0001
#define UART_RGB_TOGGLE 0x002
#define UART_RGB_LEVEL_INCREASE 0x0003
#define UART_RGB_LEVEL_DECREASE 0x0004
#define UART_RGB_COLORSET_INCREASE 0x0005
#define UART_RGB_COLORSET_DECREASE 0x0006


void uart_rgb_init(void);
bool uart_rgb_send_is_ready(void);
void uart_rgb_send_byte(uint8_t byte_data);

void uart_rgb_on(void);
void uart_rgb_off(void);
void uart_rgb_toggle(void);
void uart_rgb_level_increase(void);
void uart_rgb_level_decrease(void);
void uart_rgb_colorset_increase(void);
void uart_rgb_colorset_decrease(void);

#endif
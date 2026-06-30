#include "quantum.h"
#include "uart3.h"
#include "wireless.h"
#define LCD_init() uart3_init(115200)

extern void LCD_IND_update(uint8_t devs_host);
extern void LCD_Page_update(uint8_t page_num);
extern void LCD_vol_update(bool vol_inc);
extern void LCD_charge_update(uint8_t pvol);
extern void LCD_command_update(uint8_t LCD_command);

enum LCD_command {
    LCD_RESET = 0,
    LCD_SLEEP,
    LCD_WEAKUP,
};

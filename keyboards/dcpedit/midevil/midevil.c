#include "qp_comms.h"
#include "image/background.qgf.h"
#include "image/animated.qgf.h"

painter_device_t lcd;
painter_image_handle_t background;
painter_image_handle_t animated;

void keyboard_post_init_kb(void) {
    background = qp_load_image_mem(gfx_background);
    animated = qp_load_image_mem(gfx_animated);
    // Turn on the LCD
    setPinOutput(LCD_LED_PIN);
    writePinHigh(LCD_LED_PIN);

    // Let the LCD get some power...
    wait_ms(150);
    // Initialise the LCD
    lcd = qp_ili9488_make_spi_device(320, 480, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);
    qp_init(lcd, QP_ROTATION_180);

    // Turn on the LCD and clear the display
    qp_power(lcd, true);

    /*
    // Invert image
    qp_comms_start(lcd);
    qp_comms_command(lcd, ILI9XXX_CMD_INVERT_OFF);
    qp_comms_command(lcd, 0x21);
    qp_comms_stop(lcd);
    */

    // Draw image
    qp_drawimage(lcd, 0, 0, background);
    qp_animate(lcd, 116, 194, animated);

    // Turn on the LCD backlight
    setPinOutput(LCD_LED_PIN);
    writePinHigh(LCD_LED_PIN);

    // Allow for user post-init
    keyboard_post_init_user();
}
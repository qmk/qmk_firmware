#ifdef OLED_ENABLE

void render_logo(void);

#    define RENDER_LOGO(a) render_logo(a)

#    ifdef RGBLIGHT_ENABLE
void update_led_status(void);
void render_led_status(void);
#        define UPDATE_LED_STATUS() update_led_status()
#        define RENDER_LED_STATUS(a) render_led_status(a)
#    else
#        define UPDATE_LED_STATUS()
#        define RENDER_LED_STATUS(a)
#    endif

#else
#    define RENDER_LOGO(a)
#    define UPDATE_LED_STATUS()
#    define RENDER_LED_STATUS(a)

#endif

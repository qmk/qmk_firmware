#ifdef SSD1306OLED

void render_logo(struct CharacterMatrix *matrix);
void update_key_status(uint16_t keycode, keyrecord_t *record);
void render_key_status(struct CharacterMatrix *matrix);
void update_lock_status(void);
void render_lock_status(struct CharacterMatrix *matrix);

#define RENDER_LOGO(a) render_logo(a)
#define UPDATE_KEY_STATUS(a, b) update_key_status(a, b)
#define RENDER_KEY_STATUS(a) render_key_status(a)
#define UPDATE_LOCK_STATUS() update_lock_status()
#define RENDER_LOCK_STATUS(a) render_lock_status(a)

#ifdef RGBLIGHT_ENABLE
  void update_led_status(void);
  void render_led_status(struct CharacterMatrix *matrix);
  #define UPDATE_LED_STATUS() update_led_status()
  #define RENDER_LED_STATUS(a) render_led_status(a)
#else
  #define UPDATE_LED_STATUS()
  #define RENDER_LED_STATUS(a)
#endif

#else

#define RENDER_LOGO(a)
#define UPDATE_KEY_STATUS(a, b)
#define RENDER_KEY_STATUS(a)
#define UPDATE_LOCK_STATUS()
#define RENDER_LOCK_STATUS(a)
#define UPDATE_LED_STATUS()
#define RENDER_LED_STATUS(a)

#endif

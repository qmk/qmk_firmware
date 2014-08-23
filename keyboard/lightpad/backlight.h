
enum backlight_level {
    BACKLIGHT_FN1    = 0b0000001,
    BACKLIGHT_FN2    = 0b0000010,
    BACKLIGHT_FN3    = 0b0000100,
    BACKLIGHT_FN4    = 0b0001000,
    BACKLIGHT_NUMPAD = 0b0010000,
    BACKLIGHT_REAR   = 0b0100000,
};

void backlight_init_ports(void);

void backlight_invert_fn1(void);
void backlight_enable_fn1(void);
void backlight_disable_fn1(void);

void backlight_invert_fn2(void);
void backlight_enable_fn2(void);
void backlight_disable_fn2(void);

void backlight_invert_fn3(void);
void backlight_enable_fn3(void);
void backlight_disable_fn3(void);

void backlight_invert_fn4(void);
void backlight_enable_fn4(void);
void backlight_disable_fn4(void);

void backlight_invert_numlock(void);
void backlight_enable_numlock(void);
void backlight_disable_numlock(void);

void backlight_enable_numpad(void);
void backlight_disable_numpad(void);
void backlight_invert_numpad(void);

void backlight_enable_rear(void);
void backlight_disable_rear(void);
void backlight_invert_rear(void);

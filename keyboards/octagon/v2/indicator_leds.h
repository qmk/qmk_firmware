enum Device {
  Device_PCBRGB,
  Device_STATUSLED
};

void indicator_leds_set(bool leds[8]);
void backlight_toggle_rgb(bool enabled);
void backlight_set_rgb(uint8_t cfg[17][3]);
void backlight_init_ports(void);
void send_color(uint8_t r, uint8_t g, uint8_t b, enum Device device);
void show(void);
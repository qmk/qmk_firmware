enum Device {
  Device_PCBRGB,
  Device_STATELED
};

void backlight_init_ports(void);
void backlight_set_state(bool cfg[7]);
void backlight_update_state(void);
void backlight_toggle_rgb(bool enabled);
void backlight_set_rgb(uint8_t cfg[17][3]);
void backlight_set(uint8_t level);

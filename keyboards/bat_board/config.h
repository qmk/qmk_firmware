#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7 // Define which pins are SDA and SCL on your microcontroller model. Remember to change GP to your pin indicator if you aren't using the RP2040
#define OLED_DRIVER_ENABLE

// You may need to add these if the OLED doesn't work at first.

#define OLED_I2C_ADDRESS 0x3C  // or 0x3D, depending on your OLED
#define OLED_DISPLAY_ON 1
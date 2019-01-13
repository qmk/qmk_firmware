BACKLIGHT_ENABLE = no
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = yes #Don't enable this along with I2C
SPLIT_TRANSPORT = serial #leave out the i2c code to save space

EXTRAFLAGS += -flto -DUSE_Link_Time_Optimization

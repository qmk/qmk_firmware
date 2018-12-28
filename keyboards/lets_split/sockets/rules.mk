BACKLIGHT_ENABLE = no
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = yes #Don't enable this along with I2C
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)


 ifeq ($(strip $(AUDIO_ENABLE)), yes)
   ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
     EXTRAFLAGS += -flto
   endif
 endif

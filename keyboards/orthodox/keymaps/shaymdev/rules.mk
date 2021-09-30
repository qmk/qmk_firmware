RGBLIGHT_ENABLE = yes
VELOCIKEY_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = yes
#EXTRAFLAGS += -flto #Drashna, on QMK issue 3224, paraphrased, This enables Link Time Optimization, saving a significant amount of space. Because the Macro and Function features are incompatible with Link Time Optimization, disable those features in config.h:
LTO_ENABLE = yes #same as above but includes the others in config for you
CONSOLE_ENABLE = no
MOUSEKEY_ENABLE = no
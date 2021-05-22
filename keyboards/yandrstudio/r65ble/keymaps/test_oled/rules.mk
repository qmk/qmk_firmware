# OLED_DRIVER_ENABLE = yes
VIA_ENABLE = yes
WPM_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = no
CONSOLE_ENABLE = yes
TAP_DANCE_ENABLE = yes

SRC += graph_lib/wpm_graph.c graph_lib/kb_press_graph.c dev_oled/oled_driver.c
QUANTUM_LIB_SRC += i2c_master.c
OPT_DEFS += -DOLED_DRIVER_ENABLE
COMMON_VPATH += keyboards/yandrstudio/rainbow65/keymaps/test_oled/dev_oled

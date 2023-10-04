MOUSEKEY_ENABLE = no
LTO_ENABLE = yes
CONSOLE_ENABLE = no

OLED_ENABLE = yes
OLED_DRIVER = SSD1306

SRC += ziyoulang_k3_mod_oled.c

  $(info QMK Build Options)
  $(info -- RGBLIGHT_ENABLE    = $(RGBLIGHT_ENABLE))
  $(info -  OLED_ENABLE        = $(OLED_ENABLE))
  $(info -- OLED_DRIVER        = $(OLED_DRIVER))
  $(info -- OLED_LOCAL_ENABLE  = $(OLED_LOCAL_ENABLE))
  $(info -- CONSOLE_ENABLE     = $(CONSOLE_ENABLE))
  $(info -- OPT_DEFS           = $(OPT_DEFS))
  $(info -- LTO_ENABLE         = $(LTO_ENABLE))
  $(info )

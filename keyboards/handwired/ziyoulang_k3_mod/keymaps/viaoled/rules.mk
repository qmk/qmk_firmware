VIA_ENABLE = yes

MOUSEKEY_ENABLE = no
OLED_ENABLE = yes
CONSOLE_ENABLE = no
LTO_ENABLE = yes

SRC += ziyoulang_k3_mod_oled.c

  $(info QMK Build Options)
  $(info -- MOUSEKEY_ENABLE    = $(MOUSEKEY_ENABLE))
  $(info -  OLED_ENABLE        = $(OLED_ENABLE))
  $(info -- OLED_DRIVER        = $(OLED_DRIVER))
  $(info -- CONSOLE_ENABLE     = $(CONSOLE_ENABLE))
  $(info -- LTO_ENABLE         = $(LTO_ENABLE))
  $(info )

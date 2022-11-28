SRC += mreel.c \
       custom_keycodes.c \
	   mac_win_parity.c \
       unicode.c

UCIS_ENABLE 	   = yes
CAPS_WORD_ENABLE   = yes

# Space savings
LTO_ENABLE         = yes
CONSOLE_ENABLE     = no
COMMAND_ENABLE     = no
MOUSEKEY_ENABLE    = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE   = no
MAGIC_ENABLE       = no
RGB_MATRIX_ENABLE  = no

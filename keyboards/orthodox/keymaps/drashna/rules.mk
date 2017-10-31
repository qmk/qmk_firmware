CONSOLE_ENABLE    = no
<<<<<<< HEAD
<<<<<<< HEAD
TAP_DANCE_ENABLE  = no
RGBLIGHT_ENABLE   = yes
AUDIO_ENABLE      = no
MOUSEKEY_ENABLE   = no
NKRO_ENABLE       = yes
FAUXCLICKY_ENABLE = no
EXTRAFLAGS        = -flto
=======
TAP_DANCE_ENABLE  = yes
RGBLIGHT_ENABLE   = no
MOUSEKEY_ENABLE   = no

>>>>>>> Updated macros and added workman keymaps
=======
TAP_DANCE_ENABLE  = no
RGBLIGHT_ENABLE   = yes
AUDIO_ENABLE      = no
MOUSEKEY_ENABLE   = no
NKRO_ENABLE       = yes
FAUXCLICKY_ENABLE = no
>>>>>>> Fix makefile toggle code in ez keymap

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

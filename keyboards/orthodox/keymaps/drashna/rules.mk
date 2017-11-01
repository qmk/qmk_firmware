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
<<<<<<< HEAD
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
=======
>>>>>>> Updated RGB Underglow layer indication code due to discovery of the layer_state_set_kb function

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

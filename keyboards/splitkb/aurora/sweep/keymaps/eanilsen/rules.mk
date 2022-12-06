LTO_ENABLE 		= yes	# Link time optimisation
MOUSEKEY_ENABLE		= yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE 	= yes	# Audio control and System control(+450)
NKRO_ENABLE 		= yes	# Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
CAPS_WORD_ENABLE 	= yes
SEND_STRING_ENABLE 	= yes
RGB_MATRIX_ENABLE	= no	# Disable the per-key LEDs

SRC += features/swapper.c
SRC += features/custom_shift_keys.c

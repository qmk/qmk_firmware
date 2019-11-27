# NKRO_ENABLE = yes           	# USB Nkey Rollover
# AUTO_SHIFT_ENABLE = yes      	# Auto Shift
# # RGBLIGHT_ENABLE is not for MD boards. This is here in case you forget.
# RGBLIGHT_ENABLE = no
# COMMAND_ENABLE = yes
# BOOTMAGIC_ENABLE = full
# BOOTMAGIC_ENABLE = lite
DYNAMIC_MACRO_ENABLE = yes		# Dynamic macro recording and play
MOUSEKEY_ENABLE = yes			# Enable mouse control keycodes. Increases firmware size.
TAP_DANCE_ENABLE = yes			# Enable tap dance keys
CONSOLE_ENABLE = yes			# Enable debugging console. Increases firmware size.
SRC += config_led.c

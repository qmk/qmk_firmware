# RGBLIGHT_ENABLE = no				# Not for MD boards. This is here in case you forget.
COMMAND_ENABLE = no				# Commands for debug and configuration
# AUTO_SHIFT_ENABLE = yes      	# Auto Shift
NKRO_ENABLE = yes           	# USB Nkey Rollover
DYNAMIC_MACRO_ENABLE = no		# Dynamic macro recording and play
MOUSEKEY_ENABLE = no			# Enable mouse control keycodes. Increases firmware size.
TAP_DANCE_ENABLE = yes			# Enable tap dance keys
CONSOLE_ENABLE = no				# Enable debugging console. Increases firmware size.
SRC += config_led.c				# Used to add files to the compilation/linking list.
EXTRAKEY_ENABLE = yes			# Audio control and System control
# RAW_ENABLE = yes				# Raw HID has not yet been implemented for this keyboard
# COMBO_ENABLE					# Key combo feature
# LEADER_ENABLE					# Enable leader key chording

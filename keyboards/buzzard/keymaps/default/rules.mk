SRC += features/caps_word.c

OLED_ENABLE = yes			# uncomment if you are using an OLED display
PS2_MOUSE_ENABLE = yes		# uncomment only on the master side if you are usin a TrackPoint
HAPTIC_ENABLE += DRV2605L   # uncomment only on the master side if you are using a Pimoroni haptic buzz

MOUSEKEY_ENABLE = yes
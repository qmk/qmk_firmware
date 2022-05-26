# Compiler source files
SRC += src/layouts.c

USER_NAME := davidkristoffersen

# Firmware size optimizations
CONSOLE_ENABLE	= no	# 1646: Console for debug
AUDIO_ENABLE	= no	# 8682: Audio output on port C6
# LTO_ENABLE	= yes	# 2772: Link time optimization, breaks `action_get_macro` and `fn_action` if enabled

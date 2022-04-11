# Compiler source files
SRC += src/base.c src/base/functions.c src/macros/static.c src/macros/dynamic.c

# Firmware size optimizations
CONSOLE_ENABLE	= no	# 1646: Console for debug
AUDIO_ENABLE	= no	# 8682: Audio output on port C6
# LTO_ENABLE	= yes	# 2772: Link time optimization, breaks `action_get_macro` and `fn_action` if enabled

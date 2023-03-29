SRC += $(USER_PATH)/util/functions.c \
		$(USER_PATH)/hardware/split_space.c \
		$(USER_PATH)/macros/macros.c \
		$(USER_PATH)/macros/debug.c \
		$(USER_PATH)/macros/language.c

# Firmware size optimizations
ifeq ($(strip $(SIZE_OPTIMIZE)), yes)
	CONSOLE_ENABLE	:= no	# 1646: Console for debug
	AUDIO_ENABLE	:= no	# 8682: Audio output on port C6
	LTO_ENABLE		:= yes	# 2772: Link time optimization
endif

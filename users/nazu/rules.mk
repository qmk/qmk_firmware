SRC += $(USER_PATH)/keyrecords/process_records.c \

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
# ifdef TAP_DANCE_ENABLE
	SRC += $(USER_PATH)/keyrecords/tap_dances.c
endif

# ifeq ($(strip $(OLED_ENABLE)), yes)
# ifdef OLED_ENABLE
	# SRC += $(USER_PATH)/oled/oled_rocket.c \
	# 		# $(USER_PATH)/oled/oled_status.c \
	# 		$(USER_PATH)/oled/oled_luna.c
# endif

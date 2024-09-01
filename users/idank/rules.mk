VALID_POINTING_DEVICE_CONFIGURATIONS := trackball cirque40 cirque35 cirque35_cirque35 cirque40_cirque40 trackball_trackball trackball_cirque35 cirque35_trackball trackball_cirque40 cirque40_trackball trackpoint trackpoint_trackball trackball_trackpoint trackpoint_cirque35 cirque35_trackpoint trackpoint_cirque40 cirque40_trackpoint
ifdef POINTING_DEVICE
    ifeq ($(filter $(POINTING_DEVICE),$(VALID_POINTING_DEVICE_CONFIGURATIONS)),)
        $(call CATASTROPHIC_ERROR,Invalid POINTING_DEVICE,POINTING_DEVICE="$(POINTING_DEVICE)" is not a valid pointing device configuration)
	endif
endif

SERIAL_DRIVER = vendor
# SRC += $(USER_PATH)/idank.c

MSG_POINTING_DEVICE = none
MSG_OLED = no
MSG_MASTER_SIDE = right

ifeq ($(strip $(POINTING_DEVICE_POSITION)), right)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_RIGHT
	MSG_MASTER_SIDE = right
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), left)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_LEFT
	MSG_MASTER_SIDE = left
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), thumb)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_THUMB
	MSG_MASTER_SIDE = right
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), thumb_inner)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_THUMB_INNER
	MSG_MASTER_SIDE = right
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), thumb_outer)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_THUMB_OUTER
	MSG_MASTER_SIDE = right
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), middle)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_MIDDLE
	MSG_MASTER_SIDE = n/a (not a split keyboard)
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball)
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_PIMORONI
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = pimoroni_trackball

	ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
		SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
	endif

	MSG_POINTING_DEVICE = trackball
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque35)
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE35
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

	MSG_POINTING_DEVICE = cirque35 touchpad
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque40)
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE40
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

	MSG_POINTING_DEVICE = cirque40 touchpad
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque35_cirque35)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE35_CIRQUE35

	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

	MSG_POINTING_DEVICE = cirque35 touchpad (left), cirque35 touchpad (right)
	MSG_MASTER_SIDE = right
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque40_cirque40)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE40_CIRQUE40

	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

	MSG_POINTING_DEVICE = cirque40 touchpad (left), cirque40 touchpad (right)
	MSG_MASTER_SIDE = right
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball_trackball)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_PIMORONI_PIMORONI

	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = pimoroni_trackball

	ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
		SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
	endif

	MSG_POINTING_DEVICE = trackball (left), trackball (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = right
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball_cirque35)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_PIMORONI_CIRQUE35
	POINTING_DEVICE_ENABLE = yes

	ifeq ($(strip $(SIDE)), left)
		POINTING_DEVICE_DRIVER = pimoroni_trackball

		ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
			SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
		endif
	endif
	ifeq ($(strip $(SIDE)), right)
		POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	endif

	MSG_POINTING_DEVICE = trackball (left), cirque35 touchpad (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = right
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque35_trackball)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE35_PIMORONI
	POINTING_DEVICE_ENABLE = yes

	ifeq ($(strip $(SIDE)), right)
		POINTING_DEVICE_DRIVER = pimoroni_trackball

		ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
			SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
		endif
	endif
	ifeq ($(strip $(SIDE)), left)
		POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	endif

	MSG_POINTING_DEVICE = cirque35 touchpad (left), trackball (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = left
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball_cirque40)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_PIMORONI_CIRQUE40
	POINTING_DEVICE_ENABLE = yes

	ifeq ($(strip $(SIDE)), left)
		POINTING_DEVICE_DRIVER = pimoroni_trackball

		ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
			SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
		endif
	endif
	ifeq ($(strip $(SIDE)), right)
		POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	endif

	MSG_POINTING_DEVICE = trackball (left), cirque40 touchpad (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = right
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque40_trackball)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE40_PIMORONI
	POINTING_DEVICE_ENABLE = yes

	ifeq ($(strip $(SIDE)), right)
		POINTING_DEVICE_DRIVER = pimoroni_trackball

		ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
			SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
		endif
	endif
	ifeq ($(strip $(SIDE)), left)
		POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	endif

	MSG_POINTING_DEVICE = cirque40 touchpad (left), trackball (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = left
endif

ifeq ($(strip $(POINTING_DEVICE)), trackpoint)
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_TRACKPOINT
	PS2_ENABLE = yes
	PS2_DRIVER = vendor
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = ps2
	MSG_POINTING_DEVICE = trackpoint
endif

ifeq ($(strip $(POINTING_DEVICE)), trackpoint_trackball)
    OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_TRACKPOINT_TRACKBALL

    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DSPLIT_POINTING_ENABLE
    OPT_DEFS += -DPOINTING_DEVICE_COMBINED

    ifeq ($(strip $(SIDE)), left)
        PS2_ENABLE = yes
        PS2_DRIVER = vendor
        POINTING_DEVICE_DRIVER = ps2
    endif
    ifeq ($(strip $(SIDE)), right)
        POINTING_DEVICE_DRIVER = pimoroni_trackball

        ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
            SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
        endif
    endif

	MSG_POINTING_DEVICE = trackpoint (left), trackball (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = left
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball_trackpoint)
    OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_TRACKBALL_TRACKPOINT

    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DSPLIT_POINTING_ENABLE
    OPT_DEFS += -DPOINTING_DEVICE_COMBINED

    ifeq ($(strip $(SIDE)), right)
        PS2_ENABLE = yes
        PS2_DRIVER = vendor
        POINTING_DEVICE_DRIVER = ps2
    endif
    ifeq ($(strip $(SIDE)), left)
        POINTING_DEVICE_DRIVER = pimoroni_trackball

        ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
            SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
        endif
    endif

	MSG_POINTING_DEVICE = trackball (left), trackpoint (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = right
endif

ifeq ($(strip $(POINTING_DEVICE)), trackpoint_cirque35)
    OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_TRACKPOINT_CIRQUE35

    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DSPLIT_POINTING_ENABLE
    OPT_DEFS += -DPOINTING_DEVICE_COMBINED

    ifeq ($(strip $(SIDE)), left)
        PS2_ENABLE = yes
        PS2_DRIVER = vendor
        POINTING_DEVICE_DRIVER = ps2
    endif
    ifeq ($(strip $(SIDE)), right)
        POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
    endif

	MSG_POINTING_DEVICE = trackpoint (left), cirque35 touchpad (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = left
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque35_trackpoint)
    OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE35_TRACKPOINT

    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DSPLIT_POINTING_ENABLE
    OPT_DEFS += -DPOINTING_DEVICE_COMBINED

    ifeq ($(strip $(SIDE)), right)
        PS2_ENABLE = yes
        PS2_DRIVER = vendor
        POINTING_DEVICE_DRIVER = ps2
    endif
    ifeq ($(strip $(SIDE)), left)
        POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
    endif

	MSG_POINTING_DEVICE = cirque35 touchpad (left), trackpoint (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = right
endif

ifeq ($(strip $(POINTING_DEVICE)), trackpoint_cirque40)
    OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_TRACKPOINT_CIRQUE40

    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DSPLIT_POINTING_ENABLE
    OPT_DEFS += -DPOINTING_DEVICE_COMBINED

    ifeq ($(strip $(SIDE)), left)
        PS2_ENABLE = yes
        PS2_DRIVER = vendor
        POINTING_DEVICE_DRIVER = ps2
    endif
    ifeq ($(strip $(SIDE)), right)
        POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
    endif

	MSG_POINTING_DEVICE = trackpoint (left), cirque40 touchpad (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = left
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque40_trackpoint)
    OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE40_TRACKPOINT

    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DSPLIT_POINTING_ENABLE
    OPT_DEFS += -DPOINTING_DEVICE_COMBINED

    ifeq ($(strip $(SIDE)), right)
        PS2_ENABLE = yes
        PS2_DRIVER = vendor
        POINTING_DEVICE_DRIVER = ps2
    endif
    ifeq ($(strip $(SIDE)), left)
        POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
    endif

	MSG_POINTING_DEVICE = cirque40 touchpad (left), trackpoint (right); built for side = $(SIDE)
	MSG_MASTER_SIDE = right
endif

MOUSEKEY_ENABLE = yes

ifeq ($(strip $(OLED)), yes)
	OPT_DEFS += -DOLED_ENABLE
	OLED_ENABLE     = yes
	OLED_DRIVER     = ssd1306
	MSG_OLED = yes
else
	OLED_ENABLE     = no
	MSG_OLED = no
endif

ifeq ($(strip $(OLED_FLIP)), yes)
	OPT_DEFS += -DOLED_FLIP
	MSG_OLED_FLIPPED = (flipped)
endif

print-summary: cpfirmware
	printf "\n%s" ' _           _       _             _         ' >&2
	printf "\n%s" '| |__   ___ | |_   _| | _____  ___| |__  ___ ' >&2
	printf "\n%s" "| '_ \ / _ \| | | | | |/ / _ \/ _ \ '_ \/ __|" >&2
	printf "\n%s" '| | | | (_) | | |_| |   <  __/  __/ |_) \__ \' >&2
	printf "\n%s" '|_| |_|\___/|_|\__, |_|\_\___|\___|_.__/|___/' >&2
	printf "\n%s" '               |___/                         ' >&2
	printf "\n\nPointing Device: $(BOLD)$(MSG_POINTING_DEVICE)$(NO_COLOR)\n" >&2
	printf "OLED: $(BOLD)$(MSG_OLED) $(MSG_OLED_FLIPPED)$(NO_COLOR)\n" >&2
	printf "Keyboard main side: $(BOLD)$(MSG_MASTER_SIDE)$(NO_COLOR)\n" >&2
	printf "\n$(WARN_COLOR)WARNING!$(NO_COLOR) Avoid connecting / disconnecting the TRRS cable when the keyboard is powered. This can short the GPIO pins of the controllers.\n\n" >&2

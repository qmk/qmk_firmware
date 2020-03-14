
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = no        # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
TAP_DANCE_ENABLE = no 

# If your custom treadstone48 pcb, you can rewrite to yes.
OLED_ENABLE = no            # OLED_ENABLE
LED_UNDERGLOW_ENABLE = no  # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = no        # LED animations

# Other selectable option
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
LOCAL_GLCDFONT = no         # use each keymaps "font.h" insted of "common/glcdfont.c"
# RHYMESTONE_RIGHTHAND = no   # If connect right hand side of the Rhymestone, set to yes.
ANGELINA_KEYMAP = no        # If Alfa verstion use set to yes.

ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
else
  RGBLIGHT_ENABLE = no
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    # OPT_DEFS += -DRGBLIGHT_ANIMATIONS
    OPT_DEFS += -DLED_ANIMATIONS
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

# ifeq ($(strip $(RHYMESTONE_RIGHTHAND)), yes)
#     OPT_DEFS += -DRHYMESTONE_RIGHTHAND
# endif

ifeq ($(strip $(ANGELINA_KEYMAP)), yes)
    OPT_DEFS += -DANGELINA_KEYMAP
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

# If you want to change the display of OLED, you need to change here
SRC +=  ./common/oled_helper.c \

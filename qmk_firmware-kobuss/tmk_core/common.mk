PRINTF_PATH = $(LIB_PATH)/printf

COMMON_DIR = common
PLATFORM_COMMON_DIR = $(COMMON_DIR)/$(PLATFORM_KEY)

TMK_COMMON_SRC +=	$(COMMON_DIR)/host.c \
	$(COMMON_DIR)/keyboard.c \
	$(COMMON_DIR)/action.c \
	$(COMMON_DIR)/action_tapping.c \
	$(COMMON_DIR)/action_macro.c \
	$(COMMON_DIR)/action_layer.c \
	$(COMMON_DIR)/action_util.c \
	$(COMMON_DIR)/print.c \
	$(COMMON_DIR)/debug.c \
	$(COMMON_DIR)/sendchar_null.c \
	$(COMMON_DIR)/util.c \
	$(COMMON_DIR)/eeconfig.c \
	$(COMMON_DIR)/report.c \
	$(PLATFORM_COMMON_DIR)/suspend.c \
	$(PLATFORM_COMMON_DIR)/timer.c \
	$(PLATFORM_COMMON_DIR)/bootloader.c \

ifeq ($(PLATFORM),AVR)
  TMK_COMMON_SRC += $(PLATFORM_COMMON_DIR)/xprintf.S
else ifeq ($(PLATFORM),CHIBIOS)
  TMK_COMMON_SRC += $(PRINTF_PATH)/printf.c
  TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_FLOAT
  TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL
  TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_LONG_LONG
  TMK_COMMON_DEFS += -DPRINTF_DISABLE_SUPPORT_PTRDIFF_T
  VPATH += $(PRINTF_PATH)
else ifeq ($(PLATFORM),ARM_ATSAM)
  TMK_COMMON_SRC += $(PLATFORM_COMMON_DIR)/printf.c
endif

# Option modules
BOOTMAGIC_ENABLE ?= no
VALID_MAGIC_TYPES := yes full lite
ifneq ($(strip $(BOOTMAGIC_ENABLE)), no)
  ifeq ($(filter $(BOOTMAGIC_ENABLE),$(VALID_MAGIC_TYPES)),)
    $(error BOOTMAGIC_ENABLE="$(BOOTMAGIC_ENABLE)" is not a valid type of magic)
  endif
  ifeq ($(strip $(BOOTMAGIC_ENABLE)), lite)
      TMK_COMMON_DEFS += -DBOOTMAGIC_LITE
      TMK_COMMON_SRC += $(COMMON_DIR)/bootmagic_lite.c

      TMK_COMMON_DEFS += -DMAGIC_ENABLE
      TMK_COMMON_SRC += $(COMMON_DIR)/magic.c
  else
    TMK_COMMON_DEFS += -DBOOTMAGIC_ENABLE
    TMK_COMMON_SRC += $(COMMON_DIR)/bootmagic.c
  endif
else
    TMK_COMMON_DEFS += -DMAGIC_ENABLE
    TMK_COMMON_SRC += $(COMMON_DIR)/magic.c
endif

SHARED_EP_ENABLE = no
MOUSE_SHARED_EP ?= yes
ifeq ($(strip $(KEYBOARD_SHARED_EP)), yes)
    TMK_COMMON_DEFS += -DKEYBOARD_SHARED_EP
    SHARED_EP_ENABLE = yes
    # With the current usb_descriptor.c code,
    # you can't share kbd without sharing mouse;
    # that would be a very unexpected use case anyway
    MOUSE_SHARED_EP = yes
endif

ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
    TMK_COMMON_SRC += $(COMMON_DIR)/mousekey.c
    TMK_COMMON_DEFS += -DMOUSEKEY_ENABLE
    TMK_COMMON_DEFS += -DMOUSE_ENABLE

    ifeq ($(strip $(MOUSE_SHARED_EP)), yes)
        TMK_COMMON_DEFS += -DMOUSE_SHARED_EP
        SHARED_EP_ENABLE = yes
    endif
endif

ifeq ($(strip $(EXTRAKEY_ENABLE)), yes)
    TMK_COMMON_DEFS += -DEXTRAKEY_ENABLE
    SHARED_EP_ENABLE = yes
endif

ifeq ($(strip $(RAW_ENABLE)), yes)
    TMK_COMMON_DEFS += -DRAW_ENABLE
endif

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    TMK_COMMON_DEFS += -DCONSOLE_ENABLE
else
    TMK_COMMON_DEFS += -DNO_PRINT
    TMK_COMMON_DEFS += -DNO_DEBUG
endif

ifeq ($(strip $(COMMAND_ENABLE)), yes)
    TMK_COMMON_SRC += $(COMMON_DIR)/command.c
    TMK_COMMON_DEFS += -DCOMMAND_ENABLE
endif

ifeq ($(strip $(NKRO_ENABLE)), yes)
    ifeq ($(PROTOCOL), VUSB)
        $(info NKRO is not currently supported on V-USB, and has been disabled.)
    else ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
        $(info NKRO is not currently supported with Bluetooth, and has been disabled.)
    else ifneq ($(BLUETOOTH),)
        $(info NKRO is not currently supported with Bluetooth, and has been disabled.)
    else
        TMK_COMMON_DEFS += -DNKRO_ENABLE
        SHARED_EP_ENABLE = yes
    endif
endif

ifeq ($(strip $(USB_6KRO_ENABLE)), yes)
    TMK_COMMON_DEFS += -DUSB_6KRO_ENABLE
endif

ifeq ($(strip $(SLEEP_LED_ENABLE)), yes)
    TMK_COMMON_SRC += $(PLATFORM_COMMON_DIR)/sleep_led.c
    TMK_COMMON_DEFS += -DSLEEP_LED_ENABLE
    TMK_COMMON_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifeq ($(strip $(NO_SUSPEND_POWER_DOWN)), yes)
    TMK_COMMON_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
    TMK_COMMON_DEFS += -DBLUETOOTH_ENABLE
	TMK_COMMON_DEFS += -DNO_USB_STARTUP_CHECK
endif

ifeq ($(strip $(BLUETOOTH)), AdafruitBLE)
	TMK_COMMON_DEFS += -DBLUETOOTH_ENABLE
	TMK_COMMON_DEFS += -DMODULE_ADAFRUIT_BLE
	TMK_COMMON_DEFS += -DNO_USB_STARTUP_CHECK
endif

ifeq ($(strip $(BLUETOOTH)), RN42)
	TMK_COMMON_DEFS += -DBLUETOOTH_ENABLE
	TMK_COMMON_DEFS += -DMODULE_RN42
	TMK_COMMON_DEFS += -DNO_USB_STARTUP_CHECK
endif

ifeq ($(strip $(ONEHAND_ENABLE)), yes)
  SWAP_HANDS_ENABLE = yes # backwards compatibility
endif
ifeq ($(strip $(SWAP_HANDS_ENABLE)), yes)
    TMK_COMMON_DEFS += -DSWAP_HANDS_ENABLE
endif

ifeq ($(strip $(NO_USB_STARTUP_CHECK)), yes)
    TMK_COMMON_DEFS += -DNO_USB_STARTUP_CHECK
endif

ifeq ($(strip $(SHARED_EP_ENABLE)), yes)
    TMK_COMMON_DEFS += -DSHARED_EP_ENABLE
endif

ifeq ($(strip $(LTO_ENABLE)), yes)
    ifeq ($(PLATFORM),CHIBIOS)
        $(info Enabling LTO on ChibiOS-targeting boards is known to have a high likelihood of failure.)
        $(info If unsure, set LTO_ENABLE = no.)
    endif
    EXTRAFLAGS += -flto
    TMK_COMMON_DEFS += -DLTO_ENABLE
    TMK_COMMON_DEFS += -DLINK_TIME_OPTIMIZATON_ENABLE
else ifdef LINK_TIME_OPTIMIZATION_ENABLE
    $(error The LINK_TIME_OPTIMIZATION_ENABLE flag has been renamed to LTO_ENABLE.)
endif

# Search Path
VPATH += $(TMK_PATH)/$(COMMON_DIR)
VPATH += $(TMK_PATH)/$(PLATFORM_COMMON_DIR)

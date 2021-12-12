# name of your application
APPLICATION = qmk_firmware

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../../lib/riot/

ifneq ($(KEYBOARD_BOARD_DIR),)
EXTERNAL_BOARD_DIRS = $(abspath $(CURDIR)/../../../$(KEYBOARD_BOARD_DIR))
else
EXTERNAL_BOARD_DIRS = $(abspath $(CURDIR)/../boards/)
endif

ifneq ($(KEYMAP_OUTPUT),)
BINDIRBASE=$(KEYMAP_OUTPUT)
endif

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
# DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET = 1

QUIETER = 0

# CFLAGS_OPT = -O2
# LTO = 1

# Use a peripheral timer for the delay, if available
# FEATURES_REQUIRED += periph_timer
FEATURES_REQUIRED += periph_i2c
# USEMODULE += auto_init_usbus
DISABLE_MODULE += auto_init_usbus
USEMODULE += usbus
USEMODULE += usbus_hid
USEMODULE += xtimer

# Bind USB Config
ifneq ($(KEYBOARD_OUTPUT),)
CFLAGS += -include $(KEYBOARD_OUTPUT)/src/riot_usb.h
endif

include $(RIOTBASE)/Makefile.include

# ifeq (native,$(BOARD))
#   # For the native board, CLOCK_CORECLOCK is undefined. But we need
#   # a valid number to get the example compiled
#   CFLAGS += -DCLOCK_CORECLOCK=1000000000
# endif

# ARCHIVES2:=$(shell cat $(BINDIRBASE)/obj.txt)
# ARCHIVES = $(addprefix /home/zvecr/qmk_firmware/,$(ARCHIVES2))

ifneq ($(ASDF),)
ARCHIVES+=$(addprefix $(CURDIR)/../../../,$(shell cat $(ASDF)))
endif

# ifneq ($(QWER),)
# CFLAGS+=$(patsubst %,-include $(CURDIR)/../../../%,$(QWER))
# endif

dump_includes: $(RIOTBUILD_CONFIG_HEADER_C)
	@echo $(INCLUDES)

# dump_libs: $(BASELIBS) $(ARCHIVES)
# 	@echo $(find $(BASELIBS:%.module=$(BINDIR)/%/) -name "*.o" 2> /dev/null | sort)

dump_libs:
	@echo ""

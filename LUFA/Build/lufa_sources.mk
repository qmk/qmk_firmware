#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

LUFA_BUILD_MODULES         += SOURCES
LUFA_BUILD_TARGETS         += 
LUFA_BUILD_MANDATORY_VARS  += LUFA_PATH ARCH
LUFA_BUILD_OPTIONAL_VARS   += 
LUFA_BUILD_PROVIDED_VARS   += LUFA_SRC_USB LUFA_SRC_USBCLASS LUFA_SRC_TEMPERATURE LUFA_SRC_SERIAL LUFA_SRC_TWI LUFA_SRC_PLATFORM
LUFA_BUILD_PROVIDED_MACROS += 

# -----------------------------------------------------------------------------
#               LUFA Sources Buildsystem Makefile Module.
# -----------------------------------------------------------------------------
# DESCRIPTION:
#   Provides a set of makefile variables for the various LUFA module sources.
#   Once included, the sources required to use a given LUFA module will become
#   available using the makefile variable names listed in the LUFA project
#   documentation.
# -----------------------------------------------------------------------------
# TARGETS:
#
#    (None)
#
# MANDATORY PARAMETERS:
#
#    LUFA_PATH                 - Path to the LUFA library core
#    ARCH                      - Device architecture name
#
# OPTIONAL PARAMETERS:
#
#    (None)
#
# PROVIDED VARIABLES:
#
#    LUFA_SRC_USB              - List of LUFA USB driver source files
#    LUFA_SRC_USBCLASS         - List of LUFA USB Class driver source files
#    LUFA_SRC_TEMPERATURE      - List of LUFA temperature sensor driver source
#                                files
#    LUFA_SRC_SERIAL           - List of LUFA Serial U(S)ART driver source files
#    LUFA_SRC_TWI              - List of LUFA TWI driver source files
#    LUFA_SRC_PLATFORM         - List of LUFA architecture specific platform
#                                management source files
#
# PROVIDED MACROS:
#
#    (None)
#
# -----------------------------------------------------------------------------

SHELL = /bin/sh

ERROR_IF_UNSET   ?= $(if $(filter undefined, $(origin $(strip $(1)))), $(error Makefile $(strip $(1)) value not set))
ERROR_IF_EMPTY   ?= $(if $(strip $($(strip $(1)))), , $(error Makefile $(strip $(1)) option cannot be blank))
ERROR_IF_NONBOOL ?= $(if $(filter Y N, $($(strip $(1)))), , $(error Makefile $(strip $(1)) option must be Y or N))

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(LUFA_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, LUFA_PATH)
$(call ERROR_IF_EMPTY, ARCH)

# Allow LUFA_ROOT_PATH to be overridden elsewhere to support legacy LUFA makefiles
LUFA_ROOT_PATH ?= $(patsubst %/,%,$(LUFA_PATH))

# Construct LUFA module source variables
LUFA_SRC_USB         := $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/Device_$(ARCH).c          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/Endpoint_$(ARCH).c        \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/Host_$(ARCH).c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/Pipe_$(ARCH).c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/USBController_$(ARCH).c   \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/USBInterrupt_$(ARCH).c    \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/EndpointStream_$(ARCH).c  \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/$(ARCH)/PipeStream_$(ARCH).c      \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/ConfigDescriptors.c               \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/DeviceStandardReq.c               \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/Events.c                          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/HostStandardReq.c                 \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Core/USBTask.c                         \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Common/HIDParser.c
LUFA_SRC_USBCLASS    := $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/AudioClassDevice.c        \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/CDCClassDevice.c          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/HIDClassDevice.c          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/MassStorageClassDevice.c  \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/MIDIClassDevice.c         \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Device/RNDISClassDevice.c        \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/AndroidAccessoryClassHost.c \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/AudioClassHost.c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/CDCClassHost.c              \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/HIDClassHost.c              \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/MassStorageClassHost.c      \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/MIDIClassHost.c             \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/PrinterClassHost.c          \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/RNDISClassHost.c            \
                        $(LUFA_ROOT_PATH)/Drivers/USB/Class/Host/StillImageClassHost.c
LUFA_SRC_TEMPERATURE := $(LUFA_ROOT_PATH)/Drivers/Board/Temperature.c
LUFA_SRC_SERIAL      := $(LUFA_ROOT_PATH)/Drivers/Peripheral/$(ARCH)/Serial_$(ARCH).c
LUFA_SRC_TWI         := $(LUFA_ROOT_PATH)/Drivers/Peripheral/$(ARCH)/TWI_$(ARCH).c

ifeq ($(ARCH), UC3)
   LUFA_SRC_PLATFORM := $(LUFA_ROOT_PATH)/Platform/UC3/Exception.S   \
                        $(LUFA_ROOT_PATH)/Platform/UC3/InterruptManagement.c
else
   LUFA_SRC_PLATFORM :=
endif

# Build a list of all available module sources
LUFA_SRC_ALL_FILES   := $(LUFA_SRC_USB)            \
                        $(LUFA_SRC_USBCLASS)       \
                        $(LUFA_SRC_TEMPERATURE)    \
                        $(LUFA_SRC_SERIAL)         \
                        $(LUFA_SRC_TWI)            \
					    $(LUFA_SRC_PLATFORM)

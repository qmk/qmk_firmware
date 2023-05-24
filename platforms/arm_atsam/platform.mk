# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Compiler settings
#
CC = $(CC_PREFIX) arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar
NM = arm-none-eabi-nm
HEX = $(OBJCOPY) -O $(FORMAT) -R .eeprom -R .fuse -R .lock -R .signature
EEP = $(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT)
BIN =

COMMON_VPATH += $(LIB_PATH)/arm_atsam/packs/atmel/SAMD51_DFP/1.0.70/include
COMMON_VPATH += $(LIB_PATH)/arm_atsam/packs/arm/cmsis/5.0.1/CMSIS/Include

COMPILEFLAGS += -funsigned-char
COMPILEFLAGS += -funsigned-bitfields
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fshort-enums
COMPILEFLAGS += -fno-inline-small-functions
COMPILEFLAGS += -fno-strict-aliasing
COMPILEFLAGS += -mfloat-abi=hard
COMPILEFLAGS += -mfpu=fpv4-sp-d16
COMPILEFLAGS += -mthumb

#ALLOW_WARNINGS = yes

CFLAGS += $(COMPILEFLAGS)

CXXFLAGS += $(COMPILEFLAGS)
CXXFLAGS += -fno-exceptions -std=c++11

LDFLAGS +=-Wl,--gc-sections
LDFLAGS += -Wl,-Map="%OUT%%PROJ_NAME%.map"
LDFLAGS += -Wl,--start-group
LDFLAGS += -Wl,--end-group
LDFLAGS += --specs=rdimon.specs
LDFLAGS += -T$(LIB_PATH)/arm_atsam/packs/atmel/SAMD51_DFP/1.0.70/gcc/gcc/samd51j18a_flash.ld

OPT_DEFS += -DPROTOCOL_ARM_ATSAM

MCUFLAGS = -mcpu=$(MCU)
MCUFLAGS += -D__$(ARM_ATSAM)__

# List any extra directories to look for libraries here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRALIBDIRS =

cpfirmware: warn-arm_atsam
.INTERMEDIATE: warn-arm_atsam
warn-arm_atsam: $(FIRMWARE_FORMAT)
	$(info @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)
	$(info This MCU support package has a lack of support from the upstream provider (Massdrop).)
	$(info There are currently questions about valid licensing, and at this stage it's likely)
	$(info their boards and supporting code will be removed from QMK in the near future. Please)
	$(info contact Massdrop for support, and encourage them to align their future board design)
	$(info choices to gain proper license compatibility with QMK.)
	$(info @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@)

# Convert hex to bin.
bin: $(BUILD_DIR)/$(TARGET).hex
	$(OBJCOPY) -Iihex -Obinary $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;

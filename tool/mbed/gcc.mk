############################################################################### 
GCC_BIN = 
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE 	= $(GCC_BIN)arm-none-eabi-size
CHKSUM  = $(TMK_DIR)/tool/mbed/lpc-vector-checksum

CPU = -mcpu=cortex-m0 -mthumb

CC_FLAGS += $(CPU) -c -g -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections
CC_FLAGS += -MMD -MP
CC_SYMBOLS = -DTARGET_LPC11U35_401 -DTARGET_M0 -DTARGET_NXP -DTARGET_LPC11UXX -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M0 -DARM_MATH_CM0 -DMBED_BUILD_TIMESTAMP=1399108688.49 -D__MBED__=1 

LD_FLAGS = -mcpu=cortex-m0 -mthumb -Wl,--gc-sections --specs=nano.specs
LD_FLAGS += -Wl,-Map=$(OBJDIR)/$(PROJECT).map,--cref
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0
else
  CC_FLAGS += -DNDEBUG -Os
endif

all: $(OBJDIR)/$(PROJECT).bin $(OBJDIR)/$(PROJECT).hex size

clean:
	rm -f $(OBJDIR)/$(PROJECT).bin $(OBJDIR)/$(PROJECT).elf $(OBJDIR)/$(PROJECT).hex $(OBJDIR)/$(PROJECT).map $(OBJDIR)/$(PROJECT).lst $(OBJECTS) $(DEPS)
	rm -fr $(OBJDIR)

$(OBJDIR)/%.o: %.s
	mkdir -p $(@D)
	$(AS) $(CPU) -o $@ $<

$(OBJDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -o $@ $<


$(OBJDIR)/$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)
	@echo ""
	@echo "*****"
	@echo "***** You must modify vector checksum value in *.bin and *.hex files."
	@echo "*****"
	@echo ""

$(OBJDIR)/$(PROJECT).bin: $(OBJDIR)/$(PROJECT).elf
	@$(OBJCOPY) -O binary $< $@
	@echo "Writing vector checksum value into $@ ..."
	@$(CHKSUM) $@
	@echo

$(OBJDIR)/$(PROJECT).hex: $(OBJDIR)/$(PROJECT).elf
	@$(OBJCOPY) -O ihex $< $@

$(OBJDIR)/$(PROJECT).lst: $(OBJDIR)/$(PROJECT).elf
	@$(OBJDUMP) -Sdh $< > $@

lst: $(OBJDIR)/$(PROJECT).lst

size:
	$(SIZE) $(OBJDIR)/$(PROJECT).elf

prog:	$(OBJDIR)/$(PROJECT).bin
	@echo "Program..."
ifneq ($(shell mount | grep 'CRP DISABLD'),)
	umount /dev/nxpisp >/dev/null 2>&1
endif
	dd if=$< of=/dev/nxpisp seek=4

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)

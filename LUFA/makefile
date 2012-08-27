#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# ---------------------------------------
#  Makefile for the LUFA library itself.
# ---------------------------------------

LUFA_VERSION_NUM        := $(shell grep LUFA_VERSION_STRING Version.h | cut -d'"' -f2)
EXCLUDE_FROM_EXPORT     := Documentation DoxygenPages CodeTemplates Build *.conf *.tar *.o *.d *.lss *.lst *.hex *.elf *.hex *.eep *.map *.bin

# Default target - no default action when attempting to build the core directly
all:

# Export the library core as a TAR archive for importing into an IDE
export_tar:
	@echo Exporting LUFA library to a TAR archive...
	@tar -cf LUFA_$(LUFA_VERSION_NUM).tar --directory=. $(EXCLUDE_FROM_EXPORT:%=--exclude=%) *
	@tar -cf LUFA_$(LUFA_VERSION_NUM)_Code_Templates.tar CodeTemplates
	@echo Export LUFA_$(LUFA_VERSION_NUM).tar complete.

# Display the LUFA version of this library copy
version:
	@echo "LUFA $(LUFA_VERSION_NUM)"

# Check if this is being included from a legacy or non LUFA build system makefile
ifneq ($(LUFA_PATH),)
  LUFA_ROOT_PATH = $(patsubst %/,%,$(LUFA_PATH))/LUFA/
  
  include $(patsubst %/,%,$(LUFA_PATH))/LUFA/Build/lufa_sources.mk
else
  LUFA_BUILD_MODULES     += MASTER
  LUFA_BUILD_TARGETS     += export_tar version

  LUFA_PATH               = .
  ARCH                    = {AVR8,UC3,XMEGA}
  DOXYGEN_OVERRIDE_PARAMS = QUIET=YES PROJECT_NUMBER=$(LUFA_VERSION_NUM)
  
  # Remove all object and associated files from the LUFA library core
  clean:
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.o)
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.d)
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.lst)

  include Build/lufa_core.mk
  include Build/lufa_sources.mk
  include Build/lufa_doxygen.mk
endif

.PHONY: all export_tar version clean
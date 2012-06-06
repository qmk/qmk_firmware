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
EXCLUDE_FROM_EXPORT     := Documentation DoxygenPages CodeTemplates Build *.conf *.tar *.o *.lss *.lst *.hex *.elf *.hex *.eep *.map *.bin *.d *.o.d

DOXYGEN_OVERRIDE_PARAMS = PROJECT_NUMBER=$(LUFA_VERSION_NUM)

all:

export_tar:
	@echo Exporting LUFA library to a TAR archive...
	@tar -cf LUFA_$(LUFA_VERSION_NUM).tar --directory=. $(EXCLUDE_FROM_EXPORT:%=--exclude=%) *
	@tar -cf LUFA_$(LUFA_VERSION_NUM)_Code_Templates.tar CodeTemplates
	@echo Export LUFA_$(LUFA_VERSION_NUM).tar complete.

version:
	@echo "LUFA $(LUFA_VERSION_NUM)"

# Check if this is being included from a legacy or non LUFA build system makefile
ifneq ($(LUFA_PATH),)
  LUFA_ROOT_PATH = $(LUFA_PATH)/LUFA/
  include $(LUFA_PATH)/LUFA/Build/lufa.sources.in
else
  LUFA_BUILD_MODULES += LIBCORE
  LUFA_BUILD_TARGETS += export_tar version

  LUFA_PATH           = .
  ARCH                = {AVR8,UC3,XMEGA}
  
  clean:
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.o)
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.o.d)
	rm -f $(LUFA_SRC_ALL_FILES:%.c=%.lst)

  # Include LUFA build script makefiles
  include Build/lufa.core.in
  include Build/lufa.sources.in
  include Build/lufa.doxygen.in
endif

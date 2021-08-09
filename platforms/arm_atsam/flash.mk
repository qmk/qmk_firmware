# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

flash: bin
ifneq ($(strip $(PROGRAM_CMD)),)
	$(PROGRAM_CMD)
else
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_ARCH)"
endif

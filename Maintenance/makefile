#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Maintenance scripts not required by general LUFA users, used for development.

LUFA_ROOT = ../

upgrade-doxygen:
	@echo Upgrading Doxygen.conf files...
	@for doxygen_conf in `find $(LUFA_ROOT) -name Doxygen.conf`; do \
	  doxygen -u $$doxygen_conf; \
	done;
	@echo Doxygen configuration update complete.
	
check-release:
	@echo Checking for release suitability...
	@if ( grep "XXXXXX" $(LUFA_ROOT)/LUFA/DoxygenPages/*.txt > /dev/null ;); then \
	  echo "  ERROR: Doxygen documentation has not been updated for release!"; \
	  exit 1; \
	fi;
	@if ( grep "000000" $(LUFA_ROOT)/LUFA/Version.h > /dev/null ;); then \
	  echo "  ERROR: Version header has not been updated for release!"; \
	  exit 1; \
	fi;
	@echo Done.

#
#             LUFA Library
#     Copyright (C) Dean Camera, 2011.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile for the module build test. This test
# attempts to build as many modules as possible
# under all supported architectures, and include
# all module headers in a simple C and C++
# application.


# List of device families per architecture, one device per architecture sub-family
AVR8_FAMILIES  = at90usb1287 at90usb1286 atmega16u4 atmega16u2 at90usb162
XMEGA_FAMILIES = atxmega128a1u atxmega128a3u atxmega256a3bu atxmega128a4u atxmega128b1 atxmega128b3 atxmega128c3 atxmega32c4
UC3_FAMILIES   = uc3a0256 uc3a1256 uc3a3256 uc3a4256 uc3b0256 uc3b1256

# List of all device families, with a family postfix
DEVICE_FAMILIES = $(AVR8_FAMILIES:%=%.avr8) $(XMEGA_FAMILIES:%=%.xmega) $(UC3_FAMILIES:%=%.uc3)


all: begin $(DEVICE_FAMILIES) clean end

arch_avr8:  begin $(AVR8_FAMILIES:%=%.avr8) end
arch_xmega: begin $(XMEGA_FAMILIES:%=%.xmega) end
arch_uc3:   begin $(UC3_FAMILIES:%=%.uc3) end

begin:
	@echo Executing build test "ModuleTest".
	@echo

end:
	@echo Build test "ModuleTest" complete.
	@echo

%.avr8:
	$(MAKE) -f makefile.avr8 clean -s
	$(MAKE) -f makefile.avr8 all MCU=$(@:%.avr8=%) -s

%.xmega:
	$(MAKE) -f makefile.xmega clean -s
	$(MAKE) -f makefile.xmega all MCU=$(@:%.xmega=%) -s

%.uc3:
	$(MAKE) -f makefile.uc3 clean -s
	$(MAKE) -f makefile.uc3 all MCU=$(@:%.uc3=%) -s

clean:
	$(MAKE) -f makefile.avr8 clean -s
	$(MAKE) -f makefile.xmega clean -s
	$(MAKE) -f makefile.uc3 clean -s

%:
	
# Bonsai C4 template code

Currently, the converter for Pro Micro to Bonsai C4 only does pin mapping. This is sufficient for simple keyboards and also a good start for
incorporating into more advanced keyboards with other features (like RGB, OLED, backlighting, split communiciations, etc.). However, to make
use of the more advanced features--including using the FRAM and flash memory chip included on Bonsai C4--various peripheral hardware must
be configured. Pro Micro does not requrie such configuration because such functionality is more limited and hard-wired to specific pins.

The code here provides examples that can be used to operate SPI, I2C, PWM, and Serial comms. In addition to using the converter, you will
need to take code (as-needed) and add it to existing config.h files, or add in new halconf.h and mcuconf.h files. If you are changing which 
pins are used for certain functions, you should verify the new pins support that functionality, and check all assingments to ensure the correct settings are used (including as-applicable driver, channel, PAL (Pin ALternate function) mode, DMA stream, and/or DMA channel).

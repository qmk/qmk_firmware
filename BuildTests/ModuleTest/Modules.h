#include <LUFA/Common/Common.h>

#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Drivers/Misc/RingBuffer.h>
#include <LUFA/Drivers/Misc/TerminalCodes.h>

#if (ARCH == ARCH_AVR8)
	#include <LUFA/Drivers/Peripheral/Serial.h>
	#include <LUFA/Drivers/Peripheral/TWI.h>
	#include <LUFA/Drivers/Peripheral/ADC.h>
	#include <LUFA/Drivers/Peripheral/SPI.h>
	#include <LUFA/Drivers/Peripheral/SerialSPI.h>
#elif (ARCH == ARCH_XMEGA)
	#include <LUFA/Drivers/Peripheral/Serial.h>
	#include <LUFA/Drivers/Peripheral/SPI.h>
	#include <LUFA/Drivers/Peripheral/SerialSPI.h>
#elif (ARCH == ARCH_UC3)
	
#endif
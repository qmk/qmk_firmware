This document is not complete, please try to add more to it to keep it as much up-to-date as possible.

*************ADDING NEW TARGET*************
TODO (partially)

UNAVAILABLE PERIPHERALS:
The original build system of the KSDK simply does not compile files which are not available on a target, mbed tries to compile everything. If your target tries to compile a peripheral which is not available, compilation will fail with a "No valid CPU defined!" error message. In the file which throws the error, replace the error code with: #define MBED_NO_[PERIPHERAL-NAME]. Then in the other .h and .c file in the same folder add #ifndef guards. See for an example: \mbed\targets\hal\TARGET_Freescale\TARGET_KPSDK_MCUS\TARGET_KPSDK_CODE\hal\lpuart.

SYSTEM_MKXXXXX.C:
The file included in the top cannot be found by the compiler, replace it by cmsis.h



************UPDATING KSDK FILES************
TODO (Also good luck with it).
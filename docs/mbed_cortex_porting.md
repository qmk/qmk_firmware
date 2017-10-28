## supported projects
### PS/2 converter
Confirmed it works on NXP LPC11U35.
- http://developer.mbed.org/platforms/TG-LPC11U35-501/

### Infinity keyboard
It runs on Freescale MK20DX128.



## compile error: cstddef
Experienced this with arm-none-eabi-gcc (4.8.2-14ubuntu1+6) 4.8.2 on ubuntu 14.04.

And resolved with 4.9.3 installed from:
- https://launchpad.net/gcc-arm-embedded
- https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded

```
$ make -f Makefile.mbed                                                                                                                                                         
mkdir -p build/.
arm-none-eabi-g++ -include config_mbed.h -mcpu=cortex-m0 -mthumb -c -g -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fshort-wchar -fno-builtin -MMD -MP -DNDEBUG -Os -DTARGET_LPC11U35_401 -DTARGET_M0 -DTARGET_NXP -DTARGET_LPC11UXX -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M0 -DARM_MATH_CM0 -DMBED_BUILD_TIMESTAMP=1399108688.49 -D__MBED__=1  -std=gnu++98 -I. -I../../mbed-sdk/libraries/mbed/targets -I../../mbed-sdk/libraries/mbed/targets/cmsis -I../../mbed-sdk/libraries/mbed/targets/cmsis/TARGET_NXP -I../../mbed-sdk/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX -I../../mbed-sdk/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM -I../../mbed-sdk/libraries/mbed/targets/cmsis/TARGET_NXP/TARGET_LPC11UXX/TOOLCHAIN_GCC_ARM/TARGET_LPC11U35_501 -I../../mbed-sdk/libraries/mbed/targets/hal -I../../mbed-sdk/libraries/mbed/targets/hal/TARGET_NXP -I../../mbed-sdk/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX -I../../mbed-sdk/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/TARGET_MCU_LPC11U35_501 -I../../mbed-sdk/libraries/mbed/targets/hal/TARGET_NXP/TARGET_LPC11UXX/TARGET_MCU_LPC11U35_501/TARGET_LPC11U35_501  -I../../mbed-sdk/libraries/mbed -I../../mbed-sdk/libraries/mbed/hal -I../../mbed-sdk/libraries/mbed/api -I../../mbed-sdk/libraries/mbed/common -I../../mbed-sdk/libraries/USBDevice -I../../mbed-sdk/libraries/USBDevice/USBHID -I../../mbed-sdk/libraries/USBDevice/USBDevice -I../../mbed-sdk/libraries/USBDevice/USBAudio -I../../mbed-sdk/libraries/USBDevice/USBSerial -I../../mbed-sdk/libraries/USBDevice/USBMSD -I../../mbed-sdk/libraries/USBDevice/USBMIDI -I../../protocol/mbed -I../../common -I../../protocol -o build/./main.o main.cpp
In file included from ../../mbed-sdk/libraries/mbed/api/mbed.h:21:0,
                 from main.cpp:1:
../../mbed-sdk/libraries/mbed/api/platform.h:25:19: fatal error: cstddef: No such file or directory
 #include <cstddef>
                   ^
compilation terminated.
make: *** [build/./main.o] Error 1

[13:13] noname@desk:/mnt/old_root/home/noname/tmp/tmk_keyboard/converter/ps2_usb
$ arm-none-eabi-gcc --version
arm-none-eabi-gcc (4.8.2-14ubuntu1+6) 4.8.2
Copyright (C) 2013 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
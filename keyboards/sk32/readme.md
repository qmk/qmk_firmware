# sk32

Keyboards built around the **3Think SK32F07x** Cortex-M0 MCU.  The SK32 ChibiOS
platform in `lib/chibios-contrib` provides native drivers for every peripheral
(SK32F0xx port) and does not depend on the shared STM32 low-level drivers.

* [W17PAD (kb17)](./kb17/) — 17-key numpad with RGB matrix and VIA support.
* [LD7 (ld7_oled)](./ld7_oled/) — 7-key macropad with 7-LED RGB strip and 128x32 OLED.

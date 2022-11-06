# KLOR keyboard with RP2040 MCU

This is the RP2040 revision of the firmware.
You can use several RP2040 based MCUs with Pro Micro formfactor.

- [Sparkfun Pro Micro RP2040](https://www.sparkfun.com/products/18288)
- [Boardsource Blok](https://boardsource.xyz/store/628b95b494dfa308a6581622)
- [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040) 
- [BastardKB Splinky](https://github.com/Bastardkb/Splinktegrated)
- [EliteMicro2040](https://github.com/Envious-Data/EnvOpenPico/tree/main/EliteMicro2040)
- [Sea-Picro](https://github.com/joshajohnson/sea-picro)
- [key micro RP](https://booth.pm/ja/items/3703539)

By default the config is setup for the pinout of the Sparkfun Pro Micro RP2040, which is used by most of the RP2040 based MCUs. Since the KB2040 has a slightly different pinout you need to uncomment the appropiate lines in the `/rp2040/rules.mk` file.


## Bootloader

Enter the bootloader in 3 ways:

- **Keycode in layout**: Press the key mapped to `QK_BOOTLOADER` if it is configured.
- **Physical reset button**: Quick double-tap on the reset button soldered on the PCB.
- **Controller boot button**: Hold the `BOOT` button on the controller and plug in the USB.
- **Bootmagic reset**: Hold down the top left key on the left half and plug in the controller.

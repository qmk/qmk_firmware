# WeAct Blackpill (STM32F4x1)

This document applies to the F401- and F411-based Blackpills.

The WeAct Blackpill is a popular choice for handwired boards, as it offers a powerful micro controller, USB Type C, a good number of pins to use, and a large amount of firmware space.  All for a ~$6 USD price tag.

* [WeAct GitHub for F4x1 Blackpill](https://github.com/WeActStudio/WeActStudio.MiniSTM32F4x1)
  * Unfortunately, due to supply issues official WeAct F411 based blackpills may not be available.

![Blackpill F411](/nCgeolTh.png)


## Pin Usage Limitations

While the Blackpill is a great choice to use in your keyboard, there are a number of caveats in regards to using them.  The first is that a number of exposed pins cannot be used, or have special considerations/hardware tweaks that are required for proper operation.

### Unusable pins
* Pins `A11` and `A12` are not usable because they're used for USB connection, and cannot be shared.
  * In theory, these pins can be used.  However, doing so may disable USB connectivity, outright, if used for anything other than a USB port
* Pin `B2` is used by `BOOT1` and cannot be used, without causing problems.
* `VBAT` is not a usable pin.
* `NRST` is not a usable pin.

### Pins to be avoided
* Pin `A9` is meant for VBUS Sense and should not be used, if it can be avoided.  It has an internal pull-down resistor, which may cause issues with usage.  However, a pull-up resistor can work (~5.1k), but should be avoided.
* Pin `A10` can be used, but should be avoided.  Any connection on this pin can prevent the bootloader from entering the proper mode for DFU flashing.  A pull-up resistor (~22k) on this pin fixes the bootloader issue.

### Shared Usage
* Pin `A0` is shared with the User Key (button) on the controller.  It can be used.
* Pin `C13` is shared with the onboard LED indicator, and is connected to +3.3V.  This can be used, but may cause the LED to blink intermittently, depending on activity on the pin.
* Pins `A4`, `A5`, `A6` and `A7` are used by the SOI8 footprint on the back of the controller, that can be used for either an SPI Flash chip, or an SPI EEPROM chip.  `A4` is the Chip Select pin, and cannot be shared.  However, `A5`, `A6`, and `A7` are the `SCK`, `MISO`, and `MOSI` pins, respectively, and can be shared with other SPI devices.

### Limited Usage
* Pins `C13`, `C14`, and `C15` have limits on output current. They should be used only as input, e.g., they should not be used for row pins in COL2ROW matrix configurations, but can be used as column pins.
  * This is because the column pins (in COL2ROW) are pulled up (the pull-up strength is independent of the current sourcing limitation) and the ROW is driven low and sinks current, then we check the state of the COLs to look for keypresses.

* Pins `A0` and `B5` are not 5V tolerant, and should only be used with 3.3V compatible functionality.

## Additional Information

### Bootloader issues

Due to the use of a 25MHz crystal, the controller may have issues entering the bootloader.  Heating up the controller can help with this issue.

Also, if pin `A10` is connected to anything at all, it needs to have a pull-up resistor (see [Pins to be avoided](#pins-to-be-avoided), above)

### Tiny UF2 Support

There is [tinyuf2 support for the WeAct Blackpill](https://github.com/adafruit/tinyuf2/tree/master/ports/stm32f4/boards/stm32f411ce_blackpill).  Instructions on how to compile the bootloader can be found [here](https://github.com/adafruit/tinyuf2#build-and-flash).  Setting `BOOTLOADER = tinyuf2` will enable support for this user bootloader, and the correct configuration to prevent it from being overwritten when flashing firmware.

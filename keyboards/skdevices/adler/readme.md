# adler

![adler](imgur.com image replace me!)

Introducing Adler - the latest keyboard from SKDevices that combines advanced technology with exceptional functionality. This ANSI TKL (Tenkeyless) model maintains a compact size without sacrificing essential features, making it an ideal choice for keyboard enthusiasts and professionals alike.

Key Features:
 - ANSI TKL Design: Compact and ergonomic Tenkeyless design that ensures comfortable use while saving desk space.
 - Built-in Rotary Encoder: Allows precise control over various functions, from volume adjustment to brightness changes.
 - OLED Display: Clear and customizable OLED display that provides real-time information to the user.
 - Five Additional Macro Keys: Boost your productivity with five programmable macro keys that can be tailored to your individual needs.
 - Reconfiguration via VIA: Enables easy and intuitive reconfiguration of the keyboard using VIA software, allowing customization of keys, macros, and other functions to suit your preferences.
 - Screw-in Stabilizers (Durock V2): Provide stability and minimize noise, enhancing typing comfort.
 - Aluminum Plate: Robust aluminum mounting plate that ensures durability and the right weight for the keyboard.
 - Wooden Case: Elegant and unique wooden case that adds natural charm and style to your desk.

Adler is not just a tool, but also a stylish addition to your desk. With a robust construction, aesthetic design, and modern features, it is a keyboard that will meet the expectations of even the most demanding users. Experience comfort, precision, and limitless customization possibilities with the Adler keyboard from SKDevices.

* Keyboard Maintainer: [Krzysztof Smosna](https://github.com/ksmosna)
* Hardware Supported: [SKDevices Adler](https://skdevices.pl/)
* Hardware Availability: skdevices.pl (soon)

Make example for this keyboard (after setting up your build environment):

    make skdevices/adler:default

Flashing example for this keyboard:

    make skdevices/adler:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

# GHero20 Wireless BLE

Fully customizable 3D printed guitar controller for Clone Hero! Design based on the Adafruit Feather Bluefruit 32u4.

![GitHub Logo](https://github.com/bryan065/GHero20-Files/blob/b49a4c8bf3821357dacbda5cb2a0039395c8d67b/GHero20.jpg)

https://clonehero.net/

https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le

* Keyboard Maintainer: [bryan065](https://github.com/yourusername)
* Hardware Supported: Adafruit Feather 32u4 Bluefruit LE (https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le)

Make example for this keyboard (after setting up your build environment):

    make ghero20:default

Flashing example for this keyboard:

    make ghero20:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Features
- Wirless BLE / Wired USB Modes.
- Wireless Qi charging / MagSafe compatible.
- Hotswap.
- Per key RGB.
- 4 programmable macro keys.
- Accelerometer for tilt star power.

### Modular Design

- The design is seperated into several modules which can each be printed on a standard Ender 3 (230mm x 230mm print bed).
- Upper Neck Module.
    - Houses the main frets and 5 mechanical switches.
    - Hotswap socket not available.
    - Fret buttons are mounted directly to swtiches like a regular keycap.
    - Optional stabilizers.
- Lower Neck Module.
    - Customizable faceplate for your own needs.
    - Currently houses the accelerometer.
- Strum Module.
    - Houses the strum bar.
- Controller Module.
    - Houses the 4 macro keys, controller, and wireless Qi/Magsafe receiver.
- Cosmetic Modules.
    - Different guitar styles can be customized or designed.
    
### Fret buttons

- Can be customized with any set of mechanical switches.
    - *Customizable with various switches, travel, and bottom out distances"

### Strum Bar

- Can be customized with any pair of mechanical keyboard switches.
    - *The design expects an actuation distance of 2 to 3mm and bottom out of 4mm*
    - *Using "fast" switches like Cherry MX Speed is not tested (1 to 1.5mm actuation distance)*
- Features a flexible mounting system to accommodate for various tolerances in 3D printer models.
- Features a magnetic centering system.
    - *No springs involved so you don't get the annoying pinging.*
    - *Silent strumming unless you choose clicky mechanical switches.*
    - *Adjustable tension / centering force.*
- Hotswap socket compatible.
    - *You can solder to the switches directly or use the optional hotswap socket holder*

### Macro Buttons

- 4 standard mechanical switch + keycap sockets.
    - *Can be customized with any mechanical switch.*
    - *Regular OEM/Cherry keycaps may be too tall for some users (gets in the way of strumming), in those cases, XDA/DSA profile is recommended.*
- Hotswap socket compatible.
    - *You can solder to the switches directly or use the optional hotswap socket holder*

### Controller

- Designed for the Adafruit Feather Bluefruit 32u4.
    - https://www.adafruit.com/product/2829
- Battery mounting is designed for the Adafruit 2500Mah battery.
    - https://www.adafruit.com/product/328
    - *The mounting mechanism can be easily customized for your battery size or you can just use double sided tape.*
- Micro USB is **NOT** in the ideal location.
    - *The design is meant to be used wirelessly. The port can be used to program the controller or last resort in wired mode.*
    - *Charging can be done via the MagSafe charger*.
- Wireless Qi Charging / MagSafe compatible.
    - *Requires installation of a Qi receiver coil & MagSafe magnet array.
    - **Warning: The coil uses the USB pin to charge. THERE IS NO PROTECTION IN PLACE FOR USB & WIRELESS CHARGING AT THE SAME TIME. Doing so may damage your USB port or controller.**

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

## Build instructions / Wiring / STL's

https://github.com/bryan065/GHero20-Files

## To-do

- [x] Accelerometer / Gyroscope for tilt control (star power)
    - MPU-9250
    - Added left/right hand support
- [x] Revamp fret button design for smoother and silent operation
- [ ] ~~OLED Display~~
    - Used for info display such as battery life
- [x] BLE Battery Service
    - Will report battery level to Windows 10 1809 or newer
    - OLED Display no longer needed
- [x] Additional ground breakouts for WS2812 and MPU-9250
- [x] Update strum part to enable tuning
    - [x]  Tension
    - [x]  Actuation distance/angle
    - [x]  Shock absorbtion
    - [x]  Centering force
- [x] Hotswap switch sockets
    - [x] Strum switches
    - [x] Macro switches
    - [x] ~~Fret switches~~ *(Not enough clearance in neck for sockets)*
        - *Something like Kailh low profile switches are needed to accommodate hotswap design*
- [ ] Upload STL's for guitar components
- [x] WS2812 RGB's
    - Per key lighting & dynamic lighting

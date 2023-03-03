
# Set of custom features
**Examples for all if these features can be found at `keyboards/elpekenin/access`**

## One Hand Mode
### **WIP**
The goal for this feature is to add a new *RGB Matrix* animation which only lights a single LED, used as a "marker" so that you can then virtually press the selected key. This will allow for accessibility, because the direction in which the LED moves and the trigger of the press is completely customizable (code does just the bare minimum), thus you can change which events trigger moving around and pressing, eg using different pointing devices, or a set of keys(arrows).

Config:
 - Add `ONE_HAND = yes` to your **rules.mk**

## Quantum Painter over XAP
XAP bindings that expose Quantum Painter's drawing and `get_geometry` functions.

Config:
 - Will automatically get added if you have both XAP and Quantum Painter enabled
 - You can disable it when both features are enabled by adding `QP_XAP = no`
 - Selecting a display, font or image relies on doing `load_display(device_handle)` for every screen, load and fonts are added to an array when loaded in `graphics.c`

If you want some QGF images, I have a collection of converted Material Design Icons (and scripts to generate them from folders) in [this repo](https://github.com/elpekenin/mdi-icons-qgf)

## Touch screen driver
### Needs to be re-written for SIPO control, but "regular" mode has been tested already
Custom code to interact with my XPT2046-based touchscreen modules, the code is designed such that other SPI sensors should be somewhat easy to integrate. In a similar philosophy to the one-hand mode, this code does the bare minimum: **read the sensor**, what to do based on it... up to your imagination.

Config:
 - Add `TOUCH_SCREEN = yes` to your **rules.mk**

## Shift register "pins"
### **Seems to work OK, more testing needed**
A set of macros and functions that allow using a SerialIn-ParallelOut(SIPO) shift register to control several signals, or even chain several together, so that you can generate *virtually* infinite output signals using 3 GPIOs on the MCU.
 - SCK
 - MOSI
 - CS

My use case for this feature is to drive a multi-SPI-screen setup. This has a drawback however, we need a dedicated SPI driver because we have to change pins(CS/DC) controlling the screens while a data transmision is going, so updating those outputs requires sending data to the register(s) via SPI, which would also be received by the screens in an un-desirable way.
Thus, I've made some patches to both `qp_comms_spi.c` and created a `custom_spi_master.h` to get things working.

Code so far expects the screens to use the "tradicional" names, like `SPI_SCK_PIN` and the register ones prepend `REGISTER_` to those names, they then get merged into an array such that screen's use the driver with index 0 and register has id 1.

How to use:
 - Add `SIPO_PINS = yes` to your **rules.mk**
 - Configure the amount of pins you'll use `#define N_SIPO_PINS <N_Pins>`
 - Create your pin(s) name(s) using: `configure_sipo_pins(NAME1, NAME2, ...)`
 - Change a pin's state by doing:
   - Manually set state: `set_sipo_pin(<pin_name>, true)` or `set_sipo_pin(<pin_name>, false)`
   - Using helper macros: `sipo_pin_high(<pin_name>)` or `sipo_pin_low(<pin_name>)`
 - Send the status to the registers: `write_sipo_state()`

## Custom EEPROM
Store the current status (enabled/disabled) of some features, so we can see if they've been changed since last boot (ie: flashed differently configured firmware)

Config:
 - Add `CUSTOM_EEPROM = yes` to your **rules.mk**
 - Call `custom_eeprom_generate()` to get current features' bitmask, and compare it with previous value (`eeconfig_read_user()`)
 - Update your EEPROM by doing `eeconfig_update_user(current_config)`

If you want some QGF images, I have a collection of converted Material Design Icons (and scripts to generate them from folders) in [this repo](https://github.com/elpekenin/mdi-icons-qgf)

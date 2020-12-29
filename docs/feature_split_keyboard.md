# Split Keyboard 

Many keyboards in the QMK Firmware repo are "split" keyboards. They use two controllers—one plugging into USB, and the second connected by a serial or an I<sup>2</sup>C connection over a TRRS or similar cable. 

Split keyboards can have a lot of benefits, but there is some additional work needed to get them enabled.  

QMK Firmware has a generic implementation that is usable by any board, as well as numerous board specific implementations. 

For this, we will mostly be talking about the generic implementation used by the Let's Split and other keyboards. 

!> ARM is not yet fully supported for Split Keyboards and has many limitations. Progress is being made, but we have not yet reached 100% feature parity.


## Compatibility Overview

| Transport                    | AVR                | ARM                |
|------------------------------|--------------------|--------------------|
| ['serial'](serial_driver.md) | :heavy_check_mark: | :white_check_mark: <sup>1</sup> |
| I2C                          | :heavy_check_mark: |                    |

Notes:

1. Both hardware and software limitations are detailed within the [driver documentation](serial_driver.md).

## Hardware Configuration

This assumes that you're using two Pro Micro-compatible controllers, and are using TRRS jacks to connect to two halves. 

### Required Hardware

Apart from diodes and key switches for the keyboard matrix in each half, you will need 2x TRRS sockets and 1x TRRS cable.

Alternatively, you can use any sort of cable and socket that has at least 3 wires. 

If you want to use I<sup>2</sup>C to communicate between halves, you will need a cable with at least 4 wires and 2x 4.7kΩ pull-up resistors.

#### Considerations 

The most commonly used connection is a TRRS cable and jacks.  These provide 4 wires, making them very useful for split keyboards, and are easy to find. 

However, since one of the wires carries VCC, this means that the boards are not hot pluggable. You should always disconnect the board from USB before unplugging and plugging in TRRS cables, or you can short the controller, or worse. 

Another option is to use phone cables (as in, old school RJ-11/RJ-14 cables). Make sure that you use one that actually supports 4 wires/lanes.  

However, USB cables, SATA cables, and even just 4 wires have been known to be used for communication between the controllers. 

!> Using USB cables for communication between the controllers works just fine, but the connector could be mistaken for a normal USB connection and potentially short out the keyboard, depending on how it's wired.  For this reason, they are not recommended for connecting split keyboards.  

### Serial Wiring

The 3 wires of the TRS/TRRS cable need to connect GND, VCC, and D0/D1/D2/D3 (aka PD0/PD1/PD2/PD3) between the two Pro Micros. 

?> Note that the pin used here is actually set by `SOFT_SERIAL_PIN` below.

<img alt="sk-pd0-connection-mono" src="https://user-images.githubusercontent.com/2170248/92296488-28e9ad80-ef70-11ea-98be-c40cb48a0319.JPG" width="48%"/>
<img alt="sk-pd2-connection-mono" src="https://user-images.githubusercontent.com/2170248/92296490-2d15cb00-ef70-11ea-801f-5ace313013e6.JPG" width="48%"/>

### I<sup>2</sup>C Wiring

The 4 wires of the TRRS cable need to connect GND, VCC, and SCL and SDA (aka PD0/pin 3 and PD1/pin 2, respectively) between the two Pro Micros. 

The pull-up resistors may be placed on either half. If you wish to use the halves independently, it is also possible to use 4 resistors and have the pull-ups in both halves.

<img alt="sk-i2c-connection-mono" src="https://user-images.githubusercontent.com/2170248/92297182-92b98580-ef77-11ea-9d7d-d6033914af43.JPG" width="50%"/>

## Firmware Configuration

To enable the split keyboard feature, add the following to your `rules.mk`: 

```make
SPLIT_KEYBOARD = yes
```

If you're using a custom transport (communication method), then you will also need to add: 

```make
SPLIT_TRANSPORT = custom
```

### Setting Handedness

By default, the firmware does not know which side is which; it needs some help to determine that. There are several ways to do this, listed in order of precedence.

#### Handedness by Pin

You can configure the firmware to read a pin on the controller to determine handedness.  To do this, add the following to your `config.h` file:

```c
#define SPLIT_HAND_PIN B7
```

This will read the specified pin. If it's high, then the controller assumes it is the left hand, and if it's low, it's assumed to be the right side. 

#### Handedness by Matrix Pin

You can configure the firmware to read key matrix pins on the controller to determine handedness.  To do this, add the following to your `config.h` file:

```c
#define SPLIT_HAND_MATRIX_GRID D0, F1
```

The first pin is the output pin and the second is the input pin.

Some keyboards have unused intersections in the key matrix. This setting uses one of these unused intersections to determine the handness.

Normally, when a diode is connected to an intersection, it is judged to be left. If you add the following definition, it will be judged to be right.

```c
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
```

#### Handedness by EEPROM

This method sets the keyboard's handedness by setting a flag in the persistent storage (`EEPROM`).  This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout. 


To enable this method, add the following to your `config.h` file: 

```c
#define EE_HANDS
```

However, you'll have to flash the EEPROM files for the correct hand to each controller.  You can do this manually, or there are targets for avrdude and dfu to do this, while flashing the firmware: 

* `:avrdude-split-left`
* `:avrdude-split-right`
* `:dfu-split-left`
* `:dfu-split-right`
* `:dfu-util-split-left`
* `:dfu-util-split-right`

This setting is not changed when re-initializing the EEPROM using the `EEP_RST` key, or using the `eeconfig_init()` function.  However, if you reset the EEPROM outside of the firmware's built in options (such as flashing a file that overwrites the `EEPROM`, like how the [QMK Toolbox]()'s "Reset EEPROM" button works), you'll need to re-flash the controller with the `EEPROM` files. 

You can find the `EEPROM` files in the QMK firmware repo, [here](https://github.com/qmk/qmk_firmware/tree/master/quantum/split_common). 

#### Handedness by `#define`

You can set the handedness at compile time.  This is done by adding the following to your `config.h` file:

```c
#define MASTER_RIGHT
```

or 

```c
#define MASTER_LEFT
```

If neither are defined, the handedness defaults to `MASTER_LEFT`.


### Communication Options

Because not every split keyboard is identical, there are a number of additional options that can be configured in your `config.h` file.

```c
#define USE_I2C
```

This enables I<sup>2</sup>C support for split keyboards. This isn't strictly for communication, but can be used for OLED or other I<sup>2</sup>C-based devices. 

```c
#define SOFT_SERIAL_PIN D0
```

This sets the pin to be used for serial communication. If you're not using serial, you shouldn't need to define this.  

However, if you are using serial and I<sup>2</sup>C on the board, you will need to set this, and to something other than D0 and D1 (as these are used for I<sup>2</sup>C communication).

```c
#define SELECT_SOFT_SERIAL_SPEED {#}`
```

If you're having issues with serial communication, you can change this value, as it controls the communication speed for serial.  The default is 1, and the possible values are:

* **`0`**: about 189kbps (Experimental only)
* **`1`**: about 137kbps (default)
* **`2`**: about 75kbps
* **`3`**: about 39kbps
* **`4`**: about 26kbps
* **`5`**: about 20kbps

###  Hardware Configuration Options

There are some settings that you may need to configure, based on how the hardware is set up. 

```c
#define MATRIX_ROW_PINS_RIGHT { <row pins> }
#define MATRIX_COL_PINS_RIGHT { <col pins> }
```

This allows you to specify a different set of pins for the matrix on the right side.  This is useful if you have a board with differently-shaped halves that requires a different configuration (such as Keebio's Quefrency).

```c
#define DIRECT_PINS_RIGHT { { F1, F0, B0, C7 }, { F4, F5, F6, F7 } }
```

This allows you to specify a different set of direct pins for the right side.

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
```

This allows you to specify a different set of encoder pins for the right side.

```c
#define RGBLIGHT_SPLIT
```

This option enables synchronization of the RGB Light modes between the controllers of the split keyboard.  This is for keyboards that have RGB LEDs that are directly wired to the controller (that is, they are not using the "extra data" option on the TRRS cable).

```c
#define RGBLED_SPLIT { 6, 6 }
```

This sets how many LEDs are directly connected to each controller.  The first number is the left side, and the second number is the right side.  

?> This setting implies that `RGBLIGHT_SPLIT` is enabled, and will forcibly enable it, if it's not.


```c
#define SPLIT_USB_DETECT
```
This option changes the startup behavior to detect an active USB connection when delegating master/slave. If this operation times out, then the half is assume to be a slave. This is the default behavior for ARM, and required for AVR Teensy boards (due to hardware limitations).

?> This setting will stop the ability to demo using battery packs.

```c
#define SPLIT_USB_TIMEOUT 2000
```
This sets the maximum timeout when detecting master/slave when using `SPLIT_USB_DETECT`.

```c
#define SPLIT_USB_TIMEOUT_POLL 10
```
This sets the poll frequency when detecting master/slave when using `SPLIT_USB_DETECT`

## Hardware Considerations and Mods

While most any Pro Micro can be used, micro controllers like the AVR Teensys and most (if not all) ARM boards require the Split USB Detect.

However, with the Teensy 2.0 and Teensy++ 2.0, there is a simple hardware mod that you can perform to add VBUS detection, so you don't need the Split USB detection option.

You'll only need a few things:

* A knife (x-acto knife, ideally)
* A solder station or hot air station
* An appropriate Schottky diode, such as the [PMEG2005EH](https://www.digikey.com/en/products/detail/nexperia-usa-inc/PMEG2005EH,115/1589924)

You'll need to cut the small trace between the 5V and center pads on the back of the Teensy.

Once you have done that, you will want to solder the diode from the 5V pad to the center pad.

You may need to use the 5V pad from the regulator block above as the pads were too small and placed too closely together to place the Schottky diode properly.

![Teensy++ 2.0](https://i.imgur.com/BPEC5n5.png)

## Additional Resources

Nicinabox has a [very nice and detailed guide](https://github.com/nicinabox/lets-split-guide) for the Let's Split keyboard, that covers most everything you need to know, including troubleshooting information. 

However, the RGB Light section is out of date, as it was written long before the RGB Split code was added to QMK Firmware. Instead, wire each strip up directly to the controller.

<!-- I may port this information later, but for now ... it's very nice, and covers everything -->

# Split Keyboard 

Many keyboards in QMK Firmware's repo are "split" keyboards. Meaning, they use two controllers, one plugging into USB, and the second connected by a serial or an I<sup>2</sup>C connection over a TRRS or similar cable. 

Split keyboards can have a lot of benefits, but there are some additional work to get them enabled.  

QMK Firmware has a generic implementation that is usable by any board, as well as numerous board specific implementations. 

For this, we will mostly be talking about the generic implementation used by the Lets Split and other keyboards. 


## Hardware Configuration

This assumes that you're using two Pro Micro compatible controllers, and are using TRRS jacks to connect to two halves. 

### Required Hardware

Apart from diodes and key switches for the keyboard matrix in each half, you will need 2x TRRS sockets and 1x TRRS cable

Alternatively, you can use any sort of cable and socket that has at least 3 wires. 

If you want to use I2C to communicate between halves, you will need a cable with at least 4 wires and 2x 4.7kΩ pull-up resistors.



### Serial Wiring

The 3 wires of the TRS/TRRS cable need to connect GND, VCC, and D0 (aka PDO or pin 3) between the two Pro Micros. 

?> Note that pin used here is actually set by `SOFT_SERIAL_PIN` below.

![serial wiring](https://i.imgur.com/C3D1GAQ.png)

### I2C Wiring

The 4 wires of the TRRS cable need to connect GND, VCC, and SLC and SDA (aka PD0/pin 3 and PD1/pin 2, respectively) between the two Pro Micros. 

The pull-up resistors may be placed on either half. It is also possible
to use 4 resistors and have the pull-ups in both halves, but this is
unnecessary in simple use cases.

![i2c wiring](https://i.imgur.com/Hbzhc6E.png)

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

By default, the firmware does not know what side is which.  It needs some help to determine that. And there are several ways to do this.  And they are listed in order of precedence. 

#### Handedness by Pin

You can configure the firmware to read a pin on the controller to determine handedness.  To do this, add the following to your `config.h` file:

```c
#define SPLIT_HAND_PIN B7
```

This will read the specified pin. If it's high, then the controller assumes it is the left hand, and if it's low, it's assumed to be the right side. 

#### Handedness by EEPROM

This method sets the and reads the handedness by using the EEPROM (persistent storage of the controller). 

To set enable this method, add the following to your `config.h` file: 

```c
#define EE_HANDS
```

However, you'll have to flash the eeprom files for the correct hand to each controller.  You can do this manually, or there are targets for avrdude and dfu to do this, while flashing the firmware: 

* `:avrdude-split-left`
* `:avrdude-split-right`
* `:dfu-split-left`
* `:dfu-split-right`

If you reset the eeprom outside of the firmeware's built in options (such as using the QMK Toolbox's "reset EEPROM" option), you'll need to re-flash the EEPROM files. 

You can find the EEPROM files in the QMK firmware repo, [here](https://github.com/qmk/qmk_firmware/tree/master/quantum/split_common). 

#### Handedness by define

You can set the handedness at compile time.  This is done by adding the following to your `config.h` file:

```c
#define MASTER_RIGHT
```

or 

```c
#define MASTER_LEFT
```

Or by not defining any of these options (which defaults to `MASTER_LEFT`, in this case. 


### Communication options

Because not every split keyboard is identical, there are a number of additional options that can be configured in your `config.h` file.

```c
#define USE_I2C
```

This enables I<sup>2</sup>C support for split keyboards. This isn't strictly for communication, but can be used for OLED or other I<sup>2</sup>C based devices. 

```c
#define SOFT_SERIAL_PIN D0
```

This sets the pin to be used for serial communication. If you're not using serial, you shouldn't need to define this. 

```c
#define SELECT_SOFT_SERIAL_SPEED {#}` 
```

If you're having issues with serial communication, you can change this value, as it controls the communication speed for serial.  It defaults to 1, but the possible values are: 

    * __0__: about 189kbps (Experimental only)
    * __1__: about 137kbps (default)
    * __2__: about 75kbps
    * __3__: about 39kbps
    * __4__: about 26kbps
    * __5__: about 20kbps

###  Hardware Configuration Options

There are some settings that you may need to configure, based on how the hardware is set up. 

```c
#define MATRIX_ROW_PINS_RIGHT { <row pins> }
#define MATRIX_COL_PINS_RIGHT { <col pins> }
```

This allows you to specify a different set of pins for the matrix on the right side.  This is useful, if you have a board that the halves are very differently shaped, and need different configurations (such as Keebio's Quefrency keyboard).

```c
#define RGBLED_SPLIT { 6, 6 }
```

This lets set how many LEDs are connected to each controller. 

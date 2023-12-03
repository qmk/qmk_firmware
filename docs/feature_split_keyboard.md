# Split Keyboard 

Many keyboards in the QMK Firmware repo are "split" keyboards. They use two controllers—one plugging into USB, and the second connected by a serial or an I<sup>2</sup>C connection over a TRRS or similar cable. 

Split keyboards can have a lot of benefits, but there is some additional work needed to get them enabled.  

QMK Firmware has a generic implementation that is usable by any board, as well as numerous board specific implementations. 

For this, we will mostly be talking about the generic implementation used by the Let's Split and other keyboards. 

!> ARM split supports most QMK subsystems when using the 'serial' and 'serial_usart' drivers. I2C slave is currently unsupported.

!> Both sides must use the same MCU family, for eg two Pro Micro-compatible controllers or two Blackpills. Currently, mixing AVR and ARM is not possible as ARM vs AVR uses different method for serial communication, and are not compatible. Moreover Blackpill's uses 3.3v logic, and atmega32u4 uses 5v logic.

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
Note that the total resistance for the connected system should be within spec at 2.2k-10kOhm, with an 'ideal' at 4.7kOhm, regardless of the placement and number.

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

### Layout Macro

Configuring your layout in a split keyboard works slightly differently to a non-split keyboard. Take for example the following layout. The top left numbers refer to the matrix row and column, and the bottom right are the order of the keys in the layout:

![Physical layout](https://i.imgur.com/QeY6kMQ.png)

Since the matrix scanning procedure operates on entire rows, it first populates the left half's rows, then the right half's. Thus, the matrix as QMK views it has double the rows instead of double the columns:

![Matrix](https://i.imgur.com/4wjJzBU.png)

### Setting Handedness

By default, the firmware does not know which side is which; it needs some help to determine that. There are several ways to do this, listed in order of precedence.

#### Handedness by Pin

You can configure the firmware to read a pin on the controller to determine handedness.  To do this, add the following to your `config.h` file:

```c
#define SPLIT_HAND_PIN B7
```

This will read the specified pin. By default, if it's high, then the controller assumes it is the left hand, and if it's low, it's assumed to be the right side. 

This behaviour can be flipped by adding this to you `config.h` file:

```c
#define	SPLIT_HAND_PIN_LOW_IS_LEFT
```

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

Note that adding a diode at a previously unused intersection will effectively tell the firmware that there is a key held down at that point. You can instruct qmk to ignore that intersection by defining `MATRIX_MASKED` and then defining a `matrix_row_t matrix_mask[MATRIX_ROWS]` array in your keyboard config. Each bit of a single value (starting form the least-significant bit) is used to tell qmk whether or not to pay attention to key presses at that intersection.

While `MATRIX_MASKED` isn't necessary to use `SPLIT_HAND_MATRIX_GRID` successfully, without it you may experience issues trying to suspend your computer with your keyboard attached as the matrix will always report at least one key-press.

#### Handedness by EEPROM

This method sets the keyboard's handedness by setting a flag in the persistent storage (`EEPROM`).  This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout. 


To enable this method, add the following to your `config.h` file: 

```c
#define EE_HANDS
```

Next, you will have to flash the correct handedness option to the controller on each halve. You can do this manually with the following bootloader targets using `qmk flash -kb <keyboard> -km <keymap> -bl <bootloader>` command to flash:

|Microcontroller Type|Bootloader Parameter|
|--------------------|--------------------|
|AVR controllers with Caterina bootloader<br>(e.g. Pro Micro)|`avrdude-split-left`<br>`avrdude-split-right`|
|AVR controllers with the stock Amtel DFU or DFU compatible bootloader<br>(e.g. Elite-C)|`dfu-split-left`<br>`dfu-split-right`|
|ARM controllers with a DFU compatible bootloader<br>(e.g. Proton-C)|`dfu-util-split-left`<br>`dfu-util-split-right`|
|ARM controllers with a UF2 compatible bootloader<br>(e.g. RP2040)|`uf2-split-left`<br>`uf2-split-right`|

Example for `crkbd/rev1` keyboard with normal AVR Pro Micro MCUs, reset the left controller and run:
```
qmk flash -kb crkbd/rev1 -km default -bl avrdude-split-left
```
Reset the right controller and run:
```
qmk flash -kb crkbd/rev1 -km default -bl avrdude-split-right
```

?> Some controllers (e.g. Blackpill with DFU compatible bootloader) will need to be flashed with handedness bootloader parameter every time because it is not retained between flashes.

?> [QMK Toolbox]() can also be used to flash EEPROM handedness files. Place the controller in bootloader mode and select menu option Tools -> EEPROM -> Set Left/Right Hand

This setting is not changed when re-initializing the EEPROM using the `EE_CLR` key, or using the `eeconfig_init()` function.  However, if you reset the EEPROM outside of the firmware's built in options (such as flashing a file that overwrites the `EEPROM`, like how the [QMK Toolbox]()'s "Reset EEPROM" button works), you'll need to re-flash the controller with the `EEPROM` files. 

You can find the `EEPROM` files in the QMK firmware repo, [here](https://github.com/qmk/qmk_firmware/tree/master/quantum/split_common).


#### Handedness by `#define`

You can use this option when USB cable is always connected to just one side of the split keyboard.

If the USB cable is always connected to the right side, add the following to your `config.h` file and flash both sides with this option:
```c
#define MASTER_RIGHT
```

If the USB cable is always connected to the left side, add the following to your `config.h` file and flash both sides with this option:
```c
#define MASTER_LEFT
```

?> If neither options are defined, the handedness defaults to `MASTER_LEFT`.


### Communication Options

Because not every split keyboard is identical, there are a number of additional options that can be configured in your `config.h` file.

```c
#define USE_I2C
```

This configures the use of I<sup>2</sup>C support for split keyboard transport (AVR only).  

```c
#define SOFT_SERIAL_PIN D0
```

This sets the pin to be used for serial communication. If you're not using serial, you shouldn't need to define this.  

However, if you are using serial and I<sup>2</sup>C on the board, you will need to set this, and to something other than D0 and D1 (as these are used for I<sup>2</sup>C communication).

```c
#define SELECT_SOFT_SERIAL_SPEED {#}
```

If you're having issues with serial communication, you can change this value, as it controls the communication speed for serial.  The default is 1, and the possible values are:

* **`0`**: about 189kbps (Experimental only)
* **`1`**: about 137kbps (default)
* **`2`**: about 75kbps
* **`3`**: about 39kbps
* **`4`**: about 26kbps
* **`5`**: about 20kbps

```c
#define FORCED_SYNC_THROTTLE_MS 100
```

This sets the maximum number of milliseconds before forcing a synchronization of data from master to slave. Under normal circumstances this sync occurs whenever the data _changes_, for safety a data transfer occurs after this number of milliseconds if no change has been detected since the last sync. 

```c
#define SPLIT_MAX_CONNECTION_ERRORS 10
```
This sets the maximum number of failed communication attempts (one per scan cycle) from the master part before it assumes that no slave part is connected. This makes it possible to use a master part without the slave part connected.

Set to 0 to disable the disconnection check altogether.

```c
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
```
How long (in milliseconds) the master part should block all connection attempts to the slave after the communication has been flagged as disconnected (see `SPLIT_MAX_CONNECTION_ERRORS` above).

One communication attempt will be allowed everytime this amount of time has passed since the last attempt. If that attempt succeeds, the communication is seen as working again.

Set to 0 to disable this throttling of communications while disconnected. This can save you a couple of bytes of firmware size.


### Data Sync Options

The following sync options add overhead to the split communication protocol and may negatively impact the matrix scan speed when enabled. These can be enabled by adding the chosen option(s) to your `config.h` file.

```c
#define SPLIT_TRANSPORT_MIRROR
```

This mirrors the master side matrix to the slave side for features that react or require knowledge of master side key presses on the slave side. The purpose of this feature is to support cosmetic use of key events (e.g. RGB reacting to keypresses).

```c
#define SPLIT_LAYER_STATE_ENABLE
```

This enables syncing of the layer state between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the currently active layer.

```c
#define SPLIT_LED_STATE_ENABLE
```

This enables syncing of the Host LED status (caps lock, num lock, etc) between both halves of the split keyboard. The main purpose of this feature is to enable support for use of things like OLED display of the Host LED status.

```c
#define SPLIT_MODS_ENABLE
```

This enables transmitting modifier state (normal, weak and oneshot) to the non primary side of the split keyboard. The purpose of this feature is to support cosmetic use of modifer state (e.g. displaying status on an OLED screen).

```c
#define SPLIT_WPM_ENABLE
```

This enables transmitting the current WPM to the slave side of the split keyboard. The purpose of this feature is to support cosmetic use of WPM (e.g. displaying the current value on an OLED screen).

```c
#define SPLIT_OLED_ENABLE
```

This enables transmitting the current OLED on/off status to the slave side of the split keyboard. The purpose of this feature is to support state (on/off state only) syncing.

```c
#define SPLIT_ST7565_ENABLE
```

This enables transmitting the current ST7565 on/off status to the slave side of the split keyboard. The purpose of this feature is to support state (on/off state only) syncing.

```c
#define SPLIT_POINTING_ENABLE
```

This enables transmitting the pointing device status to the master side of the split keyboard. The purpose of this feature is to enable use pointing devices on the slave side. 

!> There is additional required configuration for `SPLIT_POINTING_ENABLE` outlined in the [pointing device documentation](feature_pointing_device.md?id=split-keyboard-configuration).

```c
#define SPLIT_HAPTIC_ENABLE
```

This enables the triggering of haptic feedback on the slave side of the split keyboard. This will send information to the slave side such as the mode, dwell, and whether buzz is enabled.

```c
#define SPLIT_ACTIVITY_ENABLE
```

This synchronizes the activity timestamps between sides of the split keyboard, allowing for activity timeouts to occur.

### Custom data sync between sides :id=custom-data-sync

QMK's split transport allows for arbitrary data transactions at both the keyboard and user levels. This is modelled on a remote procedure call, with the master invoking a function on the slave side, with the ability to send data from master to slave, process it slave side, and send data back from slave to master.

To leverage this, a keyboard or user/keymap can define a comma-separated list of _transaction IDs_:

```c
// for keyboard-level data sync:
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_SYNC_A, KEYBOARD_SYNC_B
// or, for user:
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_A, USER_SYNC_B, USER_SYNC_C
```

These _transaction IDs_ then need a slave-side handler function to be registered with the split transport, for example:

```c
typedef struct _master_to_slave_t {
    int m2s_data;
} master_to_slave_t;

typedef struct _slave_to_master_t {
    int s2m_data;
} slave_to_master_t;

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
    slave_to_master_t *s2m = (slave_to_master_t*)out_data;
    s2m->s2m_data = m2s->m2s_data + 5; // whatever comes in, add 5 so it can be sent back
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}
```

The master side can then invoke the slave-side handler - for normal keyboard functionality to be minimally affected, any keyboard- or user-level code attempting to sync data should be throttled:

```c
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            master_to_slave_t m2s = {6};
            slave_to_master_t s2m = {0};
            if(transaction_rpc_exec(USER_SYNC_A, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprintf("Slave value: %d\n", s2m.s2m_data); // this will now be 11, as the slave adds 5
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
```

!> It is recommended that any data sync between halves happens during the master side's _housekeeping task_. This ensures timely retries should failures occur.

If only one-way data transfer is needed, helper methods are provided:

```c
bool transaction_rpc_exec(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
bool transaction_rpc_send(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer);
bool transaction_rpc_recv(int8_t transaction_id, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
```

By default, the inbound and outbound data is limited to a maximum of 32 bytes each. The sizes can be altered if required:

```c
// Master to slave:
#define RPC_M2S_BUFFER_SIZE 48
// Slave to master:
#define RPC_S2M_BUFFER_SIZE 48
```

###  Hardware Configuration Options

There are some settings that you may need to configure, based on how the hardware is set up. 

```c
#define MATRIX_ROW_PINS_RIGHT { <row pins> }
#define MATRIX_COL_PINS_RIGHT { <col pins> }
```

This allows you to specify a different set of pins for the matrix on the right side.  This is useful if you have a board with differently-shaped halves that requires a different configuration (such as Keebio's Quefrency). The number of pins in the right and left matrices must be the same, if you have a board with a different number of rows or columns on one side, pad out the extra spaces with `NO_PIN` and make sure you add the unused rows or columns to your matrix.

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

Enabling this option changes the startup behavior to listen for an active USB communication to delegate which part is master and which is slave. With this option enabled and theres's USB communication, then that half assumes it is the master, otherwise it assumes it is the slave.

Without this option, the master is the half that can detect voltage on the physical USB connection (VBUS detection).

Enabled by default on ChibiOS/ARM.

?> This setting will stop the ability to demo using battery packs.

```c
#define SPLIT_USB_TIMEOUT 2000
```
This sets the maximum timeout when detecting master/slave when using `SPLIT_USB_DETECT`.

```c
#define SPLIT_USB_TIMEOUT_POLL 10
```
This sets the poll frequency when detecting master/slave when using `SPLIT_USB_DETECT`

```c
#define SPLIT_WATCHDOG_ENABLE
```

This will enable a software watchdog on any side delegated as slave and will reboot the keyboard if no successful communication occurs within `SPLIT_WATCHDOG_TIMEOUT`. This can be particularly helpful when `SPLIT_USB_DETECT` delegates both sides as slave in some circumstances.

```c
#define SPLIT_WATCHDOG_TIMEOUT 3000
```
This set the maximum slave timeout when waiting for communication from master when using `SPLIT_WATCHDOG_ENABLE`

## Hardware Considerations and Mods

Master/slave delegation is made either by detecting voltage on VBUS connection or waiting for USB communication (`SPLIT_USB_DETECT`). Pro Micro boards can use VBUS detection out of the box and be used with or without `SPLIT_USB_DETECT`.

Many ARM boards, but not all, do not support VBUS detection. Because it is common that ARM boards lack VBUS detection, `SPLIT_USB_DETECT` is automatically defined on ARM targets (technically when ChibiOS is targetted).

### Teensy boards

Teensy boards lack VBUS detection out of the box and must have `SPLIT_USB_DETECT` defined. With the Teensy 2.0 and Teensy++ 2.0, there is a simple hardware mod that you can perform to add VBUS detection, so you don't need the `SPLIT_USB_DETECT` option.

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

# OLED Control

QMK has the ability to control the content of the OLED screens attached to your keyboard. Generally this is done through keyboard-level C code, but this feature allows the content of the screens to be changed from the operating system. This makes it possible to have more dynamic information displayed, such as current weather, stocks, system utilization, and anything else you can imagine.

![Lily58 with custom OLED content](https://raw.githubusercontent.com/Drauthius/go-oled-controller/master/example.jpg)

Controlling the OLED screens requires that the keyboard uses the [OLED driver](feature_oled_driver.md), and that there is a user-space program using [raw HID](feature_rawhid.md) to communicate with the firmware. This feature is compatible with VIA, but typically only one program can communicate with the keyboard at one time.

## Usage

To enable the OLED control feature, there are three steps. First, when compiling your keyboard, you'll need to add the following to your `rules.mk`:

```make
OLED_DRIVER_ENABLE = yes
OLED_CONTROL_ENABLE = yes
RAW_ENABLE = yes
```

Then in your `keymap.c` file, inside the `oled_task()` function, add a call to the OLED control library to draw the screen. This example will fill the screen with information from the operating system if there is any available, otherwise revert to the default information:

```c
void oled_task_user(void) {
#ifdef OLED_CONTROL_ENABLE
    // If the screen has been filled by the operating system, then use that,
    // otherwise revert to the default.
    if (oledctrl_draw()) {
        return;
    }
#endif

    // Normal content to show goes here.
    ...
}
```

The last, and most important step, is to have a user-space program that feeds the OLED screens with things to draw. This is done through the [raw HID feature](feature_rawhid.md), using the protocol described below.

## Protocol

Data sent to and from the firmware contains a three-byte header. The first byte is the type, the second is the subtype, and the third is the screen index to control, starting at zero.

### Sending a command

|Byte|Description|
|----|-----------|
|1   |Should always be `0xC0`, to indicate that this is a command.|
|2   |A command ID from the table below.|
|3   |Screen ID. `0x00` to control the master side, or `0x01` to control the slave side, which requires split to be enabled.|
|4..32|Any other data that the command might need.|

|Command|Name|Description|
|-------|----|-----------|
|`0x00` |Set Up|Prepare the screen. This will clear all the content, and return the screen width and height as number of characters in the fourth and fifth bytes of the response.|
|`0x01` |Clear|Clear the content of the screen.|
|`0x02` |Set Line|Set the content of a line/row. The fourth byte should be which line to modify, and all the bytes following should be the content. Will replace everything on that line, and will not wrap to the next one.|
|`0x03` |Set Chars|Set a portion of the screen. The fourth byte should be the offset, the fifth byte the length of the data, and all the bytes following should be the content. Will replace until the length is reached, and will wrap if it goes over a line.|
|`0x04` |Present|Show the changes to the screen. This has to be called after the desired number of lines or characters have been set.|

### Receiving a response

|Byte|Description|
|----|-----------|
|1   |The result code. Either `0x00` for success, or `0x01` for failure.|
|2   |The command ID that the response is for.|
|3   |The screen ID.|
|4..32|Typically the same data that was sent as a command. The exception is the Set Up command, which will return the width and height of the OLED screen.|

### Receiving an event

The module also supports events, which are typically generated from key presses on the keyboard sent to the user-space program through the raw HID channel. This allows for certain key presses to change what the user-space program displays or does.

|Byte|Description|
|1   |Always `0xC1`, to indicate that this is an event.|
|2   |An event ID from the table below.|
|3..32|Any other data that the event wants to pass.|

Below is a list of predefined events, but it is up to the user-space program to interpret and handle them.

|Event|Name|Description|
|`0x00`|Set Tag|Specify which tag/view to show on the screen. The third byte is the screen ID, and the fourth is the tag ID that the user-space program recognises.|
|`0x01`|Increment Tag|Tell the user-space program to show the next tag. The third byte is the screen ID.|
|`0x02`|Decrement Tag|Tell the user-space program to show the previous tag. The third byte is the screen ID.|
|\*   | | Any other value. It is up to the user-space program to parse and handle the events, and can essentially do anything.|

To send an event simply invoke the function `oledctrl_send_event()` with an event ID, and any data that you wish to pass. This example in `keymap.c` uses custom keycodes defined in VIA to allow for sending events:

```c
#ifdef OLED_CONTROL_ENABLE
    #include "oledctrl.h"
    #include "via.h"
#endif

enum custom_keycodes {
#ifdef OLED_CONTROL_ENABLE
    INC_TAG = USER00,
    DEC_TAG = USER01,
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef OLED_CONTROL_ENABLE
    case INC_TAG:
        uint8_t screen = 0x00;
        oledctrl_send_event(OLEDCTRL_EVENT_INCREMENT_TAG, &screen, 1);
        return false; // Don't keep processing.
        break;
    case DEC_TAG:
        uint8_t screen = 0x00;
        oledctrl_send_event(OLEDCTRL_EVENT_DECREMENT_TAG, &screen, 1);
        return false; // Don't keep processing.
        break;
#endif
    }
}
```

The `USER00` and `USER01` keycodes then need be assigned to the keymap, either statically or in VIA.

A rotary encoder could be set up in a similar way to send events when it is spun, thus changing the content of the screen.

## Split keyboard

This feature has support for controlling the OLED screens on split keyboards that use the Split Common code.

To compile the code necessary to make the feature work, simply add the following to your `config.h`:

```c
#define OLEDCTRL_SPLIT
```

Then, any commands sent over raw HID with the screen ID field set to `0x01` will be passed to the slave side via the serial or I2C. It might be necessary to add a short delay, e.g. 10 milliseconds, between commands to the slave side, or some commands might get overwritten before the slave side has time to process them.

## Special characters

When writing content to the OLED screens, the font file will be used. This makes it possible to show different icons and even logos. There are utilities online where one can upload and modify `glcdfont.c` files, and then load them into the firmware and have the user-space program show them on the screens by including the correct decimal value. For example, adding the byte `0x01` to the content of the Set Line or Set Chars command will draw the second character in the font file.

Furthermore, this feature recognises and replaces some specific characters. The replacement is done in the QMK firmware, which allows for quick output to certain changes, such as the current layer.

|Characters|Replaced by|
|----------|-----------|
|`%l`      |The current layer, as returned by the overridable function `read_layer_state()`.|

## Advanced

### Custom raw HID receive function

Define `OLEDCTRL_CUSTOM_HID_RECEIVE` in `config.h` to not have this feature create a function for handling raw HID messages directly. When defined, you will need to manually call `oledctrl_handle_cmd()` within your own handling of raw HID messages to have this feature do anything.

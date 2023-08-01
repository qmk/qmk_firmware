# Dynamic Macros: Record and Replay Macros in Runtime

QMK supports temporary macros created on the fly. We call these Dynamic Macros. They are defined by the user from the keyboard and are lost when the keyboard is unplugged or otherwise rebooted.

You can store one or two macros and they may have a combined total of 128 keypresses. You can increase this size at the cost of RAM.

To enable them, first include `DYNAMIC_MACRO_ENABLE = yes` in your `rules.mk`. Then, add the following keys to your keymap:

|Key                              |Alias    |Description                                       |
|---------------------------------|---------|--------------------------------------------------|
|`QK_DYNAMIC_MACRO_RECORD_START_1`|`DM_REC1`|Start recording Macro 1                           |
|`QK_DYNAMIC_MACRO_RECORD_START_2`|`DM_REC2`|Start recording Macro 2                           |
|`QK_DYNAMIC_MACRO_PLAY_1`        |`DM_PLY1`|Replay Macro 1                                    |
|`QK_DYNAMIC_MACRO_PLAY_2`        |`DM_PLY2`|Replay Macro 2                                    |
|`QK_DYNAMIC_MACRO_RECORD_STOP`   |`DM_RSTP`|Finish the macro that is currently being recorded.|

That should be everything necessary. 

To start recording the macro, press either `DM_REC1` or `DM_REC2`. 

To finish the recording, press the `DM_RSTP` layer button. You can also press `DM_REC1` or `DM_REC2` again to stop the recording.

To replay the macro, press either `DM_PLY1` or `DM_PLY2`.

It is possible to replay a macro as part of a macro. It's ok to replay macro 2 while recording macro 1 and vice versa but never create recursive macros i.e. macro 1 that replays macro 1. If you do so and the keyboard will get unresponsive, unplug the keyboard and plug it again.  You can disable this completely by defining `DYNAMIC_MACRO_NO_NESTING`  in your `config.h` file.

?> For the details about the internals of the dynamic macros, please read the comments in the `process_dynamic_macro.h` and `process_dynamic_macro.c` files.

## Customization 

There are a number of options added that should allow some additional degree of customization

|Define                      |Default         |Description                                                                                                      |
|----------------------------|----------------|-----------------------------------------------------------------------------------------------------------------|
|`DYNAMIC_MACRO_SIZE`        |128             |Sets the amount of memory that Dynamic Macros can use. This is a limited resource, dependent on the controller.  |
|`DYNAMIC_MACRO_USER_CALL`   |*Not defined*   |Defining this falls back to using the user `keymap.c` file to trigger the macro behavior.                        |
|`DYNAMIC_MACRO_NO_NESTING`  |*Not Defined*   |Defining this disables the ability to call a macro from another macro (nested macros).                           | 
|`DYNAMIC_MACRO_DELAY`        |*Not Defined*   |Sets the waiting time (ms unit) when sending each key.                                                           |


If the LEDs start blinking during the recording with each keypress, it means there is no more space for the macro in the macro buffer. To fit the macro in, either make the other macro shorter (they share the same buffer) or increase the buffer size by adding the `DYNAMIC_MACRO_SIZE` define in your `config.h` (default value: 128; please read the comments for it in the header).


### DYNAMIC_MACRO_USER_CALL

For users of the earlier versions of dynamic macros: It is still possible to finish the macro recording using just the layer modifier used to access the dynamic macro keys, without a dedicated `DM_RSTP` key. If you want this behavior back, add `#define DYNAMIC_MACRO_USER_CALL` to your `config.h` and insert the following snippet at the beginning of your `process_record_user()` function:

```c
	uint16_t macro_kc = (keycode == MO(_DYN) ? DM_RSTP : keycode);

	if (!process_record_dynamic_macro(macro_kc, record)) {
		return false;
	}
```

### User Hooks

There are a number of hooks that you can use to add custom functionality and feedback options to Dynamic Macro feature.  This allows for some additional degree of customization. 

Note, that direction indicates which macro it is, with `1` being Macro 1, `-1` being Macro 2, and 0 being no macro. 

* `dynamic_macro_record_start_user(int8_t direction)` - Triggered when you start recording a macro.
* `dynamic_macro_play_user(int8_t direction)` - Triggered when you play back a macro.
* `dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record)` - Triggered on each keypress while recording a macro.
* `dynamic_macro_record_end_user(int8_t direction)` - Triggered when the macro recording is stopped. 

Additionally, you can call `dynamic_macro_led_blink()` to flash the backlights if that feature is enabled. 

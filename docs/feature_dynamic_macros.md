# Dynamic Macros: Record and Replay Macros in Runtime

QMK supports temporary macros created on the fly. We call these Dynamic Macros. They are defined by the user from the keyboard and are lost when the keyboard is unplugged or otherwise rebooted.

You can store one or two dynamic macros and they may have a combined total of 64 key strokes (i.e., 128 key press or release events). You can increase this size at the cost of RAM, see [`DYNAMIC_MACRO_SIZE` below](#customization).

To enable them, first include `DYNAMIC_MACRO_ENABLE = yes` in your `rules.mk`. Then, add the following keys to your keymap:

|Key               |Alias     |Description                                        |
|------------------|----------|---------------------------------------------------|
|`DYN_REC_START1`  |`DM_REC1` |Start recording Macro 1 (or stop recording)        |
|`DYN_REC_START2`  |`DM_REC2` |Start recording Macro 2 (or stop recording)        |
|`DYN_MACRO_PLAY1` |`DM_PLY1` |Replay Macro 1                                     |
|`DYN_MACRO_PLAY2` |`DM_PLY2` |Replay Macro 2                                     |
|`DYN_REC_STOP`    |`DM_RSTP` |Finish the macro that is currently being recorded. |

That should be everything necessary.

To start recording the macro, press either `DYN_REC_START1` or `DYN_REC_START2`. The keyboard will then go to layer 0, even if you're holding a [momentary layer switch key](feature_layers.md#switching-and-toggling-layers). Recording will start with the next key press event (i.e, key down). Any keys released before that first key press, including momentary layer switch keys, are completely ignored.

To finish the recording, press the `DYN_REC_STOP` button. You can also press `DYN_REC_START1` or `DYN_REC_START2` again to stop the recording (both will act identically to `DYN_REC_STOP`).

To replay the macro, press the corresponding play key: `DYN_MACRO_PLAY1` or `DYN_MACRO_PLAY2`. After the macro is finished playing, the keyboard will be returned to the layer state that was active when the play key was released.

To clear a macro, start recording then immediately finish it (e.g., hit `DYN_REC_START1` twice).

!> Use caution when using [momentary layer switch keys](feature_layers.md#switching-and-toggling-layers) to access your Dynamic Macro keys, e.g., `MO`, `LM`, `LT`, or `TT`. When starting recording: release all keys before typing in the macro. When playing a macro: keep any momentary keys held until the macro is finished playing.

It is possible to replay a macro as part of a macro. It's ok to replay macro 2 while recording macro 1 and vice versa but never create recursive macros i.e. macro 1 that replays macro 1. If you do so and the keyboard will get unresponsive, unplug the keyboard and plug it again.  You can disable this completely by defining `DYNAMIC_MACRO_NO_NESTING`  in your `config.h` file.

?> For the details about the internals of the dynamic macros, please read the comments in the `process_dynamic_macro.h` and `process_dynamic_macro.c` files.

## Customization :id=customization

There are a number of options added that should allow some additional degree of customization

|Define                      |Default         |Description                                                                                                                      |
|----------------------------|----------------|---------------------------------------------------------------------------------------------------------------------------------|
|`DYNAMIC_MACRO_SIZE`        |128             |The number of events Dynamic Macros can store. This affects RAM usage, which is a limited resource, dependent on the controller. |
|`DYNAMIC_MACRO_USER_CALL`   |*Not defined*   |Defining this falls back to using the user `keymap.c` file to trigger the macro behavior.                                        |
|`DYNAMIC_MACRO_NO_NESTING`  |*Not Defined*   |Defining this disables the ability to call a macro from another macro (nested macros).                                           |

If the LEDs start blinking during the recording with each keypress, it means there is no more space for the macro in the macro buffer. To fit the macro in, either make the other macro shorter (they share the same buffer) or increase the buffer size by adding the `DYNAMIC_MACRO_SIZE` define in your `config.h`. The default value is 128 events (key presses and releases); please read the comments for it in the header.

### DYNAMIC_MACRO_USER_CALL

For users of the earlier versions of dynamic macros: It is still possible to finish the macro recording using just the layer modifier used to access the dynamic macro keys, without a dedicated `DYN_REC_STOP` key. If you want this behavior back, add `#define DYNAMIC_MACRO_USER_CALL` to your `config.h` and insert the following snippet at the beginning of your `process_record_user()` function:

```c
	uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);

	if (!process_record_dynamic_macro(macro_kc, record)) {
		return false;
	}
```

### User Hooks

There are a number of hooks that you can use to add custom functionality and feedback options to Dynamic Macro feature.  This allows for some additional degree of customization.

Note, that direction indicates which macro it is, with `1` being Macro 1, `-1` being Macro 2, and 0 being no macro.

* `dynamic_macro_record_start_user(void)` - Triggered when you start recording a macro.
* `dynamic_macro_play_user(int8_t direction)` - Triggered when you play back a macro.
* `dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record)` - Triggered on each keypress while recording a macro.
* `dynamic_macro_record_end_user(int8_t direction)` - Triggered when the macro recording is stopped.

Additionally, you can call `dynamic_macro_led_blink()` to flash the backlights if that feature is enabled.

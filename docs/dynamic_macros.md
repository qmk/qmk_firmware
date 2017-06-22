# Dynamic macros: record and replay macros in runtime

QMK supports temporarily macros created on the fly. We call these Dynamic Macros. They are defined by the user from the keyboard and are lost when the keyboard is unplugged or otherwise rebooted.

You can store one or two macros and they may have a combined total of 128 keypresses. You can increase this size at the cost of RAM.

To enable them, first add a new element to the `planck_keycodes` enum — `DYNAMIC_MACRO_RANGE`:

```c
enum planck_keycodes {
	QWERTY = SAFE_RANGE,
	COLEMAK,
	DVORAK,
	PLOVER,
	LOWER,
	RAISE,
	BACKLIT,
	EXT_PLV,
	DYNAMIC_MACRO_RANGE,
};
```

It must be the last element because `dynamic_macros.h` will add some more keycodes after it.

Below it include the `dynamic_macro.h` header:

```c
	#include "dynamic_macro.h"`
```

Add the following keys to your keymap:

* `DYN_REC_START1` — start recording the macro 1,
* `DYN_REC_START2` — start recording the macro 2,
* `DYN_MACRO_PLAY1` — replay the macro 1,
* `DYN_MACRO_PLAY2` — replay the macro 2,
* `DYN_REC_STOP` — finish the macro that is currently being recorded.

Add the following code to the very beginning of your `process_record_user()` function:

```c
	if (!process_record_dynamic_macro(keycode, record)) {
		return false;
	}
```

That should be everything necessary. To start recording the macro, press either `DYN_REC_START1` or `DYN_REC_START2`. To finish the recording, press the `DYN_REC_STOP` layer button. To replay the macro, press either `DYN_MACRO_PLAY1` or `DYN_MACRO_PLAY2`.

Note that it's possible to replay a macro as part of a macro. It's ok to replay macro 2 while recording macro 1 and vice versa but never create recursive macros i.e. macro 1 that replays macro 1. If you do so and the keyboard will get unresponsive, unplug the keyboard and plug it again.

For users of the earlier versions of dynamic macros: It is still possible to finish the macro recording using just the layer modifier used to access the dynamic macro keys, without a dedicated `DYN_REC_STOP` key. If you want this behavior back, use the following snippet instead of the one above:

```c
	uint16_t macro_kc = (keycode == MO(_DYN) ? DYN_REC_STOP : keycode);
	
	if (!process_record_dynamic_macro(macro_kc, record)) {
		return false;
	}
```

If the LED's start blinking during the recording with each keypress, it means there is no more space for the macro in the macro buffer. To fit the macro in, either make the other macro shorter (they share the same buffer) or increase the buffer size by setting the `DYNAMIC_MACRO_SIZE` preprocessor macro (default value: 128; please read the comments for it in the header).

For the details about the internals of the dynamic macros, please read the comments in the `dynamic_macro.h` header.

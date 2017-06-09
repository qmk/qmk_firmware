# Macros - Send multiple keystrokes when pressing just one key

QMK has a number of ways to define and use macros. These can do anything you want- type common phrases for you, copypasta, repetitive game movements, or even help you code. 

**Security Note**: While it is possible to use macros to send passwords, credit card numbers, and other sensitive information it is a supremely bad idea to do so. Anyone who gets ahold of your keyboard will be able to access that information by opening a text editor.

# Macro Definitions

By default QMK assumes you don't have any macros. To define your macros you create an `action_get_macro()` function. For example:

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch(id) {
			case 0:
				return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
			case 1:
				return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
		}
	}
	return MACRO_NONE;
};
```

This defines two macros which will be run when the key they are assigned to is pressed. If you'd like them to run when the release is released instead you can change the if statement:

```c
	if (!record->event.pressed) {
```

## Macro Commands

A macro can include the following commands:

* I() change interval of stroke in milliseconds.
* D() press key.
* U() release key.
* T() type key(press and release).
* W() wait (milliseconds).
* END end mark.

## Sending strings

Sometimes you just want a key to type out words or phrases. For the most common situations we've provided `SEND_STRING()`, which will type out your string for you instead of having to build a `MACRO()`. Right now it assumes a US keymap with a QWERTY layout, so if you are using something else it may not behave as you expect.

For example:

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch(id) {
			case 0:
				SEND_STRING("QMK is the best thing ever!");
				return false;
		}
	}
	return MACRO_NONE;
};
```

## Mapping a Macro to a key

Use the `M()` function within your `KEYMAP()` to call a macro. For example, here is the keymap for a 2-key keyboard:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = KEYMAP(
		M(0), M(1)
	),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch(id) {
			case 0:
				return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
			case 1:
				return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
		}
	}
	return MACRO_NONE;
};
```

When you press the key on the left it will type "Hi!" and when you press the key on the right it will type "Bye!".

## Naming your macros

If you have a bunch of macros you want to refer to from your keymap while keeping the keymap easily readable you can name them using `#define` at the top of your file.

```c
#define M_HI M(0)
#define M_BYE M(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = KEYMAP(
		M_HI, M_BYE
	),
};
```

# Advanced macro functions

While working within the `action_get_macro()` function block there are some functions you may find useful. Keep in mind that while you can write some fairly advanced code within a macro if your functionality gets too complex you may want to define a custom keycode instead. Macros are meant to be simple.

#### `record->event.pressed`

This is a boolean value that can be tested to see if the switch is being pressed or released. An example of this is

```c
	if (record->event.pressed) {
		// on keydown
	} else {
		// on keyup
	}
```

#### `register_code(<kc>);`

This sends the `<kc>` keydown event to the computer. Some examples would be `KC_ESC`, `KC_C`, `KC_4`, and even modifiers such as `KC_LSFT` and `KC_LGUI`.

#### `unregister_code(<kc>);`

Parallel to `register_code` function, this sends the `<kc>` keyup event to the computer. If you don't use this, the key will be held down until it's sent.

#### `clear_keyboard();`

This will clear all mods and keys currently pressed.

#### `clear_mods();`

This will clear all mods currently pressed.

#### `clear_keyboard_but_mods();`

This will clear all keys besides the mods currently pressed.

# Advanced Example: Single-key copy/paste (hold to copy, tap to paste)

This example defines a macro which sends `Ctrl-C` when pressed down, and `Ctrl-V` when released. 

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	switch(id) {
		case 0: {
			if (record->event.pressed) {
				return MACRO( D(LCTL), T(C), U(LCTL), END  );
			} else {
				return MACRO( D(LCTL), T(V), U(LCTL), END  );
			}
			break;
		}
	}
	return MACRO_NONE;
};
```



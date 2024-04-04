# Modifications you can (want) to control :D


## CAPS_LOCK status indicator

```c
#define CAPS_LOCK_LED_SIDE      true
#define CAPS_LOCK_LED_KEY       false
```

So first one enables or disables top left LED to be CAPS_LOCK status indicator, and second one enables or disables CAPS_LOCK key to be CAPS_LOCK status indicator.

You can enable or disable both, or just one of them.

If none is enabled, CAPS_LOCK status will be not indicated at all.


## Enable/disable USB sleep

Use toggle on `FN + Backspace` to enable or disable USB sleep.


## Key bind to toggle usb sleep on the fly

In via with new definition file you can bind TOG_USB_SLEEP to any key you want to toggle USB sleep on the fly.

When you press that key, USB sleep will be toggled on or off.

Top-left LED will indicate USB sleep status.

GREEN - USB sleep is enabled
RED - USB sleep is disabled

## Keybinds guide


Here is a [list](gem80-guide.md) of keybinds that you can use to control your keyboard.

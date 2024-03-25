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


```c
#define USB_SLEEP_ENABLED      true
```


If you want to enable USB sleep, set it to true. If you want to disable USB sleep, set it to false.

Default is false (from now on).

## Key bind to toggle usb sleep on the fly

In via with new definition file you can bind TOG_USB_SLEEP to any key you want to toggle USB sleep on the fly.

When you press that key, USB sleep will be toggled on or off.

Top-left LED will indicate USB sleep status.

GREEN - USB sleep is enabled
RED - USB sleep is disabled

## Autocorrection

This feature enabled by default, and it will autocorrect some common mistakes like "teh" to "the" or "dont" to "don't".

Dictionary is located in `nuphy/gem80/ansi/dict.txt` file.

To re-generate header file ater dictionary changes run `qmk generate-autocorrect-data keyboards/nuphy/gem80/ansi/dict.txt` command. (I hope that default keyboard and keymap are set to gem80), otherwise use appropriate -kb -km values.

If you want to disable this feature, set `AUTOCORRECT_ENABLE = no` in `nuphy/gem80/ansu/rules.mk` file.


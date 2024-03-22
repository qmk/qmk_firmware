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

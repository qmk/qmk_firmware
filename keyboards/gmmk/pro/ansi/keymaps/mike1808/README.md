QMK layout for gmmk/pro
=======================

## Secrets
The format is the same as [drashna's](../../../../users/drashna/readme_secrets.md) secrets implementation. Create a `secret.h` and define your secrets like this:

```c
static const char* secrets[] = {"secret1", "secret2", "secret3", "secret4", "secret5"};
```

## Rotary encoder knob
You can hookup your encoder functions by defining new encoder states in [encoder.h](./encoder.h), then in [encoder.c](./encoder.c) assign static variable `state` your new state depending on your desired condition and add callbacks to `encoder_mapping` array. 

## RGB Matrix Ledmaps
RGB Matrix ledmaps is the future allowing you assign colors to individual keys on every keymap layer. 

You can see some examples of my usage in the bottom of [keymap.c](./keymap.c).

Color defines are just HSV colors wrapped in curly braces, like `#define RED { HSV_RED }`.

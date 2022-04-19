# QMK Apple Fn Key

This patch adds support for the Apple Fn key, which unlike most keyboards with Fn keys, is actually sent over the wire. It works by repurposing the reserved byte in the keyboard report to represent [the `KeyboardFn` usage of the `AppleVendor Top Case` usage page](https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-1035.70.7/IOHIDFamily/AppleHIDUsageTables.h.auto.html). When the Fn key is pressed, the value of this byte becomes `1`.

To apply this patch, download the below file, `cd` to your `qmk_firmware` repository in your preferred terminal, and run `git apply /path/to/applefn.patch`. Then, add the `KC_APPLE_FN` (or `KC_APFN` for short) keycode to your keymap.

There are a couple of caveats to this implementation that are important to be aware of. Firstly, it is not compatible with NKRO, as QMK's NKRO report format has no reserved byte - it is part of the 6KRO report for compatibility with the HID [boot protocol](https://deskthority.net/wiki/USB#Keyboard_Boot_Protocol). Thus you must set `NKRO_ENABLE = no` in your keymap's `rules.mk`.
You will also need to redefine the USB Vendor and Product IDs in your keymap's `config.h` to that of a genuine Apple keyboard* in order for macOS to recognise the Fn key:
```c
#undef VENDOR_ID
#define VENDOR_ID 0x05AC
#undef PRODUCT_ID
#define PRODUCT_ID <pid>
```

This is the primary reason this patch has not been integrated into upstream QMK - Apple would probably not be too happy about others using their vendor ID, and a feature that relies on the VID/PID pair being set to a specific value is not particularly ideal anyway.

See https://github.com/qmk/qmk_firmware/issues/2179 for a little more info and discussion.

<sup>\* It appears that the functionality of certain F keys can differ depending on the PID, likely because they have evolved over time on real Apple keyboards.</sup>


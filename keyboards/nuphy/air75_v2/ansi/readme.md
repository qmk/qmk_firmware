# NuPhy Air75 V2

The NuPhy Air75 V2 is an 84-key ANSI keyboard with USB, 2.4 GHz RF, and
Bluetooth connectivity.

![NuPhy Air75 V2](https://i.imgur.com/R7jS2JC.jpeg)

* Keyboard Maintainer: [nuphy](https://github.com/nuphy-src)
* Hardware Supported: NuPhy Air75 V2 PCB
* Hardware Availability: [NuPhy Air75 V2](https://nuphy.com/products/air75-v2)

## Keymaps

The `default` keymap is a minimal QMK keymap with a standard base layer and
an Fn layer.

The `nuphy` keymap preserves the original NuPhy layout and controls:

* Mac and Windows base layers, selected with the keyboard's layout switch.
* Bluetooth profiles 1–3 and 2.4 GHz RF controls.
* Mac Globe behavior: tap the Mac Fn key to send Globe; hold it to access the
  Mac Fn layer.
* Backlight controls on the Fn arrow cluster:
  * Up/Down: brightness up/down.
  * Left: next effect.
  * Right: next hue/color.
  * Comma/Period: speed down/up.
* Sidelight controls while holding Fn+M, using the same arrow and
  Comma/Period arrangement.

The `nuphy` keymap is the recommended keymap for the complete NuPhy feature
set. Its vendor-specific RF and sidelight controls are implemented by the
keyboard target and are available over USB, RF, and Bluetooth as supported by
the hardware connection.

## Build and flash

After setting up the [QMK build environment](https://docs.qmk.fm/#/getting_started_build_tools),
build the minimal keymap with:

    qmk compile -kb nuphy/air75_v2/ansi -km default

Build the full NuPhy keymap with:

    qmk compile -kb nuphy/air75_v2/ansi -km nuphy

The generated firmware file is copied to the QMK firmware root. To flash
using QMK CLI:

    qmk flash -kb nuphy/air75_v2/ansi -km nuphy

Use the [QMK make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for additional build options.

## Bootloader

The keyboard can enter the bootloader using either method:

* **Bootmagic reset:** Hold the key at matrix position `(0,0)` (normally
  Escape) while connecting the keyboard.
* **Physical reset:** Use the reset procedure specified for the Air75 V2 PCB.

When flashing, use a wired USB connection and do not disconnect the keyboard
until the flash operation has completed.

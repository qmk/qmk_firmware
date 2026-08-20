# Metakey Tenet 70

![Metakey Tenet 70](https://clickclack.io/cdn/shop/files/blackside.jpg?v=1649246960&width=1080)

A transformable (regular / southpaw) 70% keyboard with a 256x32 OLED and
per-key RGB lighting.

* Keyboard Maintainer: [connorgallopo](https://github.com/connorgallopo)
* Hardware Supported: Metakey Tenet 70 (Holtek HT32F52352)
* Hardware Availability: [clickclack.io](https://clickclack.io/pages/metakey-tenet)

## How to compile

After setting up your build environment, you can compile the default keymap
using:

    make metakey/tenet:default

## Installing

The Tenet 70 uses the stock Hexcore IAP bootloader, flashed with `hexcore_flash`
from [Tenet70-Tools](https://github.com/connorgallopo/Tenet70-Tools) — a fork of
[AnnePro2-Tools](https://github.com/OpenAnnePro/AnnePro2-Tools).

1. Build the tool: clone [Tenet70-Tools](https://github.com/connorgallopo/Tenet70-Tools)
   and run `cargo build --release`. The binary is `./target/release/hexcore_flash`.
2. Put the keyboard into IAP mode by unplugging it, then holding `Esc` while
   plugging it back in.
3. Flash the firmware you built (substitute the correct `.bin` if you built a
   different keymap):

       hexcore_flash --device tenet-70 metakey_tenet_default.bin

`QK_BOOT` (Fn + Esc in the default keymap) also re-enters IAP mode from within QMK.

## Recovery

If a bad build leaves the board unresponsive, the SWD pads at PA13/PA14 allow
re-flashing with an ST-Link or J-Link.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# TEX Shura

![TEX Shura](https://cdn.shopify.com/s/files/1/0052/5814/9978/products/52809163204_68662770a3_k.jpg?v=1681308309)

A compact keyboard with a TrackPoint and three mouse buttons below the spacebar. TEX sells ANSI,
ISO, JIS and hot-swap variants with several split-key options.

* Keyboard Maintainer: [trapexit](https://github.com/trapexit)
* Hardware Supported: TEX Shura PCB (Holtek HT32F52352), with or without a TEX BLE5 or BLE4 add-on board
* Hardware Availability: [TEX](https://tex.com.tw/products/shura)

## Build

After [setting up QMK](https://docs.qmk.fm/newbs), choose the keymap for your physical layout:

    qmk compile -kb tex/shura -km default_ansi
    qmk compile -kb tex/shura -km default_iso
    qmk compile -kb tex/shura -km default_jis

For a DIY board with split or mixed key positions, `default` includes the optional switches
and uses ANSI Enter and backslash:

    qmk compile -kb tex/shura -km default

Build for the Bluetooth module you have: BLE5 is the default. For BLE4, add
`-e SHURA_BLE_MODULE=ble4` to the compile command; for USB only, add `-e BLUETOOTH_ENABLE=no`.
USB and BLE4 were exercised on one Shura. BLE5 and battery reporting have not been hardware-tested
by the maintainer. On BLE4 the Caps Lock LED does not follow the host.

## Flash over USB

On Linux, install [tex-flash](https://github.com/trapexit/tex-flash#install) on your `PATH`
and configure USB access for your normal user. Get the original Shura 0.18 updater from
[TEX Downloads](https://tex.com.tw/pages/download); tex-flash reads it without running it.
Export your VIA layout or other settings you want to keep. The backup below contains device
metadata, not your settings or a full firmware image.

Connect only the intended Shura by USB, close VIA and unmount any stock configuration disk.
Flashing starts **without a confirmation prompt**. Use a stable USB connection: an interrupted
erase or write can leave the keyboard unable to type.

From supported QMK or the TEX bootloader, run this in the QMK firmware root. Choose a new
backup filename in an existing writable directory for each flash; tex-flash will not overwrite it.

```sh
export TEX_FLASH_UPDATER="$HOME/Downloads/AP_0532_0.18_20230914.exe"
export TEX_FLASH_BACKUP="$HOME/shura-before-update-01.backup.json"
make tex/shura:default:flash
```

Replace `default` with your keymap. Make passes its generated `.bin` and matching unstripped
`.elf` to tex-flash. If QMK has no supported raw HID interface, enter the [bootloader](#bootloader)
first.

You can also build without flashing (`make tex/shura:default`) and use tex-flash directly.
The first command below only checks the files; it does not access USB. The second flashes a
board **running stock firmware**: replace `YOUR_USB_SERIAL` with its exact USB `iSerial`
(see `lsusb -v -d 04d9:0532`), including leading zeroes. From QMK or the bootloader, omit
`--serial`. Use the files from the keymap you actually built.

```sh
tex-flash check --model shura --updater "$TEX_FLASH_UPDATER" \
    --bin .build/tex_shura_default.bin --elf .build/tex_shura_default.elf
tex-flash flash --model shura --updater "$TEX_FLASH_UPDATER" --serial 'YOUR_USB_SERIAL' \
    --bin .build/tex_shura_default.bin --elf .build/tex_shura_default.elf --backup "$TEX_FLASH_BACKUP"
```

On the last live Shura flash, tex-flash verified the image and metadata, then reported `ENODEV`
while checking for the application to return. Linux subsequently enumerated the keyboard and VIA
worked. If you get that **post-verification** error, check `lsusb` for `04d9:0532` and test the
keyboard; do not reflash solely because return detection failed.

## Bootloader

From QMK, enter the TEX bootloader (USB `04D9:1532`) using one of these methods:

* **Bootmagic reset:** Hold Escape while plugging in the keyboard. **This resets QMK EEPROM**, including saved VIA keymaps on VIA-enabled builds. Export any remaps you want to keep first.
* **Keycode in layout:** Press `QK_BOOT` if you have mapped it.
* **From the host:** On builds with a supported raw HID interface, tex-flash can ask QMK to restart into the bootloader.

All three methods require a working QMK application. No physical procedure has been verified here
for entering the TEX bootloader when the application cannot start. If the bootloader still
enumerates after an interrupted flash, follow the tool's [interrupted-flash instructions](https://github.com/trapexit/tex-flash#interrupted-flash).
The tool cannot restore a damaged bootloader: its backup contains metadata and the stock updater
contains the application, not a full-device image.

## Default controls

The default keymaps follow the factory Fn1 layout. In place of the stock middle-button layer,
holding middle gives the same Fn1 bindings as dedicated Fn. Both use remappable board
keycodes rather than `MO(1)` so releasing either control does not cancel the other's hold.

* The dedicated Fn keys (`SHURA_FN1`) hold layer 1. Pressing the middle mouse button
  (`SHURA_MIDDLE`) activates that same layer immediately. Move the TrackPoint while holding
  middle to scroll, or press another key for its Fn action. Release middle without either
  action for a middle click. `SHURA_FN2` and `SHURA_FN3` are available for custom keymaps.
* DIP switches 1-3 select a profile for custom keymaps; 4 lets the dedicated Fn1 key scroll
  the TrackPoint; 5 reverses vertical scrolling. DIP 6 does not expose the stock configuration disk.
* With a Bluetooth module, `BAT_REPORT` types a battery report and the physical Pair switch
  sends `BLE_PAIR`. Additional board keycodes let custom keymaps select hosts, adjust TrackPoint
  sensitivity and vertical speed, or set the battery sleep time.
* QMK stores settings in SPI flash sectors separate from the stock profile and configuration disk.

Custom keymaps can intercept Fn or middle in `process_record_user()`; return `false` on **both**
press and release to replace a hold. For TrackPoint customization, use QMK's
[pointing-device hooks](https://docs.qmk.fm/features/pointing_device): `pointing_device_init_user()`
for setup and `pointing_device_task_user(report)` to adjust the final motion or scrolling report.

## Pair or switch hosts with BLE4

Hold the physical Pair switch (`BLE_PAIR`) for three seconds to pair the current slot, then release
it. Select `TEX-BLE-KB-N` on the host (`N` is the slot number). If prompted, type the passkey on
the keyboard's number row and press Enter.

`BLE_SLOT1`, `BLE_SLOT2` and `BLE_SLOT3` are **not bound by default**. To select a particular
slot, map its keycode in your keymap. Tap it to connect to an existing pairing, or hold it for
three seconds to pair a new host in that slot. Release any layer key before typing a passkey.

Adapted from [Mauro DiBenedetto's TEX Shinobi port](https://github.com/cyclistmass/tex-qmk/tree/bf4a40841d3b3ecd226fc2e0ebb09cdc67b1c7da/shinobi).

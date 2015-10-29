Quantum MK Firmware
================================
This is a keyboard firmware based on the [tmk_keyboard firmware](http://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR controller, and more specifically, the OLKB product line.


### Getting started

You can create your own Quantum-based project by using `./new_project.sh <project_name>`, which will create `/keyboard/<project_name>` with all the necessary components for a Quantum project.

You have access to a bunch of goodies! Check out the Makefile to enable/disable some of the features. Uncomment the `#` to enable them. Setting them to `no` does nothing and will only confuse future you.

    BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
    MIDI_ENABLE = yes      # MIDI controls
    # UNICODE_ENABLE = yes # Unicode support
    BLUETOOTH_ENABLE = yes # Enable Bluetooth with the Adafruit EZ-Key HID

### Mod shortcuts

* `LSFT(kc)` - applies left shift to *kc* - `S(kc)` is an alias
* `RSFT(kc)` - applies right shift to *kc*
* `LCTL(kc)` - applies left control to *kc*
* `RCTL(kc)` - applies right control to *kc*
* `LALT(kc)` - applies left alt to *kc*
* `RALT(kc)` - applies right alt to *kc*
* `LGUI(kc)` - applies left gui (command/win) to *kc*
* `RGUI(kc)` - applies right gui (command/win) to *kc*

You can also use more than one, like this:

    LALT(LGUI(KC_ESC))

The following shortcuts automatically add `LSFT()` to keycodes to get commonly used symbols. Their long names (see `quantum/keymap_common.h`) are also availble.

    KC_TILD  ~
    KC_EXLM  !
    KC_AT    @
    KC_HASH  #
    KC_DLR   $
    KC_PERC  %
    KC_CIRC  ^
    KC_AMPR  &
    KC_ASTR  *
    KC_LPRN  (
    KC_RPRN  )
    KC_UNDS  _
    KC_PLUS  +
    KC_LCBR  {
    KC_RCBR  }
    KC_PIPE  |
    KC_COLN  :

### Function shortcuts

Instead of using `FNx`, you can use `F(x)` - the benefit here is being able to use more than 32 function layers (up to 4096), if you happen to need them.

There are also keycode shortcuts for common actions:

* `MO(layer)` - momentary switch to *layer*
* `DF(layer)` - sets default layer to *layer*
* `TG(layer)` - toggle between the current layer and *layer*
* `MT(mod, kc)` - is *mod* when held, and *kc* when tapped
  * `CTL_T(kc)` - is LCTL when held and *kc* when tapped 
  * `SFT_T(kc)` - is LSFT when held and *kc* when tapped 
  * `ALT_T(kc)` - is LALT when held and *kc* when tapped 
  * `GUI_T(kc)` - is LGUI when held and *kc* when tapped 
  * `ALL_T(kc)` - is Hyper (all mods) when held and *kc* when tapped 
* `LT(layer, kc)` - momentary switch to *layer* when held, and *kc* when tapped

These functions work the same way that their `ACTION_*` functions do, and will require KC_TRNS on the layer being switched to - check out the default keymap for an example.

### Additional keycodes for software-implemented layouts (Colemak, Dvorak, etc)

Everything is assuming you're in Qwerty (in software) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

     #include "keymap_<layout>.h"
     
Where <layout> is "colemak" or "dvorak". After including this line, you will get access to:
 
 * `CM_*` for all of the Colemak-equivalent characters
 * `DV_*` for all of the Dvorak-equivalent characters
 
These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features. 

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F` - `KC_F` under these same circumstances would result in `T`.

### Additional language support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbrivation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware (but it's being worked on - see Unicode support).

### Unicode support

You can currently send 4 hex digits with your OS-specific modifier key (RALT for OSX with the "Unicode Hex Input" layout) - this is currently limited to supporting one OS at a time, and requires a recompile for switching. 8 digit hex codes are being worked on. The keycode function is `UC(n)`, where *n* is a 4 digit hexidecimal. Enable from the Makefile.

### Macro shortcuts

Instead of using the `ACTION_MACRO` function, you can simply use `M(n)` to access macro *n* - *n* will get passed into the `action_get_macro` as the `id`, and you can use a switch statement to filter them. This gets called on the keydown and keyup, so you'll need to use an if statement testing `record->event.pressed` (see keymap_default.c).

### Other keyboard shortcut keycodes

* `RESET` - puts the MCU in DFU mode for flashing new firmware (with `make dfu`)
* `DEBUG` - the firmware into debug mode - you'll need hid_listen to see things
* `BL_ON` - turns the backlight on
* `BL_OFF` - turns the backlight off
* `BL_<n>` - sets the backlight to level *n*
* `BL_INC` - increments the backlight level by one
* `BL_DEC` - decrements the backlight level by one
* `BL_TOGG` - toggles the backlight
* `BL_STEP` - steps through the backlight levels

Enable the backlight from the Makefile.


### MIDI functionalty

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.

### Bluetooth functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

# TMK Documenation

Features
--------
These features can be used in your keyboard.

* Multi-layer Keymap  - Multiple keyboard layouts with layer switching
* Mouse key           - Mouse control with keyboard
* System Control Key  - Power Down, Sleep, Wake Up and USB Remote Wake up
* Media Control Key   - Volume Down/Up, Mute, Next/Prev track, Play, Stop and etc
* USB NKRO            - 120 keys(+ 8 modifiers) simultaneously
* PS/2 mouse support  - PS/2 mouse(TrackPoint) as composite device
* Keyboard protocols  - PS/2, ADB, M0110, Sun and other old keyboard protocols
* User Function       - Customizable function of key with writing code
* Macro               - Very primitive at this time
* Keyboard Tricks     - Oneshot modifier and modifier with tapping feature
* Debug Console       - Messages for debug and interaction with firmware
* Virtual DIP Switch  - Configurations stored EEPROM(Boot Magic)
* Locking CapsLock    - Mechanical switch support for CapsLock
* Breathing Sleep LED - Sleep indicator with charm during USB suspend
* Backlight           - Control backlight levels



Projects
--------
You can find some keyboard specific projects under `converter` and `keyboard` directory.

## Main projects

### OLKB products
* [planck](keyboard/planck/)                - [Planck] Ortholinear 40% keyboard
* [preonic](keyboard/preonic/)              - [Preonic] Ortholinear 50% keyboard
* [atomic](keyboard/atomic/)                - [Atomic] Ortholinear 60% keyboard

### Ergodox EZ
* [ergodox_ez](keyboard/ergodox_ez)         - [Ergodox_EZ] Assembled split keyboard

## Other projects

### converter
* [ps2_usb](converter/ps2_usb/)             - [PS/2 keyboard to USB][GH_ps2]
* [adb_usb](converter/adb_usb/)             - [ADB keyboard to USB][GH_adb]
* [m0110_usb](converter/m0110_usb)          - [Macintosh 128K/512K/Plus keyboard to USB][GH_m0110]
* [terminal_usb](converter/terminal_usb/)   - [IBM Model M terminal keyboard(PS/2 scancode set3) to USB][GH_terminal]
* [news_usb](converter/news_usb/)           - [Sony NEWS keyboard to USB][GH_news]
* [x68k_usb](converter/x68k_usb/)           - [Sharp X68000 keyboard to USB][GH_x68k]
* [sun_usb](converter/sun_usb/)             - [Sun] to USB(type4, 5 and 3?)
* [pc98_usb](converter/pc98_usb/)           - [PC98] to USB
* [usb_usb](converter/usb_usb/)             - USB to USB(experimental)
* [ascii_usb](converter/ascii_usb/)         - ASCII(Serial console terminal) to USB
* [ibm4704_usb](converter/ibm4704_usb)      - [IBM 4704 keyboard Converter][GH_ibm4704]

### keyboard
* [hhkb](keyboard/hhkb/)                    - [Happy Hacking Keyboard pro][GH_hhkb] hasu's main board
* [gh60](keyboard/gh60/)                    - [GH60] DIY 60% keyboard [prototype][GH60_proto] hasu's second board
* [hbkb](keyboard/hbkb/)                    - [Happy Buckling spring keyboard][GH_hbkb](IBM Model M 60% mod)
* [hid_liber](keyboard/hid_liber/)          - [HID liberation][HID_liber] controller (by alaricljs)
* [phantom](keyboard/phantom/)              - [Phantom] keyboard (by Tranquilite)
* [IIgs_Standard](keyboard/IIgs/)           - Apple [IIGS] keyboard mod(by JeffreySung)
* [macway](keyboard/macway/)                - [Compact keyboard mod][GH_macway] [retired]
* [KMAC](keyboard/kmac/)                    - Korean custom keyboard
* [Lightsaber](keyboard/lightsaber/)        - Korean custom keyboard
* [Infinity](keyboard/infinity/)            - Massdrop [Infinity keyboard][Infinity]
* [NerD](keyboard/nerd/)                    - Korean custom keyboard
* [KittenPaw](keyboard/kitten_paw)          - Custom Majestouch controller
* [Lightpad](keyboard/lightpad)             - Korean custom keypad
* [ghost_squid](keyboard/ghost_squid/)      - [The Ghost Squid][ghost_squid] controller for [Cooler Master QuickFire XT][cmxt]

### Extenal projects using tmk_keyboard
* [ErgoDox_cub-uanic][cub-uanic]            - Split Ergonomic Keyboard [ErgoDox][ergodox_org]
* [mcdox][mcdox_tmk]                        - [mcdox][mcdox]


[GH_macway]:    http://geekhack.org/showwiki.php?title=Island:11930
[GH_hhkb]:      http://geekhack.org/showwiki.php?title=Island:12047
[GH_ps2]:       http://geekhack.org/showwiki.php?title=Island:14618
[GH_adb]:       http://geekhack.org/showwiki.php?title=Island:14290
[GH_hhkb_bt]:   http://geekhack.org/showwiki.php?title=Island:20851
[GH_m0110]:     http://geekhack.org/showwiki.php?title=Island:24965
[GH_news]:      http://geekhack.org/showwiki.php?title=Island:25759
[GH_terminal]:  http://geekhack.org/showwiki.php?title=Island:27272
[GH_x68k]:      http://geekhack.org/showwiki.php?title=Island:29060
[GH_hbkb]:      http://geekhack.org/showwiki.php?title=Island:29483
[GH_ibm4704]:   http://geekhack.org/index.php?topic=54706.0
[HID_liber]:    http://deskthority.net/wiki/HID_Liberation_Device_-_DIY_Instructions
[Phantom]:      http://geekhack.org/index.php?topic=26742
[GH60]:         http://geekhack.org/index.php?topic=34959
[GH60_proto]:   http://geekhack.org/index.php?topic=37570.0
[PC98]:         http://en.wikipedia.org/wiki/NEC_PC-9801
[Sun]:          http://en.wikipedia.org/wiki/Sun-3
[IIGS]:         http://en.wikipedia.org/wiki/Apple_IIGS
[Infinity]:     https://www.massdrop.com/buy/infinity-keyboard-kit
[ghost_squid]:  http://deskthority.net/wiki/Costar_replacement_controllers#The_Ghost_Squid
[cmxt]:         http://gaming.coolermaster.com/en/products/keyboards/quickfirext/
[ergodox_org]:  http://ergodox.org/
[cub-uanic]:    https://github.com/cub-uanic/tmk_keyboard/tree/master/keyboard/ergodox
[mcdox]:        https://github.com/DavidMcEwan/mcdox
[mcdox_tmk]:    https://github.com/DavidMcEwan/tmk_keyboard/tree/master/keyboard/mcdox
[Planck]:       http://olkb.co/planck
[Preonic]:      http://olkb.co/preonic
[Atomic]:       http://olkb.co/atomic
[Ergodox_EZ]:   https://www.indiegogo.com/projects/ergodox-ez-an-incredible-mechanical-keyboard


License
-------
**GPLv2** or later. Some protocol files are under **Modified BSD License**.

Third party libraries like LUFA, PJRC and V-USB have their own license respectively.



Build Firmware and Program Controller
-------------------------------------
See [doc/build.md](doc/build.md), or the README in the particular keyboard/* folder.



Change your keymap
------------------
See [doc/keymap.md](doc/keymap.md).



Magic Commands
--------------
To see help press `Magic` + `H`.

`Magic` key combination is `LShift` + `RShift` in many project, but `Power` key on ADB converter. 
`Magic` keybind can be vary on each project, check `config.h` in project directory.

Following commands can be also executed with `Magic` + key. In console mode `Magic` keybind is not needed.

    ----- Command Help -----
    c:      enter console mode
    d:      toggle debug enable
    x:      toggle matrix debug
    k:      toggle keyboard debug
    m:      toggle mouse debug
    v:      print device version & info
    t:      print timer count
    s:      print status
    e:	    print eeprom config
    n:	    toggle NKRO
    0/F10:  switch to Layer0
    1/F1:   switch to Layer1
    2/F2:   switch to Layer2
    3/F3:   switch to Layer3
    4/F4:   switch to Layer4
    PScr:   power down/remote wake-up
    Caps:   Lock Keyboard(Child Proof)
    Paus:   jump to bootloader



Boot Magic Configuration - Virtual DIP Switch
---------------------------------------------
Boot Magic are executed during boot up time. Press Magic key below then plug in keyboard cable.
Note that you must use keys of **Layer 0** as Magic keys. These settings are stored in EEPROM so that retain your configure over power cycles.

To avoid configuring accidentally additive salt key `KC_SPACE` also needs to be pressed along with the following configuration keys. The salt key is configurable in `config.h`. See [tmk_core/common/bootmagic.h](tmk_core/common/bootmagic.h).

#### General
- Skip reading EEPROM to start with default configuration(`ESC`)
- Clear configuration stored in EEPROM to reset configuration(`Backspace`)

#### Bootloader
- Kick up Bootloader(`B`)

#### Debug
- Debug enable(`D`)
- Debug matrix enable(`D`+`X`)
- Debug keyboard enable(`D`+`K`)
- Debug mouse enable(`D`+`M`)

#### Keymap
- Swap Control and CapsLock(`Left Control`)
- Change CapsLock to Control(`Caps Lock`)
- Swap LeftAlt and Gui(`Left Alt`)
- Swap RightAlt and Gui(`Right Alt`)
- Disable Gui(`Left Gui`)
- Swap Grave and Escape(`Grave`)
- Swap BackSlash and BackSpace(`Back Slash`)
- Enable NKRO on boot(`N`)

#### Default Layer
- Set Default Layer to 0(`0`)
- Set Default Layer to 1(`1`)
- Set Default Layer to 2(`2`)
- Set Default Layer to 3(`3`)
- Set Default Layer to 4(`4`)
- Set Default Layer to 5(`5`)
- Set Default Layer to 6(`6`)
- Set Default Layer to 7(`7`)



Mechanical Locking support
--------------------------
This feature makes it possible for you to use mechanical locking switch for `CapsLock`, `NumLock` 
or `ScrollLock`. To enable this feature define these macros in `config.h` and use `KC_LCAP`, `KC_LN
UM` or `KC_LSCR` in keymap for locking key instead of normal `KC_CAPS`, `KC_NLCK` or `KC_SLCK`. Res
ync option tries to keep switch state consistent with keyboard LED state.
 
    #define LOCKING_SUPPORT_ENABLE
    #define LOCKING_RESYNC_ENABLE



Start Your Own Project
-----------------------
**TBD**



Debugging
--------
Use PJRC's `hid_listen` to see debug messages. You can use the tool for debug even if firmware use LUFA stack.

You can use xprintf() to display debug info on `hid_listen`, see `tmk_core/common/xprintf.h`.



Files and Directories
-------------------
### Top
* tmk_core/     - core library
* keyboard/     - keyboard projects
* converter/    - protocol converter projects
* doc/          - documents



Coding Style
-------------
- Doesn't use Tab to indent, use 4-spaces instead.



Other Keyboard Firmware Projects
------------------
You can learn a lot about keyboard firmware from these. See [doc/other_projects.md](doc/other_projects.md).

t.m.k. Keyboard Firmware Collection
====================================
This is a keyboard firmware with some features for Atmel AVR controller.

Source code is available here: <http://github.com/tmk/tmk_keyboard>


Features
--------
* Multi-layer keymap    - Multiple keyboard layouts with layer switching.
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


Projects
--------
### converter
* ps2_usb       - [PS/2 keyboard to USB][GH_ps2]
* adb_usb       - [ADB keyboard to USB][GH_adb]
* m0110_usb     - [Machintosh 128K/512K/Plus keyboard to USB][GH_m0110]
* terminal_usb  - [IBM Model M terminal keyboard(PS/2 scancode set3) to USB][GH_terminal]
* news_usb      - [Sony NEWS keyboard to USB][GH_news]
* x68k_usb      - [Sharp X68000 keyboard to USB][GH_x68k]
* sun_usb       - Sun to USB(type4, 5 and 3?)
* usb_usb       - USB to USB(experimental)

### keyboard
* hhkb          - [Happy Hacking Keyboard professional][GH_hhkb]
* macway        - [Compact keyboard mod][GH_macway]
* hbkb          - [Happy Buckling sprint keyboard(IBM Model M mod)][GH_hbkb]
* IIgs_Standard - Apple IIGS keyboard mod(by JeffreySung)
* hid_liber     - [HID liberation controller][HID_liber](by alaricljs)
* phantom       - [Phantom keyboard][PHANTOM] (by Tranquilite)
* gh60          - [GH60 keyboard][GH60]

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
[HID_liber]:    http://deskthority.net/wiki/HID_Liberation_Device_-_DIY_Instructions
[PHANTOM]:      http://geekhack.org/index.php?topic=26742
[GH60]:         http://geekhack.org/index.php?topic=34959



Build & Program
---------------
### Install Tools
First, you need tools to build firmware and program your controller. I assume you are on Windows here.

1. Install [WinAVR][winavr]. This is old but works well for this purpose. `WinAVR` is a tool set to build firmware including C compiler(gcc) and make commands. You can use [CrossPack][crosspack] instead if you are on Mac.

2. Install [Atmel FLIP][flip]. `FLIP` is a tool to program(load) firmware into AVR controller(ATMega32u4) via DFU bootloader. ATMega32u4 has DFU bootloader by factory default. You can use [dfu-programmer][dfu-prog] instead if you are on Mac.

3. Install driver for DFU bootloader. At first time you start DFU bootloader on Chip 'Found New Hardware Wizard' will come up on Windows. If you install device driver properly you can find chip name like 'ATmega32U4' under 'LibUSB-Win32 Devices' tree on 'Device Manager'. If not you shall need to update its driver on 'Device Manager'. You will find the driver in `FLIP` install directory like: C:\Program Files (x86)\Atmel\Flip 3.4.5\usb\. If you use `dfu-programmer` install its driver.

If you use PJRC Teensy you don't need step 2 and 3, just get [Teensy loader][teensy-loader].


### Download source
You can find firmware source at github: https://github.com/tmk/tmk_keyboard

If you are familiar with `Git` tools you are recommended to use it.  
If not you can download zip archive from: https://github.com/tmk/tmk_keyboard/archive/master.zip


### Build firmware
1.  Open terminal window to get access to commands. You can use `cmd` in Windows or `Terminal.app` on Mac OSX. In Windows press `Windows` key and `R` then enter `cmd` in Run command dialog showing up.

2. Move to project directory in the firmware source.

    cd tmk_keyboard/{keyboard or converter}/<project>

3. Build firmware using GNU `make` command. You'll see <project>_<variant>.hex file in that directory unless something unexpected occurs in build process.

    mkae -f Makefile.<variant> clean
    make -f Makefile.<variant>




### Program Controller
Sock AVR USB chip including ATmega32U4 has DFU bootloader by factory default, you can use DFU tools for this purpose. `FLIP` is a DFU tool on Windows offered by Atmel. Open source command line DFU tool `dfu-programmer` also supports AVR chips, which run on Linux, Mac OSX and even Windows. If you have a PJRC Teensy you should use `Teensy Loader`.

#### DFU bootloader
To program AVR chip with DFU bootloader use `FLIP` or `dfu-programmer`.
If you have a proper program command in `Makefile` just type this.

`FLIP` has two version of tool, GUI app and command line program. If you want GUI see tutorial section below.
To use command line tool run this command. Note that you need to set PATH variable properly.

    $ make -f Makefile.<variant> flip

To program with `dfu-programmer` run:

    $ make -f Makefile.<variant> dfu

#### Teensy
If you have PJRC Teensy see instruction of `Teensy Loader` at: <http://www.pjrc.com/teensy/loader.html>
Or use this command if you have command line version of Teensy Loader installed.

    $ make -f Makefile.<variant> teensy


#### Other programmer
You may want to use other you favorite programmer like `avrdude` with AVRISPmkII, Aruduino or USBasp. In that case you can still use make target `program` for build with configuring PROGRAM_CMD in Makefile.

    $ make -f Makefile.<variant> program



#### FLIP GUI tutorial
1. On menu bar click Device -> Select, then. `ATmega32u4`.
2. On menu bar click Settings -> Communication -> USB, then click 'Open' button on 'USB Port Connection' dialog.
At this point you'll see greyouted widgets on the app get colored and ready.

3. On menu bar click File -> Load HEX File, then select your firmware hex file on File Selector dialog.
4. On 'Operations Flow' panel click 'Run' button to load the firmware binary to the chip. Note that you should keep 'Erase', 'Blank Check', 'Program' and 'Verify' check boxes selected.
5. Re-plug USB cord or click 'Start Application' button to restart your controller.
Done.

See also these instaructions if you need.

- <http://code.google.com/p/micropendous/wiki/LoadingFirmwareWithFLIP>
- <http://www.atmel.com/Images/doc7769.pdf>


[winavr]:       http://winavr.sourceforge.net/
[crosspack]:    http://www.obdev.at/products/crosspack/index.html
[flip]:         http://www.atmel.com/tools/FLIP.aspx
[dfu-prog]:     http://dfu-programmer.sourceforge.net/
[teensy-loader]:http://www.pjrc.com/teensy/loader.html



Makefile Options
----------------
### 1. MCU and Frequency.

    MCU = atmega32u4       # Teensy 2.0
    #MCU = at90usb1286      # Teensy++ 2.0
    F_CPU = 16000000

### 2. Features
Note that ***comment out*** to disable them.

    MOUSEKEY_ENABLE = yes	# Mouse keys
    PS2_MOUSE_ENABLE = yes	# PS/2 mouse(TrackPoint) support
    EXTRAKEY_ENABLE = yes	# Enhanced feature for Windows(Audio control and System control)
    NKRO_ENABLE = yes		# USB Nkey Rollover

### 3. Programmer
Optional. Set proper command for your controller, bootloader and programmer.

    # for PJRC Teensy
    PROGRAM_CMD = teensy_loader_cli -mmcu=$(MCU) -w -v $(TARGET).hex

    # for Atmel chip with DFU bootloader
    PROGRAM_CMD = dfu-programmer $(MCU) flash $(TARGET).hex

    # avrdude with other methods
    PROGRAM_CMD = avrdude -p $(MCU) -c avrispmkII -P USB -U flash:w:$(TARGET).hex
    PROGRAM_CMD = avrdude -p $(MCU) -c usbasp -U flash:w:$(TARGET).hex
    PROGRAM_CMD = avrdude -p $(MCU) -c arduino -P COM1 -b 57600 -U flash:w:$(TARGET).hex



Config.h Options
----------------
### 1. USB vendor/product ID and device description
    #define VENDOR_ID       0xFEED
    #define PRODUCT_ID      0xBEEF
    /* device description */
    #define MANUFACTURER    t.m.k.
    #define PRODUCT         Macway mod
    #define DESCRIPTION     t.m.k. keyboard firmware for Macway mod

### 2. Keyboard matrix configuration
    #define MATRIX_ROWS 8
    #define MATRIX_COLS 8
    #define MATRIX_HAS_GHOST

### 3. Mouse keys

### 4. PS/2 mouse

### 5. COMMAND key combination

    #define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KB_LSHIFT) | MOD_BIT(KB_RSHIFT))) 


Keymap
------
Many of existent projects offer keymap framework to define your own keymap easily. The following will explain how you can define keymap using this framework.
 Instead, you can also implement your own `keymap_get_action()` to return action code for each key if you want.

This is keymap example for [HHKB](http://en.wikipedia.org/wiki/Happy_Hacking_Keyboard) keyboard. Keyamp is defined in `keymaps[]` array.

    static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Layer 0: Default Layer
         * ,-----------------------------------------------------------.
         * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
         * |-----------------------------------------------------------|
         * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
         * |-----------------------------------------------------------|
         * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
         * |-----------------------------------------------------------|
         * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn1|
         * `-----------------------------------------------------------'
         *       |Gui|Alt  |Space                  |Alt  |Fn2|
         *       `-------------------------------------------'
         */
        KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
               TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
               LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN2, QUOT,ENT, \
               LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN1, \
                    LGUI,LALT,          SPC,                RALT,FN3),

        /* Layer 1: HHKB mode (HHKB Fn)
         * ,-----------------------------------------------------------.
         * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
         * |-----------------------------------------------------------|
         * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
         * |-----------------------------------------------------------|
         * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
         * |-----------------------------------------------------------|
         * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |Fn1|
         * `-----------------------------------------------------------'
         *      |Gui |Alt  |Space                  |Alt  |Gui|
         *      `--------------------------------------------'
         */ 
        KEYMAP(PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
               CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  NO,  BSPC, \
               LCTL,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,ENT, \
               LSFT,NO,  NO,  NO,  NO,  NO,  PPLS,PMNS,END, PGDN,DOWN,RSFT,FN0, \
                    LGUI,LALT,          SPC,                RALT,RGUI),
        /* Layer 2: Mouse mode (Semicolon)
         * ,-----------------------------------------------------------.
         * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
         * |-----------------------------------------------------------|
         * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |   |   |Backs|
         * |-----------------------------------------------------------|
         * |Contro|   |   |   |   |   |McL|McD|McU|McR|Fn0|   |Return  |
         * |-----------------------------------------------------------|
         * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
         * `-----------------------------------------------------------'
         *      |Gui |Alt  |Mb1                    |Alt  |Fn0|
         *      `--------------------------------------------'
         * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
         */
        KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
               TAB, NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,  BSPC, \
               LCTL,NO,  ACL0,ACL1,ACL2,NO,  MS_L,MS_D,MS_U,MS_R,FN0, QUOT,ENT, \
               LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,BTN4,BTN5,SLSH,RSFT,NO, \
                    LGUI,LALT,          BTN1,               RALT,FN0),
    };

    static const uint16_t PROGMEM fn_actions[] = {
        ACTION_LAYER_DEFAULT,                           // FN0
        ACTION_LAYER_SET(1),                            // FN1
        ACTION_LAYER_SET_TAP_KEY(2, KC_SCLN),           // FN2
        ACTION_LAYER_BIT_TOGGLE(2),                     // FN3
    };



### 1. Keycode
See `common/keycode.h`. Keycode is 8bit internal code to inidicate action performed on key in keymap. Keycode has `KC_` prefixed symbol respectively. Most of keycodes like 'KC_A' have simple action register key on press and unregister on release, on the other some of keycodes has some special actions like Fn keys, Media contorl keys, System control keys and Mouse keys.

 ***In `KEYMAP` definition you need to omit prefix part `KC_` of keycode to keep keymap compact.*** For example, just use `A` instead you place `KC_A` in `KEYMAP`. Some keycodes has 4-letter short name in addition to descriptive name, you'll prefer short one in `KEYMAP`.

 **`KC_NO`** indicates the key has no keycode to transmit.

 **`KC_LGUI`** and **`KC_RGUI`** are windows key or command key in Mac.

 **`KC_FNnn`** are `Fn` keys which not given any action at the beginning unlike most of keycodes has its own action. To use these keys in `KEYMAP` you need to assign action you want at first. Action of `Fn` is defined in `fn_actions[]` and index of the array is identical with number part of `KC_FNnn`. Thus `KC_FN0` designates action defined in first element of the array. ***32 `Fn` keys can be defined at most.***

 See keycode table or `keycode.h` for other keycodes.
 ***TODO: Keycode table link here.*** 

 In regard to implementation side most of keycodes are identical with [HID usage] sent to host for real and some virtual keycodes are defined to support special actions.
[HID usage]: http://www.usb.org/developers/devclass_docs/Hut1_11.pdf



### 2. Action
See `common/action.h`. Action is a 16bit code and defines function to perform on events of a key like press, release, hold and tap. You can define various actions to use various action codes.

Most of keys just register 8bit keycode as HID usage(or scan code) to host, but to support other complex functions needs 16bit extended action codes internally. But using 16bit action codes with keymap results in double size in memory against keycodes. To avoid this waste 8bit keycodes are used in `KEYMAP` to define instead of action codes. ***Keycodes can be considered as subset of action codes.*** Like `KC_A`(0x04) is equal to a `Key` action(0x0004) that transmit keycode of `A`.

#### 2.1 Key action
Key is simple action that registers keycode on press of key and unregister on release.
You can define `Key` action on `A` with:

    ACTION_KEY(KC_A)

But you won't need to use this expression directly because you can just put symbol like `A` in `KEYMAP`.

 Say you want to assign a key to `Shift + 1` to get *!* or `Alt + Tab` to switch windows.

    ACTION_MOD_KEY(KC_LSHIFT, KC_1)
    ACTION_MOD_KEY(KC_LALT, KC_TAB)

`Alt,Shift + Tab`
    ACTION_MODS_KEY((MOD_BIT(KC_LALT) | MOD_BIT(KC_LSHIFT)), KC_TAB)

These actions are comprised of strokes of modifiers and a key. `Macro` action is needed if you want more complex key strokes.

#### 2.2 Layer Actions
This sets `default layer` into `current layer`. With this action you can return to `default layer`.

    ACTION_LAYER_DEFAULT

`Layer Set` action sets given layer argument to `current layer`. `Layer Set` action can take 0 to 15 as argument.

    ACTION_LAYER_SET(layer)
    ACTION_LAYER_SET_TOGGLE(layer)
    ACTION_LAYER_SET_TAP_KEY(layer, key)
    ACTION_LAYER_SET_TAP_TOGGLE(layer)

`Layer Bit` action XOR bits with `current layer`. `Layer Bit` action can take 0 to 8 as argument. 

    ACTION_LAYER_BIT(bits)
    ACTION_LAYER_BIT_TOGGLE(bits)
    ACTION_LAYER_BIT_TAP_KEY(bits, key)
    ACTION_LAYER_BIT_TAP_TOGGLE(bits)

These acitons change `default layer`.
    ACTION_LAYER_SET_DEFAULT(layer)
    ACTION_LAYER_BIT_DEFAULT(bits)


#### 2.3 Macro action
`Macro` action indicates complex key strokes. ***TODO***


#### 2.4 Function action
`Function` action can be defined freely in C function. ***TODO***
`Function` action is implemented in `keymap_call_function()`



### 3. Layer
 Layer is key-action map to assign action to every physical key. You can define multiple layers in keymap and select a layer out of keymap during operation at will.

 First layer is indexed by `Layer 0` which usually become **`default layer`** and active in initial state. **`current layer`** is active layer at that time and can be changed with user interaction. You can define **16 layers** at most in default keymap framework.

 you can define a layer with placing keycode symbols separated with `comma` in `KEYMAP`, which is formed with resemblance to physical keyboard layout so as you can easily put keycode on place you want to map. ***You can define most of keys with just using keycodes*** except for `Fn` key serving special actions.



### 4. Layer switching
You can have some ways to switch layer with these actions.
There are two kind of layer switch action `Layer Set` and `Layer Bit` and two type of switching behaviour **Momentary** and **Toggle**.

#### 4.1 Momentary switching
Momentary switching changes layer only while holding Fn key.

##### 4.1.1 Momentary Set
This `Layer Set` action sets new layer(`Layer 1`) to `current layer` on key press event.

    ACTION_LAYER_SET(1)

It switches to destination layer immediately when key is pressed, after that actions on keymap of destination layer is perfomed. ***Thus you shall need to place action to come back on destination layer***, or you will be stuck in destination layer without way to get back. To get back to `default layer` you can use this action.

    ACTION_LAYER_DEFAULT

##### 4.1.2 Momentary Bit
This `Layer Bit` action performs XOR(`1`) with `current layer` on both press and release event. If you are on `Layer 0` now next layer to switch will be `Layer 1`. To come back to previous layer you need to place same action on destination layer.

    ACTION_LAYER_BIT(1)

#### 4.2 Toggle switching
Toggle switching changes layer after press then release. You keep being on the layer until you press key to return.

##### 4.2.1 Toggle Set
This `Layer Set Toggle` action is to set `Layer 1` to `current layer` on release and do none on press.

    ACTION_LAYER_SET_TOGGLE(1)

To get back to `default layer` you can use this action.

    ACTION_LAYER_DEFAULT

##### 4.2.2 Toggle Bit
This `Layer Bit Toggle` action is to XOR `1` with `current layer` on release and do none on press. If you are on `Layer 2` you'll switch to `Layer 3` on press. To come back to previous layer you need to place same action on destination layer.

    ACTION_LAYER_BIT_TOGGLE(1)


#### 4.3 Momentary switching with Tap key
These actions switch to layer only while holding `Fn` key and register key on tap. **Tap** means to press and release key quickly.

    ACTION_LAYER_SET_TAP_KEY(2, KC_SCLN)
    ACTION_LAYER_SET_BIT_KEY(2, KC_SCLN)

With these you can place layer switching function on normal alphabet key like `;` without losing its original register function.

#### 4.4 Momentary switching with Tap Toggle
This changes layer only while holding `Fn` key and toggle layer after several taps. **Tap** means to press and release key quickly.

    ACTION_LAYER_SET_TAP_TOGGLE(layer)
    ACTION_LAYER_BIT_TAP_TOGGLE(layer)

Number of taps can be defined with `TAPPING_TOGGLE` in `config.h`, `5` by default.




Legacy Keymap
-------------
This was used in prior version and still works due to legacy support code in `common/keymap.c`. Legacy keymap doesn't support many of features that new keymap offers.

In comparison with new keymap how to define Fn key is different. It uses two arrays `fn_layer[]` and `fn_keycode[]`. The index of arrays corresponds with postfix number of `Fn` key. Array `fn_layer[]` indicates destination layer to switch and `fn_keycode[]` has keycodes to send when tapping `Fn` key.

In following setting example, `Fn0`, `Fn1` and `Fn2` switch layer to 1, 2 and 2 respectively. `Fn2` registers `Space` key when tap while `Fn0` and `Fn1` doesn't send any key.

    static const uint8_t PROGMEM fn_layer[] = {
        1,              // Fn0
        2,              // Fn1
        2,              // Fn2
    };

    static const uint8_t PROGMEM fn_keycode[] = {
        KC_NO,          // Fn0
        KC_NO,          // Fn1
        KC_SPC,         // Fn2
    };



Debuging
--------
Use PJRC's `hid_listen` to see debug messages. You can use the tool for debug even if firmware use LUFA stack.

You will see output from firmware like this.

    r/c 01234567
    00: 00000000
    01: 00000000
    02: 00000000
    03: 00000000
    04: 00000000
    05: 00000000
    06: 00000000
    07: 00000000

    ---- action_exec: start -----
    EVENT: 0307u(22511)
    Tapping: Tap release(2)
    ACTION: ACT_LAYER[5:2C]
    LAYER_PRESSED: Tap: unregister_code
    TAPPING_KEY=0307u(22511):2
    processed: 0307u(22511):2

    Tapping: End(Timeout after releasing last tap): FFFFu(22715)
    TAPPING_KEY=0000u(0):0




Magic Comannds
--------------
To see help press `Magic` + `H`.

 `Magic` key bind may be `LShift` + `RShift` in many project, but `Power` key on ADB converter. `Magic` keybind can be vary on each project, check `config.h` in project directory.

Following commands can be also executed with `Magic` + key. In console mode `Magic` keybind is not needed.

    ----- Command Help -----
    c:      enter console mode
    d:      toggle debug enable
    x:      toggle matrix debug
    k:      toggle keyboard debug
    m:      toggle mouse debug
    p:      toggle print enable
    v:      print device version & info
    t:      print timer count
    s:      print status
    0/F10:  switch to Layer0
    1/F1:   switch to Layer1
    2/F2:   switch to Layer2
    3/F3:   switch to Layer3
    4/F4:   switch to Layer4
    PScr:   power down/remote wake-up
    Caps:   Lock Keyboard(Child Proof)
    Paus:   jump to bootloader



Start Your Own Project
-----------------------



Files & Directories
-------------------
### Top
* common/       - common codes
* protocol/     - keyboard protocol support
* keyboard/     - keyboard projects
* converter/    - protocol converter projects
* doc/          - documents
* common.mk     - Makefile for common
* protoco.mk    - Makefile for protocol
* rules.mk      - Makefile for build rules

### Common
***TODO***

### Keyboard Protocols
* lufa/     - LUFA USB stack
* pjrc/     - PJRC USB stack
* vusb/     - Objective Development V-USB
* iwrap/    - Bluetooth HID for Bluegiga iWRAP
* ps2.c     - PS/2 protocol
* adb.c     - Apple Desktop Bus protocol
* m0110.c   - Macintosh 128K/512K/Plus keyboard protocol
* news.c    - Sony NEWS keyboard protocol
* x68k.c    - Sharp X68000 keyboard protocol
* serial_soft.c - Asynchronous Serial protocol implemented by software



License
-------
Under `GPL` 2 or later. Some protocol files are under `Modified BSD License`.
PJRC stack has its own license.

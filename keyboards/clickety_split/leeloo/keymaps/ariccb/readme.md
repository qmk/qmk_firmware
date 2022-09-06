# Clickety Split | Leeloo

![Leeloo](https://cdn.shopify.com/s/files/1/0599/3460/5491/files/Leeloo-rev1.0-w.jpg?v=1646798726)

Keyboard Designer: [clicketysplit.ca](https://clicketysplit.ca)
GitHub: [ClicketySplit](https://github.com/ClicketySplit)
Hardware Supported: Pro Micro, Elite-C, nice!nano v2

Albeit, there is no doubt where Leeloo's heritage is derived from—Lily58, and Corne.  It is not a copy-paste-modify implementation.

Leeloo has been designed from scratch; everything from the schematic to its PCB footprints, and column stagger. There are some subtle differences that may not be apparent; however, its subtle changes enable an interesting future.

Features:
* 4x6x5m Split Keyboard
* Support for MX/Box or Low Profile Choc switches.
* 90% of the switches are socketed; with the exception to the rotary encoder positions—6 positions require soldering.
* Support for 128x32 OLED Displays.
* The option to select one of three positions for an EC11 rotary encoder on each half.
* Support for Alps Alpine Micro Switch
* Support for 3.7v 301230 LiPo Battery

# Building Your Firmware
QMK Firmware: [Quantum Mechanical Keyboard Firmware](https://docs.qmk.fm/#/)
Setup: [Setting Up Your QMK Environment](https://docs.qmk.fm/#/newbs_getting_started)
Customization: [Building Your First Firmware](https://docs.qmk.fm/#/newbs_building_firmware)
Flashing Firmware: [Flashing Your Keyboard](https://docs.qmk.fm/#/newbs_flashing)

Build commands for the default keymap of Leeloo with Pro Micros:

    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl avrdude-split-left
    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl avrdude-split-right


Build commands for the default keymap of Leeloo with Elite-Cs:

    * Open rules.mk and edit the following lines:
        * Add a '#' in front of: BOOTLOADER = caterina
        * Remove the '#' in front of: #BOOTLOADER = atmel-dfu
    * Save rules.mk

    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl dfu-split-left
    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl dfu-split-right


# Support
If you have any questions with regards to Leeloo, please [Contact Us](https://clicketysplit.ca/pages/contact-us).

Clickety Split
For the love of split keyboards.

# Customizations made on Ariccb Keymap
##Note - All credit for these features go to the ones that actually designed them, I'm just a happy user that was able to fit them all into my keymap.

- ##I'm using many features in the "QMK feature libraries" by Pascal Getreuer, found here: https://getreuer.info/posts/keyboards/index.html. THANKS Pascal for such amazing functionality!!
##Including:
* Autocorrection (not on this keyboard because I ran out of memory on my promicro)
* CAPS Word (hit both shifts at same time to activate caps for only one word)
* Layer Lock key (macro to stay in current layer, more functional than Layer Toggle)
* Word Selection - (macro that selects the word the cursor is currently in, and repeated presses selects the next whole word as well. If shift is pressed prior, the whole line is selected, and repeated presses with shift held selects the next whole line)
* Macro Buttons (Arrow =>-> macro, braces {}[]<>() macro,)

- ##"Adaptive Keys" - credit to u/BoardroomCynics and u/phbonachi on reddit for pointing me in the direction of using this. It's one of my favourite and user-experience-improving features on my keyboard. I found how to do it here https://www.reddit.com/r/KeyboardLayouts/comments/smnv1o/adaptive_keys_qmk_implementation/

  * Adaptive Keys is a perfect way to fix annoying single finger bigrams which are present in EVERY LAYOUT, no matter how optimized. I use colemak dh, and the worst one is sc, on the middle finger. other ones are pt, fs, lk, ue, dg, cs, and (e,) and I am able to use really uncommonly placed together letters to get them instead. They're actually really intuitive the way I have them set up, it only took a tiny bit of practicing to now being able to use them without thinking. So SV->SC (school, science, scene, ), PF->PT (except, captain, kept), FP->FS (beliefs, briefs, playoffs), LJ->LK (milk, talk, walk), UY->UE (question, true, value, guess, continue), DX->DG, (budget, bridge, acknowledge, gadget, edge), CX->CS (graphics, politics, economics, electronics), E/->E, (anytime e is followed by a comma).

- ##Very intuitive combos
* XC(copy), CD(paste), XD(WIN+V for clipboard), ZX(cut), XV(paste without formatting)
* EM(paste email), EJ(paste work email 2), EK(paste work email 2)
* Period + Various mnemonic left-hand shortcuts for HTML code

``` Layout

/* (COLEMAKH-DH Layer)
 * .------------F1---------------------------.                                      .--------------------------F8-------------.
 * | HYPER|  F2  |  F9  |  F10 |  F11 |  F12 |                                      |  F3  |  F4  |  F5  |  F6  |  F7  |Select|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |ADJ,ESC| Q   |  W   |  F   |  P   |  B   |  // this rotary is for window        |  J   |  L   |  U   |  Y   |  ;   | BSPC |
 * |------+------+------+------+------+------|     management, zoom, and            |------+------+------+------+------+------|
 * | MTTAB|  A   |  R   |  S   |  T   |  G   |-------.                      .-------|  M   |  N   |  E   |  I   |  O   |CTRL,'|
 * |------+------+------+------+------+------| Ptoys |                      | Window|------+------+------+------+------+------|
 * | SHIFT| WIN_Z|  X   |  C   |  D   |  V   | Mute  |-->Mute mic           | Switch|  K   |  H   |  ,   |  .   |  /   |SFT,\ |
 * .-----------------------------------------|-------|   on Button Press    |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /      /                        \ LALT \       |     |MW R/L|  //This rotary for Play+Pause
 *                      | APP | ENTER| OSSft/ SPACE/                          \DELETE\ SPACE|RAISE| DIAL2|--> Right Scroll
 *                      `-------------------------'                            '-------------------------'

/* MIT Layout (LOWER Layer)
 * .-----------------------------------------.                                      .-----------------------------------------.
 * | HYPER|   1  |   2  |   3  |   4  |   5  |                                      |   6  |   7  |   8  |   9  |   0  |Delete|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
*  |   `  |   !  |   #  |   $  |   [  |   ]  |                                      |   ^  |   7  |   8  |   9  |   :  | Bsp  |
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |S(TAB)|   ~  |   ^  |   %  |   (  |   )  |-------.                      .-------|   =  |   4  |   5  |   6  |   -  |  +   |
 * |------+------+------+------+------+------|Undo/Redo|                    | Layer |------+------+------+------+------+------|
 * | SHIFT|   |  |   &  |   "  |   {  |   }  | DIAL1 |--> Toggle HDR        | Lock  |   @  |   1  |   2  |   3  |   /  |  *   |
 * .-----------------------------------------|-------|    on Button Press   |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /      /                        \      \       |      |MW U/D|
 *                      | APP | ENTER| OSSft/ SPACE/                          \ Space\   0  |  .   | DIAL2|--> does a configurable keyboard shortcut: Hyper(J)
 *                      `-------------------------'                            '--------------------------'

/* MIT Layout (RAISE Layer)
 * .-----------------------------------------.                                      .-----------------------------------------.
 * | HYPER|      |      |      |      |DEBUG |                               track  |MBtn 2|      |NumLck|      |      |      |
 * |------+------+------+------+------+------|                               point  |------+------+------+------+------+------|
 * |      | Mb3  | Mb2  | MsUp | Mb1  | Mute |                               mouse  |      |      | MbMid|      |   =  | Bksp |
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |      | Menu | MsLft| MDown|Mright| Vol+ |-------.                      .-------|ARROW | MbLft|SELWORD|MbRgt|      |   !  |
 * |------+------+------+------+------+------|Cursor |                      | Layer |------+------+------+------+------+------|
 * |      | MWLft| MWUp | NWDn |NWRght| Vol- | DIAL1 |-->pins current       | Lock  | ()<> | []{} |  <   |   >  |   ?  |   |  |
 * .-----------------------------------------|-------|   window to all      |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /      /    virtual destktops on\ Mouse\ Mouse |******|Search|
 *                      | APP | ENTER| OSSft/ SPACE/     Button Press         \ Btn 1\ Btn 3|******| DIAL2|--> sends CTRL(KC_F)
 *                      `-------------------------'                            '--------------------------'    on Button Press

 /* MIT Layout (ADJUST Layer)
 * .-----------------------------------------.                                      .-----------------------------------------.
 * | HYPER|      |      |      |      |Calc  |                                      | TabDn| TabUp| Back |Frward|      |SclLok|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |******| Ctrl | Shift| Alt  |      |MyComp|                                      |      | Home |  Up  |  End |      |Delete|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |      |  F5  |      |      |DESKTL|DESKTR|--------.                     .-------|C Left| Left | Down | Right|CRight|CAPSLK|
 * |------+------+------+------+------+------| Cursor |                     | Layer |------+------+------+------+------+------|
 * |      |      |      |      |      |AltTab| Word   |--> Resets Zoom      | Lock  |Ctrl D|PageUp|AltPDn|PageDn| PAUSE|INSERT|
 * .-----------------------------------------|--------|                     |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /Window /                       \       \       |      |Volume|
 *                      | APP | ENTER| OSSft/Switch /                         \       \      |      | DIAL2|--> Next Song
 *                      `--------------------------'                           '---------------------------'    on Button Press

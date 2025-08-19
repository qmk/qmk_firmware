# Nerdboard #

Nerdboard is a 29 key split ergonomic keyboard with a built in mouse.
Build instructions can be found https://github.com/thelowprokill/nerdboard
* Keyboard Maintainer: [thelowprokill](https://github.com/thelowprokill)
* Hardware Supported: Arduino pro micro

### QMK Firmware ###
This keyboard runs on an open source keyboard firmware called Quantum Mechanical Keyboard (QMK) Firmware.
The qmk_firmware folder is the full firmware files for this keyboard, also available on git hub. [https://github.com/thelowprokill/qmk_firmware]
The nerdboard folder is just the necessary files for nerdboard.


### Set up ###
Go to https://docs.qmk.fm/#/newbs_getting_started and follow the instructions to set up qmk on your operating system.
Copy the nerdboard folder to $qmk_home/keyboards/handwired/nerdboard.

### Flash ###
qmk flash -kb handwired/nerdboard/pro_micro_29 -km default

qmk flash is the command to build the firmware and flash the keyboard.
the -kb flag specifies which keyboard to build.
the -km flag specifies which keymap to use.
This way multiple layouts can be used without copying the entire folder or overwriting existing files.

### Editiing the Keymap ###
Inside $qmk_home/keyboards/handwired/nerdboard/pro_micro_29/keymaps/
there are named folders each with a file called keymap.c

This is where your keymaps are defined.
The name of the folder is specified by the flash command.
The keymap.c file can be edited in any text editor.
I highly recomend changing it to your liking. 
This layout works great for me and took me several revissions to get it here.

There are several sections inside the default keymap.
* defining shortcuts and layers
    * layer definitions
        This is an enumeration of all the layers.
    * layer keys
        There keys change the layers.
        TG is Toggles the layer on or off.
        TO Turns the layer on and turns off all other layers.
        MO Turns on the layer when held.
    * alternate keys
        There are shortcuts to diferent keys to make the layout easier to read.
    * mod taps
        A mod tap is a modifer key when held down and a reqular key when tapped.
        The mod taps are for the home row to have home row mods.
        There are mod taps defined for both Jonmak and querty layouts.
        CTL_ENT is ctrl when held and enter when tapped.

        Jonmak
        MT_A is shift when held and a when tapped.
        MT_R is ctrl when held and r when tapped.
        MT_S is alt when held and s when tapped.
        MT_T is shift when held and t when tapped.

        Querty
        MTQ_A is shift when held and a when tapped.
        MTQ_S is ctrl when held and s when tapped.
        MTQ_D is alt when held and d when tapped.
        MTQ_F is shift when held and f when tapped.

        These are only for the left side because I type only using the left shift. 
        Add the right side if you want to type with the right shift.
    * layer tap
        A layer tap is when you tap a key it does on key and when you hold it it changes layer.
        The two layer taps being used are both on the thumb keys.
        The MO_TAB is mouse when held and tab when tapped.
        The SY_GRV is symbol when held and grave (backtick / "\`") when tapped.
* oled
    * splash screen
        This screen is showed for the first few seconds when the keyboard is powered on.
    * layer
        This shows what layer you are on.
    * modifiers
        This shows what modifiers are active on the screen. 
        Moifier keys are Caps Lock, Shift, Ctrl, Alt, and GUI (Windows key / Super).
* auto switch layer
    This is here to make jonmak the default layer even though game is index 0
* keymap
    * game layer
        This is the first layer so that all other layers can draw over it.
        This makes the GJONMAK layer change key work to temporarily enable the jonmak layer.
        This layer is used for gaming and the keyboard switches to jonmak when it is powered on.
    * jonmak layer
        This is the default layer for the keyboard.
        This layout was created by Jon Hull as a modification to Colemak that works better with vim and this keyboard.
    * jonmak extended layer
        Because this keyboard only has 29 keys another layer is needed to get all the leters and punctuation.
    * symbol layer
        This layer is used for numbers and arythimetic symbols.
        There is a 10 key for easily typing numbers and symbols.
    * mouse layer
        This layer is for using the mouse keys. 
    * function layer
        This is for miscellaneous functions that don't fit int with other layers.

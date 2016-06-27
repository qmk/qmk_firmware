# Quantum Mechanical Keyboard Firmware

[![Build Status](https://travis-ci.org/jackhumbert/qmk_firmware.svg?branch=master)](https://travis-ci.org/jackhumbert/qmk_firmware)

This is a keyboard firmware based on the [tmk_keyboard firmware](http://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR controllers, and more specifically, the [OLKB product line](http://olkb.com), the [ErgoDox EZ](http://www.ergodox-ez.com) keyboard, and the [Clueboard product line](http://clueboard.co/).

## Official website

For an easy-to-read version of this document and the repository, check out [http://qmk.fm](http://qmk.fm). Nicely formatted keyboard and keymap listings are also available there, along with the ability to download .hex files instead of having to setup a build environment and compile them.

## Included Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [Atomic](/keyboards/atomic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard rev.1](/keyboards/clueboard1/)
* [Clueboard rev.2](/keyboards/clueboard2/)
* [Cluepad](/keyboards/cluepad/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). This repo used to be a fork of [TMK](https://github.com/tmk/tmk_keyboard), and we are incredibly grateful for his founding contributions to the firmware. We've had to break the fork due to purely technical reasons - it simply became too different over time, and we've had to start refactoring some of the basic bits and pieces. We are huge fans of TMK and Hasu :)

This documentation is edited and maintained by Erez Zukerman of ErgoDox EZ. If you spot any typos or inaccuracies, please [open an issue](https://github.com/jackhumbert/qmk_firmware/issues/new).

The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [Erez Zukerman](https://github.com/ezuk), and the Clueboard by [Zach White](https://github.com/skullydazed).

## Documentation roadmap

This is not a tiny project. While this is the main readme, there are many other files you might want to consult. Here are some points of interest:

* The readme for your own keyboard: This is found under `keyboards/<your keyboards's name>/`. So for the ErgoDox EZ, it's [here](keyboards/ergodox_ez/); for the Planck, it's [here](keyboards/planck/) and so on.
* The list of possible keycodes you can use in your keymap is actually spread out in a few different places:
  * [doc/keycode.txt](doc/keycode.txt) - an explanation of those same keycodes.
  * [quantum/keymap.h](quantum/keymap.h) - this is where the QMK-specific aliases are all set up. Things like the Hyper and Meh key, the Leader key, and all of the other QMK innovations. These are also explained and documented below, but `keymap.h` is where they're actually defined.
* The [TMK documentation](doc/TMK_readme.md). QMK is based on TMK, and this explains how it works internally.

# Getting started

Before you are able to compile, you'll need to install an environment for AVR development. You'll find the instructions for any OS below. If you find another/better way to set things up from scratch, please consider [making a pull request](https://github.com/jackhumbert/qmk_firmware/pulls) with your changes!

## Build Environment Setup

### Windows (Vista and later)
1. If you have ever installed WinAVR, uninstall it.
2. Install [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe). Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**.
3. Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The scripts depend on the default location.
4. Clone this repository. [This link will download it as a zip file, which you'll need to extract.](https://github.com/jackhumbert/qmk_firmware/archive/master.zip) Open the extracted folder in Windows Explorer.
5. Double-click on the 1-setup-path-win batch script to run it. You'll need to accept a User Account Control prompt. Press the spacebar to dismiss the success message in the command prompt that pops up.
6. Right-click on the 2-setup-environment-win batch script, select "Run as administrator", and accept the User Account Control prompt. This part may take a couple of minutes, and you'll need to approve a driver installation, but once it finishes, your environment is complete!
7. Future build commands should be run from the MHV AVR Shell, which sets up an environment compatible with colorful build output. The standard Command Prompt will also work, but add `COLOR=false` to the end of all make commands when using it.

### Mac
If you're using [homebrew,](http://brew.sh/) you can use the following commands:

    brew tap osx-cross/avr
    brew install avr-libc
    brew install dfu-programmer

This is the recommended method. If you don't have homebrew, [install it!](http://brew.sh/) It's very much worth it for anyone who works in the command line.

You can also try these instructions:

1. Install Xcode from the App Store.
2. Install the Command Line Tools from `Xcode->Preferences->Downloads`.
3. Install [DFU-Programmer][dfu-prog].

### Linux
Install AVR GCC, AVR libc, and dfu-progammer with your favorite package manager.

Debian/Ubuntu example:

    sudo apt-get update
    sudo apt-get install gcc-avr avr-libc dfu-programmer

### Vagrant
If you have any problems building the firmware, you can try using a tool called Vagrant. It will set up a virtual computer with a known configuration that's ready-to-go for firmware building. OLKB does NOT host the files for this virtual computer. Details on how to set up Vagrant are in the [VAGRANT_GUIDE file](VAGRANT_GUIDE.md).

## Verify Your Installation
1. If you haven't already, obtain this repository ([https://github.com/jackhumbert/qmk_firmware](https://github.com/jackhumbert/qmk_firmware)). You can either download it as a zip file and extract it, or clone it using the command line tool git or the Github Desktop application.
2. Open up a terminal or command prompt and navigate to the `qmk_firmware` folder using the `cd` command. The command prompt will typically open to your home directory. If, for example, you cloned the repository to your Documents folder, then you would type `cd Documents/qmk_firmware`. If you extracted the file from a zip, then it may be named `qmk_firmware-master` instead.
3. To confirm that you're in the correct location, you can display the contents of your current folder using the `dir` command on Windows, or the `ls` command on Linux or Mac. You should see several files, including `readme.md` and a `quantum` folder. From here, you need to navigate to the appropriate folder under `keyboards/`. For example, if you're building for a Planck, run `cd keyboards/planck`.
4. Once you're in the correct keyboard-specific folder, run the `make` command. This should output a lot of information about the build process. More information about the `make` command can be found below.

# Customizing your keymap

In every keymap folder, the following files are recommended:

* `config.h` - the options to configure your keymap
* `keymap.c` - all of your keymap code, required
* `Makefile` - the features of QMK that are enabled, required to run `make` in your keymap folder
* `readme.md` - a description of your keymap, how others might use it, and explanations of features 

## The `make` command

The `make` command is how you compile the firmware into a .hex file, which can be loaded by a dfu programmer (like dfu-progammer via `make dfu`) or the [Teensy loader](https://www.pjrc.com/teensy/loader.html) (only used with Teensys). You can run `make` from the root (`/`), your keyboard folder (`/keyboards/<keyboard>/`), or your keymap folder (`/keyboards/<keyboard>/keymaps/<keymap>/`) if you have a `Makefile` there (see the example [here](/doc/keymap_makefile_example.mk)).

By default, this will generate a `<keyboard>_<keymap>.hex` file in whichever folder you run `make` from. These files are ignored by git, so don't worry about deleting them when committing/creating pull requests. Your .hex file will also be available on qmk.fm/keyboards/<keyboard>/keymaps/<keymap>/.

Below are some definitions that will be useful:

* The "root" (`/`) folder is the qmk_firmware folder, in which are `doc`, `keyboard`, `quantum`, etc.
* The "keyboard" folder is any keyboard project's folder, like `/keyboards/planck`.
* The "keymap" folder is any keymap's folder, like `/keyboards/planck/keymaps/default`.

Below is a list of the useful `make` commands in QMK:

* `make` - cleans automatically and builds your keyboard and keymap depending on which folder you're in. This defaults to the "default" layout (unless in a keymap folder), and Planck keyboard in the root folder
  * `make keyboard=<keyboard>` - specifies the keyboard (only to be used in root)
  * `make keymap=<keymap>` - specifies the keymap (only to be used in root and keyboard folder - not needed when in keymap folder)
* `make quick` - skips the clean step (cannot be used immediately after modifying config.h or Makefiles)
* `make dfu` - (requires dfu-programmer) builds and flashes the keymap to your keyboard once placed in reset/dfu mode (button or press `KC_RESET`). This does not work for Teensy-based keyboards like the ErgoDox EZ.
  * `keyboard=` and `keymap=` are compatible with this
* `make all-keyboards` - builds all keymaps for all keyboards and outputs status of each (use in root)
* `make all-keyboards-default` - builds all default keymaps for all keyboards and outputs status of each (use in root)
* `make all-keymaps [keyboard=<keyboard>]` - builds all of the keymaps for whatever keyboard folder you're in, or specified by `<keyboard>`
* `make all-keyboards-quick`, `make all-keyboards-default-quick` and `make all-keymaps-quick [keyboard=<keyboard>]` - like the normal "make-all-*" commands, but they skip the clean steps

Other, less useful functionality:

* `make COLOR=false` - turns off color output
* `make SILENT=true` - turns off output besides errors/warnings
* `make VERBOSE=true` - outputs all of the avr-gcc stuff (not interesting)

## The `Makefile`

There are 3 different `make` and `Makefile` locations:

* root (`/`)
* keyboard (`/keyboards/<keyboard>/`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/`)

The root contains the code used to automatically figure out which keymap or keymaps to compile based on your current directory and commandline arguments. It's considered stable, and shouldn't be modified. The keyboard one will contain the MCU set-up and default settings for your keyboard, and shouldn't be modified unless you are the producer of that keyboard. The keymap Makefile can be modified by users, and is optional. It is included automatically if it exists. You can see an example [here](/doc/keymap_makefile_example.mk) - the last few lines are the most important. The settings you set here will override any defaults set in the keyboard Makefile. **It is required if you want to run `make` in the keymap folder.**

### Makefile options

Set the variables to `no` to disable them, and `yes` to enable them.

`BOOTMAGIC_ENABLE`

This allows you to hold a key and the salt key (space by default) and have access to a various EEPROM settings that persist over power loss. It's advised you keep this disabled, as the settings are often changed by accident, and produce confusing results that makes it difficult to debug. It's one of the more common problems encountered in help sessions.

`MOUSEKEY_ENABLE`

This gives you control over cursor movements and clicks via keycodes/custom functions.

`EXTRAKEY_ENABLE`

This allows you to use the system and audio control key codes.

`CONSOLE_ENABLE`

TODO

`COMMAND_ENABLE`

TODO

`SLEEP_LED_ENABLE`

Enables your LED to breath while your computer is sleeping. Timer1 is being used here. This feature is largely unused and untested, and needs updating/abstracting.

`NKRO_ENABLE`

This allows for n-key rollover (default is 6) to be enabled. It is off by default, but can be forced by adding `#define FORCE_NKRO` to your config.h.

`BACKLIGHT_ENABLE`

This enables your backlight on Timer1 and ports B5, B6, or B7 (for now). You can specify your port by putting this in your `config.h`:

    #define BACKLIGHT_PIN B7

`MIDI_ENABLE`

This enables MIDI sending and receiving with your keyboard. To enter MIDI send mode, you can use the keycode `MI_ON`, and `MI_OFF` to turn it off. This is a largely untested feature, but more information can be found in the `quantum/quantum.c` file.

`UNICODE_ENABLE`

This allows you to send unicode symbols via `UC(<unicode>)` in your keymap. Only codes up to 0x7FFF are currently supported.

`BLUETOOTH_ENABLE`

This allows you to interface with a Bluefruit EZ-key to send keycodes wirelessly. It uses the D2 and D3 pins.

`AUDIO_ENABLE`

This allows you output audio on the C6 pin (needs abstracting). See the [audio section](#driving-a-speaker---audio-support) for more information.

### Customizing Makefile options on a per-keymap basis

If your keymap directory has a file called `Makefile` (note the filename), any Makefile options you set in that file will take precedence over other Makefile options for your particular keyboard.

So let's say your keyboard's makefile has `BACKLIGHT_ENABLE = yes` (or maybe doesn't even list the `BACKLIGHT_ENABLE` option, which would cause it to be off). You want your particular keymap to not have the debug console, so you make a file called `Makefile` and specify `BACKLIGHT_ENABLE = no`.

You can use the `doc/keymap_makefile_example.md` as a template/starting point.

## The `config.h` file

There are 2 `config.h` locations:

* keyboard (`/keyboards/<keyboard>/`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/`)

The keyboard `config.h` is included only if the keymap one doesn't exist. The format to use for your custom one [is here](/doc/keymap_config_h_example.h). If you want to override a setting from the parent `config.h` file, you need to do this:

```c
#undef MY_SETTING
#define MY_SETTING 4
```

For a value of `4` for this imaginary setting. So we `undef` it first, then `define` it.

You can then override any settings, rather than having to copy and paste the whole thing.

## Going beyond the keycodes

Aside from the [basic keycodes](doc/keycode.txt), your keymap can include shortcuts to common operations.

### Switching and toggling layers

`MO(layer)` - momentary switch to *layer*. As soon as you let go of the key, the layer is deactivated and you pop back out to the previous layer. When you apply this to a key, that same key must be set as `KC_TRNS` on the destination layer. Otherwise, you won't make it back to the original layer when you release the key (and you'll get a keycode sent). You can only switch to layers *above* your current layer. If you're on layer 0 and you use `MO(1)`, that will switch to layer 1 just fine. But if you include `MO(3)` on layer 5, that won't do anything for you -- because layer 3 is lower than layer 5 on the stack.

`OSL(layer)` - momentary switch to *layer*, as a one-shot operation. So if you have a key that's defined as `OSL(1)`, and you tap that key, then only the very next keystroke would come from layer 1. You would drop back to layer zero immediately after that one keystroke. That's handy if you have a layer full of custom shortcuts -- for example, a dedicated key for closing a window. So you tap your one-shot layer mod, then tap that magic 'close window' key, and keep typing like a boss. Layer 1 would remain active as long as you hold that key down, too (so you can use it like a momentary toggle-layer key with extra powers).

`LT(layer, kc)` - momentary switch to *layer* when held, and *kc* when tapped. Like `MO()`, this only works upwards in the layer stack (`layer` must be higher than the current layer).

`TG(layer)` - toggles a layer on or off. As with `MO()`, you should set this key as `KC_TRNS` in the destination layer so that tapping it again actually toggles back to the original layer. Only works upwards in the layer stack.


### Fun with modifier keys

* `LSFT(kc)` - applies left Shift to *kc* (keycode) - `S(kc)` is an alias
* `RSFT(kc)` - applies right Shift to *kc*
* `LCTL(kc)` - applies left Control to *kc*
* `RCTL(kc)` - applies right Control to *kc*
* `LALT(kc)` - applies left Alt to *kc*
* `RALT(kc)` - applies right Alt to *kc*
* `LGUI(kc)` - applies left GUI (command/win) to *kc*
* `RGUI(kc)` - applies right GUI (command/win) to *kc*
* `HYPR(kc)` - applies Hyper (all modifiers) to *kc*
* `MEH(kc)`  - applies Meh (all modifiers except Win/Cmd) to *kc*
* `LCAG(kc)` - applies CtrlAltGui to *kc*

You can also chain these, like this:

    LALT(LCTL(KC_DEL)) -- this makes a key that sends Alt, Control, and Delete in a single keypress.

The following shortcuts automatically add `LSFT()` to keycodes to get commonly used symbols. Their long names are also available and documented in `/quantum/keymap_common.h`.

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
    KC_DQUO  "
    KC_LCBR  {
    KC_RCBR  }
    KC_LABK  <
    KC_RABK  >
    KC_PIPE  |
    KC_COLN  :

`OSM(mod)` - this is a "one shot" modifier. So let's say you have your left Shift key defined as `OSM(MOD_LSFT)`. Tap it, let go, and Shift is "on" -- but only for the next character you'll type. So to write "The", you don't need to hold down Shift -- you tap it, tap t, and move on with life. And if you hold down the left Shift key, it just works as a left Shift key, as you would expect (so you could type THE). There's also a magical, secret way to "lock" a modifier by tapping it multiple times. If you want to learn more about that, open an issue. :)

`MT(mod, kc)` - is *mod* (modifier key - MOD_LCTL, MOD_LSFT) when held, and *kc* when tapped. In other words, you can have a key that sends Esc (or the letter O or whatever) when you tap it, but works as a Control key or a Shift key when you hold it down.

These are the values you can use for the `mod` in `MT()` and `OSM()` (right-hand modifiers are not available for `MT()`):

  * MOD_LCTL
  * MOD_LSFT
  * MOD_LALT
  * MOD_LGUI
  * MOD_HYPR
  * MOD_MEH

These can also be combined like `MOD_LCTL | MOD_LSFT` e.g. `MT(MOD_LCTL | MOD_LSFT, KC_ESC)` which would activate Control and Shift when held, and send Escape when tapped.

We've added shortcuts to make common modifier/tap (mod-tap) mappings more compact:

  * `CTL_T(kc)` - is LCTL when held and *kc* when tapped
  * `SFT_T(kc)` - is LSFT when held and *kc* when tapped
  * `ALT_T(kc)` - is LALT when held and *kc* when tapped
  * `GUI_T(kc)` - is LGUI when held and *kc* when tapped
  * `ALL_T(kc)` - is Hyper (all mods) when held and *kc* when tapped. To read more about what you can do with a Hyper key, see [this blog post by Brett Terpstra](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)
  * `LCAG_T(kc)` - is CtrlAltGui when held and *kc* when tapped
  * `MEH_T(kc)` - is like Hyper, but not as cool -- does not include the Cmd/Win key, so just sends Alt+Ctrl+Shift.

### Space Cadet Shift: The future, built in

Steve Losh [described](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) the Space Cadet Shift quite well. Essentially, you hit the left Shift on its own, and you get an opening parenthesis; hit the right Shift on its own, and you get the closing one. When hit with other keys, the Shift key keeps working as it always does. Yes, it's as cool as it sounds.

To use it, use `KC_LSPO` (Left Shift, Parens Open) for your left Shift on your keymap, and `KC_RSPC` (Right Shift, Parens Close) for your right Shift. 

It's defaulted to work on US keyboards, but if your layout uses different keys for parenthesis, you can define those in your `config.h` like this:

    #define LSPO_KEY KC_9
    #define RSPC_KEY KC_0

The only other thing you're going to want to do is create a `Makefile` in your keymap directory and set the following:

```
COMMAND_ENABLE   = no  # Commands for debug and configuration
```

This is just to keep the keyboard from going into command mode when you hold both Shift keys at the same time.

### The Leader key: A new kind of modifier

If you've ever used Vim, you know what a Leader key is. If not, you're about to discover a wonderful concept. :) Instead of hitting Alt+Shift+W for example (holding down three keys at the same time), what if you could hit a _sequence_ of keys instead? So you'd hit our special modifier (the Leader key), followed by W and then C (just a rapid succession of keys), and something would happen.

That's what `KC_LEAD` does. Here's an example:

1. Pick a key on your keyboard you want to use as the Leader key. Assign it the keycode `KC_LEAD`. This key would be dedicated just for this -- it's a single action key, can't be used for anything else.
2. Include the line `#define LEADER_TIMEOUT 300` somewhere in your keymap.c file, probably near the top. The 300 there is 300ms -- that's how long you have for the sequence of keys following the leader. You can tweak this value for comfort, of course.
3. Within your `matrix_scan_user` function, do something like this:

```
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      register_code(KC_S);
      unregister_code(KC_S);
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_H);
      unregister_code(KC_H);
    }
    SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
```

As you can see, you have three function. you can use - `SEQ_ONE_KEY` for single-key sequences (Leader followed by just one key), and `SEQ_TWO_KEYS` and `SEQ_THREE_KEYS` for longer sequences. Each of these accepts one or more keycodes as arguments. This is an important point: You can use keycodes from **any layer on your keyboard**. That layer would need to be active for the leader macro to fire, obviously.

### Temporarily setting the default layer

`DF(layer)` - sets default layer to *layer*. The default layer is the one at the "bottom" of the layer stack - the ultimate fallback layer. This currently does not persist over power loss. When you plug the keyboard back in, layer 0 will always be the default. It is theoretically possible to work around that, but that's not what `DF` does.

### Prevent stuck modifiers

Consider the following scenario:

1. Layer 0 has a key defined as Shift.
2. The same key is defined on layer 1 as the letter A.
3. User presses Shift.
4. User switches to layer 1 for whatever reason.
5. User releases Shift, or rather the letter A.
6. User switches back to layer 0.

Shift was actually never released and is still considered pressed.

If such situation bothers you add this to your `config.h`:

    #define PREVENT_STUCK_MODIFIERS

This option uses 5 bytes of memory per every 8 keys on the keyboard
rounded up (5 bits per key). For example on Planck (48 keys) it uses
(48/8)\*5 = 30 bytes.

### Remember: These are just aliases

These functions work the same way that their `ACTION_*` functions do - they're just quick aliases. To dig into all of the tmk ACTION_* functions, please see the [TMK documentation](https://github.com/jackhumbert/qmk_firmware/blob/master/doc/keymap.md#2-action).

Instead of using `FNx` when defining `ACTION_*` functions, you can use `F(x)` - the benefit here is being able to use more than 32 function actions (up to 4096), if you happen to need them.

## Macro shortcuts: Send a whole string when pressing just one key

Instead of using the `ACTION_MACRO` function, you can simply use `M(n)` to access macro *n* - *n* will get passed into the `action_get_macro` as the `id`, and you can use a switch statement to trigger it. This gets called on the keydown and keyup, so you'll need to use an if statement testing `record->event.pressed` (see keymap_default.c).

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
  }
  return MACRO_NONE;
};
```
A macro can include the following commands:

* I() change interval of stroke in milliseconds.
* D() press key.
* U() release key.
* T() type key(press and release).
* W() wait (milliseconds).
* END end mark.

So above you can see the stroke interval changed to 255ms between each keystroke, then a bunch of keys being typed, waits a while, then the macro ends.

Note: Using macros to have your keyboard send passwords for you is possible, but a bad idea.

### Advanced macro functions

To get more control over the keys/actions your keyboard takes, the following functions are available to you in the `action_get_macro` function block:

* `record->event.pressed`

This is a boolean value that can be tested to see if the switch is being pressed or released. An example of this is

```c
if (record->event.pressed) {
  // on keydown
} else {
  // on keyup
}
```

* `register_code(<kc>);`

This sends the `<kc>` keydown event to the computer. Some examples would be `KC_ESC`, `KC_C`, `KC_4`, and even modifiers such as `KC_LSFT` and `KC_LGUI`.

* `unregister_code(<kc>);`

Parallel to `register_code` function, this sends the `<kc>` keyup event to the computer. If you don't use this, the key will be held down until it's sent.

* `layer_on(<n>);`

This will turn on the layer `<n>` - the higher layer number will always take priority. Make sure you have `KC_TRNS` for the key you're pressing on the layer you're switching to, or you'll get stick there unless you have another plan.

* `layer_off(<n>);`

This will turn off the layer `<n>`.

* `clear_keyboard();`

This will clear all mods and keys currently pressed.

* `clear_mods();`

This will clear all mods currently pressed.

* `clear_keyboard_but_mods();`

This will clear all keys besides the mods currently pressed.

* `update_tri_layer(layer_1, layer_2, layer_3);`

If the user attempts to activate layer 1 AND layer 2 at the same time (for example, by hitting their respective layer keys), layer 3 will be activated. Layers 1 and 2 will _also_ be activated, for the purposes of fallbacks (so a given key will fall back from 3 to 2, to 1 -- and only then to 0).

#### Naming your macros

If you have a bunch of macros you want to refer to from your keymap, while keeping the keymap easily readable, you can just name them like so:

```
#define AUD_OFF M(6)
#define AUD_ON M(7)
#define MUS_OFF M(8)
#define MUS_ON M(9)
#define VC_IN M(10)
#define VC_DE M(11)
#define PLOVER M(12)
#define EXT_PLV M(13)
```

As was done on the [Planck default keymap](/keyboards/planck/keymaps/default/keymap.c#L33-L40)

#### Timer functionality

It's possible to start timers and read values for time-specific events - here's an example:

```c
static uint16_t key_timer;
key_timer = timer_read();
if (timer_elapsed(key_timer) < 100) {
  // do something if less than 100ms have passed
} else {
  // do something if 100ms or more have passed
}
```

It's best to declare the `static uint16_t key_timer;` outside of the macro block (top of file, etc).

#### Example: Single-key copy/paste (hold to copy, tap to paste)

With QMK, it's easy to make one key do two things, as long as one of those things is being a modifier. :) So if you want a key to act as Ctrl when held and send the letter R when tapped, that's easy: `CTL_T(KC_R)`. But what do you do when you want that key to send Ctrl-V (paste) when tapped, and Ctrl-C (copy) when held?

Here's what you do:


```
static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0: {
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LCTL), T(C), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LCTL), T(V), U(LCTL), END  );
                }
            }
            break;
        }
      }
    return MACRO_NONE;
};
```

And then, to assign this macro to a key on your keyboard layout, you just use `M(0)` on the key you want to press for copy/paste.

## Additional keycode aliases for software-implemented layouts (Colemak, Dvorak, etc)

Everything is assuming you're in Qwerty (in software) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

   #include <keymap_colemak.h>

If you use Dvorak, use `keymap_dvorak.h` instead of `keymap_colemak.h` for this line. After including this line, you will get access to:

 * `CM_*` for all of the Colemak-equivalent characters
 * `DV_*` for all of the Dvorak-equivalent characters

These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features.

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F` - `KC_F` under these same circumstances would result in `T`.

## Additional language support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbreviation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware (but it's being worked on - see Unicode support).

## Unicode support

You can currently send 4 hex digits with your OS-specific modifier key (RALT for OSX with the "Unicode Hex Input" layout) - this is currently limited to supporting one OS at a time, and requires a recompile for switching. 8 digit hex codes are being worked on. The keycode function is `UC(n)`, where *n* is a 4 digit hexidecimal. Enable from the Makefile.

## Other firmware shortcut keycodes

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

# Custom Quantum functions

All of these functions are available in the `*_kb()` or `*_user()` variety. `kb` ones should only be used in the `<keyboard>/<keyboard>.c` file, and `user` ones should only be used in the `keymap.c`. The keyboard ones call the user ones - it's necessary to keep these calls to allow the keymap functions to work correctly.

## `void martix_init_*(void)`

This function gets called when the matrix is initiated, and can contain start-up code for your keyboard/keymap.

## `void matrix_scan_*(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

## `bool process_record_*(uint16_t keycode, keyrecord_t *record)`

This function gets called on every keypress/release, and is where you can define custom functionality. The return value is whether or not QMK should continue processing the keycode - returning `false` stops the execution.

The `keycode` variable is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. and can be switch-cased to execute code whenever a particular code is pressed.

The `record` variable contains infomation about the actual press:

```
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

The conditional `if (record->event.pressed)` can tell if the key is being pressed or released, and you can execute code based on that.

## `void led_set_*(uint8_t usb_led)`

This gets called whenever there is a state change on your host LEDs (eg caps lock, scroll lock, etc). The LEDs are defined as:

```
#define USB_LED_NUM_LOCK                0
#define USB_LED_CAPS_LOCK               1
#define USB_LED_SCROLL_LOCK             2
#define USB_LED_COMPOSE                 3
#define USB_LED_KANA                    4
```

and can be tested against the `usb_led` with a conditional like `if (usb_led & (1<<USB_LED_CAPS_LOCK))` - if this is true, you can turn your LED one, otherwise turn it off.

# Modding your keyboard

## Audio output from a speaker

Your keyboard can make sounds! If you've got a Planck, Preonic, or basically any keyboard that allows access to the C6 port, you can hook up a simple speaker and make it beep. You can use those beeps to indicate layer transitions, modifiers, special keys, or just to play some funky 8bit tunes.

The audio code lives in [quantum/audio/audio.h](/quantum/audio/audio.h) and in the other files in the audio directory. It's enabled by default on the Planck [stock keymap](/keyboards/planck/keymaps/default/keymap.c). Here are the important bits:

```
#include "audio.h"
```

Then, lower down the file:

```
float tone_startup[][2] = {
    ED_NOTE(_E7 ),
    E__NOTE(_CS7),
    E__NOTE(_E6 ),
    E__NOTE(_A6 ),
    M__NOTE(_CS7, 20)
};
```

This is how you write a song. Each of these lines is a note, so we have a little ditty composed of five notes here.

Then, we have this chunk:

```
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);

float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
float goodbye[][2] = SONG(GOODBYE_SOUND);
```

Wherein we bind predefined songs (from [audio/song_list.h](/audio/song_list.h)) into named variables. This is one optimization that helps save on memory: These songs only take up memory when you reference them in your keymap, because they're essentially all preprocessor directives.

So now you have something called `tone_plover` for example. How do you make it play the Plover tune, then? If you look further down the keymap, you'll see this:

```
PLAY_NOTE_ARRAY(tone_plover, false, 0); // Signature is: Song name, repeat, rest style
```

This is inside one of the macros. So when that macro executes, your keyboard plays that particular chime.

"Rest style" in the method signature above (the last parameter) specifies if there's a rest (a moment of silence) between the notes.

## MIDI functionalty

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.

## Bluetooth functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

## International Characters on Windows

[AutoHotkey](https://autohotkey.com) allows Windows users to create custom hotkeys among others.

The method does not require Unicode support in the keyboard itself but depends instead of AutoHotkey running in the background.

First you need to select a modifier combination that is not in use by any of your programs.
CtrlAltWin is not used very widely and should therefore be perfect for this.
There is a macro defined for a mod-tab combo `LCAG_T`.
Add this mod-tab combo to a key on your keyboard, e.g.: `LCAG_T(KC_TAB)`.
This makes the key behave like a tab key if pressed and released immediately but changes it to the modifier if used with another key.

In the default script of AutoHotkey you can define custom hotkeys.

    <^<!<#a::Send, ä
    <^<!<#<+a::Send, Ä

The hotkeys above are for the combination CtrlAltGui and CtrlAltGuiShift plus the letter a.
AutoHotkey inserts the Text right of `Send, ` when this combination is pressed.

## RGB Under Glow Mod

![Planck with RGB Underglow](https://raw.githubusercontent.com/yangliu/qmk_firmware/planck-rgb/keyboards/planck/keymaps/yang/planck-with-rgb-underglow.jpg)

Here is a quick demo on Youtube (with NPKC KC60) (https://www.youtube.com/watch?v=VKrpPAHlisY).

For this mod, you need an unused pin wiring to DI of WS2812 strip. After wiring the VCC, GND, and DI, you can enable the underglow in your Makefile.

    RGBLIGHT_ENABLE = yes

Please note that the underglow is not compatible with audio output. So you cannot enable both of them at the same time.

Please add the following options into your config.h, and set them up according your hardware configuration. These settings are for the F4 by default:

    #define ws2812_PORTREG  PORTF
    #define ws2812_DDRREG   DDRF
    #define ws2812_pin PF4
    #define RGBLED_NUM 14     // Number of LEDs
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

You'll need to edit `PORTF`, `DDRF`, and `PF4` on the first three lines to the port/pin you have your LED(s) wired to, eg for B3 change things to:

    #define ws2812_PORTREG  PORTB
    #define ws2812_DDRREG   DDRB
    #define ws2812_pin PB3

The firmware supports 5 different light effects, and the color (hue, saturation, brightness) can be customized in most effects. To control the underglow, you need to modify your keymap file to assign those functions to some keys/key combinations. For details, please check this keymap. `keyboards/planck/keymaps/yang/keymap.c`

### WS2812 Wiring

![WS2812 Wiring](https://raw.githubusercontent.com/yangliu/qmk_firmware/planck-rgb/keyboards/planck/keymaps/yang/WS2812-wiring.jpg)

Please note the USB port can only supply a limited amount of power to the keyboard (500mA by standard, however, modern computer and most usb hubs can provide 700+mA.). According to the data of NeoPixel from Adafruit, 30 WS2812 LEDs require a 5V 1A power supply, LEDs used in this mod should not more than 20.

## Safety Considerations

You probably don't want to "brick" your keyboard, making it impossible
to rewrite firmware onto it.  Here are some of the parameters to show
what things are (and likely aren't) too risky.

- If a keyboard map does not include RESET, then, to get into DFU
  mode, you will need to press the reset button on the PCB, which
  requires unscrewing some bits.
- Messing with tmk_core / common files might make the keyboard
  inoperable
- Too large a .hex file is trouble; `make dfu` will erase the block,
  test the size (oops, wrong order!), which errors out, failing to
  flash the keyboard
- DFU tools do /not/ allow you to write into the bootloader (unless
  you throw in extra fruitsalad of options), so there is little risk
  there.
- EEPROM has around a 100000 write cycle.  You shouldn't rewrite the
  firmware repeatedly and continually; that'll burn the EEPROM
  eventually.

# Porting your keyboard to QMK

If your keyboard is running an Atmega chip (atmega32u4 and others), it's pretty easy to get things setup for compiling your own firmware to flash onto your board. There is a `/util/new_project.sh <keyboard>` script to help get you started - you can simply pass your keyboard's name into the script, and all of the necessary files will be created. The components of each are described below.

## `/keyboards/<keyboard>/config.h`

The `USB Device descriptor parameter` block contains parameters are used to uniquely identify your keyboard, but they don't really matter to the machine.

Your `MATRIX_ROWS` and `MATRIX_COLS` are the numbers of rows and cols in your keyboard matrix - this may be different than the number of actual rows and columns on your keyboard. There are some tricks you can pull to increase the number of keys in a given matrix, but most keyboards are pretty straight-forward. 

The `MATRIX_ROW_PINS` and `MATRIX_COL_PINS` are the pins your MCU uses on each row/column. Your schematic (if you have one) will have this information on it, and the values will vary depending on your setup. This is one of the most important things to double-check in getting your keyboard setup correctly.

For the `DIODE_DIRECTION`, most hand-wiring guides will instruct you to wire the diodes in the `COL2ROW` position, but it's possible that they are in the other - people coming from EasyAVR often use `ROW2COL`. Nothing will function if this is incorrect.

`BACKLIGHT_PIN` is the pin that your PWM-controlled backlight (if one exists) is hooked-up to. Currently only B5, B6, and B7 are supported. 

`BACKLIGHT_BREATHING` is a fancier backlight feature, and uses one of the timers.

`BACKLIGHT_LEVELS` is how many levels exist for your backlight - max is 15, and they are computed automatically from this number.

## `/keyboards/<keyboard>/Makefile`

The values at the top likely won't need to be changed, since most boards use the `atmega32u4` chip. The `BOOTLOADER_SIZE` will need to be adjusted based on your MCU type. It's defaulted to the Teensy, since that's the most common controller. Below is quoted from the `Makefile`.

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=512
```

At the bottom of the file, you'll find lots of features to turn on and off - all of these options should be set with `?=` to allow for the keymap overrides. `?=` only assigns if the variable was previously undefined. For the full documenation of these features, see the [Makefile options](#makefile-options).

## `/keyboards/<keyboard>/readme.md`

This is where you'll describe your keyboard - please write as much as you can about it! Talking about default functionality/features is useful here. Feel free to link to external pages/sites if necessary. Images can be included here as well. This file will be rendered into a webpage at qmk.fm/keyboards/<keyboard>/.

## `/keyboards/<keyboard>/<keyboard>.c`

This is where all of the custom logic for your keyboard goes - you may not need to put anything in this file, since a lot of things are configured automatically. All of the `*_kb()` functions are defined here. If you modify them, remember to keep the calls to `*_user()`, or things in the keymaps might not work. You can read more about the functions [here](#custom-quantum-functions-for-keyboards-and-keymaps)

## `/keyboards/<keyboard>/<keyboard>.h`

Here is where you can (optionally) define your `KEYMAP` function to remap your matrix into a more readable format. With ortholinear boards, this isn't always necessary, but it can help to accomodate the dead spots on your matrix, where there are keys that take up more than one space (2u, staggering, 6.25u, etc). The example shows the difference between the physical keys, and the matrix design:

```
#define KEYMAP( \
    k00, k01, k02, \
      k10,  k11   \
) \
{ \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

Each of the `kxx` variables needs to be unique, and usually follows the format `k<row><col>`. You can place `KC_NO` where your dead keys are in your matrix.

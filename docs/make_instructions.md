# More detailed make instruction

The full syntax of the `make` command is the following, but parts of the command can be left out if you run it from other directories than the `root` (as you might already have noticed by reading the simple instructions).

`<keyboard>-<subproject>-<keymap>-<target>`, where:

* `<keyboard>` is the name of the keyboard, for example `planck`
  * Use `allkb` to compile all keyboards
* `<subproject>` is the name of the subproject (revision or sub-model of the keyboard). For example, for Ergodox it can be `ez` or `infinity`, and for Planck `rev3` or `rev4`.
  * If the keyboard doesn't have any subprojects, it can be left out
  * To compile the default subproject, you can leave it out, or specify `defaultsp`
  * Use `allsp` to compile all subprojects
* `<keymap>` is the name of the keymap, for example `algernon`
  * Use `allkm` to compile all keymaps
* `<target>` will be explained in more detail below.

**Note:** When you leave some parts of the command out, you should also remove the dash (`-`).

As mentioned above, there are some shortcuts, when you are in a:

* `keyboard` folder, the command will automatically fill the `<keyboard>` part. So you only need to type `<subproject>-<keymap>-<target>`
* `subproject` folder, it will fill in both `<keyboard>` and `<subproject>`
* `keymap` folder, then `<keyboard>` and `<keymap>` will be filled in. If you need to specify the `<subproject>` use the following syntax `<subproject>-<target>`
  * Note in order to support this shortcut, the keymap needs its own Makefile (see the example [here](https://github.com/qmk/qmk_firmware/blob/master/doc/keymap_makefile_example.mk))
* `keymap` folder of a `subproject`, then everything except the `<target>` will be filled in

The `<target>` means the following
* If no target is given, then it's the same as `all` below
* `all` compiles the keyboard and generates a `<keyboard>_<keymap>.hex` file in whichever folder you run `make` from. These files are ignored by git, so don't worry about deleting them when committing/creating pull requests.
* `dfu`, `teensy` or `dfu-util`, compile and upload the firmware to the keyboard. If the compilation fails, then nothing will be uploaded. The programmer to use depends on the keyboard. For most keyboards it's `dfu`, but for Infinity keyboards you should use `dfu-util`, and `teensy` for standard Teensys. To find out which command you should use for your keyboard, check the keyboard specific readme. **Note** that some operating systems needs root access for these commands to work, so in that case you need to run for example `sudo make dfu`.
* `clean`, cleans the build output folders to make sure that everything is built from scratch. Run this before normal compilation if you have some unexplainable problems.

Some other targets are supported but, but not important enough to be documented here. Check the source code of the make files for more information.

You can also add extra options at the end of the make command line, after the target

* `make COLOR=false` - turns off color output
* `make SILENT=true` - turns off output besides errors/warnings
* `make VERBOSE=true` - outputs all of the gcc stuff (not interesting, unless you need to debug)
* `make EXTRAFLAGS=-E` - Preprocess the code without doing any compiling (useful if you are trying to debug #define commands)

The make command itself also has some additional options, type `make --help` for more information. The most useful is probably `-jx`, which specifies that you want to compile using more than one CPU, the `x` represents the number of CPUs that you want to use. Setting that can greatly reduce the compile times, especially if you are compiling many keyboards/keymaps. I usually set it to one less than the number of CPUs that I have, so that I have some left for doing other things while it's compiling. Note that not all operating systems and make versions supports that option.

Here are some examples commands

* `make allkb-allsp-allkm` builds everything (all keyboards, all subprojects, all keymaps). Running just `make` from the `root` will also run this.
* `make` from within a `keyboard` directory, is the same as `make keyboard-allsp-allkm`, which compiles all subprojects and keymaps of the keyboard. **NOTE** that this behaviour has changed. Previously it compiled just the default keymap.
* `make ergodox-infinity-algernon-clean` will clean the build output of the Ergodox Infinity keyboard. This example uses the full syntax and can be run from any folder with a `Makefile`
* `make dfu COLOR=false` from within a keymap folder, builds and uploads the keymap, but without color output.

## The `Makefile`

There are 5 different `make` and `Makefile` locations:

* root (`/`)
* keyboard (`/keyboards/<keyboard>/`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/`)
* subproject (`/keyboards/<keyboard>/<subproject>`)
* subproject keymap (`/keyboards/<keyboard>/<subproject>/keymaps/<keymap>`)

The root contains the code used to automatically figure out which keymap or keymaps to compile based on your current directory and commandline arguments. It's considered stable, and shouldn't be modified. The keyboard one will contain the MCU set-up and default settings for your keyboard, and shouldn't be modified unless you are the producer of that keyboard. The keymap Makefile can be modified by users, and is optional. It is included automatically if it exists. You can see an example [here](https://github.com/qmk/qmk_firmware/blob/master/doc/keymap_makefile_example.mk) - the last few lines are the most important. The settings you set here will override any defaults set in the keyboard Makefile. **The file is required if you want to run `make` in the keymap folder.**

For keyboards and subprojects, the make files are split in two parts `Makefile` and `rules.mk`. All settings can be found in the `rules.mk` file, while the `Makefile` is just there for support and including the root `Makefile`. Keymaps contain just one `Makefile` for simplicity.

### Makefile options

Set these variables to `no` to disable them, and `yes` to enable them.

`BOOTMAGIC_ENABLE`

This allows you to hold a key and the salt key (space by default) and have access to a various EEPROM settings that persist over power loss. It's advised you keep this disabled, as the settings are often changed by accident, and produce confusing results that makes it difficult to debug. It's one of the more common problems encountered in help sessions.

Consumes about 1000 bytes.

`MOUSEKEY_ENABLE`

This gives you control over cursor movements and clicks via keycodes/custom functions.

`EXTRAKEY_ENABLE`

This allows you to use the system and audio control key codes.

`CONSOLE_ENABLE`

This allows you to print messages that can be read using [`hid_listen`](https://www.pjrc.com/teensy/hid_listen.html). 

By default, all debug (*dprint*) print (*print*, *xprintf*), and user print (*uprint*) messages will be enabled. This will eat up a significant portion of the flash and may make the keyboard .hex file too big to program. 

To disable debug messages (*dprint*) and reduce the .hex file size, include `#define NO_DEBUG` in your `config.h` file.

To disable print messages (*print*, *xprintf*) and user print messages (*uprint*) and reduce the .hex file size, include `#define NO_PRINT` in your `config.h` file.

To disable print messages (*print*, *xprintf*) and **KEEP** user print messages (*uprint*), include `#define USER_PRINT` in your `config.h` file.

To see the text, open `hid_listen` and enjoy looking at your printed messages.

**NOTE:** Do not include *uprint* messages in anything other than your keymap code. It must not be used within the QMK system framework. Otherwise, you will bloat other people's .hex files. 

Consumes about 400 bytes.

`COMMAND_ENABLE`

This enables magic commands, typically fired with the default magic key combo `LSHIFT+RSHIFT+KEY`. Magic commands include turning on debugging messages (`MAGIC+D`) or temporarily toggling NKRO (`MAGIC+N`).

`SLEEP_LED_ENABLE`

Enables your LED to breath while your computer is sleeping. Timer1 is being used here. This feature is largely unused and untested, and needs updating/abstracting.

`NKRO_ENABLE`

This allows the keyboard to tell the host OS that up to 248 keys are held down at once (default without NKRO is 6). NKRO is off by default, even if `NKRO_ENABLE` is set. NKRO can be forced by adding `#define FORCE_NKRO` to your config.h or by binding `MAGIC_TOGGLE_NKRO` to a key and then hitting the key.

`BACKLIGHT_ENABLE`

This enables your backlight on Timer1 and ports B5, B6, or B7 (for now). You can specify your port by putting this in your `config.h`:

    #define BACKLIGHT_PIN B7

`MIDI_ENABLE`

This enables MIDI sending and receiving with your keyboard. To enter MIDI send mode, you can use the keycode `MI_ON`, and `MI_OFF` to turn it off. This is a largely untested feature, but more information can be found in the `quantum/quantum.c` file.

`UNICODE_ENABLE`

This allows you to send unicode symbols via `UC(<unicode>)` in your keymap. Only codes up to 0x7FFF are currently supported.

`UNICODEMAP_ENABLE`

This allows sending unicode symbols using `X(<unicode>)` in your keymap. Codes
up to 0xFFFFFFFF are supported, including emojis. You will need to maintain
a separate mapping table in your keymap file.

Known limitations:
- Under Mac OS, only codes up to 0xFFFF are supported.
- Under Linux ibus, only codes up to 0xFFFFF are supported (but anything important is still under this limit for now).

Characters out of range supported by the OS will be ignored.

`BLUETOOTH_ENABLE`

This allows you to interface with a Bluefruit EZ-key to send keycodes wirelessly. It uses the D2 and D3 pins.

`AUDIO_ENABLE`

This allows you output audio on the C6 pin (needs abstracting). See the [audio section](#audio-output-from-a-speaker) for more information.

`FAUXCLICKY_ENABLE`

Uses buzzer to emulate clicky switches. A cheap imitation of the Cherry blue switches. By default, uses the C6 pin, same as AUDIO_ENABLE.

`VARIABLE_TRACE`

Use this to debug changes to variable values, see the [tracing variables](#tracing-variables) section for more information.

`API_SYSEX_ENABLE`

This enables using the Quantum SYSEX API to send strings (somewhere?)

This consumes about 5390 bytes.

### Customizing Makefile options on a per-keymap basis

If your keymap directory has a file called `Makefile` (note the filename), any Makefile options you set in that file will take precedence over other Makefile options for your particular keyboard.

So let's say your keyboard's makefile has `BACKLIGHT_ENABLE = yes` (or maybe doesn't even list the `BACKLIGHT_ENABLE` option, which would cause it to be off). You want your particular keymap to not have the debug console, so you make a file called `Makefile` and specify `BACKLIGHT_ENABLE = no`.

You can use the `docs/keymap_makefile_example.md` as a template/starting point.

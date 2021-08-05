# More Detailed `make` Instructions

The full syntax of the `make` command is `<keyboard_folder>:<keymap>:<target>`, where:

* `<keyboard_folder>` is the path of the keyboard, for example `planck`
  * Use `all` to compile all keyboards
  * Specify the path to compile a revision, for example `planck/rev4` or `planck/rev3`
  * If the keyboard doesn't have any folders, it can be left out
  * To compile the default folder, you can leave it out
* `<keymap>` is the name of the keymap, for example `algernon`
  * Use `all` to compile all keymaps
* `<target>` will be explained in more detail below.

The `<target>` means the following
* If no target is given, then it's the same as `all` below
* `all` compiles as many keyboard/revision/keymap combinations as specified. For example, `make planck/rev4:default` will generate a single .hex, while `make planck/rev4:all` will generate a hex for every keymap available to the planck.
* `flash`, `dfu`, `teensy`, `avrdude`, `dfu-util`, or `bootloadHID` compile and upload the firmware to the keyboard. If the compilation fails, then nothing will be uploaded. The programmer to use depends on the keyboard. For most keyboards it's `dfu`, but for ChibiOS keyboards you should use `dfu-util`, and `teensy` for standard Teensys. To find out which command you should use for your keyboard, check the keyboard specific readme. 
  Visit the [Flashing Firmware](flashing.md) guide for more details of the available bootloaders.
  * **Note**: some operating systems need privileged access for these commands to work. This means that you may need to setup [`udev rules`](faq_build.md#linux-udev-rules) to access these without root access, or to run the command with root access (`sudo make planck/rev4:default:flash`).
* `clean`, cleans the build output folders to make sure that everything is built from scratch. Run this before normal compilation if you have some unexplainable problems.
* `distclean` removes .hex files and .bin files.

The following targets are for developers:

* `show_path` shows the path of the source and object files.
* `dump_vars` dumps the makefile variable.
* `objs-size` displays the size of individual object files.
* `show_build_options` shows the options set in 'rules.mk'.
* `check-md5` displays the md5 checksum of the generated binary file.

You can also add extra options at the end of the make command line, after the target

* `make COLOR=false` - turns off color output
* `make SILENT=true` - turns off output besides errors/warnings
* `make VERBOSE=true` - outputs all of the gcc stuff (not interesting, unless you need to debug)
* `make VERBOSE_LD_CMD=yes` - execute the ld command with the -v option.
* `make VERBOSE_AS_CMD=yes` - execute the as command with the -v option.
* `make VERBOSE_C_CMD=<c_source_file>` - add the -v option when compiling the specified C source file.
* `make DUMP_C_MACROS=<c_source_file>` - dump preprocessor macros when compiling the specified C source file.
* `make DUMP_C_MACROS=<c_source_file> > <logfile>` - dump preprocessor macros to `<logfile>` when compiling the specified C source file.
* `make VERBOSE_C_INCLUDE=<c_source_file>` - dumps the file names to be included when compiling the specified C source file.
* `make VERBOSE_C_INCLUDE=<c_source_file> 2> <logfile>` - dumps the file names to be included to `<logfile>` when compiling the specified C source file.

The make command itself also has some additional options, type `make --help` for more information. The most useful is probably `-jx`, which specifies that you want to compile using more than one CPU, the `x` represents the number of CPUs that you want to use. Setting that can greatly reduce the compile times, especially if you are compiling many keyboards/keymaps. I usually set it to one less than the number of CPUs that I have, so that I have some left for doing other things while it's compiling. Note that not all operating systems and make versions supports that option.

Here are some examples commands

* `make all:all` builds everything (all keyboard folders, all keymaps). Running just `make` from the `root` will also run this.
* `make ergodox_infinity:algernon:clean` will clean the build output of the Ergodox Infinity keyboard.
* `make planck/rev4:default:flash COLOR=false` builds and uploads the keymap without color output.

## `rules.mk` Options

Set these variables to `no` to disable them, and `yes` to enable them.

`BOOTMAGIC_ENABLE`

This allows you to hold a key and the salt key (space by default) and have access to a various EEPROM settings that persist over power loss. It's advised you keep this disabled, as the settings are often changed by accident, and produce confusing results that makes it difficult to debug. It's one of the more common problems encountered in help sessions.

`MOUSEKEY_ENABLE`

This gives you control over cursor movements and clicks via keycodes/custom functions.

`EXTRAKEY_ENABLE`

This allows you to use the system and audio control key codes.

`CONSOLE_ENABLE`

This allows you to print messages that can be read using [`hid_listen`](https://www.pjrc.com/teensy/hid_listen.html).

By default, all debug (*dprint*) print (*print*, *xprintf*), and user print (*uprint*) messages will be enabled. This will eat up a significant portion of the flash and may make the keyboard .hex file too big to program.

To disable debug messages (*dprint*) and reduce the .hex file size, include `#define NO_DEBUG` in your `config.h` file.

To disable print messages (*print*, *xprintf*) and user print messages (*uprint*) and reduce the .hex file size, include `#define NO_PRINT` in your `config.h` file.

To disable print messages (*print*, *xprintf*) and **KEEP** user print messages (*uprint*), include `#define USER_PRINT` in your `config.h` file (do not also include `#define NO_PRINT` in this case).

To see the text, open `hid_listen` and enjoy looking at your printed messages.

**NOTE:** Do not include *uprint* messages in anything other than your keymap code. It must not be used within the QMK system framework. Otherwise, you will bloat other people's .hex files.

`COMMAND_ENABLE`

This enables magic commands, typically fired with the default magic key combo `LSHIFT+RSHIFT+KEY`. Magic commands include turning on debugging messages (`MAGIC+D`) or temporarily toggling NKRO (`MAGIC+N`).

`SLEEP_LED_ENABLE`

Enables your LED to breath while your computer is sleeping. Timer1 is being used here. This feature is largely unused and untested, and needs updating/abstracting.

`NKRO_ENABLE`

This allows the keyboard to tell the host OS that up to 248 keys are held down at once (default without NKRO is 6). NKRO is off by default, even if `NKRO_ENABLE` is set. NKRO can be forced by adding `#define FORCE_NKRO` to your config.h or by binding `MAGIC_TOGGLE_NKRO` to a key and then hitting the key.

`BACKLIGHT_ENABLE`

This enables the in-switch LED backlighting. You can specify the backlight pin by putting this in your `config.h`:

    #define BACKLIGHT_PIN B7

`MIDI_ENABLE`

This enables MIDI sending and receiving with your keyboard. To enter MIDI send mode, you can use the keycode `MI_ON`, and `MI_OFF` to turn it off. This is a largely untested feature, but more information can be found in the `quantum/quantum.c` file.

`UNICODE_ENABLE`

This allows you to send Unicode characters using `UC(<code point>)` in your keymap. Code points up to `0x7FFF` are supported. This covers characters for most modern languages, as well as symbols, but it doesn't cover emoji.

`UNICODEMAP_ENABLE`

This allows you to send Unicode characters using `X(<map index>)` in your keymap. You will need to maintain a mapping table in your keymap file. All possible code points (up to `0x10FFFF`) are supported.

`UCIS_ENABLE`

This allows you to send Unicode characters by inputting a mnemonic corresponding to the character you want to send. You will need to maintain a mapping table in your keymap file. All possible code points (up to `0x10FFFF`) are supported.

For further details, as well as limitations, see the [Unicode page](feature_unicode.md).

`AUDIO_ENABLE`

This allows you output audio on the C6 pin (needs abstracting). See the [audio page](feature_audio.md) for more information.

`VARIABLE_TRACE`

Use this to debug changes to variable values, see the [tracing variables](unit_testing.md#tracing-variables) section of the Unit Testing page for more information.

`API_SYSEX_ENABLE`

This enables using the Quantum SYSEX API to send strings (somewhere?)

`KEY_LOCK_ENABLE`

This enables [key lock](feature_key_lock.md).

`SPLIT_KEYBOARD`

This enables split keyboard support (dual MCU like the let's split and bakingpy's boards) and includes all necessary files located at quantum/split_common

`SPLIT_TRANSPORT`

As there is no standard split communication driver for ARM-based split keyboards yet, `SPLIT_TRANSPORT = custom` must be used for these. It will prevent the standard split keyboard communication code (which is AVR-specific) from being included, allowing a custom implementation to be used.

`CUSTOM_MATRIX`

Lets you replace the default matrix scanning routine with your own code. For further details, see the [Custom Matrix page](custom_matrix.md).

`DEBOUNCE_TYPE`

Lets you replace the default key debouncing routine with an alternative one. If `custom` you will need to provide your own implementation.

## Customizing Makefile Options on a Per-Keymap Basis

If your keymap directory has a file called `rules.mk` any options you set in that file will take precedence over other `rules.mk` options for your particular keyboard.

So let's say your keyboard's `rules.mk` has `BACKLIGHT_ENABLE = yes`. You want your particular keyboard to not have the backlight, so you make a file called `rules.mk` and specify `BACKLIGHT_ENABLE = no`.

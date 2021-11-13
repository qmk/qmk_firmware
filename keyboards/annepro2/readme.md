# Anne Pro 2 rev. C15 and C18 QMK firmware

## Introduction

This is the QMK firmware repository for the Anne Pro 2 rev. C15 and C18 keyboard.

## Layouts

Keyboard has 60% ANSI standard layout.

## How to compile

After setting up your build environment, you can compile the Anne Pro 2 C18 default keymap by using:

    make annepro2/c18:default

If you want to compile the Anne Pro 2 C15 default keymap use:

    make annepro2/c15:default

## Installing

### Get AnnePro2 Tools

If you want the executable instead of compiling it yourself, [download it here](https://ci.codetector.org/job/OpenAnnePro/job/AnnePro2-Tools/job/master/).
Windows and Linux versions are available. Otherwise, follow the steps below:

0. Install the latest stable `rust` toolchain using [rustup](https://rustup.rs/)
0. Also install [Visual Studio Community edition](https://visualstudio.microsoft.com/downloads/)
including the C/C++ module to prevent errors while compiling
0. Download or Clone the [AnnePro2-Tools](https://github.com/OpenAnnePro/AnnePro2-Tools) project.
0. Compile the tool using
```bash
cargo build --release
```
0. The compiled tool should be in `./target/release/annepro2_tools` (In later I will refer to this as `annepro2_tools`)

### Flashing the firmware
0. Put the keyboard into DFU/IAP mode by unplugging the keyboard, then holding ESC while plugging it back in.
0. Run annepro2_tools with the firmware you just built.

**Please substitute with the correct paths and correct bin file if you chose another keymap profile**
```bash
annepro2_tools annepro2_c15_default.bin
```

If the tool can't find the keyboard please double check you have the keyboard in IAP mode.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
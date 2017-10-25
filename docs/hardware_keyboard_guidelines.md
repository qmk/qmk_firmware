# QMK Keyboard Guidelines

We welcome all keyboard projects into QMK, but ask that you try to stick to a couple guidelines that help us keep things organised and consistent.

## Naming your keyboard/project

All names should be lowercase alphanumeric, and separated by an underscore (`_`), but not begin with one. Your directory and your `.h` and `.c` files should have exactly the same name. All folders should follow the same format.

## `readme.md`

All projects need to have a `readme.md` file that explains what the keyboard is, who made it, where it is available, and links to more information. Please follow the [published template](documentation_templates.md#keyboard-readmemd-template).

## Image/Hardware files

In an effort to keep the repo size down, we're no longer accepting images of any format in the repo, with few exceptions. Hosting them elsewhere (imgur) and linking them in the `readme.md` is the preferred method.

Any sort of hardware file (plate, case, pcb) can't be stored in qmk_firmware, but we have the [qmk.fm repo](https://github.com/qmk/qmk.fm) where such files (as well as in-depth info) can be stored and viewed on [qmk.fm](http://qmk.fm). Downloadable files are stored in `/<keyboard>/` (name follows the same format as above) which are served at `http://qmk.fm/<keyboard>/`, and pages are generated from `/_pages/<keyboard>/` which are served at the same location (.md files are generated into .html files through Jekyll). Check out the `lets_split` directory for an example.

## Non-production/handwired projects

We're happy to accept any project that uses QMK, including prototypes and handwired ones, but we have a separate `/keyboards/handwired/` folder for them, so the main `/keyboards/` folder doesn't get overcrowded. If a prototype project becomes a production project at some point in the future, we'd be happy to move it to the main `/keyboards/` folder!

## Warnings as errors

When developing your keyboard, keep in mind that all warnings will be treated as errors - these small warnings can build-up and cause larger errors down the road (and keeping them is generally a bad practice).

## Copyright Blurb

If you're adapting your keyboard's setup from another project, but not using the same code, but sure to update the copyright header at the top of the files to show your name, in this format:

    Copyright 2017 Your Name <your@email.com>

If you are modifying someone else's code and have made only trivial changes you should leave their name in the copyright statement. If you have done significant work on the file you should add your name to theirs, like so:

    Copyright 2017 Their Name <original_author@example.com> Your Name <you@example.com>

The year should be the first year the file is created. If work was done to that file in later years you can reflect that by appending the second year to the first, like so:

    Copyright 2015-2017 Your Name <you@example.com>

## License

The core of QMK is licensed under the [GNU General Public License](https://www.gnu.org/licenses/licenses.en.html). If you are shipping binaries for AVR processors you may choose either [GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) or [GPLv3](https://www.gnu.org/licenses/gpl.html). If you are shipping binaries for ARM processors you must choose [GPL Version 3](https://www.gnu.org/licenses/gpl.html) to comply with the [ChibiOS](http://www.chibios.org) GPLv3 license.

If your keyboard makes use of the [uGFX](https://ugfx.io) features within QMK you must comply with the [uGFX License](https://ugfx.io/license.html), which requires a separate commercial license before selling a device containing uGFX.

## Technical details

If you're looking for more information on making your keyboard work with QMK, [check out the hardware section](hardware.md)!

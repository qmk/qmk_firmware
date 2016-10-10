Clueboard keyboard firmware
======================

DIY/Assembled compact 66% keyboard by [Clueboard](http://clueboard.co).

For the full Quantum Mechanical Keyboard feature list, see [the parent readme.md](/readme.md).

## First Time Setup

Download or clone the whole firmware and navigate to the keyboards/clueboard directory. Once your dev env is setup, you'll be able to generate the default .hex:

```
$ make
```

You will see a lot of output and if everything worked correctly you will see something similar to this:

```
Size after:
   text	   data	    bss	    dec	    hex	filename
      0	  19992	      0	  19992	   4e18	clueboard_rev2_default.hex
```

At this point you can press RESET on your Clueboard and flash your keyboard with this command:

```
$ make dfu
```

If you would like to use one of the alternative keymaps, or create your own, see below.

## Clueboard 1.0

If you have a first generation Clueboard (one with a black PCB) you will need to use the revision 1 code. To do so add `rev1` to your make command, like this:

```
$ make rev1
```

And when flashing your keyboard:

```
$ make rev1-dfu
```

If you are flashing an alternative layout to your rev1, include both `rev1` and `<keymap>` in your command, for example when flashing max:

```
$ make rev1-max-dfu
```

## Alternate Keymaps

There are many alternative and user-contributed layouts available in the [keymaps/](keymaps/) directory. To compile and flash an alternative you will want to add `<keymap>` to your command:

```
$ make skully
```

And when flashing your keyboard, put `<keymap>` between "make" and "dfu":

```
$ make skully-dfu
```

### Notable Layouts

These layouts are notable for one reason or another. If you are looking for ideas or inspiration you should look at these first:

* [keymaps/default](keymaps/default) - The default Clueboard layout
* [keymaps/max](keymaps/max) - A maximised layout that makes use of every key and feature of the Clueboard 2.0 PCB.
* [keymaps/skully](keymaps/skully) - The layout that @skullydazed uses on his own Clueboards.

## Create Your Own Keymap

There are a lot of possibilities when creating your own keymap, and the primary documentation for doing that is [Customizing Your Keymap](/readme.md##customizing-your-keymap) in the main readme.md. As a way to get started, here is the procedure I recommend:

* Copy `[keymaps/default](keymaps/default/)` to `keymaps/<your_layout>`.
* Compile the firmware (`$ make <your_layout>`)
* Flash the firmware (`$ make <your_layout>-dfu`)
* Make sure everything works like the default keyboard
* Modify `keymaps/<your_layout>/readme.md` to tell others about your layout.
* Modify `keymaps/<your_layout>/keymap.c` to reflect your desired layout.
* Compile your new custom firmware (`$ make <your_layout>`)
** If you have warnings you may flash without fixing them, but something may not work right.
** If you have any errors you must fix them before continuing.
* Flash the firmware (`$ make <your_layout>-dfu`)

## Share Your Keymap

Got your layout dialed in? Please share it with the world so we can benefit from your work! Simply submit a pull request with your layout and we'll include it in the official repository. Please use the following guidelines when putting together your pull request:

* Include a readme.md that states what your primary keyboard use is, how your layout differs from the default, and highlights anything you think makes your layout particularly great.
* If your layout requires certain features (EG, RGB underlight or backlighting) ensure you have a Makefile and config.h that reflects that
* If your layout requires special hardware to be added, please describe that in the readme.md

TODO: Write up or link quick how-to on creating and submitting a PR. (Pull requests accepted. :)

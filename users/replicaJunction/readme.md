replicaJunction QMK Userspace
=============================

# Overview
I alternate between a few keyboards, one of which is the 44-key Keyboardio Atreus. Small keyboards require a liberal use of layers. Even though larger keyboards don't rely on layers as heavily, my muscle memory adapted to my Atreus layout, so I've ended up building several of those features in my keymaps for larger boards as well.

The result, I believe, is a good compromise between ergonomics and ease of use.

The code in this userspace is designed to be very modular. I use a few different keyboards, and I'm constantly tweaking one or another, so I want the ability to add and remove features from the firmware at compile-time. While my endgame goal is to get all the layouts to be compatible, in practice, it's been years and I'm still not to that point...

Modular code also means that it should be easy to identify and adapt specific pieces to your own firmware.

## Keyboards and Keymaps

The following keyboards use the files in this userspace:

* [Atreus](../../keyboards/atreus/keymaps/replicaJunction/readme.md) (42-key)
* [Ergodox](../../layouts/community/ergodox/replicaJunction/readme.md)
* [Keyboardio Atreus](../../keyboards/keyboardio/atreus/keymaps/replicaJunction/readme.md) (44-key)
* [XD75](../../keyboards/xd75/keymaps/replicaJunction/readme.md)

# Features

* **Secrets**, as [explained by Drashna](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme_secrets.md)
* **CAPSWORD** and **NUMWORD**
* Mouse jiggler
* Super alt-tab

## Secrets
My implementation of the "secrets" concept is very similar to Drashna's, but I've chosen to allow most of the supporting code to be committed to the repo. The only thing missing is a file called `secret_definitions.h`, which contains the actual text contained in those macros.

To use my implementation, create a file of that name in the same directory. Make sure you've got a `.gitignore` file in place, and add these contents to the definitions file:

```c
#pragma once
static const char * const secrets[] = {
  "secret1",
  "secret2",
  "secret3",
  "secret4"
}
```

Change the quoted text to the text you'd like and you're golden. If you need more (or fewer) items, you'll probably need to adjust the code in `secrets.c` as well, since it looks for up to four items in a switch case. 

## CAPSWORD and NUMWORD
The concept here is simple: more often than you'd think, you need to type a single word in ALL CAPS. An easy example for me, as a programmer, is a constant value; in most programming languages, constants are typed in all caps by convention.

You typically have a few choices, but each one comes with a drawback. Here are the options I'm aware of:

* Use proper typing technique and alternate which hand holds Shift for each keypress
    * This can often end up requiring you to switch / re-press Shift again and again, making this a tedious process
* Hold a single Shift key down
    * This can lead to uncomfortable finger gymnastics
* Hit the Caps Lock key, then hit it again when you're done
    * Requires you to remember to hit it again, meaning a higher cognitive load
    * In some layouts for smaller keyboards, Caps Lock is not easily accessible (sometimes not mapped at all)
    
The solution to this problem is CAPSWORD. When enabled, it activates Caps Lock and begins running an additional callback on each keypress. If the keypress is an alphanumeric key or one of a specific few symbols (such as the underscore), nothing happens. Otherwise, before processing the keypress, Caps Lock is disabled again.

NUMWORD is a similar concept, but has a slightly more elaborate implementation. There's a bit of extra logic in the NUMWORD code that allows the keycode to act as a tap/hold key as well. Tapping enables NUMWORD while number keys are in use, while holding the key enables a number layer for the duration of the key hold and disables it again afterwards.

**Note:** The implementation of NUMWORD requires that the keyboard's layer definitions be accessible in a header file. In my case, since I use a fairly standard set of layers, I've declared it in my userspace.

## Mouse Jiggler
This adds a keycode that will move the mouse cursor on each matrix scan. Used to prevent the screen from locking if you're temporarily doing something else (working on a different machine, reading / writing, etc.).

When you press the keycode, the keyboard will write the text "Mouse jiggler enabled" to signify that the behavior is active. I suggest opening a Notepad window before pressing the key.

Pressing any key will automatically disable the feature again. This is because it causes a huge hit to the reliability and performance of the keyboard while it's active (adding stuff to every matrix scan will do that). I kept forgetting to turn it off before trying to use the keyboard again, so I decided to make it automatically disable itself.

Enable this by setting `USER_MOUSE_JIGGLE_ENABLE = yes` in your `rules.mk` file. The feature also depends on the Mouse Keys feature, so ensure you don't disable `MOUSEKEY_ENABLE`.

## Super Alt-Tab
Taken [straight out of the QMK documentation](https://docs.qmk.fm/#/feature_macros?id=super-alt%E2%86%AFtab), this is an easy way to shift between a couple different windows. I use it with a very low interval when I'm alternating back and forth between two known windows with no real need for the visual feedback and thought. If you want to be able to browse the open windows before the function releases Alt, I'd suggest raising `USER_SUPER_ALT_TAB_TIMEOUT` to a higher value.

# Credits
I'm absolutely sure I've missed a few sources here. If you see something in my code that you think is yours and isn't credited here, I sincerely apologize.

[bpruitt-goddard](https://github.com/qmk/qmk_firmware/blob/master/keyboards/ergodox_ez/keymaps/bpruitt-goddard/readme.md)
* Dynamic macro tap-dance (no longer used, but I did use this for a while)

[Drashna](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme.md)
* Secrets concept and basic implementation
* "Wrappers" concept (no longer used, but I did use this for a while)

[Treeman](https://github.com/treeman/qmk_firmware/blob/master/keyboards/kyria/keymaps/treeman)
* CAPSWORD and NUMBERWORD concept
    * I re-implented some of the code based on my own prefences, but I did use some implementation code from here
    * [Treeman's blog post](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/) provides more context on these features, and is a great read

[QMK issue #452](https://github.com/qmk/qmk_firmware/issues/452)
* Helped clarify a good organizational structure for the individual features in this userspace

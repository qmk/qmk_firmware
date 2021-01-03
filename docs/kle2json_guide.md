# KLE To info.json

This page describes how to create a [Keyboard Layout Editor](http://keyboard-layout-editor.com) layout that works with `qmk kle2json`. You will also be able to use the same KLE layout to create VIA support for your keyboard.

## Overview

QMK uses `info.json` to store metadata about the keyboard including the matrix pins, row and column configuration, and keyboard layout. You can encode some of this data into a KLE layout and then convert that to `info.json`, which saves you time and headaches creating files from scratch.

Our reference layout is here: <http://www.keyboard-layout-editor.com/#/gists/70aaa4bed76d0b2f67fd165641239552>

Keep that open in a separate window so that you can refer to it while reading this document.

## Layout Structure

The first thing you should notice is that the main layout for the keyboard is in the middle. This is the default layout. Around the sides you'll find layout options. These are groups of keys that can replace specific keys in the default layout. More on that later.

## Anatomy of a Key

Every key in KLE has 12 labels- top left, top center, top right, center left, center, center right, bottom left, bottom center, bottom right, front left, front center, front right. We do not use all 12 labels, but we do some of them.

The labels we use are below:

| | | |
|-|-|-|
| **Matrix** | (unused) | (unused) |
| **Keycode** | (unused) | (unused) |
| (unused) | (unused) | **Option Group** |
| **Option Name** | (unused) | (unused) |

### Matrix

This is the location of the key in the keyboard matrix. It should be two whole numbers separated by a comma representing row and column. For example, the top left location of the keyboard is usually `0,0`, to the right of that key is `0,1`, below that key is `1,0`, and so on.

### Keycode

This is the default keycode for layer 0. You should supply this now even if you won't use the generated keymap because QMK will make greater use of it in the future.

### Option Group

This identifies what Layout Options (if any) this key is part of. If this value is empty the key is not part of any Layout Options.

The value is two whole numbers separated by a comma. The first number is the Layout Option Group Number, which identifies the specific Layout Option this key is associated with. The second number is the specific Layout Option Choice this key is associated with.

### Option Name

This identifies the name for each Option Group Choice. This will be used in the future to automatically build layouts from each option. All keys with the same Option Group identifier should have the same Option Name.

## Running qmk kle2json

Once you have built your KLE layout you are ready to convert it to `info.json`. Start by clicking `Sign In with GitHub` on Keyboard Layout Editor. Once you have signed in you can click `Save` to save your KLE. Once it's saved grab the URL from the bar, it should end end in `/#/gists/<long_number>`.

To use the reference layout as an example, I could update the keyboard `clueboard/60` from that KLE using this command:

```shell
qmk kle2json -kb clueboard/60 -l LAYOUT_60_ansi 'http://www.keyboard-layout-editor.com/#/gists/70aaa4bed76d0b2f67fd165641239552'
```

It will fetch the KLE, generate a new `LAYOUT_60_ansi`, and either add a new layout or change the existing layout to match.

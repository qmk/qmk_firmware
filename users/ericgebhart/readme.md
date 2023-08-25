Overview
========

This is as much a keymap framework as it is a keymap. It can take many
shapes with just a few configuration choices. Base layers, Mods, thumb clusters, 
edge_keys, all can be changed with just a configuration option.
There are over 50 base layouts to choose from, as well as multiple 
choices of navigation, mouse, media, 
symbols, and keypads. Home row mods come in a few flavors or none,
in a mod layer which is easily understandable and can be turned on
or off, or switched. There are Miryoku options for everything if
that is your thing.

If there is a oled of 64x128 the maps of each layer will be displayed, which
helps a lot in remembering and learning.

This is an easily configurable keymap for keymap exploration. It is for
primarily for minimalist, ortho split keyboards but does support some rectangles.
It´s first keyboard was an Ergodox-ez many years ago. My daily driver
is now a Kyria or a Corne, but I still use an original dactyl, rebound 
and ergodox-ez regularly although most of the love goes to the Kyria and Corne.

The framework is Language
agnostic, it supports having layers for different locales which can be
cycled through.
There are multiple mods layers to choose or
not, home row mods or not, a variety of thumb layouts, mouse/no mouse,
smart lock layers and mods, N-Shot mods like callum's, swapper. Combos,
tap_hold, accented keys, alternate shifted keys, automatic custom
keys, key overrides. Minimal or no C-code required for most things. 
Language, mods, layouts and extensions are encapsulated, so that they 
do not interact in the configuration which makes it much easier to modify 
and grow. Mods and combos are by key location rather than specific key codes.

Quick start
-------------

Everything is encapsulated here. Base layers, functional layers, mods,
or no mods, even the language. This means that anything can change 
independently and easily.

If you don't mind dvorak, beakl or hands down, you can probably 
just use what is configured. Or just change it to a base layer
of your choice. The fastest way to get started is to just change
the base layers to the ones you want, compile and flash. 

Edit _config.h_,
  * Set the lang_is, probably to EN.
    * US international and BEPO are also supported out of the box.
  * Uncomment the base layers you wish to have.
    * comment the ones you don't.
    * keep the number below 5 if you enable a second locale.
  * Set the thumb clusters
  * Choose a mod layer
  * Choose an edge key set if you need one.
  * Choose the layer flavors that you want.
  * For Miryoku, copy the `miryoku_hd_gold_config.h` over `config.h`
    It is a complete config with miryoku choices. Choose the base
    layers you wish if Hands Down Gold and Qwerty is not your thing.
  
  ** do not turn off extensions until you know them **
  It will likely cause a stream of errors for the keycodes that
  go missing when something is turned off. There are known
  interactions between combos, smart locks, not_dead, and alt local keys.
  Turning encoders or oled on and off certainly won´t break
  anything.
  
  There are other interactions between your choices.
  Edge keys, thumbs, combos, other extensions, 
  may use the extensions that are enabled.
  
### Look here to see the parts
  * Everything can be turned on and off in *config.h*
  * Base layers are in *base_layers/*
  * Edge keys are in *layers/edge_keys.h*
  * Thumbs can be reviewed in *layers/thumbs.h*
  * Mods are in *mod_layers/*
  * All other layers are also in *layers/*


The long version
-----------------

All can be turned on or off in the config. 
supports en-us and fr-bepo Support for other languages is easily added.

Layouts are human readable, all extensions are defined with def files.
If an 128x64 oled is available, a map of the current layer is shown if enabled.

I'm an Xmonad, emacs in vi emulation programmer, that 
just means that _Gui, Esc, :/?!% and ._ are all easy access and I like my
arrow and mouse keys in a 4 column row.

I have also become minimalist in my keyboard choices. I don't use
number rows, not even on my kinesis, dactyl, or ergodox_ez, which have them. 
Although my maps do reasonably support these bigger keyboards as that is where
it all started for me and I do still use them. My preference for keyboards 
is more in line with the Kyria and Corne. I still use 6 columns, but have been
looking to use only 5.

Note: Combos at QMK master do not currently support multiple reference layers which this
configuration uses. Combos still work as always, but do not support all the features
found here. To get fully functioning multi-reference combos, see my *ericgebhart_dev*
branch and pull request below.

Actually, at the moment, the fix is in my ericgebhart branch, since I accidently
pushed it.  I'll remedy that soon.

A more current version of my QMK user can be found here in
A sparse tree [of my QMK User Space ](https://github.com/EricGebhart/MyQMK/users/ericgebhart)

For full multi-lingual combo functionality you will need my [pull request for fully functioning multi-reference combos which can found here.](https://github.com/qmk/qmk_firmware/pull/16699)

Things which effect the thinking.
  * No mouse. 
  * Preference for 3x10 layouts. Corne, Kyria, etc.
  * Still works with bigger keyboards like xd75, kinesis, dactyl, ergodox, viterbi.
  * Change mods without changing any maps.
  * No number row preference. - all layouts have them if needed.
  * Xmonad window manager, GUI key is the entrance to the Xmonad world.
  * Typing in other languages.
  * Curious about keyboard layouts and experimenting.
  * Must be easy to maintain, extend and modify.
  * Minimize digging in code to add new things, or change old ones.
  * Minimize process record user.
  * Easy to add enums for keys and layers, as well as oled display.
  * Easy to support multiple languages regardless of maps.
  * Minimize the need to write C code.
  * Encapsulate C code, so that it is extensible through data.


Features:
  * Everything is configurable from config.h and .def files.
  * Def files for most things.
  * Custom key codes are mostly defined automatically.
  * Everything is chosen or turned on and off in config.h
  * Lots of macros to make it easy to redefine things without a refactor.
  * Multiple edge/outer pinky column sets.
  * Multiple thumb clusters to choose from.
  * Thumb clusters and mods can be changed on a map by map basis.
  * Easily define thumb clusters with an alpha letter.
  * Easily define thumb clusters for non-base layer.
  * Multiple base layers to choose from.
  * Several variations of function layers to choose from
  * Miryoku layers, thumbs and mods if desired
  * Miryoku hands down gold config can be swapped with config.h
  * Navigation and mouse layers
  * A selection of symbol, keypads, and other layers.
  * Regular and Beakl keypad and number rows
  * Multi language support, (locales in the code).
  * Multiple mod layers to choose from. Easy to add more.
    * home row mods - a selection 
    * no mods
    * alt mods 
    * miryoku mods
  * Extensions are easily defined in def files.
    * N-shot mods
    * One-shot mods
    * swapper
    * Smart lock mods 
    * Smart lock layers.
    * Accent keys
    * Alternate shift keys
    * Alternate local keys
    * key overrides
    * Tap hold
    * Not dead keys
    * Send unicode
    * Send string
    * Encoders
  * Display a map of the current layer on the oled.
  * Adding a new layer is painless.
  * Adding or changing most things, is not difficult.
  * Console key logging for [heatmap analysis.](https://precondition.github.io/qmk-heatmap)
  
  
Layout shape and keyboard choices.
-------------------------------------

   In all cases these keyboards are defined in a matrix which is
   a set of rows. Maybe like so, or less. Kinesis has one more row.
                                                       
``` 
   -------------------------|------------------------ */
   | Left0 | Numbers L | mid|dle0 | numbers R | Right0 |
   | Left1 | keys0-5   | mid|dle1 | Keys6-10  | Right1 |
   | Left2 | keys11-15 | mid|dle2 | Keys16-20 | Right2 |
   | Left3 | keys20-25 | mid|dle3 | Keys25-30 | Right3 |
   | Row5L                  |                    Row5R |
   |               ThumbsL  | ThumbsR                  |
   -------------------------|------------------------ 
```

Generally speaking, the keys on the right and left and middle don't change.
Neither do the bottom row or the thumbs, unless asked. Frequently the numbers 
row is identical across layers. 

For automatic edge columns set EDGE_COLS. 
Outside pinky keys are 'yes'.  This is on by default.
N rows by 6 columns per side.
Should be undef/def'd by the keyboard's keymap if no.
#define EDGE_COLS yes. this is all taken care of for supported keyboards.

Thumbs and Edge keys are grouped into sets so that different sets can be chosen in
the config. 

All layer macros take 3x10 or 3x12 as needed. Edge columns are
added as needed, and middle keys fill up the gap.
Thumb keys are added as asked.

keyboard shapes: 
Matrix size + 5th row + thumbs.
Matrix size + thumbs.

 * kinesis
   4x6 + 4 + 6 - 18 func keys.
 * dactyl - Morpho handwire
   4x6 + 5 + 6
 * ergodox_ez
   4x6 + 5 + 6 & 3 pairs of center keys.
 * crkbd - corne
   3x6 + 3 or 3x5 + 3
 * xiudi/xd75
   5x15
 * keebio/viterbi
   5x14
 * montsinger/rebound/rev4
   4x12 + 3 center keys.
 * -- 4x12
 * splitkb/kyria
   3x6 + 7 or 3x5 + 7
 
The parts of a keymap
---------------------

  * keymap
    * defined in _keymap/keymap.c_. 
    * Completely configurable from config.h
    * Separated into logical chunks.
    * Uses a language setting to create all maps.
    * Creates the same maps in multiple languages.
    * More than one language simultaneously on one keyboard.
    * Currently provides these languag settings and keycodes. 
      * US - US-intl (US_)
      * EN - US-en (KC_), 
      * BEPO - fr-bepo (BP_).
    * Choosing dvorak, and enabling bepo as the second locale, 
    will produce two base layers to choose from on the keyboard. 
    Dvorak on US and BEPO.
   
 * Base layers
   * Simple and compact definitions.
   * Base layers are pure.
   * Mods are defined separately.
   * OLED Maps for 128x64 sized oleds.
   * Language agnostic.
   * Core layer chunks are 3x10.
     * Except for few exceptions which are 3x12
   * More than 50 base layers to choose from.
   
   **Caution: Choosing too many base layers will result in toprows or keypad layer LT's 
   to stop working. If bepo is enabled, all base layers are doubled so it's
   easy to hit the 16 layer limit for LT.**

 * Locales
    * Locales, defines a set of layers for a locale.
    * Layer definitions are language agnostic. - see lang.h.

 * Extensions - Defs.
    * Can be selected in config.h
    * Defined in easy to read .def files.
    * Correspondance between *extensions/* and *defs/*

    * accented_keys.def - direct access to altgr keys
    * altlocal_keys.def - alternate un/shifted pairs.
    * alt_shift.def - alternate shifting behaviors for existing keycodes.
    * not_dead.def - definitions for non-dead dead keys.
    * caps_word - no def file.
    * combos.def - 
    * custom_keys.def  - list of custom keys.
    * encoders.def - encoder behaviors by mod/layer.
    * key_overrides.def - Bigger more complex alt keys.
    * mod_lock.def - smart locking mods with a set of ignore keys.
    * nshot.def - N-shot locking mods
    * oneshot.def - One-shot locking mods
    * smart_lock.def - Smart lock layers and mods.
    * swapper.def - key substitution, reverser.
      * eg. toggle between tab, backtab on a key, with a reverse key.
    * tap_hold.def - Define key for tap and hold for tapping term for qqc autre.
    * unicode.def - keycodes to send unicode strings.
    * send_string.def - keycodes to send strings.


 * Layers 
    * Multiple selections of the Transient layers.
    * Layer chunks are 3x10, with some options.
    * Full Navigation layer - stable and well used.
    * Mouse keys or without.
    * 1 or 2 layer nav, 2nd for mouse. or all on one. - choices.
    * Multiple choices of an easy to use _top rows_ layer similar 
      to `raise` and `lower`. 
    * A fully complete symbol layer, Used for coding and writing.
    * Accented letters and dead key layers.
    * Keypads and function pads.
    * Beakl keypads and symbol layers.
    * Control layers.
        * Layers
        * Adjust
        * RGB
   
 * OLED A simple, configurable implementation.
   * Current base layer
   * Current locale
   * Current transient layer
   * Last key, matrix location and value.
   * Mods and locks
   * Map of the current layer. (Oled 128x64)
   * key logger

 * Keyboards
    * nothing is needed in keymaps/*/keymap.c
    * Layouts - keyboard matrix adaptation.
        * Adaptive. Usually taking 3x10 maps and filling the edges and thumbs.
        * 4x10 or whatever is possible. 
        * 3 versions, thinking in a split kb, way.
            * 5 columns in, 5 out. 
            * 5 columns in, 6 out. 
            * 6 columns in, 6 out. 
   * per keyboard shape.
   * There are layouts per keyboard.
     * Base layout with mods and thumbs and edges added.
     * Transient layout which can be KC_TRANS, in those same places.
   * The number row addition can be turned on and off as needed by the layout.
   * Layouts can hard code the number row, negating the need for giving one.
     
 * Multiple edge key sets
 
 * Multiple Thumb clusters - see config or thumbs.h for up to date choices.
   * Support for multiple definitions. 
     * mods
     * layers
     * mods_layers
     * mods_layers_nav
     * beakl wi
     * beakl wi - official.
     * test  - to play with.
     * trans - transparent, could be used in the transient layout to allow alternates.
     * miryoku with keypad
     * miryoku with toprows
     * mods_layers with left thumb letter
     * hands down approximation with left thumb letter
     * miryoku with keypad, letter on left, space on right. - no tab.
     * miryoku with toprows, letter on left, space on right. - no tab.
     
 * Mod Layers
   * Completely independent of any layer or base layer definition.
   * Easy to create a new one by copying the transparent version.
   * Can be changed on a layer per layer basis.
   * Based on position in the matrix.
   * Chosen in config.
   * Multiple choices.
     * Home Row Mods. sacg, gacs, gasc
       Left and right mods on left and right.
     * Transparent - the default if not chosen.
     * Alt - Non home row mod variant.
     * miryoku HRMS is sacg plus right alt/altgr on third row.

 * Alternate language/locale support
   * Happens at the lowest level
   * All maps work with any of the [keymap extras.](https://docs.qmk.fm/#/reference_keymap_extras)
   * Language support is simple to add with just a new, very simple macro.
   
The language keycodes can be found 
[here.](https://github.com/qmk/qmk_firmware/tree/master/quantum/keymap_extras)


Architecture
-----------------
The idea here is that most things don't change, and the things that do are
easy to understand and change. The defs directory is where all the extras are,
tap_hold, alternate shift keys, combos, keycodes, smart lock, one shot mods,etc.

If layers exist that you want and like, then all other behaviors are defined in
def files which are much nicer than working directly with C code. If there is
need there is always the copy pasta way too.

Things that are likely to be changed when adapting a layout to personal preferences
are *layers/thumbs.h* and *mod_layers/*.  The function layers are all in the
layers folder and should be easy to understand. Once added, it is only necessary to
add the appropriate defines in _config.h_

Adding new layers requires changes in layer_names, *oled/oled_layers.h* and *oled/oled_cartes.h* and the appropriate *keymap/ .h* file.

Adding a new keyboard is done in keyboards and should be fairly obvious.
```
.
├── base_layers
│   ├── accents.h
│   ├── alt.h
│   ├── base_layers.h
│   ├── beakl.h
│   ├── bepo.h
│   ├── carpalx.h
│   ├── dvorak.h
│   ├── gap.h
│   ├── hands_down.h
│   ├── keymaps.txt
│   ├── maks.h
│   ├── qwerty.h
│   └── toprows.h
├── config.h
├── defs
│   ├── accented_keys.def
│   ├── altlocal_keys.def
│   ├── alt_shift.def
│   ├── combos.def
│   ├── custom_keys.def
│   ├── encoders.def
│   ├── key_overrides.def
│   ├── mod_lock.def
│   ├── not_dead.def
│   ├── nshot.def
│   ├── oneshot.def
│   ├── send_string.def
│   ├── smart_lock.def
│   ├── swapper.def
│   ├── tap_hold.def
│   └── unicode.def
├── ericgebhart.c
├── ericgebhart.h
├── extensions
│   ├── accented_keys.c
│   ├── accented_keys.h
│   ├── altlocal_keys.c
│   ├── altlocal_keys.h
│   ├── alt_shift.c
│   ├── caps_word.c
│   ├── caps_word.h
│   ├── console_key_logger.c
│   ├── console_key_logger.h
│   ├── encoders.c
│   ├── encoders.h
│   ├── extensions.h
│   ├── keycodes.h
│   ├── keymap_combo.h
│   ├── key_overrides.h
│   ├── mod_lock.c
│   ├── mod_lock.h
│   ├── not_dead.c
│   ├── nshot_mod.c
│   ├── nshot_mod.h
│   ├── oneshot.c
│   ├── oneshot.h
│   ├── process_locales.h
│   ├── process_nshot.h
│   ├── process_smart_lock.h
│   ├── send_string.c
│   ├── smart_lock.c
│   ├── smart_lock.h
│   ├── swapper.c
│   ├── swapper.h
│   ├── tap_dances.c
│   ├── tap_dances.h
│   ├── tap_hold.c
│   ├── tap_hold.h
│   ├── unicode.c
│   └── unicode.h
├── keyboards
│   ├── keyboards.h
│   └── layouts.h
├── keymap
│   ├── keymap.c
│   ├── map_accented.h
│   ├── map_alt.h
│   ├── map_beakl.h
│   ├── map_bepo.h
│   ├── map_carpalx.h
│   ├── map_dvorak.h
│   ├── map_funcs.h
│   ├── map_gap.h
│   ├── map_hd.h
│   ├── map_keypads.h
│   ├── map_maks.h
│   ├── map_qwerty.h
│   ├── map_symbols.h
│   └── map_toprows.h
├── lang
│   ├── lang.h
│   ├── lang_map.h
│   ├── locale_layers.h
│   ├── locales.c
│   └── locales.h
├── layer_names
│   ├── base_names.h
│   ├── func_names.h
│   ├── layer_names.h
│   └── util_names.h
├── layers
│   ├── edge_keys.h
│   ├── keypads.h
│   ├── layers.h
│   ├── nav.h
│   ├── symbols.h
│   ├── thumbs.h
│   ├── toprows.h
│   └── utility.h
├── listen_keylogger.sh
├── mod_layers
│   ├── alt_mods.h
│   ├── hrm_gacs.h
│   ├── hrm_gacs_miryoku.h
│   ├── hrm_gasc.h
│   ├── hrm_sacg.h
│   ├── hrs_nav.h
│   ├── mod_layer.h
│   └── trns_mods.h
├── oled
│   ├── oled_cartes.c
│   ├── oled_layers.c
│   ├── oled_stuff.c
│   └── oled_stuff.h
├── process_records.c
├── readme.md
└── rules.mk

10 directories, 118 files
```

Locales
-------------------
There are currently three locales.  LANG_IS defines the one in use.
The map changes this value as it goes, to get the maps that are asked for.
I have recently renamed some variables, such that it seems that only 2 locales
are possible. It seems more than two might be too many. And keeping at 2 is
a little easier.

 * EN - en-us, **KC_** keycodes.
 * US-INT - us-international variant, **US_** keycodes.
 * BEPO - bepo-fr, **BP_** keycodes.

Switching LANG_IS before adding a new map will cause that map to 
use LANG keycodes and keymap chunks when building the map.

Enabling a second locale to bepo, will cause bepo versions of the chosen layers to
be added to the keymap.

### defining a locale.

This is to manage BEPO and Qwerty Locale/language/Layers
Each locale is defined with a start and end layer from the layers enum.

This is only necessary to give contextual base layer choices based on
the current locale setting, which the keyboard tracks.

The first and last defines are all done with the magic of defines in 
ericgebhart.h where the layers enum is defined.

This could potentially hold multiple locales, The map turns on off the layers 
and their enums if they are not enabled so that the layer array does not 
fill up with too many base layers, or other layers because LT only works 
up to layer 15.

What this does is allow the keyboard to know which locales it has, and which
layers go with them.

If you have an oled, the locale will be displayed after the layout name. Currently
en-us and bepo-fr are there.

Locales are tracked, as to the layer ranges which belong to them in the layers enum.
This allows for a `KC_NEXT_LOCALE` key and a `KC_NEXT_BASE_LAYER` key, on the _layers_
layer. 
`KC_SET_BASE` sets the default layer in the eeprom.

When cycling through layers only the layers for the chosen local will appear.

The layers are different keycode sets. 
So there are two symbol layers, two toprows layers, two keypad layers. 
One for Qwerty and one for bepo. The Navigation layer is not affected because
it has only control keycodes which are independent of locale. 


### Locales, how they work in layouts.

This is done through consistent naming patterns and macros.
Here are the macros that support creation of layout parts by locale.
All are defined in **lang.h**

 * Keycode Prefix - KC or BP, etc. 
    `LANG_KC(_A) -> KC_A or BP_A`

 * Defined key/layer Suffix - SYMB_EN, SYMB_BP, ... 
    `LANG_N(NAME) -> NAME_EN, NAME_BP`
 
 * Map chunk Suffix - _EN, SYMB_BP, etc.
    `MAP_CHUNK(15_BOTTOM) --> ___15_BOTTOM_EN___ or ___15_BOTTOM_BP___`

_lang.h_ has the macro definitions used in the keymap resolution,
A new locale, will need a new set of macros that match the others.
They use LANG_IS, Follow the patterns. It should be reasonably obvious.

It is only necessary to create new base level macros that are used by these
macros.  All of them are similar.

**LANG_KC** uses these macros to resolve it's values.
```
    // Give the right keycode prefix by LANG_IS
    #define LANG_PFX CAT(LANG_IS_, KC)
    #define BEPO_KC BP_
    #define EN_KC KC_
```

Adding a new one is just a matter of adding the a macro named with
this format. `LANG_IS _Keycode prefix`.
for Slovak, if the **LANG_IS** value is `SK` that would be,

    `#define SK_KC SK_`

LANG_N macro uses these similar macros for it's resolution.

```
    // Give the right symbol suffix by LANG_IS
    #define LANG_SFX CAT(CAT(LANG_IS, _), SFX)
    #define BEPO_SFX _BP
    #define EN_SFX _EN
```
Adding Slovak support to the LANG_N macro looks like this.

    `#define SK_SFX _SK`


### Thumb clusters.

Thumb clusters can be chosen by layer with the value of **THUMBS_ARE**.

The easiest way to see them is to look in *layers/thumbs.h*.

At the core of the thumb clusters are a set of six keys which
can be changed to a one of a set of keys, with settings in the config. 
Supporting a 4 key thumb cluster would just need a similar set.

The newer Hands down variants also have need of thumb clusters which
can take a letter.  A default can be given in config.h.
Each keymap layer entry can give it's letter to change the thumb cluster.
This is needed for hands down, maltron, rsthd, and beakl wi.

These layouts use a special thumb cluster variant which will use the value
of *THUMB_LETTER* to place a letter on one of the thumb keys.

It is reasonably easy to add a new thumb cluster and use it. Add it to
thumbs.h, add to the list of macros for it's suffix, and turn it on 
by setting it to *THUMBS_ARE* in config.h

Additionally a thumb cluster can be set for the various function layers as
well. The transparent thumbs can be used, or something else. The nav and 
mouse layers have the mouse buttons if mouse keys are enabled.

It is also possible to use a Miryoku thumb cluster and layers 
or mix the other layers in as desired.

The language of thumb clusters is managed at the lowest level.
These keys are mostly not language specific.

Here is the definition for my space and symbol layer key. 
This changes the name of the layer given like this.

_SYMB becomes *_SYMB_EN* or *_SYMB_BP*. Depending on the value of *LANG_IS*

    `#define SPC_SYMB LT(LANG_N(_SYMB), KC_SPC)`


Edge key sets
----------------
Edge keys, or the 6th, and outer pinky column are often not specified
in base keymaps and are not strictly necessary. There are a few sets
to choose from here. A NOKC set with no keys, NORM which is sorta normal
with grave, equal, tab, -, and \/. There is also a smart lock set
which gives access to smart lock layers tab and -. Last there is 
test, so its easy to try new things. Edge keys are defined in
*layers/edge_keys.h*.


Base Layers
-----------------
I like to experiment with layouts. So I have a few. 
They can be turned on in config.h.

To switch base layers there is a combo to raise the layers layer.
Hold both pinkies on their lower row keys to get the layer.
Tap the home row left middle finger to change layers.
Tap the ring finger to set it to eeprom if you want it to stick.

The left index finger will cycle through locales if you have them.

Here is a list of some of the base layers..

 * Dvorakish
    * Dvorak
    * Capewell-Dvorak
    * Ahei
    * Boo
    * Dvorak RLC-UI
 * Beakl
    * 15
    * 19
    * 27
    * WI
 * Qwertyish
    * Qwerty
    * Azerty
    * Workman
    * Norman
 * Maks
    * Colemak
    * Colemak_DH
    * Halmak
    * Minimak
    * Minimak 8
    * Minimak 12
 * Carpalx 
    * QFMLWY
    * QGMLWB
    * QGMLWY
 * Hands Down
    * Neu
    * Neu narrow
    * Titanium
    * Gold
    * Platinum
    * Silver
    * Bronze
    * Elan
    * Dash
    * Ref
 * MTGAP
    * Mtgap
    * Ctgap
    * Apt
    * Canary
 * Others
    * Maltron
    * Eucalyn
    * Rsthd
    * Isrt
    * Hands Up
    * White
    * Soul
    * Niro
    * Asset
    * Whorf
    * Whorf6
 * Bepo, layers with accented letters.
    * Bepo
    * Optimot
    * Optimot compact
    * Beakl19bis

### Adding a new base layer, or any layer 

Adding a new base layer is easy. They all live in *base_layers/*. A base layer
entry looks like this. There is an empty template in *base_layers.h* which collects
all the other maps. The name of the carte  de map, should be **CARTE** followed by
the layer name that will be used. Layer names are usually an underscore followed by
the name.  For dvorak, that is *_DVORAK*, which because of the language layer ultimately
and magically becomes *_DVORAK_EN*, *_DVORAK_US*, *_DVORAK_BP* as needed. 

```
#define CARTE_DVORAK                            \
  carte_de_map(" ',.py fgcrl ",                 \
               " aoeui dhtns ",                 \
               " ;qjkx bmwvz ")

#define ___DVORAK___                                                    \
  LANG_MAP(TL_QUOT,  TL_COMM, TL_DOT, _P,  _Y,   _F, _G, _C, _R, _L,               \
           _A,       _O,      _E,     _U,  _I,   _D, _H, _T, _N, _S,    \
           TL_SCLN,  _Q,      _J,     _K,  _X,   _B, _M, _W, _V, _Z)
```

#### TL_ keycodes 

Use TL_ keycodes for any punctuation, this allows for targeting
of these keys by language and by target layout as needed.
for instance *TL_COMM* -> TLKC(_COMM). The *Target-Language-comma*, 
becomes BP_BK_COMM, or KC_DV_COMM, US_HD_COMM, or whatever it
needs to be based on current language and target layout. If your layer has special
puncuation needs, 

  * Add key entries to *altlocal_keys.def* 
  * Edit to *lang/lang_map.h* to add the new *TARGET_PFX* entry.
  * Set the appropriate value to *ALT_TARGET_IS* in the layer's keymap entry.

#### Integration

Integrating the new map into the rest of the framework is just a simple entry
in a few places. 
  * *layer_names* needs to know about the new name so we can use it, 
  * The oled needs to know about it so it can display it.
  * The config needs to know about it so we can turn it on.

Follow these steps. Everything is very simple, and just one to 3 lines. 
Just follow the same patterns as all the rest. 

  * Add the layer definition and map of the definition in *base_layers/<appropiate>.h*.
  * Add the layer name to *layer_names/base_names.h*
  * Add the layer name to *keymap/<appropiate>.h*
  * Add the layer entry to *oled/oled_layers.c*
  * Add the layer map entry to *oled/oled_cartes.c*
  * Add the define for the layer enable to *config.h*

Adding a new functional layer follows the same patterns, although their
keymap and oled entries may be more complex, since it is usually trying
to pick one from a set of choices.

### Adding a new thumb cluster configuration

Adding a new thumb keys definition is done in *layers/thumbs.h*.
The keys that change are just 6 and they all have the name of *___6_ERGO_THUMBS_...*.

  * Define a new thumb definition with a nice suffix like all the rest.
  * Add an entry to the *THUMB_EXT* list with the nice new suffix.
  * Set the appropriate *THUMBS_ARE* defines in config.h to it's 
  new thumb extension name.
  
### Adding a new mod layer

This is also easy. Mod layers live in the mod_layers folder. Each file
there is a separate mod layer, which is tracked in *mod_layers.h*
The file, *trns_mods.h* is the transparent mods layer and by definition has
no modifiers applied, providing a clean slate. 

The steps are these:
  * Make a new copy of an existing mod layer.
  * Edit the new file and change the names to your new name.
      * ie. *_trns* changes to *_my_new_mods*
  * Add the mods you want. MT's and LT's, tap holds, etc. 
  * Edit  *mod_layers/mod_layer.h*
    * Add the include for the new mods file*
    * Add the *MOD_EXT* entry for the new name
  * Define *MODS_ARE* in _config.h_ to use the new name.


Keymaps
-----------
I only have one. It's in keymap/keymap.c.  
My config.h has all the current usable settings.
Turn on the layers by enabling and choosing them in config.h. 
Most keyboards don't need a keymap.c. 

There are corresponding Bepo layers, as needed, which will arrive if *SECOND_LOCALE* is
set to _BEPO_.
This essentially doubles the number of keymaps.  
Nav, mouse, media, layers, RGB, and Adjust are not duplicated as there is no 
current need.

## Mods, home row and otherwise.
With all these layers it was a real pain to apply mods consistently and 
easily with the old wrapper code. So I changed the way I use keymap macro 
wrappers and added in my own mod layer. The only thing it has is the mods 
to apply. No more editing keymaps to apply mods.  I do it once, and it 
works everywhere I want by location.

Multiple versions are possible. Just copy the trns_mod_layer.h to a new
name and modify it with a new extension name, (replace '_trns'). Then add it's include to mod_layer.h, to be used when the config says.

The defines for *MODS_ARE* and *DEFAULT_MODS* determine which mods are applied
to a given keymap layer. 

Keyboard matrix Layouts
-----------
This is where the keymap of the
keyboard meets the mods and all the edge, middle and thumb keys, and makes 
it easy to give just a 3x10 definition for most layers regardless of which 
keyboard it is going to.

To use an existing layout for a different keyboard, simply make an entry
in *keyboards.h* to assign the proper layouts that fit that keyboard.
So a planck could use the 4x12 layout out of the box. In the keyboards 
keymap there is only a need for config.h or rules.mk if something needs
changing. For the keyboard an empty keymap.c will do.

The base layout can be anything really.
The base layer sets the thumbs and anything outside of the 3x10.
The mod layer is wrapped in the base layout and adds the mods, and a 6th 
outer pinky column as needed.

Some layouts take an extra number row.
Layouts can be any shape, all of these take a 3x10, 3x12, 4x10 or 4x12, 
and make it fit the keyboard.

The layouts defined in _layouts.h_ take a list of keys. and give them
to the keyboard's layout.  The Corne (crkbd), uses a layout called
  `LAYOUT_split_3x6_3`. So for the corne, I have a `Base_3x6_6` that
  is the same shape, in its resolution.
  
There are layouts for Corne, ergodox, kinesis, dactyl, viterbi, xd75, rebound.

Currently, 3 layouts are needed per keyboard. 
 * A Base layout, for default/base layers, 
 * A transient layout for the function layers.
 * A version which takes 3x12 for the larger bepo base layers.

The base layouts can take 3 or 4 rows by 10 columns as desired.
They add in the mods, and any pieces of matrix outside of
the 3x10 center, function, numbers, lower rows, outside pinky keys,
and thumb clusters. 


Functional layers
--------------------
There are quite a few of these to choose from. The easiest way to see
them all is to go look at them in _layers/_. They are logically divided
into files, and their cartes/maps are easy to look at. There are 
minimalist Miryoku versions as needed.

## Navigation Layer
I do not use a mouse. I use Xmonad as my window manager, and I have
practically no use for one.  They are necessary however. So I have
a Navigation layer which is all mouse, arrows, home, end, tab, page
up, down,  5 mouse buttons and so on. 

There are a growing number of choices, left and right sided mouse layers
right side arrows etc, and some monolithic nav layers like the one shown
below.

There is also a split layer, with arrows etc on the right, and smart mods
and N-shots on the other. A left side mouse layer is accessible from
the first nav layer.  There are various choices at this point. It is
best to look at the config.h for clues. 

The miryoku nav and mouse layers are somewhat but not terribly different.


#### One of the Navigation layers.
                                                       
```
M = Mouse
B = Button
W = Wheel
AC   = Acceleration
CCCV = Tap -> Ctrl-C, hold for double tap duration -> Ctrl-V
CTCN = Tap -> Ctrl-T, hold for double tap duration -> Ctrl-N
CWCQ = Tap -> Ctrl-W, hold for double tap duration -> Ctrl-Q
HOME = TAB & PGDN
END = BKTAB & PGUP
Lock/Unlock LAYER = PGDN & PGUP
 
MB5  MB4    MB3    MB2  MB1     MAC0  |  CTCN  MB1    MB2    MB3  MB4   MB5 
TAB  MLeft  MDown  MUp  MRight  MAC1  |  CCCV  Left   Down   UP   Right TAB 
     WLeft  WDown  WUp  WRight  MAC2  |  CWCQ  TAB    PGDN   PGUP BKTAB
                                                                             
     Left   Down   Up   Right   CCCV  |  CCCV  MLeft  MDown  MUp  MRight
     
     
```
                                                                            

## Symbol Layer

The symbol layer is based on the Beakl15 symbol layer. It was very similar to a symbol
layer that I had before beakl, but this felt better, and has been through a few 
iterations at this point. Vi likes using :/?! a lot. The = is not that important to
me, as the : for the vi ex: command. The ! is very satisfying in this location.

For US-intl and Bepo which have dead keys, the symbol layer uses the *not_dead* extension
to give _'`"^~_ which are not dead.

The beakl symbol layer is intuitive and fairly easy to remember. There are 3 versions.
The original, an extended, and an extended and enhanced for vi.
The primary purpose of the extension was to provide keys which might not be available
elsewhere on the default layer. The vi version takes this further and moves :/? 
to better places.

I prefer a modified beakl15 symbol layer. here it is, left and right.
This layer has some extra characters so it works with non-beakl base layouts.
The beakl wi symbol layer is not an improvement on this IMO.
Miryoku symbols layer is only left sided, and minimalist as well.
This might be a little vi centric, with the : in the middle. ymmv.

There are a few choices, this is one.

```
        `<$>'  ?[_-] 
      - \("#)  !{:/} ;
        @=*+;  %&^~|
```


## TopRows Layer

The toprows layer is a nice way to transition to small keyboards.
I think, truly this is the layer that makes tiny keyboards accessible in the beginning.
Everything can remain familiar. I use this one with a beakl number row.
The default, if no choices are made, aside from enabling toprows, will  
have a normal qwerty number row, as in the second map.

I do not use F keys, The latest addition has _smart_ and _nshot mods_ in the third row.
There is a miryoku thumb cluster which uses this layer instead of a keypad.

    ```
    !@#$%   ^&*()
    40123   76598
    F1   ---  F10
    ```
 or

    ```
    !@#$%   ^&*()
    12345   67890
    F1   ---  F10
    ```

## Keypad and Funcpad Layers

There are several variations of keypads and function key pads in various sizes,
and left and right. 
There are also versions with smart and nshot mods instead of F-keys.
There are monolithic, left and right, and also half keyboard left mostly...
A miryoku version also exists.
The keypad can be chosen in config.h.

```
    523:  F9-12 
   7.104  F5-8
   /698,  F1-4
```
## Media Layer

A simple Miryoku, media layer, controls on the right.

OLED
--------------------
The oled shows the basic stuff I could find in most places. 
* Default layer
* Current layer
* Locale
* Mods 
* Locks 
* Last key pressed
* Map of the current layer as simply as possible. (128x64)

Process_records.c
--------------------
This is where the keycodes are processed...
It tends to be where cruft gathers. Mostly I try to keep it empty
and do all my processing with the extensions.  The file, _extensions.h_ 
takes care of inserting them in process_records with it's macro.


Extensions
---------------------
Extensions are all in the extensions directory and have a single 
entry point via extensions.h which provides a macro to place in **process_record_user**. 
The intention is that they are easy to copy and use as is without digging around
in the C code. Custom keys are also defined there. Any keycodes defined by
an extension are automatically added to the custom keys enumeration so there is no need to define them manually.

A new extension can be added with a process record entry in
extensions.h. Just follow the same code pattern. If an extension defines keycodes, 
add it's include entry in *keycodes.h* so that they are automatically added to the enum. 
Keycodes.h is also where all the miscellaneous short cut key defines are done. 

To copy all the extensions, 
  * Copy the extensions and defs folders, 
  * Copy process_records.c file or adapt yours.
  * Adapt your custom keycodes to custom_keys.def.
  * Copy the pertinant parts of config.h so that everything can be enabled.
  * Define _USERSPACE_H such that all the extensions can find your stuff.

To adapt to your own process_record_user do this;
Include extensions.h in your process_record_user,then add this 
above the switch.
```
PROCESS_EXTENSIONS
```
This will cause process records to use whatever extensions are turned on.

Many extensions have a _.def_ file in _/defs_ for any data that is needed.

Because many of them use custom keycodes or layers in their definitions, 
it is necessary to include your userspace .h such that keycodes and layer
codes can be found. To simplify this, simply add a define to config.h
to point at your .h or wherever your custom codes can be found.

In my case;
```c
#define USERSPACE_H "ericgebhart.h"
```


Custom keys
-------------------
The Custom keys are in __custom_keys.def__.

__keycodes.h__ is an extension of sorts. It is the custom keys enumeration.
The __custom_keys.def__ has a few random keycodes in it.

All other keys are automatically generated from the other def files.

For the extensions that have key definitions those keys are enumerated
automatically. The keys are defined in the def files so there is no need
to add them to the enumeration manually.

It will complain as usual if there are duplicates.

Mostly, __keycodes.h__ is key defines to make shortcuts, since the enumeration
is done almost completely automatically. When adding a new extension
which defines keycodes, that extension will also need an entry in 
keycodes.h in order to automatically define the new key enumerations
it´s def file creates.


Accent keys
-----------------
This is a way to create keycodes which access keys
which are normally only accessible with an Altgr/Ralt and a dead key.

Each definition takes a keycode, the key to modify, and the dead key
to apply to it.

```
ACCENTED(BP_OCIR, BP_O, BP_DCIR)
ACCENTED(BP_ACIR, BP_A, BP_DCIR)
```


Alternate keycodes 
-----------------------------
Normally, a keycode has unshifted and shifted key values. These are defined
by the OS and it's locale, not the keyboard. This feature allows a keycode 
to be defined that uses arbitrary unshifted and shifted keycodes and their modifiers. 
This is necessary, because, for instance, qwerty has , and ; paired. Other
locales may not. Bepo, and Beakl both have different pairings as do many other
layouts.

Because of wanting dvorak and beakl on bepo there was the necessity to create keys
from keycodes which were not combined. key overrides were not 
sufficient because some keys are not actually keys that can be accessed
without modifiers. Each keycode for the new key specifies it's own
modifiers making any character available as an unshifted or shifted key.

Alternate keys for a locale, are defined in **altlocal_keys.def**.
These are to emulate a key, from 2 keycodes. 

This is for emulating keys on another locale/language.
Dvorak on Bepo-fr, or Qwerty on sk-SK, or de_DE.

It is also good for alternate shifted and unshifted pairs like
what is needed for beakl or hands down on en-us/qwerty.

This feature is usually only needed for punctuation keys 
and the top row number keys. Where the unshifted and shifted keys
are not the same character as the keyboard local on the OS.

It has turned out that most of these keys have a destination language,
and a target language/layout. 
The target is to emulate something on some language. QMK uses keycode prefixes,
so this works pretty well and the names stay consistent with all the others,
but with a middle name.

The pattern is Language prefix, target language prefix, name.
The target prefix is made up. BK -> beakl, DV -> dvorak, HD -> hands down, etc.

The naming pattern is only important in that it works with all of the Lang
macros elsewhere in this userspace. A macro is provided on a per key 
basis, which can be used at the base layer definition, such that *TL_COMM*; 
target-language-comma, becomes BP_BK_COMM, or KC_BK_COMM, or whatever it 
needs to be based on 
current language and target layout.

Here is a def entry to create the 1/! keycode for dvorak in the Bepo-fr locale
in *altlocal_keys.def*.
```
  MK_KEY(BP_DV_1,    BP_DQUO, MOD_LSFT,      BP_DCIR, MOD_LSFT)
```

Here is what some Beakl keys look like for en-us/qwerty.
Beakl has dot with @, comma with ! and " with `.

In *altlocal_keys.def*.
```
  // Keys for BEAKL on Qwerty
  MK_KEY(KC_BK_DOT,  KC_DOT, MOD_NONE,    KC_2, MOD_LSFT)
  MK_KEY(KC_BK_COMM, KC_COMMA, MOD_NONE,  KC_1, MOD_LSFT)
  MK_KEY(KC_BK_QUOT, KC_QUOT, MOD_NONE,   KC_GRV, MOD_NONE)
```

Not Dead keys
--------------------
As a writer dead keys give me access to accented letters in other languages,
As a programmer they are a pain, especially for a vi user. This problem is
limited to a few characters; "'`^ and ~. This extension helps to fix these
characters and make them accessible as non-dead keys. It does this by adding
a space afterward. The space is eaten by the OS keyboard driver and the letter
emerges as needed. Here are some non dead keys for US-Intl.
In use, I put these on the symbol layer, and let all the others remain dead.

```
NOT_DEAD(US_DQUO_ND, US_DQUO)
NOT_DEAD(US_GRV_ND,  US_GRV)
NOT_DEAD(US_QUOT_ND, US_QUOT)
NOT_DEAD(US_CIRC_ND, US_CIRC)
NOT_DEAD(US_TILD_ND, US_TILD)
```

Alternate shifts
---------------------
The alt shift extension is very simple, it uses a usual keycode, it does
not define custom keys. It allows for an existing key like dot or semi-colon 
to have a different letter on its shifted value. 

There are currently three types of shift mods.
  * Give a different character than usual on shift.
  * Give two of the usual character instead of one.
  * Give three of the usual character instead of one.

They are all defined in *defs/alt_shift.def*.
Here are some silly examples.

```
ALT_SHIFT(US_EXLM, US_PERC)
SHIFT_FOR_2(US_AT)
SHIFT_FOR_3(US_DLR)
```


Key Overrides
-------------------
These are the standard QMK key overrides. For un/shifted pair keys *altlocal_keys* is
much, +3x, smaller and direct in that it makes keycodes that can be placed anywhere.
However, if ko's are desired, this extension is an easy place to start.

There are nice macros which take care of defining everything that is possible
with the ?_ko() functions

This first example is better done with **altlocal_keys**.

```
// KOL(slash_pipe,      MOD_MASK_SHIFT, KC_SLSH, KC_PIPE, _DVORAK_EN)
```

Other key overrides can be defined with these.

```
KO(name, mods, key, replacement)

KOL(name, mods, modded_key, replacement, layer)

KOLN(name, mods, key, replacement, layer, neg_mods)

KOLNO(name, mods, key, replacement, layer, neg_mods, options)
```

Combos/Chords
----------------------------

The combos here use multiple reference layers which is a pending
pull request in the dev branch of QMK. The combos here will still work
to an extent if *COMBO_ONLY_FROM_LAYER* is set to the correct layer number.

[See my pull request to enhance combos here](https://github.com/qmk/qmk_firmware/pull/16699)

This pull request defines a hook function for combos to determine the
reference layer for the current layer.  This allows for multiple reference
layers to be used depending on the situation.

Reference layers will be created and used according to the following
defines. 
If the reference layer is enabled, it will automatically be assigned to
COMBO_REF_DEFAULT and that will be the default reference if none
is specified. If not specified, the reference will be the current layer.

  * #define COMBO_REF_LAYER_ENABLE // enable a reference layer.
  * #define COMBO_REF_LAYER_TWO_ENABLE // enable a second reference layer
  * #define COMBO_ONLY_FROM_LAYER 2
  * #define COMBO_REF_DEFAULT 2
    Works in config.h if you know the number of your layer.
    Automatically set if ref layer is enabled.

Defining layer specific combo reference layers by layer in combos.def
In this case, the default will be _COMBO_REF, the NAV layer will
reference it's self, while bepo dvorak will reference the second
combo reference layer. Keys start or end with CB or CB2.
    
```
COMBO_REF_LAYER(_DVORAK_BP, _COMBO_REF2)
COMBO_REF_LAYER(_NAV, _NAV)
```

The combo reference layers follow an easy to remember keycode naming
convention so that it is easy to define combos based on position.
Keycodes are prefixed by CB or CB2, the first number is the row,
followed by L or R for left and right, then the column number,
for each hand left to right.

Row 0 is the number row, there are 4 rows possible.

`CB_1L1` is the left pinky, `CB_1R1` is the inside right hand index column.

```
  _1L1,  _1L2, _1L3, _1L4,  _1L5,   _1R1, _1R2, _1R3, _1R4, _1R5, 
```

If there are edge keys, they are named accordingly, left and right.

```
L0_CB, L1_CB, L2_CB, L3_CB
R0_CB, R1_CB, R2_CB, R3_CB
```

Thumb keys use the COMBO and COMBO2 thumb settings which give keycodes
like this.

```
#define ___6_ERGO_THUMBS_COMBO___  CB_TH1, CB_TH2, CB_TH3, CB_TH4, CB_TH5, CB_TH6
#define ___6_ERGO_THUMBS_COMBO2___ CB2_TH1, CB2_TH2, CB2_TH3, CB2_TH4, CB2_TH5, CB2_TH6
```

Tap-Hold
-----------------------

Tap hold currently has *tap_taplong* and *open_openclose* functions.
These are in *tap_hold.c*, *tap_hold.h* and *tap_hold.defs*.
Both use **TAP_HOLD_TERM** as the hold duration.

Tap_taplong sends one keycode on tap, and another after a hold of tapping term.
Open_openclose, sends one keycode on tap, hold sends that, plus the second, 
followed by a back arrow.

Additionally, open_openclose will send a triple of the open keycode when tapped with
the shift modifier on.

There as also a __not dead__ version of open_openclose that accomodates using
dead keys like quote so that the functionalty behaves as if the key were not
a dead key, giving a quote, a pair of quotes or a triple of quotes.

The file _tap_hold.defs_ contains all the definitions. Like combos,
these entries are processed with a function call from **process_user_record**
`process_tap_hold_user(keycode, record);`

Define your keys in *tap_hold.defs*.

Here is Ctrl-C, Ctrl-V, as tap and long tap.
```
TP_TPL(KC_CCCV, LCTL(KC_C), LCTL(KC_V))
```

For tap open, hold for open and close then a back arrow.
Here is __(__ or __()__ with tap and long tap.

```
OPEN_OCL(KC_OCPRN, KC_LPRN, KC_RPRN)

OPEN_OCL(KC_OCQUOT, KC_QUOT, KC_QUOT)
// non dead version of quote.
OPEN_OCL_ND(BP_OCQUOT, BP_QUOT, BP_QUOT)
OPEN_OCL_ND(US_OCQUOT, US_QUOT, US_QUOT)
```

It is also possible to trigger a smart lock with a hold.
This example creates a keycode, `ENTNAV` which can be used
to type enter, or smart lock the nav layer.
Note that `SML_NAV` should be defined in `smart_lock.defs`.

__Caveat:__
This does have the unfortunate behavior of delaying the action
until key up. So it may not be that useful. I did not like it
for this particular example.

```
TP_SML(ENTNAV, KC_ENTER, SML_NAV)
```

Caps Word
-------------
This is a slightly modified version of caps word which adds a *CAPS_WORD_ON* keycode
which can be used to turn caps word on explicitly. This is useful for mapping a
single key or creating a combo.

[As documented in here.](https://getreuer.info/posts/keyboards/caps-word/index.html)
Holding both pinkies on home row for double tapping term, is effectively 
right-shift and left-shift, invokes caps-word. The next word will be capitalized. 
It continues until it shouldn't.

Smart lock
----------------
They are defined in *smart_lock.def*. They need
a custom keycode, and a layer or mods, not mod keycode, to apply, 
followed by a list of keycodes to ignore and stay active. 
This allows popping to layer which will stick until it doesn't. 
Or to apply mods until it shouldn't. Each definition has it's
own list of key codes to ignore. Derived from _smart_layers_
by @possumvibes.

Add a keycode to custom_keys.def then assign it to it's action in smart_lock.def.
```
// SMLL = smart lock layer.
// SMLM = smart lock mod.

// Keycode, layer/mod.
// list of keycodes to ignore.

SMLM(SMLM_LSFT, MOD_LSFT,
  ___VI_ARROWS___,
  ___HOME_PGDN_PGUP_END___,
  ___TAB_PGDN_PGUP_BKTAB___,
  ___SML_MODS_L___)

SMLL(SML_NAV, _NAV, ___NAVA_3x10___)

```

Mod lock
----------------
Mod lock is originally from @possumvibes, it has ignore keys as well,
but these keys apply to all locks defined. which gives a slightly smaller 
memory footprint than smart locks. The mods, are keycodes, rather than mod codes.

The behavior is the same as smart lock mods, but less flexible, and smaller.
First create a keycode in custom_keys.def, then assign it to the mod you want.

Ignore keys are universal for all mod locks.

```
// mod lock keys. takes keymods not mods.
// keycode should be defined in custom_keys.def.
// custom key,  modkey to activate
MODL(ML_LSFT, KC_LSFT)
MODL(ML_LCTL, KC_LCTL)
MODL(ML_LALT, KC_LALT)
MODL(ML_LGUI, KC_LGUI)

// Keycodes which will NOT cancel mod lock mode.
IGNORE_KC( KC_LEFT)
IGNORE_KC( KC_RGHT)
```

N-shot mods
----------------
I simply modified N-shots to use a def file. This is essentially @possumvibes
fancier version of @callum's one shot mods. It has ignore and cancel keys,
and there are one shot mods or N shot mods. Ignore and cancel keys apply
to all oneshot and n-shots.

```
// Define keycodes in custom keys.
// KEYCode, mod keycode, to set for n-shot.
// ONESHOT is for one.
// NSHOT takes a count.

// oneshots
ONESHOT(OS_LSFT, KC_LSFT)

// N-Shots
NSHOT(TS_LCTL, KC_LCTL, 2)

// Keys which will cancel the n-shots.
CANCEL_KEY( PANIC)

// Keys which will be ignored by n-shots.
IGNORE_KEY( SML_NAV)
```

One-shot mods
----------------
This code came by way of @jurgen-kluft, I encapsulated the code and made 
the user functions definable with a .def file. This is similar to N-shots. 
This one keeps track of the last key consumed which helps it's decision making. 
It also has cancel and ignore keys like N-shots.

Essentially the same as n-shots, but with less elegant C code. Choose one or
the other. 

In evaluation.  The code for nshots is better.

```
// custom-key, Oneshot name.
ONESHOT( OS_LSFT, ONESHOT_LSFT)

// keys to cancel
CANCEL_KEY( KC_ESC)

// keys to ignore.
IGNORE_KEY( SPC_NAV)
```

Swapper
----------------
I added the defs code so they are easy to define. This is a way to
alternate between 2 keycodes for a key by sending another keycode. An
example is tab or backtab on one key, which reverses when you press a
second key. It also allows for mods to be applied. The following defines
SW_WIN, which sends left alt-tab and shift- left alt- tab, when reversed
by SW_REV.

```
SWAPPER_KEY(SW_WIN, SW_REV, KC_TAB, S(KC_TAB), KC_LALT)
```
Note: The switch key is not automatically defined in the custom keys enum in
_keycodes.h_. It is convenient to use the same one which causes problems
for automatically adding it. Add it to *custom_keys.def*

Encoders
----------------
This is basic encoder stuff, modified to use a def file which makes it a lot easier
to define and use. It can switch the encoder functions based on layers and mods.
Give it a layer name and/or mods to match on, and the clockwise and counter 
clockwise keycodes to send.

I used LEFT and RIGHT, but really it's just 0-N, but I happen to have one
on the left and one on the right. If you have one, use 0 or LEFT.

The code scans the entries for matches on layer first, checking for a match for
mods. If an encoder entry is not found it then scans for entries with
layer set to LAYER_NONE.

RGB light controls require calling the functions directly, for this
there is a special macro and function that does this. The functions
should take no arguments.

```
// Layer/none, encoder index 0/1, CW_KC, CCW_KC, Qualifying mod or none
// LAYER_NONE and MOD_NONE for a single use.
// LEFT and RIGHT for index. they go on from there, 2, 3, etc
// if one encoder, LEFT/0, is the first one, on the master side.

// default encoders, all layers no mods.
ENCODER_ACTION(LAYER_NONE, RIGHT,  KC_PGDN, KC_PGUP, MOD_NONE)
ENCODER_ACTION(LAYER_NONE, LEFT,  KC_DOWN, KC_UP, MOD_NONE)
ENCODER_ACTION(LAYER_NONE, LEFT,  KC_PGDN, KC_PGUP, MOD_LSFT)

// Symbol layer encoders.
ENCODER_ACTION(_SYMB, LEFT, KC_LEFT, KC_RIGHT, MOD_NONE)

// RGB function encoders
ENCODER_FUNCTION(_RGB, LEFT,
                rgb_matrix_increase_speed_noeeprom,
                rgb_matrix_decrease_speed_noeeprom, MOD_NONE)
```


Unicode
----------------
This is just the basic unicode example everyone seems to have.
Add your keys to send unicode strings like so.

```
 UC_STR(UC_DISA, "ಠ_ಠ")
```

Send_string
--------------
This is just basic send string functionality using *SEND_STRING* and 
*SEND_STRING_DELAY*. Each entry defines a key to send a string.

```
SEND_STR(MYKEY, "this is a test")
SEND_STR_DELAY(VRSN, QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE)
```

Console key logging - for heat maps.
----------------------
Both CONSOLE_ENABLE and CONSOLE_KEY_LOGGER_ENABLE must be enabled for this to work.

This is a console key logger which can save keys typed for analysis of keymaps
using Vlad/Precondition's heat map tool. The code for the logger came from
[here](https://precondition.github.io/qmk-heatmap#how-to-collect-the-required-data)
The explanation and use of the heatmap is [here](https://precondition.github.io/qmk-heatmap)

There is a script ```listen_keylogger.sh``` which should be run to collect
the keylogger data. 

This does require **hid_listen** to be installed on the computer.
On Arch linux this can by installed from the AUR with ```yay -S hid_listen```

The output can also be seen just by using ```qmk console```.

Note: _print.h_ is automatically included when CONSOLE_ENABLE is set. This allows 
for debug messages anwhere in the code base as needed to see what might be going
on.

Tap Dance
--------------------
I had a lot of tap dance, It's turned off. It's big. tap-hold works pretty well most of the time, instead.
My favorites were tab-backtab,  home-end.


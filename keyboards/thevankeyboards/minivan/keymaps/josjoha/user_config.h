/*
 * License (GPL):
  
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

 * © 2019,2020 by Jos Boersema
 *
 */


// ------------------------------------- ⬇ --------------------------------------
//                                 Configuration:
// ------------------------------------- ⬇ --------------------------------------

  // (For the non-coders: “_Remove_” means to place ‛//’ in front of a line. The rest of the line becomes a comment.
  //                      Placing ‛//’ in front of a line, means whatever follows it will be ignored during compilation.
  //                      “_Activate_”   means to *delete* the two ‛//’ in front. Now the rest of the line *will* be compiled
  //                      /* ... */ is another a way to turn “...” into being a comment which is ignored during compilation.
      
       /*                       ➡ Letters / Numbers & Symbols layouts ⬅
        *
        * Here you can configure what letters layer (BASE layer), and number&symbols layer you
        * want. This is a dual layout system, so you can choose a second pair as well. You can
        * switch between them with a key on the _RAR layer. All the other layers are the same,
        * regardless of your choice in letter/number&symbol layers.
        *
        * The letters layer is the BASE layer, from which you also reach all other layers.
        * The letters it has is the alphabet in its simplest form: abcdefghijklmnopqrstuvwxyz.
        * The numbers & symbols layer has what you find on any regular keyboard: 123… !@#… []/…
        * The numbers & symbols layer is made to fit the Letters layer, due to small differences
        * between layouts like Qwerty and Dvorak (in this case the symbols ‛-’, ‛/’, ‛?’, and ‛_’).
        *
        * Example: A Qwerty letters layer, with a fitting numbers & symbols layer, as ‛Default’.
        *          A Dvorak letters layer, with a fitting numbers & symbols layer, as ‛Alternate’.
        *
        * You will be asked to configure one layout as ‛Default’ and another as ‛Alternate’.
        *
        * A bases layout may have locally re-defined one or more of the common layers. If you
        * choose two bases layouts who re-define the same common layer locally, you will need
        * to choose either one by commenting out the other.
        */
        //
        //          • Dvorak
        //                  (a regular Dvorak layout)
        // _Activate_ one of these two, _remove_ the other.
  #define BASE_DVORAK__DEF_BASE // _Activate_ if you want Dvorak on the ‛Default’ spot
//#define BASE_DVORAK__ALT_BASE // _Activate_ if you want Dvorak on the ‛Alternate’ spot
        // 
        //          • Dvorak descramble mode
        //                  (Dvorak for a computer already remapping to Dvorak)
        //  This layout is only available on ‛Alternate’, because of the special _HALF_ descramble mode.
//#define BASE_DVORAK_DESCRAMBLE__ALT_BASE // _Activate_ if you want Dvorak on the ‛Alternate’ spot
        // 
        //          • Qwerty
        //                   (a regular Qwerty layout)
        //  _Activate_ one of these two, _remove_ the other.
//#define BASE_QWERTY__DEF_BASE // _Activate_ if you want Qwerty on the ‛Default’ spot
//#define BASE_QWERTY__ALT_BASE // _Activate_ if you want Qwerty on the ‛Alternate’ spot
        // 
        //          • Colemak
        //                   (a regular Colemak layout)
        //  _Activate_ one of these two, _remove_ the other.
//#define BASE_COLEMAK__DEF_BASE // _Activate_ if you want Colemak on the ‛Default’ spot
//#define BASE_COLEMAK__ALT_BASE // _Activate_ if you want Colemak on the ‛Alternate’ spot
        // 
        //          • Numpad
        //                   (a numerical keypad, one for left hand and one for right hand)
        //  _Activate_ to get Numpad on Alternate. There is no option for Numpad on ‛Default’ base.
  #define BASE_NUMPAD__ALT_BASE // _Activate_ if you want Numpad on the ‛Alternate’ spot
        // ➡ ➡ ➡ This Base layer has configuration options at the top of its file. See ./base_numpad.c
        //
        /*                      ➡ Eviscerations ( ① / ② ) ⬅
         */
        /*          • Single layout
         *
         * Removes the ‛Alternate’ base layers, and removes the switch key on _RAR.
         * ⚠ You have to not define a ‛Alternate’ base layer pair. Define only a ‛Default’ pair.
         */
//#define MINIFAN_SINGLE_LAYOUT // _Activate_ to only have the ‛Default’ base layers, _remove_ to also have ‛Alternate’.


        /*                      ➡ Startup layer ⬅
         *
         * You can define which of the two BASE layers is on when powering up the keyboard.
         */
//#define STARTUP_ALTERNATE // Example: For BASES_QWERTY_DVORAK defined: _remove_ is startup in Qwerty, _active_ is
                            //              startup in Dvorak


        /*                      ➡ How many hardware keys 1st row ⬅
         *
         * Define how many keys your keyboard has.
         */
         // Default               (12x12x12x8 keys)
         //'Command'              (12x12x12x9 keys) + key on the left
         //'Arrow'                (12x12x12x9 keys) + key on the right
         //'South paw' + 'Arrow'  (12x12x12x10 keys)
//#define MORE_KEY__COMMAND // Additional key 1st row on the left. This hardware layout is called 'Command' or 'South paw'.
//#define MORE_KEY__ARROW   // Additional key 1st row (counting from row with space-bar) on the right, called 'Arrow' layout. 
         //
         // See below for how to define your additional key(s).


        /*                        ⚠ ≠ Minivan ⬅
         *
         * This section is for when you want to flash this keymap unto a board with more
         * keys than the Minivan has. 
         *
         *       Trans-Minivan keymap: 12x12x12x11, 12x12x12x12, 12x12x12x13 keys
         *                                          Example board: Planck (12x12x12x12)
         *
         * It is assumed that you enabled MORE_KEY__ARROW and
         * MORE_KEY__COMMAND, to get to 12x12x12x10 keys. With this you
         * can get to one, two or three more keys on row 1, without manually
         * editing all layers. You could first edit the definition on layers that you have
         * a specific meaning for these keys, and let the rest be patched with the definitions
         * here.
         *
         * It can help to inspect the preprocessing with > gcc -E keymap.c | less
         *
         *                        Planck keyboard
         *
         * The identifier TRANSMINIVAN_MIDLEFT could help compile the layout on a Planck keyboard,
         * if it has a two unit large spacebar. You compile without TRANSMINIVAN_LEFTSIDE in that case.
         * All keys on the left, row 1 (closest to the user) shift one unit to the left, with TRANS_MIDLEFT
         * inserted on what would be the left key of the two unit spacebar (assuming that is a key).
         *
         *                         Other keyboards formats
         *
         * It is always possible to just padd the rows somewhere, if you have even more keys. On the other
         * hand, to try to cut this layout down to fewer keys than it has at minimum (12x12x12x8), is likely
         * going to reduce its functionality, and will require some puzzling to keep a well organized BASE
         * layer, and have “hold key” layer switching work correctly.
         *
         * FIXME: not been compiled or tested for any boards.
         */
//#define TRANSMINIVAN_LAYOUT ....... // Set this to something with the needed amount of keycodes.
                          // Your values are inserted here: [ _LTR ] = LAYOUT_redefined (
                          //                                           ^^^^^^^^^^^^^^^^ (throughout all layers)
//#define TRANSMINIVAN_LEFTSIDE  // _Activate_ to get yet one more key on the left side row 1
  #define TRANS_LEFT XXXXXXX     // Define what the TRANSMINIVAN_LEFTSIDE key should be, where it is not otherwise defined.
                                 // (Ignored if TRANSMINIVAN_LEFTSIDE is _removed_).
                                 //
//#define TRANSMINIVAN_MIDLEFT   // _Activate_ to get yet one more key on the first key from center, row 1.
  #define TRANS_MIDLEFT XXXXXXX  // Define what the TRANSMINIVAN_RIGHTSIDE key should be on all layers at once.
                                 // (Ignored if TRANSMINIVAN_MIDLEFT is _removed_).
                                 //
//#define TRANSMINIVAN_RIGHTSIDE // _Activate_ to get yet one more key on the right side row 1
  #define TRANS_RIGHT XXXXXXX    // Define what the TRANSMINIVAN_RIGHTSIDE key should be, where it is not otherwise defined.
                                 // (Ignored if TRANSMINIVAN_RIGHTSIDE is _removed_).


        /*                      ➡ Defining the meaning of the additional hardware keys ⬅
         *
         * Some possibilities you might like:
         *
         * ① Number-pad and F-keys layers are only on a toggle. If you want them accessible on a hold key, you can use
         *   these additional hardware keys. Make sure to use a transparent key on that location on those layers.
         *
         * ② You can use the right side additional key for quick access to an arrow/navigation cluster (see below).
         *
         * ③ Other uses, such as a delete key and/or a special interface key your system needs.
         */
        /*          • Defining the additional key for 'South paw' (also called 'Command')
         *
         * Left side additional key. This is ignored if MORE_KEY__COMMAND is not defined.
         */
        // Configure here what this key is on the BASE layers
//#define MORE_key1_BASE KC__XGUI 
  #define MORE_key1_BASE TG ( _RAR ) // _Activate_ this to get a toggle to layer _RAR.  MO(_RAR) does not follow a BASE switch by ‛Other Base’.
        //
        // Configure here what this key is on all other layers
  #define MORE_key1      KC_DEL  // Configure here what this key is on all other layers
        //
        //
        /*          • Defining 'Arrow' hardware layout additional keys
         *
         * You can create an arrow-cluster with your additional MORE_key2 hardware key on the _MOV layer.
         * Either way: this new key can toggle to _MOV layer, with the key that on the _MOV layer becomes the down-arrow,
         * in the middle of an arrow cluster. To do that, uncomment MOREKEY2_ARROW_CLUSTER.
         * The keys that are by default defined on those keys on _MOV layer, will now be overwritten (they are not typically
         * that much used there).
         *
         * Arrow cluster for 'arrow' layout: _activate_ MOREKEY2_ARROW_CLUSTER and _activate_ #define MORE_key2 _MOV_UP
         * No arrow cluster for 'arrow' layout: _remove_ MOREKEY2_ARROW_CLUSTER, and set MORE_key2 to whatever you want.
         */
  #define MOREKEY2_ARROW_CLUSTER // Arrow cluster on _MOV layer. This is ignored if MORE_KEY__ARROW is not defined.
                             // This will cost you 'Right Alt' and 'GUI' on the _MOV layer.
  #define MOREKEY2_ADD_NAVIGATION // Additional navigation keys around arrow cluster MOREKEY2_ARROW_CLUSTER. Ignored if MOREKEY2_ARROW_CLUSTER is not defined.
                                // Note: this will cause mouse buttons 'BTN4' and 'BTN5' on the _MOV layer to be moved.
        /*
         * Define the key you want on the additional key (leave it to _MOV_UP if you want an arrow cluster, easily
         * accessed with this key): 
         */
  #define MORE_key2 _MOV_UP // Right side additional key. This is ignored if MORE_KEY__ARROW is not defined.
//#define MORE_key2 <...your choice...> // Right side additional key.
        //


        /*                      ➡ Arrows/Navigation cluster ⬅
         */
        /*          • Navigation cluster configuration
         * 
         * _Activate_ below line to use a "WASD" type layout (on the spot where WASD is in Qwerty).
         * _Remove_ if you prefer a flat type layout, with arrows in a row, on the right hand.
         */
  #define ARROWS_TRIANGLE // Implies mouse is also similarly in a triangle.
        /*
         *          • VI editor arrows
         *
         * Vi is a famous editor, with its own peculiar text cursor movement arrangement (arrows).
         * This option modifies the flat arrows layout on the right hand, to be like the “HJKL” 
         * arrows in the editor vi(1). “HJKL” meaning: the 7th to 10th key on the 3rd row.
         * The arrows on the additional MOREKEY2_ARROW_CLUSTER also get harmonized to be like vi.
         */
//#define VI_SWITCHERYDOO //  You have to _remove_ ARROWS_TRIANGLE, or this gets ignored.


        /*                      ➡ Number pad Configuration⬅
         *
         * This concerns the Numbers Pad layer, which is part of the common layers (not the Bse
         * layer, which also has a Numbers Pad option).
         *
         * There are two compile versions for the number pad layer ‛_PAD’, in the common layers. 
         *
         * _Activate_ the below to have the numbers pad _PAD layer resemble the squared layout of
         * a numerical keyboard, allowing to type all numbers with the right hand.
         * _Remove_ the below to have the numbers in this layer follow the layout of the _NSY layer,
         * with the numbers on a line from left to right on the home row, across both hands.
         */
  #define NUMPAD_COMMON_SQUARE // _Activate_ to resemble a one handed numerical keyboard.


        /*                      ➡ Speed measuring ⬅
         *
         */
  #define SPEED_INIT // _Activate_ for default speed measuring on, _remove_ to set off at startup.
        /*
         * Led color configuration. You can see the speed you have configured below directly on the keyboard,
         * after you compiled and flashed it.
         * Set speed measuring to <off>.
         * Hold the 'Report' key for one second, then release. The keyboard prints a number, which is the
         * amount of characters per second for which that color is then being shown. Hold it again for
         * a second, and it increments. Toggle speed measuring on/off to restart.
         * You can play with the below settings until you like the result.
         *
         * The default values (8, 160 respectively) are starting at blue, avoiding confusion with default
         * cyan for BASE layer, going to purple and further avoiding confusion with text size counting.
         * Very fast typers could reach red, and then it goes further to yellow, etc.
         */
  #define SPEED_COUNTDOWN 25 // After how many keypresses to update the effect(s).
  #define SPEED_HUE_STEP 8 // For each key/sec faster, the hue value of HSV goes this step further.
  #define SPEED_HUE_START 160 // The starting hue for 0 k/s (0 = 255 = red).
        /*
         * Speed report in words-per-minute (wpm) rather than keystrokes-per-second (k/s). wpm = k/s * ⁶⁰/₅ = k/s * 12
         */
  #define WORDS_PER_MINUTE // _Activate_ to get speed report in words-per-minute, _remove_ to get it in keystrokes-per-second (k/s).


        /*                      ➡ Text size counting ⬅
         *
         */
  #define COUNT_INIT // _Activate_ for default character/word counting on, _remove_ to set off at startup.


        /*                      ➡ GUI left/right ⬅
         *
         * _Activate_ below line to have LGUI (also called OS or Win key, etc) where RGUI is, 
         * and RGUI where LGUI is.
         */
  #define SWITCH_GUIS // _Activate_ this if you want LGUI on the BASE layer rather than RGUI, despite that spot being on the right.


        /*                      ➡ Alternate currency symbol ⬅
         *
         * _Activate_ the below to get a Euro symbol, where ƒ (Dutch Guilder) is on the default map (_DRA layer).
         */
//#define UNICODE_CURRENCY 0x20ac // Hex number, euro symbol €. The unicode hex number for position ƒ in the default keymap.


        /*                      ➡ Check boxes or Pointers ⬅
         *
         * You can have these symbols (checkboxes):  ☐  ☒  ☑  🗹
         *                     or these (pointers):  ⮘  ⮙  ⮚  ⮛
         */
//#define POINT_ON_CHECKBOXES // _Activate_ to get arrows, _remove_ to get checkboxes on _DRA layer.


        /*                      ➡ Eviscerations ( ② / ② ) ⬅
         */
        /*          • Removing the numbers pad _PAD layer
         *
         * You may have no use for this common layer, if you have a numerical keypad on the Alternate Base already.
         *
         * ⚠ Note: ./base_numpad.h can overrides this setting, if compiled with that ‛Base layers’.
         */
  #define REMOVE_PAD // _Activate_ to strip out the _PAD layer, _remove_ to have the _PAD layer.
        //
        /*          • Removing one or more of the Unicode layers _ACC, _DRA or_BON
         */
        /* Removes the _ACC layer, optionally redirect its key. This can save some 750 bytes. 
         */
//#define REMOVE_ACC // _Activate_ to strip out the _ACC layer, _remove_ to have the _ACC layer.
        /* Unless REMOVE_ACC is _active_, the next defines which redirect the _ACC key(s) are ignored. */
//#define _ACC_KEY_ALT_LAYER _BON // _Activate_ to make the key(s) that normally goes to _ACC, go to _BON instead.
//#define _ACC_KEY_ALT_LAYER _DRA // _Activate_ to make the key(s) that normally goes to _ACC, go to _DRA instead.
        /*
         *
         * Removes the _DRA layer, optionally redirect its key. Also saves some 750 bytes.
         */
//#define REMOVE_DRA // _Activate_ to strip out the _DRA layer, _remove_ to have the _DRA layer.
        /* Unless REMOVE_DRA is _active_, the next defines which redirect the _DRA key(s) are ignored. */
//#define _DRA_KEY_ALT_LAYER _ACC // _Activate_ to make the key(s) that normally goes to _ACC, go to _ACC instead.
//#define _DRA_KEY_ALT_LAYER _BON // _Activate_ to make the key(s) that normally goes to _ACC, go to _BON instead.
        /*
         *
         * Removes the _BON layer, optionally redirect its key. Also saves some 750 bytes.
         */
//#define REMOVE_BON // _Activate_ to strip out the _BON layer, _remove_ to have the _BON layer.
        /* Unless REMOVE_BON is _active_, the next defines which redirect the _BON key(s) are ignored. */
//#define _BON_KEY_ALT_LAYER _ACC // _Activate_ to make the key(s) that normally goes to _BON, go to _ACC instead.
//#define _BON_KEY_ALT_LAYER _DRA // _Activate_ to make the key(s) that normally goes to _BON, go to _DRA instead.
        /*
         *
         *          • Removing groups of characters
         */
        /*
         * The below cut out an amount of symbols on a given layer, to simplify and/or reduce firmware size a little.
         */
//#define ALL_DRA_BON_EVISCERATIONS // _Activate_ this to _remove_ the below all at once. (Seems to save only ±114 bytes)
                                    //
  #define BOX_DRAWINGS // _Activate_ to get box drawings on _BON. Horizontal lines (━─┄┅) on _DRA are not affected.
                   // Affected on rows 2 and 3: ┣┫┏┗┃┇┛┓
                   // Full, 3rd row, boxdr.:  Ctrl   ① ⬅   ② ⬇   ③ ➡  ④ ┏  ⑤  ┓  ⑥ ┃  ⑦ ┇   ⑧ ╋  ⑨    ⓪ ∞   — 
                   // Full, 2nd row, boxdr.:  LSht   ‹     ›     ÷    ☞ ┗  ≠  ┛  ✗ ┣  ✓ ┫   ⚠    «    »     RSht
                   //
                   // 3rd row, no boxdrawing: Ctrl   ① ⬅   ② ⬇   ③ ➡  ④    ⑤     ⑥    ⑦     ⑧    ⑨    ⓪ ∞   — 
                   // 2nd row, no boxdrawing: LSht   ‹     ›     ÷    ☞    ≠     ✗    ✓     ⚠    «    »     RSht
                   //
  #define SUB_SCRIPT_NUMS // _Activate_ to get subscript numbers (₁₂₃…₀) on _DRA.
                      // Affected on row 3: ₁₂₃₄₅₆₇₈₉₀
                      // Thinned out 3rd row: xxx   ¹     ²     ³    ⁴    ⁵    ⁶     ⁷     ⁸     ⁹     ⁰   xxx
                      // Full 3rd row:        xxx   ¹₁    ²₂    ³₃   ⁴₄   ⁵₅   ⁶₆    ⁷₇    ⁸₈    ⁹₉    ⁰₀  xxx
                      //
  #define FULL_DRA_2NDROW // _Activate_ to have symbols on all unshifted + shifted positions on _DRA, 2nd row.
                      // Affected: 「 」 〇 § · 🗹  《 》
                      // Full 2nd row:        LSht  「━   」─   °〇  •§   …·   ☐ ☒   ☑ 🗹   ¿¡ 《┄   》┅    Rsht
                      // Thinned out 2nd row: LSht  ━     ─     °    •    …    ☐ ☑   ☑     ¿¡  ┄    ┅      RSht
                      //
  #define FULL_DRA_4THROW // _Activate_ to have symbols on all unshifted + shifted positions on _DRA, 4th row.
                      // Affected 4th row: „ ≤ ≥ ∅ ¢ ƒ ❦ 🙂 🙁 👍 👎 ⁽ ₍ ⁾ ₎
                      // Full 4th row:        BASE  “„    ”≤    £≥   ∅ ¢  ±ƒ   ❦ ♥   🙂🙁  👍👎 ⁽₍   ⁾₎    Bkspc
                      // Thinned out 4th row: BASE  “     ”     £         ±    ♥                           Bkspc
                      //
  #define FULL_BON_4THROW // _Activate_ to have symbols on all unshifted + shifted positions on _BON, 4th row.
                        // Affected 4th row: 🛠 ¤ ∑ ‱ ٭ 😊 ⍨  ⃰ ⁻ ⁺ 🄯 ©
                        // Full 4th row:        BASE  ‛🛠   ’⬆    ¤ 🄯   ∑ ©  ‰‱   ★٭   😊⍨    × ⃰   √    ⁻⁺    Bkspc
                        // Thinned out 4th row: BASE  ‛     ’⬆               ‰    ★           ×               Bkspc
                        //


       /*                       ➡ Middle led BASE layer: last layer color ⬅
        *
        * It is a bit wacky that in the BASE layer the middle led shows the last active layer. Here you
        * can stop this behavior. This results in the same middle led behavior, given for when the side
        * leds are set off: one special color for the BASE layer (cyan) on middle led.
        */
  #define MIDLED_BASELAYER_CONSTANT // _Activate_ for one color on middle led for BASE layer, _remove_ to show last layer color


// ------------------------------------- ⬆ --------------------------------------
//            Below here no more comfortable configuration options.....
//            There may be configuration options in the layout ./bases_....h file you chose.
// ------------------------------------- ⬆ --------------------------------------



// ------------------------------------- ⬇ --------------------------------------
//                                 Base layer headers
// ------------------------------------- ⬇ --------------------------------------

//                         * Numpad *
# if defined(BASE_NUMPAD__ALT_BASE)
#     include "./base_numpad.h" // Numbers pad header
# endif

// // ⬇ insert your ./base_YOUR_KEYMAP.h #include here:

//                         * YOUR KEYMAP *
// # if defined(BASE_YOUR_KEYMAP__DEF_BASE) || defined(BASE_YOUR_KEYMAP__ALT_BASE)
// #     include "./base_YOUR_KEYMAP.h" // Your Keymap header/configuration file.
// # endif

// // ⬆

// ------------------------------------- ⬆ --------------------------------------
// Base layer headers are best #included here, so the preprocessor statements 
// following the user configuration block can pick up on anything that was set.
//
// Example: base_numpad.h _activate_ ‛REMOVE_PAD’. Based upon that, the preprocessor
// constant ‛_PAD’ is changed into ‛_FUN’ in the below statements.
// ------------------------------------- ⬆ --------------------------------------



// The below sets some things up based on the above #defines.

// This is sort of a hack. It re-defines _ALT_BASE and _ALT_NSY to point to the same
// layer as _DEF_BASE and _DEF_NSY, because there are quite a few references to the
// former and putting #if then around each one complicated the code even more. If needed,
// it can be changed later. This option already reduces firmware size, so we should be
// well below the maximum.
# ifdef MINIFAN_SINGLE_LAYOUT
#     define _ALT_BASE _DEF_BASE
#     define _ALT_NSY _DEF_NSY
# endif

// This triggers the compilation of special _HALF_ descramble mode, where you access
// the Unicode layers without passing them through the descramble system (middle led
// lit on _RAR_ when cycling through the base layers with ‛Other Base’ key).
# ifdef BASE_DVORAK_DESCRAMBLE__ALT_BASE
#     define DVORAK_DESCRAMBLE_HALF
# endif

// Prevent likely erroneous configuration. If no 'Arrow' hardware layout, then not patching in an arrow cluster.
# if !defined(MORE_KEY__ARROW) && defined(MOREKEY2_ARROW_CLUSTER)
#     undef MOREKEY2_ARROW_CLUSTER
# endif

# if !defined(MORE_KEY__ARROW) && defined(MOREKEY2_ADD_NAVIGATION)
#     undef MOREKEY2_ADD_NAVIGATION
# endif
# if !defined(MOREKEY2_ARROW_CLUSTER) && defined(MOREKEY2_ADD_NAVIGATION)
#     undef MOREKEY2_ADD_NAVIGATION // Only navigation keys, when the are arrows defined.
# endif

// When choosing 'triangle' arrows, then they go left. Not 'triangle' arrows, than right.
# ifdef ARROWS_TRIANGLE
         /* _Activate_ below line to put the arrows on the left, comment out to have arrows right. */
#     define ARROWS_LEFT // Implies mouse is right
# endif


// Set up user GUI choice:
# ifndef SWITCH_GUIS
#     define KC__XGUI KC_LGUI // Name logic is alphabetic order left to right …X (…) …Y in layout definitions..
#     define KC__YGUI KC_RGUI // .. meaning KC__XGUI is left on the keymap, KC__YGUI is right.
# endif

# ifdef SWITCH_GUIS
#     define KC__XGUI KC_RGUI
#     define KC__YGUI KC_LGUI
# endif


// Define the layout macro for the amount of hardware keys.
// These for Minivan are defined up in the code tree.
# if !defined(MORE_KEY__COMMAND) && !defined(MORE_KEY__ARROW)
#     define LAYOUT_redefined LAYOUT                // Default (8 keys on 1st row)
# endif

# if !defined(MORE_KEY__COMMAND) && defined(MORE_KEY__ARROW)
#     define LAYOUT_redefined LAYOUT_arrow          // Additional key 1st row on the right. 'Arrow'
# endif

# if defined(MORE_KEY__COMMAND) && !defined(MORE_KEY__ARROW)
#     define LAYOUT_redefined LAYOUT_command        // Additional key 1st row on the left. 'Command'
# endif

# if defined(MORE_KEY__COMMAND) && defined(MORE_KEY__ARROW)
#     define LAYOUT_redefined LAYOUT_arrow_command  // Additional keys 1st row both left and right. 'Arrow' + 'Command'
# endif

# ifdef TRANSMINIVAN_LAYOUT 
#     undef LAYOUT_redefined
#     define LAYOUT_redefined TRANSMINIVAN_LAYOUT
# endif


// Process user config setting for speed measuring
# ifdef SPEED_INIT
#     define SPEED_INIT_VALUE TRUE
# else
#     define SPEED_INIT_VALUE FALSE
# endif
// Process user config setting for text size measuring
# ifdef COUNT_INIT
#     define COUNT_INIT_VALUE TRUE
# else
#     define COUNT_INIT_VALUE FALSE
# endif


// Get all key reductions at once
# ifdef ALL_DRA_BON_EVISCERATIONS
#     ifdef BOX_DRAWINGS   
#         undef BOX_DRAWINGS   
#     endif

#     ifdef SUB_SCRIPT_NUMS
#         undef SUB_SCRIPT_NUMS
#     endif

#     ifdef FULL_DRA_2NDROW
#         undef FULL_DRA_2NDROW
#     endif

#     ifdef FULL_DRA_4THROW
#         undef FULL_DRA_4THROW
#     endif

#     ifdef FULL_BON_4THROW
#         undef FULL_BON_4THROW
#     endif
# endif

// This resolves compiling “TO (_BON)” on the _FUN layer.
# ifdef REMOVE_BON
#     undef _BON
#     ifdef _BON_KEY_ALT_LAYER
#         define _BON _BON_KEY_ALT_LAYER  // To what user wants
#     else
#         define _BON _FUN                // void behavior
#     endif
# endif

// This resolves compiling “TO (_PAD)” on the _FUN layer.
# ifdef REMOVE_PAD
#     undef _PAD
#     define _PAD _FUN                // void behavior
# endif

// If the _ACC layer hold key has no function anymore because the layers _ACC and _BON to which it
// switches have been removed, and no alternative use been set, that key reverts to being KC_DEL,
// and the whole macro CHOLTAP_ACCE it normally activates gets cut.
# if  defined(REMOVE_ACC) \
  && !defined(_ACC_KEY_ALT_LAYER) \
  &&  defined(REMOVE_BON) \
  && !defined(_BON_KEY_ALT_LAYER)
#     define CHOLTAP_ACCE KC_DEL // replaces in the keymap
#     define CHOLTAP_ACCE_NOP    // cuts CHOLTAP_ACCE out of macros
# endif

// Here all Unicode layers _ACC, _DRA and _BON have been removed, and none of their key(s) has
// been re-assigned to a useful purpose. That makes that whole system redundant, so it is simplified.
# if  defined(REMOVE_ACC) \
  && !defined(_ACC_KEY_ALT_LAYER) \
  &&  defined(REMOVE_DRA) \
  && !defined(_DRA_KEY_ALT_LAYER) \
  &&  defined(REMOVE_BON) \
  && !defined(_BON_KEY_ALT_LAYER)
#     define CHOLTAP_ACCE KC_DEL // replaces in the keymap
#     define CHOLTAP_ACCE_NOP    // cuts CHOLTAP_ACCE out of macros
#     define DUO_HOLD_BASIC   // cuts out the long DUO_HOLD macro, replaces it with a simple 'descramble'-aware hold(_NSY/_DDN) 
# endif

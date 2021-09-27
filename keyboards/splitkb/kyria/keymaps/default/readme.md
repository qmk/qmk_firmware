# Kyria's Default Keymap

![KLE render of the default Kyria keymap with QWERTY as the base layer. Layers are shown in sublegends.](https://i.ibb.co/RQZx2dY/default-kyria2.jpg)


The default keymap contains 5 layers which allows it to include all keys found on an ANSI layout TKL keyboard plus media keys.
Hardware features of the Kyria such as OLEDs, rotary encoders and underglow are also supported.

The five different layers are the following:
1. Base layer (QWERTY, Colemak-DH or Dvorak)
2. Navigation layer
3. Symbols/Numbers layer
4. Function layer
5. Adjust layer

## Base layer(s)
```
Base Layer: -

,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   -  |   -  |   -  |   -  |   -  |                              |   -  |   -  |   -  |   -  |   -  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|Ctrl/Esc|   -  |   -  |   -  |   -  |   -  |                              |   -  |   -  |   -  |   -  |   -  |Ctrl/ - |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   -  |   -  |   -  |   -  |   -  | [ {  |CapsLk|  |F-Keys|  ] } |   -  |   -  |   -  |   -  |   -  | RShift |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
                       |      |      | Enter|      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```
Three different well-known keyboard layouts are provided to fill in the placeholder `-` keys: QWERTY, Colemak-DH, and Dvorak. The default layer can be changed at runtime, more info on that in the section on the [adjust layer](#adjust-layer).

For the rest of this write-up, the base layer will be assumed to be QWERTY and will be used as a reference to describe physical keys, e.g. “<kbd>B</kbd> key” vs, the much more verbose, “lower inner index key”.

```
Base Layer: QWERTY

,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
                       |      |      | Enter|      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

Aside from variations in the alpha cluster, the rest of the base keys remain the same and are designed to feel familiar.

![Step-by-step animation of the transformation of an ortholinear TKL to a Kyria](https://i.imgur.com/uVDCOek.gif)

<details>
After making transformations to the classic ANSI US QWERTY TKL 60% to arrive to the layout of the Kyria, as illustrated in the animation above, the result looks like this:

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
| Cap Lk |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : | '  "   |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? | RShift |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       | LCtrl| LGUI | LAlt | Space|      |  |      | Space| AltGr| RGUI | Menu |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  '----------------------------------'
```

First thing to notice is the presence of blank keys. To fill in the blank keys above the <kbd>Space</kbd> keys, we can take inspiration from other split keyboards featuring an extra inner index column on each half. A common mapping for those kind of keys are the bracket keys that got removed in the fourth step of the animated transformation. The thumb keys besides <kbd>Space</kbd>s is prime real estate for dedicated layer-switching keys. It doesn't matter on which side is assigned the sym-layer-switch key but it helps to keep the nav-layer-switch on the left in order to keep the arrow keys on the right side like on a classic keyboard, so we'll put nav on the left and sym on the right. We'll address the remaining blank thumb keys later.

The base layer is starting to form but there remains some flaws. One glaring issue is the position of Control. Control is a very commonly used function but the key on which it sits right now is way too tucked in under the hand to be able to press it comfortably with either the thumb or the pinky from resting position. In fact, installing a rotary encoder there is a common move among Kyria users and I guarantee you that activating Control by holding down a rotary encoder does not spark joy. Instead, let's employ a popular trick that involves remapping the current Caps Lock key, which is positioned at a comfortable position on the keyboard, to Control. 

We can go further though; a variant of this trick makes the Control key produce Escape when tapped. This is called a “modtap”. There is no use to tapping Control by itself without chording it with another key and there is no use to holding down the Esc key so why not combine the two into a single key?

All of this leaves us with three blank keys.

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : | '  "   |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |      |  |      |  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
`--------+-------------+--------------------+------+------|  |------+------+--------------------+------+---------------'
                       |      | LGUI | LAlt | Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  '----------------------------------'
```

These keys are not easily reachable while touch typing (that is, not reachable without picking up your hand) and should thus be associated with functions that you are not likely to be typed within a stream of text. The idea is that if you have to pick up your hand to hit a key, you want it to be at a time when you are likely to be pausing your interaction with the machine, rather than in the midst of a flurry of typing.  They're thus well suited for accessing the adjust layer and the function layer. We can also toss in Caps Lock even though it is an editing-type function that gets used within a stream of text because shouting in ALL-CAPS should be a deliberate action.

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : | '  "   |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |Adjust| LGUI | LAlt | Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

The next glaring issue is the absence of an Enter key on the current base layer this far. Enter is a very frequently used key so it deserves to be placed at a good spot in the keymap. The best way to insert it in the keymap with minimal changes to the current layout is to use modtaps. A tempting solution is to turn the <kbd>RShift</kbd> key into a <kbd>RShift/Enter</kbd> modtap but that can result in chat messages sent too frustratingly early when you're not used to it. Using GUI is also sub-optimal because tapping the GUI modifier actually has a use as opposed to taps of the Control or the Shift key. Pressing and releasing the GUI key by itself opens the App menu in many desktop environments. The natural choice is thus <kbd>LAlt/Enter</kbd>. That way, Enter is 1u away from resting thumb position and is unlikely to get accidentally activated because Alt is very rarely used in the midst of prose.

Finally, we're one Quality-Of-Life update away from the actual base layer. <kbd>Ctrl/' "</kbd> not only preserves symmetry in the keymap with <kbd>Ctrl/Esc</kbd> but also helps balance the load between your pinkies and invites you to use both hands instead of contortions. Perhaps more importantly, it also frees you from the necessity of picking up your hand, breaking touch typing position and pressing a pinky key with your ring finger in order to execute Ctrl+A or Ctrl+Z. That becomes even more important on a board with such an aggressive pinky columnar stagger like the Kyria.


```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
                       |      |      | Enter|      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

</details>

## Navigation layer

```
Nav Layer: Media, navigation
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

This is where you'll find all the keys that are generally between the main block of a classic keyboard and the numpad in addition to media controls and modifiers on easy access on the home row for fast and comfortable chording with navigation keys.

Useful mnemonics:
- “GACS” to remember the order of the modifiers on the left-hand home row
- <kbd>Scroll Lock</kbd> is on the same key as <kbd>Caps Lock</kbd> because they're both locks
- <kbd>Delete</kbd> is on the same key as <kbd>Backspace</kbd> because they both erase characters
- <kbd>Home</kbd> is the leftmost position on the current line so it is above <kbd>←</kbd>. Same logic applies for <kbd>End</kbd>.
- <kbd>Media Previous</kbd> = ⏮, <kbd>Media Next</kbd> = ⏭
- <kbd>Page Up</kbd>, <kbd>Page Down</kbd> and <kbd>Volume Up</kbd>, <kbd>Volume Down</kbd> are positioned like the main <kbd>Up</kbd> and <kbd>Down</kbd> keys.

## Sym layer
```
Sym Layer: Numbers, symbols
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```
The top row is the unshifted num row, the home row of the layer is the shifted num row and the bottom row contains the hyphen `-` and the underscore `_` on the best lower row spot because of how frequent they are as well as redundant symbols that are already present on the base layer but are reproduced here to avoid juggling back and forth between base, shift, and sym when typing a string of symbols.

The layout of the first two rows needs no introduction, you're already used to them but it's worth looking into the structure of the bottom row.

The two halves are mirrored in a sense. On the right, you can find <kbd>,</kbd> <kbd>.</kbd> <kbd>/</kbd> at their usual spots with the addition of <kbd>Shift</kbd>+<kbd>/</kbd>=<kbd>?</kbd> to the right of the <kbd>/</kbd> key to remove the need to press simultaneously <kbd>Sym</kbd> and a <kbd>Shift</kbd> key to access `?`. 

Now, if you look at the left side, you'll notice that the mirror of <kbd>,</kbd> is <kbd>;</kbd>, the mirror of <kbd>.</kbd> is <kbd>:</kbd> and the mirror of <kbd>/</kbd> is <kbd>\\</kbd>. The same logic used for <kbd>Shift</kbd>+<kbd>/</kbd>=<kbd>?</kbd> also applies to <kbd>Shift</kbd>+<kbd>\\</kbd>=<kbd>|</kbd>.

In case you wish to combine <kbd>Shift</kbd> with a symbol key anyways, you can hold down <kbd>Shift</kbd> on the base layer with your pinky, activate <kbd>Sym</kbd> with your right thumb and while still holding down the <kbd>Shift</kbd> key, tap your desired symbol key. Same thing if you need <kbd>Ctrl</kbd>+<kbd>Digit</kbd>.

## Function layer
```
Function Layer: Function keys
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```
In a similar fashion to the nav layer, pressing down `FKEYS` with the right thumb enables a numpad of function keys on the opposite hand and modifiers on the right-hand home row. Once again, mirror symmetry is leveraged in this keymap for the order of the right-hand modifiers.

The <kbd>Alt</kbd> modifier, despite being situated on the right half of the keyboard is *not* `KC_RALT`, it is `KC_LALT`. `KC_RALT` is actually the <kbd>AltGr</kbd> key which generally acts very differently to the left <kbd>Alt</kbd> key. Keyboard shortcuts involving <kbd>AltGr</kbd>+<kbd>F#</kbd> are rare and infrequent as opposed to the much more common <kbd>Alt</kbd>+<kbd>F#</kbd> shortcuts. Consequently, `KC_LALT` was chosen for the function layer.

Since there are more than 10 function keys, the cluster of F-keys does not follow the usual 3×3+1 numpad arrangement.


## Adjust layer
```
Adjust Layer: Default layer settings, RGB
                                                                                                                         
,-------------------------------------------.                              ,-------------------------------------------.
|        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

Default layer settings on the left and various RGB underglow controls on the right.

The default layer settings are lined up on the middle finger column because the home middle finger key is <kbd>D</kbd> on QWERTY (like the “D” in “Dvorak”) and the lower middle finger key is <kbd>C</kbd> on QWERTY (like the “C” in “Colemak”). I can hear you say that “QWERTY” doesn't start with “E” but Dvorak and Colemak were already aligned in a column so the QWERTY may as well join the formation.

NOTE: The default layer settings set by those keys are *NOT* stored in EEPROM and thus do not persist through boots. If you wish to change the default layer in a non-volatile manner, either change the order of the layers in the firmware, for example like so if you want to set Dvorak as the new default:
```c
enum layers {
    _DVORAK = 0,
    _QWERTY,
    _COLEMAK_DH,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST
};
```
or re-define the `QWERTY`, `COLEMAK` and `DVORAK` keys to point to custom keycodes starting on `SAFE_RANGE` and calling the `set_single_persistent_default_layer` function inside of `process_record_user`.

## Hardware Features

### Rotary Encoder
The left rotary encoder is programmed to control the volume whereas the right encoder sends <kbd>PgUp</kbd> or <kbd>PgDn</kbd> on every turn.

### OLEDs
The OLEDs display the current layer at the top of the active layers stack, the Kyria logo and lock status (caps lock, num lock, scroll lock).

### Underglow
The underglow LEDs should be red.

## Going further…

This default keymap can be used as is, unchanged, as a daily driver for your Kyria but you're invited to treat your keymap like a bonsai. At the beginning, it's just like the default keymap but from time to time, you can tweak it a little. Cut a little key here, let another combo grow there. Slowly but surely it will be a unique keymap that will fit you like a glove.

Check out the #keymap-ideas channel on the official SplitKB Discord server for inspiration.

256k HHKB Layout:
===

this is my personal layer that i use on my Tina-C HHKB layout board with a DZ60 PCB.
---

there is 1 base layer and 4 modifyer layers:

BASE:
---

```
 /* BASE LAYER
 *
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \| | ~ ` |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
 * |-----------------------------------------------------------------------------------------+
 * | CTRL    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  RShift   |  FN |
 * |-----------------------------------------------------------------------------------------+
 * |              Win  |      Alt  |            Space       |   Alt     |    LIGHTS          |
 * `-----------------------------------------------------------------------------------------'
 */
 ```
 
 LAYER 1 (ALTFN):
 ---
 
 this layer is my main function layer, i changed the default HHKB function layer to suit my need and also changed the placement of the modifyer key to the left alt since i want to control the layer activation with one hand and have the other hand control the keys on that layer freely. perhaps this is due to me being left handed but it feels more natural to me this way.
 
 ```
 /* ALTFN LAYER
 *
 *  ,---------------------------------------------------------------------------------------------------------------------
 * |         | F1   | F2   | F3   | F4    | F5    | F6    | F7   | F8    | F9   | F10   | F11   | F12   | INSERT  |  _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CAPS     |   _  |   _  |   _   |    _  |    _  |    _  |    _  |    _   |  UP  |  MUTE  |  V_DEC   |  V_INC  | DEL  |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CTRL       |   _   |   _   |   _   |   _   |   _    |   _  | HOME | LEFT | DOWN | RIGHT  |   END    |    _          |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | Shift         |  _   |  _   |  _   |  _   |  _   |  _   |  _   |  PREV  |    NEXT  |  PLAY  |    _       |   _      |
 * |---------------------------------------------------------------------------------------------------------------------+
 * |                          _    |      _     |               _               |     _      |     _                     |
 * `---------------------------------------------------------------------------------------------------------------------'
 */
 ```


MOUSE LAYER (MOUSEFN):
---

*To access this layer you need to enter the ALTFN layer first then hit ESC button which will switch to the MOUSEFN layer*

this is the second *hidden* layer that controls the mouse scroll wheel directions. i find it's useful to have these controls on the keyboard for certain applications that require scrolling in all 4 directions (Simple example: expanding an image preview to full size that overflows outside of the default monitor size and using the scroll wheel to mouve the image around.)

also another benefit is that a lot of mice do not have horizontal control buttons for the scrolling

(This layer is still experimental so i might change it later or modify it but so far i enjoy it)

```
/* MOUSEFN LAYER
 *
 *  ,---------------------------------------------------------------------------------------------------------------------
 * |        |  ACC_1  |  ACC_2  |  ACC_3  |  _    |  _    |  _    |  _   |  _    |  _   |  _   |  _   |  _   | _  |  _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CAPS     |   _  |   _  |   _   |    _  |    _  |    _  |    _  |    _   |  WHEEL_UP  |  _  |   _   |    _   |   _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | CTRL       |   _   |   _   |   _   |   _   |   _    |   _  | _ |  WH_LEFT |  WH_DOWN |  WH_RIGHT  |   _    |    _   |
 * |---------------------------------------------------------------------------------------------------------------------+
 * | Shift         |  _   |  _   |  _   |  _   |  _   |  _   |  _   |   _    |    _    |    _    |    _       |   _      |
 * |---------------------------------------------------------------------------------------------------------------------+
 * |                          _    |      _     |               _               |     _      |     _                     |
 * `---------------------------------------------------------------------------------------------------------------------'
 */
 ```
 
 
 STANDARD HHKB FN LAYER (FN):
 ---
 
 this is the default HHKB function layer (mostly)... I have left it there on the same button and everything for 2 reasons: 1. for backup incase i forget where something was or if it contains a button that i did not include in my ALTFN layer. 2. as a reference for anyone else.
 
 *this layer will probably get removed once i get comfortable with my ALTFN layer.*
 
 
 
 LIGHTS LAYER:
 ---
 
 this is the basic lights layer used to control the RBG backlight on the DZ60... i have removed the 3 backlight controls since i do not use any key LED Backlight.
 
 
 ```
 /* LIGHTS LAYER
 *
 *  ,---------------------------------------------------------------------------------------------------------------------+
 * | RGB_TOGGLE  | STATIC | BREATHE | RAINBOW | SWIRL | SNAKE | KNIGHTRIDER | XMAS | STATIC_GRAD | _ |  _ | _ | _ | _ | _ |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | RBG_MOD      |  HUE_INC |  SATURATION_INC  |  BRIGHT_INC   |  _  |  _  |  _  |  _ |  _ |  _ |  _ |  _  |  _  |  _    |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | CTRL           |  HUE_DEC |  SATURATION_DEC  |  BRIGHT_DEC  |  _  |  _  |  _ |  _  |  _  |  _  |  _  |  _  |    _    |
 * |----------------------------------------------------------------------------------------------------------------------+
 * | Shift                |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |   _   |  _   |    _   |
 * |----------------------------------------------------------------------------------------------------------------------+
 * |                             _    |      _     |               _               |     _      |     _                   |
 * `----------------------------------------------------------------------------------------------------------------------'
 */
 ```
 
 
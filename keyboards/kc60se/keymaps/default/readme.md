# HHKB:  The default keymap for KC60SE

## Happy Hacker Keyboard (US layout):
* [Esc] moves down replacing [ ~ ]
* 2u [Backspace] split into [ \ ] and [ ~ ]
* move [Backspace] down a row to replace [  \  ]
* a dip switch toggles the default: Delete or Backspace, [Fn ] invokes non-default
* 2.75u [  Shift  ] split into 1.75u [Shift] & [Fn ]
* Control replaces Caplock, [FN ] [ Tab ] toggles Caplock, led under Control toggles w/Caplock
* the botom row is configurable, the Meta key could be assigned a few values with dip switches, 
* HHKB Lite2

```
    |Fn |Alt |Meta|        Space          |Meta|Alt |
    |Fn |Meta|Alt |        Space          |ALt |Meta|
```
* HHKB Professional2

```
        |Alt |Fn  |        Space          |Meta|Alt |
        |Meta|Alt |        Space          |Alt |Meta|
        |Fn  |Alt |        Space          |Alt |Meta|
```
* this PCB and keymap will support up to 8 keys on the bottom row with minimal editing.


## Base Layer

```
  ,--------------------------------------------------------------------------.
  | esc|  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |  \ |  ` |
  |--------------------------------------------------------------------------|
  | tab   |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] | bksp |
  |--------------------------------------------------------------------------|
  | ctrl   |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' |  enter   |
  |--------------------------------------------------------------------------|
  | lshift   |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / | rshift | fn0|
  `--------------------------------------------------------------------------'
         |lalt| fn0   |               space              | rgui  |ralt|
         `------------------------------------------------------------'
```
## Function Layer
* Extra keys: (mprv, mply, mnxt)
* I think the number pad * / - and + did not come on the Professional, but did on Lite

```
  ,--------------------------------------------------------------------------.
  |    | f1 | f2 | f3 | f4 | f5 | f6 | f7 | f8 | f9 | f10| f11| f12|    | ins|
  |--------------------------------------------------------------------------|
  | caps |blon|blup|    |    |NKRO|    |    | psc|slck|paus| up |    |  del  |
  |--------------------------------------------------------------------------|
  |       |vol-|vol+|mute|    |    | *  | /  |home|pgup|left|rght| penter    |
  |--------------------------------------------------------------------------|
  |          |mprv|mply|mnxt|    |    | +  | -  |end |pgdn|down|        |    |
  `--------------------------------------------------------------------------'
          |    |      |                                  | mstop |    |
          `-----------------------------------------------------------'
``` 


space space default layout 

Default layout on space space uses 2 layers + base, 5 combos, layer taps on the split space bars, and tap-hold for shift on F & J. Note that
CLI compiler must be used for all features to function. QMK Configurator does not support combos or encoders.

* combos include:

O+P = backspace

K+L = enter

S+D = tab

T+Y = escape

Q+W = delete


* The encoders are also set to function differently depending on layer:

right encoder:
default = volume up/down

symbol layer (hold space) = media next/previous

left encoder:
default = mousewheel up/down

symbol layer (hold space) = page up/down

nav layer (hold backspace) = ctrl+tab


Default Layout:

```
Base

 ,-------------------------------------------------------------------.
 |  Q  |  W  |  E  |  R  |  T  |  Del  |  Y  |  U  |  I  |  O  |  P  |
 |-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----|
 |  A  |  S  |  D  |  F  |  G  |  Tab  |  H  |  J  |  K  |  L  |  "  |
 |-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----|
 |  Z  |  X  |  C  |  V  |  B  | Shift |  N  |  M  |  ,  |  .  |  /  |
 `-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----'
          |  GUI | Ctl | Back/Nav | Space/Sym  | Alt |  Play |
           `-------------------------------------------------'
Symbols
 ,-------------------------------------------------------------------.
 |  1  |  2  |  3  |  4  |  5  |  Del  |  6  |  7  |  8  |  9  |  0  |
 |-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----|
 |  !  |  @  |  #  |  $  |  %  |  Tab  |  ^  |  &  |  *  |  =  |  -  |
 |-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----|
 |  |  |  \  |  (  |  [  |  ;  | Shift |  :  |  ]  |  )  |  +  |  _  |
 `-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----'
          |  GUI | Ctl | Back/Nav |     x      | Alt |  Play |
           `-------------------------------------------------'

Nav
 ,-------------------------------------------------------------------.
 |  Q  |  Hm |  Up | End | PgU | RESET |  F1 |  F2 |  F3 |  F4 | Bsp |
 |-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----|
 |  A  | Lft |  Dn | Rgt | PgD |  Tab  |  F5 |  F6 |  F7 |  F8 | Tab |
 |-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----|
 |  Z  | Prv | Pse | Nxt |  V  |  Caps |  F9 | F10 | F11 | F12 | Ent |
 `-----+-----+-----+-----+-----+-------+-----+-----+-----+-----+-----'
          |  GUI | Ctl |    x     | Space/Sym  | Alt |  Play |
           `-------------------------------------------------'
		   

# [dragonchasers](https://github.com/dragonchaser) GH60 layout

Layout derived from the default GH60 keymap.

![Photo of the keyboard](https://pbs.twimg.com/media/DQzlD0yX0AA8spX.jpg)

## Layers

### Base Layer
```
,-----------------------------------------------------------.
|Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
|-----------------------------------------------------------|
|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
|-----------------------------------------------------------|
|FN     |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
|-----------------------------------------------------------|
|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  Up  |FN |
|-----------------------------------------------------------|
|Ctrl|Gui |Alt |      Space           |Alt |Left |Down|Right|
`-----------------------------------------------------------'

Note: right FN triggers function layer,
      left FN(CAPS) is a one-shot button for the macro layer
```

### Function Layer
```
,-----------------------------------------------------------.
|GRV|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|   DEL |
|-----------------------------------------------------------|
|  MB3|MB2|MUP|MB1|MWU|   |   |   |INS|   |RST|   |   |Print|
|-----------------------------------------------------------|
|      | ML|MDN|MR |MWD|   |   |       |   |   |   |        |
|-----------------------------------------------------------|
|CAPS    |   |   |   |   |   |   |   |   |   |   |PGUP|     |
|-----------------------------------------------------------|
|    |    |    |                        |Ctrl|HOME|PGD |END |
`-----------------------------------------------------------'
```

### Macro Layer
```
,-----------------------------------------------------------.
|DEF|   |DUE|   |   |   |   |   |   |   |   |   |GAM|    ARR|
|-----------------------------------------------------------|
|     |MAG|CLO|DUT|RBS|TIG|   |   |   |COU|PSH|   |   |     |
|-----------------------------------------------------------|
|      |ADD|STS|DFF|FTC|PLL|   |       |LOG|   |   |        |
|-----------------------------------------------------------|
|         |   |   |COM|   |BRN|   |   |   |   |MUT|VOL+|PLPA|
|-----------------------------------------------------------|
|    |    |    |                        |APP |PREV|VOL-|NEXT|
`-----------------------------------------------------------'

Abbreviations:
--------------
DEF  - return to default layer
DUE  - enable git duet mode
GAM  - backlight WASD
ARR  - backlight arrows
-
MAG  - git submodule sync --recursive \
       && git submodule update --init --recursive \
       && git submodule foreach --recursive "git co . \
       && git reset --hard && git clean -dffx"
CLO  - git clone
DUT  - git duet (when in duet mode)
RBS  - git rebase
TIG  - tig
COU  - git checkout
PSH  - git push
-
ADD  - git add
STS  - git status
DFF  - git diff
FTC  - git fetch
PLL  - git pull
LOG  - git log
-
COM  - git commit (or git duet commit if in duet mode)
BRN  - git branch
MUT  - audio mute
VOL+ - increase volume
PLPA - play/pause
-
APP  - application (windows menu key)
PREV - previous song
VOL- - decrease volume
NEXT - next song

Note: git commands are SEND_STRING macros sent to the
      currently focused window Make sure it is your terminal :)
 ```

**NOTE:** an outdated version of this keymap is also present for the Satan keyboard, which is no longer maintained since I could not get my hands on a properly working PCB.

# magui's international map

## Abstract

A gergo keymap designed with us-intl layout in mind, with a light focus on sysadmin UX (e.g. the | and - keys are easier to access, and a few terminal keyboard shortcuts are embedded)

I mostly type in french so I use lots of é, è, ç, â... that must be easily accessible too.


## Features

- Tap dance:
  - ' and \` on same key, é and è coming fast!

- shortcuts
  - insert and shift-insert are just right to g and b! Quick insert and linux-paste!
  - key under ',' is ctrl-x which is my tmux command
  - '|' is located on top-rightmost key for faster one-liners
  - replaced useless right shift with '-', use lots of command line options!
  - key under n is r-alt which is my dead key

- Combos:
  - f + j = Enter. In my gergo learning process I pressed Enter instead of space too often, so I just disabled it! Now press both index fingers on resting row to press enter
  - g + <insert> = Enter. Mouse-select some text, swap to term, use shift-insert shortcut (right to b) to paste, then g + insert (right to g) to press enter. Paste commands faster than you can read it!
  - x + c + v = CAPSLOCK BECAUSE CAPSLOCK FEELS LIKE SCREAMING AND YOU SHOULD SMASH YOUR KEYBOARD WHEN YOU SCREAM

## Keymap
Keymap 0: Basic layer

,--------------------------------------------.                         ,-------------------------------------------.
|  ESC    |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |  | \   |
|---------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
|tab/ctrl |   A  |   S  |  D   |   F  |   G  | Ins  |           |  ^   |   H  |   J  |   K  |   L  | ;  : |TD(',`) |
|---------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
| LShift  |   Z  |   X  |   C  |   V  |   B  | s-Ins|           |      |   N  |   M  | ,  < | . >  | /  ? |  - _   |
`---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
                   .----------.   .-------.                                 .------.   .-----.
                   |   ctrl   |   | Super |                                 | ralt |   | c-x |
                   '----------'   '-------'                                 `------.   '-----'
                                       ,-------.                      ,-------.
                                       |FUN/ f1|                      |   f2  |
                                ,------|-------|                      |-------|------.
                                | SYMB |       |                      |       | MOVE |
                                | Space|  Alt  |                      | Del   | bkspc|
                                |      |       |                      |       |      |
                                `--------------'                      `--------------'

Keymap 1: SYMB
,--------------------------------------------.                         ,-------------------------------------------.
|         |   1  |   2  |   3  |   4  |   5  |                         |   6  |   7  |   8  |   9  |   0  |   \    |
|---------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
|         |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   +  |   =  |        |
|---------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
|         |   ~  |   {  |   {  |   [  |   (  |      |           |      |   )  |   ]  |   }  |      |      |        |
`---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
                   .----------.   .-------.                                 .------.   .-----.
                   |          |   |       |                                 |      |   |     |
                   '----------'   '-------'                                 `------.   '-----'
                                       ,-------.                      ,-------.
                                       |       |                      |       |
                                ,------|-------|                      |-------|------.
                                |      |       |                      |       |      |
                                |      |       |                      |       |      |
                                |      |       |                      |       |      |
                                `--------------'                      `--------------'

Keymap 2: MOVE
,--------------------------------------------.                         ,-------------------------------------------.
|         |   1  |   2  |   3  |   4  |   5  |                         | Home | PgDn | PgUp | End  |VolUp |        |
|---------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
|         |  f1  |  f2  |  f3  |  f4  |  f5  |  f6  |           |      | left | down |  up  |right |VolDn |        |
|---------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
|         |  f7  |  f8  |  f9  |  f10 |  f11 | f12  |           |      | Prev | Stop | Play |      |      |        |
`---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
                   .----------.   .-------.                                 .------.   .-----.
                   |          |   |       |                                 |      |   |     |
                   '----------'   '-------'                                 `------.   '-----'
                                       ,-------.                      ,-------.
                                       |       |                      |       |
                                ,------|-------|                      |-------|------.
                                |      |       |                      |       |      |
                                |      |       |                      |       |      |
                                |      |       |                      |       |      |
                                `--------------'                      `--------------'


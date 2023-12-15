# The 35 keymap for bm40hsrgb

This layout is made almost entirely from [miryoku](https://github.com/manna-harbour/miryoku). However, I used fewer layers and reduced 36 keys to 34.

> As little as possible, as simple as possible, as easy as possible to memorize

Replaced the Ctrl, GUI, Alt, and Shift keys with home mod row. A combo function was added by removing some RGB animations of the bm40's keyboard to free up memory. If animation is not removed, it is because there is not enough memory to compile. Added code that uses RGB matrix animation so that you can see at a glance which layer is being used, and you can move faster by increasing the speed of the mouse key. 

And because I'm Korean, a combo for Korean and English keyboard conversion has been added, but if you don't need it, you can delete it.


- Flash:

  `qmk flash -kb kprepublic/bm40hsrgb -km 34keys`

# Layout

Press and hold to activate the keys in parentheses.


https://imgur.com/a/UkKfCYm


## _BASE(QWERTY)

![](https://i.imgur.com/PuHFVXT.png)


| Q | W | E | R | T | | | Y | U | I | O | P | 
|---|---|---|---|---|---|---|---|---|---|---|---|
| A(GUI) | S(Alt) | D(Ctrl) | F(Shift) |  G | |  | H | J(Shift) | K(Ctrl)  | L(Alt) | '(GUI) |
| Z | X| C| V| B| | | N | M | , | . | /|
| | | | NaviLayer| Space(_Func) | | | Backspace | NumberLayer | | | |  

## _Navi

![](https://i.imgur.com/BwDHx64.png)

| Mousewheel left | Mousewheel down | Mousewheel up | Mousewheel right | ESC | | | DEL | HOME | PageDown | PageUP | END | 
|---|---|---|---|---|---|---|---|---|---|---|---|
| A(GUI) | S(Alt) | D(Ctrl) | F(Shift) |  TAB | |  | ENTER | J(Shift) | K(Ctrl)  | L(Alt) | '(GUI) |
| Mouse left | Mouse down | Mouse up| Mouse right | left click | | | left click | Left | Down | Up | Right |
| | | |  | Space | | | Backspace | NumberLayer | | | |  

## _Numb

![](https://i.imgur.com/lPPyUsk.png)

| [ | 7 | 8 | 9 | ] | | | DEL |  |  |  |  | 
|---|---|---|---|---|---|---|---|---|---|---|---|
| ; | 4 | 5 | 6 | = | |  | ENTER | J(Shift) | K(Ctrl)  | L(Alt) | '(GUI) |
| ` |  1 | 2 | 3 | \ | | |  |  |  |  | |
| | | | 0|  - | | | Backspace | | | | |  

## _Func

![](https://i.imgur.com/rz0jaoe.png)

| F12 | F7 | F8 | F9 | PrintScreen | | | RESET |  |  |  |  | 
|---|---|---|---|---|---|---|---|---|---|---|---|
| F11 | F4 | F5 | F6 | ScrollLock | |  | CapsLock | J(Shift) | K(Ctrl)  | L(Alt) | '(GUI) |
| F10 |  F1 | F2 | F3 | PauseBreak | | | Insert |  |  |  | |
| | | | NaviLayer | Space | | | Backspace | NumberLayer | | | |  

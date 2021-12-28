# Chris' DZ60 Layout

This is a custom keymap for the layout of the DZ60.

## Keyboard Picture

![Keyboard](https://i.imgur.com/qyWgShY.png)

## Keyboard Layout

![Chris DZ60](https://i.imgur.com/6mwsEOl.png)

## Setup

[QMK Toolbox Download](https://github.com/qmk/qmk_toolbox/releases/tag/0.0.13)

[MYSYS2 for Windows](http://www.msys2.org/)

``` bash
#After downloading
pacman -Syu
#Close and re-open
pacman -Su
pacman -S git

#Clone this repo and run this command in directory
util/qmk_install.sh
```

``` bash
#From the qmk_firware directory run
make dz60:chrisae9
```

# Ergo-V-1

Fork of [Ergo-S-1](https://github.com/wizarddata/Ergo-S-1) from WizardKeyboards

Ergo-S-1 on its part is heavily inspired from Kinesis Advantage

![Ergo-V-1](https://i.imgur.com/eE1l5IV.jpeg)

This keyboard is practically identical to the orignal one with some differences
* Modified thumb cluster with one extra key
* Improved switch cutouts, compatible with kailh style switches
* unlike Ergo-S-1 this is a wired keyboard based on qmk

### Instructions
QMK firmware for Ergo-V-1 is heavily influenced by dactyl manuform and especially [5x6 variant](https://github.com/qmk/qmk_firmware/tree/master/keyboards/handwired/dactyl_manuform/5x6)
so the flashing process is very similar

run these commands
```
qmk compile -kb handwired/ergo_v_1 -km default
qmk flash -kb handwired/ergo_v_1 -km default
```

> **_NOTE:_** if you get a git related error try updating submodules by running
> <br>```git submodule update --init --recursive```

then double click to reset button located upper part of front side of the keyboard

### Adding new keymaps
To add your own variant go to Ergo-V-1 base directory then keymaps and add sibling folder to `default/`
After that you can put whatever you want in your `keymap.c`

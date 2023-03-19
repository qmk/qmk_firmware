# Rainkeebs/trailmix

Ortho split 40% keyboard by rainkeenbs with encoders.

* Keyboard Maintainer: [ATron789](https://github.com/atron789)

## DISCLAIMER 
This readme is set for a keyboard using `elite c` controllers.
If using different controllers be sure to update the `rules.mk` and `info.json` to your needs.

### Compiling and flashing firmware:

#### Compile firmware via Makefile
Make example for this keyboard (after setting up your build environment):
```
make rainkeebs/trailmix:default
```

#### Compile and flash firmware via Makefile
Before proceeding disconnect the 2 sides from each other. Connect one side to your machine, put the keyboard's in DFU mode via the button next to the encoder, run the following. Once completed do the same for the other side.
```
make rainkeebs/rainkeeb:default:flash
``` 

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# johu's E6-V2 Last Edition (LE) HHKB
Make example for this keyboard (after setting up your build environment):
```bash
$ make e6v2/le:johu
```

Or to make and flash:
```bash
$ make e6v2/le:johu:dfu
```

See the [build environment setup] and the [make instructions] for more
information. Brand new to QMK? Start with our [Complete Newbs Guide].

## Layer 0: Base Layer
* HHKB Qwerty layout plus some specials:
  * The Space key sends `Space` when tapped, toggles to *Space FN Layer* when held
  * [Grave Escape]
  * The Ctrl key sends `Esc` when tapped, `Ctrl` when held
  * The Tab key sends `Tab` when tapped, [Hyper] (`Super+Ctrl+Alt+Shift`) when held
  * The right Shift key sends `Enter` when tapped, `Shift` when held

## Layer 1: Function Layer
* Default HHKB function layer includig the iconic diamond arrow cluster
* Multimedia controls

## Layer 2: Space FN Layer
* VIM style arrow cluster
* Multimedia controls

## Layer 3: Control Layer
* Reset button
* RGB controls
* Caps Lock

[build environment setup]: https://docs.qmk.fm/#/getting_started_build_tools
[make instructions]: https://docs.qmk.fm/#/getting_started_make_guide
[Complete Newbs Guide]: https://docs.qmk.fm/#/newbs
[Grave Escape]: https://beta.docs.qmk.fm/features/feature_grave_esc
[Hyper]: http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key

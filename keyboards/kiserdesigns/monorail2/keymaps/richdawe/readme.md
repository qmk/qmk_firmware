# richdawe keymap for Monorail by Kiser Designs

While the Monorail supports Vial out of the box, using a fork of the Vial repo, I like to use vanilla QMK. So here it is, in my fork of QMK!

https://github.com/KiserDesigns/Monorail
https://kiserdesigns.bigcartel.com/

```
qmk compile -km richdawe -kb kiserdesigns/monorail2
qmk flash -km richdawe -kb kiserdesigns/monorail2
```

TODO:

 * Left bar = space too, don't like accidental backspace there
 * Media keys
 * Fix this warning - probably need to move layout to info.json?

```
kiserdesigns/monorail2: LAYOUT: Layout macro should not be defined within ".h" files.
```
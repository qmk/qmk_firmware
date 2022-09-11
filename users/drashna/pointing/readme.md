# User Pointing Device customization

To disable the customized pointing device code and implement it at the keymap, add `CUSTOM_POINTING_DEVICE = no` to your `rules.mk`.

## Automatic Mouse Layer

Movement on the optical sensor triggers a layer that has all of the mouse keys on that layer.  After a set time, the layer will automatically turn itself off after 650ms.

Also, using mousekeys will extend the amount of time that the layer will stay active. 

Additionally, layer keys for the mouse layer will lock the layer on.

## Gaming

When the gamepad or diablo layers are enabled, the mouse layer is locked on, as well. 

## Keycodes

The only custom keycode for Pointing devices here is `KC_ACCEL`.  This allow the mouse report to have an acceleration curve (exponential).

# 68keys

A 68-key keyboard with per-key RGB, Kailh hotswap sockets, and USB-C. Uses Blue Pill.

## History

This keyboard was inspired by the [68keys.io](https://68keys.io/) keyboard. The
68keys keyboard has a similar layout to the
[MagicForce 68](https://www.amazon.com/Qisan-Mechanical-Keyboard-68-Keys-Magicforce/dp/B01E8KO2B0).
[di0ib](https://github.com/di0ib) did a
[replacement PCB](https://github.com/di0ib/tmk_keyboard/tree/master/keyboard/mf68)
for the Magicforce 68.

I love the Magicforce 68, but wanted a few changes. As a colossally
disproportionate response to this challenge, I created
[a utility](https://github.com/sowbug/keycad/) that generates PCBs from
arbitrary KLE JSON files, and used it to create this keyboard.

## A note about backlighting

I wanted my per-key RGB keyboard to have a dim backlight on all keys, but didn't
want to sacrifice cool RGB matrix effects to have it. So I wrote up
[a QMK patch](https://github.com/sowbug/qmk_firmware/commit/f7f859ceeefde40e639cfc75044af477504d30f8)
that treats RGB(0, 0, 0) as eligible for backlighting. Unfortunately the QMK
maintainers weren't interested (actually, now that I look back, I didn't submit
a pull request, but rather discussed it in a chat room), so it's not upstreamed.
Thus you'll have to add that patch (and
[this](https://github.com/sowbug/qmk_firmware/commit/ff17800ef4a9cba59d754c72720d6877edb8fbb9))
to your copy of QMK and then enable it in config.h and rules.mk.

## Building and flashing

`qmk flash -kb sowbug/68keys -km default`

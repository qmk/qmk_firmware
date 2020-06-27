# ARISU

PCB designed using KiCad. The layout is inspired by Lyn's EM7 and TGR Alice with some modification of my own.

Key differences:

    - I removed the extra [B] key on the right half and shifted the [NM,.?] row to the left by 0.25U.
    - Shifted the 3 keys to the right and added arrow keys.
    - Tweaked the bottom so that the 1.5U keys doesn't protrude out a little.

Shifting the [NM,.?] row to the left by 0.25U required quite some work on the arrangement of keys for the right half. As a result, this does not give the same typing experience as Lyn's EM7 and TGR Alice. Lyn's EM7 and TGR Alice uses the home row as the center point to vertically align both halves while I used the number row instead. Due to the nature of staggered keyboards, aligning using the number row resulted in the home row not being aligned.

Keyboard Maintainer: [Fate Nozomi](https://github.com/FateNozomi/arisu-pcb)  
Hardware Supported: ARISU PCB 
Hardware Availability: [Fate Nozomi](https://github.com/FateNozomi/arisu-pcb)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb arisu -km default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

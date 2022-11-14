# @ohlin's Kyria Keymap
###### _This keymap is a work in progress._ 

I am a Product Manager and QA Lead, not a developer, so I spend a lot of my time doing things that require a mouse, so one handed keyboard shortcuts are very useful to me.

This keymap is used on a Mac in conjunction with a [Ploopy Nano](https://github.com/ploopyco/nano-trackball) trackball.

```
,-----------------------------.                      ,-----------------------------.   .--------------.
|    |    |    |    |    |    |                      |    |    |    |    |    |    |  |      ----      |
|----+----+----+----+----+----|                      |----|----+----+----+----+----|  |   PL°°°°°°PY   |
|    |    |    |    |    |    |                      |    |    |    |    |    |    |  |  PL°°°°°°°°PY  |
|----+----+----+----+----+----+---------.  ,---------+----+----+----+----+----+----|  |  PL°°°°°°°°PY  |
|    |    |    |    |    |    |    |    |  |    |    |    |    |    |    |    |    |  |   PL°°°°°°PY   |
`-------------------+----+----+----+----|  |----+----+----+----+----+----+---------'  |      ----      |
               |    |    |    |    |    |  |    |    |    |    |    |                  '--------------'
               `------------------------'  `------------------------'
```

## Home Row Mods
Home row mods help came from @precondition's in-depth article, [_A guide to home row mods_](https://precondition.github.io/home-row-mods). `CAGS` makes the most sense to me as a Mac user.

## Karabiner Elements
Karabiner Elements has been a part of my Mac workflow for years now, so when I switched from a Planck to this Kyria, it fit neatly around this keymap to make things easier. Karabiner serves two primary functions here:

- Change `Caps Lock` to `Hyper` (`ctrl + opt + cmd + shift`)
- Hold mouse button 5 to enable `mouse_motion_to_scroll`

### Caps Lock to Hyper
Years ago, following Brett Terpstra's article [_A useful Caps Lock key_](https://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/), I swapped caps lock for hyper, then mapped a number of system-wide keyboard shortcuts to `Hyper` + `[key]`, such as launching apps using [Alfred](https://www.alfredapp.com/) workflows, resizing and moving windows using [Rectangle](https://github.com/rxhanson/Rectangle), and changing all of my montiors' brightness levels together using [Display Buddy](https://displaybuddy.app/). 

Remapping the Caps Lock key in Karabiner ensures I can still easily use these shortcuts with the built-in keyboard on my laptop as well as with any QMK keyboard (where I use the `KC_HYPR` key code directly).
### Scrolling with the Ploopy Nano
Initially, I tried using the NumLock scroll developed by [@zealws](https://github.com/zealws/qmk_firmware/commit/293d3c211d9e93c127b628ac9ef9e4cb201a01da) ([Reddit post here](https://old.reddit.com/r/ploopy/comments/nlvgkq/how_to_scroll_with_the_trackball_nano/)), but had some difficulty making it work on Mac. Since I was already using Karabiner for the Caps Lock to Hyper Switch, I decided to just use it for [mouse motion to scroll](https://karabiner-elements.pqrs.org/docs/json/complex-modifications-manipulator-definition/other-types/mouse-motion-to-scroll/) as well by holding Mouse Button 5. Easily done.

Despite not being able to make the NumLock scroll work, I did keep the [Ploopy Acceleration](https://github.com/zealws/qmk_firmware/commit/293d3c211d9e93c127b628ac9ef9e4cb201a01da#diff-d9cdae01e54acdc5c6ec6f6b28f48a676287d2f9cc2c9c3aaf63724fa625f520R90-R96) from @zealws' code, as it made using the Nano much easier when moving across the 3 monitors I typically use for work.
## OLED Logo
I created my own OLED logo in [Figma](https://www.figma.com/), converted it with @javl's [image2cpp](https://javl.github.io/image2cpp), and cleaned up the result with @joric's [QMK Logo Editor](https://joric.github.io/qle/).
```
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡/1‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡! ,‡‡‡‡‡‡‡‡‡z!!!!!!!!!!!!r‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡!       .1‡‡‡‡‡‡‡@!  '&‡‡‡‡‡‡_"                ';1‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡'       `‡‡‡‡‡‡‡BI ` `‡‡‡‡‡‡<                      `‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡?        ;‡‡‡‡‡‡@l.;j'>‡‡‡‡‡&'         .""""`         .j‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡!       `‡‡‡‡‡‡@I ,‡r ,‡‡‡‡‡‡l        `M‡‡‡‡‡‡‡(         M‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡1.       "#‡‡‡‡z>';j‡; '&‡‡‡‡‡‡.       i‡‡‡‡‡‡‡‡‡‡l        .‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡^       ;8‡‡‡‡('.;#‡‡" >‡‡‡‡‡‡‡‡        ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡/        )‡‡‡‡r`.{‡‡‡‡` M‡‡‡‡‡‡‡‡‡        ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ""       "j‡‡‡j".;#‡‡‡c  .""""""""""""""""1/‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡                 ,‡‡‡1' ,‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡<  `!  ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡                 'M‡`.;j‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡1'',;'   ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡                   \<                .‡‡‡‡(  /!      ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡;        >‡‡‡‡‡‡‡‡‡‡‡‡1 '1‡‡j;''1‡'       ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡M        !‡‡‡‡‡‡‡‡‡‡' ^‡‡‡` .<‡‡‡        ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡r        .(‡‡‡‡‡‡‡' ;‡1" ,j‡‡‡‡‡        ‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡l        >‡‡‡‡; `jl."1@‡‡‡‡‡‡‡        >‡‡‡‡‡‡‡‡‡‡-         ‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡B.       I‡z  "^  t‡‡‡‡‡‡‡‡‡‡;        I‡‡‡‡‡‡‡‡t         c‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡x       ./'   ^/‡‡‡‡‡‡‡‡‡‡‡‡z.         `""""".         (‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡`    `<   Ir‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡!                      `‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡         ‡‡‡‡‡‡‡‡‡‡‡,  "^  ""1‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡i`                ."1‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡!!!!!!!!!‡‡‡‡‡‡‡‡‡‡‡‡!{` !‡!!!!‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡x!!!!!!!!!!!!?M‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡>';#‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡u8‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡‡
```

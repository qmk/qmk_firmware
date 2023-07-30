# 3geek14's Planck layout

A QWERTY layout based on my Ergodox/Moonlander layouts. I got a Planck in part
because I broke my left thumb, and I wanted a board where my left thumb wasn't
as necessary (no thumb cluster). My thumb was somewhat better by the time I got
the board, so I was able to use the left layer key from the default layout.

Notable carry-overs from my other layouts:
* tap/hold to use CTRL from the [Z] and [/] keys
* tap/hold to use GUI from the ['] key
* tap dance to type ellipsis from the [.] key
* a layer with various emoji macros and a numpad

By defining strings in a custom user-includes.h file, you can get your own email
and signature to be put into the keyboard's firmware. Doing this as a way to
store a password is a significant security risk, so please don't do that.
Because I wanted to store an email address and signature that include emojis, I
use `send_unicode_string` to print the two. If you don't add your own file, the
kaymap will still compile, and those two keys simply won't do anything.

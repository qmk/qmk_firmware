# Wamsm's TADA68 layout

This layout aims to be more MacOS compatible as well as improving upon the functions in the second layer.

The changes that were applied over default layout:

* Make Win/cmd keys right next to space bar just like Apple keyboards.
* 'Grave-Escape' the escape key. This will allow the Esc key to function like Esc when pressed but act like the Grave key when pressed along with GUI or Shift keys. This allows you to use the Apple hotkey of CMD + ~ to switch between windows of the same app. In my config.h file I implemented the override 'GRAVE_ESC_ALT_OVERRIDE'. This will force ESC to be registered when hitting ALT. This preserves the Apple hotkey Cmd+Opt+Esc.
* Moved CAPSLOCK function layer in the space of right shift. In first layer, CAPS acts as secondary fucntion key.
* Changed LEDDown, LEDUp, LEDPower to Fn+,./ (seems more natural to put them towards the edge of the 1u keys)
* Added arrow cluster as Fn+ijkl
* Changed Home and End to Fn+PgUpPgDn
* Replaced mouse controls with media controls (previous track = left arrow, next track = right arrow, play/pause = down arrow, stop track = up arrow)
* Added an extra play/pause as Fn+f (so I can easily reach pause while fingers are on the home row)
* Changed volume controls to Fn+zxc (this make mute eminently reachable)
* Changed Insert to Fn+Del

Many of the secondary function control ideas came from this blog post: https://chrisabides.wordpress.com/2016/08/31/review-and-programming-tutorial-tada68/
So thank you to chrisabides!

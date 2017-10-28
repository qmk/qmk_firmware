# Can I increase the speed of the mouse keys?

**Q:** The default speed for controlling the mouse with the keyboard is slow. I've tried increasing the mouse's sensitivity at work using xset m and it worked, although sometimes it changes by itself for some reason. At home, on Arch Linux, this does not change ti. I've looked through the forums and resolved to use libinput using xinput but using that I only manage to change the speed of the mouse using the actual mouse. The speed of the mouse using the keyboard controls remained unchanged.
Is there perhaps something I can input in the keymap.c to change the sensitivity? Or some other surefire way of increasing the speed?
Thanks!

**A:**  In your keymap's config.h:

```
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0
```

Tweak away. A lower interval or higher max speed will effectively make the mouse move faster. Time-to-max controls acceleration. (See [this Reddit thread for the original discussion](https://www.reddit.com/r/ErgoDoxEZ/comments/61fwr2/a_reliable_way_to_increase_the_speed_of_the_mouse/)).
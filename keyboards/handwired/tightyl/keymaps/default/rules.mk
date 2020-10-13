MOUSEKEY_ENABLE = yes
BOOTLOADER = caterina

 # help from @eraserhd
# @Okke well, "load" is a ... loaded ... word.  You can find a .c library and and it to SRC in rules.mk.  I've found also that many built-in arduino functions are just there.
#er, copy it into your user/<foo> directory or your keymap directory, and add it in the corresponding rules.mk's SRC +=  definition.
#Also, I got an I2C trackball working in my ErgoDox EZ.  If you have an I2C component, it becomes much easier.

# VIA Configurator Support Layout

This "keymap" provides support for the [VIA
Configurator](http://www.caniusevia.com).  The layout defined by the included
keymap.c is used only as the default to initialize the VIA layout on a
newly-flashed board, and should not contain any custom keycodes, since they
show up as not-very-user-friendly opaque hex codes in VIA.  Since its purpose
is to make the keyboard more or less work until the user can configure it with
VIA, it should also be a fairly "normal" layout, i.e. QWERTY with minimal bells
and whistles.  So, the keymap.c is derived from the default layout, which
provides a QWERTY layout for the main keys and use minimal custom keycodes.
The only modifications are removing the version key and solid-backlight key,
and adding an empty fourth layer, because VIA expects to use four layers, and
will see uninitialized garbage otherwise.

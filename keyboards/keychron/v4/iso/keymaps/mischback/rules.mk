# The Keychron V4 features a DIP switch at the back that let the user switch
# between Mac and Windows layouts. As I run Linux anyways, this switch is not
# in use for me personally.
#
# While this feature is deactivated, the default selection of layers in
# Keychron's default keymap is not working and the first layer will be applied
# as the default to the keyboard.
#
# The DIP switch may be used for a different purpose by implementing
# ``dip_switch_update_user(uint8_t index, bool active)`` in ``keymap.c``.
DIP_SWITCH_ENABLE = no

# The V4's keyboard code enables Mouse Keys but that feature is not used in
# this keymap.
MOUSEKEY_ENABLE = no

# Enable Link Time Optimization (LTO) to reduce build size.
#
# Not strictly necessary, as there are no size issues!
LTO_ENABLE = yes

SRC += muse.c

RUST_CRATE = rust_example
RUST_TARGET = thumbv7em-none-eabi
RUST_TOOLCHAIN = nightly # for alloc crate support
RUST_QMK_FEATURES = malloc
RUST_QMK_HEADERS = # rgb_matrix.h eeprom.h

# required for malloc
EXTRALDFLAGS += -specs=nosys.specs

# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LINK_TIME_OPTIMIZATION_ENABLE = yes
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
UNICODEMAP_ENABLE = yes

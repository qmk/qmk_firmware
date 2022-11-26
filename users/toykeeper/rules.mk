# Compile options for ToyKeeper's keymaps

##### Shared options

SRC += toykeeper.c

# Vim-like macros in any program
DYNAMIC_MACRO_ENABLE = yes

# just in case non-nkro compat is needed
NKRO_ENABLE        = yes

# I use mouse keys a lot
MOUSEKEY_ENABLE    = yes

# tap shift for a paren
SPACE_CADET_ENABLE = yes

# tap both shifts for temporary capslock which lasts only one word
CAPS_WORD_ENABLE   = yes

# this causes a compiler error when enabled
VISUALIZER_ENABLE  = no

# Shouldn't be used with CAPS_WORD_ENABLE
COMMAND_ENABLE     = no

# Allows me do to auto-repeat internally in the keyboard
DEFERRED_EXEC_ENABLE = yes

MOUSEKEY_ENABLE=no     # Mouse keys
RGB_MATRIX_ENABLE=no
LTO_ENABLE=yes
COMBO_ENABLE=yes
COMMAND_ENABLE=no
AUTO_SHIFT_ENABLE=no
CAPS_WORD_ENABLE=yes
CONVERT_TO=promicro_rp2040
SPLIT_KEYBOARD=yes


# Additional settings to help with boot detection
SPLIT_TRANSPORT_SYNC=yes
USB_SUSPEND_WAKEUP_DELAY=0
DEBOUNCE_TYPE=sym_defer_g

# Add these for better USB detection
BOOTLOADER = rp2040
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
DEFERRED_EXEC_ENABLE = yes  # Enable deferred execution for better boot timing

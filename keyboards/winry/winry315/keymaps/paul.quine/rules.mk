# Enable Link-Time Optimization (LTO) to shrink firmware size
LTO_ENABLE = yes

# Features disabled to save flash space
MOUSEKEY_ENABLE = no       # Disables mouse movement keys (you don't use these)
EXTRAKEY_ENABLE = no       # Disables Audio/System keys if not used
CONSOLE_ENABLE = no        # Disables debug console output
COMMAND_ENABLE = no        # Disables interactive command suite
BOOTMAGIC_ENABLE = lite    # Uses lightweight bootmagic implementation

# Keep required features enabled
RGB_MATRIX_ENABLE = yes    # Keep enabled for your RGB indicators
ENCODER_ENABLE = yes       # Keep enabled for your rotary encoders
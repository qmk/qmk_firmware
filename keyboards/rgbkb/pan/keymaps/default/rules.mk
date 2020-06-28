# Example:
#     if you wanted to disable EXTRAKEY_ENABLE, you would copy the line from the pan/rules.mk file
#     and paste it in to this file, changing the yes to no. Like so:
# EXTRAKEY_ENABLE         = no       # Audio control and System control
#
# To keep things clean and tidy, as well as make upgrades easier, only place overrides from the defaults in this file.

# Processor choice= comment out either line 9 or 10.
ATmega32A = yes
# ProtonC = yes

# RGB layout selection
RGB_ENCODERS          = yes    # For RGB encoders, solder on both WS2811 chips
STAGGERED_LAYOUT      = no     # If you soldered R1-A12 and R4-A12, enable this.

# Do not edit past here
include keyboards/$(KEYBOARD)/post_rules.mk

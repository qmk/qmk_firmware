# Steno implies virtual serial.
STENO_ENABLE     = yes
# Not enough interupts, so something has to go. You can't have
# more than one, because virtual serial uses so many things.
# Note, you don't need NKRO for the Gemini-protocol serial steno.
MOUSEKEY_ENABLE  = no
CONSOLE_ENABLE   = no  # this is way too large now :(
NKRO_ENABLE      = no
I2CLCD_AF_ENABLE = no  # Use with Adafruit's MCP23008 backpack for LCD displays
I2CLCD_SB_ENABLE = yes # Use with the weird hacky custom thing seebs built
LCDSTENO_ENABLE  = yes

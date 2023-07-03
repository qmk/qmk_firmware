# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
NO_SUSPEND_POWER_DOWN = yes

# Wear-levering driver
WEAR_LEVELING_DRIVER = rp2040_flash

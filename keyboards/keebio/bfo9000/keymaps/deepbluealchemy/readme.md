# Deep Blue Alchemy BFO-9000 layout

This layout uses an oled on the left side. Only the left side can have the driver, since the I2C bus is shared between controllers, so if both halves have it, the right side crashes.

Make the left side with the option: make keebio/bfo9000:deepbluealchemy:avrdude SPLIT_LEFT=yes

// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#	define RGBLED_NUM 58  
#   define RGB_MATRIX_SPLIT {29, 29}
#	define DRIVER_LED_TOTAL RGBLED_NUM

#	define RGB_MATRIX_MAXIMUM_BRIGHTNESS 175
#	define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended

#	define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#	define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)

#	define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
#	define RGB_MATRIX_KEYPRESSES   // reacts to keypresses
#	define RGB_MATRIX_FRAMEBUFFER_EFFECTS  // reacts to keyreleases (instead of keypresses)

#	ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
#		define  ENABLE_RGB_MATRIX_TYPING_HEATMAP      // How hot is your WPM!
#	endif

#	ifdef RGB_MATRIX_KEYPRESSES
		#define  ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // Pulses keys hit to hue & value then fades value out	
	#endif
	
#	define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#	define ENABLE_RGB_MATRIX_CYCLE_ALL
#	define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Static gradient left to right, speed controls how much gradient changes

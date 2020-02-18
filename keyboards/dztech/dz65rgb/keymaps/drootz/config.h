// Optimization: https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT

// #define DYNAMIC_MACRO_NO_NESTING
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 425

#ifdef RGB_MATRIX_ENABLE

	// "UNDEF" DEFAULT dz65rgb/v2 config.h     
	#undef DISABLE_RGB_MATRIX_SPLASH 
	#undef DISABLE_RGB_MATRIX_SOLID_SPLASH 
	#undef RGB_MATRIX_LED_FLUSH_LIMIT
	#undef RGB_MATRIX_STARTUP_MODE
	#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
	#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255

	// #define DISABLE_RGB_MATRIX_NONE
	// #define DISABLE_RGB_MATRIX_SOLID_COLOR     // Static single hue, no speed support
	#define DISABLE_RGB_MATRIX_ALPHAS_MODS         // Static dual hue, speed is hue for secondary hue 
	#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT    // Static gradient left to right, speed controls how much gradient changes
	#define DISABLE_RGB_MATRIX_BREATHING           	// Single hue brightness cycling animation 
	#define DISABLE_RGB_MATRIX_BAND_VAL        // Single hue band fading brightness scrolling left to right 
	#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL   // Single hue 3 blade spinning pinwheel fades brightness 
	#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness
	#define DISABLE_RGB_MATRIX_CYCLE_ALL           // Full keyboard solid hue cycling through full gradient
	#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Full gradient scrolling left to right
	#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN       // Full gradient scrolling top to bottom
	#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN        // Full gradient scrolling out to in
	#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL   // Full dual gradients scrolling out to in
	#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradent Chevron shapped scrolling left to right
	#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL      // Full gradient spinning pinwheel around center of keyboard
	#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL        // Full gradient spinning spiral around center of keyboard
	#define DISABLE_RGB_MATRIX_DUAL_BEACON         // Full gradient spinning around center of keyboard
	#define DISABLE_RGB_MATRIX_RAINBOW_BEACON      // Full tighter gradient spinning around center of keyboard
	#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS   // Full dual gradients spinning two halfs of keyboard
	#define DISABLE_RGB_MATRIX_RAINDROPS           // Randomly changes a single key's hue
	#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS // Randomly changes a single key's hue and saturation
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE      // Static single hue, pulses keys hit to shifted hue then fades to current hue
	// #define DISABLE_RGB_MATRIX_TYPING_HEATMAP      // How hot is your WPM!  
	// #define DISABLE_RGB_MATRIX_SPLASH              // Full gradient & value pulse away from a single key hit then fades value out 
	// #define DISABLE_RGB_MATRIX_SOLID_SPLASH        // Hue & value pulse away from a single key hit then fades value out 

	#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // default: 26 
	#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP
	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

	#define RGB_MATRIX_STARTUP_HUE 150 // Sets the default hue value, if none has been set
	#define RGB_MATRIX_STARTUP_SAT 255 // Sets the default saturation value, if none has been set
	#define RGB_MATRIX_STARTUP_VAL 200 // Sets the default brightness value, if none has been set
	#define RGB_MATRIX_STARTUP_SPD 75 // Sets the default animation speed, if none has been set

#endif

// while you’re not debugging:
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

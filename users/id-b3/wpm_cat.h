#ifdef WPM_ENABLE

	// WPM-responsive animation stuff here
	#define IDLE_FRAMES 5
	#define IDLE_SPEED 40 // below this wpm value your animation will idle

	// #define PREP_FRAMES 1 // uncomment if >1

	#define TAP_FRAMES 2
	#define TAP_SPEED 60 // above this wpm value typing animation to triggere

	#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
	// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
	#define ANIM_SIZE 636 // number of bytes in array, minimize for adequate firmware size, max is 1024

	uint32_t anim_timer = 0;
	uint32_t anim_sleep = 0;
	uint8_t current_idle_frame = 0;
	// uint8_t current_prep_frame = 0; // uncomment if PREP_FRAMES >1
	uint8_t current_tap_frame = 0;

#endif


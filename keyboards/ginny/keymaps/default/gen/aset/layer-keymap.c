	// Thumb Keys
	P(AL,														SEND(KC_LSFT));
	P(AR,														SEND(KC_SPC));
	
	// Layer Switches 
	// To Number
	P(			AA | AT | AN | AP,																SET_STICKY(NUM));
	P(NUM | AA | AT | AN | AP,																SET_STICKY(0));
	P(CMD | AA | AT | AN | AP,																SET_STICKY(NUM));
	P(USR | AA | AT | AN | AP,																SET_STICKY(NUM));
	
	// To Command
	P(			AS | AE | AI | AO,																SET_STICKY(CMD));
	P(NUM | AS | AE | AI | AO,																SET_STICKY(CMD));
	P(CMD | AS | AE | AI | AO,																SET_STICKY(0));
	P(USR | AS | AE | AI | AO,																SET_STICKY(CMD));

	// To User
	P(			AA | AS | AE | AT | AN | AI | AO | AP | AL | AR,	SET_STICKY(USR));
	P(NUM | AA | AS | AE | AT | AN | AI | AO | AP | AL | AR,	SET_STICKY(USR));
	P(CMD | AA | AS | AE | AT | AN | AI | AO | AP | AL | AR,  SET_STICKY(USR));
	P(USR | AA | AS | AE | AT | AN | AI | AO | AP | AL | AR,  SET_STICKY(0));

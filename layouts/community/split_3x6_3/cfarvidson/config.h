#pragma once

#define MASTER_LEFT

#define LAYOUT_cfarvidson_wrapper(\
	k00, k01, k02, k03, k04, k05,			k40, k41, k42, k43, k44, k45, \
	k10, k11, k12, k13, k14, k15,			k50, k51, k52, k53, k54, k55, \
	k20, k21, k22, k23, k24, k25,			k60, k61, k62, k63, k64, k65, \
		       k31, k32, k33,		        k71, k72, k73  \
)\
LAYOUT_split_3x6_3(\
	k00, k01, k02, k03, k04, k05,			k40, k41, k42, k43, k44, k45, \
	k10, k11, k12, k13, k14, k15,			k50, k51, k52, k53, k54, k55, \
	k20, k21, k22, k23, k24, k25,			k60, k61, k62, k63, k64, k65, \
		       k31, k32, k33,		        k71, k72, k73  \
)


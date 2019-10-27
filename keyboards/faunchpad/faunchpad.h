#pragma once

#include "quantum.h"

#define LAYOUT_faunch( 												\
    k00, k01, k02, k03, k10, k11, k12, k13		\
) { 																					\
	{ k00, k01, k02, k03 },								\
	{ k10, k11, k12, k13 },								\
}

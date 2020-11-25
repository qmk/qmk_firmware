#pragma once
#ifndef KB_H
#define KB_H
#include "quantum.h"

#define LAYOUT( \
	K00, K01,\
	K11, K12 \
) { \
	{K00,   K01},\
		{K11  ,K12}\
}
#endif
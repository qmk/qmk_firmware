#pragma once

// This fixes the diodes mounted reversed (fab fail) on M60-A prototype
#undef DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

#pragma once

// higher value means deeper actuation point, less sensitive
// be careful and only make small adjustments (steps of 1 or 2).
// too high and keys will fail to actuate. too low and keys will actuate spontaneously.
// test all keys before further adjustment.
// this should probably stay in the range +/-5.
#undef ACTUATION_DEPTH_ADJUSTMENT
#define ACTUATION_DEPTH_ADJUSTMENT +2

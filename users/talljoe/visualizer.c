#include "talljoe.h"

static void get_visualizer_layer_and_color(visualizer_state_t* state) {
  state->status_text = layer_names[biton32(state->status.layer)];
}

#include "talljoe.h"

static void get_visualizer_layer_and_color(visualizer_state_t* state) {
  for(int i = 0; i < 16; ++i) {
    if(IS_LAYER_ON(state->status.layer, i)) {
      state->status_text = layer_names[i];
    }
  }
}

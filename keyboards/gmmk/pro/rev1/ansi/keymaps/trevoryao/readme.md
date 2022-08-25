# Minimalist macOS GMMK Pro Layout

Pretty stock, but uses macOS modifiers and also swaps the placement of the `fn` key to the end. Default function row imitates apple keyboard. Only enabled regular and breathing LEDs, and provides custom colour cycling. Function layer has git shortcuts. Encoder + modifiers control lighting. Extra row for line scrolling in vs code, and also power button.

## Adding custom colours
In [`rgb_matrix_map.h`](./rgb_matrix_map.h), add a `RGB` structure with your desired colour codes to the `COLOUR_LAYERS` array. Order is preserved.

Thanks to @gourdo1 for their work on the `rgb_matrix_map`.

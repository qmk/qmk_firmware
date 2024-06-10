
This was the original layout definition showing how the physical key locations map
to the matrix grid.

* A3 and B35 are the trackball keys
* A42, A34, A45 are for the encoder CCW, click and CW bindings

The last three, B42, B34 and B45 don't seem to used.

````
define LAYOUT( \
    A00, A01, A02, A03, A04, A05,                 B05, B04, B03, B02, B01, B00, \
    A10, A11, A12, A13, A14, A15,                 B15, B14, B13, B12, B11, B10, \
    A20, A21, A22, A23, A24, A25,                 B25, B24, B23, B22, B21, B20, \
              A30, A31, A32, A33, A35,      B35,  B33, B32, B31, B30, \
                                  A42, A34, A45,  B42, B34, B45 \
   ) \
  { \
    { A00,   A01,   A02,   A03,   A04,   A05 }, \
    { A10,   A11,   A12,   A13,   A14,   A15 }, \
    { A20,   A21,   A22,   A23,   A24,   A25 }, \
    { A30,   A31,   A32,   A33,   A34,   A35 }, \
    { KC_NO, KC_NO, A42, KC_NO, KC_NO,   A45 }, \
    { B00,   B01,   B02,   B03,   B04,   B05 }, \
    { B10,   B11,   B12,   B13,   B14,   B15 }, \
    { B20,   B21,   B22,   B23,   B24,   B25 }, \
    { B30,   B31,   B32,   B33,   B34,   B35 },  \
    { KC_NO, KC_NO, B42, KC_NO, KC_NO,   B45 }  \
```

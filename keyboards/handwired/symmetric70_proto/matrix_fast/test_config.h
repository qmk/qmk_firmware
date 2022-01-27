// list of OUTPUT(row) ports
#define MATRIX_OUT_PORTS (Port_D, MCU_GPIO, D0), (Port_C, MCU_GPIO, C0), (Port_E, MCU_GPIO, E0), (Port_B, MCU_GPIO, B0)
// list of OUTPUT(row) pins
#define MATRIX_OUT_PINS  \
    (0, Port_D, 4), \
    (1, Port_C, 6), \
    (2, Port_D, 7), \
    (3, Port_E, 6), \
    (4, Port_B, 4), \
    (5, Port_B, 5)

// list of INPUT(col) ports
#define MATRIX_IN_PORTS (Port_F, MCU_GPIO, F0), (Port_B, MCU_GPIO, B0)
// list of INPUT(col) pins
#define MATRIX_IN_PINS \
    (0, Port_F, 4), \
    (1, Port_F, 5), \
    (2, Port_F, 6), \
    (3, Port_F, 7), \
    (4, Port_B, 1), \
    (5, Port_B, 3)

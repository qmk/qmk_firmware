#define MATRIX_EXTENSION_74HC157 B2
// #define MATRIX_EXTENSION_74HC153 B2, B6

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
#define MATRIX_IN_PORTS \
    (Port_Fa, MCU_GPIOa, F0), \
    (Port_Ba, MCU_GPIOa, B0), \
    (Port_Fb, MCU_GPIOb, F0), \
    (Port_Bb, MCU_GPIOb, B0)
// list of INPUT(col) pins
#define MATRIX_IN_PINS \
    (0, Port_Fa, 4), \
    (1, Port_Fb, 5), \
    (2, Port_Fb, 6), \
    (3, Port_Fa, 7), \
    (4, Port_Ba, 1), \
    (5, Port_Bb, 3)

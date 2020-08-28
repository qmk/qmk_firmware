# Demultiplexer

In case you need to use more pins on your microcontroller than it has available, you can use a demultiplexer. Only the 74HC138 and 74HC154 are supported.

You can enable support for a demultiplexer by setting the `MATRIX_DEMUX` flag in your keyboards `rules.mk` to yes. You will also have to set the `CUSTOM_MATRIX` flag to lite.

## Configuration

You will need to configure which type of demultiplexer is used, which pins control its inputs and its enable pin in your keyboard's `config.h`.

````
/*
 * Demultiplexer configuration
 */

#define DEMUX_74HC138 // This can also be DEMUX_74HC154, depending on the demultiplexer used in the keyboard.
#define DEMUX_INPUT_PINS { D2, D1, D0 } // These are A0, A1, A2 (and A3) respectively.
#define DEMUX_ENABLE_PIN D4

/* Uncomment the line below if the enable pin needs to be high instead of low to enable the demultiplexer */
//#define DEMUX_ENABLE_HIGH
````

You can define which column or row pins are used by the demultiplexer by just defining them in the column and row pins. Here's an example of column pins on the microcontroller and the demultiplexer:
````
#define MATRIX_COL_PINS { F7, F5, F6, F1, F4, F0, Y7, D5, D3, Y6, Y5, Y4, Y3, Y2, Y1, Y0 }
````

The demultiplexer pins can be `Y0, Y1, Y2...` up to `Y7` for the 74HC138 and up to `Y15` for the 74HC154.

If none of the enable pins are connected to the microcontroller, it means that there will always an active output. To circumvent that, make sure nothing is connected to its Y0 pin, uncomment the definition of `DEMUX_ENABLE_PIN` and add `#define DEMUX_NO_ENABLE_PIN` to your keyboard's `config.h`.

## Schematic wiring

A demultiplexer has inputs and outputs. Based on which combination of inputs are high and low, one output will be active. There is one very important thing to know about using them in your design, which is that they should be put on the end of the diode direction. This means that, when used on columns, the diode direction should be `ROW2COL`. If the diode direction is `COL2ROW`, the demultiplexer should only be used on rows. Make sure to read the datasheet before using a demultiplexer.

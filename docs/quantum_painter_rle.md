# QMK QGF/QFF RLE data schema {#qmk-qp-rle-schema}

There are two "modes" to the RLE algorithm used in both [QGF](quantum_painter_qgf)/[QFF](quantum_painter_qff):

* Non-repeating sections of octets, with associated length of up to `128` octets
    * `length` = `marker - 128`
    * A corresponding `length` number of octets follow directly after the marker octet
* Repeated octet with associated length, with associated length of up to `128`
    * `length` = `marker`
    * A single octet follows the marker that should be repeated `length` times.

Decoder pseudocode:
```
while !EOF
    marker = READ_OCTET()

    if marker >= 128
        length = marker - 128
        for i = 0 ... length-1
            c = READ_OCTET()
            WRITE_OCTET(c)

    else
        length = marker
        c = READ_OCTET()
        for i = 0 ... length-1
            WRITE_OCTET(c)

```

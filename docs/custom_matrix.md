# Custom Matrix

QMK provides a mechanism to supplement or replace the default matrix scanning routine with your own code.

The reasons to use this feature include:

* Extra hardware between the keyboard's switches and MCU pins
  * I/O multiplexer
  * Line decoder
* Irregular switch matrix
  * Simultaneous use of `COL2ROW` and `ROW2COL`

## Prerequisites

Implementing custom matrix usually involves compilation of an additional source file. It is recommended that for consistency, this file is called `matrix.c`.

Add a new file to your keyboard directory:
```
keyboards/<keyboard>/matrix.c
```

And to configure compilation for the new file, add this to your `rules.mk`:
```make
SRC += matrix.c
```

## 'lite'

Provides a default implementation for various scanning functions, reducing the boilerplate code when implementing custom matrix.
To configure it, add this to your `rules.mk`:

```make
CUSTOM_MATRIX = lite
```

And implement the following functions in a `matrix.c` file in your keyboard folder:

```c
void matrix_init_custom(void) {
    // TODO: initialize hardware here
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here

    return matrix_has_changed;
}
```


## Full Replacement

When more control over the scanning routine is required, you can choose to implement the full scanning routine.
To configure it, add this to your rules.mk:

```make
CUSTOM_MATRIX = yes
```

And implement the following functions in a `matrix.c` file in your keyboard folder:

```c
matrix_row_t matrix_get_row(uint8_t row) {
    // TODO: return the requested row data
}

void matrix_print(void) {
    // TODO: use print() to dump the current matrix state to console
}

void matrix_init(void) {
    // TODO: initialize hardware and global matrix state here

    // Unless hardware debouncing - Init the configured debounce routine
    debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here

    // Unless hardware debouncing - use the configured debounce routine
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    // This *must* be called for correct keyboard behavior
    matrix_scan_quantum();

    return matrix_has_changed;
}
```

And also provide defaults for the following callbacks:

```c
__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}
```

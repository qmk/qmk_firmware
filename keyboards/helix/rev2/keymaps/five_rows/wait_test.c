#include QMK_KEYBOARD_H

#define wait_us_old(us)                             \
    do {                                        \
        if (__builtin_constant_p(us)) {         \
            _delay_us(us);                      \
        } else {                                \
            for (uint16_t i = us; i > 0; i--) { \
                _delay_us(1);                   \
            }                                   \
        }                                       \
    } while (0)


#define gap()  _delay_us(4)

void  housekeeping_task_user(void) {
    static uint16_t w = 1;
    setPinOutput(B5);
    writePinLow(B5);

    switch (w) {
    case 1:
        ATOMIC_BLOCK_FORCEON {
            writePinHigh(B5);
            wait_us(1000);
            writePinLow(B5);
        }
        break;
    case 2:
        ATOMIC_BLOCK_FORCEON {
            writePinHigh(B5);
            wait_us(2000);
            writePinLow(B5);
        }
        break;
    }
    gap();

    uint16_t ws = w*1000;
    ATOMIC_BLOCK_FORCEON {
        writePinHigh(B5);
        wait_us(ws);
        writePinLow(B5);
    }
    gap();

    ATOMIC_BLOCK_FORCEON {
        writePinHigh(B5);
        wait_us_old(ws);
        writePinLow(B5);
    }
    gap();

    w += 1;
    if ( w > 2 )
        w = 1;
}

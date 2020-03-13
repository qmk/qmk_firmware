#ifndef SOFT_SERIAL_CONFIG_H
#define SOFT_SERIAL_CONFIG_H

#ifndef SOFT_SERIAL_PIN
/* Soft Serial defines */
#define SOFT_SERIAL_PIN D2
//  OPTIONAL: #define SELECT_SOFT_SERIAL_SPEED ? // ? = 1,2,3,4,5
//                                               //  1: about 137kbps (default)
//                                               //  2: about 75kbps
//                                               //  3: about 39kbps
//                                               //  4: about 26kbps
//                                               //  5: about 20kbps
#endif

//// USE flexible API (using multi-type transaction function)
#define SERIAL_USE_MULTI_TRANSACTION

#endif /* SOFT_SERIAL_CONFIG_H */

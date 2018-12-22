/* serial.h backward compatibility */

// #ifndef SOFT_SERIAL_PIN
//  #define SOFT_SERIAL_PIN D0
// #endif

#ifndef SERIAL_SLAVE_BUFFER_LENGTH
 #define SERIAL_SLAVE_BUFFER_LENGTH MATRIX_ROWS/2
 #define SERIAL_MASTER_BUFFER_LENGTH 1
#endif


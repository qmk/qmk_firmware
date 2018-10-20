/*
MIT License
Copyright (c) 2018, JacoBurge
Adapted for QMK by Jack Humbert in 2018

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "matrix.h"
#include "i2c_master.h"
#include "quantum.h"

#define VIBRATE_LENGTH 38 //Defines number of interrupts motor will vibrate for, must be bigger than 8 for correct operation
volatile uint8_t vibrate = 0; //Trigger vibration in interrupt

static matrix_row_t matrix[MATRIX_ROWS];

const uint8_t SENr[6] = {1, 2, 3, 5, 6, 7};//Maps capacitive pads to pins
const uint8_t SENc[6] = {0, 4, 8, 9, 10, 11};

volatile uint8_t LEDs[6][6] = {{0}};//Stores current LED values

//Setup interrupt to handle LEDs
void interruptSetup(void) {
//   cli();          // disable global interrupts
//   TCCR1A = 0;     // set entire TCCR1A register to 0
//   TCCR1B = 0;     // same for TCCR1B
//   // set compare match register to desired timer count
//   OCR1A = 10;
//   // turn on CTC mode:
//   TCCR1B |= (1 << WGM12);
//   // Set CS10 and CS12 bits for 1024 prescaler
//   TCCR1B |= (1 << CS10);
//   TCCR1B |= (1 << CS12);
//   // enable timer compare interrupt
//   TIMSK1 |= (1 << OCIE1A);
//   // enable global interrupts
//   TCNT1 = 0;
//   sei();
}

//Read data from the cap touch IC
uint8_t readDataFromTS(uint8_t reg) {
  uint8_t rx[1];
  if (i2c_readReg(0x1C << 1, reg, rx, 1, 100) == 0) {
    return rx[0];
  }
  return 0;
}

//Write data to cap touch IC
uint8_t writeDataToTS(uint8_t reg, uint8_t data) {
  uint8_t tx[2] = { reg, data };
  if (i2c_transmit(0x1C << 1, tx, 2, 100) == 0) {
    return 1;
  } else {
    return 0;
  }
}


uint8_t checkTSPres(void) {
  return (readDataFromTS(0x00) == 0x3E);
}

uint8_t capSetup(void) {

  uint8_t temp_return = checkTSPres();

  if (temp_return == 1) {
    writePinLow(B7);
    // Perform measurements every 16ms
    writeDataToTS(0x08, 1);

    // Increase detection integrator value
    writeDataToTS(0x0B, 1);

    // Oversample to gain two bits for columns
    writeDataToTS(0x28, 0x42);
    writeDataToTS(0x29, 0x00);
    writeDataToTS(0x2A, 0x00);
    writeDataToTS(0x2B, 0x00);
    writeDataToTS(0x2C, 0x42);
    writeDataToTS(0x2D, 0x00);
    writeDataToTS(0x2E, 0x00);
    writeDataToTS(0x2F, 0x00);
    writeDataToTS(0x30, 0x42);
    writeDataToTS(0x31, 0x42);
    writeDataToTS(0x32, 0x42);
    writeDataToTS(0x33, 0x42);

    // Recalibration if touch detected for more than 8 seconds n*0.16s
    writeDataToTS(0x0C, 50);

    // Enable keys and set key groups
    writeDataToTS(0x1C, 0x00 | 0x04);
    writeDataToTS(0x1D, 0x00 | 0x08);
    writeDataToTS(0x1E, 0x00 | 0x08);
    writeDataToTS(0x1F, 0x00 | 0x08);
    writeDataToTS(0x20, 0x00 | 0x04);
    writeDataToTS(0x21, 0x00 | 0x08);
    writeDataToTS(0x22, 0x00 | 0x08);
    writeDataToTS(0x23, 0x00 | 0x08);
    writeDataToTS(0x24, 0x00 | 0x04);
    writeDataToTS(0x25, 0x00 | 0x04);
    writeDataToTS(0x26, 0x00 | 0x04);
    writeDataToTS(0x27, 0x00 | 0x04);

  }
  return temp_return;
}

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

void matrix_init(void) {

  i2c_init();

  //pinMode(7, OUTPUT);//Motor enable     E6
  setPinOutput(E6);
  //pinMode(6, OUTPUT);//Motor PWM        D7
  setPinOutput(D7);

  //pinMode(11, OUTPUT);//Power LED       B7
  setPinOutput(B7);
  writePinHigh(B7);

  //pinMode(A0, OUTPUT);//LEDs Columns    F7
  setPinOutput(F7);
  //pinMode(A1, OUTPUT);               // F6
  setPinOutput(F6);
  //pinMode(A2, OUTPUT);               // F5
  setPinOutput(F5);
  //pinMode(A3, OUTPUT);               // F4
  setPinOutput(F4);
  //pinMode(A4, OUTPUT);               // F1
  setPinOutput(F1);
  //pinMode(A5, OUTPUT);               // F0
  setPinOutput(F0);

  //pinMode(12, OUTPUT);//LEDs Rows       D6
  setPinOutput(D6);
  //pinMode(8, OUTPUT);                // B4
  setPinOutput(B4);
  //pinMode(9, OUTPUT);                // B5
  setPinOutput(B5);
  //pinMode(10, OUTPUT);               // B6
  setPinOutput(B6);
  //pinMode(5, OUTPUT);                // C6
  setPinOutput(C6);
  //pinMode(13, OUTPUT);               // C7
  setPinOutput(C7);

  //pinMode(0, INPUT);//Capacitive Interrupt     D2
  setPinInput(D2);

  interruptSetup();

  capSetup();
  writeDataToTS(0x06, 0x12); //Calibrate capacitive touch IC

  memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));

  matrix_init_quantum();
}


uint16_t touchDetectionRoutine(void) {
  uint16_t data;
  uint8_t temp1, temp2;

  temp1 = readDataFromTS(0x04);
  temp2 = readDataFromTS(0x03);
  data = temp1;
  data = (data << 8) | temp2;
  return data;

}

//Process raw capacitive data, map pins to rows and columns
void decodeArray(uint16_t dataIn, uint8_t *column, uint8_t *row) {
  uint8_t i1 = 20, i2 = 20;
  for (uint8_t i = 0; i < 12; i++) {
    if ((dataIn & 0b1) == 1) {
      if (i1 == 20) {
        i1 = i;
      } else if (i2 == 20) {
        i2 = i;
      }
    }
    dataIn = dataIn >> 1;
  }

  for (uint8_t j = 0; j < 6; j++) {
    if (SENr[j] == i1 || SENr[j] == i2) {
      *row = j;
    }
    if (SENc[j] == i1 || SENc[j] == i2) {
      *column = j;
    }
  }
}

void touchClearCurrentDetections(void) {
  readDataFromTS(0x05);
  readDataFromTS(0x02);
  readDataFromTS(0x03);
  readDataFromTS(0x04);
}

//Check interrupt pin
uint8_t isTouchChangeDetected(void) {
  return !readPin(D2);
}

uint8_t matrix_scan(void) {
  if (isTouchChangeDetected()) {
    uint16_t dataIn = touchDetectionRoutine();
    if ((dataIn & 0b111100010001) > 0 && (dataIn & 0b000011101110) > 0) {
      writePinLow(B7);
      uint8_t column = 10, row = 10;
      decodeArray(dataIn, &column, &row);
      if (column != 10 && row != 10) {
        vibrate = VIBRATE_LENGTH; //Trigger vibration
        LEDs[column][row] = 1;
        matrix[row] = _BV(column);
      } else {
        //memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
      }
    }
    touchClearCurrentDetections();
  }
  LEDs[3][4] = 1;

  for (uint8_t c = 0; c < 6; c++) {
    for (uint8_t r = 0; r < 6; r++) {
      switch (r) {
        case 0: writePin(D6, LEDs[c][r]); break;
        case 1: writePin(B4, LEDs[c][r]); break;
        case 2: writePin(B5, LEDs[c][r]); break;
        case 3: writePin(B6, LEDs[c][r]); break;
        case 4: writePin(C6, LEDs[c][r]); break;
        case 5: writePin(C7, LEDs[c][r]); break;
      }

      switch (c) {
        case 0: writePin(F5, !LEDs[c][r]); break;
        case 1: writePin(F4, !LEDs[c][r]); break;
        case 2: writePin(F1, !LEDs[c][r]); break;
        case 3: writePin(F0, !LEDs[c][r]); break;
        case 4: writePin(F6, !LEDs[c][r]); break;
        case 5: writePin(F7, !LEDs[c][r]); break;
      }
    }
  }

  // if (vibrate == VIBRATE_LENGTH) {
  //   //digitalWrite(7, HIGH);
  //   writePinHigh(E6);
  //   // analogWrite(6, 255);
  //   writePinHigh(D7);
  //   vibrate--;
  // } else if (vibrate == 8) {
  //   // analogWrite(6, 0);
  //   writePinLow(D7);
  //   vibrate--;
  // } else if (vibrate == 1) {
  //   // analogWrite(6, 127);
  //   writePinHigh(D7);
  //   //digitalWrite(7, LOW);
  //   writePinLow(E6);
  //   vibrate--;
  // }
  // else if (vibrate > 0) {
  //   vibrate--;
  // }





  matrix_scan_quantum();

  return 1;

}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}


 //  if (isTouchChangeDetected()) {
 //    uint16_t dataIn, row = 10, column = 10;
 //    dataIn = touchDetectionRoutine();


 //    if ((dataIn & 0b111100010001) > 0 && (dataIn & 0b000011101110) > 0) {
 //      uint8_t column, row;
 //      decodeArray(dataIn, &column, &row);

 //      if (column != 10 && row != 10) {
 //        vibrate = VIBRATE_LENGTH;//Trigger vibration

 //        LEDs[column][row] = 1;
 //        dataIn = touchDetectionRoutine();
 //        // while
 //        while ((dataIn & _BV(SENr[row])) > 0  || (dataIn & _BV(SENc[column])) > 0) {
 //          dataIn = touchDetectionRoutine();
 //          //Horizontal swipe detect
 //          if ((dataIn & _BV(SENr[row])) > 0  && (dataIn & _BV(SENc[column])) == 0 && (dataIn & 0b111100010001) > 0 && state == NORMAL) {
 //            uint8_t columnNew, rowNew;
 //            decodeArray(dataIn, &columnNew, &rowNew);

 //            if (columnNew > column) {
 //              //===============================================================================================Swipe Right...


 //              //===============================================================================================...Swipe Right
 //            } else {
 //              //===============================================================================================Swipe Left...


 //              //===============================================================================================...Swipe Left
 //            }

 //            while ((dataIn & _BV(SENr[row])) > 0  || (dataIn & _BV(SENc[column])) > 0) {
 //              dataIn = touchDetectionRoutine();
 //            }
 //            break;
 //          }
 //          //Vertical swipe detect
 //          if ((dataIn & _BV(SENc[column])) > 0  && (dataIn & _BV(SENr[row])) == 0 && (dataIn & 0b000011101110) > 0) {
 //            uint8_t columnNew, rowNew;
 //            decodeArray(dataIn, &columnNew, &rowNew);
 //            if (rowNew > row) {
 //              //===============================================================================================Swipe Up...

 //              //===============================================================================================...Swipe Up
 //            }
 //            else {
 //              //===============================================================================================Swipe Down...

 //              //===============================================================================================...Swipe Down

 //            }

 //            while ((dataIn & _BV(SENr[row])) > 0  || (dataIn & _BV(SENc[column])) > 0) {
 //              dataIn = touchDetectionRoutine();
 //            }
 //            break;
 //          }
 //          //===============================================================================================While Pressed...


 //          //===============================================================================================...While Pressed
 //        }
 //        touchClearCurrentDetections();

 //        //===============================================================================================When Released...

 //        //===============================================================================================...When Released
 //        return 1;
 //      }
 //    } else {
 //      touchClearCurrentDetections();
 //    }
 //  }

 // analogWrite(11, blinker);//Update LED    B7

//LED driving interrupt
// ISR(TIMER1_COMPA_vect) {

//   for (uint8_t c = 0; c < 6; c ++) {
//     switch (c) {
//       case 0: writePinLow(D6); break;
//       case 1: writePinLow(B4); break;
//       case 2: writePinLow(B5); break;
//       case 3: writePinLow(B6); break;
//       case 4: writePinLow(C6); break;
//       case 5: writePinLow(C7); break;
//     }
//   }

//   switch (col) {
//     case 0: writePinHigh(F7); break;
//     case 1: writePinHigh(F5); break;
//     case 2: writePinHigh(F4); break;
//     case 3: writePinHigh(F1); break;
//     case 4: writePinHigh(F0); break;
//     case 5: writePinHigh(F6); break;
//   }

//   switch (col) {
//     case 0: writePinLow(F7); break;
//     case 1: writePinLow(F5); break;
//     case 2: writePinLow(F4); break;
//     case 3: writePinLow(F1); break;
//     case 4: writePinLow(F0); break;
//     case 5: writePinLow(F6); break;
//   }

//   for (uint8_t c = 0; c < 6; c ++) {
//     switch (c) {
//       case 0: writePin(D6, LEDs[col][c]); break;
//       case 1: writePin(B4, LEDs[col][c]); break;
//       case 2: writePin(B5, LEDs[col][c]); break;
//       case 3: writePin(B6, LEDs[col][c]); break;
//       case 4: writePin(C6, LEDs[col][c]); break;
//       case 5: writePin(C7, LEDs[col][c]); break;
//     }
//   }

//   col++;
//   if (col > 5) {
//     col = 0;
//   }

//   if (vibrate == VIBRATE_LENGTH) {
//     //digitalWrite(7, HIGH);
//     writePinHigh(E6);
//     // analogWrite(6, 255);
//     writePinHigh(D7);
//     vibrate--;
//   } else if (vibrate == 8) {
//     // analogWrite(6, 0);
//     writePinLow(D7);
//     vibrate--;
//   } else if (vibrate == 1) {
//     // analogWrite(6, 127);
//     writePinHigh(D7);
//     //digitalWrite(7, LOW);
//     writePinLow(E6);
//     vibrate--;
//   }
//   else if (vibrate > 0) {
//     vibrate--;
//   }
// }

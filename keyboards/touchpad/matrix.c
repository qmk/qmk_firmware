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

#define VIBRATE_LENGTH 50 //Defines number of interrupts motor will vibrate for, must be bigger than 8 for correct operation
volatile uint8_t vibrate = 0; //Trigger vibration in interrupt

static matrix_row_t matrix[MATRIX_ROWS];

const uint8_t SENr[6] = {1, 2, 3, 5, 6, 7};//Maps capacitive pads to pins
const uint8_t SENc[6] = {0, 4, 8, 9, 10, 11};

volatile uint8_t LEDs[6][6] = {{0}};//Stores current LED values

//Read data from the cap touch IC
uint8_t readDataFromTS(uint8_t reg) {
  uint8_t rx[1] = { 0 };
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

  //Motor enable
  setPinOutput(E6);
  //Motor PWM
  setPinOutput(D7);

  //Power LED
  setPinOutput(B7);
  writePinHigh(B7);

  //LEDs Columns
  setPinOutput(F7);
  setPinOutput(F6);
  setPinOutput(F5);
  setPinOutput(F4);
  setPinOutput(F1);
  setPinOutput(F0);

  //LEDs Rows
  setPinOutput(D6);
  setPinOutput(B4);
  setPinOutput(B5);
  setPinOutput(B6);
  setPinOutput(C6);
  setPinOutput(C7);

  //Capacitive Interrupt
  setPinInput(D2);

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
      uint8_t column = 10, row = 10;
      decodeArray(dataIn, &column, &row);
      if (column != 10 && row != 10) {
        vibrate = VIBRATE_LENGTH; //Trigger vibration
        matrix[row] = _BV(column);
      } else {
        memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
      }
    } else {
      memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    }
    touchClearCurrentDetections();
  }

  for (uint8_t c = 0; c < 6; c++) {
    for (uint8_t r = 0; r < 6; r++) {
      switch (r) {
        case 0: writePin(D6, matrix_is_on(r, c)); break;
        case 1: writePin(B4, matrix_is_on(r, c)); break;
        case 2: writePin(B5, matrix_is_on(r, c)); break;
        case 3: writePin(B6, matrix_is_on(r, c)); break;
        case 4: writePin(C6, matrix_is_on(r, c)); break;
        case 5: writePin(C7, matrix_is_on(r, c)); break;
      }

      switch (c) {
        case 0: writePin(F5, !matrix_is_on(r, c)); break;
        case 1: writePin(F4, !matrix_is_on(r, c)); break;
        case 2: writePin(F1, !matrix_is_on(r, c)); break;
        case 3: writePin(F0, !matrix_is_on(r, c)); break;
        case 4: writePin(F6, !matrix_is_on(r, c)); break;
        case 5: writePin(F7, !matrix_is_on(r, c)); break;
      }
    }
  }

  if (vibrate == VIBRATE_LENGTH) {
    writePinHigh(E6);
    writePinHigh(D7);
    vibrate--;
  }  else if (vibrate > 0) {
    vibrate--;
  } else if (vibrate == 0) {
    writePinLow(D7);
    writePinLow(E6);
  }

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

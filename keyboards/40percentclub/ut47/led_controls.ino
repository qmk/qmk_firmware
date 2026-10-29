#include <FastGPIO.h>
#include <TimerOne.h>

int iByte;
byte col = 0;
byte leds[12][4];
byte pass = 1;
int fadecount = 1;
const int fadelimit = 3000;
const int fadelimitshort = 1000;
byte mode = 4;
byte brightness = 2;
boolean changemode = 0;
int rain = 0;
const int rainlimit = 5000;
const int rainfade = 5000;
byte rx = 0;
byte ry = 0;

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17] = {
  -1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15, 18, 19, 20, 21
};

// col[xx] of leds = pin yy on led matrix
int cols[12] = {
  pins[8], pins[7], pins[6], pins[5], pins[9], pins[10], pins[11], pins[12], pins[13], pins[14], pins[15], pins[16]
};

// row[xx] of leds = pin yy on led matrix
int rows[4] = {
  pins[1], pins[2], pins[3], pins[4]
};


#define DELAY 0
extern byte leds[12][4];

void setup() {
  Serial1.begin(9600);
  setupLeds();
  for (int s = 0; s < 5; s++) {
    for ( int r = 1; r  < 9; r++)  {
      delayMicroseconds(65000);
      delayMicroseconds(65000);
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 12; i++) {
          leds[i][j] = 1;
          for (int p = 0; p < 25; p++) {
          }
          leds[i][j] = r;
        }
      }
    }
    for ( int r = 9; r  > 0; r--)  {
      delayMicroseconds(65000);
      delayMicroseconds(65000);
      delayMicroseconds(65000);
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 12; i++) {
          leds[i][j] = 1;
          for (int p = 0; p < 25; p++) {
          }
          leds[i][j] = r;
        }
      }
    }
  }
}

void loop() {

  switch (mode) {
    case 0:
      //Blacklight
      for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 4; j++) {
          leds[i][j] = brightness;
        }
      }
      checkserial();
      break;
    case 1:
      //Breathing
      for ( int r = 1; r  < 9; r++)  {
        checkserial();
        if (changemode == 0) {
          delayMicroseconds(65000);
          delayMicroseconds(65000);
          delayMicroseconds(65000);
          for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 12; i++) {
              leds[i][j] = 1;
              for (int p = 0; p < 25; p++) {
              }
              leds[i][j] = r;
            }
          }
        }
        else {
          break;
        }
      }
      for ( int r = 9; r  > 0; r--)  {
        checkserial();
        if (changemode == 0) {
          delayMicroseconds(65000);
          delayMicroseconds(65000);
          delayMicroseconds(65000);
          delayMicroseconds(65000);
          for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 12; i++) {
              leds[i][j] = 1;
              for (int p = 0; p < 25; p++) {
              }
              leds[i][j] = r;
            }
          }
        }
        else {
          break;
        }
      }
      for ( int r = 1; r  < 30; r++)  {
        checkserial();
        if (changemode == 0) {
          delayMicroseconds(65000);
          delayMicroseconds(65000);
        }
        else {
          break;
        }
      }
      break;
    case 2:
      //Random
      leds[random(12)][random(4)] = random(8);
      delayMicroseconds(10000);
      checkserial();
      break;
    case 3:
      //Rain
      rain++;
      if (rain > rainlimit) {
        rain = 0;
        rx = random(12);
        ry = random(4);
        if (leds[rx][ry] == 0) {
          leds[rx][ry] = 18;
        }
      }
      fadecount++;
      if (fadecount > rainfade) {
        fadecount = 1;
        for (int i = 0; i < 12; i++) {
          for (int j = 0; j < 4; j++) {
            if (leds[i][j] > 0) {
              leds[i][j] = leds[i][j] - 1;
            }
          }
        }
      }
      checkserial();
      break;
    case 4:
      //Reactive
      fadecount++;
      if (fadecount > fadelimit) {
        fadecount = 1;
        for (int i = 0; i < 12; i++) {
          for (int j = 0; j < 4; j++) {
            if (leds[i][j] > 0) {
              leds[i][j] = leds[i][j] - 1;
            }
          }
        }
      }
      checkserial();
      break;
    case 5:
      //Reactive Target
      fadecount++;
      if (fadecount > fadelimitshort) {
        fadecount = 1;
        for (int i = 0; i < 12; i++) {
          for (int j = 0; j < 4; j++) {
            if (leds[i][j] > 0) {
              leds[i][j] = leds[i][j] - 1;
            }
          }
        }
      }
      checkserial();
      break;
    default:
      mode = 0;
      break;
  }
  changemode = 0;
}

void checkserial() {
  if (Serial1.available() > 0) {
    iByte = Serial1.read();
    if (iByte == 100) {
      brightness++;
      if (brightness > 9) {
        brightness = 1;
      }
    }
    if (iByte == 101) {
      mode++;
    }
    if (iByte < 100) {
      if (mode == 4) {
        byte row = iByte / 16;
        byte col = iByte % 16;
        leds[col][row] = 18;
      }
      if (mode == 5) {
        byte row = iByte / 16;
        byte col = iByte % 16;
        for (byte i = 0; i < 12;  i++) {
          leds[i][row] = 18;
        }
        for (byte p = 0; p < 4;  p++) {
          leds[col][p] = 18;
        }
      }
    }
  }
}

void setupLeds() {
  // sets the pins as output
  FastGPIO::Pin<2>::setOutputLow();
  FastGPIO::Pin<3>::setOutputLow();
  FastGPIO::Pin<4>::setOutputLow();
  FastGPIO::Pin<5>::setOutputLow();
  FastGPIO::Pin<6>::setOutputLow();
  FastGPIO::Pin<7>::setOutputLow();
  FastGPIO::Pin<8>::setOutputLow();
  FastGPIO::Pin<9>::setOutputLow();
  FastGPIO::Pin<10>::setOutputLow();
  FastGPIO::Pin<16>::setOutputLow();
  FastGPIO::Pin<14>::setOutputLow();
  FastGPIO::Pin<15>::setOutputLow();
  FastGPIO::Pin<18>::setOutputLow();
  FastGPIO::Pin<19>::setOutputLow();
  FastGPIO::Pin<20>::setOutputLow();
  FastGPIO::Pin<21>::setOutputLow();

  // set up Cols
  FastGPIO::Pin<6>::setOutputValueLow();
  FastGPIO::Pin<7>::setOutputValueLow();
  FastGPIO::Pin<8>::setOutputValueLow();
  FastGPIO::Pin<9>::setOutputValueLow();
  FastGPIO::Pin<10>::setOutputValueLow();
  FastGPIO::Pin<16>::setOutputValueLow();
  FastGPIO::Pin<14>::setOutputValueLow();
  FastGPIO::Pin<15>::setOutputValueLow();
  FastGPIO::Pin<18>::setOutputValueLow();
  FastGPIO::Pin<19>::setOutputValueLow();
  FastGPIO::Pin<20>::setOutputValueLow();
  FastGPIO::Pin<21>::setOutputValueLow();

  // set up Rows
  FastGPIO::Pin<2>::setOutputValueLow();
  FastGPIO::Pin<3>::setOutputValueLow();
  FastGPIO::Pin<4>::setOutputValueLow();
  FastGPIO::Pin<5>::setOutputValueLow();

  clearLeds();
  Timer1.initialize(25);
  Timer1.attachInterrupt(display);

}

void clearLeds() {
  // Clear display array
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      leds[i][j] = 0;
    }
  }
}

void onLeds() {
  // Clear display array
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      leds[i][j] = 7;
    }
  }
}

// Interrupt routine
void display() {

  switch (col) { // Turn whole previous column off
    case 0:
      FastGPIO::Pin<6>::setOutputValueLow();
      break;
    case 1:
      FastGPIO::Pin<7>::setOutputValueLow();
      break;
    case 2:
      FastGPIO::Pin<8>::setOutputValueLow();
      break;
    case 3:
      FastGPIO::Pin<9>::setOutputValueLow();
      break;
    case 4:
      FastGPIO::Pin<10>::setOutputValueLow();
      break;
    case 5:
      FastGPIO::Pin<16>::setOutputValueLow();
      break;
    case 6:
      FastGPIO::Pin<14>::setOutputValueLow();
      break;
    case 7:
      FastGPIO::Pin<15>::setOutputValueLow();
      break;
    case 8:
      FastGPIO::Pin<18>::setOutputValueLow();
      break;
    case 9:
      FastGPIO::Pin<19>::setOutputValueLow();
      break;
    case 10:
      FastGPIO::Pin<20>::setOutputValueLow();
      break;
    case 11:
      FastGPIO::Pin<21>::setOutputValueLow();
      break;
  }

  col++;
  if (col == 12) {
    col = 0;
    pass++;
    if (pass > 8) {
      pass = 1;
    }
  }
  for (int row = 0; row < 4; row++) {
    if (leds[col][row] > pass) {
      switch (row) { // Turn on this led
        case 0:
          FastGPIO::Pin<2>::setOutputValueLow();
          break;
        case 1:
          FastGPIO::Pin<3>::setOutputValueLow();
          break;
        case 2:
          FastGPIO::Pin<4>::setOutputValueLow();
          break;
        case 3:
          FastGPIO::Pin<5>::setOutputValueLow();
          break;
      }
    }
    else {
      switch (row) { // Turn off this led
        case 0:
          FastGPIO::Pin<2>::setOutputValueHigh();
          break;
        case 1:
          FastGPIO::Pin<3>::setOutputValueHigh();
          break;
        case 2:
          FastGPIO::Pin<4>::setOutputValueHigh();
          break;
        case 3:
          FastGPIO::Pin<5>::setOutputValueHigh();
          break;
      }
    }
  }
  switch (col) { // Turn column on
    case 0:
      FastGPIO::Pin<6>::setOutputValueHigh();
      break;
    case 1:
      FastGPIO::Pin<7>::setOutputValueHigh();
      break;
    case 2:
      FastGPIO::Pin<8>::setOutputValueHigh();
      break;
    case 3:
      FastGPIO::Pin<9>::setOutputValueHigh();
      break;
    case 4:
      FastGPIO::Pin<10>::setOutputValueHigh();
      break;
    case 5:
      FastGPIO::Pin<16>::setOutputValueHigh();
      break;
    case 6:
      FastGPIO::Pin<14>::setOutputValueHigh();
      break;
    case 7:
      FastGPIO::Pin<15>::setOutputValueHigh();
      break;
    case 8:
      FastGPIO::Pin<18>::setOutputValueHigh();
      break;
    case 9:
      FastGPIO::Pin<19>::setOutputValueHigh();
      break;
    case 10:
      FastGPIO::Pin<20>::setOutputValueHigh();
      break;
    case 11:
      FastGPIO::Pin<21>::setOutputValueHigh();
      break;
  }

}

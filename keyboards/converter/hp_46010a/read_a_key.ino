
/*
this isketch requires the use of the teensyduino environment if running on a teensy 2.0. i have not tried to run it on other boards.
it should ask for you to press a series of button on the board and it will record the corresponding key pattern out as it reads the entire matrix of the board.
the pins used on the teensy, are SS, SCLK, MISO, aka PB0, PB1, and PB3.
<insert something about wireing here>
in order to use this program, you have to have an acutual terminal, the one that comes with the arduino environment is subpar.
for windows i suggest putty, there are tutorials on how to us it with a serial port on the internet.
for linux there isnt really any special program needed, as linux is mostly terminal programs anyway, so simply telneting into the corresponding serial port will work just fine.
when the program starts up it will ask for the user to press the key, but will not continue until prompted further. just hit enter/return on the computer (not the 46010a under test)
make sure that you are pressing and holding the key under test and not tapping it, the matrix is read out really fast so any switch bounce will be easily caught.
when the program has finished scanning the board, it will emit all of the codes with their corresponding clock.
*/

#include <SPI.h>
#include <stdio.h>
#include <string.h>

// BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY are from:
// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"

#define BYTE_TO_BINARY(byte)  \
   (byte & 0x80 ? '1' : '0'), \
   (byte & 0x40 ? '1' : '0'), \
   (byte & 0x20 ? '1' : '0'), \
   (byte & 0x10 ? '1' : '0'), \
   (byte & 0x08 ? '1' : '0'), \
   (byte & 0x04 ? '1' : '0'), \
   (byte & 0x02 ? '1' : '0'), \
   (byte & 0x01 ? '1' : '0') 

const int resetPin = 0
        , ledPin   = 11
        ;

const char keyNames [ 107 ] [ 5 ] =
  { "res ", "stop", "f1  ", "f2  ", "f3  ", "f4  ", "menu", "user", "f5  ", "f6  ", "f7  ", "f8  ", "clrl", "clrd", "b1  ", "b2  ", "b3  ", "b4  "
  , "`~  ", "1   ", "2   ", "3   ", "4   ", "5   ", "6   ", "7   ", "8   ", "9   ", "0   ", "-   ", "=   ", "back", "insl", "dell", "pad*", "pad/", "pad+", "pad-"
  , "tab ", "q   ", "w   ", "e   ", "r   ", "t   ", "y   ", "u   ", "i   ", "o   ", "p   ", "[   ", "]   ", "\\  ", "insc", "delc", "pad7", "pad8", "pad9", "pade"
  , "caps", "ctrl", "a   ", "s   ", "d   ", "f   ", "g   ", "h   ", "j   ", "k   ", "l   ", ";   ", "'   ", "ret ", "cur ", "prev", "pad4", "pad5", "pad6", "pad,"
  , "del ", "lshf", "z   ", "x   ", "c   ", "v   ", "b   ", "n   ", "m   ", ",   ", ".   ", "/   ", "rshf", "sel ", "up  ", "next", "pad1", "pad2", "pad3", "padt"
  , "prnt", "lalt", "spce", "ralt", "left", "down", "rght", "pad0", "pad."
  } ;
  
struct code {
           char keycodeMask ; // the bit mask of this key
  unsigned char clockStart  ; // the starting clock number of the byte this key is found in
} ;
  

         char serialOutBuffer [ 29  ] ;
unsigned char matrixOld       [ 16  ] ; 
unsigned char matrixNew       [ 16  ] ;
         code matrixCodes     [ 107 ] ;
unsigned char currentKey              ;

void setup() {
  currentKey = 0 ;
  
  Serial.begin( 115200 ) ;
  while ( !Serial ) ;
  
  pinMode( resetPin, OUTPUT ) ;
  pinMode( ledPin,   OUTPUT ) ;

  digitalWrite( ledPin,   LOW ) ;
  digitalWrite( resetPin, LOW ) ;
  
  SPI.begin() ;

  // grab the initial matrix of the keyboard
  digitalWrite( resetPin, HIGH ) ;
  digitalWrite( resetPin, LOW  ) ;
  SPI.beginTransaction( SPISettings( 200, LSBFIRST, SPI_MODE1 ) ) ;
  SPI.transfer( matrixOld, 16 ) ;
  SPI.endTransaction();

  memcpy( matrixNew, matrixOld, 16 ) ;
}

void loop() {
  if ( currentKey < 108 ) {
    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
    
    // find and manually map each key
    Serial.print( "\npress " ) ;
    Serial.print( keyNames[currentKey] );

    while ( Serial.read() == -1 ) {}

    // read 16 bytes from the keyboard
    digitalWrite( resetPin, HIGH ) ;
    digitalWrite( resetPin, LOW  ) ;
    SPI.beginTransaction( SPISettings( 3200, LSBFIRST, SPI_MODE1 ) ) ;
    SPI.transfer( matrixNew, 16 ) ;
    SPI.endTransaction();

/* if you need debuggin uncommenting the following might help. it displays the entire matrix as set of 16 bytes */
//    Serial.write(27);       // ESC command
//    Serial.print("[2J");    // clear screen command
//    Serial.write(27);
//    Serial.print("[H");     // cursor to home command
//    Serial.println( "keyboard bitmap" ) ;
//    // display fetched bytes as binary
//    for ( unsigned int i = 0; i < 16 ; ++i ) {
//      sprintf( serialOutBuffer, "clocks: %3i to %3i : " BYTE_TO_BINARY_PATTERN, i*8, i*8 + 7, BYTE_TO_BINARY( matrixNew[i] ) ) ;
//      Serial.println( serialOutBuffer ) ;
//      memset( serialOutBuffer, '\0', 29 ) ;
//    }

    // this little burb simply finds the first bit that differs from the previous mask (wich would be the empty no keys pressed state)
    for ( unsigned int i = 0; i < 16; ++i ) {
      if ( matrixOld[i] != matrixNew[i] ) {
        matrixCodes[currentKey].keycodeMask = matrixNew[i] ;
        matrixCodes[currentKey].clockStart  = i*8 ;
        break ;
      }
    }

    ++currentKey ;
    memcpy( matrixNew, matrixOld, 16 ) ;
  } else {

    Serial.write(27);       // ESC command
    Serial.print("[2J");    // clear screen command
    Serial.write(27);
    Serial.print("[H");     // cursor to home command
    Serial.println( "code bitmask  clock" ) ;
    
    // print out byte code for each key
    
    for ( unsigned int i = 0 ; i < 107; ++i ) {
      sprintf( serialOutBuffer, "%4s " BYTE_TO_BINARY_PATTERN " %3i "
             , keyNames[i]
             , BYTE_TO_BINARY( matrixCodes[i].keycodeMask )
             , matrixCodes[i].clockStart
             ) ;

      Serial.println( serialOutBuffer ) ;

      memset( serialOutBuffer, '\0', 29 ) ;
    }

    while ( 1 ) {}
  }
}


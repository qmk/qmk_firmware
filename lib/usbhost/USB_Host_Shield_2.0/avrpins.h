/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */

/* derived from Konstantin Chizhov's AVR port templates */

#if !defined(_usb_h_) || defined(_avrpins_h_)
#error "Never include avrpins.h directly; include Usb.h instead"
#else
#define _avrpins_h_

#if defined(__AVR__)

// pointers are 16 bits on AVR
#define pgm_read_pointer(p) pgm_read_word(p)

// Support for these boards needs to be manually activated in settings.h or in a makefile
#if !defined(BOARD_MEGA_ADK) && defined(__AVR_ATmega2560__) && (USE_UHS_MEGA_ADK || defined(ARDUINO_AVR_ADK))
#define BOARD_MEGA_ADK
#elif !defined(BOARD_BLACK_WIDDOW) && USE_UHS_BLACK_WIDDOW
#define BOARD_BLACK_WIDDOW
#endif

#ifdef PORTA
#define USE_PORTA
#endif
#ifdef PORTB
#define USE_PORTB
#endif
#ifdef PORTC
#define USE_PORTC
#endif
#ifdef PORTD
#define USE_PORTD
#endif
#ifdef PORTE
#define USE_PORTE
#endif
#ifdef PORTF
#define USE_PORTF
#endif
#ifdef PORTG
#define USE_PORTG
#endif
#ifdef PORTH
#define USE_PORTH
#endif
#ifdef PORTJ
#define USE_PORTJ
#endif
#ifdef PORTK
#define USE_PORTK
#endif
#ifdef PORTL
#define USE_PORTL
#endif
#ifdef PORTQ
#define USE_PORTQ
#endif
#ifdef PORTR
#define USE_PORTR
#endif

#ifdef TCCR0A
#define USE_TCCR0A
#endif
#ifdef TCCR1A
#define USE_TCCR1A
#endif
#ifdef TCCR2A
#define USE_TCCR2A
#endif

//Port definitions for AtTiny, AtMega families.

#define MAKE_PORT(portName, ddrName, pinName, className, ID) \
    class className{\
    public:\
      typedef uint8_t DataT;\
    public:\
      static void Write(DataT value){portName = value;}\
      static void ClearAndSet(DataT clearMask, DataT value){portName = (portName & ~clearMask) | value;}\
      static DataT Read(){return portName;}\
      static void DirWrite(DataT value){ddrName = value;}\
      static DataT DirRead(){return ddrName;}\
      static void Set(DataT value){portName |= value;}\
      static void Clear(DataT value){portName &= ~value;}\
      static void Toggle(DataT value){portName ^= value;}\
      static void DirSet(DataT value){ddrName |= value;}\
      static void DirClear(DataT value){ddrName &= ~value;}\
      static void DirToggle(DataT value){ddrName ^= value;}\
      static DataT PinRead(){return pinName;}\
      enum{Id = ID};\
      enum{Width=sizeof(DataT)*8};\
    };

// TCCR registers to set/clear Arduino PWM
#define MAKE_TCCR(TccrName, className) \
    class className{\
    public:\
      typedef uint8_t DataT;\
    public:\
      static void Write(DataT value){TccrName = value;}\
      static void ClearAndSet(DataT clearMask, DataT value){TccrName = (TccrName & ~clearMask) | value;}\
      static DataT Read(){return TccrName;}\
      static void Set(DataT value){TccrName |= value;}\
      static void Clear(DataT value){TccrName &= ~value;}\
      static void Toggle(DataT value){TccrName ^= value;}\
      enum{Width=sizeof(DataT)*8};\
    };

#ifdef USE_PORTA

MAKE_PORT(PORTA, DDRA, PINA, Porta, 'A')
#endif
#ifdef USE_PORTB
MAKE_PORT(PORTB, DDRB, PINB, Portb, 'B')
#endif
#ifdef USE_PORTC
MAKE_PORT(PORTC, DDRC, PINC, Portc, 'C')
#endif
#ifdef USE_PORTD
MAKE_PORT(PORTD, DDRD, PIND, Portd, 'D')
#endif
#ifdef USE_PORTE
MAKE_PORT(PORTE, DDRE, PINE, Porte, 'E')
#endif
#ifdef USE_PORTF
MAKE_PORT(PORTF, DDRF, PINF, Portf, 'F')
#endif
#ifdef USE_PORTG
MAKE_PORT(PORTG, DDRG, PING, Portg, 'G')
#endif
#ifdef USE_PORTH
MAKE_PORT(PORTH, DDRH, PINH, Porth, 'H')
#endif
#ifdef USE_PORTJ
MAKE_PORT(PORTJ, DDRJ, PINJ, Portj, 'J')
#endif
#ifdef USE_PORTK
MAKE_PORT(PORTK, DDRK, PINK, Portk, 'K')
#endif
#ifdef USE_PORTL
MAKE_PORT(PORTL, DDRL, PINL, Portl, 'L')
#endif
#ifdef USE_PORTQ
MAKE_PORT(PORTQ, DDRQ, PINQ, Portq, 'Q')
#endif
#ifdef USE_PORTR
MAKE_PORT(PORTR, DDRR, PINR, Portr, 'R')
#endif

#ifdef USE_TCCR0A
MAKE_TCCR(TCCR0A, Tccr0a)
#endif
#ifdef USE_TCCR1A
MAKE_TCCR(TCCR1A, Tccr1a)
#endif
#ifdef USE_TCCR2A
MAKE_TCCR(TCCR2A, Tccr2a)
#endif

// this class represents one pin in a IO port.
// It is fully static.
template<typename PORT, uint8_t PIN>
class TPin {
        //    BOOST_STATIC_ASSERT(PIN < PORT::Width);
public:
        typedef PORT Port;

        enum {
                Number = PIN
        };

        static void Set() {
                PORT::Set(1 << PIN);
        }

        static void Set(uint8_t val) {
                if(val)
                        Set();
                else Clear();
        }

        static void SetDir(uint8_t val) {
                if(val)
                        SetDirWrite();
                else SetDirRead();
        }

        static void Clear() {
                PORT::Clear(1 << PIN);
        }

        static void Toggle() {
                PORT::Toggle(1 << PIN);
        }

        static void SetDirRead() {
                PORT::DirClear(1 << PIN);
        }

        static void SetDirWrite() {
                PORT::DirSet(1 << PIN);
        }

        static uint8_t IsSet() {
                return PORT::PinRead() & (uint8_t)(1 << PIN);
        }

        static void WaiteForSet() {
                while(IsSet() == 0) {
                }
        }

        static void WaiteForClear() {
                while(IsSet()) {
                }
        }
}; //class TPin...

// this class represents one bit in TCCR port.
// used to set/clear TCCRx bits
// It is fully static.

template<typename TCCR, uint8_t COM>
class TCom {
        //    BOOST_STATIC_ASSERT(PIN < PORT::Width);
public:
        typedef TCCR Tccr;

        enum {
                Com = COM
        };

        static void Set() {
                TCCR::Set(1 << COM);
        }

        static void Clear() {
                TCCR::Clear(1 << COM);
        }

        static void Toggle() {
                TCCR::Toggle(1 << COM);
        }
}; //class TCom...

//Short pin definitions
#ifdef USE_PORTA
typedef TPin<Porta, 0 > Pa0;
typedef TPin<Porta, 1 > Pa1;
typedef TPin<Porta, 2 > Pa2;
typedef TPin<Porta, 3 > Pa3;
typedef TPin<Porta, 4 > Pa4;
typedef TPin<Porta, 5 > Pa5;
typedef TPin<Porta, 6 > Pa6;
typedef TPin<Porta, 7 > Pa7;
#endif

#ifdef USE_PORTB
typedef TPin<Portb, 0 > Pb0;
typedef TPin<Portb, 1 > Pb1;
typedef TPin<Portb, 2 > Pb2;
typedef TPin<Portb, 3 > Pb3;
typedef TPin<Portb, 4 > Pb4;
typedef TPin<Portb, 5 > Pb5;
typedef TPin<Portb, 6 > Pb6;
typedef TPin<Portb, 7 > Pb7;
#endif

#ifdef USE_PORTC
typedef TPin<Portc, 0 > Pc0;
typedef TPin<Portc, 1 > Pc1;
typedef TPin<Portc, 2 > Pc2;
typedef TPin<Portc, 3 > Pc3;
typedef TPin<Portc, 4 > Pc4;
typedef TPin<Portc, 5 > Pc5;
typedef TPin<Portc, 6 > Pc6;
typedef TPin<Portc, 7 > Pc7;
#endif

#ifdef USE_PORTD
typedef TPin<Portd, 0 > Pd0;
typedef TPin<Portd, 1 > Pd1;
typedef TPin<Portd, 2 > Pd2;
typedef TPin<Portd, 3 > Pd3;
typedef TPin<Portd, 4 > Pd4;
typedef TPin<Portd, 5 > Pd5;
typedef TPin<Portd, 6 > Pd6;
typedef TPin<Portd, 7 > Pd7;
#endif

#ifdef USE_PORTE
typedef TPin<Porte, 0 > Pe0;
typedef TPin<Porte, 1 > Pe1;
typedef TPin<Porte, 2 > Pe2;
typedef TPin<Porte, 3 > Pe3;
typedef TPin<Porte, 4 > Pe4;
typedef TPin<Porte, 5 > Pe5;
typedef TPin<Porte, 6 > Pe6;
typedef TPin<Porte, 7 > Pe7;
#endif

#ifdef USE_PORTF
typedef TPin<Portf, 0 > Pf0;
typedef TPin<Portf, 1 > Pf1;
typedef TPin<Portf, 2 > Pf2;
typedef TPin<Portf, 3 > Pf3;
typedef TPin<Portf, 4 > Pf4;
typedef TPin<Portf, 5 > Pf5;
typedef TPin<Portf, 6 > Pf6;
typedef TPin<Portf, 7 > Pf7;
#endif

#ifdef USE_PORTG
typedef TPin<Portg, 0 > Pg0;
typedef TPin<Portg, 1 > Pg1;
typedef TPin<Portg, 2 > Pg2;
typedef TPin<Portg, 3 > Pg3;
typedef TPin<Portg, 4 > Pg4;
typedef TPin<Portg, 5 > Pg5;
typedef TPin<Portg, 6 > Pg6;
typedef TPin<Portg, 7 > Pg7;
#endif

#ifdef USE_PORTH
typedef TPin<Porth, 0 > Ph0;
typedef TPin<Porth, 1 > Ph1;
typedef TPin<Porth, 2 > Ph2;
typedef TPin<Porth, 3 > Ph3;
typedef TPin<Porth, 4 > Ph4;
typedef TPin<Porth, 5 > Ph5;
typedef TPin<Porth, 6 > Ph6;
typedef TPin<Porth, 7 > Ph7;
#endif

#ifdef USE_PORTJ
typedef TPin<Portj, 0 > Pj0;
typedef TPin<Portj, 1 > Pj1;
typedef TPin<Portj, 2 > Pj2;
typedef TPin<Portj, 3 > Pj3;
typedef TPin<Portj, 4 > Pj4;
typedef TPin<Portj, 5 > Pj5;
typedef TPin<Portj, 6 > Pj6;
typedef TPin<Portj, 7 > Pj7;
#endif

#ifdef USE_PORTK
typedef TPin<Portk, 0 > Pk0;
typedef TPin<Portk, 1 > Pk1;
typedef TPin<Portk, 2 > Pk2;
typedef TPin<Portk, 3 > Pk3;
typedef TPin<Portk, 4 > Pk4;
typedef TPin<Portk, 5 > Pk5;
typedef TPin<Portk, 6 > Pk6;
typedef TPin<Portk, 7 > Pk7;
#endif

#ifdef USE_PORTL
typedef TPin<Portl, 0 > Pl0;
typedef TPin<Portl, 1 > Pl1;
typedef TPin<Portl, 2 > Pl2;
typedef TPin<Portl, 3 > Pl3;
typedef TPin<Portl, 4 > Pl4;
typedef TPin<Portl, 5 > Pl5;
typedef TPin<Portl, 6 > Pl6;
typedef TPin<Portl, 7 > Pl7;
#endif

#ifdef USE_PORTQ
typedef TPin<Portq, 0 > Pq0;
typedef TPin<Portq, 1 > Pq1;
typedef TPin<Portq, 2 > Pq2;
typedef TPin<Portq, 3 > Pq3;
typedef TPin<Portq, 4 > Pq4;
typedef TPin<Portq, 5 > Pq5;
typedef TPin<Portq, 6 > Pq6;
typedef TPin<Portq, 7 > Pq7;
#endif

#ifdef USE_PORTR
typedef TPin<Portr, 0 > Pr0;
typedef TPin<Portr, 1 > Pr1;
typedef TPin<Portr, 2 > Pr2;
typedef TPin<Portr, 3 > Pr3;
typedef TPin<Portr, 4 > Pr4;
typedef TPin<Portr, 5 > Pr5;
typedef TPin<Portr, 6 > Pr6;
typedef TPin<Portr, 7 > Pr7;
#endif

#ifdef USE_TCCR0A
typedef TCom<Tccr0a, COM0A1> Tc0a; //P6
typedef TCom<Tccr0a, COM0B1> Tc0b; //P5
#endif

#ifdef USE_TCCR1A
typedef TCom<Tccr1a, COM1A1> Tc1a; //P9
typedef TCom<Tccr1a, COM1B1> Tc1b; //P10
#endif

#ifdef USE_TCCR2A
typedef TCom<Tccr2a, COM2A1> Tc2a; //P11
typedef TCom<Tccr2a, COM2B1> Tc2b; //P3
#endif

template<typename Tp_pin, typename Tc_bit>
class Tp_Tc {
public:

        static void SetDir(uint8_t val) {
                if(val)
                        SetDirWrite();
                else SetDirRead();
        }

        static void SetDirRead() {
                Tp_pin::SetDirRead(); //set pin direction
                Tc_bit::Clear(); //disconnect pin from PWM
        }

        static void SetDirWrite() {
                Tp_pin::SetDirWrite();
                Tc_bit::Clear();
        }
};

/* pin definitions for cases where it's necessary to clear compare output mode bits */

//typedef Tp_Tc<Pd3, Tc2b> P3;  //Arduino pin 3
//typedef Tp_Tc<Pd5, Tc0b> P5;  //Arduino pin 5
//typedef Tp_Tc<Pd6, Tc0a> P6;  //Arduino pin 6
//typedef Tp_Tc<Pb1, Tc1a> P9;  //Arduino pin 9
//typedef Tp_Tc<Pb2, Tc1b> P10;  //Arduino pin 10
//typedef Tp_Tc<Pb3, Tc2a> P11;  //Arduino pin 11

/* Arduino pin definitions  */
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// "Mega" Arduino pin numbers

#define P0  Pe0
#define P1  Pe1
#define P2  Pe4
#define P3  Pe5
#define P4  Pg5
#define P5  Pe3
#define P6  Ph3
#define P7  Ph4

#define P8  Ph5
#define P9  Ph6
#define P10  Pb4
#define P11  Pb5
#define P12  Pb6
#define P13  Pb7

#define P14  Pj1
#define P15  Pj0
#define P16  Ph1
#define P17  Ph0
#define P18  Pd3
#define P19  Pd2
#define P20  Pd1
#define P21  Pd0

#define P22 Pa0
#define P23 Pa1
#define P24 Pa2
#define P25 Pa3
#define P26 Pa4
#define P27 Pa5
#define P28 Pa6
#define P29 Pa7
#define P30 Pc7
#define P31 Pc6
#define P32 Pc5
#define P33 Pc4
#define P34 Pc3
#define P35 Pc2
#define P36 Pc1
#define P37 Pc0

#define P38 Pd7
#define P39 Pg2
#define P40 Pg1
#define P41 Pg0
#define P42 Pl7
#define P43 Pl6
#define P44 Pl5
#define P45 Pl4
#define P46 Pl3
#define P47 Pl2
#define P48 Pl1
#define P49 Pl0
#define P50 Pb3
#define P51 Pb2
#define P52 Pb1
#define P53 Pb0

#ifdef BOARD_MEGA_ADK // These pins are not broken out on the Arduino ADK
#define P54 Pe6 // INT on Arduino ADK
#define P55 Pj2 // MAX_RESET on Arduino ADK
#endif

// "Mega" pin numbers

#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
// "Classic" Arduino pin numbers

#define P0  Pd0
#define P1  Pd1
#define P2  Pd2
#define P3  Pd3
#define P4  Pd4
#define P5  Pd5
#define P6  Pd6
#define P7  Pd7

#define P8  Pb0
#define P9  Pb1
#define P10  Pb2
#define P11  Pb3
#define P12  Pb4
#define P13  Pb5

#define P14  Pc0
#define P15  Pc1
#define P16  Pc2
#define P17  Pc3
#define P18  Pc4
#define P19  Pc5

// "Classic" Arduino pin numbers

#elif defined(CORE_TEENSY) && defined(__AVR_ATmega32U4__)
// Teensy 2.0 pin numbers
// http://www.pjrc.com/teensy/pinout.html
#define P0  Pb0
#define P1  Pb1
#define P2  Pb2
#define P3  Pb3
#define P4  Pb7
#define P5  Pd0
#define P6  Pd1
#define P7  Pd2
#define P8  Pd3
#define P9  Pc6
#define P10 Pc7
#define P11 Pd6
#define P12 Pd7
#define P13 Pb4
#define P14 Pb5
#define P15 Pb6
#define P16 Pf7
#define P17 Pf6
#define P18 Pf5
#define P19 Pf4
#define P20 Pf1
#define P21 Pf0
#define P22 Pd4
#define P23 Pd5
#define P24 Pe6
// Teensy 2.0

#elif defined(__AVR_ATmega32U4__)
// Arduino Leonardo pin numbers

#define P0  Pd2 // D0 - PD2
#define P1  Pd3 // D1 - PD3
#define P2  Pd1 // D2 - PD1
#define P3  Pd0 // D3 - PD0
#define P4  Pd4 // D4 - PD4
#define P5  Pc6 // D5 - PC6
#define P6  Pd7 // D6 - PD7
#define P7  Pe6 // D7 - PE6

#define P8  Pb4 // D8 - PB4
#define P9  Pb5 // D9 - PB5
#define P10 Pb6 // D10 - PB6
#define P11 Pb7 // D11 - PB7
#define P12 Pd6 // D12 - PD6
#define P13 Pc7 // D13 - PC7

#define P14 Pb3 // D14 - MISO - PB3
#define P15 Pb1 // D15 - SCK - PB1
#define P16 Pb2 // D16 - MOSI - PB2
#define P17 Pb0 // D17 - SS - PB0

#define P18 Pf7 // D18 - A0 - PF7
#define P19 Pf6 // D19 - A1 - PF6
#define P20 Pf5 // D20 - A2 - PF5
#define P21 Pf4 // D21 - A3 - PF4
#define P22 Pf1 // D22 - A4 - PF1
#define P23 Pf0 // D23 - A5 - PF0

#define P24 Pd4 // D24 / D4 - A6 - PD4
#define P25 Pd7 // D25 / D6 - A7 - PD7
#define P26 Pb4 // D26 / D8 - A8 - PB4
#define P27 Pb5 // D27 / D9 - A9 - PB5
#define P28 Pb6 // D28 / D10 - A10 - PB6
#define P29 Pd6 // D29 / D12 - A11 - PD6

// Arduino Leonardo pin numbers

#elif defined(CORE_TEENSY) && (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__))
// Teensy++ 1.0 and 2.0 pin numbers
// http://www.pjrc.com/teensy/pinout.html
#define P0  Pd0
#define P1  Pd1
#define P2  Pd2
#define P3  Pd3
#define P4  Pd4
#define P5  Pd5
#define P6  Pd6
#define P7  Pd7
#define P8  Pe0
#define P9  Pe1
#define P10 Pc0
#define P11 Pc1
#define P12 Pc2
#define P13 Pc3
#define P14 Pc4
#define P15 Pc5
#define P16 Pc6
#define P17 Pc7
#define P18 Pe6
#define P19 Pe7
#define P20 Pb0
#define P21 Pb1
#define P22 Pb2
#define P23 Pb3
#define P24 Pb4
#define P25 Pb5
#define P26 Pb6
#define P27 Pb7
#define P28 Pa0
#define P29 Pa1
#define P30 Pa2
#define P31 Pa3
#define P32 Pa4
#define P33 Pa5
#define P34 Pa6
#define P35 Pa7
#define P36 Pe4
#define P37 Pe5
#define P38 Pf0
#define P39 Pf1
#define P40 Pf2
#define P41 Pf3
#define P42 Pf4
#define P43 Pf5
#define P44 Pf6
#define P45 Pf7
// Teensy++ 1.0 and 2.0

#elif defined(ARDUINO_AVR_BALANDUINO) && (defined(__AVR_ATmega644__) || defined(__AVR_ATmega1284P__))
// Balanduino pin numbers
// http://balanduino.net/
#define P0  Pd0 /* 0  - PD0 */
#define P1  Pd1 /* 1  - PD1 */

#if BALANDUINO_REVISION < 13
  #define P2  Pb2 /* 2  - PB2 */
  #define P3  Pd6 /* 3  - PD6 */
  #define P4  Pd7 /* 4  - PD7 */
  #define P5  Pb3 /* 5  - PB3 */
#else
  #define P2  Pd2 /* 2  - PD2 */
  #define P3  Pd3 /* 3  - PD3 */
  #define P4  Pd6 /* 4  - PD6 */
  #define P5  Pd7 /* 5  - PD7 */
#endif

#define P6  Pb4 /* 6  - PB4 */
#define P7  Pa0 /* 7  - PA0 */
#define P8  Pa1 /* 8  - PA1 */
#define P9  Pa2 /* 9  - PA2 */
#define P10 Pa3 /* 10 - PA3 */
#define P11 Pa4 /* 11 - PA4 */
#define P12 Pa5 /* 12 - PA5 */
#define P13 Pc1 /* 13 - PC1 */
#define P14 Pc0 /* 14 - PC0 */

#if BALANDUINO_REVISION < 13
  #define P15 Pd2 /* 15 - PD2 */
  #define P16 Pd3 /* 16 - PD3 */
#else
  #define P15 Pb2 /* 15 - PB2 */
  #define P16 Pb3 /* 16 - PB2 */
#endif

#define P17 Pd4 /* 17 - PD4 */
#define P18 Pd5 /* 18 - PD5 */
#define P19 Pc2 /* 19 - PC2 */
#define P20 Pc3 /* 20 - PC3 */
#define P21 Pc4 /* 21 - PC4 */
#define P22 Pc5 /* 22 - PC5 */
#define P23 Pc6 /* 23 - PC6 */
#define P24 Pc7 /* 24 - PC7 */
#define P25 Pb0 /* 25 - PB0 */
#define P26 Pb1 /* 26 - PB1 */
#define P27 Pb5 /* 27 - PB5 */
#define P28 Pb6 /* 28 - PB6 */
#define P29 Pb7 /* 29 - PB7 */
#define P30 Pa6 /* 30 - PA6 */
#define P31 Pa7 /* 31 - PA7 */
// Balanduino

#elif defined(__AVR_ATmega644__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
// Sanguino pin numbers
// Homepage: http://sanguino.cc/hardware
// Hardware add-on: https://github.com/Lauszus/Sanguino
#define P0  Pb0
#define P1  Pb1
#define P2  Pb2
#define P3  Pb3
#define P4  Pb4
#define P5  Pb5
#define P6  Pb6
#define P7  Pb7
#define P8  Pd0
#define P9  Pd1
#define P10 Pd2
#define P11 Pd3
#define P12 Pd4
#define P13 Pd5
#define P14 Pd6
#define P15 Pd7
#define P16 Pc0
#define P17 Pc1
#define P18 Pc2
#define P19 Pc3
#define P20 Pc4
#define P21 Pc5
#define P22 Pc6
#define P23 Pc7
#define P24 Pa0
#define P25 Pa1
#define P26 Pa2
#define P27 Pa3
#define P28 Pa4
#define P29 Pa5
#define P30 Pa6
#define P31 Pa7
// Sanguino

#else
#error "Please define board in avrpins.h"

#endif // Arduino pin definitions

#elif defined(__arm__)

// pointers are 32 bits on ARM
#define pgm_read_pointer(p) pgm_read_dword(p)

#if defined(CORE_TEENSY) && (defined(__MK20DX128__) || defined(__MK20DX256__))

#include "core_pins.h"
#include "avr_emulation.h"

#define GPIO_BITBAND_ADDR(reg, bit) (((uint32_t)&(reg) - 0x40000000) * 32 + (bit) * 4 + 0x42000000)
#define GPIO_BITBAND_PTR(reg, bit) ((uint8_t *)GPIO_BITBAND_ADDR((reg), (bit)))

#define MAKE_PIN(className, baseReg, pinNum, configReg) \
class className { \
public: \
  static void Set() { \
    *GPIO_BITBAND_PTR(baseReg, pinNum) = 1; \
  } \
  static void Clear() { \
    *GPIO_BITBAND_PTR(baseReg, pinNum) = 0; \
  } \
  static void SetDirRead() { \
    configReg = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); \
    *(GPIO_BITBAND_PTR(baseReg, pinNum) + 640) = 0; \
  } \
  static void SetDirWrite() { \
    configReg = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1); \
    *(GPIO_BITBAND_PTR(baseReg, pinNum) + 640) = 1; \
  } \
  static uint8_t IsSet() { \
    return *(GPIO_BITBAND_PTR(baseReg, pinNum) + 512); \
  } \
};

MAKE_PIN(P0, CORE_PIN0_PORTREG, CORE_PIN0_BIT, CORE_PIN0_CONFIG);
MAKE_PIN(P1, CORE_PIN1_PORTREG, CORE_PIN1_BIT, CORE_PIN1_CONFIG);
MAKE_PIN(P2, CORE_PIN2_PORTREG, CORE_PIN2_BIT, CORE_PIN2_CONFIG);
MAKE_PIN(P3, CORE_PIN3_PORTREG, CORE_PIN3_BIT, CORE_PIN3_CONFIG);
MAKE_PIN(P4, CORE_PIN4_PORTREG, CORE_PIN4_BIT, CORE_PIN4_CONFIG);
MAKE_PIN(P5, CORE_PIN5_PORTREG, CORE_PIN5_BIT, CORE_PIN5_CONFIG);
MAKE_PIN(P6, CORE_PIN6_PORTREG, CORE_PIN6_BIT, CORE_PIN6_CONFIG);
MAKE_PIN(P7, CORE_PIN7_PORTREG, CORE_PIN7_BIT, CORE_PIN7_CONFIG);
MAKE_PIN(P8, CORE_PIN8_PORTREG, CORE_PIN8_BIT, CORE_PIN8_CONFIG);
MAKE_PIN(P9, CORE_PIN9_PORTREG, CORE_PIN9_BIT, CORE_PIN9_CONFIG);
MAKE_PIN(P10, CORE_PIN10_PORTREG, CORE_PIN10_BIT, CORE_PIN10_CONFIG);
MAKE_PIN(P11, CORE_PIN11_PORTREG, CORE_PIN11_BIT, CORE_PIN11_CONFIG);
MAKE_PIN(P12, CORE_PIN12_PORTREG, CORE_PIN12_BIT, CORE_PIN12_CONFIG);
MAKE_PIN(P13, CORE_PIN13_PORTREG, CORE_PIN13_BIT, CORE_PIN13_CONFIG);
MAKE_PIN(P14, CORE_PIN14_PORTREG, CORE_PIN14_BIT, CORE_PIN14_CONFIG);
MAKE_PIN(P15, CORE_PIN15_PORTREG, CORE_PIN15_BIT, CORE_PIN15_CONFIG);
MAKE_PIN(P16, CORE_PIN16_PORTREG, CORE_PIN16_BIT, CORE_PIN16_CONFIG);
MAKE_PIN(P17, CORE_PIN17_PORTREG, CORE_PIN17_BIT, CORE_PIN17_CONFIG);
MAKE_PIN(P18, CORE_PIN18_PORTREG, CORE_PIN18_BIT, CORE_PIN18_CONFIG);
MAKE_PIN(P19, CORE_PIN19_PORTREG, CORE_PIN19_BIT, CORE_PIN19_CONFIG);
MAKE_PIN(P20, CORE_PIN20_PORTREG, CORE_PIN20_BIT, CORE_PIN20_CONFIG);
MAKE_PIN(P21, CORE_PIN21_PORTREG, CORE_PIN21_BIT, CORE_PIN21_CONFIG);
MAKE_PIN(P22, CORE_PIN22_PORTREG, CORE_PIN22_BIT, CORE_PIN22_CONFIG);
MAKE_PIN(P23, CORE_PIN23_PORTREG, CORE_PIN23_BIT, CORE_PIN23_CONFIG);
MAKE_PIN(P24, CORE_PIN24_PORTREG, CORE_PIN24_BIT, CORE_PIN24_CONFIG);
MAKE_PIN(P25, CORE_PIN25_PORTREG, CORE_PIN25_BIT, CORE_PIN25_CONFIG);
MAKE_PIN(P26, CORE_PIN26_PORTREG, CORE_PIN26_BIT, CORE_PIN26_CONFIG);
MAKE_PIN(P27, CORE_PIN27_PORTREG, CORE_PIN27_BIT, CORE_PIN27_CONFIG);
MAKE_PIN(P28, CORE_PIN28_PORTREG, CORE_PIN28_BIT, CORE_PIN28_CONFIG);
MAKE_PIN(P29, CORE_PIN29_PORTREG, CORE_PIN29_BIT, CORE_PIN29_CONFIG);
MAKE_PIN(P30, CORE_PIN30_PORTREG, CORE_PIN30_BIT, CORE_PIN30_CONFIG);
MAKE_PIN(P31, CORE_PIN31_PORTREG, CORE_PIN31_BIT, CORE_PIN31_CONFIG);
MAKE_PIN(P32, CORE_PIN32_PORTREG, CORE_PIN32_BIT, CORE_PIN32_CONFIG);
MAKE_PIN(P33, CORE_PIN33_PORTREG, CORE_PIN33_BIT, CORE_PIN33_CONFIG);

#undef MAKE_PIN

#elif defined(ARDUINO_SAM_DUE) && defined(__SAM3X8E__)

// SetDirRead:
//   Disable interrupts
//   Disable the pull up resistor
//   Set to INPUT
//   Enable PIO

// SetDirWrite:
//   Disable interrupts
//   Disable the pull up resistor
//   Set to OUTPUT
//   Enable PIO

#define MAKE_PIN(className, pio, pinMask) \
class className { \
public: \
  static void Set() { \
    pio->PIO_SODR = pinMask; \
  } \
  static void Clear() { \
    pio->PIO_CODR = pinMask; \
  } \
  static void SetDirRead() { \
    pio->PIO_IDR = pinMask ; \
    pio->PIO_PUDR = pinMask; \
    pio->PIO_ODR = pinMask; \
    pio->PIO_PER = pinMask; \
  } \
  static void SetDirWrite() { \
    pio->PIO_IDR = pinMask ; \
    pio->PIO_PUDR = pinMask; \
    pio->PIO_OER = pinMask; \
    pio->PIO_PER = pinMask; \
  } \
  static uint8_t IsSet() { \
    return pio->PIO_PDSR & pinMask; \
  } \
};

// See: http://arduino.cc/en/Hacking/PinMappingSAM3X and variant.cpp

MAKE_PIN(P0, PIOA, PIO_PA8);
MAKE_PIN(P1, PIOA, PIO_PA9);
MAKE_PIN(P2, PIOB, PIO_PB25);
MAKE_PIN(P3, PIOC, PIO_PC28);
MAKE_PIN(P4, PIOC, PIO_PC26);
MAKE_PIN(P5, PIOC, PIO_PC25);
MAKE_PIN(P6, PIOC, PIO_PC24);
MAKE_PIN(P7, PIOC, PIO_PC23);
MAKE_PIN(P8, PIOC, PIO_PC22);
MAKE_PIN(P9, PIOC, PIO_PC21);
MAKE_PIN(P10, PIOC, PIO_PC29);
MAKE_PIN(P11, PIOD, PIO_PD7);
MAKE_PIN(P12, PIOD, PIO_PD8);
MAKE_PIN(P13, PIOB, PIO_PB27);
MAKE_PIN(P14, PIOD, PIO_PD4);
MAKE_PIN(P15, PIOD, PIO_PD5);
MAKE_PIN(P16, PIOA, PIO_PA13);
MAKE_PIN(P17, PIOA, PIO_PA12);
MAKE_PIN(P18, PIOA, PIO_PA11);
MAKE_PIN(P19, PIOA, PIO_PA10);
MAKE_PIN(P20, PIOB, PIO_PB12);
MAKE_PIN(P21, PIOB, PIO_PB13);
MAKE_PIN(P22, PIOB, PIO_PB26);
MAKE_PIN(P23, PIOA, PIO_PA14);
MAKE_PIN(P24, PIOA, PIO_PA15);
MAKE_PIN(P25, PIOD, PIO_PD0);
MAKE_PIN(P26, PIOD, PIO_PD1);
MAKE_PIN(P27, PIOD, PIO_PD2);
MAKE_PIN(P28, PIOD, PIO_PD3);
MAKE_PIN(P29, PIOD, PIO_PD6);
MAKE_PIN(P30, PIOD, PIO_PD9);
MAKE_PIN(P31, PIOA, PIO_PA7);
MAKE_PIN(P32, PIOD, PIO_PD10);
MAKE_PIN(P33, PIOC, PIO_PC1);
MAKE_PIN(P34, PIOC, PIO_PC2);
MAKE_PIN(P35, PIOC, PIO_PC3);
MAKE_PIN(P36, PIOC, PIO_PC4);
MAKE_PIN(P37, PIOC, PIO_PC5);
MAKE_PIN(P38, PIOC, PIO_PC6);
MAKE_PIN(P39, PIOC, PIO_PC7);
MAKE_PIN(P40, PIOC, PIO_PC8);
MAKE_PIN(P41, PIOC, PIO_PC9);
MAKE_PIN(P42, PIOA, PIO_PA19);
MAKE_PIN(P43, PIOA, PIO_PA20);
MAKE_PIN(P44, PIOC, PIO_PC19);
MAKE_PIN(P45, PIOC, PIO_PC18);
MAKE_PIN(P46, PIOC, PIO_PC17);
MAKE_PIN(P47, PIOC, PIO_PC16);
MAKE_PIN(P48, PIOC, PIO_PC15);
MAKE_PIN(P49, PIOC, PIO_PC14);
MAKE_PIN(P50, PIOC, PIO_PC13);
MAKE_PIN(P51, PIOC, PIO_PC12);
MAKE_PIN(P52, PIOB, PIO_PB21);
MAKE_PIN(P53, PIOB, PIO_PB14);
MAKE_PIN(P54, PIOA, PIO_PA16);
MAKE_PIN(P55, PIOA, PIO_PA24);
MAKE_PIN(P56, PIOA, PIO_PA23);
MAKE_PIN(P57, PIOA, PIO_PA22);
MAKE_PIN(P58, PIOA, PIO_PA6);
MAKE_PIN(P59, PIOA, PIO_PA4);
MAKE_PIN(P60, PIOA, PIO_PA3);
MAKE_PIN(P61, PIOA, PIO_PA2);
MAKE_PIN(P62, PIOB, PIO_PB17);
MAKE_PIN(P63, PIOB, PIO_PB18);
MAKE_PIN(P64, PIOB, PIO_PB19);
MAKE_PIN(P65, PIOB, PIO_PB20);
MAKE_PIN(P66, PIOB, PIO_PB15);
MAKE_PIN(P67, PIOB, PIO_PB16);
MAKE_PIN(P68, PIOA, PIO_PA1);
MAKE_PIN(P69, PIOA, PIO_PA0);
MAKE_PIN(P70, PIOA, PIO_PA17);
MAKE_PIN(P71, PIOA, PIO_PA18);
MAKE_PIN(P72, PIOC, PIO_PC30);
MAKE_PIN(P73, PIOA, PIO_PA21);
MAKE_PIN(P74, PIOA, PIO_PA25); // MISO
MAKE_PIN(P75, PIOA, PIO_PA26); // MOSI
MAKE_PIN(P76, PIOA, PIO_PA27); // CLK
MAKE_PIN(P77, PIOA, PIO_PA28);
MAKE_PIN(P78, PIOB, PIO_PB23); // Unconnected

#undef MAKE_PIN

#elif defined(RBL_NRF51822)

#define MAKE_PIN(className, pin) \
class className { \
public: \
    static void Set() { \
        nrf_gpio_pin_set(pin); \
    } \
    static void Clear() { \
        nrf_gpio_pin_clear(pin); \
    } \
    static void SetDirRead() { \
        nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL); \
    } \
    static void SetDirWrite() { \
        nrf_gpio_cfg_output(pin); \
    } \
    static uint8_t IsSet() { \
        return (uint8_t)nrf_gpio_pin_read(pin); \
    } \
};

// See: pin_transform.c in RBL nRF51822 SDK
MAKE_PIN(P0, Pin_nRF51822_to_Arduino(D0));
MAKE_PIN(P1, Pin_nRF51822_to_Arduino(D1));
MAKE_PIN(P2, Pin_nRF51822_to_Arduino(D2));
MAKE_PIN(P3, Pin_nRF51822_to_Arduino(D3));
MAKE_PIN(P4, Pin_nRF51822_to_Arduino(D4));
MAKE_PIN(P5, Pin_nRF51822_to_Arduino(D5));
MAKE_PIN(P6, Pin_nRF51822_to_Arduino(D6));
MAKE_PIN(P7, Pin_nRF51822_to_Arduino(D7));
MAKE_PIN(P8, Pin_nRF51822_to_Arduino(D8));
MAKE_PIN(P9, Pin_nRF51822_to_Arduino(D9)); // INT
MAKE_PIN(P10, Pin_nRF51822_to_Arduino(D10)); // SS
MAKE_PIN(P11, Pin_nRF51822_to_Arduino(D11));
MAKE_PIN(P12, Pin_nRF51822_to_Arduino(D12));
MAKE_PIN(P13, Pin_nRF51822_to_Arduino(D13));
MAKE_PIN(P14, Pin_nRF51822_to_Arduino(D14));
MAKE_PIN(P15, Pin_nRF51822_to_Arduino(D15));
MAKE_PIN(P17, Pin_nRF51822_to_Arduino(D17)); // MISO
MAKE_PIN(P18, Pin_nRF51822_to_Arduino(D18)); // MOSI
MAKE_PIN(P16, Pin_nRF51822_to_Arduino(D16)); // CLK
MAKE_PIN(P19, Pin_nRF51822_to_Arduino(D19));
MAKE_PIN(P20, Pin_nRF51822_to_Arduino(D20));
MAKE_PIN(P21, Pin_nRF51822_to_Arduino(D21));
MAKE_PIN(P22, Pin_nRF51822_to_Arduino(D22));
MAKE_PIN(P23, Pin_nRF51822_to_Arduino(D23));
MAKE_PIN(P24, Pin_nRF51822_to_Arduino(D24));

#undef MAKE_PIN

#else
#error "Please define board in avrpins.h"

#endif

#elif defined(__ARDUINO_X86__) // Intel Galileo, Intel Galileo 2 and Intel Edison

#include <avr/pgmspace.h>

// Pointers are 32 bits on x86
#define pgm_read_pointer(p) pgm_read_dword(p)

#if PLATFORM_ID == 0xE1 // Edison platform id
#define pinToFastPin(pin) 1 // As far as I can tell all pins can be used as fast pins
#endif

// Pin 2 and 3 on the Intel Galileo supports a higher rate,
// so it is recommended to use one of these as the SS pin.

#define MAKE_PIN(className, pin) \
class className { \
public: \
  static void Set() { \
    fastDigitalWrite(pin, HIGH); \
  } \
  static void Clear() { \
    fastDigitalWrite(pin, LOW); \
  } \
  static void SetDirRead() { \
    if (pinToFastPin(pin)) \
      pinMode(pin, INPUT_FAST); \
    else \
      pinMode(pin, INPUT); \
  } \
  static void SetDirWrite() { \
    if (pinToFastPin(pin)) \
      pinMode(pin, OUTPUT_FAST); \
    else \
      pinMode(pin, OUTPUT); \
  } \
  static uint8_t IsSet() { \
    return fastDigitalRead(pin); \
  } \
};

MAKE_PIN(P0, 0);
MAKE_PIN(P1, 1);
MAKE_PIN(P2, 2);
MAKE_PIN(P3, 3);
MAKE_PIN(P4, 4);
MAKE_PIN(P5, 5);
MAKE_PIN(P6, 6);
MAKE_PIN(P7, 7);
MAKE_PIN(P8, 8);
MAKE_PIN(P9, 9);
MAKE_PIN(P10, 10);
MAKE_PIN(P11, 11);
MAKE_PIN(P12, 12);
MAKE_PIN(P13, 13);
MAKE_PIN(P14, 14); // A0
MAKE_PIN(P15, 15); // A1
MAKE_PIN(P16, 16); // A2
MAKE_PIN(P17, 17); // A3
MAKE_PIN(P18, 18); // A4
MAKE_PIN(P19, 19); // A5

#undef MAKE_PIN

#elif defined(__MIPSEL__)
// MIPSEL (MIPS architecture using a little endian byte order)

// MIPS size_t = 4
#define pgm_read_pointer(p) pgm_read_dword(p)

#define MAKE_PIN(className, pin) \
class className { \
public: \
  static void Set() { \
    digitalWrite(pin, HIGH);\
  } \
  static void Clear() { \
    digitalWrite(pin, LOW); \
  } \
  static void SetDirRead() { \
    pinMode(pin, INPUT); \
  } \
  static void SetDirWrite() { \
    pinMode(pin, OUTPUT); \
  } \
  static uint8_t IsSet() { \
    return digitalRead(pin); \
  } \
};

// 0 .. 13 - Digital pins
MAKE_PIN(P0, 0); // RX
MAKE_PIN(P1, 1); // TX
MAKE_PIN(P2, 2); //
MAKE_PIN(P3, 3); //
MAKE_PIN(P4, 4); //
MAKE_PIN(P5, 5); //
MAKE_PIN(P6, 6); //
MAKE_PIN(P7, 7); //
MAKE_PIN(P8, 8); //
MAKE_PIN(P9, 9); //
MAKE_PIN(P10, 10); //
MAKE_PIN(P11, 11); //
MAKE_PIN(P12, 12); //
MAKE_PIN(P13, 13); //

#undef MAKE_PIN

#else
#error "Please define board in avrpins.h"

#endif

#endif //_avrpins_h_

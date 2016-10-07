# My take on a splitted keyboard

to build :

    docker run --rm -e keymap=default -e subproject=v1 -e keyboard=frenchdev --rm -v D:/Repositories/qmk:/qmk:rw edasque/qmk_firmware
    

The PHYSICAL rows and columns are connected as such :

on right hand (slave) :

              I2C mcp23018
           .-------   --------.
      GND -| 1 VSS \_/  NC 28 |
           | 2 NC       A7 27 |- C15
       R5 -| 3 B0       A6 26 |- C14
       R4 -| 4 B1       A5 25 |- C13
       R3 -| 5 B2       A4 24 |- C12
       R2 -| 6 B3       A3 23 |- C11
       R1 -| 7 B4       A2 22 |- C10
       R0 -| 8 B5       A1 21 |- C9
           | 9 B6       A0 20 |- C8
           | 10 B7    INTA 19 |
      VCC -| 11 VDD   INTB 18 |
      SCL -| 12 SCL     NC 17 |
      SDA -| 13 SDA    RST 16 |- VCC
           | 14 NC    ADDR 15 |- GND
           `------------------'

and on left hand (main) :

                  TEENSY
           .------------------.
           | GND          VCC |
       C7 -| B0            F0 |- R5
       C6 -| B1            F1 |- R4
       C5 -| B2            F4 |- R3
       C4 -| B3            F5 |- R2
     LEDC -| B7            F6 |- R1
      SCL -| D0            F7 |- R0
      SDA -| D1            B6 |- LEDB
       C3 -| D2            B5 |- LEDA
       C2 -| D3            B4 |
       C1 -| C6            D7 |
       C0 -| C7            D6 |- GND
           | D5            D4 |
           | VCC          RST |
           | E6           GND |
           `------------------'

we use pull up resistor for SCL et VDA, see https://github.com/ErgoDox-EZ/docs/blob/master/ErgoDox%20EZ%20Schematic.pdf for example

the connector is a standard TRRS (jack with audio + mic)

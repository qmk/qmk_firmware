
This is a way to take a Microsoft ergonomic bluetooth keyboard, and make it 
into a hard-wired keyboard running QMK. 

The keyboard is known under several different names:
Mobile Bluetooth 5000, Mobile 6000, Sculpt mobile, and Asus rebranded 

I had a stack of them,since they're cheap on ebay, travel well, and are just ergo enough. 

The ribbon cable is 1mm pitch, which is hard to hand solder. I bought a cheap set of 
"pitch adapter" boards https://www.amazon.com/Double-Sided-0-4mm-1-0-Adapter-60mmx38mm/dp/B00OK42118

Cut the original ribbon cable sockets off the bluetooth board using a razor, they're hard to desolder. 
They're also allow the cable to be inserted on top or bottom. 

If I was going to do it again, I'd make the MCU connection come out the top of the keyboard
and avoid the wires dangling out the bottom. 

As I was debugging the matrix, I started to get random failures. In desparation I tried a second MCU, 
but had the same problems. It turns out that the ribbon cable connections can get worn. Shave a
half millimeter off the end of the ribbon cable & the errors go away. 

My method for discovering the matrix was to set up a KEYMAP macro that included all pins. 
See MATRIX_TESTING_KEYMAP if you need it. Then set up a keymap that has all printable symbols
in the first 4 rows. test each key & record output. Then switch the printable symbols to the
bottom 4 rows & repeat. This was enough to show the matrix. 


The full original keymap for the sculpt is 
        A       B       C       D       E       F       G       H   --->  
0       b       n       m       ,       .       /                
1       g       h       "                                          
2       7       8       9       0       Del             PgUp     
3       p       [       ]       \                                
4       y       u       i       o                                      
5       ~       -       +=      j       k       l       ;       5
6       a       s       d       q       w       e,      Up      left    
7       F7      F8      F9      F10     F11     F12             f
    			
----->  I       J       K       L       M       N       O       P       Q       R       
0               Caps                                                            FN      
1                       Vol+    mute    Rctl            vol-    pgdn    LCTL            
2                               Rshift                          LShift                  
3                       Ralt                            LAlt                    
4                                               LGUI                                            
5       6       bakspc  1       2       3       4       F4      F5      F6                      
6       Down    right                           spc     F1      F2      F3      tab             
7       r       t       z       x       c               v       enter   Esc                     

This works with 18 cols + 8  rows on a Teensy++, or Arm based Teensy. 

The Astar mini has all pins exposed , so you can do 18x8
If you want a speaker, LEDs &etc, you'll need to free up a pin.  I recommend joining columns
R and L to the same pin. 

Building - add ASTAR=1 to the compile line or leave out for teensy2++



# haervig Userspace

This userspace keeps my userdefined codes. I work on a ANSI keyboard on a Danish macOS system. I believe this code might be relevant for similar users. A big shout out to user spacebarracecar for the ideas on how to map keys, which served as the basis of this code.

## US Layout Keys for Danish PCs

By daily work involves a lot of coding. I find an ANSI layout superior and decided to buy a QMK keyboard. However, all PC's here in Denmark are set to input language Danish. Even though I could simply set input language language to US international, I find this inconvenient. I instead decided to map my keys so the ANSI keyboard would will function as expected when the OS inputn language is Danish.

## More details

Tracking the current state of the shift code is nessesary for it to work. User spacebarracecar has documented the idea thoroughly and should serve you as a starting point if you wish to implement this code. I modified the code to suit Danish input language. Additionally, a couple of functions were added to accomodate the altgr key.
# Santoku Gen 2

![Santoku Gen 2](https://preview.redd.it/nhoapw0iipa71.jpg?width=960&crop=smart&auto=webp&s=e320ca4ef5c62676f29c2c193c00d6a6d3278e01)

[Reddit intro post](https://www.reddit.com/r/ErgoMechKeyboards/comments/oisnad/i_made_this_santoku_gen_2_trackpoint_as_a/)

## Design Goals:

A compact keyboard that is equally useful at home or on the road. I don't have any interest in using separate boards depending on where I am.

It had to be compact but flexible in use. It had to fit in with my mobile office and easily fit in my work bag or carry-on. Because I visit various offices, it had to look professional even if it isn't what people are used to seeing. It also had to be robust enough to handle the rigors of travel (still somewhat TBD). So, naked PCBs were out -- the case is an integral part of the entire design.

I've taken a fair amount of flak for emphasizing the "travel board" aspect of my designs. I don't know what to say except that it's important to me since I live out of a suitcase four months out of the year and laptop keyboards generally suck. (well… I traveled pre-COVID-19. But things are slowly coming around again.)

It was also important to try to future-proof the design. The large garage in the middle of the board provides some freedom to add new hardware without redesigning everything from scratch. Specifically, I'm looking at you, ZMK/wireless, and waiting to see how peripheral hardware support evolves.



### Trackpoint:

The Gen 1 Santoku forced me to rethink many of my original ideas about how to implement a Trackpoint. Much of that thinking made it into Gen 2. However, I'm not done yet and I'm already generating TODOs for Gen 3.

The Trackpoint and mouse buttons are integral to the design. I'd go so far as to say the Santoku was built around the Trackpoint. I played with using the keyboard keys as mouse buttons and just never liked it enough to stick with it. I wanted a clear distinct separation of functions while still not having to reach for the actual mouse.

The mouse buttons for the Gen 2 Trackpoint are duplicated on both the left and right side. Gen 1 had them only on the right side with the Trackpoint. However, having buttons on both sides allows the user more precision because one hand can control fine mouse movement while the other hand handles clicking.

Additionally, Gen 2 allows the Trackpoint to be used between either the "UI" or the "YU" pair of keys (on qwerty). I personally still prefer "UI" but... "options". And, yeah, I hear the pleas from everyone... I'm working on adding support to put the Trackpoint between "hjnm" and "jkm" also. Sadly, there are only so many hours in a week.



### But that RIBBON CABLE!!1!!!111!:

Yeah, the cable. I've heard it. Yes, I used an FFC (Flat Flexible Cable) on Gen 2 also, just like Gen 1. Why???? Because, with all the other goals and limitations in mind, I still think it's the least bad solution.

Other choices:

TRRS: Requires additional hardware (I/O expander) on one side. Adds complexity to the code. The current Trackpoint code in QMK is very slow and interferes with the scanning of the matrix. I also had trouble finding readily available TRRS cables that would fit perfectly in the garage when using the board as a one piece.

HDMI: Cables are too bulky. Connectors are too bulky.

Custom Braid: Technically possible. But I'm trying to make this board into a kit to be sold. Braiding wasn't feasible beyond a single unit.

Cat5: Too big. Not enough conductors for one-to-one matrix connections.

USB C: Bulky connectors. Hard to fit into garage. Adds complexity.

Traditional Ribbon Cables: Connectors too bulky. Don't like to flex much. Cable itself is too big if you want to keep the matrix simple.

So, what's left? FFC (Flat Flexible Cable). Is it perfect? Nope. But I still think it's the best choice for the Santoku. FFCs, as the name implies, are very flat and flexible. They take up little space when tucked away and can bend/unbend for 1000s of repetitions. You just have to be careful to not fold them flat. Keep a little curve and they'll last a long time. Case in point, my Gen 1 Santoku is still using the same cable I started with one year ago. COVID-19 stopped my travelling and in person office visits dead. So, to simulate, every evening I switch my board to one piece mode and stow the cable in the garage. In the morning, I convert to split mode and unstow the cable. It still works great after one year. If you do break a cable, they're cheap and easy to replace.

So, what's the downside to FFC? In my opinion, the connectors are the weak link. FFC connectors typically only have a duty cycle of 20-40 connections. Meaning, you can only replace a cable about 20-40 times before you'll need to replace the connector. The Santoku makes this less of a concern because the case provides built-in storage. That said, if your life involves cats or small children who like to bite through things, or maybe you're just really clumsy… You'll want to be extra careful. I am working on a sleeve that will fit over the cable and provide strain relief but I'm not quite happy enough with it yet.



### Why make it "splittable"?

Why not just choose split or not split?**This is another design choice that I've found is really polarizing. Why not just choose one or the other? As mentioned, I designed this as my "one board to rule them all". It's my travel board, and my home desk board, and my office visit board, and my coffee shop board. I don't like switching layouts depending on where I am. I prefer a small split but my environment doesn't always allow it. When on a plane, or a packed coffee house, I may not have room to spread out. On a plane or the HSR, the seat trays are inviting disaster with the cable. Being able to combine the halves keeps things strong and compact without having to tote around a different device.

"So, just use your laptop board when you're not at a desk…" I think I've explained it enough. I don't wanna use the crappy laptop keyboard. I want to use my board, with my Trackpoint, and all my QMK customizations.



### Is it for sale?:

This board is currently in a closed Beta stage but I hope to get to an open distribution soon. 


## Build Info
* Keyboard Maintainer: [Tye](https://github.com/tyetye)
* Hardware Supported: PCB from Tye, Elite-C
* Hardware Availability: Currently in a closed beta phase before groupbuy/distribution

Make example for this keyboard (after setting up your build environment):

    make santoku:default

Flashing example for this keyboard:

    make santoku:default:flash

If you are using qmk msys you may use: 

    qmk flash -kb santoku

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. vBrand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: *If Bootmagic enabled in rules.mk* Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the Elite-C (pro-micro: short gnd and rst pads)
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

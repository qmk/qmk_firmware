# This is u/TurboMech's keyboard layout for Espectro.  

## It is designed for Mac OS, due to the specific functions created.  

### Here is the layout found in the keymap.c file.
#####  I use shortcuts for the Function row (above number row) listed below
  - Scrn Bright Up: F14
  - Scrn Bright Down: F15
  - Expose: LCTRL + Up 
  - Launchpad: LCTRL + L
  - Show Desktop: F11
  - Show/Hide Dock: LALT + LGUI + D
  - Screen Capture: LCTRL + S
  - Custom Shortcut 1: LCTRL + LGUI + 1
  - Custom Shortcut 2: LCTRL + LGUI + 2
    - use the custom shortcuts for whatever you want: launch an application, a macro, etc.  
  - Play/Pause: exactly that
  - Mute / Volume Up / Volume Down: exactly what it says
  - QALL: Quit all applications

 ##### Going down the right side from Vol Down:
  - POWER: this serves as the power button on Mac's only.  Press and hold the button as you would on your Macbook or iMac keyboard.
  - Menu: this slides the notification bar on the right side (its the same as on iPhones/ iPads) 

### See below keymaps for how to setup shortcuts on Mac

#### Base Layer
```
Needs updating.
```
#### Function Layer 1 - See above for shortcuts
```
Needs updating
```

#### How to use/ setup shortcuts on Mac
- First navigate to System Preferences > Keyboard > Shortcuts
  - You can use any of them in here
  - Just set them to the shortcut keys listed above

#### How to make your own (to launch applications, quit all, etc.)
- Navigate to Automator > New Document > click Service > Choose
- Now we have to setup our shortcut
  - Here's how to setup the Quit All Shortcut
    - In the right window select the Service recieves dropdown > select No Input
    - At the top left click the Name (Search) > type quit > click and hold Quit All Applications > drag to the right hand box (under the Service Recieves) 
      - **IMPORTANT** You have to click the Run button at the upper right hand corner in order for these to actually work. 
    - Now click File > Save > save it as Quit All Apps (or whatever you want) / you can also just exit out and it'll ask you if you want to save
- Navigate back to System Preferences > Keyboard > Shortcuts
    - The new shortcut can be found under services, set it to one of the shortcuts I listed above and done
- The same applies for applications in the Name (search) just type the application you want to have as shortcut. Don't forget to run it, then do the same steps
  to set it up as a shortcut.





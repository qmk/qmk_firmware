Todo:
=====


                       § Further development

           The following seem interesting for further development. However following the “scratch your
           own itch” rule, perhaps it should be someone else's interest. Contributions welcomed !

             ☐ It seems fun to have a user friendly front end to compile the available variations of this keymap.
               Such a front end could edit minifan_config_compact.h 
           
             ☐ Language specific keyboards, such as Qwertz and Azerty, etc.

               • Using an include like #include keymap_german.h (etc), and matching computer operating side
                 remapping does seem to make a lot possible, although it does introduce the dead key problem.
                 It seems that computer side remapping of the common symbols, could require the Unicode input
                 to have its own special “descramble” system, similar to that for Dvorak-Descramble. If so,
                 it should not be too difficult to copy/alter that code.

               • If a language specific #include and computer language setting is not used, but merely some basics
                 such as a matching basic alphabet ABC…XYZ on Base, with some additional Unicode symbols for that
                 language on _ACC and or other Unicode layers, it might be simple to make, and avoid the dead key
                 problem. To go another step and recreate a key like ‛<>’ (as it seems to exist in Qwertz), would
                 seem to require their own macros in unicode_macros.c.

               This ‛<>’ key on a Qwertz keyboard illustrates the issue. Qwerty doesn't have ‛<>’, only ‛,<’ and 
               ‛.>’. With computer keyboard language set to German and this #included:
               https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_german.h,
               you can program the key ‛<>’ by writing ‛DE_LABK’, which turns out to be: ‛KC_NUBS’, which turns
               out to mean: https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes_basic ➡ 
               “KC_NONUS_BSLASH KC_NUBS Non-US \ and \|”. Your keyboard is generating ‛\|’. The computer with
               an English/US keyboard setting read that scancode as ‛\|’. With a German language setting, this
               scancode would be converted into ‛<>’ (that is, ‛<’ unshifted, ‛>’ shifted).
               See also: “#define DE_RABK S(DE_LABK) // >”. Shifted KC_NUBS becomes ‛>’.
               Notice that also the letters get recoded: #define DE_Z    KC_Y    // Z
               
               Hence there are the two possibilities: keyboard language set to English/US, shuffle the simple
               symbols which are the same shifted/unshifted like letters around until it works, with macros for 
               otherwise non-existing keys; or the other way around: make it easy on the common symbols by setting 
               the computer keyboard interpretation to the target language (German for Qwertz, for example), use
               those QMK language #defines, and do the work on making the Unicodes work.

               You can also have it both ways, similar to Dvorak and Dvorak-Descramble can both be compiled
               together. It seems however that both versions might work differently, because one of them uses
               the dead-key system to generate symbols, and the other doesn't. There could be ways around this,
               altering the Qwertz keymap, giving a combination of two symbols for one keystroke. Example:
               ‛Ç’, as one stroke, first the ‛,’ thingy, then the ‛C’.

               With a few changes to for example standard Qwertz (like ‛üÜ’ below ‛uU’ on _ACC), it looks like 
               it should fit on the Minivan, or sacrifice that Backspace. The whole _ACC layer can be repurposed, 
               or even _DRA and _BON as well.

               {Original author of this keymap (Jos B.): I'm not familiar enough with the other languages to
                do a good job.}

                       § Other:

             ☐ Testing all user configurations
             ☐ Porting to Planck keyboard. This has been cooked into the code already, at least to a degree,
               but it remains untested. If someone has a Planck they could try it. 
             ☐ Test/fix what happens when leds are undefined with the existing QMK led #define(s)
             ☐ Review/fix C indendation. QMK indentation is not my preferred style, and 
               therefore it is not entirely consistent. 
            ?☐ A lock mode, so that others cannot type on it if you walk off ?
            ?☐ Fun and games: game layer.

            ?☒ User defining macros (record/play user input), another special Base layer ? Is there 
               room for this, or how to create it if not.
               ➡ It seems a bit odd to have a keyboard with internal registers. Probably better handled at the
                 application level, so that the keyboard remains a basic input device.

Todo:
=====


                       § Further development

           The following seem interesting for further development. However following the “scratch your
           own itch” rule, perhaps it should be someone else's interest.

             ☐ It seems fun to have a user friendly front end to compile the available variations of this keymap.
               Such a front end could edit minifan_config_compact.h 
           
             ☐ Language specific keyboards, such as Qwertz and Azerty, etc.
               Two option exist:
               • Using an include like #include keymap_german.h (etc).
               • If a language specific #include and computer language setting is not used, but merely some basics
                 such as a matching basic alphabet ABC…XYZ on Base, with some additional Unicode symbols for that
                 language on _ACC and or other Unicode layers, it might be simple to make, and avoid the dead key
                 problem. To go another step and recreate a key like ‛<>’ (as it seems to exist in Qwertz), would
                 seem to require macros in unicode_macros.c.

                       § Other:

             ☐ Testing all user configurations
             ☐ Porting to Planck keyboard.
             ☐ Review/fix C indendation. QMK indentation is not my preferred style, and 
               therefore it is not entirely consistent. 
            ?☐ A lock mode, so that others cannot type on it if you walk off ?
            ?☐ Fun and games: game layer.

            ?☒ User defining macros (record/play user input), another special Base layer ? Is there 
               room for this, or how to create it if not.
               ➡ It seems a bit odd to have a keyboard with internal registers. Probably better handled at the
                 application level, so that the keyboard remains a basic input device.

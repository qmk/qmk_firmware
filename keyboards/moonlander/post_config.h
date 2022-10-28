#pragma once

#ifdef AUDIO_ENABLE
#    ifndef STARTUP_SONG
#        define STARTUP_SONG SONG(E__NOTE(_DS5), E__NOTE(_D5), E__NOTE(_AS4), Q__NOTE(_F5))
#    endif

#    ifndef GOODBYE_SONG
#        define GOODBYE_SONG SONG(E__NOTE(_D5), E__NOTE(_F5), E__NOTE(_C5), Q__NOTE(_AS4))
#    endif
#endif

#ifndef ISSI_TIMEOUT
#    define ISSI_TIMEOUT 5
#endif

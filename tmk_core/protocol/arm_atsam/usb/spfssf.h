#ifndef ____spfssf_h
#define ____spfssf_h

#include <stdarg.h>

#define sprintf spf
#define sscanf  ssf

#define SIZEOF_OFFSET 1

#ifndef NULL
#define NULL 0
#endif

#define SPF_NONE    0

#define SPF_SPEC_START      37      //%
#define SPF_SPEC_DECIMAL    100     //d  16bit dec signed           (-32767 to 32767)               DONE same as i
#define SPF_SPEC_INT        105     //i  16bit dec signed           (-32767 to 32767)               DONE same as d
#define SPF_SPEC_UINT       117     //u  16bit dec unsigned         (0 to 65535)                    DONE
#define SPF_SPEC_STRING     115     //s  variable length            (abcd...)                       DONE
#define SPF_SPEC_UHINT      120     //x  16bit hex lwrc             (7fa)                           DONE
#define SPF_SPEC_UHINT_UP   88      //x  16bit hex lwrc             (7fa)                           DONE
#define SPF_SPEC_LONG       108     //l  start of either ld or lu                                   DONE
#define SPF_SPEC_DECIMAL    100     //ld 32bit dec signed           (-2147483647 to 2147483647)     DONE
#define SPF_SPEC_UNSIGNED   117     //lu 32bit dec unsigned         (0 to 4294967295)               DONE
#define SPF_SPEC_UHINT      120     //lx 32bit hex unsigned         (0 to ffffffff)                 DONE

#define SSF_SPEC_START      37      //%
#define SSF_SPEC_SHORTINT   104     //h  8bit dec signed            (-127 to 127)                   DONE
#define SSF_LEN_SHORTINT    3       //hhd
#define SSF_SPEC_DECIMAL    100     //d  16bit dec signed           (-32767 to 32767)               DONE
#define SSF_LEN_DECIMAL     5       //32767
#define SSF_SPEC_INT        105     //i  16bit dec signed           (-32767 to 32767)               DONE
#define SSF_LEN_INT         5       //32767
#define SSF_SPEC_LONG       108     //l  start of either ld or lu                                   DONE
#define SSF_SPEC_DECIMAL    100     //ld 32bit dec signed           (-2147483647 to 2147483647)     DONE
#define SSF_SPEC_UHINT      120     //lx 32bit hex unsigned                                         DONE
#define SSF_LEN_LDECIMAL    10      //2147483647
#define SSF_SPEC_STRING     115     //s  variable length            (abcd...)                       DONE
#define SSF_SKIP_SPACE      32      //space

#define SSF_SPEC_VERSION    118     //v collect to comma delimiter - special
#define SSF_DELIM_COMMA     44      //,

#define ASCII_NUM_START     48      //0
#define ASCII_NUM_END       58      //9

#define T_UINT32_0_LIMIT    14
#define T_UINT32_1_LIMIT    27

int vspf(char *_Dest, const char *_Format, va_list va);
int spf(char *_Dest, const char *_Format, ...);
int ssf(const char *_Src, const char *_Format, ...);

#endif //____spfssf_h


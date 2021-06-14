/**
 * This file has a different license to the rest of the uGFX system.
 * You can copy, modify and distribute this file as you see fit.
 * You do not need to publish your source modifications to this file.
 * The only thing you are not permitted to do is to relicense it
 * under a different license.
 */

/**
 * Copy this file into your project directory and rename it as gfxconf.h
 * Edit your copy to turn on the uGFX features you want to use.
 * The values below are the defaults.
 *
 * Only remove the comments from lines where you want to change the
 * default value. This allows definitions to be included from
 * driver makefiles when required and provides the best future
 * compatibility for your project.
 *
 * Please use spaces instead of tabs in this file.
 */

#pragma once

///////////////////////////////////////////////////////////////////////////
// GFX - Compatibility options                                           //
///////////////////////////////////////////////////////////////////////////
//#define GFX_COMPAT_V2                                GFXON
//#define GFX_COMPAT_OLDCOLORS                         GFXON

///////////////////////////////////////////////////////////////////////////
// GOS - One of these must be defined, preferably in your Makefile       //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_OS_CHIBIOS                           GFXOFF
//#define GFX_USE_OS_FREERTOS                          GFXOFF
//    #define GFX_FREERTOS_USE_TRACE                   GFXOFF
//#define GFX_USE_OS_WIN32                             GFXOFF
//#define GFX_USE_OS_LINUX                             GFXOFF
//#define GFX_USE_OS_OSX                               GFXOFF
//#define GFX_USE_OS_ECOS                              GFXOFF
//#define GFX_USE_OS_RAWRTOS                           GFXOFF
//#define GFX_USE_OS_ARDUINO                           GFXOFF
//#define GFX_USE_OS_KEIL                              GFXOFF
//#define GFX_USE_OS_RTX5                              GFXOFF
//#define GFX_USE_OS_CMSIS                             GFXOFF
//#define GFX_USE_OS_CMSIS2                            GFXOFF
//#define GFX_USE_OS_RAW32                             GFXOFF
//#define GFX_USE_OS_ZEPHYR                            GFXOFF
//#define GFX_USE_OS_NIOS                              GFXOFF
//#define GFX_USE_OS_QT                                GFXOFF
//    #define INTERRUPTS_OFF()                         optional_code
//    #define INTERRUPTS_ON()                          optional_code

// Options that (should where relevant) apply to all operating systems
#define GFX_NO_INLINE GFXON
//    #define GFX_COMPILER                             GFX_COMPILER_UNKNOWN
//    #define GFX_SHOW_COMPILER                        GFXOFF
//    #define GFX_CPU                                  GFX_CPU_UNKNOWN
//    #define GFX_CPU_NO_ALIGNMENT_FAULTS              GFXOFF
//    #define GFX_CPU_ENDIAN                           GFX_CPU_ENDIAN_UNKNOWN
//    #define GFX_OS_HEAP_SIZE                         0
//    #define GFX_OS_NO_INIT                           GFXOFF
//    #define GFX_OS_INIT_NO_WARNING                   GFXOFF
//    #define GFX_OS_PRE_INIT_FUNCTION                 myHardwareInitRoutine
//    #define GFX_OS_EXTRA_INIT_FUNCTION               myOSInitRoutine
//    #define GFX_OS_EXTRA_DEINIT_FUNCTION             myOSDeInitRoutine
//    #define GFX_OS_CALL_UGFXMAIN                     GFXOFF
//    #define GFX_OS_UGFXMAIN_STACKSIZE                0
//    #define GFX_EMULATE_MALLOC                       GFXOFF
//    #define GFX_MEM_LT64K                            GFXOFF

///////////////////////////////////////////////////////////////////////////
// GDISP                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GDISP GFXON

//#define GDISP_NEED_AUTOFLUSH                         GFXOFF
//#define GDISP_NEED_TIMERFLUSH                        GFXOFF
//#define GDISP_NEED_VALIDATION                        GFXON
//#define GDISP_NEED_CLIP                              GFXON
#define GDISP_NEED_CIRCLE GFXON
//#define GDISP_NEED_DUALCIRCLE                        GFXOFF
#define GDISP_NEED_ELLIPSE GFXON
#define GDISP_NEED_ARC GFXON
#define GDISP_NEED_ARCSECTORS GFXON
#define GDISP_NEED_CONVEX_POLYGON GFXON
//#define GDISP_NEED_SCROLL                            GFXOFF
#define GDISP_NEED_PIXELREAD GFXON
#define GDISP_NEED_CONTROL GFXON
//#define GDISP_NEED_QUERY                             GFXOFF
//#define GDISP_NEED_MULTITHREAD                       GFXOFF
//#define GDISP_NEED_STREAMING                         GFXOFF
#define GDISP_NEED_TEXT GFXON
//    #define GDISP_NEED_TEXT_WORDWRAP                 GFXOFF
//    #define GDISP_NEED_TEXT_BOXPADLR                 1
//    #define GDISP_NEED_TEXT_BOXPADTB                 1
//    #define GDISP_NEED_ANTIALIAS                     GFXOFF
//    #define GDISP_NEED_UTF8                          GFXOFF
#define GDISP_NEED_TEXT_KERNING GFXON
//    #define GDISP_INCLUDE_FONT_UI1                   GFXOFF
//    #define GDISP_INCLUDE_FONT_UI2                   GFXOFF		// The smallest preferred font.
//    #define GDISP_INCLUDE_FONT_LARGENUMBERS          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS10          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS12          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS16          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS20          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24          GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32          GFXOFF
#define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12 GFXON
//    #define GDISP_INCLUDE_FONT_FIXED_10X20           GFXOFF
//    #define GDISP_INCLUDE_FONT_FIXED_7X14            GFXOFF
#define GDISP_INCLUDE_FONT_FIXED_5X8 GFXON
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS12_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS16_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS20_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12_AA   GFXOFF
//    #define GDISP_INCLUDE_USER_FONTS                 GFXOFF

//#define GDISP_NEED_IMAGE                             GFXOFF
//    #define GDISP_NEED_IMAGE_NATIVE                  GFXOFF
//    #define GDISP_NEED_IMAGE_GIF                     GFXOFF
//        #define GDISP_IMAGE_GIF_BLIT_BUFFER_SIZE     32
//    #define GDISP_NEED_IMAGE_BMP                     GFXOFF
//        #define GDISP_NEED_IMAGE_BMP_1               GFXON
//        #define GDISP_NEED_IMAGE_BMP_4               GFXON
//        #define GDISP_NEED_IMAGE_BMP_4_RLE           GFXON
//        #define GDISP_NEED_IMAGE_BMP_8               GFXON
//        #define GDISP_NEED_IMAGE_BMP_8_RLE           GFXON
//        #define GDISP_NEED_IMAGE_BMP_16              GFXON
//        #define GDISP_NEED_IMAGE_BMP_24              GFXON
//        #define GDISP_NEED_IMAGE_BMP_32              GFXON
//        #define GDISP_IMAGE_BMP_BLIT_BUFFER_SIZE     32
//    #define GDISP_NEED_IMAGE_JPG                     GFXOFF
//    #define GDISP_NEED_IMAGE_PNG                     GFXOFF
//        #define GDISP_NEED_IMAGE_PNG_INTERLACED      GFXOFF
//        #define GDISP_NEED_IMAGE_PNG_TRANSPARENCY    GFXON
//        #define GDISP_NEED_IMAGE_PNG_BACKGROUND      GFXON
//        #define GDISP_NEED_IMAGE_PNG_ALPHACLIFF      32
//        #define GDISP_NEED_IMAGE_PNG_PALETTE_124     GFXON
//        #define GDISP_NEED_IMAGE_PNG_PALETTE_8       GFXON
//        #define GDISP_NEED_IMAGE_PNG_GRAYSCALE_124   GFXON
//        #define GDISP_NEED_IMAGE_PNG_GRAYSCALE_8     GFXON
//        #define GDISP_NEED_IMAGE_PNG_GRAYSCALE_16    GFXON
//        #define GDISP_NEED_IMAGE_PNG_GRAYALPHA_8     GFXON
//        #define GDISP_NEED_IMAGE_PNG_GRAYALPHA_16    GFXON
//        #define GDISP_NEED_IMAGE_PNG_RGB_8           GFXON
//        #define GDISP_NEED_IMAGE_PNG_RGB_16          GFXON
//        #define GDISP_NEED_IMAGE_PNG_RGBALPHA_8      GFXON
//        #define GDISP_NEED_IMAGE_PNG_RGBALPHA_16     GFXON
//        #define GDISP_IMAGE_PNG_BLIT_BUFFER_SIZE     32
//        #define GDISP_IMAGE_PNG_FILE_BUFFER_SIZE     8
//        #define GDISP_IMAGE_PNG_Z_BUFFER_SIZE        32768
//    #define GDISP_NEED_IMAGE_ACCOUNTING              GFXOFF

//#define GDISP_NEED_PIXMAP                            GFXOFF
//    #define GDISP_NEED_PIXMAP_IMAGE                  GFXOFF

//#define GDISP_DEFAULT_ORIENTATION                    gOrientationLandscape    // If not defined the native hardware orientation is used.
//#define GDISP_LINEBUF_SIZE                           128
//#define GDISP_STARTUP_COLOR                          GFX_BLACK
#define GDISP_NEED_STARTUP_LOGO GFXOFF

//#define GDISP_TOTAL_DISPLAYS                         1

//#define GDISP_DRIVER_LIST                            GDISPVMT_Win32, GDISPVMT_Win32
#ifdef GDISP_DRIVER_LIST
//        // For code and speed optimization define as GFXON or GFXOFF if all controllers have the same capability
#    define GDISP_HARDWARE_STREAM_WRITE GFXOFF
#    define GDISP_HARDWARE_STREAM_READ GFXOFF
#    define GDISP_HARDWARE_STREAM_POS GFXOFF
#    define GDISP_HARDWARE_DRAWPIXEL GFXON
#    define GDISP_HARDWARE_CLEARS GFXOFF
#    define GDISP_HARDWARE_FILLS GFXOFF
//#define GDISP_HARDWARE_BITFILLS              GFXOFF
#    define GDISP_HARDWARE_SCROLL GFXOFF
#    define GDISP_HARDWARE_PIXELREAD GFXON
#    define GDISP_HARDWARE_CONTROL GFXON
#    define GDISP_HARDWARE_QUERY GFXOFF
#    define GDISP_HARDWARE_CLIP GFXOFF

#    define GDISP_PIXELFORMAT GDISP_PIXELFORMAT_RGB888
#endif

#define GDISP_USE_GFXNET GFXOFF
//    #define GDISP_GFXNET_PORT                        13001
//    #define GDISP_GFXNET_CUSTOM_LWIP_STARTUP         GFXOFF
//    #define GDISP_DONT_WAIT_FOR_NET_DISPLAY          GFXOFF
//    #define GDISP_GFXNET_UNSAFE_SOCKETS              GFXOFF

///////////////////////////////////////////////////////////////////////////
// GWIN                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GWIN GFXOFF

//#define GWIN_NEED_WINDOWMANAGER                      GFXOFF
//    #define GWIN_REDRAW_IMMEDIATE                    GFXOFF
//    #define GWIN_REDRAW_SINGLEOP                     GFXOFF
//    #define GWIN_NEED_FLASHING                       GFXOFF
//        #define GWIN_FLASHING_PERIOD                 250

//#define GWIN_NEED_CONSOLE                            GFXOFF
//    #define GWIN_CONSOLE_USE_HISTORY                 GFXOFF
//        #define GWIN_CONSOLE_HISTORY_AVERAGING       GFXOFF
//        #define GWIN_CONSOLE_HISTORY_ATCREATE        GFXOFF
//    #define GWIN_CONSOLE_ESCSEQ                      GFXOFF
//    #define GWIN_CONSOLE_USE_BASESTREAM              GFXOFF
//    #define GWIN_CONSOLE_USE_FLOAT                   GFXOFF
//#define GWIN_NEED_GRAPH                              GFXOFF
//#define GWIN_NEED_GL3D                               GFXOFF

//#define GWIN_NEED_WIDGET                             GFXOFF
//#define GWIN_FOCUS_HIGHLIGHT_WIDTH                   1
//    #define GWIN_NEED_LABEL                          GFXOFF
//        #define GWIN_LABEL_ATTRIBUTE                 GFXOFF
//    #define GWIN_NEED_BUTTON                         GFXOFF
//        #define GWIN_BUTTON_LAZY_RELEASE             GFXOFF
//    #define GWIN_NEED_SLIDER                         GFXOFF
//        #define GWIN_SLIDER_NOSNAP                   GFXOFF
//        #define GWIN_SLIDER_DEAD_BAND                5
//        #define GWIN_SLIDER_TOGGLE_INC               20
//    #define GWIN_NEED_CHECKBOX                       GFXOFF
//    #define GWIN_NEED_IMAGE                          GFXOFF
//        #define GWIN_NEED_IMAGE_ANIMATION            GFXOFF
//    #define GWIN_NEED_RADIO                          GFXOFF
//    #define GWIN_NEED_LIST                           GFXOFF
//        #define GWIN_NEED_LIST_IMAGES                GFXOFF
//    #define GWIN_NEED_PROGRESSBAR                    GFXOFF
//        #define GWIN_PROGRESSBAR_AUTO                GFXOFF
//    #define GWIN_NEED_KEYBOARD                       GFXOFF
//        #define GWIN_KEYBOARD_DEFAULT_LAYOUT         VirtualKeyboard_English1
//        #define GWIN_NEED_KEYBOARD_ENGLISH1          GFXON
//    #define GWIN_NEED_TEXTEDIT                       GFXOFF
//    #define GWIN_FLAT_STYLING                        GFXOFF
//    #define GWIN_WIDGET_TAGS                         GFXOFF

//#define GWIN_NEED_CONTAINERS                         GFXOFF
//    #define GWIN_NEED_CONTAINER                      GFXOFF
//    #define GWIN_NEED_FRAME                          GFXOFF
//    #define GWIN_NEED_TABSET                         GFXOFF
//        #define GWIN_TABSET_TABHEIGHT                18

///////////////////////////////////////////////////////////////////////////
// GTRANS                                                                //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_GTRANS                               GFXOFF

///////////////////////////////////////////////////////////////////////////
// GEVENT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GEVENT GFXON

//#define GEVENT_ASSERT_NO_RESOURCE                    GFXOFF
//#define GEVENT_MAXIMUM_SIZE                          32
//#define GEVENT_MAX_SOURCE_LISTENERS                  32

///////////////////////////////////////////////////////////////////////////
// GTIMER                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GTIMER GFXOFF

//#define GTIMER_THREAD_PRIORITY                       gThreadpriorityHigh
//#define GTIMER_THREAD_WORKAREA_SIZE                  2048

///////////////////////////////////////////////////////////////////////////
// GQUEUE                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GQUEUE GFXOFF

//#define GQUEUE_NEED_ASYNC                            GFXOFF
//#define GQUEUE_NEED_GSYNC                            GFXOFF
//#define GQUEUE_NEED_FSYNC                            GFXOFF
//#define GQUEUE_NEED_BUFFERS                          GFXOFF

///////////////////////////////////////////////////////////////////////////
// GINPUT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GINPUT GFXOFF

//#define GINPUT_NEED_MOUSE                            GFXOFF
//    #define GINPUT_TOUCH_STARTRAW                    GFXOFF
//    #define GINPUT_TOUCH_NOTOUCH                     GFXOFF
//    #define GINPUT_TOUCH_NOCALIBRATE                 GFXOFF
//    #define GINPUT_TOUCH_NOCALIBRATE_GUI             GFXOFF
//    #define GINPUT_MOUSE_POLL_PERIOD                 25
//    #define GINPUT_MOUSE_CLICK_TIME                  300
//    #define GINPUT_TOUCH_CXTCLICK_TIME               700
//    #define GINPUT_TOUCH_USER_CALIBRATION_LOAD       GFXOFF
//    #define GINPUT_TOUCH_USER_CALIBRATION_SAVE       GFXOFF
//    #define GMOUSE_DRIVER_LIST                       GMOUSEVMT_Win32, GMOUSEVMT_Win32
//    #define GINPUT_TOUCH_CALIBRATION_FONT1           "* Double"
//    #define GINPUT_TOUCH_CALIBRATION_FONT2           "* Narrow"
//    #define GINPUT_TOUCH_CALIBRATION_TITLE           "Calibration"
//    #define GINPUT_TOUCH_CALIBRATION_ERROR           "Calibration Failed!"
//#define GINPUT_NEED_KEYBOARD                         GFXOFF
//    #define GINPUT_KEYBOARD_POLL_PERIOD              200
//    #define GKEYBOARD_DRIVER_LIST                    GKEYBOARDVMT_Win32, GKEYBOARDVMT_Win32
//    #define GKEYBOARD_LAYOUT_OFF                     GFXOFF
//        #define GKEYBOARD_LAYOUT_SCANCODE2_US        GFXOFF
//#define GINPUT_NEED_TOGGLE                           GFXOFF
//#define GINPUT_NEED_DIAL                             GFXOFF

///////////////////////////////////////////////////////////////////////////
// GFILE                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GFILE GFXOFF

//#define GFILE_NEED_PRINTG                            GFXOFF
//#define GFILE_NEED_SCANG                             GFXOFF
//#define GFILE_NEED_STRINGS                           GFXOFF
//#define GFILE_NEED_FILELISTS                         GFXOFF
//#define GFILE_NEED_STDIO                             GFXOFF
//#define GFILE_NEED_NOAUTOMOUNT                       GFXOFF
//#define GFILE_NEED_NOAUTOSYNC                        GFXOFF

//#define GFILE_NEED_MEMFS                             GFXOFF
//#define GFILE_NEED_ROMFS                             GFXOFF
//#define GFILE_NEED_RAMFS                             GFXOFF
//#define GFILE_NEED_FATFS                             GFXOFF
//#define GFILE_NEED_NATIVEFS                          GFXOFF
//#define GFILE_NEED_CHBIOSFS                          GFXOFF
//#define GFILE_NEED_USERFS                            GFXOFF

//#define GFILE_ALLOW_FLOATS                           GFXOFF
//#define GFILE_ALLOW_DEVICESPECIFIC                   GFXOFF
//#define GFILE_MAX_GFILES                             3

///////////////////////////////////////////////////////////////////////////
// GADC                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GADC GFXOFF
//    #define GADC_MAX_LOWSPEED_DEVICES                4

///////////////////////////////////////////////////////////////////////////
// GAUDIO                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GAUDIO GFXOFF
//    #define GAUDIO_NEED_PLAY                         GFXOFF
//    #define GAUDIO_NEED_RECORD                       GFXOFF

///////////////////////////////////////////////////////////////////////////
// GMISC                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GMISC GFXON

//#define GMISC_NEED_ARRAYOPS                          GFXOFF
//#define GMISC_NEED_FASTTRIG                          GFXOFF
//#define GMISC_NEED_FIXEDTRIG                         GFXOFF
//#define GMISC_NEED_INVSQRT                           GFXOFF
//    #define GMISC_INVSQRT_MIXED_ENDIAN               GFXOFF
//    #define GMISC_INVSQRT_REAL_SLOW                  GFXOFF
#define GMISC_NEED_MATRIXFLOAT2D GFXON
#define GMISC_NEED_MATRIXFIXED2D GFXOFF
//#define GMISC_NEED_HITTEST_POLY                      GFXOFF

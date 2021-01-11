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

#ifndef COMMON_GFXCONF_H
#define COMMON_GFXCONF_H

///////////////////////////////////////////////////////////////////////////
// GOS - One of these must be defined, preferably in your Makefile       //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_OS_CHIBIOS                           TRUE
//#define GFX_USE_OS_FREERTOS                          FALSE
//    #define GFX_FREERTOS_USE_TRACE                   FALSE
//#define GFX_USE_OS_WIN32                             FALSE
//#define GFX_USE_OS_LINUX                             FALSE
//#define GFX_USE_OS_OSX                               FALSE
//#define GFX_USE_OS_ECOS                              FALSE
//#define GFX_USE_OS_RAWRTOS                           FALSE
//#define GFX_USE_OS_ARDUINO                           FALSE
//#define GFX_USE_OS_KEIL                              FALSE
//#define GFX_USE_OS_CMSIS                             FALSE
//#define GFX_USE_OS_RAW32                             FALSE
//    #define INTERRUPTS_OFF()                         optional_code
//    #define INTERRUPTS_ON()                          optional_code
// These are not defined by default for some reason
#define GOS_NEED_X_THREADS FALSE
#define GOS_NEED_X_HEAP FALSE

// Options that (should where relevant) apply to all operating systems
#define GFX_NO_INLINE FALSE
//    #define GFX_COMPILER                             GFX_COMPILER_UNKNOWN
//    #define GFX_CPU                                  GFX_CPU_UNKNOWN
//    #define GFX_OS_HEAP_SIZE                         0
//    #define GFX_OS_NO_INIT                           FALSE
//    #define GFX_OS_INIT_NO_WARNING                   FALSE
//    #define GFX_OS_PRE_INIT_FUNCTION                 myHardwareInitRoutine
//    #define GFX_OS_EXTRA_INIT_FUNCTION               myOSInitRoutine
//    #define GFX_OS_EXTRA_DEINIT_FUNCTION             myOSDeInitRoutine

///////////////////////////////////////////////////////////////////////////
// GDISP                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GDISP TRUE

//#define GDISP_NEED_AUTOFLUSH                         FALSE
//#define GDISP_NEED_TIMERFLUSH                        FALSE
//#define GDISP_NEED_VALIDATION                        TRUE
//#define GDISP_NEED_CLIP                              TRUE
#define GDISP_NEED_CIRCLE TRUE
#define GDISP_NEED_ELLIPSE TRUE
#define GDISP_NEED_ARC TRUE
#define GDISP_NEED_ARCSECTORS TRUE
#define GDISP_NEED_CONVEX_POLYGON TRUE
//#define GDISP_NEED_SCROLL                            FALSE
#define GDISP_NEED_PIXELREAD TRUE
#define GDISP_NEED_CONTROL TRUE
//#define GDISP_NEED_QUERY                             FALSE
//#define GDISP_NEED_MULTITHREAD                       FALSE
//#define GDISP_NEED_STREAMING                         FALSE
#define GDISP_NEED_TEXT TRUE
//    #define GDISP_NEED_TEXT_WORDWRAP                 FALSE
//    #define GDISP_NEED_ANTIALIAS                     FALSE
//    #define GDISP_NEED_UTF8                          FALSE
#define GDISP_NEED_TEXT_KERNING TRUE
//    #define GDISP_INCLUDE_FONT_UI1                   FALSE
//    #define GDISP_INCLUDE_FONT_UI2                   FALSE		// The smallest preferred font.
//    #define GDISP_INCLUDE_FONT_LARGENUMBERS          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS10          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS12          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS16          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS20          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24          FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32          FALSE
#define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12 TRUE
//    #define GDISP_INCLUDE_FONT_FIXED_10X20           FALSE
//    #define GDISP_INCLUDE_FONT_FIXED_7X14            FALSE
#define GDISP_INCLUDE_FONT_FIXED_5X8 TRUE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS12_AA       FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS16_AA       FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS20_AA       FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24_AA       FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32_AA       FALSE
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12_AA   FALSE
//    #define GDISP_INCLUDE_USER_FONTS                 FALSE

//#define GDISP_NEED_IMAGE                             FALSE
//    #define GDISP_NEED_IMAGE_NATIVE                  FALSE
//    #define GDISP_NEED_IMAGE_GIF                     FALSE
//    #define GDISP_NEED_IMAGE_BMP                     FALSE
//        #define GDISP_NEED_IMAGE_BMP_1               FALSE
//        #define GDISP_NEED_IMAGE_BMP_4               FALSE
//        #define GDISP_NEED_IMAGE_BMP_4_RLE           FALSE
//        #define GDISP_NEED_IMAGE_BMP_8               FALSE
//        #define GDISP_NEED_IMAGE_BMP_8_RLE           FALSE
//        #define GDISP_NEED_IMAGE_BMP_16              FALSE
//        #define GDISP_NEED_IMAGE_BMP_24              FALSE
//        #define GDISP_NEED_IMAGE_BMP_32              FALSE
//    #define GDISP_NEED_IMAGE_JPG                     FALSE
//    #define GDISP_NEED_IMAGE_PNG                     FALSE
//    #define GDISP_NEED_IMAGE_ACCOUNTING              FALSE
#ifdef EMULATOR
#    define GDISP_NEED_PIXMAP TRUE
#endif
//    #define GDISP_NEED_PIXMAP_IMAGE                  FALSE

//#define GDISP_DEFAULT_ORIENTATION                    GDISP_ROTATE_LANDSCAPE    // If not defined the native hardware orientation is used.
//#define GDISP_LINEBUF_SIZE                           128
//#define GDISP_STARTUP_COLOR                          Black
#define GDISP_NEED_STARTUP_LOGO FALSE

//#define GDISP_TOTAL_DISPLAYS		                 2

#ifdef GDISP_DRIVER_LIST
// For code and speed optimization define as TRUE or FALSE if all controllers have the same capability
#    define GDISP_HARDWARE_STREAM_WRITE FALSE
#    define GDISP_HARDWARE_STREAM_READ FALSE
#    define GDISP_HARDWARE_STREAM_POS FALSE
#    define GDISP_HARDWARE_DRAWPIXEL TRUE
#    define GDISP_HARDWARE_CLEARS FALSE
#    define GDISP_HARDWARE_FILLS FALSE
//#define GDISP_HARDWARE_BITFILLS              FALSE
#    define GDISP_HARDWARE_SCROLL FALSE
#    define GDISP_HARDWARE_PIXELREAD TRUE
#    define GDISP_HARDWARE_CONTROL TRUE
#    define GDISP_HARDWARE_QUERY FALSE
#    define GDISP_HARDWARE_CLIP FALSE

#    define GDISP_PIXELFORMAT GDISP_PIXELFORMAT_RGB888
#endif

// The custom format is not defined for some reason, so define it as error
// so we don't get compiler warnings
#define GDISP_PIXELFORMAT_CUSTOM GDISP_PIXELFORMAT_ERROR

#define GDISP_USE_GFXNET FALSE
//    #define GDISP_GFXNET_PORT                        13001
//    #define GDISP_GFXNET_CUSTOM_LWIP_STARTUP         FALSE
//    #define GDISP_DONT_WAIT_FOR_NET_DISPLAY          FALSE
//    #define GDISP_GFXNET_UNSAFE_SOCKETS              FALSE

///////////////////////////////////////////////////////////////////////////
// GWIN                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GWIN FALSE

//#define GWIN_NEED_WINDOWMANAGER                      FALSE
//    #define GWIN_REDRAW_IMMEDIATE                    FALSE
//    #define GWIN_REDRAW_SINGLEOP                     FALSE
//    #define GWIN_NEED_FLASHING                       FALSE
//        #define GWIN_FLASHING_PERIOD                 250

//#define GWIN_NEED_CONSOLE                            FALSE
//    #define GWIN_CONSOLE_USE_HISTORY                 FALSE
//        #define GWIN_CONSOLE_HISTORY_AVERAGING       FALSE
//        #define GWIN_CONSOLE_HISTORY_ATCREATE        FALSE
//    #define GWIN_CONSOLE_ESCSEQ                      FALSE
//    #define GWIN_CONSOLE_USE_BASESTREAM              FALSE
//    #define GWIN_CONSOLE_USE_FLOAT                   FALSE
//#define GWIN_NEED_GRAPH                              FALSE
//#define GWIN_NEED_GL3D                               FALSE

//#define GWIN_NEED_WIDGET                             FALSE
//#define GWIN_FOCUS_HIGHLIGHT_WIDTH                   1
//    #define GWIN_NEED_LABEL                          FALSE
//        #define GWIN_LABEL_ATTRIBUTE                 FALSE
//    #define GWIN_NEED_BUTTON                         FALSE
//        #define GWIN_BUTTON_LAZY_RELEASE             FALSE
//    #define GWIN_NEED_SLIDER                         FALSE
//        #define GWIN_SLIDER_NOSNAP                   FALSE
//        #define GWIN_SLIDER_DEAD_BAND                5
//        #define GWIN_SLIDER_TOGGLE_INC               20
//    #define GWIN_NEED_CHECKBOX                       FALSE
//    #define GWIN_NEED_IMAGE                          FALSE
//        #define GWIN_NEED_IMAGE_ANIMATION            FALSE
//    #define GWIN_NEED_RADIO                          FALSE
//    #define GWIN_NEED_LIST                           FALSE
//        #define GWIN_NEED_LIST_IMAGES                FALSE
//    #define GWIN_NEED_PROGRESSBAR                    FALSE
//        #define GWIN_PROGRESSBAR_AUTO                FALSE
//    #define GWIN_NEED_KEYBOARD                       FALSE
//        #define GWIN_KEYBOARD_DEFAULT_LAYOUT         VirtualKeyboard_English1
//        #define GWIN_NEED_KEYBOARD_ENGLISH1          TRUE
//    #define GWIN_NEED_TEXTEDIT                       FALSE
//    #define GWIN_FLAT_STYLING                        FALSE
//    #define GWIN_WIDGET_TAGS                         FALSE

//#define GWIN_NEED_CONTAINERS                         FALSE
//    #define GWIN_NEED_CONTAINER                      FALSE
//    #define GWIN_NEED_FRAME                          FALSE
//    #define GWIN_NEED_TABSET                         FALSE
//        #define GWIN_TABSET_TABHEIGHT                18

///////////////////////////////////////////////////////////////////////////
// GEVENT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GEVENT TRUE

//#define GEVENT_ASSERT_NO_RESOURCE                    FALSE
//#define GEVENT_MAXIMUM_SIZE                          32
//#define GEVENT_MAX_SOURCE_LISTENERS                  32

///////////////////////////////////////////////////////////////////////////
// GTIMER                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GTIMER FALSE

//#define GTIMER_THREAD_PRIORITY                       HIGH_PRIORITY
//#define GTIMER_THREAD_WORKAREA_SIZE                  2048

///////////////////////////////////////////////////////////////////////////
// GQUEUE                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GQUEUE FALSE

//#define GQUEUE_NEED_ASYNC                            FALSE
//#define GQUEUE_NEED_GSYNC                            FALSE
//#define GQUEUE_NEED_FSYNC                            FALSE
//#define GQUEUE_NEED_BUFFERS                          FALSE

///////////////////////////////////////////////////////////////////////////
// GINPUT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GINPUT FALSE

//#define GINPUT_NEED_MOUSE                            FALSE
//    #define GINPUT_TOUCH_STARTRAW                    FALSE
//    #define GINPUT_TOUCH_NOTOUCH                     FALSE
//    #define GINPUT_TOUCH_NOCALIBRATE                 FALSE
//    #define GINPUT_TOUCH_NOCALIBRATE_GUI             FALSE
//    #define GINPUT_MOUSE_POLL_PERIOD                 25
//    #define GINPUT_MOUSE_CLICK_TIME                  300
//    #define GINPUT_TOUCH_CXTCLICK_TIME               700
//    #define GINPUT_TOUCH_USER_CALIBRATION_LOAD       FALSE
//    #define GINPUT_TOUCH_USER_CALIBRATION_SAVE       FALSE
//    #define GMOUSE_DRIVER_LIST                       GMOUSEVMT_Win32, GMOUSEVMT_Win32
//#define GINPUT_NEED_KEYBOARD                         FALSE
//    #define GINPUT_KEYBOARD_POLL_PERIOD              200
//    #define GKEYBOARD_DRIVER_LIST                    GKEYBOARDVMT_Win32, GKEYBOARDVMT_Win32
//    #define GKEYBOARD_LAYOUT_OFF                     FALSE
//        #define GKEYBOARD_LAYOUT_SCANCODE2_US        FALSE
//#define GINPUT_NEED_TOGGLE                           FALSE
//#define GINPUT_NEED_DIAL                             FALSE

///////////////////////////////////////////////////////////////////////////
// GFILE                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GFILE FALSE

//#define GFILE_NEED_PRINTG                            FALSE
//#define GFILE_NEED_SCANG                             FALSE
//#define GFILE_NEED_STRINGS                           FALSE
//#define GFILE_NEED_FILELISTS                         FALSE
//#define GFILE_NEED_STDIO                             FALSE
//#define GFILE_NEED_NOAUTOMOUNT                       FALSE
//#define GFILE_NEED_NOAUTOSYNC                        FALSE

//#define GFILE_NEED_MEMFS                             FALSE
//#define GFILE_NEED_ROMFS                             FALSE
//#define GFILE_NEED_RAMFS                             FALSE
//#define GFILE_NEED_FATFS                             FALSE
//#define GFILE_NEED_NATIVEFS                          FALSE
//#define GFILE_NEED_CHBIOSFS                          FALSE

//#define GFILE_ALLOW_FLOATS                           FALSE
//#define GFILE_ALLOW_DEVICESPECIFIC                   FALSE
//#define GFILE_MAX_GFILES                             3

///////////////////////////////////////////////////////////////////////////
// GADC                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GADC FALSE

//#define GADC_MAX_LOWSPEED_DEVICES                    4

///////////////////////////////////////////////////////////////////////////
// GAUDIO                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GAUDIO FALSE
// There seems to be a bug in the ugfx code, the wrong define is used
// So define it in order to avoid warnings
#define GFX_USE_GAUDIN GFX_USE_GAUDIO
//    #define GAUDIO_NEED_PLAY                         FALSE
//    #define GAUDIO_NEED_RECORD                       FALSE

///////////////////////////////////////////////////////////////////////////
// GMISC                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GMISC TRUE

//#define GMISC_NEED_ARRAYOPS                          FALSE
//#define GMISC_NEED_FASTTRIG                          FALSE
//#define GMISC_NEED_FIXEDTRIG                         FALSE
//#define GMISC_NEED_INVSQRT                           FALSE
//    #define GMISC_INVSQRT_MIXED_ENDIAN               FALSE
//    #define GMISC_INVSQRT_REAL_SLOW                  FALSE
#define GMISC_NEED_MATRIXFLOAT2D TRUE
#define GMISC_NEED_MATRIXFIXED2D FALSE

#endif /* COMMON_GFXCONF_H */

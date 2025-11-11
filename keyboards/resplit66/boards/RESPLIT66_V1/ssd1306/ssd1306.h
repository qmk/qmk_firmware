#ifndef SSD1306_H
#define SSD1306_H

#include "ch.h"
#include "hal.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

enum ssd1306_cmds {

    /* Fundamental Command */
    SetContrastControl = 0x81,
    DisableEntireDisplayOn = 0xA4,
    EnableEntireDisplayOn = 0xA5,
    SetNormalDisplay = 0xA6,
    SetInvertDisplay = 0xA7,
    SetDisplayOff = 0xAE,
    SetDisplayOn = 0xAF,

    /* Charge Pump Command */
    ChargePumpSetting = 0x8D,

    /* Timing & Driving Scheme Setting Command */
    SetOscFreqAndClkDiv = 0xD5,
    SetPreChargePeriod = 0xD9,
    SetVcomhLevel = 0xDB,

    /* Addressing Setting Command */
    SetMemoryAddressMode = 0x20,
    SetColumnAddress = 0x21,
    SetPageAddress = 0x22,
    // SetLowColumn = 0x00, /* 0x00 - 0x0F */
    // SetHighColumn = 0x10, /* 0x10 - 0x1F */
    // SetPageStartAddress = 0xB0, /* 0xB0 - 0xB7 */

    /* Hardware Configuration Command */
    SetDisplayStartLine = 0x40, /* 0x40 - 0x7F */
    SetSegmentRemapNormal = 0xA0,
    SetSegmentRemapReverse = 0xA1,
    SetMultiplexRatio = 0xA8,
    SetComScanOrderNormal = 0xC0,
    SetComScanOrderReverse = 0xC8,
    SetDisplayOffset = 0xD3,
    SetComPins = 0xDA,

    /* Scrolling Command */
    RightHorizontalScroll = 0x26,
    LeftHorizontalScroll = 0x27,
    VerticalAndRightHorizontalScroll = 0x29,
    VerticalAndLeftHorizontalScroll = 0x2A,
    DeactivateScroll = 0x2E,
    ActivateScroll = 0x2F,
    SetVerticalScrollArea = 0xA3,

    /* Other Command */
    NoOperation = 0xE3,
};

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#ifndef SSD1306_ADDRESS
/* for your reference (0x3C << 1) == 0x78 , (0x3D << 1) == 0x7A . */
#define SSD1306_ADDRESS 0x3C
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Structure representing a SSD1306 driver.
 */
typedef struct SSD1306Driver SSD1306Driver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    SSD1306_UNINIT = 0,               /**< Not initialized.                   */
    SSD1306_STOP = 1,                 /**< Stopped.                           */
    SSD1306_READY = 2,                /**< Ready.                             */
} ssd1306_state_t;

/**
 * @brief   SSD1306 configuration structure.
 */
typedef struct {
    /**
     * @brief I2C driver associated to this SSD1306 OLED screen.
     */
    I2CDriver *i2cd;
    /**
     * @brief I2C configuration to use.
     */
    const I2CConfig *i2ccfg;
    /**
     * @brief I2C address of screen.
     */
    uint8_t i2caddr;
    /**
     * @brief Width of screen.
     */
    uint8_t width;
    /**
     * @brief Height of screen.
     */
    uint8_t height;
    /**
     * @brief True if screen is rotated 180°.
     */
    bool rotate180;
    /**
     * @brief Optional framebuffer.
     */
    void *buf;
} SSD1306Config;

typedef struct SSD1306Driver {
    /* Current configuration data.*/
    const SSD1306Config        *config;
    /* Driver state */
    ssd1306_state_t             state;
	/* Number of pages */
	uint8_t                     pages;
	/* Framebuffer length */
	size_t                      len;
    /* Holds all pixels */
    uint8_t                    *buf;
} SSD1306Driver;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/
#define SSD1306_PREAMBLE_LENGTH 1
#define ssd1306GetFramebuffer(ssd1306)          \
  (&((ssd1306)->buf[SSD1306_PREAMBLE_LENGTH]))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void ssd1306ObjectInit(SSD1306Driver *devp);
void ssd1306Start(SSD1306Driver *devp, const SSD1306Config *config);
void ssd1306Stop(SSD1306Driver *devp);

bool ssd1306DisplayOn(SSD1306Driver *ssd1306);
bool ssd1306DisplayOff(SSD1306Driver *ssd1306);

bool ssd1306Show(SSD1306Driver *ssd1306);

bool ssd1306StartScrollRight(SSD1306Driver *ssd1306, uint8_t start, uint8_t stop);
bool ssd1306StartScrollLeft(SSD1306Driver *ssd1306, uint8_t start, uint8_t stop);
bool ssd1306StopScroll(SSD1306Driver *ssd1306);
bool ssd1306Invert(SSD1306Driver *ssd1306, bool i);
bool ssd1306Dim(SSD1306Driver *ssd1306, uint8_t contrast);

#ifdef __cplusplus
}
#endif

#endif

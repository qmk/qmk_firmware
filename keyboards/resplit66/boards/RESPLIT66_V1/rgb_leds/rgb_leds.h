#ifndef _RGB_LEDS_H_
#define _RGB_LEDS_H_

#include "ch.h"
#include "hal.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !HAL_USE_SPI
#error "RGB_LEDS requires HAL_USE_SPI"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Structure representing a RGBLEDS driver.
 */
typedef struct RGBLEDSDriver RGBLEDSDriver;

/**
 * @brief   Type of RGB leds used.
 */
typedef enum {
    WS2801_RGB,
    WS2801_GRB,
    APA102_ABGR,
    SK6812_GRB,
} rgb_type_t;

/**
 * @brief   Frequency divider to used Type of RGB leds used.
 *
 * For use in SPIConfig structure.
 */
typedef enum {
    WS2801_CLOCK = SPI_CR1_BR_0 | SPI_CR1_BR_2, /* fpclk / 64 */
    APA102_CLOCK = SPI_CR1_BR_2,                /* fpclk / 32 */
    SK6812_CLOCK = SPI_CR1_BR_2,                /* fpclk / 32 */
} rgb_clock_t;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  RGBLEDS_UNINIT = 0,               /**< Not initialized.                   */
  RGBLEDS_STOP = 1,                 /**< Stopped.                           */
  RGBLEDS_READY = 2,                /**< Ready.                             */
} rgbleds_state_t;

/**
 * @brief   RGB_LEDS configuration structure.
 */
typedef struct {
  /**
   * @brief SPI driver associated to this RGB leds string.
   */
  SPIDriver                 *spip;
  /**
   * @brief SPI configuration associated to this RGB leds string.
   */
  const SPIConfig           *spicfg;
  /**
   * @brief RGB leds type.
   */
  rgb_type_t                 type;
  /**
   * @brief Power pin to on/off the RGB leds.
   */
  ioline_t                   power;
  /**
   * @brief Data pin in GPIO mode.
   */
  ioline_t                   data;
  /**
   * @brief Clock pin in GPIO mode, if required.
   */
  ioline_t                   clock;
  /**
   * @brief Width of leds matrix.
   */
  uint16_t                   width;
  /**
   * @brief Height of leds matrix.
   */
  uint16_t                   height;
} RGBLEDSConfig;

struct RGBLEDSDriver {
  /* Current configuration data.*/
  const RGBLEDSConfig       *config;
  /* Driver state */
  rgbleds_state_t            state;
  /* Holds color values for each LED (3 or 4 bytes each). */
  uint8_t                   *pixels;
  /* Number of RGB leds. */
  uint16_t                   count;
  /* Bytes per leds, according their type. */
  uint8_t                    bpl;
  /* Header size, according their type. */
  uint8_t                    hsz;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Return number of leds.
 *
 * @param[in] devp      pointer to @p RGBLEDSDriver.
 *
 * @return              The number of pixels.
 */
#define rgbledsNumPixels(devp) ((devp)->count)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void rgbledsObjectInit(RGBLEDSDriver *devp);
  void rgbledsStart(RGBLEDSDriver *devp, const RGBLEDSConfig *config);
  void rgbledsStop(RGBLEDSDriver *devp);

  void rgbledsOn(RGBLEDSDriver *devp);
  void rgbledsOff(RGBLEDSDriver *devp);
  void rgbledsShow(RGBLEDSDriver *devp);
  void rgbledsClear(RGBLEDSDriver *devp);

  void rgbledsSetPixelColor(RGBLEDSDriver *devp, uint16_t n, uint32_t c);
  void rgbledsSetPixelRGB(RGBLEDSDriver *devp, uint16_t n, uint8_t r, uint8_t g, uint8_t b);
  void rgbledsSetPixelXYColor(RGBLEDSDriver *devp, uint16_t x, uint16_t y, uint32_t c);
  void rgbledsSetPixelXYRGB(RGBLEDSDriver *devp, uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
  uint32_t rgbledsGetPixelColor(RGBLEDSDriver *devp, uint16_t n);
#ifdef __cplusplus
}
#endif

#endif /* __RGB_LEDS__ */

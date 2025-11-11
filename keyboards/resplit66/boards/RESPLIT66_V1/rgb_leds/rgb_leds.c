/**
 * @file    rgb_leds.c
 * @brief   RGB leds strings interface module code.
 *
 * @addtogroup RGBLEDS
 * @{
 */
#include "rgb_leds.h"
#include <string.h>

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
#ifndef SHARED_SPI_OR_DMA
#define SHARED_SPI_OR_DMA 1
#endif

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/* Lookup table for SK6812 bits
 * In big-endian (MSB first) */
static const uint16_t SK6812[16] = {
  0x8888,
  0x8c88,
  0xc888,
  0xcc88,
  0x888c,
  0x8c8c,
  0xc88c,
  0xcc8c,
  0x88c8,
  0x8cc8,
  0xc8c8,
  0xccc8,
  0x88cc,
  0x8ccc,
  0xc8cc,
  0xcccc
};

/* Inverse conversion mask. */
#define SK6812_MASK (0b0100010001000100)
/* Bit number:          1,  0,  3,  2
                        |   |   |   >>0
   Left shift           |   |   >>3
                        |   >>10
                        >>13
*/

/* Inverse conversion macro. */
#define fromSK6812(b) (uint32_t)((((b) & 0x4000) >> 13) | \
                                 (((b) & 0x0400) >> 10) | \
                                 (((b) & 0x0040) >> 3) |  \
                                  ((b) & 0x0004))

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Convert 24 bits color to 12 bytes SK6812 required representation
 *
 * @param[out] p       pointer to where to put SK6812 pixel representation
 * @param[in]  c       pixel color to convert
 */
static inline void colorToSK6812(uint8_t *p, uint32_t c)
{
  uint16_t *d = (uint16_t *)p;
  *d++ = SK6812[(c >> 12) & 15]; // Green
  *d++ = SK6812[(c >>  8) & 15]; // Green
  *d++ = SK6812[(c >> 20) & 15]; // Red
  *d++ = SK6812[(c >> 16) & 15]; // Red
  *d++ = SK6812[(c >>  4) & 15]; // Blue
  *d++ = SK6812[(c      ) & 15]; // Blue
}

static inline uint32_t colorFromSK6812(uint8_t *p)
{
  uint16_t *d = (uint16_t *)p;
  uint32_t c;
  c  = fromSK6812(*d) << 12; d++; // Green
  c |= fromSK6812(*d) <<  8; d++; // Green
  c |= fromSK6812(*d) << 20; d++; // Red
  c |= fromSK6812(*d) << 16; d++; // Red
  c |= fromSK6812(*d) <<  4; d++; // Blue
  c |= fromSK6812(*d);       d++; // Blue
  return c;
}

/**
 * @brief   Allocate pixels buffer, init to RGB 'off' state
 *
 * @param[in] devp     pointer to the @p RGBLEDSDriver object
 * @param[in] n        number of connected RGB leds
 */
static void rgbledsAlloc(RGBLEDSDriver *devp, uint16_t n)
{
  if (devp->pixels && devp->count == n)
    return; // Existing buffer has the correct size. Do nothing.
  if (devp->pixels)
    chHeapFree(devp->pixels); // Free existing data (if any)
  devp->pixels = (uint8_t *)chHeapAllocAligned(
    NULL, n * devp->bpl + devp->hsz * 2, sizeof(int));
  devp->count = devp->pixels ? n : 0;
  rgbledsClear(devp);
}

/**
 * @brief   Begin transaction
 *
 * @param[in] devp     pointer to the @p RGBLEDSDriver object
 */
static void rgbledsBegin(RGBLEDSDriver *devp)
{
  if (devp->config->spip) {
#if SHARED_SPI_OR_DMA
    spiAcquireBus(devp->config->spip);
    spiStart(devp->config->spip, devp->config->spicfg);
    chThdSleepMilliseconds(2);
#endif
  }
  else {
    palSetLineMode(devp->config->data, PAL_MODE_OUTPUT_PUSHPULL);
    if (devp->config->clock)
      palSetLineMode(devp->config->clock, PAL_MODE_OUTPUT_PUSHPULL);
  }
}

/**
 * @brief   End transaction
 *
 * @param[in] devp     pointer to the @p RGBLEDSDriver object
 */
static void rgbledsEnd(RGBLEDSDriver *devp)
{
  if (devp->config->spip) {
#if SHARED_SPI_OR_DMA
    spiStop(devp->config->spip);
    spiReleaseBus(devp->config->spip);
#endif
  }
  else {
    // Restore prior data and clock pins to inputs
    palSetLineMode(devp->config->data, PAL_MODE_INPUT);
    if (devp->config->clock)
      palSetLineMode(devp->config->clock, PAL_MODE_INPUT);
  }
}

/**
 * @brief   Send pixels buffer to SPI bus
 *
 * @param[in] devp     pointer to the @p RGBLEDSDriver object
 */
static void rgbledsSendSPI(RGBLEDSDriver *devp)
{
  SPIDriver *spip = devp->config->spip;
  size_t max = devp->count * devp->bpl;
  if (!max)
    return;
  max += devp->hsz * 2; // Add header/footer.
  spiSelect(spip);
  spiSend(spip, max, devp->pixels);
  spiUnselect(spip);
}

/**
 * @brief   Send pixels buffer using GPIO outputs
 *
 * @param[in] devp     pointer to the @p RGBLEDSDriver object
 */
static void rgbledsSendGPIO(RGBLEDSDriver *devp)
{
  size_t max = devp->count * devp->bpl;
  if (!max)
    return;
  max += devp->hsz * 2; // Add header/footer.
  for (unsigned i = 0; i < max; i++) {
    uint8_t v = devp->pixels[i];
    /* Send each bytes one by one using GPIO, MSB first. */
    for (uint8_t bit = 0x80; bit; bit >>= 1) {
      if(v & bit) palSetLine(devp->config->data);
      else        palClearLine(devp->config->data);
      if (devp->config->clock) {
        palSetLine(devp->config->clock);
        palClearLine(devp->config->clock);
      }
    }
  }
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p RGBLEDSDriver object
 *
 * @init
 */
void rgbledsObjectInit(RGBLEDSDriver *devp) {
  devp->config = NULL;
  devp->pixels = NULL;
  devp->state  = RGBLEDS_STOP;
}

/**
 * @brief   Configures and activates RGBLEDS Driver peripheral.
 *
 * @param[in] devp      pointer to the @p RGBLEDSDriver object
 * @param[in] config    pointer to the @p RGBLEDSConfig object
 *
 * This function don't change power status of LEDs string.
 * The rgbledsOn() must be called manually when required.
 *
 * @api
 */
void rgbledsStart(RGBLEDSDriver *devp, const RGBLEDSConfig *config)
{
  osalDbgCheck((devp != NULL) && (config != NULL));
  osalDbgAssert(devp->state == RGBLEDS_STOP,
                "rgbledsStart(), invalid state");

  devp->config = config;
  switch (config->type) {
  case APA102_ABGR:
    devp->bpl = 4;
    devp->hsz = 4;
    break;
  case SK6812_GRB:
    devp->bpl = 3 * 4;
    devp->hsz = 0;
    break;
  default:
    devp->bpl = 3;
    devp->hsz = 0;
    break;
  }
  if (config->spip) {
    /* SPI mode, configure it once if not shared. */
#if !SHARED_SPI_OR_DMA
    spiStart(config->spip, config->spicfg);
#endif
  }
  /* Allocate pixels buffer */
  rgbledsAlloc(devp, config->width * config->height);
  if (devp->pixels && devp->count)
    devp->state = RGBLEDS_READY;
}

/**
 * @brief   Deactivates the RGBLEDS Driver peripheral.
 *
 * @param[in] devp       pointer to the @p RGBLEDSDriver object
 *
 * This function also calls rgbledsOff(), so all leds light off.
 *
 * @api
 */
void rgbledsStop(RGBLEDSDriver *devp)
{
  osalDbgCheck(devp != NULL);

  osalDbgAssert((devp->state == RGBLEDS_STOP) || (devp->state == RGBLEDS_READY),
                "rgbledsStop(), invalid state");

  if (devp->state == RGBLEDS_READY) {
    rgbledsOff(devp);
    if (devp->pixels) {
      chHeapFree(devp->pixels);
      devp->pixels = NULL;
    }
    if (devp->config->spip) {
#if !SHARED_SPI_OR_DMA
      spiStop(devp->config->spip);
#endif
    }
  }
  devp->state = RGBLEDS_STOP;
}

/**
 * @brief   Power-on the RGBLEDS Driver peripheral.
 *
 * @param[in] devp       pointer to the @p RGBLEDSDriver object
 *
 * @api
 */
void rgbledsOn(RGBLEDSDriver *devp)
{
	if (devp->config && devp->config->power) {
		palSetLine(devp->config->power);
		chThdSleepMilliseconds(5);
	}
}

/**
 * @brief   Power-on the RGBLEDS Driver peripheral.
 *
 * @param[in] devp       pointer to the @p RGBLEDSDriver object
 *
 * @api
 */
void rgbledsOff(RGBLEDSDriver *devp)
{
	if (devp->config && devp->config->power) {
        palClearLine(devp->config->power);
    }
}

/**
 * @brief   Clear all RGb leds.
 *
 * @param[in] devp       pointer to the @p RGBLEDSDriver object
 *
 * @api
 */
void rgbledsClear(RGBLEDSDriver *devp)
{
	int val = 0;
  if (!devp->pixels || !devp->count)
    return;
  if (devp->config->type == SK6812_GRB)
    val = (int)0x88888888ul;
  memset(devp->pixels, val, devp->count * devp->bpl + devp->hsz * 2);
  if (devp->config->type == APA102_ABGR) {
    uint8_t *p = devp->pixels;
    /* Header already set by previous memset(). */
    p += devp->hsz;
    // Each pixels start with 3 bits 1's.
    for (unsigned i = 0; i < devp->count; i++)
      p[i * devp->bpl] = 0b11100000;
    p += devp->count * devp->bpl;
    // Set footer to all bits 1's.
    for (unsigned i = 0; i < devp->hsz; i++)
      p[i] = 255;
  }
}

/**
 * @brief   Display all RGB leds according pixels values.
 *
 * @param[in] devp       pointer to the @p RGBLEDSDriver object
 *
 * @api
 */
void rgbledsShow(RGBLEDSDriver *devp)
{
  osalDbgCheck(devp != NULL);
  osalDbgAssert(devp->state == RGBLEDS_READY,
                "rgbledsShow(), invalid state");
  rgbledsBegin(devp);
  if (devp->config->spip)
    rgbledsSendSPI(devp);
  else
    rgbledsSendGPIO(devp);
  if (devp->config->type != APA102_ABGR)
    // Data is latched by holding clock pin low for 1 millisecond.
    chThdSleepMilliseconds(1);
  rgbledsEnd(devp);
}

// Set pixel color from 'packed' 32-bit (A)RGB value:
void rgbledsSetPixelColor(RGBLEDSDriver *devp, uint16_t n, uint32_t c)
{
  uint8_t *p = devp->pixels + devp->hsz;
  if (n < devp->count) {
    p += n * devp->bpl;
    // To keep the show() loop as simple & fast as possible, the
    // internal color representation is native to different pixel
    // types.  For compatibility with existing code, 'packed' RGB
    // values passed in or out are always 0xAARRGGBB order.
    switch (devp->config->type) {
    case APA102_ABGR:
      *p++ = 0b11100000 | ((c >> 24) & 31); // Alpha channel/brightness
      *p++ = c;       // Blue
      *p++ = c >>  8; // Green
      *p++ = c >> 16; // Red
      break;
    case WS2801_RGB:
      *p++ = c >> 16; // Red
      *p++ = c >>  8; // Green
      *p++ = c;       // Blue
      break;
    case WS2801_GRB:
      *p++ = c >>  8; // Green
      *p++ = c >> 16; // Red
      *p++ = c;       // Blue
      break;
    case SK6812_GRB:
      colorToSK6812(p, c);
      break;
    }
  }
}

// Set pixel color from separate 8-bit R, G, B components:
void rgbledsSetPixelRGB(RGBLEDSDriver *devp, uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
  if (n < devp->count) { // Arrays are 0-indexed, thus NOT '<='
    uint32_t c = (uint32_t)b | (uint32_t)g << 8 | (uint32_t)r << 16;
    if (devp->config->type == APA102_ABGR)
      c |= (uint32_t)7 << 24; /* Default brightness */
    rgbledsSetPixelColor(devp, n, c);
  }
}

static inline uint16_t rgbledsPixelXYOffset(RGBLEDSDriver *devp, uint16_t x, uint16_t y)
{
    bool evenRow = ((y % 2) == 0);
    // calculate x offset first
    uint16_t offset = x % devp->config->width;
    if (!evenRow)
        offset = (devp->config->width - 1) - offset;
    // add y offset
    offset += y * devp->config->width;
    return offset;
}

// Set pixel color from 'packed' 32-bit RGB value using x,y coordinate system:
void rgbledsSetPixelXYColor(RGBLEDSDriver *devp, uint16_t x, uint16_t y, uint32_t c)
{
    uint16_t offset = rgbledsPixelXYOffset(devp, x, y);
    rgbledsSetPixelColor(devp, offset, c);
}

// Set pixel color from separate 8-bit R, G, B components using x,y coordinate system:
void rgbledsSetPixelXYRGB(RGBLEDSDriver *devp, uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t offset = rgbledsPixelXYOffset(devp, x, y);
    rgbledsSetPixelRGB(devp, offset, r, g, b);
}

// Query color from previously-set pixel (returns packed 32-bit (A)RGB value)
uint32_t rgbledsGetPixelColor(RGBLEDSDriver *devp, uint16_t n)
{
  uint8_t *p = devp->pixels + devp->hsz;
  uint32_t val = 0;
  if (n < devp->count) {
    p += n * devp->bpl;
    // To keep the show() loop as simple & fast as possible, the
    // internal color representation is native to different pixel
    // types.  For compatibility with existing code, 'packed' RGB
    // values passed in or out are always 0xRRGGBB order.
    switch (devp->config->type) {
    case APA102_ABGR:
      return (((uint32_t)p[0] & 31) << 24) | ((uint32_t)p[3] << 16) | ((uint16_t)p[2] <<  8) | p[1];
    case WS2801_RGB:
      return ((uint32_t)p[0] << 16) | ((uint16_t)p[1] <<  8) | p[2];
    case WS2801_GRB:
      return ((uint32_t)p[1] << 16) | ((uint16_t)p[0] <<  8) | p[2];
    case SK6812_GRB:
      val = colorFromSK6812(p);
      break;
    }
  }
  return val;
}

/** @} */

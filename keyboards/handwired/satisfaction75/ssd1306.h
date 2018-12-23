
#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "hal.h"

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !HAL_USE_I2C
#error "SSD1306 requires HAL_USE_I2C"
#endif

#define SSD1306_WIDTH					128
#define SSD1306_HEIGHT					32
#define SSD1306_WIDTH_FIXED				(SSD1306_WIDTH + 1)


/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

typedef enum {
	SSD1306_COLOR_BLACK = 0x00,
	SSD1306_COLOR_WHITE = 0x01
} ssd1306_color_t;

typedef struct {
	uint8_t fw;
	uint8_t fh;
	const uint16_t *dt;
} ssd1306_font_t;

typedef enum {
	SSD1306_SAD_0X78 = (0x78 >> 1),
	SSD1306_SAD_0X7A = (0x7A >> 1)
} ssd1306_sad_t;

typedef enum {
	SSD1306_UNINIT = 0,
	SSD1306_STOP = 1,
	SSD1306_READY = 2,
} ssd1306_state_t;

typedef struct {
	I2CDriver *i2cp;
	const I2CConfig *i2ccfg;

	ssd1306_sad_t sad;
} SSD1306Config;

#define _ssd1306_methods \
	void (*updateScreen)(void *ip); \
	void (*toggleInvert)(void *ip); \
	void (*fillScreen)(void *ip, ssd1306_color_t color); \
	void (*drawPixel)(void *ip, uint8_t x, uint8_t y, ssd1306_color_t color); \
	void (*gotoXy)(void *ip, uint8_t x, uint8_t y); \
	char (*putc)(void *ip, char ch, const ssd1306_font_t *font, ssd1306_color_t color); \
	char (*puts)(void *ip, char *str, const ssd1306_font_t *font, ssd1306_color_t color); \
	void (*setDisplay)(void *ip, uint8_t on);

struct SSD1306VMT {
	_ssd1306_methods
};

#define _ssd1306_data \
	ssd1306_state_t state; \
	const SSD1306Config *config; \

typedef struct SSD1306Driver {
	const struct SSD1306VMT *vmt;
	_ssd1306_data;

	uint8_t x;
	uint8_t y;
	uint8_t inv;
	uint8_t fb[SSD1306_WIDTH_FIXED * SSD1306_HEIGHT / 8];
} SSD1306Driver;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

#define ssd1306UpdateScreen(ip) \
	(ip)->vmt->updateScreen(ip)

#define ssd1306ToggleInvert(ip) \
	(ip)->vmt->toggleInvert(ip)

#define ssd1306FillScreen(ip, color) \
	(ip)->vmt->fillScreen(ip, color)

#define ssd1306DrawPixel(ip, x, y, color) \
	(ip)->vmt->drawPixel(ip, x, y, color)

#define ssd1306GotoXy(ip, x, y) \
	(ip)->vmt->gotoXy(ip, x, y)

#define ssd1306Putc(ip, ch, font, color) \
	(ip)->vmt->putc(ip, ch, font, color)

#define ssd1306Puts(ip, str, font, color) \
	(ip)->vmt->puts(ip, str, font, color)

#define ssd1306SetDisplay(ip, on) \
	(ip)->vmt->setDisplay(ip, on)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

extern const ssd1306_font_t ssd1306_font_7x10;

void ssd1306ObjectInit(SSD1306Driver *devp);
void ssd1306Start(SSD1306Driver *devp, const SSD1306Config *config);
void ssd1306Stop(SSD1306Driver *devp);

#ifdef __cplusplus
}
#endif

#endif /* __SSD1306_H__ */

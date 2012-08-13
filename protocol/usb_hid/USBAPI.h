/*
 * Override original arduino USBAPI.h.
 */
#include <stdint.h>
#include "Stream.h"


class NullSerial : public Stream
{
public:
	void begin(uint16_t baud_count);
	void end(void);

	virtual int available(void);
	virtual void accept(void);
	virtual int peek(void);
	virtual int read(void);
	virtual void flush(void);
	virtual size_t write(uint8_t);
	operator bool();
};
extern NullSerial Serial;

#include "gfx.h"
#if GFX_COMPAT_V2 && GFX_COMPAT_OLDCOLORS
	#undef Red
	#undef Green
	#undef Blue
#endif
#include "stm32f7_i2c.h"

/*
 * The CR2 register needs atomic access. Hence always use this function to setup a transfer configuration.
 */
static void _i2cConfigTransfer(I2C_TypeDef* i2c, gU16 slaveAddr, gU8 numBytes, gU32 mode, gU32 request)
{
	gU32 tmpreg = 0;

	// Get the current CR2 register value
	tmpreg = i2c->CR2;

	// Clear tmpreg specific bits
	tmpreg &= (gU32) ~((gU32) (I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP));

	// update tmpreg
	tmpreg |= (gU32) (((gU32) slaveAddr & I2C_CR2_SADD) | (((gU32) numBytes << 16) & I2C_CR2_NBYTES) | (gU32) mode | (gU32) request);

	// Update the actual CR2 contents
	i2c->CR2 = tmpreg;
}

/*
 * According to the STM32Cube HAL the CR2 register needs to be reset after each transaction.
 */
static void _i2cResetCr2(I2C_TypeDef* i2c)
{
	i2c->CR2 &= (gU32) ~((gU32) (I2C_CR2_SADD | I2C_CR2_HEAD10R | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_RD_WRN));
}

gBool i2cInit(I2C_TypeDef* i2c)
{
	// Enable I2Cx peripheral clock.
	// Select APB1 as clock source
	if (i2c == I2C1) {
		RCC->DCKCFGR2 &= ~RCC_DCKCFGR2_I2C1SEL;
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	} else if (i2c == I2C2) {
		RCC->DCKCFGR2 &= ~RCC_DCKCFGR2_I2C2SEL;
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	} else if (i2c == I2C3) {
		RCC->DCKCFGR2 &= ~RCC_DCKCFGR2_I2C3SEL;
		RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
	} else if (i2c == I2C4) {
		RCC->DCKCFGR2 &= ~RCC_DCKCFGR2_I2C4SEL;
		RCC->APB1ENR |= RCC_APB1ENR_I2C4EN;
	} else {
		return gFalse;
	}

	// Disable the I2Cx peripheral
	i2c->CR1 &= ~I2C_CR1_PE;
	while (i2c->CR1 & I2C_CR1_PE);

	// Set timings. Asuming I2CCLK is 50 MHz (APB1 clock source)
	i2c->TIMINGR = 0x40912732;		// Discovery BSP code from ST examples

	// Use 7-bit addresses
	i2c->CR2 &=~ I2C_CR2_ADD10;

	// Enable auto-end mode
	i2c->CR2 |= I2C_CR2_AUTOEND;

	// Disable the analog filter
	i2c->CR1 |= I2C_CR1_ANFOFF;

	// Disable NOSTRETCH
	i2c->CR1 |= I2C_CR1_NOSTRETCH;

	// Enable the I2Cx peripheral
	i2c->CR1 |= I2C_CR1_PE;

	return gTrue;
}

void i2cSend(I2C_TypeDef* i2c, gU8 slaveAddr, gU8* data, gU16 length)
{
	// We are currently not able to send more than 255 bytes at once
	if (length > 255) {
		return;
	}

	// Setup the configuration
	_i2cConfigTransfer(i2c, slaveAddr, length, (!I2C_CR2_RD_WRN) | I2C_CR2_AUTOEND, I2C_CR2_START);

	// Transmit the whole buffer
	while (length > 0) {
		while (!(i2c->ISR & I2C_ISR_TXIS));
		i2c->TXDR = *data++;
		length--;
	}

	// Wait until the transfer is complete
	while (!(i2c->ISR & I2C_ISR_TXE));

	// Wait until the stop condition was automagically sent
	while (!(i2c->ISR & I2C_ISR_STOPF));

	// Reset the STOP bit
	i2c->ISR &= ~I2C_ISR_STOPF;

	// Reset the CR2 register
	_i2cResetCr2(i2c);
}

void i2cSendByte(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 data)
{
	i2cSend(i2c, slaveAddr, &data, 1);
}

void i2cWriteReg(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 regAddr, gU8 value)
{
	gU8 txbuf[2];
	txbuf[0] = regAddr;
	txbuf[1] = value;

	i2cSend(i2c, slaveAddr, txbuf, 2);
}

void i2cRead(I2C_TypeDef* i2c, gU8 slaveAddr, gU8* data, gU16 length)
{
	int		i;

	// We are currently not able to read more than 255 bytes at once
	if (length > 255) {
		return;
	}

	// Setup the configuration
	_i2cConfigTransfer(i2c, slaveAddr, length, I2C_CR2_RD_WRN | I2C_CR2_AUTOEND, I2C_CR2_START);

	// Transmit the whole buffer
	for (i = 0; i < length; i++) {
		while (!(i2c->ISR & I2C_ISR_RXNE));
		data[i] = i2c->RXDR;
	}

	// Wait until the stop condition was automagically sent
	while (!(i2c->ISR & I2C_ISR_STOPF));

	// Reset the STOP bit
	i2c->ISR &= ~I2C_ISR_STOPF;

	// Reset the CR2 register
	_i2cResetCr2(i2c);
}

gU8 i2cReadByte(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 regAddr)
{
	gU8 ret = 0xAA;

	i2cSend(i2c, slaveAddr, &regAddr, 1);
	i2cRead(i2c, slaveAddr, &ret, 1);

	return ret;
}

gU16 i2cReadWord(I2C_TypeDef* i2c, gU8 slaveAddr, gU8 regAddr)
{
	gU8 ret[2] = { 0xAA, 0xAA };

	i2cSend(i2c, slaveAddr, &regAddr, 1);
	i2cRead(i2c, slaveAddr, ret, 2);

	return (gU16)((ret[0] << 8) | (ret[1] & 0x00FF));
}

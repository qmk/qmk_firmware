#include "test_env.h"
#include "mbed.h"
#include "spifi_rom_api.h"

extern const unsigned char splash_image1[]; extern int splash_image1_sz;
extern const unsigned char splash_image2[]; extern int splash_image2_sz;
extern const unsigned char splash_image3[]; extern int splash_image3_sz;
extern const unsigned char splash_image4[]; extern int splash_image4_sz;
extern const unsigned char splash_image5[]; extern int splash_image5_sz;
extern const unsigned char splash_image6[]; extern int splash_image6_sz;
extern const unsigned char splash_image7[]; extern int splash_image7_sz;
extern const unsigned char splash_image8[]; extern int splash_image8_sz;
extern const unsigned char splash_image9[]; extern int splash_image9_sz;
extern const unsigned char splash_image10[]; extern int splash_image10_sz;
extern const unsigned char splash_image11[]; extern int splash_image11_sz;
extern const unsigned char splash_image12[]; extern int splash_image12_sz;
extern const unsigned char splash_image13[]; extern int splash_image13_sz;
extern const unsigned char splash_image14[]; extern int splash_image14_sz;
extern const unsigned char splash_image15[]; extern int splash_image15_sz;

/*
 * The SPIFI_ROM_PTR (0x1FFF1FF8) points to an area where the pointers to
 * different drivers in ROM are stored.
 */
typedef struct {
   /*const*/ unsigned p_usbd;     // USBROMD
   /*const*/ unsigned p_clib;
   /*const*/ unsigned p_cand;
   /*const*/ unsigned p_pwrd;     // PWRROMD
   /*const*/ unsigned p_promd;    // DIVROMD
   /*const*/ SPIFI_RTNS *pSPIFID; // SPIFIROMD
   /*const*/ unsigned p_dev3;
   /*const*/ unsigned p_dev4;
} ROM;

#define ROM_DRIVERS_PTR ((ROM *)(*((unsigned int *)SPIFI_ROM_PTR)))
#define IS_ADDR_IN_SPIFI(__addr)  ( (((uint32_t)(__addr)) & 0xff000000) == SPIFI_MEM_BASE )
#define IS_ADDR_IN_IFLASH(__addr) ( (((uint32_t)(__addr)) & 0xff000000) == 0x10000000 )

static void initialize_spifi(void)
{
  SPIFIobj* obj = (SPIFIobj*)malloc(sizeof(SPIFIobj));
  if (obj == NULL) {
    // Failed to allocate memory for ROM data
	notify_completion(false);
  }

  // Turn on SPIFI block as it is disabled on reset
  LPC_SC->PCONP |= 0x00010000;

  // pinsel for SPIFI
  LPC_IOCON->P2_7 = 5; /* SPIFI_CSN @ P2.7 */
  LPC_IOCON->P0_22 = 5; /* SPIFI_CLK @ P0.22 */
  LPC_IOCON->P0_15 = 5; /* SPIFI_IO2 @ P0.15 */
  LPC_IOCON->P0_16 = 5; /* SPIFI_IO3 @ P0.16 */
  LPC_IOCON->P0_17 = 5; /* SPIFI_IO1 @ P0.17 */
  LPC_IOCON->P0_18 = 5; /* SPIFI_IO0 @ P0.18 */

  uint32_t spifi_clk_div = (*((volatile uint32_t*)0x400FC1B4)) & 0x1f;
  uint32_t spifi_clk_mhz = (SystemCoreClock / spifi_clk_div) / 1000000;

  const SPIFI_RTNS* _spifi = ROM_DRIVERS_PTR->pSPIFID;

  /* Typical time tCS is 20 ns min, we give 200 ns to be on safer side */
  int rc = _spifi->spifi_init (obj, spifi_clk_mhz/5, S_FULLCLK+S_RCVCLK, spifi_clk_mhz);
  if (rc) {
	// Failed to initialize SPIFI
	notify_completion(false);
  }
}

int main() {

	initialize_spifi();

	// Make sure that most files are placed in IFLASH
	if (IS_ADDR_IN_SPIFI(splash_image1)  ||
	    IS_ADDR_IN_SPIFI(splash_image2)  ||
	    IS_ADDR_IN_SPIFI(splash_image3)  ||
	    IS_ADDR_IN_SPIFI(splash_image4)  ||
	    IS_ADDR_IN_SPIFI(splash_image5)  ||
	    IS_ADDR_IN_SPIFI(splash_image6)  ||
	    IS_ADDR_IN_SPIFI(splash_image7)  ||
	    IS_ADDR_IN_SPIFI(splash_image8)  ||
	    IS_ADDR_IN_SPIFI(splash_image9)  ||
	    IS_ADDR_IN_SPIFI(splash_image10) ||
	    IS_ADDR_IN_SPIFI(splash_image11) ||
	    IS_ADDR_IN_SPIFI(splash_image12) ||
	    IS_ADDR_IN_SPIFI(splash_image13) ||
	    IS_ADDR_IN_SPIFI(splash_image14)) {
		notify_completion(false);
	}

	// Make sure that splash_image15 is placed in SPIFI
	if (!IS_ADDR_IN_SPIFI(splash_image15)) {
		notify_completion(false);
	}

	notify_completion(true);
}

#include "test_env.h"
#include "mbed.h"
#include "spifi_rom_api.h"

__attribute__((section("SPIFI_MEM"))) const unsigned char cube_image[] = {
137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,
0,0,0,150,0,0,0,200,8,2,0,0,0,133,231,143,
50,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,
0,4,103,65,77,65,0,0,177,143,11,252,97,5,0,0,
0,9,112,72,89,115,0,0,14,195,0,0,14,195,1,199,
111,168,100,0,0,156,193,73,68,65,84,120,94,236,253,103,
124,27,233,125,54,140,14,48,24,0,51,24,244,94,9,246,
0,0,0,0,73,69,78,68,174,66,96,130};

int cube_image_sz = sizeof(cube_image);

const unsigned char cube_image_ref[] = {
137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,
0,0,0,150,0,0,0,200,8,2,0,0,0,133,231,143,
50,0,0,0,1,115,82,71,66,0,174,206,28,233,0,0,
0,4,103,65,77,65,0,0,177,143,11,252,97,5,0,0,
0,9,112,72,89,115,0,0,14,195,0,0,14,195,1,199,
111,168,100,0,0,156,193,73,68,65,84,120,94,236,253,103,
124,27,233,125,54,140,14,48,24,0,51,24,244,94,9,246,
0,0,0,0,73,69,78,68,174,66,96,130};

int cube_image_ref_sz = sizeof(cube_image_ref);

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

	// Make sure that cube_image is placed in SPIFI
	if (!IS_ADDR_IN_SPIFI(cube_image)) {
		notify_completion(false);
	}

	// Make sure that cube_image_ref is in IFLASH
	if (IS_ADDR_IN_SPIFI(cube_image_ref)) {
		notify_completion(false);
	}

	// Compare content
    if (cube_image_sz != cube_image_ref_sz) {
		notify_completion(false);
    } else {
      int i = 0;
      for (; i < cube_image_sz; i++) {
        if (cube_image[i] != cube_image_ref[i]) {
			notify_completion(false);
        }
      }
    }

	notify_completion(true);
}

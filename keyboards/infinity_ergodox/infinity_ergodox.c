#include "infinity_ergodox.h"
#include "ch.h"
#include "hal.h"
#include "serial_link/system/serial_link.h"

void init_serial_link_hal(void) {
    PORTA->PCR[1] = PORTx_PCRn_PE | PORTx_PCRn_PS | PORTx_PCRn_PFE | PORTx_PCRn_MUX(2);
    PORTA->PCR[2] = PORTx_PCRn_DSE | PORTx_PCRn_SRE | PORTx_PCRn_MUX(2);
    PORTE->PCR[0] = PORTx_PCRn_PE | PORTx_PCRn_PS | PORTx_PCRn_PFE | PORTx_PCRn_MUX(3);
    PORTE->PCR[1] = PORTx_PCRn_DSE | PORTx_PCRn_SRE | PORTx_PCRn_MUX(3);
}

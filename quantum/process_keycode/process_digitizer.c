#include "digitizer.h"
#include "process_digitizer.h"

__attribute__((weak)) void digitizer_task(void) {
    if (digitizer.status & DZ_UPDATED) {
        host_digitizer_send(&digitizer);
        digitizer.status &= ~DZ_UPDATED;
        
        //send a mouse report to make the cursor show up again (on windows at least)
        report_mouse_t newMouseReport;
        newMouseReport.h = 0;
        newMouseReport.v = 0;
        newMouseReport.x = 1;
        newMouseReport.y = 0;
        newMouseReport.buttons = 0;
        host_mouse_send(&newMouseReport);
    }
    
    
}


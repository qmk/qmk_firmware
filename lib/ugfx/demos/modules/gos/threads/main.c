#include "gfx.h"

#if defined(WIN32)
	#include <windows.h>

	static DWORD nres;

	// On Win32 don't use the C library fprintf or write as they crash.
	// Maybe we just need to add the multi-thread C library options to the compile.
	// Instead we use the Win32 API directly as that always works.
	#define DEBUGWRITE(str)		WriteFile(GetStdHandle(STD_ERROR_HANDLE), str, strlen(str), &nres, 0)
#else
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "You must alter this demo to define a DEBUGWRITE macro for your platform."
		#warning "Be careful of using C library functions as they sometimes crash if they are not expecting stack changes (if possible use a multi-thread aware C library)"
		#warning "You might flash LED's instead if that is better for your platform."
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("You must alter this demo to define a DEBUGWRITE macro for your platform.")
		COMPILER_WARNING("Be careful of using C library functions as they sometimes crash if they are not expecting stack changes (if possible use a multi-thread aware C library)")
		COMPILER_WARNING("You might flash LED's instead if that is better for your platform.")
	#endif
	#error "--"
#endif

gThreadreturn heartbeat1(void* param)
{
    (void)param;

    while (1) {
    	DEBUGWRITE("thread 1\n");
        gfxSleepMilliseconds(500);
    }

    return (gThreadreturn)0;
}

gThreadreturn heartbeat2(void* param)
{
    (void)param;

    while (1) {
    	DEBUGWRITE("thread 2\n");
        gfxSleepMilliseconds(900);
    }

    return (gThreadreturn)0;
}

int main(void)
{
    gfxInit();

    // Give this plenty of stack. Stack size optimisation should be a production change only
    gfxThreadCreate(0, 2048, gThreadpriorityNormal, heartbeat1, 0);
    gfxThreadCreate(0, 2048, gThreadpriorityNormal, heartbeat2, 0);

    while (1) {
    	DEBUGWRITE("thread main\n");
        gfxSleepMilliseconds(1400);
    }
}

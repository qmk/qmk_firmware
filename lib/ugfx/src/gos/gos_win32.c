/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

// We need to include stdio.h below. Turn off GFILE_NEED_STDIO just for this file to prevent conflicts
#define GFILE_NEED_STDIO_MUST_BE_OFF

#include "../../gfx.h"

#if GFX_USE_OS_WIN32

#include <stdio.h>

static HANDLE	SystemMutex;

void _gosInit(void)
{
	/* No initialization of the operating system itself is needed */
}

void _gosPostInit(void)
{
}

void _gosDeinit(void)
{

}

void gfxHalt(const char *msg) {
	if (msg)
		fprintf(stderr, "%s\n", msg);

	ExitProcess(1);
}

void gfxSleepMicroseconds(gDelay ms) {
    static LARGE_INTEGER pcfreq;
    static int initflag;
    LARGE_INTEGER t1, t2, tdiff;

    switch(ms) {
		case gDelayNone:
			return;

		case gDelayForever:
			while(1)
				Sleep(1000);
			return;
	}

    if (!initflag) {
        QueryPerformanceFrequency(&pcfreq);
        initflag++;
    }
    tdiff.QuadPart = pcfreq.QuadPart * ms / 1000000;

    QueryPerformanceCounter(&t1);
    do {
    	QueryPerformanceCounter(&t2);
    } while (t2.QuadPart - t1.QuadPart < tdiff.QuadPart);
}

void gfxSystemLock(void) {
	if (!SystemMutex)
		SystemMutex = CreateMutex(0, FALSE, 0);
	WaitForSingleObject(SystemMutex, INFINITE);
}

void gfxSystemUnlock(void) {
	ReleaseMutex(SystemMutex);
}

gBool gfxSemWait(gSem *psem, gDelay ms) {
	return WaitForSingleObject(*psem, ms) == WAIT_OBJECT_0;
}

typedef LONG (__stdcall *_NtQuerySemaphore)(
    HANDLE SemaphoreHandle,
    DWORD SemaphoreInformationClass, /* Would be SEMAPHORE_INFORMATION_CLASS */
    PVOID SemaphoreInformation,      /* but this is to much to dump here     */
    ULONG SemaphoreInformationLength,
    PULONG ReturnLength OPTIONAL
);

/* - Left here simply because of its undocumented cleverness...
gSemcount gfxSemCounter(gSem *pSem) {
	static _NtQuerySemaphore NtQuerySemaphore;
	struct _SEMAPHORE_BASIC_INFORMATION {
	    ULONG CurrentCount;
	    ULONG MaximumCount;
	} BasicInfo;

    if (!NtQuerySemaphore)
    	NtQuerySemaphore = (_NtQuerySemaphore)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQuerySemaphore");

    NtQuerySemaphore(*pSem, 0, &BasicInfo, sizeof(BasicInfo), 0);

    return BasicInfo.CurrentCount;
}
*/

gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION(*fn,p), void *param) {
	(void)	stackarea;
	HANDLE	thd;

	if (!(thd = CreateThread(0, stacksz, fn, param, CREATE_SUSPENDED, 0)))
		return 0;

	SetThreadPriority(thd, prio);
	ResumeThread(thd);

	return thd;
}

gThreadreturn gfxThreadWait(gThread thread) {
	DWORD	ret;

	WaitForSingleObject(thread, INFINITE);
	GetExitCodeThread(thread, &ret);
	CloseHandle(thread);

	return ret;
}

#endif /* GFX_USE_OS_WIN32 */
/** @} */


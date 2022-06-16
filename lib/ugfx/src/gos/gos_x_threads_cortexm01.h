/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * Thread Switching Functions for the Cortex M0 & M1
 *
 * Use the EABI calling standard (ARM's AAPCS) - Save r4 - r11
 * The context is saved at the current stack location and a pointer is maintained in the thread structure.
 */

#if defined(CORTEX_USE_FPU) && CORTEX_USE_FPU
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "GOS Threads: You have specified GFX_CPU=GFX_CPU_CORTX_M? with no hardware floating point support but CORTEX_USE_FPU is GFXON. Try using GFX_CPU_GFX_CPU_CORTEX_M?_FP instead"
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("GOS Threads: You have specified GFX_CPU=GFX_CPU_CORTX_M? with no hardware floating point support but CORTEX_USE_FPU is GFXON. Try using GFX_CPU_GFX_CPU_CORTEX_M?_FP instead")
	#endif
#endif

#if GFX_COMPILER == GFX_COMPILER_GCC || GFX_COMPILER == GFX_COMPILER_CYGWIN || GFX_COMPILER == GFX_COMPILER_MINGW32 || GFX_COMPILER == GFX_COMPILER_MINGW64
	#define GFX_THREADS_DONE
	#define _gfxThreadsInit()

	static __attribute__((pcs("aapcs"),naked)) void _gfxTaskSwitch(thread *oldt, thread *newt) {
		__asm__ volatile (	"push    {r4, r5, r6, r7, lr}                   \n\t"
							"mov     r4, r8                                 \n\t"
							"mov     r5, r9                                 \n\t"
							"mov     r6, r10                                \n\t"
							"mov     r7, r11                                \n\t"
							"push    {r4, r5, r6, r7}						\n\t"
							"mov     r4, sp                                 \n\t"
							"str     r4, %[oldtcxt]							\n\t"
							"ldr     r4, %[newtcxt]							\n\t"
							"mov     sp, r4                                 \n\t"
							"pop     {r4, r5, r6, r7}                   	\n\t"
							"mov     r8, r4                                 \n\t"
							"mov     r9, r5                                 \n\t"
							"mov     r10, r6                                \n\t"
							"mov     r11, r7                                \n\t"
							"pop     {r4, r5, r6, r7, pc}					\n\t"
							: [newtcxt] "=m" (newt->cxt)
							: [oldtcxt] "m" (oldt->cxt)
							: "memory");
	}

	static __attribute__((pcs("aapcs"),naked)) void _gfxStartThread(thread *oldt, thread *newt) {
		newt->cxt = (void *)(((unsigned)newt + newt->size) & ~7);
		__asm__ volatile (	"push    {r4, r5, r6, r7, lr}                   \n\t"
							"mov     r4, r8                                 \n\t"
							"mov     r5, r9                                 \n\t"
							"mov     r6, r10                                \n\t"
							"mov     r7, r11                                \n\t"
							"push    {r4, r5, r6, r7}						\n\t"
							"mov     r4, sp                                 \n\t"
							"str     r4, %[oldtcxt]							\n\t"
							"ldr     r4, %[newtcxt]							\n\t"
							"mov     sp, r4                                 \n\t"
							: [newtcxt] "=m" (newt->cxt)
							: [oldtcxt] "m" (oldt->cxt)
							: "memory");

		// Run the users function
		gfxThreadExit(_gfxCurrentThread->fn(_gfxCurrentThread->param));
	}

#elif GFX_COMPILER == GFX_COMPILER_KEIL || GFX_COMPILER == GFX_COMPILER_ARMCC
	#define GFX_THREADS_DONE
	#define _gfxThreadsInit()

	static __asm void _gfxTaskSwitch(thread *oldt, thread *newt) {
		PRESERVE8

		// Save the old context
		push	{r4, r5, r6, r7, lr}
		mov     r4, r8
		mov     r5, r9
		mov     r6, r10
		mov     r7, r11
		push    {r4, r5, r6, r7}
		mov		r4, sp
		str		r4, [r0,#__cpp(offsetof(thread,cxt))]		// oldt->cxt
		
		// Load the new context
		ldr		r4, [r1,#__cpp(offsetof(thread,cxt))]		// newt->cxt
		mov		sp, r4
		pop     {r4, r5, r6, r7}
		mov     r8, r4
		mov     r9, r5
		mov     r10, r6
		mov     r11, r7
		pop     {r4, r5, r6, r7, pc}
	}

	static __asm void _gfxStartThread(thread *oldt, thread *newt) {
		PRESERVE8

		// Calculate where to generate the new context
		//		newt->cxt = (void *)(((unsigned)newt + newt->size) & ~7);
		ldr      r2,[r1,#__cpp(offsetof(thread,size))]
		add      r2,r2,r1
		and      r2, r2, #0xFFFFFFF8
		str      r2,[r1,#__cpp(offsetof(thread,cxt))]
		
		// Save the old context
		push	{r4, r5, r6, r7, lr}
		mov     r4, r8
		mov     r5, r9
		mov     r6, r10
		mov     r7, r11
		push    {r4, r5, r6, r7}
		mov		r4, sp
		str		r4, [r0,#__cpp(offsetof(thread,cxt))]	// oldt->cxt
		
		// Load the new (imcomplete) context
		ldr		r4, [r1,#__cpp(offsetof(thread,cxt))]	// newt->cxt
		mov		sp, r4
		
		// Run the users function - we save some code because gfxThreadExit() never returns
		//		gfxThreadExit(_gfxCurrentThread->fn(_gfxCurrentThread->param));
		ldr      r2,=__cpp(&_gfxCurrentThread)
		ldr      r2,[r2,#0]
		ldr      r0,[r2,#__cpp(offsetof(thread,param))]
		ldr      r1,[r2,#__cpp(offsetof(thread,fn))]
		blx      r1
		mov      r4,r0
		bl       __cpp(gfxThreadExit)
		
		ALIGN
	}

#else
	#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
		#warning "GOS Threads: You have specified a specific CPU but your compiler is not supported. Defaulting to CLIB switching"
	#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
		COMPILER_WARNING("GOS Threads: You have specified a specific CPU but your compiler is not supported. Defaulting to CLIB switching")
	#endif
#endif

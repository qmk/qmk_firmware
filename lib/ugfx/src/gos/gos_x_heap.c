/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GOS_NEED_X_HEAP

#include <string.h>				// Prototype for memcpy()


#if GFX_OS_HEAP_SIZE == 0
	#include <stdlib.h>				// Prototype for malloc(), realloc() and free()

	void _gosHeapInit(void) {
	}
	void *gfxAlloc(gMemSize sz) {
		return malloc(sz);
	}

	void *gfxRealloc(void *ptr, gMemSize oldsz, gMemSize newsz) {
		(void) oldsz;
		return realloc(ptr, newsz);
	}

	void gfxFree(void *ptr) {
		free(ptr);
	}

#else

	// Slot structure - user memory follows
	typedef struct memslot {
		gMemSize			sz;			// Includes the size of this memslot.
		} memslot;

	// Free Slot - immediately follows the memslot structure
	typedef struct freeslot {
		memslot *nextfree;			// The next free slot
	} freeslot;

	#define GetSlotSize(sz)		((((sz) + (sizeof(freeslot) - 1)) & ~(sizeof(freeslot) - 1)) + sizeof(memslot))
	#define NextFree(pslot)		((freeslot *)Slot2Ptr(pslot))->nextfree
	#define Ptr2Slot(p)			((memslot *)(p) - 1)
	#define Slot2Ptr(pslot)		((pslot)+1)

	static memslot *			freeSlots;
	static char					heap[GFX_OS_HEAP_SIZE];

	void _gosHeapInit(void) {
		gfxAddHeapBlock(heap, GFX_OS_HEAP_SIZE);
	}

	void gfxAddHeapBlock(void *ptr, gMemSize sz) {
		if (sz < sizeof(memslot)+sizeof(freeslot))
			return;

		((memslot *)ptr)->sz = sz;
		gfxFree(Slot2Ptr((memslot *)ptr));
	}

	void *gfxAlloc(gMemSize sz) {
		register memslot *prev, *p, *pnew;

		if (!sz) return 0;
		sz = GetSlotSize(sz);
		for (prev = 0, p = freeSlots; p != 0; prev = p, p = NextFree(p)) {
			// Loop till we have a block big enough
			if (p->sz < sz)
				continue;
				
			// Can we save some memory by splitting this block?
			if (p->sz >= sz + sizeof(memslot)+sizeof(freeslot)) {
				pnew = (memslot *)((char *)p + sz);
				pnew->sz = p->sz - sz;
				p->sz = sz;
				NextFree(pnew) = NextFree(p);
				NextFree(p) = pnew;
			}
			
			// Remove it from the free list
			if (prev)
				NextFree(prev) = NextFree(p);
			else
				freeSlots = NextFree(p);
				
			// Return the result found
			return Slot2Ptr(p);
		}
		// No slots large enough
		return 0;
	}

	void *gfxRealloc(void *ptr, gMemSize oldsz, gMemSize sz) {
		register memslot *prev, *p, *pfree;
		(void) oldsz;

		if (!ptr)
			return gfxAlloc(sz);
		if (!sz) {
			gfxFree(ptr);
			return 0;
		}

		p = Ptr2Slot(ptr);
		sz = GetSlotSize(sz);

		// If the next slot is free (and contiguous) merge it into this one
		for (prev = 0, pfree = freeSlots; pfree != 0; prev = pfree, pfree = NextFree(pfree)) {
			if (pfree == (memslot *)((char *)p + p->sz)) {
				p->sz += pfree->sz;
				if (prev)
					NextFree(prev) = NextFree(pfree);
				else
					freeSlots = NextFree(pfree);
				break;
			}
		}

		// If this block is large enough we are nearly done
		if (sz < p->sz) {
			// Can we save some memory by splitting this block?
			if (p->sz >= sz + sizeof(memslot)+sizeof(freeslot)) {
				pfree = (memslot *)((char *)p + sz);
				pfree->sz = p->sz - sz;
				p->sz = sz;
				NextFree(pfree) = freeSlots;
				freeSlots = pfree;
			}
			return Slot2Ptr(p);
		}

		// We need to do this the hard way
		pfree = gfxAlloc(sz);
		if (!pfree)
			return 0;
		memcpy(pfree, ptr, p->sz - sizeof(memslot));
		gfxFree(ptr);
		return pfree;
	}

	void gfxFree(void *ptr) {
		register memslot *prev, *p, *pfree;

		if (!ptr)
			return;

		p = Ptr2Slot(ptr);

		// Find a free slot that is contiguous precceding and merge it into us
		for (prev = 0, pfree = freeSlots; pfree != 0; prev = pfree, pfree = NextFree(pfree)) {
			if (p == (memslot *)((char *)pfree + pfree->sz)) {
				pfree->sz += p->sz;
				if (prev)
					NextFree(prev) = NextFree(pfree);
				else
					freeSlots = NextFree(pfree);
				p = pfree;
				break;
			}
		}

		// Find a free slot that is contiguous after and merge it into this one
		for (prev = 0, pfree = freeSlots; pfree != 0; prev = pfree, pfree = NextFree(pfree)) {
			if (pfree == (memslot *)((char *)p + p->sz)) {
				p->sz += pfree->sz;
				if (prev)
					NextFree(prev) = NextFree(pfree);
				else
					freeSlots = NextFree(pfree);
				break;
			}
		}

		// Add it into the free chain
		NextFree(p) = freeSlots;
		freeSlots = p;
	}
#endif

#endif /* GOS_NEED_X_HEAP */

#if GFX_EMULATE_MALLOC
	#include <stdlib.h>

	void* malloc(size_t size) {
		return gfxAlloc((gMemSize)size);
	}
	void free(void *ptr) {
		gfxFree(ptr);
	}
#endif

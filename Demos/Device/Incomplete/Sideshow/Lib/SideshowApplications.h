/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#ifndef _SIDESHOW_APPLICATIONS_H_
#define _SIDESHOW_APPLICATIONS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>
		#include <stdbool.h>

		#include "SideshowCommon.h"

	/* Type Defines: */
		typedef struct
		{
			bool                   InUse;
			GUID_t                 ApplicationID;
			GUID_t                 EndpointID;
			UNICODE_STRING_t(50)   ApplicationName;
			uint32_t               CachePolicy;
			uint32_t               OnlineOnly;
			bool                   HaveContent;
			uint32_t               CurrentContentID;
			uint8_t                CurrentContent[MAX_CONTENTBUFFER_PER_APP];
		} SideShow_Application_t;

	/* External Variables: */
		extern SideShow_Application_t InstalledApplications[MAX_APPLICATIONS];

	/* Function Prototypes: */
		SideShow_Application_t* SideShow_GetFreeApplication(void);
		SideShow_Application_t* SideShow_GetApplicationFromGUID(GUID_t* const GUID);

#endif


/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  \brief LUFA library version constants.
 *
 *  Version constants for informational purposes and version-specific macro creation. This header file contains the
 *  current LUFA version number in several forms, for use in the user-application (for example, for printing out
 *  whilst debugging, or for testing for version compatibility).
 */

#ifndef __LUFA_VERSION_H__
#define __LUFA_VERSION_H__

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name LUFA Release Type Constants */
			//@{
				/** Constant for \ref LUFA_VERSION_RELEASE_TYPE indicating a development release. */
				#define LUFA_VERSION_RELEASE_TYPE_DEVELOPMENT   0

				/** Constant for \ref LUFA_VERSION_RELEASE_TYPE indicating a beta release. */
				#define LUFA_VERSION_RELEASE_TYPE_BETA          1

				/** Constant for \ref LUFA_VERSION_RELEASE_TYPE indicating a full official release. */
				#define LUFA_VERSION_RELEASE_TYPE_FULL          2
			//@}

			/** Indicates the version number of the library, as an integer. \note This value is only updates in non-development releases. */
			#define LUFA_VERSION_INTEGER              0x170418

			/** Indicates the version number of the library, as a string. \note This value is only updates in non-development releases. */
			#define LUFA_VERSION_STRING               "170418"

			/** Indicates the release type of the library. */
			#define LUFA_VERSION_RELEASE_TYPE         LUFA_VERSION_RELEASE_TYPE_DEVELOPMENT

#endif


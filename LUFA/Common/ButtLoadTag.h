/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

/** \file
 *
 *  This file contains macros for the embedding of compile-time strings into the resultant project binary for
 *  identification purposes. It is designed to prefix "tags" with the magic string of "@(#)" so that the tags
 *  can easily be identified in the binary data.
 *
 *  These tags are compatible with the ButtLoad project at http://www.fourwalledcubicle.com/ButtLoad.php .
 */

#ifndef __BUTTLOADTAG_H__
#define __BUTTLOADTAG_H__

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Creates a new tag in the resultant binary, containing the specified data array. The macro id
			 *  parameter is only for identification purposes (so that the tag data can be referenced in code)
			 *  and is not visible in the compiled binary.
			 */
			#define BUTTLOADTAG(id, data)  const struct ButtLoadTagData BUTTTAG_##id \
			                               PROGMEM __attribute__((used, externally_visible)) = \
			                               {MagicString: BT_TAGHEADER, TagData: data}
			
			/** Macro for retrieving a reference to the specified tag's contents. The tag data is located in
			 *  the program memory (FLASH) space, and so must be read out with the macros in avr-libc which
			 *  deal with embedded data.
			 */
			#define BUTTLOADTAG_DATA(id)  BUTTTAG_##id.TagData

		/* Structures: */
			/** Structure for ButtLoad compatible binary tags. */
			struct ButtLoadTagData
			{
				char MagicString[4]; /**< Magic tag header, containing the string "@(#)". */
				char TagData[];      /**< Tag contents as a char array. */
			};										  

	/* Private Interface - For use in library only: */	
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define BT_TAGHEADER          {'@','(','#',')'}
	#endif
	
#endif

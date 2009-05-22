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
 *  Configuration descriptor parser API. This section of the library gives a friendly API which can be used in
 *  host applications to easily parse an attached device's configuration descriptor so that endpoint, interface
 *  and other descriptor data can be extracted and used as needed.
 */

/** \ingroup Group_Descriptors
 *  @defgroup Group_ConfigDescriptorParser Configuration Descriptor Parser
 *
 *  Functions, macros, variables, enums and types related to the parsing of Configuration Descriptors.
 *
 *  @{
 */

#ifndef __CONFIGDESCRIPTOR_H__
#define __CONFIGDESCRIPTOR_H__

	/* Includes: */
		#include <avr/io.h>
		
		#include "../../../Common/Common.h"
		#include "../HighLevel/USBMode.h"
		#include "../LowLevel/HostChapter9.h"
		#include "../HighLevel/StdDescriptors.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */	
		/* Macros: */
			/** Mask for determining the type of an endpoint from an endpoint descriptor. This should then be compared
			 *  with the EP_TYPE_* masks to determine the exact type of the endpoint.
			 */
			#define EP_TYPE_MASK                       0x03

			/** Casts a pointer to a descriptor inside the configuration descriptor into a pointer to the given
			 *  descriptor type.
			 *
			 *  Usage Example:
			 *  \code
			 *  uint8_t* CurrDescriptor = &ConfigDescriptor[0]; // Pointing to the configuration header
			 *  USB_Descriptor_Configuration_Header_t* ConfigHeaderPtr = DESCRIPTOR_PCAST(CurrDescriptor,
			 *                                                           USB_Descriptor_Configuration_Header_t);
			 *
			 *  // Can now access elements of the configuration header struct using the -> indirection operator
			 *  \endcode
			 */
			#define DESCRIPTOR_PCAST(DescriptorPtr, Type) ((Type*)DescriptorPtr)

			/** Casts a pointer to a descriptor inside the configuration descriptor into the given descriptor
			 *  type (as an actual struct instance rather than a pointer to a struct).
			 *
			 *  Usage Example:
			 *  \code
			 *  uint8_t* CurrDescriptor = &ConfigDescriptor[0]; // Pointing to the configuration header
			 *  USB_Descriptor_Configuration_Header_t ConfigHeader = DESCRIPTOR_CAST(CurrDescriptor,
			 *                                                       USB_Descriptor_Configuration_Header_t);
			 *
			 *  // Can now access elements of the configuration header struct using the . operator
			 *  \endcode
			 */
			#define DESCRIPTOR_CAST(DescriptorPtr, Type)  (*DESCRIPTOR_PCAST(DescriptorPtr, Type))

			/** Returns the descriptor's type, expressed as the 8-bit type value in the header of the descriptor.
			 *  This value's meaning depends on the descriptor's placement in the descriptor, but standard type
			 *  values can be accessed in the \ref USB_DescriptorTypes_t enum.
			 */
			#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				#define DESCRIPTOR_TYPE(DescriptorPtr)    DESCRIPTOR_CAST(DescriptorPtr, USB_Descriptor_Header_t).Type
			#else
				#define DESCRIPTOR_TYPE(DescriptorPtr)    DESCRIPTOR_CAST(DescriptorPtr, USB_Descriptor_Header_t).bDescriptorType			
			#endif
			
			/** Returns the descriptor's size, expressed as the 8-bit value indicating the number of bytes. */
			#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				#define DESCRIPTOR_SIZE(DescriptorPtr)    DESCRIPTOR_CAST(DescriptorPtr, USB_Descriptor_Header_t).Size
			#else
				#define DESCRIPTOR_SIZE(DescriptorPtr)    DESCRIPTOR_CAST(DescriptorPtr, USB_Descriptor_Header_t).bLength
			#endif

		/* Type Defines: */
			/** Type define for a Configuration Descriptor comparator function (function taking a pointer to an array
			 *  of type void, returning a uint8_t value).
			 *
			 *  \see \ref USB_GetNextDescriptorComp function for more details
			 */
			typedef uint8_t (* const ConfigComparatorPtr_t)(void* const);

		/* Function Prototypes: */
			/** Searches for the next descriptor in the given configuration descriptor using a premade comparator
			 *  function. The routine updates the position and remaining configuration descriptor bytes values
			 *  automatically. If a comparator routine fails a search, the descriptor pointer is retreated back
			 *  so that the next descriptor search invocation will start from the descriptor which first caused the
			 *  original search to fail. This behaviour allows for one comparator to be used immediately after another
			 *  has failed, starting the second search from the descriptor which failed the first.
			 *
			 *  Comparator functions should be standard functions which accept a pointer to the header of the current
			 *  descriptor inside the configuration descriptor which is being compared, and should return a value from
			 *  the \ref DSearch_Return_ErrorCodes_t enum as a uint8_t value.
			 *
			 *  \note This function is available in USB Host mode only.
			 *
			 *  \param BytesRem  Pointer to an int storing the remaining bytes in the configuration descriptor
			 *  \param CurrConfigLoc  Pointer to the current position in the configuration descriptor
			 *  \param ComparatorRoutine  Name of the comparator search function to use on the configuration descriptor
			 *
			 *  \return Value of one of the members of the \ref DSearch_Comp_Return_ErrorCodes_t enum
			 *
			 *  Usage Example:
			 *  \code
			 *  uint8_t EndpointSearcher(void* CurrentDescriptor); // Comparator Prototype
			 *
			 *  uint8_t EndpointSearcher(void* CurrentDescriptor)
			 *  {
			 *     if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
			 *         return DESCRIPTOR_SEARCH_Found;
			 *     else
			 *         return DESCRIPTOR_SEARCH_NotFound;
			 *  }
			 *
			 *  //...
			 *  // After retrieving configuration descriptor:
			 *  if (USB_Host_GetNextDescriptorComp(&BytesRemaining, &ConfigDescriptorData, EndpointSearcher) ==
			 *      Descriptor_Search_Comp_Found)
			 *  {
			 *      // Do something with the endpoint descriptor
			 *  }
			 *  \endcode
			 */
			uint8_t USB_GetNextDescriptorComp(uint16_t* BytesRem, uint8_t** CurrConfigLoc, ConfigComparatorPtr_t ComparatorRoutine);
			
		/* Enums: */
			/** Enum for return values of a descriptor comparator function. */
			enum DSearch_Return_ErrorCodes_t
			{
				DESCRIPTOR_SEARCH_Found                = 0, /**< Current descriptor matches comparator criteria. */
				DESCRIPTOR_SEARCH_Fail                 = 1, /**< No further descriptor could possibly match criteria, fail the search. */
				DESCRIPTOR_SEARCH_NotFound             = 2, /**< Current descriptor does not match comparator criteria. */
			};

			/** Enum for return values of \ref USB_GetNextDescriptorComp(). */
			enum DSearch_Comp_Return_ErrorCodes_t
			{
				DESCRIPTOR_SEARCH_COMP_Found           = 0, /**< Configuration descriptor now points to descriptor which matches
				                                             *   search criteria of the given comparator function. */
				DESCRIPTOR_SEARCH_COMP_Fail            = 1, /**< Comparator function returned Descriptor_Search_Fail. */
				DESCRIPTOR_SEARCH_COMP_EndOfDescriptor = 2, /**< End of configuration descriptor reached before match found. */
			};
	
		/* Function Prototypes: */
			/** Retrieves the configuration descriptor data or size from an attached device via a standard request.
			 *
			 *  \param ConfigSizePtr  Pointer to a uint16_t for either storing or retrieving the configuration
			 *         descriptor size
			 *
			 *  \param BufferPtr  Pointer to the buffer for storing the configuration descriptor data. If this is
			 *                    NULL, the size of the configuration descriptor will be retrieved instead and
			 *                    placed in the variable pointed to by ConfigSizePtr. If this is non-NULL, the number
			 *                    of bytes indicated by ConfigSizePtr of the configuration descriptor will be loaded
			 *                    into the buffer
			 */
			uint8_t USB_GetDeviceConfigDescriptor(uint16_t* const ConfigSizePtr, void* BufferPtr)
			                                      ATTR_NON_NULL_PTR_ARG(1);

			/** Skips to the next sub-descriptor inside the configuration descriptor of the specified type value.
			 *  The bytes remaining value is automatically decremented.
			 *
			 * \param BytesRem  Pointer to the number of bytes remaining of the configuration descriptor
			 * \param CurrConfigLoc  Pointer to the current descriptor inside the configuration descriptor
			 * \param Type  Descriptor type value to search for
			 */
			void USB_GetNextDescriptorOfType(uint16_t* const BytesRem,
			                                 uint8_t** const CurrConfigLoc,
			                                 const uint8_t Type)
			                                 ATTR_NON_NULL_PTR_ARG(1, 2);

			/** Skips to the next sub-descriptor inside the configuration descriptor of the specified type value,
			 *  which must come before a descriptor of the second given type value. If the BeforeType type
			 *  descriptor is reached first, the number of bytes remaining to process is set to zero and the
			 *  function exits. The bytes remaining value is automatically decremented.
			 *
			 * \param BytesRem  Pointer to the number of bytes remaining of the configuration descriptor
			 * \param CurrConfigLoc  Pointer to the current descriptor inside the configuration descriptor
			 * \param Type  Descriptor type value to search for
			 * \param BeforeType  Descriptor type value which must not be reached before the given Type descriptor
			 */
			void USB_GetNextDescriptorOfTypeBefore(uint16_t* const BytesRem,
			                                       uint8_t** const CurrConfigLoc,
			                                       const uint8_t Type,
			                                       const uint8_t BeforeType)
			                                       ATTR_NON_NULL_PTR_ARG(1, 2);

			/** Skips to the next sub-descriptor inside the configuration descriptor of the specified type value,
			 *  which must come after a descriptor of the second given type value. The bytes remaining value is
			 *  automatically decremented.
			 *
			 * \param BytesRem  Pointer to the number of bytes remaining of the configuration descriptor
			 * \param CurrConfigLoc  Pointer to the current descriptor inside the configuration descriptor
			 * \param Type  Descriptor type value to search for
			 * \param AfterType  Descriptor type value which must be reached before the given Type descriptor
			 */
			void USB_GetNextDescriptorOfTypeAfter(uint16_t* const BytesRem,
			                                      uint8_t** const CurrConfigLoc,
			                                      const uint8_t Type,
			                                      const uint8_t AfterType)
			                                      ATTR_NON_NULL_PTR_ARG(1, 2);

		/* Inline Functions: */
			/** Skips over the current sub-descriptor inside the configuration descriptor, so that the pointer then
			    points to the next sub-descriptor. The bytes remaining value is automatically decremented.
			 *
			 * \param BytesRem  Pointer to the number of bytes remaining of the configuration descriptor
			 * \param CurrConfigLoc  Pointer to the current descriptor inside the configuration descriptor
			 */
			static inline void USB_GetNextDescriptor(uint16_t* const BytesRem,
			                                         uint8_t** const CurrConfigLoc) 
			                                         ATTR_NON_NULL_PTR_ARG(1, 2);									  
			static inline void USB_GetNextDescriptor(uint16_t* const BytesRem,
			                                         uint8_t** const CurrConfigLoc)
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES)
				uint16_t CurrDescriptorSize = DESCRIPTOR_CAST(*CurrConfigLoc, USB_Descriptor_Header_t).Size;
				#else
				uint16_t CurrDescriptorSize = DESCRIPTOR_CAST(*CurrConfigLoc, USB_Descriptor_Header_t).bLength;				
				#endif

				*CurrConfigLoc += CurrDescriptorSize;
				*BytesRem      -= CurrDescriptorSize;
			}
			
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

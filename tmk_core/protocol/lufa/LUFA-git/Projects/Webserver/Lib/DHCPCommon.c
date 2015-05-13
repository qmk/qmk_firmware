/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Common DHCP routines to manage DHCP packet data.
 */

#include "DHCPCommon.h"

#if defined(ENABLE_DHCP_CLIENT) || defined(ENABLE_DHCP_SERVER) || defined(__DOXYGEN__)

/** Sets the given DHCP option in the DHCP packet's option list. This automatically moves the
 *  end of options terminator past the new option in the options list.
 *
 *  \param[in,out] DHCPOptionList  Pointer to the start of the DHCP packet's options list
 *  \param[in]     Option          DHCP option to add to the list
 *  \param[in]     DataLen         Size in bytes of the option data to add
 *  \param[in]     OptionData      Buffer where the option's data is to be sourced from
 *
 *  \return Number of bytes added to the DHCP packet
 */
uint8_t DHCPCommon_SetOption(uint8_t* DHCPOptionList,
                             const uint8_t Option,
                             const uint8_t DataLen,
                             void* const OptionData)
{
	/* Skip through the DHCP options list until the terminator option is found */
	while (*DHCPOptionList != DHCP_OPTION_END)
	  DHCPOptionList += (DHCPOptionList[1] + 2);

	/* Overwrite the existing terminator with the new option, add a new terminator at the end of the list */
	DHCPOptionList[0] = Option;
	DHCPOptionList[1] = DataLen;
	memcpy(&DHCPOptionList[2], OptionData, DataLen);
	DHCPOptionList[2 + DataLen] = DHCP_OPTION_END;

	/* Calculate the total number of bytes added to the outgoing packet */
	return (2 + DataLen);
}

/** Retrieves the given option's data (if present) from the DHCP packet's options list.
 *
 *  \param[in,out] DHCPOptionList  Pointer to the start of the DHCP packet's options list
 *  \param[in]     Option          DHCP option to retrieve to the list
 *  \param[out]    Destination     Buffer where the option's data is to be written to if found
 *
 *  \return Boolean \c true if the option was found in the DHCP packet's options list, \c false otherwise
 */
bool DHCPCommon_GetOption(const uint8_t* DHCPOptionList,
                          const uint8_t Option,
                          void* const Destination)
{
	/* Look through the incoming DHCP packet's options list for the requested option */
	while (*DHCPOptionList != DHCP_OPTION_END)
	{
		/* Check if the current DHCP option in the packet is the one requested */
		if (DHCPOptionList[0] == Option)
		{
			/* Copy request option's data to the destination buffer */
			memcpy(Destination, &DHCPOptionList[2], DHCPOptionList[1]);

			/* Indicate that the requested option data was successfully retrieved */
			return true;
		}

		/* Skip to next DHCP option in the options list */
		DHCPOptionList += (DHCPOptionList[1] + 2);
	}

	/* Requested option not found in the incoming packet's DHCP options list */
	return false;
}

#endif


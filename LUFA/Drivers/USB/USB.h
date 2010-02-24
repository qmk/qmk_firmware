/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Master include file for the library USB functionality. This file should be included in all user projects making
 *  use of the USB portions of the library, instead of including any headers in the USB/LowLevel or USB/HighLevel
 *  directories.
 */

/** @defgroup Group_USB USB - LUFA/Drivers/USB/USB.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/LowLevel/DevChapter9.c
 *    - LUFA/Drivers/USB/LowLevel/Endpoint.c
 *    - LUFA/Drivers/USB/LowLevel/Host.c
 *    - LUFA/Drivers/USB/LowLevel/HostChapter9.c
 *    - LUFA/Drivers/USB/LowLevel/LowLevel.c
 *    - LUFA/Drivers/USB/LowLevel/Pipe.c
 *    - LUFA/Drivers/USB/HighLevel/Events.c
 *    - LUFA/Drivers/USB/HighLevel/USBInterrupt.c
 *    - LUFA/Drivers/USB/HighLevel/USBTask.c
 *    - LUFA/Drivers/USB/HighLevel/ConfigDescriptor.c
 *
 *  \section Module Description
 *  Driver and framework for the USB controller hardware on the USB series of AVR microcontrollers. This module
 *  consists of many submodules, and is designed to provide an easy way to configure and control USB host, device
 *  or OTG mode USB applications.
 *
 *  The USB stack requires the sole control over the USB controller in the microcontroller only; i.e. it does not
 *  require any additional AVR timers, etc. to operate. This ensures that the USB stack requires as few resources
 *  as possible.
 *
 *  The USB stack can be used in Device Mode for connections to USB Hosts (see \ref Group_Device), in Host mode for
 *  hosting of other USB devices (see \ref Group_Host), or as a dual role device which can either act as a USB host
 *  or device depending on what peripheral is connected (see \ref Group_OTG). Both modes also require a common set
 *  of USB management functions found \ref Group_USBManagement.
 */

/** \ingroup Group_USB
 *  @defgroup Group_USBClassDrivers USB Class Drivers
 *
 *  Drivers for both host and device mode of the standard USB classes, for rapid application development.
 *  Class drivers give a framework which sits on top of the low level library API, allowing for standard
 *  USB classes to be implemented in a project with minimal user code. These drivers can be used in
 *  conjunction with the library low level APIs to implement interfaces both via the class drivers and via
 *  the standard library APIs.
 *
 *  Multiple device mode class drivers can be used within a project, including multiple instances of the
 *  same class driver. In this way, USB Hosts and Devices can be made quickly using the internal class drivers
 *  so that more time and effort can be put into the end application instead of the USB protocol.
 *
 *  The available class drivers and their modes are listed below.
 *
 *  <table>
 *  <tr>
 *   <th width="100px">USB Class</th> 
 *   <th width="90px">Device Mode</th> 
 *   <th width="90px">Host Mode</th> 
 *  </tr>
 *  <tr>
 *   <td>Audio</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *   <td bgcolor="#EE0000">No</td>
 *  </tr>
 *  <tr>
 *   <td>CDC</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *  </tr>
 *  <tr>
 *   <td>HID</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *  </tr>
 *  <tr>
 *   <td>MIDI</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *  </tr>
 *  <tr>
 *   <td>Mass Storage</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *  </tr>
 *  <tr>
 *   <td>Printer</td>
 *   <td bgcolor="#EE0000">No</td>
*    <td bgcolor="#00EE00">Yes</td>
 *  </tr>
 *  <tr>
 *   <td>RNDIS</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *  </tr>
 *  <tr>
 *   <td>Still Image</td>
 *   <td bgcolor="#EE0000">No</td>
 *   <td bgcolor="#00EE00">Yes</td>
 *  </tr>
 *  </table>
 *
 *
 *  \section Sec_UsingClassDrivers Using the Class Drivers
 *  To make the Class drivers easy to integrate into a user application, they all implement a standardized
 *  design with similarly named/used function, enums, defines and types. The two different modes are implemented
 *  slightly differently, and thus will be explained separately. For information on a specific class driver, read
 *  the class driver's module documentation.
 *
 *  \subsection SSec_ClassDriverDevice Device Mode Class Drivers
 *  Implementing a Device Mode Class Driver in a user application requires a number of steps to be followed. Firstly,
 *  the module configuration and state structure must be added to the project source. These structures are named in a 
 *  similar manner between classes, that of <i>USB_ClassInfo_<b>{Class Name}</b>_Device_t</i>, and are used to hold the
 *  complete state and configuration for each class instance. Multiple class instances is where the power of the class 
 *  drivers lie; multiple interfaces of the same class simply require more instances of the Class Driver's ClassInfo 
 *  structure.
 *
 *  Inside the ClassInfo structure lies two sections, a <i>Config</i> section, and a <i>State</i> section. The Config
 *  section contains the instance's configuration parameters, and <b>must have all fields set by the user application</b>
 *  before the class driver is used. Each Device mode Class driver typically contains a set of configuration parameters
 *  for the endpoint size/number of the associated logical USB interface, plus any class-specific configuration parameters.
 *
 *  The <i>State</i> section of the ClassInfo structures are designed to be controlled by the Class Drivers only for
 *  maintaining the Class Driver instance's state, and should not normally be set by the user application.
 *
 *  The following is an example of a properly initialized instance of the Audio Class Driver structure:
 *
 *  \code
 *  USB_ClassInfo_Audio_Device_t My_Audio_Interface =
 *  {
 *      .Config =
 *          {
 *              .StreamingInterfaceNumber = 1,
 *              
 *              .DataINEndpointNumber     = 1,
 *              .DataINEndpointSize       = 256,
 *          },
 *  };
 *  \endcode
 *
 *  \note The class driver's configuration parameters should match those used in the device's descriptors that are
 *  sent to the host.
 *
 *  To initialize the Class driver instance, the driver's <i><b>{Class Name}</b>_Device_ConfigureEndpoints()</i> function
 *  should be called in response to the \ref EVENT_USB_Device_ConfigurationChanged() event. This function will return a
 *  boolean value if the driver sucessfully initialized the instance. Like all the class driver functions, this function
 *  takes in the address of the specific instance you wish to initialize - in this manner, multiple seperate instances of
 *  the same class type can be initialized like thus:
 *
 *  \code
 *  void EVENT_USB_Device_ConfigurationChanged(void)
 *  {
 *  	LEDs_SetAllLEDs(LEDMASK_USB_READY);
 *  	
 *  	if (!(Audio_Device_ConfigureEndpoints(&My_Audio_Interface)))
 *  	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
 *  }
 *  \endcode
 * 
 *  Once initialized, it is important to maintain the class driver's state by repeatedly calling the Class Driver's
 *  <i><b>{Class Name}</b>_Device_USBTask()</i> function in the main program loop. The exact implementation of this
 *  function varies between class drivers, and can be used for any internal class driver purpose to maintain each
 *  instance. Again, this function uses the address of the instance to operate on, and thus needs to be called for each
 *  seperate instance, just like the main USB maintenance routine \ref USB_USBTask():
 *
 *  \code
 *  int main(void)
 *  {
 *      SetupHardware();
 *  
 *      LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
 *  
 *      for (;;)
 *      {
 *          Create_And_Process_Samples();
 *      
 *          Audio_Device_USBTask(&My_Audio_Interface);
 *          USB_USBTask();
 *      }
 *  }
 *  \endcode
 *
 *  The final standardized Device Class Driver function is the Control Request handler function
 *  <i><b>{Class Name}</b>_Device_ProcessControlRequest()</i>, which should be called when the
 *  \ref EVENT_USB_Device_UnhandledControlRequest() event fires. This function should also be
 *  called for each class driver instance, using the address of the instance to operate on as
 *  the function's parameter. The request handler will abort if it is determined that the current
 *  request is not targeted at the given class driver instance, thus these methods can safely be
 *  called one-after-another in the event handler with no form of error checking:
 *
 *  \code
 *  void EVENT_USB_Device_UnhandledControlRequest(void)
 *  {
 *      Audio_Device_ProcessControlRequest(&My_Audio_Interface);
 *  }
 *  \endcode
 *
 *  Each class driver may also define a set of callback functions (which are prefixed by "CALLBACK_"
 *  in the function's name) which <b>must</b> also be added to the user application - refer to each
 *  individual class driver's documentation for mandatory callbacks. In addition, each class driver may
 *  also define a set of events (identifiable by their prefix of "EVENT_" in the function's name), which
 *  the user application <b>may</b> choose to implement, or ignore if not needed.
 *
 *  The individual Device Mode Class Driver documentation contains more information on the non-standardized,
 *  class-specific functions which the user application can then use on the driver instances, such as data
 *  read and write routines. See each driver's individual documentation for more information on the
 *  class-specific functions.
 *
 *  \subsection SSec_ClassDriverHost Host Mode Class Drivers
 *  Implementing a Host Mode Class Driver in a user application requires a number of steps to be followed. Firstly,
 *  the module configuration and state structure must be added to the project source. These structures are named in a 
 *  similar manner between classes, that of <i>USB_ClassInfo_<b>{Class Name}</b>_Host_t</i>, and are used to hold the
 *  complete state and configuration for each class instance. Multiple class instances is where the power of the class 
 *  drivers lie; multiple interfaces of the same class simply require more instances of the Class Driver's ClassInfo 
 *  structure.
 *
 *  Inside the ClassInfo structure lies two sections, a <i>Config</i> section, and a <i>State</i> section. The Config
 *  section contains the instance's configuration parameters, and <b>must have all fields set by the user application</b>
 *  before the class driver is used. Each Device mode Class driver typically contains a set of configuration parameters
 *  for the endpoint size/number of the associated logical USB interface, plus any class-specific configuration parameters.
 *
 *  The <i>State</i> section of the ClassInfo structures are designed to be controlled by the Class Drivers only for
 *  maintaining the Class Driver instance's state, and should not normally be set by the user application.
 *
 *  The following is an example of a properly initialized instance of the MIDI Class Driver structure:
 *
 *  \code
 *  USB_ClassInfo_MIDI_Host_t My_MIDI_Interface =
 *  {
 *      .Config =
 *          {
 *              .DataINPipeNumber       = 1,
 *              .DataINPipeDoubleBank   = false,
 *              
 *              .DataOUTPipeNumber      = 2,
 *              .DataOUTPipeDoubleBank  = false,
 *          },
 *  };
 *  \endcode
 *
 *  To initialize the Class driver instance, the driver's <i><b>{Class Name}</b>_Host_ConfigurePipes()</i> function
 *  should be called in response to the host state machine entering the \ref HOST_STATE_Addressed state. This function
 *  will return an error code from the class driver's <i><b>{Class Name}</b>_EnumerationFailure_ErrorCodes_t</i> enum
 *  to indicate if the driver sucessfully initialized the instance and bound it to an interface in the attached device.
 *  Like all the class driver functions, this function takes in the address of the specific instance you wish to initialize
 *  - in this manner, multiple seperate instances of the same class type can be initialized. A fragment of a Class Driver
 *  based Host mode application may look like the following:
 *
 *  \code
 *      switch (USB_HostState)
 *      {
 *          case HOST_STATE_Addressed:
 *              LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
 *          
 *              uint16_t ConfigDescriptorSize;
 *              uint8_t  ConfigDescriptorData[512];
 *
 *              if (USB_Host_GetDeviceConfigDescriptor(1, &ConfigDescriptorSize, ConfigDescriptorData,
 *                                                     sizeof(ConfigDescriptorData)) != HOST_GETCONFIG_Successful)
 *              {
 *                  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
 *                  USB_HostState = HOST_STATE_WaitForDeviceRemoval;
 *                  break;
 *              }
 *
 *              if (MIDI_Host_ConfigurePipes(&My_MIDI_Interface,
 *                                           ConfigDescriptorSize, ConfigDescriptorData) != MIDI_ENUMERROR_NoError)
 *              {
 *                  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
 *                  USB_HostState = HOST_STATE_WaitForDeviceRemoval;
 *                  break;
 *              }
 *
 *              // Other state handler code here
 *  \endcode
 *
 *  Note that the function also required the device's configuration descriptor so that it can determine which interface
 *  in the device to bind to - this can be retrieved as shown in the above fragment using the
 *  \ref USB_Host_GetDeviceConfigDescriptor() function. If the device does not implement the interface the class driver
 *  is looking for, if all the matching interfaces are already bound to class driver instances or if an error occurs while
 *  binding to a device interface (for example, a device endpoint bank larger that the maximum supported bank size is used)
 *  the configuration will fail.
 *
 *  Once initialized, it is important to maintain the class driver's state by repeatedly calling the Class Driver's
 *  <i><b>{Class Name}</b>_Host_USBTask()</i> function in the main program loop. The exact implementation of this
 *  function varies between class drivers, and can be used for any internal class driver purpose to maintain each
 *  instance. Again, this function uses the address of the instance to operate on, and thus needs to be called for each
 *  seperate instance, just like the main USB maintenance routine \ref USB_USBTask():
 *
 *  \code
 *  int main(void)
 *  {
 *      SetupHardware();
 *  
 *      LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
 *  
 *      for (;;)
 *      {
 *          switch (USB_HostState)
 *          {
 *             // Host state machine handling here
 *          } 
 *      
 *          MIDI_Host_USBTask(&My_Audio_Interface);
 *          USB_USBTask();
 *      }
 *  }
 *  \endcode
 *
 *  Each class driver may also define a set of callback functions (which are prefixed by "CALLBACK_"
 *  in the function's name) which <b>must</b> also be added to the user application - refer to each
 *  individual class driver's documentation for mandatory callbacks. In addition, each class driver may
 *  also define a set of events (identifiable by their prefix of "EVENT_" in the function's name), which
 *  the user application <b>may</b> choose to implement, or ignore if not needed.
 *
 *  The individual Host Mode Class Driver documentation contains more information on the non-standardized,
 *  class-specific functions which the user application can then use on the driver instances, such as data
 *  read and write routines. See each driver's individual documentation for more information on the
 *  class-specific functions.
 */
 
#ifndef __USB_H__
#define __USB_H__

	/* Macros: */
		#if !defined(__DOXYGEN__)
			#define __INCLUDE_FROM_USB_DRIVER
		#endif
		
	/* Includes: */
		#include "HighLevel/USBMode.h"

	/* Preprocessor Checks: */		
		#if (!defined(USB_SERIES_2_AVR) && !defined(USB_SERIES_4_AVR) && \
		     !defined(USB_SERIES_6_AVR) && !defined(USB_SERIES_7_AVR) && \
			 !defined(USB_SERIES_UC3B_AVR))
			#error The currently selected AVR model is not supported under the USB component of the LUFA library.
		#endif
		
	/* Includes: */
		#include "HighLevel/USBTask.h"
		#include "HighLevel/USBInterrupt.h"
		#include "HighLevel/Events.h"
		#include "HighLevel/StdDescriptors.h"

		#include "LowLevel/LowLevel.h"
	
		#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
			#include "LowLevel/Host.h"
			#include "LowLevel/HostChapter9.h"
			#include "LowLevel/Pipe.h"
		#endif
		
		#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
			#include "LowLevel/Device.h"
			#include "LowLevel/DevChapter9.h"
			#include "LowLevel/Endpoint.h"
		#endif
		
		#if defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__)
			#include "LowLevel/OTG.h"
		#endif
		
		#include "HighLevel/ConfigDescriptor.h"
		
#endif


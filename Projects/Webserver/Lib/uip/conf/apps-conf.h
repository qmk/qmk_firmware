#ifndef __APPS_CONF_H__
#define __APPS_CONF_H__

	#include <ff.h>

	typedef struct
	{
		uint8_t  CurrentState;
		uint8_t  NextState;
		
		char     FileName[30];
		FIL      FileHandle;
		bool     FileOpen;
		uint32_t ACKedFilePos;
		uint16_t SentChunkSize;
	} uip_tcp_appstate_t;

	typedef struct
	{
		uint8_t CurrentState;
		struct  uip_udp_conn* Connection;
		
		struct
		{
			uint8_t AllocatedIP[4];
			uint8_t Netmask[4];
			uint8_t GatewayIP[4];
			uint8_t ServerIP[4];
		} DHCPOffer_Data;
	} uip_udp_appstate_t;

	#define UIP_APPCALL     WebserverApp_Callback
	#define UIP_UDP_APPCALL DHCPApp_Callback
	void UIP_APPCALL(void);
	void UIP_UDP_APPCALL(void);

#endif /*__APPS_CONF_H__*/

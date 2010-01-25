#ifndef __APPS_CONF_H__
#define __APPS_CONF_H__

	enum Webserver_States_t
	{
		WEBSERVER_STATE_SendHeaders,
		WEBSERVER_STATE_SendData,
		WEBSERVER_STATE_Closed,
	};

	typedef struct
	{
		uint8_t CurrentState;
		char*   SendPos;
	} uip_tcp_appstate_t;

	#define UIP_APPCALL     WebserverApp_Callback
	void UIP_APPCALL(void);

#endif /*__APPS_CONF_H__*/

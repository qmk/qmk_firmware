/**
 * \addtogroup uip
 * @{
 */

/**
 * \defgroup uipopt Configuration options for uIP
 * @{
 *
 * uIP is configured using the per-project configuration file
 * "uipopt.h". This file contains all compile-time options for uIP and
 * should be tweaked to match each specific project. The uIP
 * distribution contains a documented example "uipopt.h" that can be
 * copied and modified for each project.
 */

/**
 * \file
 * Configuration options for uIP.
 * \author Adam Dunkels <adam@dunkels.com>
 *
 * This file is used for tweaking various configuration options for
 * uIP. You should make a copy of this file into one of your project's
 * directories instead of editing this example "uipopt.h" file that
 * comes with the uIP distribution.
 */

/*
 * Copyright (c) 2001-2003, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: uipopt.h,v 1.11 2009/04/10 00:37:48 adamdunkels Exp $
 *
 */

#ifndef __UIPOPT_H__
#define __UIPOPT_H__

#ifndef UIP_LITTLE_ENDIAN
#define UIP_LITTLE_ENDIAN  3412
#endif /* UIP_LITTLE_ENDIAN */
#ifndef UIP_BIG_ENDIAN
#define UIP_BIG_ENDIAN     1234
#endif /* UIP_BIG_ENDIAN */

/*------------------------------------------------------------------------------*/

/**
 * \defgroup uipoptstaticconf Static configuration options
 * @{
 *
 * These configuration options can be used for setting the IP address
 * settings statically, but only if UIP_FIXEDADDR is set to 1. The
 * configuration options for a specific node includes IP address,
 * netmask and default router as well as the Ethernet address. The
 * netmask, default router and Ethernet address are applicable only
 * if uIP should be run over Ethernet.
 *
 * This options are meaningful only for the IPv4 code.
 *
 * All of these should be changed to suit your project.
 */

/**
 * Determines if uIP should use a fixed IP address or not.
 *
 * If uIP should use a fixed IP address, the settings are set in the
 * uipopt.h file. If not, the macros uip_sethostaddr(),
 * uip_setdraddr() and uip_setnetmask() should be used instead.
 *
 * \hideinitializer
 */
#define UIP_FIXEDADDR    0

/**
 * Ping IP address assignment.
 *
 * uIP uses a "ping" packets for setting its own IP address if this
 * option is set. If so, uIP will start with an empty IP address and
 * the destination IP address of the first incoming "ping" (ICMP echo)
 * packet will be used for setting the hosts IP address.
 *
 * \note This works only if UIP_FIXEDADDR is 0.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_PINGADDRCONF
#define UIP_PINGADDRCONF UIP_CONF_PINGADDRCONF
#else /* UIP_CONF_PINGADDRCONF */
#define UIP_PINGADDRCONF 0
#endif /* UIP_CONF_PINGADDRCONF */


/**
 * Specifies if the uIP ARP module should be compiled with a fixed
 * Ethernet MAC address or not.
 *
 * If this configuration option is 0, the macro uip_setethaddr() can
 * be used to specify the Ethernet address at run-time.
 *
 * \hideinitializer
 */
#define UIP_FIXEDETHADDR 0

/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \defgroup uipoptip IP configuration options
 * @{
 *
 */
/**
 * The IP TTL (time to live) of IP packets sent by uIP.
 *
 * This should normally not be changed.
 */
#define UIP_TTL         64

/**
 * The maximum time an IP fragment should wait in the reassembly
 * buffer before it is dropped.
 *
 */
#define UIP_REASS_MAXAGE 60 /*60s*/

/**
 * Turn on support for IP packet reassembly.
 *
 * uIP supports reassembly of fragmented IP packets. This features
 * requires an additional amount of RAM to hold the reassembly buffer
 * and the reassembly code size is approximately 700 bytes.  The
 * reassembly buffer is of the same size as the uip_buf buffer
 * (configured by UIP_BUFSIZE).
 *
 * \note IP packet reassembly is not heavily tested.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_REASSEMBLY
#define UIP_REASSEMBLY UIP_CONF_REASSEMBLY
#else /* UIP_CONF_REASSEMBLY */
#define UIP_REASSEMBLY 0
#endif /* UIP_CONF_REASSEMBLY */
/** @} */

/*------------------------------------------------------------------------------*/
/**
 * \defgroup uipoptipv6 IPv6 configuration options
 * @{
 *
 */

/** The maximum transmission unit at the IP Layer*/
#define UIP_LINK_MTU 1280

#ifndef UIP_CONF_IPV6
/** Do we use IPv6 or not (default: no) */
#define UIP_CONF_IPV6                 0
#endif

#ifndef UIP_CONF_IPV6_QUEUE_PKT
/** Do we do per %neighbor queuing during address resolution (default: no) */
#define UIP_CONF_IPV6_QUEUE_PKT       0
#endif

#ifndef UIP_CONF_IPV6_CHECKS 
/** Do we do IPv6 consistency checks (highly recommended, default: yes) */
#define UIP_CONF_IPV6_CHECKS          1
#endif

#ifndef UIP_CONF_IPV6_REASSEMBLY 
/** Do we do IPv6 fragmentation (default: no) */
#define UIP_CONF_IPV6_REASSEMBLY      0
#endif

#ifndef UIP_CONF_NETIF_MAX_ADDRESSES
/** Default number of IPv6 addresses associated to the node's interface */
#define UIP_CONF_NETIF_MAX_ADDRESSES  3
#endif

#ifndef UIP_CONF_ND6_MAX_PREFIXES 
/** Default number of IPv6 prefixes associated to the node's interface */
#define UIP_CONF_ND6_MAX_PREFIXES     3
#endif

#ifndef UIP_CONF_ND6_MAX_NEIGHBORS 
/** Default number of neighbors that can be stored in the %neighbor cache */
#define UIP_CONF_ND6_MAX_NEIGHBORS    4  
#endif

#ifndef UIP_CONF_ND6_MAX_DEFROUTERS
/** Minimum number of default routers */
#define UIP_CONF_ND6_MAX_DEFROUTERS   2
#endif
/** @} */

/*------------------------------------------------------------------------------*/
/**
 * \defgroup uipoptudp UDP configuration options
 * @{
 *
 * \note The UDP support in uIP is still not entirely complete; there
 * is no support for sending or receiving broadcast or multicast
 * packets, but it works well enough to support a number of vital
 * applications such as DNS queries, though
 */

/**
 * Toggles whether UDP support should be compiled in or not.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP
#define UIP_UDP UIP_CONF_UDP
#else /* UIP_CONF_UDP */
#define UIP_UDP           1
#endif /* UIP_CONF_UDP */

/**
 * Toggles if UDP checksums should be used or not.
 *
 * \note Support for UDP checksums is currently not included in uIP,
 * so this option has no function.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP_CHECKSUMS
#define UIP_UDP_CHECKSUMS UIP_CONF_UDP_CHECKSUMS
#else
#define UIP_UDP_CHECKSUMS 0
#endif

/**
 * The maximum amount of concurrent UDP connections.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_UDP_CONNS
#define UIP_UDP_CONNS UIP_CONF_UDP_CONNS
#else /* UIP_CONF_UDP_CONNS */
#define UIP_UDP_CONNS    10
#endif /* UIP_CONF_UDP_CONNS */

/**
 * The name of the function that should be called when UDP datagrams arrive.
 *
 * \hideinitializer
 */


/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \defgroup uipopttcp TCP configuration options
 * @{
 */

/**
 * Toggles whether UDP support should be compiled in or not.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_TCP
#define UIP_TCP UIP_CONF_TCP
#else /* UIP_CONF_UDP */
#define UIP_TCP           1
#endif /* UIP_CONF_UDP */

/**
 * Determines if support for opening connections from uIP should be
 * compiled in.
 *
 * If the applications that are running on top of uIP for this project
 * do not need to open outgoing TCP connections, this configuration
 * option can be turned off to reduce the code size of uIP.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_ACTIVE_OPEN
#define UIP_ACTIVE_OPEN 1
#else /* UIP_CONF_ACTIVE_OPEN */
#define UIP_ACTIVE_OPEN UIP_CONF_ACTIVE_OPEN
#endif /* UIP_CONF_ACTIVE_OPEN */

/**
 * The maximum number of simultaneously open TCP connections.
 *
 * Since the TCP connections are statically allocated, turning this
 * configuration knob down results in less RAM used. Each TCP
 * connection requires approximately 30 bytes of memory.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_MAX_CONNECTIONS
#define UIP_CONNS       10
#else /* UIP_CONF_MAX_CONNECTIONS */
#define UIP_CONNS UIP_CONF_MAX_CONNECTIONS
#endif /* UIP_CONF_MAX_CONNECTIONS */


/**
 * The maximum number of simultaneously listening TCP ports.
 *
 * Each listening TCP port requires 2 bytes of memory.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_MAX_LISTENPORTS
#define UIP_LISTENPORTS 20
#else /* UIP_CONF_MAX_LISTENPORTS */
#define UIP_LISTENPORTS UIP_CONF_MAX_LISTENPORTS
#endif /* UIP_CONF_MAX_LISTENPORTS */

/**
 * Determines if support for TCP urgent data notification should be
 * compiled in.
 *
 * Urgent data (out-of-band data) is a rarely used TCP feature that
 * very seldom would be required.
 *
 * \hideinitializer
 */
#define UIP_URGDATA      0

/**
 * The initial retransmission timeout counted in timer pulses.
 *
 * This should not be changed.
 */
#define UIP_RTO         3

/**
 * The maximum number of times a segment should be retransmitted
 * before the connection should be aborted.
 *
 * This should not be changed.
 */
#define UIP_MAXRTX      8

/**
 * The maximum number of times a SYN segment should be retransmitted
 * before a connection request should be deemed to have been
 * unsuccessful.
 *
 * This should not need to be changed.
 */
#define UIP_MAXSYNRTX      5

/**
 * The TCP maximum segment size.
 *
 * This is should not be to set to more than
 * UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN.
 */
#ifdef UIP_CONF_TCP_MSS
#define UIP_TCP_MSS UIP_CONF_TCP_MSS
#else
#define UIP_TCP_MSS     (UIP_BUFSIZE - UIP_LLH_LEN - UIP_TCPIP_HLEN)
#endif

/**
 * The size of the advertised receiver's window.
 *
 * Should be set low (i.e., to the size of the uip_buf buffer) if the
 * application is slow to process incoming data, or high (32768 bytes)
 * if the application processes data quickly.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_RECEIVE_WINDOW
#define UIP_RECEIVE_WINDOW UIP_TCP_MSS
#else
#define UIP_RECEIVE_WINDOW UIP_CONF_RECEIVE_WINDOW
#endif

/**
 * How long a connection should stay in the TIME_WAIT state.
 *
 * This configuration option has no real implication, and it should be
 * left untouched.
 */
#define UIP_TIME_WAIT_TIMEOUT 120


/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \defgroup uipoptarp ARP configuration options
 * @{
 */

/**
 * The size of the ARP table.
 *
 * This option should be set to a larger value if this uIP node will
 * have many connections from the local network.
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_ARPTAB_SIZE
#define UIP_ARPTAB_SIZE UIP_CONF_ARPTAB_SIZE
#else
#define UIP_ARPTAB_SIZE 8
#endif

/**
 * The maximum age of ARP table entries measured in 10ths of seconds.
 *
 * An UIP_ARP_MAXAGE of 120 corresponds to 20 minutes (BSD
 * default).
 */
#define UIP_ARP_MAXAGE 120


/** @} */

/*------------------------------------------------------------------------------*/

/**
 * \defgroup uipoptmac layer 2 options (for ipv6)
 * @{
 */

#define UIP_DEFAULT_PREFIX_LEN 64

/** @} */

/*------------------------------------------------------------------------------*/

/**
 * \defgroup uipoptsics 6lowpan options (for ipv6)
 * @{
 */
/**
 * Timeout for packet reassembly at the 6lowpan layer
 * (should be < 60s)
 */
#ifdef SICSLOWPAN_CONF_MAXAGE
#define SICSLOWPAN_REASS_MAXAGE SICSLOWPAN_CONF_MAXAGE
#else
#define SICSLOWPAN_REASS_MAXAGE 20
#endif

/**
 * Do we compress the IP header or not (default: no)
 */
#ifndef SICSLOWPAN_CONF_COMPRESSION
#define SICSLOWPAN_CONF_COMPRESSION 0
#endif

/**
 * If we use IPHC compression, how many address contexts do we support
 */
#ifndef SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS 
#define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS 1
#endif

/**
 * Do we support 6lowpan fragmentation
 */
#ifndef SICSLOWPAN_CONF_FRAG  
#define SICSLOWPAN_CONF_FRAG  0
#endif

/** @} */

/*------------------------------------------------------------------------------*/

/**
 * \defgroup uipoptgeneral General configuration options
 * @{
 */

/**
 * The size of the uIP packet buffer.
 *
 * The uIP packet buffer should not be smaller than 60 bytes, and does
 * not need to be larger than 1514 bytes. Lower size results in lower
 * TCP throughput, larger size results in higher TCP throughput.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_BUFFER_SIZE
#define UIP_BUFSIZE UIP_LINK_MTU + UIP_LLH_LEN
#else /* UIP_CONF_BUFFER_SIZE */
#define UIP_BUFSIZE UIP_CONF_BUFFER_SIZE
#endif /* UIP_CONF_BUFFER_SIZE */


/**
 * Determines if statistics support should be compiled in.
 *
 * The statistics is useful for debugging and to show the user.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_STATISTICS
#define UIP_STATISTICS  0
#else /* UIP_CONF_STATISTICS */
#define UIP_STATISTICS UIP_CONF_STATISTICS
#endif /* UIP_CONF_STATISTICS */

/**
 * Determines if logging of certain events should be compiled in.
 *
 * This is useful mostly for debugging. The function uip_log()
 * must be implemented to suit the architecture of the project, if
 * logging is turned on.
 *
 * \hideinitializer
 */
#ifndef UIP_CONF_LOGGING
#define UIP_LOGGING     0
#else /* UIP_CONF_LOGGING */
#define UIP_LOGGING     UIP_CONF_LOGGING
#endif /* UIP_CONF_LOGGING */

/**
 * Broadcast support.
 *
 * This flag configures IP broadcast support. This is useful only
 * together with UDP.
 *
 * \hideinitializer
 *
 */
#ifndef UIP_CONF_BROADCAST
#define UIP_BROADCAST 0
#else /* UIP_CONF_BROADCAST */
#define UIP_BROADCAST UIP_CONF_BROADCAST
#endif /* UIP_CONF_BROADCAST */

/**
 * Print out a uIP log message.
 *
 * This function must be implemented by the module that uses uIP, and
 * is called by uIP whenever a log message is generated.
 */
void uip_log(char *msg);

/**
 * The link level header length.
 *
 * This is the offset into the uip_buf where the IP header can be
 * found. For Ethernet, this should be set to 14. For SLIP, this
 * should be set to 0.
 *
 * \note we probably won't use this constant for other link layers than
 * ethernet as they have variable header length (this is due to variable
 * number and type of address fields and to optional security features)
 * E.g.: 802.15.4 -> 2 + (1/2*4/8) + 0/5/6/10/14
 *       802.11 -> 4 + (6*3/4) + 2
 * \hideinitializer
 */
#ifdef UIP_CONF_LLH_LEN
#define UIP_LLH_LEN UIP_CONF_LLH_LEN
#else /* UIP_LLH_LEN */
#define UIP_LLH_LEN     14
#endif /* UIP_CONF_LLH_LEN */

/** @} */
/*------------------------------------------------------------------------------*/
/**
 * \defgroup uipoptcpu CPU architecture configuration
 * @{
 *
 * The CPU architecture configuration is where the endianess of the
 * CPU on which uIP is to be run is specified. Most CPUs today are
 * little endian, and the most notable exception are the Motorolas
 * which are big endian. The BYTE_ORDER macro should be changed to
 * reflect the CPU architecture on which uIP is to be run.
 */

/**
 * The byte order of the CPU architecture on which uIP is to be run.
 *
 * This option can be either UIP_BIG_ENDIAN (Motorola byte order) or
 * UIP_LITTLE_ENDIAN (Intel byte order).
 *
 * \hideinitializer
 */
#ifdef UIP_CONF_BYTE_ORDER
#define UIP_BYTE_ORDER     UIP_CONF_BYTE_ORDER
#else /* UIP_CONF_BYTE_ORDER */
#define UIP_BYTE_ORDER     UIP_LITTLE_ENDIAN
#endif /* UIP_CONF_BYTE_ORDER */

/** @} */
/*------------------------------------------------------------------------------*/

#include <ff.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint32_t uip_stats_t;

/**
 * \defgroup uipoptapp Application specific configurations
 * @{
 *
 * An uIP application is implemented using a single application
 * function that is called by uIP whenever a TCP/IP event occurs. The
 * name of this function must be registered with uIP at compile time
 * using the UIP_APPCALL definition.
 *
 * uIP applications can store the application state within the
 * uip_conn structure by specifying the type of the application
 * structure by typedef:ing the type uip_tcp_appstate_t and uip_udp_appstate_t.
 *
 * The file containing the definitions must be included in the
 * uipopt.h file.
 *
 * The following example illustrates how this can look.
 \code

 void httpd_appcall(void);
 #define UIP_APPCALL     httpd_appcall

 struct httpd_state {
 u8_t state;
 u16_t count;
 char *dataptr;
 char *script;
 };
 typedef struct httpd_state uip_tcp_appstate_t
 \endcode
*/
#define UIP_UDP_APPCALL DHCPApp_Callback
void UIP_UDP_APPCALL(void);

/**
 * \var #define UIP_APPCALL
 *
 * The name of the application function that uIP should call in
 * response to TCP/IP events.
 *
 */
#define UIP_APPCALL     HTTPServerApp_Callback
void UIP_APPCALL(void);

/**
 * \var typedef uip_tcp_appstate_t
 *
 * The type of the application state that is to be stored in the
 * uip_conn structure. This usually is typedef:ed to a struct holding
 * application state information.
 */
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

/**
 * \var typedef uip_udp_appstate_t
 *
 * The type of the application state that is to be stored in the
 * uip_conn structure. This usually is typedef:ed to a struct holding
 * application state information.
 */
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
/** @} */

#endif /* __UIPOPT_H__ */
/** @} */
/** @} */

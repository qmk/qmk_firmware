/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_ENET_DRIVER_H__
#define __FSL_ENET_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_enet_hal.h"
#include "fsl_os_abstraction.h"

#ifndef MBED_NO_ENET

/*!
 * @addtogroup enet_driver
 * @{
 */

/*******************************************************************************
 * Definitions

 ******************************************************************************/
/*! @brief Defines the approach: ENET interrupt handler do receive */
#define ENET_RECEIVE_ALL_INTERRUPT  0

/*! @brief Defines the statistic enable macro.*/
#define ENET_ENABLE_DETAIL_STATS    0

/*! @brief Defines the alignment operation.*/
#define ENET_ALIGN(x,align)        ((unsigned int)((x) + ((align)-1)) & (unsigned int)(~(unsigned int)((align)- 1)))

#if FSL_FEATURE_ENET_SUPPORT_PTP
/*! @brief Defines the PTP IOCTL macro.*/
typedef enum _enet_ptp_ioctl
{
    kEnetPtpGetRxTimestamp = 0,    /*!< ENET PTP gets receive timestamp*/
    kEnetPtpGetTxTimestamp,        /*!< ENET PTP gets transmit timestamp*/
    kEnetPtpGetCurrentTime,        /*!< ENET PTP gets current time*/
    kEnetPtpSetCurrentTime,        /*!< ENET PTP sets current time*/
    kEnetPtpFlushTimestamp,        /*!< ENET PTP flushes timestamp*/
    kEnetPtpCorrectTime,           /*!< ENET PTP time correction*/
    kEnetPtpSendEthernetPtpV2,     /*!< ENET PTPv2 sends Ethernet frame*/
    kEnetPtpReceiveEthernetPtpV2   /*!< ENET PTPv2 receives with Ethernet frame*/
} enet_ptp_ioctl_t;

/*! @brief Defines the PTP message buffer number.*/
typedef enum _enet_ptp_buffer_number
{
    kEnetPtpL2bufferNumber = 10,  /*!< PTP layer2 frame buffer number*/
    kEnetPtpRingNumber = 25       /*!< PTP Ring buffer number*/
} enet_ptp_buffer_number_t;

/*! @brief Defines the ENET PTP message related constant.*/
typedef enum _enet_ptp_event_type
{
     kEnetPtpSourcePortIdLen = 10,  /*!< PTP message sequence id length*/
     kEnetPtpEventMsgType = 3,      /*!< PTP event message type*/
     kEnetPtpEventPort = 319,       /*!< PTP event port number*/
     kEnetPtpGnrlPort = 320         /*!< PTP general port number*/
} enet_ptp_event_type_t;

/*! @brief Defines all ENET PTP content offsets in the IPv4 PTP UDP/IP multicast message.*/
typedef enum _enet_ipv4_ptp_content_offset
{
    kEnetPtpIpVersionOffset = 0xe,   /*!< IPv4 PTP message IP version offset*/
    kEnetPtpUdpProtocolOffset = 0x17,/*!< IPv4 PTP message UDP protocol offset*/
    kEnetPtpUdpPortOffset = 0x24,    /*!< IPv4 PTP message UDP port offset*/
    kEnetPtpUdpMsgTypeOffset = 0x2a, /*!< IPv4 PTP message UDP message type offset*/
    kEnetPtpUdpVersionoffset = 0x2b, /*!< IPv4 PTP message UDP version offset*/
    kEnetPtpUdpClockIdOffset = 0x3e, /*!< IPv4 PTP message UDP clock id offset*/
    kEnetPtpUdpSequenIdOffset = 0x48,/*!< IPv4 PTP message UDP sequence id offset*/
    kEnetPtpUdpCtlOffset = 0x4a      /*!< IPv4 PTP message UDP control offset*/
} enet_ipv4_ptp_content_offset_t;

/*! @brief Defines all ENET PTP content offset in THE IPv6 PTP UDP/IP multicast message.*/
typedef enum _enet_ipv6_ptp_content_offset
{
    kEnetPtpIpv6UdpProtocolOffset = 0x14,  /*!< IPv6 PTP message UDP protocol offset*/
    kEnetPtpIpv6UdpPortOffset = 0x38,      /*!< IPv6 PTP message UDP port offset*/
    kEnetPtpIpv6UdpMsgTypeOffset = 0x3e,   /*!< IPv6 PTP message UDP message type offset*/
    kEnetPtpIpv6UdpVersionOffset = 0x3f,   /*!< IPv6 PTP message UDP version offset*/
    kEnetPtpIpv6UdpClockIdOffset = 0x52,   /*!< IPv6 PTP message UDP clock id offset*/
    kEnetPtpIpv6UdpSequenceIdOffset = 0x5c,/*!< IPv6 PTP message UDP sequence id offset*/
    kEnetPtpIpv6UdpCtlOffset = 0x5e        /*!< IPv6 PTP message UDP control offset*/
} enet_ipv6_ptp_content_offset_t;

/*! @brief Defines all ENET PTP content offset in the PTP Layer2 Ethernet message.*/
typedef enum _enet_ethernet_ptp_content_offset
{
    kEnetPtpEtherPktTypeOffset = 0x0c,   /*!< PTPv2 message Ethernet packet type offset*/
    kEnetPtpEtherMsgTypeOffset = 0x0e,   /*!< PTPv2 message Ethernet message type offset*/
    kEnetPtpEtherVersionOffset = 0x0f,   /*!< PTPv2 message Ethernet version type offset*/
    kEnetPtpEtherClockIdOffset = 0x22,   /*!< PTPv2 message Ethernet clock id offset*/
    kEnetPtpEtherSequenceIdOffset = 0x2c,/*!< PTPv2 message Ethernet sequence id offset*/
    kEnetPtpEtherCtlOffset = 0x2e        /*!< PTPv2 message Ethernet control offset*/
} enet_ethernet_ptp_content_offset_t;

/*! @brief Defines the 1588 timer parameters.*/
typedef enum _enet_ptp_timer_wrap_period
{
    kEnetPtpAtperVaule = 1000000000, /*!< PTP timer wrap around one second */
    kEnetBaseIncreaseUnit = 2        /*!< PTP timer adjusts clock and increases value to 2*/
} enet_ptp_timer_wrap_period_t;
#endif

/*! @brief Defines the interrupt source index for the interrupt vector change table.*/
typedef enum _enet_interrupt_number
{
    kEnetTstimerInt = 0, /*!< Timestamp interrupt*/
    kEnetTsAvailInt, /*!< TS-avail interrupt*/
    kEnetWakeUpInt,  /*!< Wakeup interrupt*/
    kEnetPlrInt,     /*!< Plr interrupt*/
    kEnetUnInt,      /*!< Un interrupt*/
    kEnetRlInt,      /*!< RL interrupt*/
    kEnetLcInt,      /*!< LC interrupt*/
    kEnetEberrInt,   /*!< Eberr interrupt*/
    kEnetMiiInt,     /*!< MII interrupt*/
    kEnetRxbInt ,    /*!< Receive byte interrupt*/
    kEnetRxfInt,    /*!< Receive frame interrupt*/
    kEnetTxbInt,    /*!< Transmit byte interrupt*/
    kEnetTxfInt,    /*!< Transmit frame interrupt*/
    kEnetGraInt,    /*!< Gra interrupt*/
    kEnetBabtInt,   /*!< Babt interrupt*/
    kEnetBabrInt,   /*!< Babr interrupt*/
    kEnetIntNum     /*!< Interrupt number*/
} enet_interrupt_number_t;

/*! @brief Defines the ENET main constant.*/
typedef enum _enet_frame_max
{
    kEnetMaxTimeout = 0x10000,    /*!< Maximum timeout*/
    kEnetMaxFrameSize = 1518,     /*!< Maximum frame size*/
    kEnetMaxFrameVlanSize = 1522, /*!< Maximum VLAN frame size*/
    kEnetMaxFrameDateSize = 1500, /*!< Maximum frame data size*/
    kEnetMaxFrameBdNumbers = 7,   /*!< Maximum buffer descriptor numbers of a frame*/
    kEnetFrameFcsLen = 4,         /*!< FCS length*/
    kEnetEthernetHeadLen = 14     /*!< Ethernet Frame header length*/
} enet_frame_max_t;

/*! @brief Defines the CRC data for a hash value calculation.*/
typedef enum _enet_crc_parameter
{
    kEnetCrcData = 0xFFFFFFFFU,  /*!< CRC-32 maximum data */
    kEnetCrcOffset = 8,          /*!< CRC-32 offset2*/
    kEnetCrcMask1 = 0x3F         /*!< CRC-32 mask*/
} enet_crc_parameter_t;

/*! @brief Defines the ENET protocol type and main parameters.*/
typedef enum _enet_protocol_type
{
    kEnetProtocolIeee8023 = 0x88F7,  /*!< Packet type Ethernet ieee802.3*/
    kEnetProtocolIpv4 = 0x0800,      /*!< Packet type IPv4*/
    kEnetProtocolIpv6 = 0x86dd,      /*!< Packet type IPv6*/
    kEnetProtocol8021QVlan = 0x8100, /*!< Packet type VLAN*/
    kEnetPacketUdpVersion = 0x11,    /*!< UDP protocol type*/
    kEnetPacketIpv4Version = 0x4,    /*!< Packet IP version IPv4*/
    kEnetPacketIpv6Version = 0x6     /*!< Packet IP version IPv6*/
} enet_protocol_type_t;

/*! @brief Defines the ENET MAC control Configure*/
typedef enum _enet_mac_control_flag
{
    kEnetSleepModeEnable = 0x1, /*!< ENET control sleep mode Enable*/
    kEnetPayloadlenCheckEnable = 0x2, /*!< ENET receive payload length check Enable*/
    kEnetRxFlowControlEnable = 0x4, /*!< ENET flow control, receiver detects PAUSE frames and stops transmitting data when a PAUSE frame is detected*/
    kEnetRxCrcFwdEnable = 0x8, /*!< Received frame crc is stripped from the frame*/
    kEnetRxPauseFwdEnable = 0x10,/*!< Pause frames are forwarded to the user application*/
    kEnetRxPadRemoveEnable = 0x20, /*!< Padding is removed from received frames*/
    kEnetRxBcRejectEnable = 0x40, /*!< Broadcast frame reject*/
    kEnetRxPromiscuousEnable = 0x80, /*!< Promiscuous mode enabled*/
    kEnetRxMiiLoopback = 0x100, /*!< MAC MII loopback mode*/
} enet_mac_control_flag_t;

/*! @brief Defines the multicast group structure for the ENET device. */
typedef struct ENETMulticastGroup
{
    enetMacAddr groupAdddr;        /*!< Multicast group address*/
    uint32_t hash;                 /*!< Hash value of the multicast group address*/
    struct ENETMulticastGroup *next; /*!< Pointer of the next group structure*/
    struct ENETMulticastGroup *prv;  /*!< Pointer of the previous structure*/
} enet_multicast_group_t;

/*! @brief Defines the receive buffer descriptor configure structure.*/
typedef struct ENETRxBdConfig
{
    uint8_t *rxBdPtrAlign;      /*!< Aligned receive buffer descriptor pointer */
    uint8_t *rxBufferAlign;     /*!< Aligned receive data buffer pointer */
    uint8_t *rxLargeBufferAlign; /*!< Aligned receive large data buffer pointer*/
    uint8_t rxBdNum;             /*!< Aligned receive buffer descriptor pointer*/
    uint8_t rxBufferNum;         /*!< Receive buffer number*/
    uint8_t rxLargeBufferNum;    /*!< Large receive buffer number*/
    uint32_t rxLargeBufferSizeAlign; /*!< Aligned large receive buffer size*/
}enet_rxbd_config_t;

/*! @brief Defines the transmit buffer descriptor configure structure.*/
typedef struct ENETTxBdConfig
{
    uint8_t *txBdPtrAlign;      /*!< Aligned transmit buffer descriptor pointer*/
    uint8_t *txBufferAlign;     /*!< Aligned transmit buffer descriptor pointer*/
    uint8_t txBufferNum;         /*!< Transmit buffer number*/
    uint32_t txBufferSizeAlign;  /*!< Aligned transmit buffer size*/
}enet_txbd_config_t;

/*! @brief Defines the basic configuration structure for the ENET device.*/
typedef struct ENETMacConfig
{
    uint16_t rxBufferSize;  /*!< Receive buffer size*/
    uint16_t rxLargeBufferNumber; /*!< Receive large buffer number; Needed only when the BD size is smaller than the maximum frame length.*/
    uint16_t rxBdNumber;    /*!< Receive buffer descriptor number*/
    uint16_t txBdNumber;    /*!< Transmit buffer descriptor number*/
    enetMacAddr macAddr;    /*!< MAC hardware address*/
    enet_config_rmii_t rmiiCfgMode;/*!< RMII configure mode*/
    enet_config_speed_t speed;     /*!< Speed configuration*/
    enet_config_duplex_t duplex;   /*!< Duplex configuration*/
    /*!< Mac control configure, it is recommended to use enet_mac_control_flag_t
       it is special control set for loop mode, sleep mode, crc forward/terminate etc*/
    uint32_t macCtlConfigure; 
    bool isTxAccelEnabled;/*!< Switcher to enable transmit accelerator*/
    bool isRxAccelEnabled;/*!< Switcher to enable receive accelerator*/
    bool isStoreAndFwEnabled;  /*!< Switcher to enable store and forward*/
    enet_config_rx_accelerator_t rxAcceler; /*!< Receive accelerator configure*/
    enet_config_tx_accelerator_t txAcceler; /*!< Transmit accelerator configure*/
    bool isVlanEnabled;    /*!< Switcher to enable VLAN frame*/
    bool isPhyAutoDiscover;/*!< Switcher to use PHY auto discover*/
    uint32_t miiClock;     /*!< MII speed*/
#if FSL_FEATURE_ENET_SUPPORT_PTP
    uint16_t ptpRingBufferNumber; /*!< PTP ring buffer number*/
    bool isSlaveModeEnabled;      /*!< PTP timer configuration*/
#endif
} enet_mac_config_t;

/*! @brief Defines the basic configuration for PHY.*/
typedef struct ENETPhyConfig
{
    uint8_t phyAddr;    /*!< PHY address*/
    bool isLoopEnabled; /*!< Switcher to enable the HY loop mode*/
} enet_phy_config_t;

#if FSL_FEATURE_ENET_SUPPORT_PTP
/*! @brief Defines the  ENET Mac PTP timestamp structure.*/
typedef struct ENETMacPtpTime
{
    uint64_t second;     /*!< Second*/
    uint32_t nanosecond; /*!< Nanosecond*/
} enet_mac_ptp_time_t;

/*! @brief Defines the ENET PTP timer drift structure.*/
typedef struct ENETPtpDrift
{
    int32_t drift;    /*!< Drift for the PTP timer to adjust*/
} enet_ptp_drift_t;

/*! @brief Defines the ENET MAC PTP time parameter.*/
typedef struct ENETPtpMasterTimeData
{
    uint8_t masterPtpInstance;/*!< PTP master timer instance*/
    uint64_t second;          /*!< PTP master timer second */
} enet_ptp_master_time_data_t;

/*! @brief Defines the structure for the ENET PTP message data and timestamp data.*/
typedef struct ENETMacPtpTsData
{
    uint8_t version;              /*!< PTP version*/
    uint8_t sourcePortId[kEnetPtpSourcePortIdLen];/*!< PTP source port ID*/
    uint16_t sequenceId;          /*!< PTP sequence ID*/
    uint8_t messageType;          /*!< PTP message type*/
    enet_mac_ptp_time_t timeStamp;/*!< PTP timestamp*/
} enet_mac_ptp_ts_data_t;

/*! @brief Defines the ENET PTP ring buffer structure for the PTP message timestamp store.*/
typedef struct ENETMacPtpTsRing
{
    uint32_t front; /*!< The first index of the ring*/
    uint32_t end;   /*!< The end index of the ring*/
    uint32_t size;  /*!< The size of the ring*/
    enet_mac_ptp_ts_data_t *ptpTsDataPtr;/*!< PTP message data structure*/
} enet_mac_ptp_ts_ring_t;

/*! @brief Defines the ENET packet for the PTP version2 message using the layer2 Ethernet frame.*/
typedef struct ENETPtpL2packet
{
    uint8_t packet[kEnetMaxFrameDateSize]; /*!< Buffer for ptpv2 message*/
    uint16_t length;                       /*!< PTP message length*/
} enet_ptp_l2packet_t;

/*! @brief Defines the ENET PTPv2 packet queue using the layer2 Ethernet frame.*/
typedef struct ENETPtpL2queue
{
    enet_ptp_l2packet_t l2Packet[kEnetPtpL2bufferNumber]; /*!< PTP layer2 packet*/
    uint16_t writeIdex;          /*!< Queue write index*/
    uint16_t readIdx;            /*!< Queue read index*/
} enet_ptp_l2queue_t;

/*! @brief Defines the ENET PTP layer2 Ethernet frame structure.*/
typedef struct ENETPtpL2Ethernet
{
    uint8_t *ptpMsg;     /*!< PTP message*/
    uint16_t length;     /*!< Length of the PTP message*/
    enetMacAddr hwAddr;  /*!< Destination hardware address*/
} enet_ptp_l2_ethernet_t;

/*! @brief Defines the ENET PTP buffer structure for all 1588 data.*/
typedef struct ENETPrivatePtpBuffer
{
    enet_mac_ptp_ts_ring_t rxTimeStamp;/*!< Data structure for receive message*/
    enet_mac_ptp_ts_ring_t txTimeStamp;/*!< Data structure for transmit timestamp*/
    enet_ptp_l2queue_t *l2QueuePtr;    /*!< Data structure for layer2 Ethernet queue*/
    uint64_t masterSecond;             /*!< PTP time second when it's master time*/
} enet_private_ptp_buffer_t;
#endif

/*! @brief Defines the ENET header structure. */
typedef struct ENETEthernetHeader
{
    enetMacAddr destAddr;  /*!< Destination address */
    enetMacAddr sourceAddr;/*!< Source address*/
    uint16_t type;         /*!< Protocol type*/
} enet_ethernet_header_t;

/*! @brief Defines the ENET VLAN frame header structure. */
typedef struct ENET8021vlanHeader
{
    enetMacAddr destAddr;  /*!< Destination address */
    enetMacAddr sourceAddr;/*!< Source address*/
    uint16_t tpidtag;      /*!< ENET 8021tag header tag region*/
    uint16_t othertag;     /*!< ENET 8021tag header type region*/
    uint16_t type;         /*!< Protocol type*/
} enet_8021vlan_header_t;

/*! @brief Defines the ENET MAC context structure for the buffer address, buffer descriptor address, etc.*/
typedef struct ENETMacContext
{
    uint8_t *rxBufferPtr;   /*!< Receive buffer pointer*/
    uint8_t *rxLargeBufferPtr; /*!< Receive large buffer descriptor*/
    uint8_t *txBufferPtr;   /*!< Transmit buffer pointer*/
    uint8_t *rxBdBasePtr;   /*!< Receive buffer descriptor base address pointer*/
    uint8_t *rxBdCurPtr;    /*!< Current receive buffer descriptor pointer*/
    uint8_t *rxBdDirtyPtr;  /*!< Receive dirty buffer descriptor*/
    uint8_t *txBdBasePtr;   /*!< Transmit buffer descriptor base address pointer*/
    uint8_t *txBdCurPtr;    /*!< Current transmit buffer descriptor pointer*/
    uint8_t *txBdDirtyPtr;  /*!< Last cleaned transmit buffer descriptor pointer*/
    bool  isTxFull;         /*!< Transmit buffer descriptor full*/
    bool  isRxFull;         /*!< Receive buffer descriptor full*/
    uint32_t bufferdescSize;         /*!< ENET buffer descriptor size*/
    uint16_t rxBufferSizeAligned;      /*!< Receive buffer alignment size*/
#if FSL_FEATURE_ENET_SUPPORT_PTP
    enet_private_ptp_buffer_t privatePtp;/*!< PTP private buffer*/
#endif
} enet_mac_context_t;

/*! @brief Defines the ENET packets statistic structure.*/
typedef struct ENETMacStats
{
    uint32_t statsRxTotal;   /*!< Total number of receive packets*/
    uint32_t statsRxMissed;  /*!< Total number of receive packets*/
    uint32_t statsRxDiscard; /*!< Receive discarded with error */
    uint32_t statsRxError;   /*!< Receive discarded with error packets*/
    uint32_t statsTxTotal;   /*!< Total number of transmit packets*/
    uint32_t statsTxMissed;  /*!< Transmit missed*/
    uint32_t statsTxDiscard; /*!< Transmit discarded with error */
    uint32_t statsTxError;   /*!< Transmit error*/
    uint32_t statsRxAlign;   /*!< Receive non-octet alignment*/
    uint32_t statsRxFcs;     /*!< Receive CRC error*/
    uint32_t statsRxTruncate;/*!< Receive truncate*/
    uint32_t statsRxLengthGreater;  /*!< Receive length greater than RCR[MAX_FL] */
    uint32_t statsRxCollision;      /*!< Receive collision*/
    uint32_t statsRxOverRun;        /*!< Receive over run*/
    uint32_t statsTxOverFlow;       /*!< Transmit overflow*/
    uint32_t statsTxLateCollision;  /*!< Transmit late collision*/
    uint32_t statsTxExcessCollision;/*!< Transmit excess collision*/
    uint32_t statsTxUnderFlow;      /*!< Transmit under flow*/
    uint32_t statsTxLarge;          /*!< Transmit large packet*/
    uint32_t statsTxSmall;          /*!< Transmit small packet*/
} enet_stats_t;

/*! @brief Defines the ENET MAC packet buffer structure.*/
typedef struct ENETMacPacketBuffer
{
    uint8_t *data;
    uint16_t length;
} enet_mac_packet_buffer_t;

#if ENET_RECEIVE_ALL_INTERRUPT
typedef uint32_t (* enet_netif_callback_t)(void *enetPtr, enet_mac_packet_buffer_t *packetBuffer);
#endif

/*! @brief Defines the ENET device data structure for the ENET.*/
typedef struct ENETDevIf
{
    struct ENETDevIf *next; /*!< Next device structure address*/
    void *netIfPtr;           /*!< Store the connected  upper layer in the structure*/
#if ENET_RECEIVE_ALL_INTERRUPT
    void *enetNetifService;   /*!< Service function*/
#endif
    enet_multicast_group_t *multiGroupPtr; /*!< Multicast group chain*/
    uint32_t deviceNumber;    /*!< Device number*/
    bool isInitialized;       /*!< Device initialized*/
    uint16_t maxFrameSize;  /*!< MAC maximum frame size*/
    enet_mac_config_t *macCfgPtr;/*!< MAC configuration structure*/
    enet_phy_config_t *phyCfgPtr;/*!< PHY configuration structure*/
    const struct ENETMacApi *macApiPtr;   /*!< MAC application interface structure*/
    void *phyApiPtr;             /*!< PHY application interface structure*/
    enet_mac_context_t *macContextPtr; /*!< MAC context pointer*/
#if ENET_ENABLE_DETAIL_STATS
    enet_stats_t stats;                /*!< Packets statistic*/
#endif
#if ENET_RECEIVE_ALL_INTERRUPT
    enet_netif_callback_t  enetNetifcall;  /*!< Receive callback function to the upper layer*/
#else
    event_object_t enetReceiveSync;     /*!< Receive sync signal*/
#endif
    lock_object_t enetContextSync;     /*!< Sync signal*/
} enet_dev_if_t;

/*! @brief Defines the basic application for the ENET device.*/
typedef struct ENETMacApi
{
    uint32_t (* enet_mac_init)(enet_dev_if_t * enetIfPtr, enet_rxbd_config_t *rxbdCfg, enet_txbd_config_t *txbdCfg);/*!< MAC initialize interface*/
    uint32_t (* enet_mac_deinit)(enet_dev_if_t * enetIfPtr);/*!< MAC close interface*/
    uint32_t (* enet_mac_send)(enet_dev_if_t * enetIfPtr, uint8_t *packet, uint32_t size);/*!< MAC send packets*/
#if !ENET_RECEIVE_ALL_INTERRUPT
    uint32_t (* enet_mac_receive)(enet_dev_if_t * enetIfPtr, enet_mac_packet_buffer_t *packBuffer);/*!< MAC receive interface*/
#endif
    uint32_t (* enet_mii_read)(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr);/*!< MII reads PHY*/
    uint32_t (* enet_mii_write)(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t data);/*!< MII writes PHY*/
    uint32_t (* enet_add_multicast_group)(uint32_t instance, enet_multicast_group_t *multiGroupPtr, uint8_t *groupAddr);/*!< Add multicast group*/
    uint32_t (* enet_leave_multicast_group)(uint32_t instance, enet_multicast_group_t *multiGroupPtr, uint8_t *groupAddr);/*!< Leave multicast group*/
} enet_mac_api_t;

/*******************************************************************
* Global variables
 
***********************************************************************/
extern const enet_mac_api_t g_enetMacApi;

/*******************************************************************************
 * API 
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
  * @name ENET Driver
  * @{
  */


#if FSL_FEATURE_ENET_SUPPORT_PTP
/*!
 * @brief Initializes the ENET PTP context structure with the basic configuration.
 *
 * @param macContextPtr The pointer to the ENET MAC macContext structure.
 * @return The execution status.
 */
uint32_t enet_ptp_init(enet_private_ptp_buffer_t *privatePtpPtr, uint32_t ptpRxBufferNum, enet_mac_ptp_ts_data_t *ptpTsRxDataPtr, uint32_t ptpTxBufferNum, enet_mac_ptp_ts_data_t *ptpTsTxDataPtr);
  
/*!
 * @brief Initializes the ENET PTP timer with the basic configuration.
 *
 * After the PTP starts, the 1588 timer also starts running. If the user wants the 1588 timer
 * as the slave, enable the isSlaveEnabled flag.
 *
 * @param instance The ENET instance number.
 * @param ptpCfgPtr The pointer to the basic PTP timer configuration structure.
 * @return The execution status.
 */
uint32_t enet_ptp_start(uint32_t instance, bool isSlaveEnabled);

/*!
 * @brief Parses the ENET packet. 
 *
 * Parses the ENET message and checks if it is a PTP message. If it is a PTP message,
 * the message is stored in the PTP information structure. Message parsing 
 * decides whether timestamp processing is done after that.
 *
 * @param packet The ENET packet.
 * @param ptpTsPtr The pointer to the PTP data structure.
 * @param isPtpMsg The PTP message flag.
 * @param isFastEnabled The fast operation flag. If set, only check if it is a ptp message
 *        and doesn't store any ptp message.
 * @return The execution status.
 */
uint32_t enet_ptp_parse(uint8_t *packet, enet_mac_ptp_ts_data_t *ptpTsPtr, bool *isPtpMsg, bool isFastEnabled);

/*!
 * @brief Gets the current value of the ENET PTP time.
 *
 * @param ptpTimerPtr The PTP timer structure.
 * @return The execution status.
 */
uint32_t enet_ptp_get_time(enet_mac_ptp_time_t *ptpTimerPtr);

/*!
 * @brief Sets the current value of the ENET PTP time.
 *
 * @param ptpTimerPtr The PTP timer structure.
 * @return The execution status.
 */
uint32_t enet_ptp_set_time(enet_mac_ptp_time_t *ptpTimerPtr);

/*!
 * @brief Adjusts the ENET PTP time.
 *
 * @param instance The ENET instance number.
 * @param drift The PTP timer drift value.
 * @return The execution status.
 */
uint32_t enet_ptp_correction_time(uint32_t instance, int32_t drift);


/*!
 * @brief Stores the transmit timestamp.
 *
 * @param ptpBuffer The PTP buffer pointer.
 * @param bdPtr The current transmit buffer descriptor.
 * @return The execution status.
 */	
uint32_t enet_ptp_store_tx_timestamp(enet_private_ptp_buffer_t *ptpBuffer,void *bdPtr);

/*!
 * @brief Stores receive timestamp.
 *
 * @param ptpBuffer The PTP buffer pointer.
 * @param packet The current receive packet.
 * @param bdPtr The current receive buffer descriptor.
 * @return The execution status.
 */
uint32_t enet_ptp_store_rx_timestamp(enet_private_ptp_buffer_t *ptpBuffer, uint8_t *packet, void *bdPtr);

/*!
 * @brief Initializes the buffer queue for the PTP layer2 Ethernet packets.
 *
 * @param ptpBuffer The PTP buffer pointer.
 * @return The execution status.
 */
uint32_t enet_ptp_l2queue_init(enet_private_ptp_buffer_t *ptpBuffer, enet_ptp_l2queue_t *ptpL2QuePtr);

/*!
 * @brief Adds the PTP layer2 Ethernet packet to the PTP Ethernet packet queue.
 *
 * @param ptpQuePtr The ENET private ptp layer2 buffer queue structure pointer.
 * @param packet The packet buffer pointer.
 * @param length The packet length. 
 * @return The execution status.
 */
uint32_t enet_ptp_service_l2packet(enet_ptp_l2queue_t * ptpQuePtr, uint8_t *packet, uint16_t length);

/*!
 * @brief Sends the PTP layer2 Ethernet packet to the Net.
 *
 * @param enetIfPtr The ENET context structure.
 * @param paramPtr The buffer from upper layer. 
 * @return The execution status.
 */
uint32_t enet_ptp_send_l2packet(enet_dev_if_t * enetIfPtr, void *paramPtr);

/*!
 * @brief Receives the PTP layer2 Ethernet packet from the Net.
 *
 * @param enetIfPtr The ENET context structure.
 * @param paramPtr The buffer receive from net and will send to upper layer. 
 * @return The execution status.
 */
uint32_t enet_ptp_receive_l2packet(enet_dev_if_t * enetIfPtr,void *paramPtr);

/*!
 * @brief Provides the handler for the 1588 stack to do PTP IOCTL.
 *
 * @param enetIfPtr The ENET context structure.
 * @param commandId The command id.
 * @param inOutPtr The data buffer. 
 * @return The execution status.
 */
uint32_t enet_ptp_ioctl(enet_dev_if_t * enetIfPtr, uint32_t commandId, void *inOutPtr);

/*!
 * @brief Stops the ENET PTP timer.
 *
 * @param instance The ENET instance number.
 * @return The execution status.
 */
uint32_t enet_ptp_stop(uint32_t instance);

/*!
 * @brief Checks whether the PTP ring buffer is full.
 *
 * @param ptpTsRingPtr The ENET PTP timestamp ring.
 * @return True if the PTP ring buffer is full. Otherwise, false.
 */
bool enet_ptp_ring_is_full(enet_mac_ptp_ts_ring_t *ptpTsRingPtr);

/*!
 * @brief Updates the latest ring buffers.
 *
 * Adds the PTP message data to the PTP ring buffers and increases the 
 * PTP ring buffer index.
 *
 * @param ptpTsRingPtr The ENET PTP timestamp ring.
 * @param data The PTP data buffer.
 * @return The execution status.
 */
uint32_t enet_ptp_ring_update(enet_mac_ptp_ts_ring_t *ptpTsRingPtr, enet_mac_ptp_ts_data_t *data);

/*!
 * @brief Searches the element in ring buffers with the message ID and Clock ID.
 *
 * @param ptpTsRingPtr The ENET PTP timestamp ring.
 * @param data The PTP data buffer.
 * @return The execution status.
 */
uint32_t enet_ptp_ring_search(enet_mac_ptp_ts_ring_t *ptpTsRingPtr, enet_mac_ptp_ts_data_t *data);

/*!
 * @brief Calculates the ENET PTP ring buffer index.
 *
 * @param size The ring size.
 * @param curIdx The current ring index.
 * @param offset The offset index.
 * @return The execution status.
 */
static inline uint32_t enet_ptp_ring_index(uint32_t size, uint32_t curIdx, uint32_t offset)
{
    return ((curIdx + offset) % size);
}

/*!
 * @brief Frees all ring buffers.
 *
 * @param enetContextPtr The ENET MAC context buffer.
 * @return The execution status.
 */
uint32_t enet_ptp_deinit(enet_mac_context_t *enetContextPtr);

/*!
 * @brief The ENET PTP time interrupt handler.
 *
 * @param enetIfPtr The ENET context structure pointer.
 */
void enet_mac_ts_isr(void *enetIfPtr);
#endif
/*!
 * @brief(R)MII Read function.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param dataPtr The data read from MII.
 * @return The execution status.
 */
uint32_t enet_mii_read(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr);

/*!
 * @brief(R)MII Read function.
 *
 * @param instance The ENET instance number.
 * @param phyAddr The PHY address.
 * @param phyReg The PHY register.
 * @param data The data write to MII.
 * @return The execution status.
 */
uint32_t enet_mii_write(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t data);

/*!
 * @brief Initializes  ENET buffer descriptors.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_bd_init(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Initializes the ENET MAC MII(MDC/MDIO) interface.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_mii_init(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Initialize the ENET receive buffer descriptors.
 *
 * If you open ENET_RECEIVE_ALL_INTERRUPT to do receive 
 * data buffer numbers can be the same as the receive descriptor numbers. 
 * But if you close ENET_RECEIVE_ALL_INTERRUPT and choose polling receive 
 * frames please make sure the receive data buffers are more than 
 * buffer descriptor numbers to guarantee a good performance.
 *
 * @param enetIfPtr The ENET context structure.
 * @param rxbdCfg The receive buffer descriptor configuration. 
 * @return The execution status.
 */
uint32_t enet_mac_rxbd_init(enet_dev_if_t * enetIfPtr, enet_rxbd_config_t *rxbdCfg);

/*!
 * @brief Deinitialize the ENET receive buffer descriptors.
 *
 * Deinitialize the ENET receive buffer descriptors. 
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */ 

uint32_t enet_mac_rxbd_deinit(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Initialize the ENET transmit buffer descriptors.
 *
 * @param enetIfPtr The ENET context structure.
 * @param txbdCfg The transmit buffer descriptor configuration. 
 * @return The execution status.
 */
uint32_t enet_mac_txbd_init(enet_dev_if_t * enetIfPtr, enet_txbd_config_t *txbdCfg);

/*!
 * @brief Deinitialize the ENET transmit buffer descriptors.
 *
 * Deinitialize the ENET transmit buffer descriptors. 
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */ 
uint32_t enet_mac_txbd_deinit(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Initializes ENET MAC FIFO and accelerator with the basic configuration.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_configure_fifo_accel(enet_dev_if_t * enetIfPtr);

/*!
 * @brief the ENET controller with the basic configuration.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_configure_controller(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Deinit the ENET device.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_deinit(enet_dev_if_t * enetIfPtr);

#if !ENET_RECEIVE_ALL_INTERRUPT
/*!
 * @brief Updates the receive buffer descriptor.
 *
 * This updates the used receive buffer descriptor ring to
 * ensure that the used BDS is correctly used again. It  cleans 
 * the status region and sets the control region of the used receive buffer 
 * descriptor. If the isBufferUpdate flag is set, the data buffer in the
 * buffer descriptor is updated.
 *
 * @param enetIfPtr The ENET context structure.
 * @param isBufferUpdate The data buffer update flag.
 * @return The execution status.
 */
uint32_t enet_mac_update_rxbd(enet_dev_if_t * enetIfPtr, bool isBufferUpdate);
#else
/*!
 * @brief Updates the receive buffer descriptor.
 *
 * Clears the status region and sets the control region of the current receive buffer 
 * descriptor to ensure that it is  used correctly again. It  increases the buffer 
 * descriptor index to the next buffer descriptor.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_update_rxbd(enet_dev_if_t * enetIfPtr);
#endif
/*!
 * @brief Processes the ENET receive frame error statistics.
 *
 * This interface gets the error statistics of the received frame.
 * Because the error information is in the last BD of a frame, this interface
 * should be called when processing the last BD of a frame.
 *
 * @param enetIfPtr The ENET context structure.
 * @param data The current control and status data of the buffer descriptor.
 * @return The frame error status.
 *         - True if the frame has an error. 
 *         - False if the frame does not have an error.
 */
bool enet_mac_rx_error_stats(enet_dev_if_t * enetIfPtr, uint32_t data);

/*!
 * @brief Processes the ENET transmit frame statistics.
 *
 * This interface gets the error statistics of the transmit frame.
 * Because the error information is in the last BD of a frame, this interface
 * should be called when processing the last BD of a frame.
 *
 * @param enetIfPtr The ENET context structure.
 * @param curBd The current buffer descriptor.
 */
void enet_mac_tx_error_stats(enet_dev_if_t * enetIfPtr,void *curBd);

/*!
 * @brief ENET transmit buffer descriptor cleanup.
 *
 * First, store the transmit frame error statistic and PTP timestamp of the transmitted packets. 
 * Second, clean up the used transmit buffer descriptors.
 * If the PTP 1588 feature is open, this interface  captures the 1588 timestamp. 
 * It is called by the transmit interrupt handler.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_tx_cleanup(enet_dev_if_t * enetIfPtr);
#if !ENET_RECEIVE_ALL_INTERRUPT
/*!
 * @brief Receives ENET packets.
 *
 * @param enetIfPtr The ENET context structure.
 * @param packBuffer The received data buffer.
 * @return The execution status.
 */
uint32_t enet_mac_receive(enet_dev_if_t * enetIfPtr, enet_mac_packet_buffer_t *packBuffer);
#else
/*!
 * @brief Receives ENET packets.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t enet_mac_receive(enet_dev_if_t * enetIfPtr);
#endif
/*!
 * @brief Transmits ENET packets.
 *
 * @param enetIfPtr The ENET context structure.
 * @param packet The frame to be transmitted.
 * @param size The frame size.
 * @return The execution status.
 */
uint32_t enet_mac_send(enet_dev_if_t * enetIfPtr, uint8_t *packet, uint32_t size);

/*!
 * @brief The ENET receive interrupt handler.
 *
 * @param enetIfPtr The ENET context structure pointer.
 */
void enet_mac_rx_isr(void *enetIfPtr);

/*!
 * @brief The ENET transmit interrupt handler.
 *
 * @param enetIfPtr The ENET context structure pointer.
 */
void enet_mac_tx_isr(void *enetIfPtr);

/*!
 * @brief Calculates the CRC hash value.
 *
 * @param address The ENET MAC hardware address.
 * @param crcVlaue The calculated CRC value of the Mac address.
 */
void enet_mac_calculate_crc32(enetMacAddr address, uint32_t *crcValue);

/*!
 * @brief Adds the ENET device to a multicast group.
 *
 * @param instance The ENET instance number.
 * @param multiGroupPtr The ENET multicast group structure.
 * @param address The ENET MAC hardware address.
 * @return The execution status.
 */
uint32_t enet_mac_add_multicast_group(uint32_t instance, enet_multicast_group_t *multiGroupPtr, enetMacAddr address);

/*!
 * @brief Moves the ENET device from a multicast group.
 *
 * @param instance The ENET instance number.
 * @param multiGroupPtr The ENET multicast group structure.
 * @param address The ENET MAC hardware address.
 * @return The execution status.
 */
uint32_t enet_mac_leave_multicast_group(uint32_t instance, enet_multicast_group_t *multiGroupPtr, enetMacAddr address);

/*!
 * @brief Initializes the ENET with the basic configuration.
 *
 * @param enetIfPtr The pointer to the basic configuration structure.
 * @return The execution status.
 */
uint32_t enet_mac_init(enet_dev_if_t * enetIfPtr, enet_rxbd_config_t *rxbdCfg,
                            enet_txbd_config_t *txbdCfg);

/*!
 * @brief Enqueues a data buffer to the buffer queue.
 *
 * @param queue The buffer queue.
 * @param buffer The buffer to add to the buffer queue.
 */
void enet_mac_enqueue_buffer( void **queue, void *buffer);

/*!
 * @brief Dequeues a buffer from the buffer queue.
 *
 * @param queue The buffer queue.
 * @return The dequeued data buffer.
 */
void *enet_mac_dequeue_buffer( void **queue);

/* @} */

#if defined(__cplusplus)
}
#endif

#endif

/*! @}*/

#endif /* __FSL_ENET_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/


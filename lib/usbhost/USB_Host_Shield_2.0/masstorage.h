/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */

#if !defined(__MASSTORAGE_H__)
#define __MASSTORAGE_H__

// Cruft removal, makes driver smaller, faster.
#ifndef MS_WANT_PARSER
#define MS_WANT_PARSER 0
#endif

#include "Usb.h"

#define bmREQ_MASSOUT       USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE
#define bmREQ_MASSIN        USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE

// Mass Storage Subclass Constants
#define MASS_SUBCLASS_SCSI_NOT_REPORTED 0x00    // De facto use
#define MASS_SUBCLASS_RBC               0x01
#define MASS_SUBCLASS_ATAPI             0x02    // MMC-5 (ATAPI)
#define MASS_SUBCLASS_OBSOLETE1         0x03    // Was QIC-157
#define MASS_SUBCLASS_UFI               0x04    // Specifies how to interface Floppy Disk Drives to USB
#define MASS_SUBCLASS_OBSOLETE2         0x05    // Was SFF-8070i
#define MASS_SUBCLASS_SCSI              0x06    // SCSI Transparent Command Set
#define MASS_SUBCLASS_LSDFS             0x07    // Specifies how host has to negotiate access before trying SCSI
#define MASS_SUBCLASS_IEEE1667          0x08

// Mass Storage Class Protocols
#define MASS_PROTO_CBI                  0x00    // CBI (with command completion interrupt)
#define MASS_PROTO_CBI_NO_INT           0x01    // CBI (without command completion interrupt)
#define MASS_PROTO_OBSOLETE             0x02
#define MASS_PROTO_BBB                  0x50    // Bulk Only Transport
#define MASS_PROTO_UAS                  0x62

// Request Codes
#define MASS_REQ_ADSC                   0x00
#define MASS_REQ_GET                    0xFC
#define MASS_REQ_PUT                    0xFD
#define MASS_REQ_GET_MAX_LUN            0xFE
#define MASS_REQ_BOMSR                  0xFF    // Bulk-Only Mass Storage Reset

#define MASS_CBW_SIGNATURE              0x43425355
#define MASS_CSW_SIGNATURE              0x53425355

#define MASS_CMD_DIR_OUT                0 // (0 << 7)
#define MASS_CMD_DIR_IN                 0x80 //(1 << 7)

/*
 * Reference documents from T10 (http://www.t10.org)
 * SCSI Primary Commands - 3 (SPC-3)
 * SCSI Block Commands - 2 (SBC-2)
 * Multi-Media Commands - 5 (MMC-5)
 */

/* Group 1 commands (CDB's here are should all be 6-bytes) */
#define SCSI_CMD_TEST_UNIT_READY        0x00
#define SCSI_CMD_REQUEST_SENSE          0x03
#define SCSI_CMD_FORMAT_UNIT            0x04
#define SCSI_CMD_READ_6                 0x08
#define SCSI_CMD_WRITE_6                0x0A
#define SCSI_CMD_INQUIRY                0x12
#define SCSI_CMD_MODE_SELECT_6          0x15
#define SCSI_CMD_MODE_SENSE_6           0x1A
#define SCSI_CMD_START_STOP_UNIT        0x1B
#define SCSI_CMD_PREVENT_REMOVAL        0x1E
/* Group 2 Commands (CDB's here are 10-bytes) */
#define SCSI_CMD_READ_FORMAT_CAPACITIES 0x23
#define SCSI_CMD_READ_CAPACITY_10       0x25
#define SCSI_CMD_READ_10                0x28
#define SCSI_CMD_WRITE_10               0x2A
#define SCSI_CMD_SEEK_10                0x2B
#define SCSI_CMD_ERASE_10               0x2C
#define SCSI_CMD_WRITE_AND_VERIFY_10    0x2E
#define SCSI_CMD_VERIFY_10              0x2F
#define SCSI_CMD_SYNCHRONIZE_CACHE      0x35
#define SCSI_CMD_WRITE_BUFFER           0x3B
#define SCSI_CMD_READ_BUFFER            0x3C
#define SCSI_CMD_READ_SUBCHANNEL        0x42
#define SCSI_CMD_READ_TOC               0x43
#define SCSI_CMD_READ_HEADER            0x44
#define SCSI_CMD_PLAY_AUDIO_10          0x45
#define SCSI_CMD_GET_CONFIGURATION      0x46
#define SCSI_CMD_PLAY_AUDIO_MSF         0x47
#define SCSI_CMD_PLAY_AUDIO_TI          0x48
#define SCSI_CMD_PLAY_TRACK_REL_10      0x49
#define SCSI_CMD_GET_EVENT_STATUS       0x4A
#define SCSI_CMD_PAUSE_RESUME           0x4B
#define SCSI_CMD_READ_DISC_INFORMATION  0x51
#define SCSI_CMD_READ_TRACK_INFORMATION 0x52
#define SCSI_CMD_RESERVE_TRACK          0x53
#define SCSI_CMD_SEND_OPC_INFORMATION   0x54
#define SCSI_CMD_MODE_SELECT_10         0x55
#define SCSI_CMD_REPAIR_TRACK           0x58
#define SCSI_CMD_MODE_SENSE_10          0x5A
#define SCSI_CMD_CLOSE_TRACK_SESSION    0x5B
#define SCSI_CMD_READ_BUFFER_CAPACITY   0x5C
#define SCSI_CMD_SEND_CUE_SHEET         0x5D
/* Group 5 Commands (CDB's here are 12-bytes) */
#define SCSI_CMD_REPORT_LUNS            0xA0
#define SCSI_CMD_BLANK                  0xA1
#define SCSI_CMD_SECURITY_PROTOCOL_IN   0xA2
#define SCSI_CMD_SEND_KEY               0xA3
#define SCSI_CMD_REPORT_KEY             0xA4
#define SCSI_CMD_PLAY_AUDIO_12          0xA5
#define SCSI_CMD_LOAD_UNLOAD            0xA6
#define SCSI_CMD_SET_READ_AHEAD         0xA7
#define SCSI_CMD_READ_12                0xA8
#define SCSI_CMD_PLAY_TRACK_REL_12      0xA9
#define SCSI_CMD_WRITE_12               0xAA
#define SCSI_CMD_READ_MEDIA_SERIAL_12   0xAB
#define SCSI_CMD_GET_PERFORMANCE        0xAC
#define SCSI_CMD_READ_DVD_STRUCTURE     0xAD
#define SCSI_CMD_SECURITY_PROTOCOL_OUT  0xB5
#define SCSI_CMD_SET_STREAMING          0xB6
#define SCSI_CMD_READ_MSF               0xB9
#define SCSI_CMD_SET_SPEED              0xBB
#define SCSI_CMD_MECHANISM_STATUS       0xBD
#define SCSI_CMD_READ_CD                0xBE
#define SCSI_CMD_SEND_DISC_STRUCTURE    0xBF
/* Vendor-unique Commands, included for completeness */
#define SCSI_CMD_CD_PLAYBACK_STATUS     0xC4 /* SONY unique */
#define SCSI_CMD_PLAYBACK_CONTROL       0xC9 /* SONY unique */
#define SCSI_CMD_READ_CDDA              0xD8 /* Vendor unique */
#define SCSI_CMD_READ_CDXA              0xDB /* Vendor unique */
#define SCSI_CMD_READ_ALL_SUBCODES      0xDF /* Vendor unique */

/* SCSI error codes */
#define SCSI_S_NOT_READY                0x02
#define SCSI_S_MEDIUM_ERROR             0x03
#define SCSI_S_ILLEGAL_REQUEST          0x05
#define SCSI_S_UNIT_ATTENTION           0x06
#define SCSI_ASC_LBA_OUT_OF_RANGE       0x21
#define SCSI_ASC_MEDIA_CHANGED          0x28
#define SCSI_ASC_MEDIUM_NOT_PRESENT     0x3A

/* USB error codes */
#define MASS_ERR_SUCCESS                0x00
#define MASS_ERR_PHASE_ERROR            0x02
#define MASS_ERR_UNIT_NOT_READY         0x03
#define MASS_ERR_UNIT_BUSY              0x04
#define MASS_ERR_STALL                  0x05
#define MASS_ERR_CMD_NOT_SUPPORTED      0x06
#define MASS_ERR_INVALID_CSW            0x07
#define MASS_ERR_NO_MEDIA               0x08
#define MASS_ERR_BAD_LBA                0x09
#define MASS_ERR_MEDIA_CHANGED          0x0A
#define MASS_ERR_DEVICE_DISCONNECTED    0x11
#define MASS_ERR_UNABLE_TO_RECOVER      0x12    // Reset recovery error
#define MASS_ERR_INVALID_LUN            0x13
#define MASS_ERR_WRITE_STALL            0x14
#define MASS_ERR_READ_NAKS              0x15
#define MASS_ERR_WRITE_NAKS             0x16
#define MASS_ERR_WRITE_PROTECTED        0x17
#define MASS_ERR_NOT_IMPLEMENTED        0xFD
#define MASS_ERR_GENERAL_SCSI_ERROR     0xFE
#define MASS_ERR_GENERAL_USB_ERROR      0xFF
#define MASS_ERR_USER                   0xA0    // For subclasses to define their own error codes

#define MASS_TRANS_FLG_CALLBACK         0x01    // Callback is involved
#define MASS_TRANS_FLG_NO_STALL_CHECK   0x02    // STALL condition is not checked
#define MASS_TRANS_FLG_NO_PHASE_CHECK   0x04    // PHASE_ERROR is not checked

#define MASS_MAX_ENDPOINTS              3

struct Capacity {
        uint8_t data[8];
        //uint32_t dwBlockAddress;
        //uint32_t dwBlockLength;
} __attribute__((packed));

struct BASICCDB {
        uint8_t Opcode;

        unsigned unused : 5;
        unsigned LUN : 3;

        uint8_t info[12];
} __attribute__((packed));

typedef BASICCDB BASICCDB_t;

struct CDB6 {
        uint8_t Opcode;

        unsigned LBAMSB : 5;
        unsigned LUN : 3;

        uint8_t LBAHB;
        uint8_t LBALB;
        uint8_t AllocationLength;
        uint8_t Control;

public:

        CDB6(uint8_t _Opcode, uint8_t _LUN, uint32_t LBA, uint8_t _AllocationLength, uint8_t _Control) :
        Opcode(_Opcode), LBAMSB(BGRAB2(LBA) & 0x1f), LUN(_LUN), LBAHB(BGRAB1(LBA)), LBALB(BGRAB0(LBA)),
        AllocationLength(_AllocationLength), Control(_Control) {
        }

        CDB6(uint8_t _Opcode, uint8_t _LUN, uint8_t _AllocationLength, uint8_t _Control) :
        Opcode(_Opcode), LBAMSB(0), LUN(_LUN), LBAHB(0), LBALB(0),
        AllocationLength(_AllocationLength), Control(_Control) {
        }
} __attribute__((packed));

typedef CDB6 CDB6_t;

struct CDB10 {
        uint8_t Opcode;

        unsigned Service_Action : 5;
        unsigned LUN : 3;

        uint8_t LBA_L_M_MB;
        uint8_t LBA_L_M_LB;
        uint8_t LBA_L_L_MB;
        uint8_t LBA_L_L_LB;

        uint8_t Misc2;

        uint8_t ALC_MB;
        uint8_t ALC_LB;

        uint8_t Control;
public:

        CDB10(uint8_t _Opcode, uint8_t _LUN) :
        Opcode(_Opcode), Service_Action(0), LUN(_LUN),
        LBA_L_M_MB(0), LBA_L_M_LB(0), LBA_L_L_MB(0), LBA_L_L_LB(0),
        Misc2(0), ALC_MB(0), ALC_LB(0), Control(0) {
        }

        CDB10(uint8_t _Opcode, uint8_t _LUN, uint16_t xflen, uint32_t _LBA) :
        Opcode(_Opcode), Service_Action(0), LUN(_LUN),
        LBA_L_M_MB(BGRAB3(_LBA)), LBA_L_M_LB(BGRAB2(_LBA)), LBA_L_L_MB(BGRAB1(_LBA)), LBA_L_L_LB(BGRAB0(_LBA)),
        Misc2(0), ALC_MB(BGRAB1(xflen)), ALC_LB(BGRAB0(xflen)), Control(0) {
        }
} __attribute__((packed));

typedef CDB10 CDB10_t;

struct CDB12 {
        uint8_t Opcode;

        unsigned Service_Action : 5;
        unsigned Misc : 3;

        uint8_t LBA_L_M_LB;
        uint8_t LBA_L_L_MB;
        uint8_t LBA_L_L_LB;

        uint8_t ALC_M_LB;
        uint8_t ALC_L_MB;
        uint8_t ALC_L_LB;
        uint8_t Control;
} __attribute__((packed));

typedef CDB12 CDB12_t;

struct CDB_LBA32_16 {
        uint8_t Opcode;

        unsigned Service_Action : 5;
        unsigned Misc : 3;

        uint8_t LBA_L_M_MB;
        uint8_t LBA_L_M_LB;
        uint8_t LBA_L_L_MB;
        uint8_t LBA_L_L_LB;

        uint8_t A_M_M_MB;
        uint8_t A_M_M_LB;
        uint8_t A_M_L_MB;
        uint8_t A_M_L_LB;

        uint8_t ALC_M_MB;
        uint8_t ALC_M_LB;
        uint8_t ALC_L_MB;
        uint8_t ALC_L_LB;

        uint8_t Misc2;
        uint8_t Control;
} __attribute__((packed));

struct CDB_LBA64_16 {
        uint8_t Opcode;
        uint8_t Misc;

        uint8_t LBA_M_M_MB;
        uint8_t LBA_M_M_LB;
        uint8_t LBA_M_L_MB;
        uint8_t LBA_M_L_LB;

        uint8_t LBA_L_M_MB;
        uint8_t LBA_L_M_LB;
        uint8_t LBA_L_L_MB;
        uint8_t LBA_L_L_LB;

        uint8_t ALC_M_MB;
        uint8_t ALC_M_LB;
        uint8_t ALC_L_MB;
        uint8_t ALC_L_LB;

        uint8_t Misc2;
        uint8_t Control;
} __attribute__((packed));

struct InquiryResponse {
        uint8_t DeviceType : 5;
        uint8_t PeripheralQualifier : 3;

        unsigned Reserved : 7;
        unsigned Removable : 1;

        uint8_t Version;

        unsigned ResponseDataFormat : 4;
        unsigned HISUP : 1;
        unsigned NormACA : 1;
        unsigned TrmTsk : 1;
        unsigned AERC : 1;

        uint8_t AdditionalLength;
        //uint8_t Reserved3[2];

        unsigned PROTECT : 1;
        unsigned Res : 2;
        unsigned ThreePC : 1;
        unsigned TPGS : 2;
        unsigned ACC : 1;
        unsigned SCCS : 1;

        unsigned ADDR16 : 1;
        unsigned R1 : 1;
        unsigned R2 : 1;
        unsigned MCHNGR : 1;
        unsigned MULTIP : 1;
        unsigned VS : 1;
        unsigned ENCSERV : 1;
        unsigned BQUE : 1;

        unsigned SoftReset : 1;
        unsigned CmdQue : 1;
        unsigned Reserved4 : 1;
        unsigned Linked : 1;
        unsigned Sync : 1;
        unsigned WideBus16Bit : 1;
        unsigned WideBus32Bit : 1;
        unsigned RelAddr : 1;

        uint8_t VendorID[8];
        uint8_t ProductID[16];
        uint8_t RevisionID[4];
} __attribute__((packed));

struct CommandBlockWrapperBase {
        uint32_t dCBWSignature;
        uint32_t dCBWTag;
        uint32_t dCBWDataTransferLength;
        uint8_t bmCBWFlags;
public:

        CommandBlockWrapperBase() {
        }

        CommandBlockWrapperBase(uint32_t tag, uint32_t xflen, uint8_t flgs) :
        dCBWSignature(MASS_CBW_SIGNATURE), dCBWTag(tag), dCBWDataTransferLength(xflen), bmCBWFlags(flgs) {
        }
} __attribute__((packed));

struct CommandBlockWrapper : public CommandBlockWrapperBase {

        struct {
                uint8_t bmCBWLUN : 4;
                uint8_t bmReserved1 : 4;
        };

        struct {
                uint8_t bmCBWCBLength : 4;
                uint8_t bmReserved2 : 4;
        };

        uint8_t CBWCB[16];

public:
        // All zeroed.

        CommandBlockWrapper() :
        CommandBlockWrapperBase(0, 0, 0), bmReserved1(0), bmReserved2(0) {
                for(int i = 0; i < 16; i++) CBWCB[i] = 0;
        }

        // Generic Wrap, CDB zeroed.

        CommandBlockWrapper(uint32_t tag, uint32_t xflen, uint8_t flgs, uint8_t lu, uint8_t cmdlen, uint8_t cmd) :
        CommandBlockWrapperBase(tag, xflen, flgs),
        bmCBWLUN(lu), bmReserved1(0), bmCBWCBLength(cmdlen), bmReserved2(0) {
                for(int i = 0; i < 16; i++) CBWCB[i] = 0;
                // Type punning can cause optimization problems and bugs.
                // Using reinterpret_cast to a dreinterpretifferent object is the proper way to do this.
                //(((BASICCDB_t *) CBWCB)->LUN) = cmd;
                BASICCDB_t *x = reinterpret_cast<BASICCDB_t *>(CBWCB);
                x->LUN = cmd;
        }

        // Wrap for CDB of 6

        CommandBlockWrapper(uint32_t tag, uint32_t xflen, CDB6_t *cdb, uint8_t dir) :
        CommandBlockWrapperBase(tag, xflen, dir),
        bmCBWLUN(cdb->LUN), bmReserved1(0), bmCBWCBLength(6), bmReserved2(0) {
                memcpy(&CBWCB, cdb, 6);
        }
        // Wrap for CDB of 10

        CommandBlockWrapper(uint32_t tag, uint32_t xflen, CDB10_t *cdb, uint8_t dir) :
        CommandBlockWrapperBase(tag, xflen, dir),
        bmCBWLUN(cdb->LUN), bmReserved1(0), bmCBWCBLength(10), bmReserved2(0) {
                memcpy(&CBWCB, cdb, 10);
        }
} __attribute__((packed));

struct CommandStatusWrapper {
        uint32_t dCSWSignature;
        uint32_t dCSWTag;
        uint32_t dCSWDataResidue;
        uint8_t bCSWStatus;
} __attribute__((packed));

struct RequestSenseResponce {
        uint8_t bResponseCode;
        uint8_t bSegmentNumber;

        uint8_t bmSenseKey : 4;
        uint8_t bmReserved : 1;
        uint8_t bmILI : 1;
        uint8_t bmEOM : 1;
        uint8_t bmFileMark : 1;

        uint8_t Information[4];
        uint8_t bAdditionalLength;
        uint8_t CmdSpecificInformation[4];
        uint8_t bAdditionalSenseCode;
        uint8_t bAdditionalSenseQualifier;
        uint8_t bFieldReplaceableUnitCode;
        uint8_t SenseKeySpecific[3];
} __attribute__((packed));

class BulkOnly : public USBDeviceConfig, public UsbConfigXtracter {
protected:
        static const uint8_t epDataInIndex; // DataIn endpoint index
        static const uint8_t epDataOutIndex; // DataOUT endpoint index
        static const uint8_t epInterruptInIndex; // InterruptIN  endpoint index

        USB *pUsb;
        uint8_t bAddress;
        uint8_t bConfNum; // configuration number
        uint8_t bIface; // interface value
        uint8_t bNumEP; // total number of EP in the configuration
        uint32_t qNextPollTime; // next poll time
        bool bPollEnable; // poll enable flag

        EpInfo epInfo[MASS_MAX_ENDPOINTS];

        uint32_t dCBWTag; // Tag
        //uint32_t dCBWDataTransferLength; // Data Transfer Length
        uint8_t bLastUsbError; // Last USB error
        uint8_t bMaxLUN; // Max LUN
        uint8_t bTheLUN; // Active LUN
        uint32_t CurrentCapacity[MASS_MAX_SUPPORTED_LUN]; // Total sectors
        uint16_t CurrentSectorSize[MASS_MAX_SUPPORTED_LUN]; // Sector size, clipped to 16 bits
        bool LUNOk[MASS_MAX_SUPPORTED_LUN]; // use this to check for media changes.
        bool WriteOk[MASS_MAX_SUPPORTED_LUN];
        void PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr);


        // Additional Initialization Method for Subclasses

        virtual uint8_t OnInit() {
                return 0;
        };
public:
        BulkOnly(USB *p);

        uint8_t GetLastUsbError() {
                return bLastUsbError;
        };

        uint8_t GetbMaxLUN() {
                return bMaxLUN; // Max LUN
        }

        uint8_t GetbTheLUN() {
                return bTheLUN; // Active LUN
        }

        bool WriteProtected(uint8_t lun);
        uint8_t MediaCTL(uint8_t lun, uint8_t ctl);
        uint8_t Read(uint8_t lun, uint32_t addr, uint16_t bsize, uint8_t blocks, uint8_t *buf);
        uint8_t Read(uint8_t lun, uint32_t addr, uint16_t bsize, uint8_t blocks, USBReadParser *prs);
        uint8_t Write(uint8_t lun, uint32_t addr, uint16_t bsize, uint8_t blocks, const uint8_t *buf);
        uint8_t LockMedia(uint8_t lun, uint8_t lock);

        bool LUNIsGood(uint8_t lun);
        uint32_t GetCapacity(uint8_t lun);
        uint16_t GetSectorSize(uint8_t lun);

        // USBDeviceConfig implementation
        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        uint8_t ConfigureDevice(uint8_t parent, uint8_t port, bool lowspeed);

        uint8_t Release();
        uint8_t Poll();

        virtual uint8_t GetAddress() {
                return bAddress;
        };

        // UsbConfigXtracter implementation
        void EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *ep);

        virtual bool DEVCLASSOK(uint8_t klass) {
                return (klass == USB_CLASS_MASS_STORAGE);
        }

        uint8_t SCSITransaction6(CDB6_t *cdb, uint16_t buf_size, void *buf, uint8_t dir);
        uint8_t SCSITransaction10(CDB10_t *cdb, uint16_t buf_size, void *buf, uint8_t dir);

private:
        uint8_t Inquiry(uint8_t lun, uint16_t size, uint8_t *buf);
        uint8_t TestUnitReady(uint8_t lun);
        uint8_t RequestSense(uint8_t lun, uint16_t size, uint8_t *buf);
        uint8_t ModeSense6(uint8_t lun, uint8_t pc, uint8_t page, uint8_t subpage, uint8_t len, uint8_t *buf);
        uint8_t GetMaxLUN(uint8_t *max_lun);
        uint8_t SetCurLUN(uint8_t lun);
        void Reset();
        uint8_t ResetRecovery();
        uint8_t ReadCapacity10(uint8_t lun, uint8_t *buf);
        void ClearAllEP();
        void CheckMedia();
        bool CheckLUN(uint8_t lun);
        uint8_t Page3F(uint8_t lun);
        bool IsValidCBW(uint8_t size, uint8_t *pcbw);
        bool IsMeaningfulCBW(uint8_t size, uint8_t *pcbw);

        bool IsValidCSW(CommandStatusWrapper *pcsw, CommandBlockWrapperBase *pcbw);

        uint8_t ClearEpHalt(uint8_t index);
#if MS_WANT_PARSER
        uint8_t Transaction(CommandBlockWrapper *cbw, uint16_t bsize, void *buf, uint8_t flags);
#endif
        uint8_t Transaction(CommandBlockWrapper *cbw, uint16_t bsize, void *buf);
        uint8_t HandleUsbError(uint8_t error, uint8_t index);
        uint8_t HandleSCSIError(uint8_t status);

};

#endif // __MASSTORAGE_H__

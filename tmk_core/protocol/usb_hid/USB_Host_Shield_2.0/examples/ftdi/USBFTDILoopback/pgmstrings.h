#if !defined(__PGMSTRINGS_H__)
#define __PGMSTRINGS_H__

#define LOBYTE(x) ((char*)(&(x)))[0]
#define HIBYTE(x) ((char*)(&(x)))[1]
#define BUFSIZE 256    //buffer size
 

/* Print strings in Program Memory */
const char Gen_Error_str[] PROGMEM = "\r\nRequest error. Error code:\t"; 
const char Dev_Header_str[] PROGMEM ="\r\nDevice descriptor: ";
const char Dev_Length_str[] PROGMEM ="\r\nDescriptor Length:\t";
const char Dev_Type_str[] PROGMEM ="\r\nDescriptor type:\t";
const char Dev_Version_str[] PROGMEM ="\r\nUSB version:\t\t";
const char Dev_Class_str[] PROGMEM ="\r\nDevice class:\t\t";
const char Dev_Subclass_str[] PROGMEM ="\r\nDevice Subclass:\t";
const char Dev_Protocol_str[] PROGMEM ="\r\nDevice Protocol:\t";
const char Dev_Pktsize_str[] PROGMEM ="\r\nMax.packet size:\t";
const char Dev_Vendor_str[] PROGMEM ="\r\nVendor  ID:\t\t";
const char Dev_Product_str[] PROGMEM ="\r\nProduct ID:\t\t";
const char Dev_Revision_str[] PROGMEM ="\r\nRevision ID:\t\t";
const char Dev_Mfg_str[] PROGMEM ="\r\nMfg.string index:\t";
const char Dev_Prod_str[] PROGMEM ="\r\nProd.string index:\t";
const char Dev_Serial_str[] PROGMEM ="\r\nSerial number index:\t";
const char Dev_Nconf_str[] PROGMEM ="\r\nNumber of conf.:\t";
const char Conf_Trunc_str[] PROGMEM ="Total length truncated to 256 bytes";
const char Conf_Header_str[] PROGMEM ="\r\nConfiguration descriptor:";
const char Conf_Totlen_str[] PROGMEM ="\r\nTotal length:\t\t";
const char Conf_Nint_str[] PROGMEM ="\r\nNum.intf:\t\t";
const char Conf_Value_str[] PROGMEM ="\r\nConf.value:\t\t";
const char Conf_String_str[] PROGMEM ="\r\nConf.string:\t\t";
const char Conf_Attr_str[] PROGMEM ="\r\nAttr.:\t\t\t";
const char Conf_Pwr_str[] PROGMEM ="\r\nMax.pwr:\t\t";
const char Int_Header_str[] PROGMEM ="\r\n\r\nInterface descriptor:";
const char Int_Number_str[] PROGMEM ="\r\nIntf.number:\t\t";
const char Int_Alt_str[] PROGMEM ="\r\nAlt.:\t\t\t";
const char Int_Endpoints_str[] PROGMEM ="\r\nEndpoints:\t\t";
const char Int_Class_str[] PROGMEM ="\r\nIntf. Class:\t\t";
const char Int_Subclass_str[] PROGMEM ="\r\nIntf. Subclass:\t\t";
const char Int_Protocol_str[] PROGMEM ="\r\nIntf. Protocol:\t\t";
const char Int_String_str[] PROGMEM ="\r\nIntf.string:\t\t";
const char End_Header_str[] PROGMEM ="\r\n\r\nEndpoint descriptor:";
const char End_Address_str[] PROGMEM ="\r\nEndpoint address:\t";
const char End_Attr_str[] PROGMEM ="\r\nAttr.:\t\t\t";
const char End_Pktsize_str[] PROGMEM ="\r\nMax.pkt size:\t\t";
const char End_Interval_str[] PROGMEM ="\r\nPolling interval:\t";
const char Unk_Header_str[] PROGMEM = "\r\nUnknown descriptor:";
const char Unk_Length_str[] PROGMEM ="\r\nLength:\t\t";
const char Unk_Type_str[] PROGMEM ="\r\nType:\t\t";
const char Unk_Contents_str[] PROGMEM ="\r\nContents:\t";
 
#endif // __PGMSTRINGS_H__
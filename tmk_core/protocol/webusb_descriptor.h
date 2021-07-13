#pragma once

#ifndef WORD_TO_BYTES_LE
#  define WORD_TO_BYTES_LE(n) n % 256, (n / 256) % 256
#endif
#ifndef LONG_TO_BYTES_LE
#  define LONG_TO_BYTES_LE(n) n % 256, (n / 256) % 256, (n / 65536) % 256, (n / 16777216) % 256
#endif

#define WEBUSB_VENDOR_CODE 0x42

#ifndef WEBUSB_LANDING_PAGE_URL
#  define WEBUSB_LANDING_PAGE_URL u8"docs.qmk.fm"
#endif

#define WEBUSB_LANDING_PAGE_PROTOCOL 1 /* 0: http  1: https forced to 1 since https is a requirement to connect over webusb */

#ifndef WEBUSB_LANDING_PAGE_INDEX
#  define WEBUSB_LANDING_PAGE_INDEX 0
#endif

#define WEBUSB_VERSION VERSION_BCD(1, 0, 0)

/* $ python -c "import uuid;print(', '.join(map(hex, uuid.UUID('3408b638-09a9-47a0-8bfd-a0768815b665').bytes_le)))" */
#define WEBUSB_PLATFORM_UUID 0x38, 0xb6, 0x8, 0x34, 0xa9, 0x9, 0xa0, 0x47, 0x8b, 0xfd, 0xa0, 0x76, 0x88, 0x15, 0xb6, 0x65

/** \brief Convenience macro to easily create device capability platform descriptors for the WebUSB platform.
 *
 *  \note This macro is designed to be wrapped in parentheses and included in a sequence to the \ref BOS_DESCRIPTOR macro.
 *
 * 	\param[in] VendorCode  Vendor Code that all control requests coming from the browser must use.
 *
 * 	\param[in] LandingPageIndex  Index of the URL Descriptor to use as the Landing Page for the device.
 *
 */
#define WEBUSB_PLATFORM_DESCRIPTOR(VendorCode, LandingPageIndex) /* WebUSB Platform Descriptor size */ 24, DTYPE_DeviceCapability, DCTYPE_Platform, /* Reserved */ 0, WEBUSB_PLATFORM_UUID, WORD_TO_BYTES_LE(WEBUSB_VERSION), VendorCode, LandingPageIndex

/** \brief Convenience macro to easily create \ref WebUSB_URL_Descriptor_t instances from a wide character string.
 *
 *  \note This macro is for little-endian systems only.
 *
 *  \param[in] URL  URL string to initialize a URL Descriptor structure with.
 *
 * 	\note Prefix String literal with u8 to ensure proper conversion: e.g. WEBUSB_URL_DESCRIPTOR(u8"www.google.com")
 */
#define WEBUSB_URL_DESCRIPTOR(URL) \
  { .Header = {.Size = sizeof(WebUSB_URL_Descriptor_t) + (sizeof(URL) - 1), .Type = WebUSB_DTYPE_URL}, .Scheme = (WEBUSB_LANDING_PAGE_PROTOCOL), .UTF8_URL = (URL) }

/* WebUSB Protocol Data Structures */
enum WebUSB_Request_t {
  WebUSB_RTYPE_GetURL = 2, /**< Indicates the device should return the indicated WebUSB_URL descriptor. */
};

enum WebUSB_Descriptor_t {
  WebUSB_DTYPE_URL = 3, /**< Indicates that the descriptor is a URL descriptor. */
};

/** \brief WebUSB URL Descriptor (LUFA naming convention).
 *
 *  Type define for a WebUSB URL Descriptor. This structure uses LUFA-specific element names
 *  to make each element's purpose clearer.
 *
 *  \note Regardless of CPU architecture, these values should be stored as little endian.
 */
typedef struct {
  USB_Descriptor_Header_t Header; /**< Descriptor header, including type (WebUSB_DTYPE_URL) and size. */

  uint8_t Scheme;     /**< URL scheme prefix: 0 means http://, 1 means https://, 255 means included in URL */
  uint8_t UTF8_URL[]; /**< UTF-8 encoded URL (excluding scheme prefix). */
} ATTR_PACKED WebUSB_URL_Descriptor_t;

#define MS_OS_20_VENDOR_CODE 0x45  // Must be different than WEBUSB_VENDOR_CODE

#define MS_OS_20_DESCRIPTOR_CONFIGURATION_HEADER_LENGTH 168
#define MS_OS_20_DESCRIPTOR_FUNCTION_HEADER_LENGTH 160
#define MS_OS_20_DESCRIPTOR_SET_TOTAL_LENGTH 178  // Sum of `.Length`s in MS_OS_20_Descriptor in WebUSB.c

#define MS_OS_20_DESCRIPTOR_COMPATIBILITY_ID { 'W', 'I', 'N', 'U', 'S', 'B', 0, 0 }
#define MS_OS_20_DESCRIPTOR_SUB_COMPATIBILITY_ID {0, 0, 0, 0, 0, 0, 0, 0}

#define MS_OS_20_PROPERTY_NAME_LENGTH 42
#define MS_OS_20_PROPERTY_NAME { \
      'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00, 'c', 0x00, 'e', 0x00, \
      'I', 0x00, 'n', 0x00, 't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00, \
      'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00, 'U', 0x00, 'I', 0x00, \
      'D', 0x00, 's', 0x00, 0x00, 0x00 \
    }
#define MS_OS_20_PROPERTY_DATA_LENGTH 80
#define MS_OS_20_PROPERTY_DATA { \
      '{', 0x00, '9', 0x00, 'D', 0x00, 'B', 0x00, '7', 0x00, 'F', 0x00, \
      '1', 0x00, 'F', 0x00, 'D', 0x00, '-', 0x00, '7', 0x00, 'E', 0x00, \
      '7', 0x00, 'A', 0x00, '-', 0x00, '4', 0x00, '0', 0x00, '0', 0x00, \
      '8', 0x00, '-', 0x00, '9', 0x00, '3', 0x00, '6', 0x00, 'B', 0x00, \
      '-', 0x00, '6', 0x00, 'B', 0x00, 'A', 0x00, '6', 0x00, 'C', 0x00, \
      '1', 0x00, '9', 0x00, 'A', 0x00, '3', 0x00, '0', 0x00, '8', 0x00, \
      'c', 0x00, '}', 0x00, 0x00, 0x00, 0x00, 0x00 \
    }

#define MS_OS_20_PLATFORM_UUID 0xdf, 0x60, 0xdd, 0xd8, 0x89, 0x45, 0xc7, 0x4c, 0x9c, 0xd2, 0x65, 0x9d, 0x9e, 0x64, 0x8a, 0x9f

#define MS_OS_20_WINDOWS_VERSION_8_1 0x06030000  // Windows version (8.1)

#ifndef MS_OS_20_ALTERNATE_ENUMERATION_CODE
#  define MS_OS_20_ALTERNATE_ENUMERATION_CODE 0 /**< Set to non-zero to enable Windows to allow device to return alternate USB descriptors. */
#endif

/** \brief Convenience macro to easily create device capability platform descriptors for the MS OS 2.0 platform.
 *
 *  \note This macro is designed to be wrapped in parentheses and included in a sequence to the \ref BOS_DESCRIPTOR macro.
 *
 * 	\param[in] VendorCode  Vendor Code that all control requests coming from Windows must use.
 *
 * 	\param[in] TotalLength  The length, in bytes, of the MS OS 2.0 descriptor set to be retrieved by Windows.
 */
#define MS_OS_20_PLATFORM_DESCRIPTOR(VendorCode, TotalLength) /* Total size of this descriptor */ 28, DTYPE_DeviceCapability, DCTYPE_Platform, /* Reserved */ 0, MS_OS_20_PLATFORM_UUID, LONG_TO_BYTES_LE(MS_OS_20_WINDOWS_VERSION_8_1), WORD_TO_BYTES_LE(TotalLength), VendorCode, MS_OS_20_ALTERNATE_ENUMERATION_CODE

    /* MS OS 2.0 Descriptors Data Structures */
    enum MS_OS_20_wIndex_t {
      MS_OS_20_DESCRIPTOR_INDEX    = 0x07, /**< Indicates the device should return MS OS 2.0 Descriptor Set. */
      MS_OS_20_SET_ALT_ENUMERATION = 0x08, /**< Indicates the device may "subsequently return alternate USB descriptors when Windows requests the information." */
    };

enum MS_OS_20_Descriptor_Types {
  MS_OS_20_SET_HEADER_DESCRIPTOR       = 0x00,
  MS_OS_20_SUBSET_HEADER_CONFIGURATION = 0x01,
  MS_OS_20_SUBSET_HEADER_FUNCTION      = 0x02,
  MS_OS_20_FEATURE_COMPATBLE_ID        = 0x03,
  MS_OS_20_FEATURE_REG_PROPERTY        = 0x04,
  //			MS_OS_20_FEATURE_MIN_RESUME_TIME = 0x05,
  //			MS_OS_20_FEATURE_MODEL_ID = 0x06,
  MS_OS_20_FEATURE_CCGP_DEVICE = 0x07,
};

/** \brief Microsoft OS 2.0 Descriptor Set Header (LUFA naming convention).
 *
 *  \note Regardless of CPU architecture, these values should be stored as little endian.
 */
typedef struct {
  uint16_t Length;         /**< The length, in bytes, of this header. Shall be set to 10. */
  uint16_t DescriptorType; /**< Shall be set to MS_OS_20_SET_HEADER_DESCRIPTOR */
  uint32_t WindowsVersion;
  uint16_t TotalLength; /**< The size of entire MS OS 2.0 descriptor set. The value shall match the value in the descriptor set information structure. */
} ATTR_PACKED MS_OS_20_Descriptor_Set_Header_t;

/** \brief Microsoft OS 2.0 configuration subset header.
 *
 */
typedef struct {
  uint16_t Length;             /**< The length, in bytes, of this subset header. Shall be set to 8. */
  uint16_t DescriptorType;     /**< MS_OS_20_SUBSET_HEADER_CONFIGURATION */
  uint8_t  ConfigurationValue; /**< The configuration value for the USB configuration to which this subset applies. */
  uint8_t  Reserved;           /**< Shall be set to 0. */
  uint16_t TotalLength;        /**< The size of entire configuration subset including this header. */
} ATTR_PACKED MS_OS_20_Configuration_Subset_Header;

/** \brief Microsoft OS 2.0 Function subset header.
 *
 */
typedef struct {
  uint16_t Length;         /**< The length, in bytes, of this subset header. Shall be set to 8. */
  uint16_t DescriptorType; /**< MS_OS_20_SUBSET_HEADER_FUNCTION */
  uint8_t  FirstInterface; /**< The interface number for the first interface of the function to which this subset applies. */
  uint8_t  Reserved;       /**< Shall be set to 0. */
  uint16_t SubsetLength;   /**< The size of entire function subset including this header. */
} ATTR_PACKED MS_OS_20_Function_Subset_Header;

/** \brief Microsoft OS 2.0 Feature Descriptor for CompatibleID.
 *
 *  These values are used by Windows to locate the appropriate driver for the device.
 *
 *  For WebUSB in Chrome, the CompatibleID needs to be WINUSB, and the SubCompatibleID is null.
 *
 *  \note ID values must be 8 bytes long and contain only the ASCII values for uppercase letters, numbers, underscores, and the NULL character. No other characters are allowed, and the last byte in the ID must be the NULL 0x00.
 */
typedef struct {
  uint16_t Length;             /**< The length, bytes, of the compatible ID descriptor including value descriptors. Shall be set to 20. */
  uint16_t DescriptorType;     /**< MS_OS_20_FEATURE_COMPATIBLE_ID */
  uint8_t  CompatibleID[8];    /**< Compatible ID ASCII String */
  uint8_t  SubCompatibleID[8]; /**< Sub-compatible ID ASCII String */
} ATTR_PACKED MS_OS_20_CompatibleID_Descriptor;

/** \brief Property Data Type values for the Microsoft OS 2.0 Registry Property Descriptor.
 *
 */
enum MS_OS_20_Property_Data_Types {
  MS_OS_20_REG_SZ                  = 1, /**< A NULL-terminated Unicode String */
  MS_OS_20_REG_EXPAND_SZ           = 2, /**< A NULL-terminated Unicode String that includes environment variables */
  MS_OS_20_REG_BINARY              = 3, /**< Free-form binary */
  MS_OS_20_REG_DWORD_LITTLE_ENDIAN = 4, /**< A little-endian 32-bit integer */
  MS_OS_20_REG_DWORD_BIG_ENDIAN    = 5, /**< A big-endian 32-bit integer */
  MS_OS_20_REG_LINK                = 6, /**< A NULL-terminated Unicode string that contains a symbolic link */
  MS_OS_20_REG_MULTI_SZ            = 7  /**< Multiple NULL-terminated Unicode strings */
};

/** \brief Microsoft OS 2.0 Registry Property Descriptor.
 *
 *  This descriptor is used to add per-device or per-function registry values that is read by the Windows USB driver stack or the device’s function driver.
 */
typedef struct {
  uint16_t Length;             /**< The length in bytes of is descriptor. */
  uint16_t DescriptorType;     /**< MS_OS_20_FEATURE_REG_PROPERTY */
  uint16_t PropertyDataType;   /**< MS_OS_20_Property_Data_types, MS_OS_20_REG_MULTI_SZ even for single interface because libusb. */
  uint16_t PropertyNameLength; /**< The length of the property name. */
  uint8_t  PropertyName[MS_OS_20_PROPERTY_NAME_LENGTH]; /**< The name of registry property as NULL-terminated UTF-16 LE string. */
  uint16_t PropertyDataLength; /**< The length of property data. */
  uint8_t  PropertyData[MS_OS_20_PROPERTY_DATA_LENGTH]; /**< Property Data. */
} ATTR_PACKED MS_OS_20_Registry_Property_Descriptor;

/** \brief Microsoft OS 2.0 Feature Descriptor for CCGP Devices.
 *
 *  This descriptor indicates that the device should be treated as a composite device by Windows regardless of
 *  the number of interfaces, configuration, or class, subclass, and protocol codes, the device reports.
 *
 *  \note The CCGP device descriptor must be applied to the entire device.
 */
typedef struct {
  uint16_t Length;         /**< The length, bytes, of the compatible ID descriptor including value descriptors. Shall be set to 4. */
  uint16_t DescriptorType; /**< MS_OS_20_FEATURE_CCGP_DEVICE */
} ATTR_PACKED MS_OS_20_CCGP_Device_Descriptor;

typedef struct {
  MS_OS_20_Descriptor_Set_Header_t      Header;
  MS_OS_20_Configuration_Subset_Header  ConfigurationSubsetHeader;
  MS_OS_20_Function_Subset_Header       FunctionSubsetHeader;
  MS_OS_20_CompatibleID_Descriptor      CompatibleID;
  MS_OS_20_Registry_Property_Descriptor RegistryProperty;
} MS_OS_20_Descriptor_t;

#define MS_OS_20_DESCRIPTOR { \
    .Header = { \
        .Length = CPU_TO_LE16(10), \
        .DescriptorType = CPU_TO_LE16(MS_OS_20_SET_HEADER_DESCRIPTOR), \
        .WindowsVersion = MS_OS_20_WINDOWS_VERSION_8_1, \
        .TotalLength = CPU_TO_LE16(MS_OS_20_DESCRIPTOR_SET_TOTAL_LENGTH) \
    }, \
    .ConfigurationSubsetHeader = { \
        .Length = CPU_TO_LE16(8), \
        .DescriptorType = CPU_TO_LE16(MS_OS_20_SUBSET_HEADER_CONFIGURATION), \
        .ConfigurationValue = 0, \
        .Reserved = 0, \
        .TotalLength = CPU_TO_LE16(MS_OS_20_DESCRIPTOR_CONFIGURATION_HEADER_LENGTH) \
    }, \
    .FunctionSubsetHeader = { \
        .Length = CPU_TO_LE16(8), \
        .DescriptorType = CPU_TO_LE16(MS_OS_20_SUBSET_HEADER_FUNCTION), \
        .FirstInterface = INTERFACE_ID_WebUSB, \
        .Reserved = 0, \
        .SubsetLength = CPU_TO_LE16(MS_OS_20_DESCRIPTOR_FUNCTION_HEADER_LENGTH) \
    }, \
    .CompatibleID = { \
        .Length = CPU_TO_LE16(20), \
        .DescriptorType  = CPU_TO_LE16(MS_OS_20_FEATURE_COMPATBLE_ID), \
        .CompatibleID = MS_OS_20_DESCRIPTOR_COMPATIBILITY_ID, \
        .SubCompatibleID = MS_OS_20_DESCRIPTOR_SUB_COMPATIBILITY_ID \
    }, \
    .RegistryProperty = { \
        .Length = CPU_TO_LE16(132), \
        .DescriptorType = CPU_TO_LE16(MS_OS_20_FEATURE_REG_PROPERTY), \
        .PropertyDataType = CPU_TO_LE16(MS_OS_20_REG_MULTI_SZ), \
        .PropertyNameLength = CPU_TO_LE16(MS_OS_20_PROPERTY_NAME_LENGTH), \
        .PropertyName = MS_OS_20_PROPERTY_NAME, \
        .PropertyDataLength = CPU_TO_LE16(MS_OS_20_PROPERTY_DATA_LENGTH), \
        .PropertyData = MS_OS_20_PROPERTY_DATA \
    } \
}


// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
// based on https://github.com/cirque-corp/Cirque_Pinnacle_1CA027/tree/master/Additional_Examples
// with modifications and changes for QMK
// refer to documentation: Gen2 and Gen3 (Pinnacle ASIC) at https://www.cirque.com/gen2gen3-asic-details

#pragma once

// clang-format off

#define Cirque_HostReg__0      (0x00)
#define Cirque_HostReg__1      (0x01)
#define Cirque_HostReg__2      (0x02)
#define Cirque_HostReg__3      (0x03)
#define Cirque_HostReg__4      (0x04)
#define Cirque_HostReg__5      (0x05)
#define Cirque_HostReg__6      (0x06)
#define Cirque_HostReg__7      (0x07)
#define Cirque_HostReg__8      (0x08)
#define Cirque_HostReg__9      (0x09)
#define Cirque_HostReg__10     (0x0A)
#define Cirque_HostReg__11     (0x0B)
#define Cirque_HostReg__12     (0x0C)
#define Cirque_HostReg__13     (0x0D)
#define Cirque_HostReg__14     (0x0E)
#define Cirque_HostReg__15     (0x0F)
#define Cirque_HostReg__16     (0x10)
#define Cirque_HostReg__17     (0x11)
#define Cirque_HostReg__18     (0x12)
#define Cirque_HostReg__19     (0x13)
#define Cirque_HostReg__20     (0x14)
#define Cirque_HostReg__21     (0x15)
#define Cirque_HostReg__22     (0x16)
#define Cirque_HostReg__23     (0x17)
#define Cirque_HostReg__24     (0x18)
#define Cirque_HostReg__25     (0x19)
#define Cirque_HostReg__26     (0x1A)
#define Cirque_HostReg__27     (0x1B)
#define Cirque_HostReg__28     (0x1C)
#define Cirque_HostReg__29     (0x1D)
#define Cirque_HostReg__30     (0x1E)
#define Cirque_HostReg__31     (0x1F)

// ---------------- Register Assignments -------------------------------------

/*--------------------------------------------------------------------------*\
                           Chip ID / Version
\*--------------------------------------------------------------------------*/
// Chip ID Register
#define CIRQUE_HOSTREG__CHIPID                                             Cirque_HostReg__0

// Chip Version Register
#define CIRQUE_HOSTREG__VERSION                                            Cirque_HostReg__1

/*--------------------------------------------------------------------------*\
                           Status Register
\*--------------------------------------------------------------------------*/
// Status 1 Register -- MUST BE CIRQUE_HOSTREG__2
#define CIRQUE_HOSTREG__STATUS1                                            Cirque_HostReg__2
#    define CIRQUE_HOSTREG__STATUS1__DATA_READY                            0x04
#    define CIRQUE_HOSTREG__STATUS1__COMMAND_COMPLETE                      0x08
#define CIRQUE_HOSTREG__STATUS1_DEFVAL                                     0x00

/*--------------------------------------------------------------------------*\
                           System Config Register
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__SYSCONFIG1                                         Cirque_HostReg__3
#    define CIRQUE_HOSTREG__SYSCONFIG1__RESET                              0x01
#    define CIRQUE_HOSTREG__SYSCONFIG1__STANDBY                            0x02
#    define CIRQUE_HOSTREG__SYSCONFIG1__AUTO_SLEEP                         0x04
#    define CIRQUE_HOSTREG__SYSCONFIG1__TRACK_DISABLE                      0x08
#    define CIRQUE_HOSTREG__SYSCONFIG1__ANYMEAS_ENABLE                     0x10
#    define CIRQUE_HOSTREG__SYSCONFIG1__GPIO_CTRL_ENABLE                   0x20
#    define CIRQUE_HOSTREG__SYSCONFIG1__WAKEUP_TOGGLE                      0x40
#    define CIRQUE_HOSTREG__SYSCONFIG1__FORCE_WAKEUP                       0x80
#define CIRQUE_HOSTREG__SYSCONFIG1_DEFVAL                                  0x00

/*--------------------------------------------------------------------------*\
                           Feed Config Registers
\*--------------------------------------------------------------------------*/
// Feed Config Register1
#define CIRQUE_HOSTREG__FEEDCONFIG1                                        Cirque_HostReg__4
#    define CIRQUE_HOSTREG__FEEDCONFIG1__FEED_ENABLE                       0x01
#    define CIRQUE_HOSTREG__FEEDCONFIG1__DATA_TYPE__REL0_ABS1              0x02
#    define CIRQUE_HOSTREG__FEEDCONFIG1__FILTER_DISABLE                    0x04
#    define CIRQUE_HOSTREG__FEEDCONFIG1__X_AXIS_DISABLE                    0x08
#    define CIRQUE_HOSTREG__FEEDCONFIG1__Y_AXIS_DISABLE                    0x10
#    define CIRQUE_HOSTREG__FEEDCONFIG1__AXIS_FOR_Z__Y0_X1                 0x20
#    define CIRQUE_HOSTREG__FEEDCONFIG1__X_DATA_INVERT                     0x40
#    define CIRQUE_HOSTREG__FEEDCONFIG1__Y_DATA_INVERT                     0x80
#define CIRQUE_HOSTREG__FEEDCONFIG1_DEFVAL                                 0x00

// Feed Config Register2
#define CIRQUE_HOSTREG__FEEDCONFIG2                                        Cirque_HostReg__5
#    define CIRQUE_HOSTREG__FEEDCONFIG2__INTELLIMOUSE_MODE                 0x01
#    define CIRQUE_HOSTREG__FEEDCONFIG2__ALL_TAP_DISABLE                   0x02
#    define CIRQUE_HOSTREG__FEEDCONFIG2__SECONDARY_TAP_DISABLE             0x04
#    define CIRQUE_HOSTREG__FEEDCONFIG2__SCROLL_DISABLE                    0x08
#    define CIRQUE_HOSTREG__FEEDCONFIG2__GLIDE_EXTEND_DISABLE              0x10
#    define CIRQUE_HOSTREG__FEEDCONFIG2__PALM_BEFORE_Z_ENABLE              0x20
#    define CIRQUE_HOSTREG__FEEDCONFIG2__BUTNS_46_SCROLL_5_MIDDLE          0x40
#    define CIRQUE_HOSTREG__FEEDCONFIG2__SWAP_XY_RELATIVE                  0x80
#define CIRQUE_HOSTREG__FEEDCONFIG2_DEFVAL                                 0x00

// Feed Config Register3
#define CIRQUE_HOSTREG__FEEDCONFIG3                                        Cirque_HostReg__6
#    define CIRQUE_HOSTREG__FEEDCONFIG3__BTNS_456_TO_123_IN_REL            0x01
#    define CIRQUE_HOSTREG__FEEDCONFIG3__DISABLE_CROSS_RATE_SMOOTHING      0x02
#    define CIRQUE_HOSTREG__FEEDCONFIG3__DISABLE_PALM_NERD_MEAS            0x04
#    define CIRQUE_HOSTREG__FEEDCONFIG3__DISABLE_NOISE_AVOIDANCE           0x08
#    define CIRQUE_HOSTREG__FEEDCONFIG3__DISABLE_WRAP_LOCKOUT              0x10
#    define CIRQUE_HOSTREG__FEEDCONFIG3__DISABLE_DYNAMIC_EMI_ADJUST        0x20
#    define CIRQUE_HOSTREG__FEEDCONFIG3__DISABLE_HW_EMI_DETECT             0x40
#    define CIRQUE_HOSTREG__FEEDCONFIG3__DISABLE_SW_EMI_DETECT             0x80
#define CIRQUE_HOSTREG__FEEDCONFIG3_DEFVAL                                 0x00

/*--------------------------------------------------------------------------*\
                           Calibration Config
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__CALCONFIG1                                         Cirque_HostReg__7
#    define CIRQUE_HOSTREG__CALCONFIG1__CALIBRATE                          0x01
#    define CIRQUE_HOSTREG__CALCONFIG1__BACKGROUND_COMP_ENABLE             0x02
#    define CIRQUE_HOSTREG__CALCONFIG1__NERD_COMP_ENABLE                   0x04
#    define CIRQUE_HOSTREG__CALCONFIG1__TRACK_ERROR_COMP_ENABLE            0x08
#    define CIRQUE_HOSTREG__CALCONFIG1__TAP_COMP_ENABLE                    0x10
#    define CIRQUE_HOSTREG__CALCONFIG1__PALM_ERROR_COMP_ENABLE             0x20
#    define CIRQUE_HOSTREG__CALCONFIG1__CALIBRATION_MATRIX_DISABLE         0x40
#    define CIRQUE_HOSTREG__CALCONFIG1__FORCE_PRECALIBRATION_NOISE_CHECK   0x80
#define CIRQUE_HOSTREG__CALCONFIG1_DEFVAL                                  (CIRQUE_HOSTREG__CALCONFIG1__BACKGROUND_COMP_ENABLE | CIRQUE_HOSTREG__CALCONFIG1__NERD_COMP_ENABLE | CIRQUE_HOSTREG__CALCONFIG1__TRACK_ERROR_COMP_ENABLE | CIRQUE_HOSTREG__CALCONFIG1__TAP_COMP_ENABLE | CIRQUE_HOSTREG__CALCONFIG1__PALM_ERROR_COMP_ENABLE)

/*--------------------------------------------------------------------------*\
                           PS2 Aux Control Register
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__PS2AUX_CTRL                                        Cirque_HostReg__8
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__CMD_PASSTHRU_ENABLE               0x01
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__SP_EXTENDED_MODE                  0x02
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__GS_DISABLE                        0x04
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__SP_DISABLE                        0x08
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__GS_COORDINATE_DISABLE             0x10
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__SP_COORDINATE_DISABLE             0x20
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__DISABLE_AA00_DETECT               0x40
#    define CIRQUE_HOSTREG__PS2AUX_CTRL__AUX_PRESENT                       0x80
#define CIRQUE_HOSTREG__PR2AUX_CTRL_DEFVAL                                 0x00

/*--------------------------------------------------------------------------*\
                           Sample Rate Value
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__SAMPLERATE                                         Cirque_HostReg__9
#    define CIRQUE_HOSTREG__SAMPLERATE__10_SPS                             0x0A
#    define CIRQUE_HOSTREG__SAMPLERATE__20_SPS                             0x14
#    define CIRQUE_HOSTREG__SAMPLERATE__40_SPS                             0x28
#    define CIRQUE_HOSTREG__SAMPLERATE__60_SPS                             0x3C
#    define CIRQUE_HOSTREG__SAMPLERATE__80_SPS                             0x50
#    define CIRQUE_HOSTREG__SAMPLERATE__100_SPS                            0x64
#    define CIRQUE_HOSTREG__SAMPLERATE__200_SPS                            0xC8        // 200sps not supported
                                                                                // only for ps2 compatibility
                                                                                // rate set to 100sps
#define CIRQUE_HOSTREG__SAMPLERATE_DEFVAL                                  CIRQUE_HOSTREG__SAMPLERATE__100_SPS

/*--------------------------------------------------------------------------*\
                           Z Idle Value
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__ZIDLE                                              Cirque_HostReg__10
#define CIRQUE_HOSTREG__ZIDLE_DEFVAL                                       30 // 0x1E

/*--------------------------------------------------------------------------*\
                           Z Scaler Value
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__ZSCALER                                            Cirque_HostReg__11
#define CIRQUE_HOSTREG__ZSCALER_DEFVAL                                     8 // 0x08

/*--------------------------------------------------------------------------*\
                           Sleep Interval Value
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__SLEEP_INTERVAL                                     Cirque_HostReg__12
#define CIRQUE_HOSTREG__SLEEP_INTERVAL_DEFVAL                              73 // 0x49

/*--------------------------------------------------------------------------*\
                           Sleep Delay Value
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__SLEEP_DELAY                                        Cirque_HostReg__13
#define CIRQUE_HOSTREG__SLEEP_DELAY_DEFVAL                                 39 // 0x27

/*--------------------------------------------------------------------------*\
                           Dynamic EMI Bad Channel Count Thresholds
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__DYNAMIC_EMI_ADJUST_THRESHOLD                       Cirque_HostReg__14
#define CIRQUE_HOSTREG__DYNAMIC_EMI_ADJUST_THRESHOLD_DEFVAL                66 // 0x42

/*--------------------------------------------------------------------------*\
                           Packet Registers
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__PACKETBYTE_0                                       Cirque_HostReg__18
#define CIRQUE_HOSTREG__PACKETBYTE_1                                       Cirque_HostReg__19
#define CIRQUE_HOSTREG__PACKETBYTE_2                                       Cirque_HostReg__20
#define CIRQUE_HOSTREG__PACKETBYTE_3                                       Cirque_HostReg__21
#define CIRQUE_HOSTREG__PACKETBYTE_4                                       Cirque_HostReg__22
#define CIRQUE_HOSTREG__PACKETBYTE_5                                       Cirque_HostReg__23

/*--------------------------------------------------------------------------*\
                           Port A GPIO Control
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__PORTA_GPIO_CTRL                                    Cirque_HostReg__24
#define CIRQUE_HOSTREG__PORTA_GPIO_CTRL_DEFVAL                             0xFF

/*--------------------------------------------------------------------------*\
                           Port A GPIO Data
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__PORTA_GPIO_DATA                                    Cirque_HostReg__25
#define CIRQUE_HOSTREG__PORTA_GPIO_DATA_DEFVAL                             0x00

/*--------------------------------------------------------------------------*\
                           Port B GPIO Control And Data
\*--------------------------------------------------------------------------*/

#define CIRQUE_HOSTREG__PORTB_GPIO_CTRL_DATA                               Cirque_HostReg__26
#    define CIRQUE_HOSTREG__PORTB_GPIO_DATA__PB0                           0x01
#    define CIRQUE_HOSTREG__PORTB_GPIO_DATA__PB1                           0x02
#    define CIRQUE_HOSTREG__PORTB_GPIO_DATA__PB2                           0x04
#    define CIRQUE_HOSTREG__PORTB_GPIO_CTRL__PB0                           0x08
#    define CIRQUE_HOSTREG__PORTB_GPIO_CTRL__PB1                           0x10
#    define CIRQUE_HOSTREG__PORTB_GPIO_CTRL__PB2                           0x20
#    define CIRQUE_HOSTREG__PORTB_GPIO_RSVD_0                              0x40
#    define CIRQUE_HOSTREG__PORTB_GPIO_READ1_WRITE0                        0x80
#define CIRQUE_HOSTREG__PORTB_GPIO_CTRL_DATA_DEFVAL                        (CIRQUE_HOSTREG__PORTB_GPIO_CTRL__PB0 | CIRQUE_HOSTREG__PORTB_GPIO_CTRL__PB1 | CIRQUE_HOSTREG__PORTB_GPIO_CTRL__PB2)

/*--------------------------------------------------------------------------*\
                           Extended Register Access
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__EXT_REG_AXS_VALUE                                  Cirque_HostReg__27

#define CIRQUE_HOSTREG__EXT_REG_AXS_ADDR_HIGH                              Cirque_HostReg__28
#define CIRQUE_HOSTREG__EXT_REG_AXS_ADDR_LOW                               Cirque_HostReg__29

#define CIRQUE_HOSTREG__EXT_REG_AXS_CTRL                                   Cirque_HostReg__30
#    define CIRQUE_HOSTREG__EREG_AXS__READ                                 0x01
#    define CIRQUE_HOSTREG__EREG_AXS__WRITE                                0x02
#    define CIRQUE_HOSTREG__EREG_AXS__INC_ADDR_READ                        0x04
#    define CIRQUE_HOSTREG__EREG_AXS__INC_ADDR_WRITE                       0x08
#    define CIRQUE_HOSTREG__EREG_AXS__RSVD_3                               0x10
#    define CIRQUE_HOSTREG__EREG_AXS__RSVD_2                               0x20
#    define CIRQUE_HOSTREG__EREG_AXS__RSVD_1                               0x40
#    define CIRQUE_HOSTREG__EREG_AXS__RSVD_0                               0x80

#define CIRQUE_HOSTREG__EXT_REG_AXS_VALUE_DEFVAL                           0x00
#define CIRQUE_HOSTREG__EXT_REG_AXS_ADDR_HIGH_DEFVAL                       0x00
#define CIRQUE_HOSTREG__EXT_REG_AXS_ADDR_LOW_DEFVAL                        0x00
#define CIRQUE_HOSTREG__EXT_REG_AXS_CTRL_DEFVAL                            0x00

/*--------------------------------------------------------------------------*\
                           Product ID
\*--------------------------------------------------------------------------*/
#define CIRQUE_HOSTREG__PRODUCT_ID                                         Cirque_HostReg__31



//Some useful values
#define CIRQUE_I2C_ADDRESS_DEFAULT                                         0x2A
#define CIRQUE_FIRMWARE_ID                                                 0x07
#define CIRQUE_FIRMWARE_VERSION                                            0x9D

//Anymeas config options
//First setting is HostReg 5.  This sets toggle frequency (EF) and gain.
//Gain is upper two bits (0xC0), frequency is lower 6 bits (0x3F)
#define CIRQUE_CIRQUE_AnyMeas_AccumBits_ElecFreq                                  Cirque_HostReg__5
#    define CIRQUE_CIRQUE_ADCCNFG_ELEC_FREQ                                       0x3F  /* Bit 4, 3, 2, 1, 0 */
#        define CIRQUE_ADCCNFG_EF_0                                        0x02  // 500,000Hz
#        define CIRQUE_ADCCNFG_EF_1                                        0x03  // 444,444Hz
#        define CIRQUE_ADCCNFG_EF_2                                        0x04  // 400,000Hz
#        define CIRQUE_ADCCNFG_EF_3                                        0x05  // 363,636Hz
#        define CIRQUE_ADCCNFG_EF_4                                        0x06  // 333,333Hz
#        define CIRQUE_ADCCNFG_EF_5                                        0x07  // 307,692Hz
#        define CIRQUE_ADCCNFG_EF_6                                        0x09  // 267,000Hz
#        define CIRQUE_ADCCNFG_EF_7                                        0x0B  // 235,000Hz
#    define CIRQUE_ADCCNFG_ACCUMBITSSELECT                                 0xC0  /* Bit 7, 6 */
#        define CIRQUE_ADCCNFG_ACCBITS_17_14_0                             0x00  //This is about 2x gain
#        define CIRQUE_ADCCNFG_ACCBITS_17_15_1                             0x40  //This is about 1.6x gain
#        define CIRQUE_ADCCNFG_ACCBITS_17_2__80                            0x80  //This is about 1.3x gain
#        define CIRQUE_ADCCNFG_ACCBITS_17_2__C0                            0xC0  //This is lowest gain
//Note, all frequencies above are based on default 500ns aperture.  If aperture is shorter the frequencies will be faster and if aperture is longer the frequencies will be slower.

//Next is HostReg 6.  This sets the sample length.  There are four possible settings to bit length.  All other settings are not normally used and should be a 0.
#define CIRQUE_AnyMeas_BitLength                                           Cirque_HostReg__6
#    define CIRQUE_ADCCTRL_BIT_LENGTH                                      0x03  /* Bit 1, 0 */
#        define CIRQUE_ADCCTRL_SAMPLES_32                                  0x00  //Note: this does not work.
#        define CIRQUE_ADCCTRL_SAMPLES_128                                 0x01
#        define CIRQUE_ADCCTRL_SAMPLES_256                                 0x02
#        define CIRQUE_ADCCTRL_SAMPLES_512                                 0x03
#    define CIRQUE_ADCCTRL_ENABLE                                          0x20  /* Bit 5 */
#    define CIRQUE_ADCCTRL_INT_FLAG                                        0x40  /* Bit 6 */
#    define CIRQUE_ADCCTRL_START_BUSY                                      0x80  /* Bit 7 */
//The smaller the sample length the faster the measurement but the lower the SNR.  For high SNR requirements 512 sample length is recommended.  Alternatively, multiple 128 or 256 length measurements could be averaged.

//Next is HostReg 7.  This sets the sense mux.  Pinnacle has 2 sense lines, Sense N and Sense P1.  There is also a Sense P2 but it is not bonded out, it is only internal.
//Signal on Sense N will be inverted from signal on Sense P1.  Other than sign inversion, signal strength should be the same.
#define CIRQUE_AnyMeas_ADC_MuxControl                                      Cirque_HostReg__7
#    define CIRQUE_ADCMUXCTRL_SENSEP1GATE                                  0x01  //Enables Sense P1.  Can be combined with Sense N input or exclusivly Sense P1 alone.
#    define CIRQUE_ADCMUXCTRL_SENSEP2GATE                                  0x02  //Not used.
#    define CIRQUE_ADCMUXCTRL_SENSENGATE                                   0x04  //Enables Sense N.  Can be combined with Sense P inputs or exclusivly Sense N alone.
#    define CIRQUE_ADCMUXCTRL_REF0GATE                                     0x08  //This enables the RefCap0.  This is a capacitor inside the chip that is roughly 0.25pF. It is also controlled with the toggle and polarity bits so those bits must be set properly as well in order to use it.
#    define CIRQUE_ADCMUXCTRL_REF1GATE                                     0x10  //This enables the RefCap1.  This is a capacitor inside the chip that is roughly 0.5pF. It is also controlled with the toggle and polarity bits so those bits must be set properly as well in order to use it.
#    define CIRQUE_ADCMUXCTRL_OSCMEASEN                                    0x80  //this is a test mode for measuring the internal oscillator.  It is for IC test only.

//Next is HostReg 8.  This contains various ADC config settings that are not likely to be used.
#define CIRQUE_AnyMeas_ADC_Config2                                         Cirque_HostReg__8
#    define CIRQUE_ADCCNFG2_ADC_CLK_SELECT                                 0x01  /* Bit 0 */   //If 0 use the standard 8Mhz clock.  If 1 use a divide by 2, 4Mhz clock.  Only used if extra slow toggle frequencies are required.
#    define CIRQUE_ADCCNFG2_EMI_FLAG                                       0x02  /* Bit 1 */   //EMI flag threshold only used with internal FW.  Not valid in anymeas mode.
#    define CIRQUE_ADCCNFG2_EMI_FLAG_THRESHOLD_0                           0x04  /* Bit 2 */   //EMI flag threshold only used with internal FW.  Not valid in anymeas mode.
#    define CIRQUE_ADCCNFG2_EMI_FLAG_THRESHOLD_1                           0x08  /* Bit 3 */   //EMI flag threshold only used with internal FW.  Not valid in anymeas mode.
#    define CIRQUE_ADCCNFG2_DSX2_EXTEND                                    0x10  /* Bit 4 */   //extend one signal on the receive.  Could also be helpful in situations where sensor cap is extremely high.
#    define CIRQUE_ADCCNFG2_ETOGGLE_DELAY                                  0x20  /* Bit 5 */   //delay a bit before toggling electrodes.  Could be helpful in situations where sensor cap is extremely high.

//Next is HostReg 9.  This sets the aperture length.  Bottom 4 bits set the aperture width
#define CIRQUE_AnyMeas_ADC_AWidth                                          Cirque_HostReg__9
#    define CIRQUE_ADCAWIDTH_AWIDTHMASK                                    0x0F
#        define CIRQUE_ADCAWIDTH_APERTURE_OPEN                             0x00  //does not work
#        define CIRQUE_ADCAWIDTH_APERTURE_125NS                            0x01  //does not work
#        define CIRQUE_ADCAWIDTH_APERTURE_250NS                            0x02
#        define CIRQUE_ADCAWIDTH_APERTURE_375NS                            0x03
#        define CIRQUE_ADCAWIDTH_APERTURE_500NS                            0x04
#        define CIRQUE_ADCAWIDTH_APERTURE_625NS                            0x05
#        define CIRQUE_ADCAWIDTH_APERTURE_750NS                            0x06
#        define CIRQUE_ADCAWIDTH_APERTURE_875NS                            0x07
#        define CIRQUE_ADCAWIDTH_APERTURE_1000NS                           0x08
#        define CIRQUE_ADCAWIDTH_APERTURE_1125NS                           0x09
#        define CIRQUE_ADCAWIDTH_APERTURE_1250NS                           0x0A
#        define CIRQUE_ADCAWIDTH_APERTURE_1375NS                           0x0B
#        define CIRQUE_ADCAWIDTH_APERTURE_1500NS                           0x0C
#        define CIRQUE_ADCAWIDTH_APERTURE_1625NS                           0x0D
#        define CIRQUE_ADCAWIDTH_APERTURE_1750NS                           0x0E
#        define CIRQUE_ADCAWIDTH_APERTURE_1875NS                           0x0F
#    define CIRQUE_ADCAWIDTH_AWIDTHPLUSHALF                                0x10
#    define CIRQUE_ADCAWIDTH_AOPEN                                         0x20
#    define CIRQUE_ADCAWIDTH_W2WAIT                                        0x40

//next two registers give the high and low bytes to the 16 bit address where Pinnacle will pull the measurement data.  Normally these addresses are within the base 32 registers.
#define CIRQUE_AnyMeas_pADCMeasInfoStart_High_Byte                         Cirque_HostReg__10
#define CIRQUE_AnyMeas_pADCMeasInfoStart_Low_Byte                          Cirque_HostReg__11

//Next is the measurement index, this sets the measurement state machine to the start and should be a 0 at start.
#define CIRQUE_AnyMeas_MeasIndex                                           Cirque_HostReg__12
#   define CIRQUE_ANYMEASSTATE_RESET_START                                 0x00
#   define CIRQUE_ANYMEASSTATE_START_MEASUREMENT                           0x01
#   define CIRQUE_ANYMEASSTATE_WAIT_FOR_MEASUREMENT_AND_HOST               0x02

//next is the state itself of the measurement, should always be 0.
#define CIRQUE_AnyMeas_State                                               Cirque_HostReg__13

//next is the number of measurements.  Use 0x80 to repeat the single measurement or repeat a number of measurements.
//0x40 will turn the ADC off after measurements.  This will result in longer startup time for a subsequent measurement, but lower idle power draw.
#define CIRQUE_AnyMeas_Control_NumMeas                                     Cirque_HostReg__14
#    define CIRQUE_ANYMEAS_CONTROL__NUM_MEAS_MASK                          0x3F
#    define CIRQUE_ANYMEAS_CONTROL__ADC_POST_MEAS_PWR                      0x40
#    define CIRQUE_ANYMEAS_CONTROL__REPEAT                                 0x80

//These are not used
#define CIRQUE_AnyMeas_pADCMeasInfo_High_Byte                              Cirque_HostReg__15
#define CIRQUE_AnyMeas_pADCMeasInfo_Low_Byte                               Cirque_HostReg__16

//16 bit result of measurement will be found in these two registers.
#define CIRQUE_AnyMeas_Result_High_Byte                                    Cirque_HostReg__17
#define CIRQUE_AnyMeas_Result_Low_Byte                                     Cirque_HostReg__18

// ---------------- Extended Register Assignments ----------------------------
/*--------------------------------------------------------------------------*\
                           ADC Mux Control
\*--------------------------------------------------------------------------*/
#define CIRQUE_EXTREG__ADCMUX_CTRL                                         0x00EB
#    define CIRQUE_EXTREG__ADCMUX_CTRL__SNSP_ENABLE                        0x01
#    define CIRQUE_EXTREG__ADCMUX_CTRL__SNSN_ENABLE                        0x04

/*--------------------------------------------------------------------------*\
                           Timer Reload Registers
\*--------------------------------------------------------------------------*/
#define CIRQUE_EXTREG__PACKET_TIMER_RELOAD                                 0x019F
#define CIRQUE_EXTREG__TRACK_TIMER_RELOAD                                  0x019E
// These two registers should have matching content.
#    define CIRQUE_EXTREG__TIMER_RELOAD__300_SPS                           0x06
#    define CIRQUE_EXTREG__TIMER_RELOAD__200_SPS                           0x09
#    define CIRQUE_EXTREG__TIMER_RELOAD__100_SPS                           0x13

/*--------------------------------------------------------------------------*\
                           Track ADC Config
\*--------------------------------------------------------------------------*/
#define CIRQUE_EXTREG__TRACK_ADCCONFIG                                     0x0187
// ADC-attenuation settings (held in BIT_7 and BIT_6)
// 1X = most sensitive, 4X = least sensitive
#    define CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_MASK             0xC0
#        define CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_1X           0x00
#        define CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X           0x40
#        define CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X           0x80
#        define CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X           0xC0
#define CIRQUE_EXTREG__TRACK_ADCCONFIG_DEFVAL                              0x4E


/*--------------------------------------------------------------------------*\
                           Tune Edge Sensitivity
\*--------------------------------------------------------------------------*/
// These registers are not detailed in any publically available documentation
// Names inferred from debug prints in https://github.com/cirque-corp/Cirque_Pinnacle_1CA027/blob/master/Circular_Trackpad
#define CIRQUE_EXTREG__XAXIS_WIDEZMIN                                      0x0149
#define CIRQUE_EXTREG__YAXIS_WIDEZMIN                                      0x0168
#define CIRQUE_EXTREG__XAXIS_WIDEZMIN_DEFVAL                               0x06
#define CIRQUE_EXTREG__YAXIS_WIDEZMIN_DEFVAL                               0x05

// clang-format on

// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
// based on https://github.com/cirque-corp/Cirque_Pinnacle_1CA027/tree/master/Additional_Examples
// with modifications and changes for QMK
// refer to documentation: Gen2 and Gen3 (Pinnacle ASIC) at https://www.cirque.com/gen2gen3-asic-details

#pragma once

// clang-format off

#define HostReg__0      (0x00)
#define HostReg__1      (0x01)
#define HostReg__2      (0x02)
#define HostReg__3      (0x03)
#define HostReg__4      (0x04)
#define HostReg__5      (0x05)
#define HostReg__6      (0x06)
#define HostReg__7      (0x07)
#define HostReg__8      (0x08)
#define HostReg__9      (0x09)
#define HostReg__10     (0x0A)
#define HostReg__11     (0x0B)
#define HostReg__12     (0x0C)
#define HostReg__13     (0x0D)
#define HostReg__14     (0x0E)
#define HostReg__15     (0x0F)
#define HostReg__16     (0x10)
#define HostReg__17     (0x11)
#define HostReg__18     (0x12)
#define HostReg__19     (0x13)
#define HostReg__20     (0x14)
#define HostReg__21     (0x15)
#define HostReg__22     (0x16)
#define HostReg__23     (0x17)
#define HostReg__24     (0x18)
#define HostReg__25     (0x19)
#define HostReg__26     (0x1A)
#define HostReg__27     (0x1B)
#define HostReg__28     (0x1C)
#define HostReg__29     (0x1D)
#define HostReg__30     (0x1E)
#define HostReg__31     (0x1F)

// ---------------- Register Assignments -------------------------------------

/*--------------------------------------------------------------------------*\
                           Chip ID / Version
\*--------------------------------------------------------------------------*/
// Chip ID Register
#define HOSTREG__CHIPID                                             HostReg__0

// Chip Version Register
#define HOSTREG__VERSION                                            HostReg__1

/*--------------------------------------------------------------------------*\
                           Status Register
\*--------------------------------------------------------------------------*/
// Status 1 Register -- MUST BE HOSTREG__2
#define HOSTREG__STATUS1                                            HostReg__2
#    define HOSTREG__STATUS1__DATA_READY                            0x04
#    define HOSTREG__STATUS1__COMMAND_COMPLETE                      0x08
#define HOSTREG__STATUS1_DEFVAL                                     0x00

/*--------------------------------------------------------------------------*\
                           System Config Register
\*--------------------------------------------------------------------------*/
#define HOSTREG__SYSCONFIG1                                         HostReg__3
#    define HOSTREG__SYSCONFIG1__RESET                              0x01
#    define HOSTREG__SYSCONFIG1__STANDBY                            0x02
#    define HOSTREG__SYSCONFIG1__AUTO_SLEEP                         0x04
#    define HOSTREG__SYSCONFIG1__TRACK_DISABLE                      0x08
#    define HOSTREG__SYSCONFIG1__ANYMEAS_ENABLE                     0x10
#    define HOSTREG__SYSCONFIG1__GPIO_CTRL_ENABLE                   0x20
#    define HOSTREG__SYSCONFIG1__WAKEUP_TOGGLE                      0x40
#    define HOSTREG__SYSCONFIG1__FORCE_WAKEUP                       0x80
#define HOSTREG__SYSCONFIG1_DEFVAL                                  0x00

/*--------------------------------------------------------------------------*\
                           Feed Config Registers
\*--------------------------------------------------------------------------*/
// Feed Config Register1
#define HOSTREG__FEEDCONFIG1                                        HostReg__4
#    define HOSTREG__FEEDCONFIG1__FEED_ENABLE                       0x01
#    define HOSTREG__FEEDCONFIG1__DATA_TYPE__REL0_ABS1              0x02
#    define HOSTREG__FEEDCONFIG1__FILTER_DISABLE                    0x04
#    define HOSTREG__FEEDCONFIG1__X_AXIS_DISABLE                    0x08
#    define HOSTREG__FEEDCONFIG1__Y_AXIS_DISABLE                    0x10
#    define HOSTREG__FEEDCONFIG1__AXIS_FOR_Z__Y0_X1                 0x20
#    define HOSTREG__FEEDCONFIG1__X_DATA_INVERT                     0x40
#    define HOSTREG__FEEDCONFIG1__Y_DATA_INVERT                     0x80
#define HOSTREG__FEEDCONFIG1_DEFVAL                                 0x00

// Feed Config Register2
#define HOSTREG__FEEDCONFIG2                                        HostReg__5
#    define HOSTREG__FEEDCONFIG2__INTELLIMOUSE_MODE                 0x01
#    define HOSTREG__FEEDCONFIG2__ALL_TAP_DISABLE                   0x02
#    define HOSTREG__FEEDCONFIG2__SECONDARY_TAP_DISABLE             0x04
#    define HOSTREG__FEEDCONFIG2__SCROLL_DISABLE                    0x08
#    define HOSTREG__FEEDCONFIG2__GLIDE_EXTEND_DISABLE              0x10
#    define HOSTREG__FEEDCONFIG2__PALM_BEFORE_Z_ENABLE              0x20
#    define HOSTREG__FEEDCONFIG2__BUTNS_46_SCROLL_5_MIDDLE          0x40
#    define HOSTREG__FEEDCONFIG2__SWAP_XY_RELATIVE                  0x80
#define HOSTREG__FEEDCONFIG2_DEFVAL                                 0x00

// Feed Config Register3
#define HOSTREG__FEEDCONFIG3                                        HostReg__6
#    define HOSTREG__FEEDCONFIG3__BTNS_456_TO_123_IN_REL            0x01
#    define HOSTREG__FEEDCONFIG3__DISABLE_CROSS_RATE_SMOOTHING      0x02
#    define HOSTREG__FEEDCONFIG3__DISABLE_PALM_NERD_MEAS            0x04
#    define HOSTREG__FEEDCONFIG3__DISABLE_NOISE_AVOIDANCE           0x08
#    define HOSTREG__FEEDCONFIG3__DISABLE_WRAP_LOCKOUT              0x10
#    define HOSTREG__FEEDCONFIG3__DISABLE_DYNAMIC_EMI_ADJUST        0x20
#    define HOSTREG__FEEDCONFIG3__DISABLE_HW_EMI_DETECT             0x40
#    define HOSTREG__FEEDCONFIG3__DISABLE_SW_EMI_DETECT             0x80
#define HOSTREG__FEEDCONFIG3_DEFVAL                                 0x00

/*--------------------------------------------------------------------------*\
                           Calibration Config
\*--------------------------------------------------------------------------*/
#define HOSTREG__CALCONFIG1                                         HostReg__7
#    define HOSTREG__CALCONFIG1__CALIBRATE                          0x01
#    define HOSTREG__CALCONFIG1__BACKGROUND_COMP_ENABLE             0x02
#    define HOSTREG__CALCONFIG1__NERD_COMP_ENABLE                   0x04
#    define HOSTREG__CALCONFIG1__TRACK_ERROR_COMP_ENABLE            0x08
#    define HOSTREG__CALCONFIG1__TAP_COMP_ENABLE                    0x10
#    define HOSTREG__CALCONFIG1__PALM_ERROR_COMP_ENABLE             0x20
#    define HOSTREG__CALCONFIG1__CALIBRATION_MATRIX_DISABLE         0x40
#    define HOSTREG__CALCONFIG1__FORCE_PRECALIBRATION_NOISE_CHECK   0x80
#define HOSTREG__CALCONFIG1_DEFVAL                                  (HOSTREG__CALCONFIG1__BACKGROUND_COMP_ENABLE | HOSTREG__CALCONFIG1__NERD_COMP_ENABLE | HOSTREG__CALCONFIG1__TRACK_ERROR_COMP_ENABLE | HOSTREG__CALCONFIG1__TAP_COMP_ENABLE | HOSTREG__CALCONFIG1__PALM_ERROR_COMP_ENABLE)

/*--------------------------------------------------------------------------*\
                           PS2 Aux Control Register
\*--------------------------------------------------------------------------*/
#define HOSTREG__PS2AUX_CTRL                                        HostReg__8
#    define HOSTREG__PS2AUX_CTRL__CMD_PASSTHRU_ENABLE               0x01
#    define HOSTREG__PS2AUX_CTRL__SP_EXTENDED_MODE                  0x02
#    define HOSTREG__PS2AUX_CTRL__GS_DISABLE                        0x04
#    define HOSTREG__PS2AUX_CTRL__SP_DISABLE                        0x08
#    define HOSTREG__PS2AUX_CTRL__GS_COORDINATE_DISABLE             0x10
#    define HOSTREG__PS2AUX_CTRL__SP_COORDINATE_DISABLE             0x20
#    define HOSTREG__PS2AUX_CTRL__DISABLE_AA00_DETECT               0x40
#    define HOSTREG__PS2AUX_CTRL__AUX_PRESENT                       0x80
#define HOSTREG__PR2AUX_CTRL_DEFVAL                                 0x00

/*--------------------------------------------------------------------------*\
                           Sample Rate Value
\*--------------------------------------------------------------------------*/
#define HOSTREG__SAMPLERATE                                         HostReg__9
#    define HOSTREG__SAMPLERATE__10_SPS                             0x0A
#    define HOSTREG__SAMPLERATE__20_SPS                             0x14
#    define HOSTREG__SAMPLERATE__40_SPS                             0x28
#    define HOSTREG__SAMPLERATE__60_SPS                             0x3C
#    define HOSTREG__SAMPLERATE__80_SPS                             0x50
#    define HOSTREG__SAMPLERATE__100_SPS                            0x64
#    define HOSTREG__SAMPLERATE__200_SPS                            0xC8        // 200sps not supported
                                                                                // only for ps2 compatibility
                                                                                // rate set to 100sps
#define HOSTREG__SAMPLERATE_DEFVAL                                  HOSTREG__SAMPLERATE__100_SPS

/*--------------------------------------------------------------------------*\
                           Z Idle Value
\*--------------------------------------------------------------------------*/
#define HOSTREG__ZIDLE                                              HostReg__10
#define HOSTREG__ZIDLE_DEFVAL                                       30 // 0x1E

/*--------------------------------------------------------------------------*\
                           Z Scaler Value
\*--------------------------------------------------------------------------*/
#define HOSTREG__ZSCALER                                            HostReg__11
#define HOSTREG__ZSCALER_DEFVAL                                     8 // 0x08

/*--------------------------------------------------------------------------*\
                           Sleep Interval Value
\*--------------------------------------------------------------------------*/
#define HOSTREG__SLEEP_INTERVAL                                     HostReg__12
#define HOSTREG__SLEEP_INTERVAL_DEFVAL                              73 // 0x49

/*--------------------------------------------------------------------------*\
                           Sleep Delay Value
\*--------------------------------------------------------------------------*/
#define HOSTREG__SLEEP_DELAY                                        HostReg__13
#define HOSTREG__SLEEP_DELAY_DEFVAL                                 39 // 0x27

/*--------------------------------------------------------------------------*\
                           Dynamic EMI Bad Channel Count Thresholds
\*--------------------------------------------------------------------------*/
#define HOSTREG__DYNAMIC_EMI_ADJUST_THRESHOLD                       HostReg__14
#define HOSTREG__DYNAMIC_EMI_ADJUST_THRESHOLD_DEFVAL                66 // 0x42

/*--------------------------------------------------------------------------*\
                           Packet Registers
\*--------------------------------------------------------------------------*/
#define HOSTREG__PACKETBYTE_0                                       HostReg__18
#define HOSTREG__PACKETBYTE_1                                       HostReg__19
#define HOSTREG__PACKETBYTE_2                                       HostReg__20
#define HOSTREG__PACKETBYTE_3                                       HostReg__21
#define HOSTREG__PACKETBYTE_4                                       HostReg__22
#define HOSTREG__PACKETBYTE_5                                       HostReg__23

/*--------------------------------------------------------------------------*\
                           Port A GPIO Control
\*--------------------------------------------------------------------------*/
#define HOSTREG__PORTA_GPIO_CTRL                                    HostReg__24
#define HOSTREG__PORTA_GPIO_CTRL_DEFVAL                             0xFF

/*--------------------------------------------------------------------------*\
                           Port A GPIO Data
\*--------------------------------------------------------------------------*/
#define HOSTREG__PORTA_GPIO_DATA                                    HostReg__25
#define HOSTREG__PORTA_GPIO_DATA_DEFVAL                             0x00

/*--------------------------------------------------------------------------*\
                           Port B GPIO Control And Data
\*--------------------------------------------------------------------------*/

#define HOSTREG__PORTB_GPIO_CTRL_DATA                               HostReg__26
#    define HOSTREG__PORTB_GPIO_DATA__PB0                           0x01
#    define HOSTREG__PORTB_GPIO_DATA__PB1                           0x02
#    define HOSTREG__PORTB_GPIO_DATA__PB2                           0x04
#    define HOSTREG__PORTB_GPIO_CTRL__PB0                           0x08
#    define HOSTREG__PORTB_GPIO_CTRL__PB1                           0x10
#    define HOSTREG__PORTB_GPIO_CTRL__PB2                           0x20
#    define HOSTREG__PORTB_GPIO_RSVD_0                              0x40
#    define HOSTREG__PORTB_GPIO_READ1_WRITE0                        0x80
#define HOSTREG__PORTB_GPIO_CTRL_DATA_DEFVAL                        (HOSTREG__PORTB_GPIO_CTRL__PB0 | HOSTREG__PORTB_GPIO_CTRL__PB1 | HOSTREG__PORTB_GPIO_CTRL__PB2)

/*--------------------------------------------------------------------------*\
                           Extended Register Access
\*--------------------------------------------------------------------------*/
#define HOSTREG__EXT_REG_AXS_VALUE                                  HostReg__27

#define HOSTREG__EXT_REG_AXS_ADDR_HIGH                              HostReg__28
#define HOSTREG__EXT_REG_AXS_ADDR_LOW                               HostReg__29

#define HOSTREG__EXT_REG_AXS_CTRL                                   HostReg__30
#    define HOSTREG__EREG_AXS__READ                                 0x01
#    define HOSTREG__EREG_AXS__WRITE                                0x02
#    define HOSTREG__EREG_AXS__INC_ADDR_READ                        0x04
#    define HOSTREG__EREG_AXS__INC_ADDR_WRITE                       0x08
#    define HOSTREG__EREG_AXS__RSVD_3                               0x10
#    define HOSTREG__EREG_AXS__RSVD_2                               0x20
#    define HOSTREG__EREG_AXS__RSVD_1                               0x40
#    define HOSTREG__EREG_AXS__RSVD_0                               0x80

#define HOSTREG__EXT_REG_AXS_VALUE_DEFVAL                           0x00
#define HOSTREG__EXT_REG_AXS_ADDR_HIGH_DEFVAL                       0x00
#define HOSTREG__EXT_REG_AXS_ADDR_LOW_DEFVAL                        0x00
#define HOSTREG__EXT_REG_AXS_CTRL_DEFVAL                            0x00

/*--------------------------------------------------------------------------*\
                           Product ID
\*--------------------------------------------------------------------------*/
#define HOSTREG__PRODUCT_ID                                         HostReg__31



//Some useful values
#define I2C_ADDRESS_DEFAULT                                         0x2A
#define FIRMWARE_ID                                                 0x07
#define FIRMWARE_VERSION                                            0x9D

//Anymeas config options
//First setting is HostReg 5.  This sets toggle frequency (EF) and gain.
//Gain is upper two bits (0xC0), frequency is lower 6 bits (0x3F)
#define AnyMeas_AccumBits_ElecFreq                                  HostReg__5
#    define ADCCNFG_ELEC_FREQ                                       0x3F  /* Bit 4, 3, 2, 1, 0 */
#        define ADCCNFG_EF_0                                        0x02  // 500,000Hz
#        define ADCCNFG_EF_1                                        0x03  // 444,444Hz
#        define ADCCNFG_EF_2                                        0x04  // 400,000Hz
#        define ADCCNFG_EF_3                                        0x05  // 363,636Hz
#        define ADCCNFG_EF_4                                        0x06  // 333,333Hz
#        define ADCCNFG_EF_5                                        0x07  // 307,692Hz
#        define ADCCNFG_EF_6                                        0x09  // 267,000Hz
#        define ADCCNFG_EF_7                                        0x0B  // 235,000Hz
#    define ADCCNFG_ACCUMBITSSELECT                                 0xC0  /* Bit 7, 6 */
#        define ADCCNFG_ACCBITS_17_14_0                             0x00  //This is about 2x gain
#        define ADCCNFG_ACCBITS_17_15_1                             0x40  //This is about 1.6x gain
#        define ADCCNFG_ACCBITS_17_2__80                            0x80  //This is about 1.3x gain
#        define ADCCNFG_ACCBITS_17_2__C0                            0xC0  //This is lowest gain
//Note, all frequencies above are based on default 500ns aperture.  If aperture is shorter the frequencies will be faster and if aperture is longer the frequencies will be slower.

//Next is HostReg 6.  This sets the sample length.  There are four possible settings to bit length.  All other settings are not normally used and should be a 0.
#define AnyMeas_BitLength                                           HostReg__6
#    define ADCCTRL_BIT_LENGTH                                      0x03  /* Bit 1, 0 */
#        define ADCCTRL_SAMPLES_32                                  0x00  //Note: this does not work.
#        define ADCCTRL_SAMPLES_128                                 0x01
#        define ADCCTRL_SAMPLES_256                                 0x02
#        define ADCCTRL_SAMPLES_512                                 0x03
#    define ADCCTRL_ENABLE                                          0x20  /* Bit 5 */
#    define ADCCTRL_INT_FLAG                                        0x40  /* Bit 6 */
#    define ADCCTRL_START_BUSY                                      0x80  /* Bit 7 */
//The smaller the sample length the faster the measurement but the lower the SNR.  For high SNR requirements 512 sample length is recommended.  Alternatively, multiple 128 or 256 length measurements could be averaged.

//Next is HostReg 7.  This sets the sense mux.  Pinnacle has 2 sense lines, Sense N and Sense P1.  There is also a Sense P2 but it is not bonded out, it is only internal.
//Signal on Sense N will be inverted from signal on Sense P1.  Other than sign inversion, signal strength should be the same.
#define AnyMeas_ADC_MuxControl                                      HostReg__7
#    define ADCMUXCTRL_SENSEP1GATE                                  0x01  //Enables Sense P1.  Can be combined with Sense N input or exclusivly Sense P1 alone.
#    define ADCMUXCTRL_SENSEP2GATE                                  0x02  //Not used.
#    define ADCMUXCTRL_SENSENGATE                                   0x04  //Enables Sense N.  Can be combined with Sense P inputs or exclusivly Sense N alone.
#    define ADCMUXCTRL_REF0GATE                                     0x08  //This enables the RefCap0.  This is a capacitor inside the chip that is roughly 0.25pF. It is also controlled with the toggle and polarity bits so those bits must be set properly as well in order to use it.
#    define ADCMUXCTRL_REF1GATE                                     0x10  //This enables the RefCap1.  This is a capacitor inside the chip that is roughly 0.5pF. It is also controlled with the toggle and polarity bits so those bits must be set properly as well in order to use it.
#    define ADCMUXCTRL_OSCMEASEN                                    0x80  //this is a test mode for measuring the internal oscillator.  It is for IC test only.

//Next is HostReg 8.  This contains various ADC config settings that are not likely to be used.
#define AnyMeas_ADC_Config2                                         HostReg__8
#    define ADCCNFG2_ADC_CLK_SELECT                                 0x01  /* Bit 0 */   //If 0 use the standard 8Mhz clock.  If 1 use a divide by 2, 4Mhz clock.  Only used if extra slow toggle frequencies are required.
#    define ADCCNFG2_EMI_FLAG                                       0x02  /* Bit 1 */   //EMI flag threshold only used with internal FW.  Not valid in anymeas mode.
#    define ADCCNFG2_EMI_FLAG_THRESHOLD_0                           0x04  /* Bit 2 */   //EMI flag threshold only used with internal FW.  Not valid in anymeas mode.
#    define ADCCNFG2_EMI_FLAG_THRESHOLD_1                           0x08  /* Bit 3 */   //EMI flag threshold only used with internal FW.  Not valid in anymeas mode.
#    define ADCCNFG2_DSX2_EXTEND                                    0x10  /* Bit 4 */   //extend one signal on the receive.  Could also be helpful in situations where sensor cap is extremely high.
#    define ADCCNFG2_ETOGGLE_DELAY                                  0x20  /* Bit 5 */   //delay a bit before toggling electrodes.  Could be helpful in situations where sensor cap is extremely high.

//Next is HostReg 9.  This sets the aperture length.  Bottom 4 bits set the aperture width
#define AnyMeas_ADC_AWidth                                          HostReg__9
#    define ADCAWIDTH_AWIDTHMASK                                    0x0F
#        define ADCAWIDTH_APERTURE_OPEN                             0x00  //does not work
#        define ADCAWIDTH_APERTURE_125NS                            0x01  //does not work
#        define ADCAWIDTH_APERTURE_250NS                            0x02
#        define ADCAWIDTH_APERTURE_375NS                            0x03
#        define ADCAWIDTH_APERTURE_500NS                            0x04
#        define ADCAWIDTH_APERTURE_625NS                            0x05
#        define ADCAWIDTH_APERTURE_750NS                            0x06
#        define ADCAWIDTH_APERTURE_875NS                            0x07
#        define ADCAWIDTH_APERTURE_1000NS                           0x08
#        define ADCAWIDTH_APERTURE_1125NS                           0x09
#        define ADCAWIDTH_APERTURE_1250NS                           0x0A
#        define ADCAWIDTH_APERTURE_1375NS                           0x0B
#        define ADCAWIDTH_APERTURE_1500NS                           0x0C
#        define ADCAWIDTH_APERTURE_1625NS                           0x0D
#        define ADCAWIDTH_APERTURE_1750NS                           0x0E
#        define ADCAWIDTH_APERTURE_1875NS                           0x0F
#    define ADCAWIDTH_AWIDTHPLUSHALF                                0x10
#    define ADCAWIDTH_AOPEN                                         0x20
#    define ADCAWIDTH_W2WAIT                                        0x40

//next two registers give the high and low bytes to the 16 bit address where Pinnacle will pull the measurement data.  Normally these addresses are within the base 32 registers.
#define AnyMeas_pADCMeasInfoStart_High_Byte                         HostReg__10
#define AnyMeas_pADCMeasInfoStart_Low_Byte                          HostReg__11

//Next is the measurement index, this sets the measurement state machine to the start and should be a 0 at start.
#define AnyMeas_MeasIndex                                           HostReg__12
#   define ANYMEASSTATE_RESET_START                                 0x00
#   define ANYMEASSTATE_START_MEASUREMENT                           0x01
#   define ANYMEASSTATE_WAIT_FOR_MEASUREMENT_AND_HOST               0x02

//next is the state itself of the measurement, should always be 0.
#define AnyMeas_State                                               HostReg__13

//next is the number of measurements.  Use 0x80 to repeat the single measurement or repeat a number of measurements.
//0x40 will turn the ADC off after measurements.  This will result in longer startup time for a subsequent measurement, but lower idle power draw.
#define AnyMeas_Control_NumMeas                                     HostReg__14
#    define ANYMEAS_CONTROL__NUM_MEAS_MASK                          0x3F
#    define ANYMEAS_CONTROL__ADC_POST_MEAS_PWR                      0x40
#    define ANYMEAS_CONTROL__REPEAT                                 0x80

//These are not used
#define AnyMeas_pADCMeasInfo_High_Byte                              HostReg__15
#define AnyMeas_pADCMeasInfo_Low_Byte                               HostReg__16

//16 bit result of measurement will be found in these two registers.
#define AnyMeas_Result_High_Byte                                    HostReg__17
#define AnyMeas_Result_Low_Byte                                     HostReg__18

// ---------------- Extended Register Assignments ----------------------------
/*--------------------------------------------------------------------------*\
                           ADC Mux Control
\*--------------------------------------------------------------------------*/
#define EXTREG__ADCMUX_CTRL                                         0x00EB
#    define EXTREG__ADCMUX_CTRL__SNSP_ENABLE                        0x01
#    define EXTREG__ADCMUX_CTRL__SNSN_ENABLE                        0x04

/*--------------------------------------------------------------------------*\
                           Timer Reload Registers
\*--------------------------------------------------------------------------*/
#define EXTREG__PACKET_TIMER_RELOAD                                 0x019F
#define EXTREG__TRACK_TIMER_RELOAD                                  0x019E
// These two registers should have matching content.
#    define EXTREG__TIMER_RELOAD__300_SPS                           0x06
#    define EXTREG__TIMER_RELOAD__200_SPS                           0x09
#    define EXTREG__TIMER_RELOAD__100_SPS                           0x13

/*--------------------------------------------------------------------------*\
                           Track ADC Config
\*--------------------------------------------------------------------------*/
#define EXTREG__TRACK_ADCCONFIG                                     0x0187
// ADC-attenuation settings (held in BIT_7 and BIT_6)
// 1X = most sensitive, 4X = least sensitive
#    define EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_MASK             0x3F
#        define EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_1X           0x00
#        define EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X           0x40
#        define EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X           0x80
#        define EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X           0xC0
#define EXTREG__TRACK_ADCCONFIG_DEFVAL                              0x4E


/*--------------------------------------------------------------------------*\
                           Tune Edge Sensitivity
\*--------------------------------------------------------------------------*/
// These registers are not detailed in any publically available documentation
// Names inferred from debug prints in https://github.com/cirque-corp/Cirque_Pinnacle_1CA027/blob/master/Circular_Trackpad
#define EXTREG__XAXIS_WIDEZMIN                                      0x0149
#define EXTREG__YAXIS_WIDEZMIN                                      0x0168
#define EXTREG__XAXIS_WIDEZMIN_DEFVAL                               0x06
#define EXTREG__YAXIS_WIDEZMIN_DEFVAL                               0x05

// clang-format on

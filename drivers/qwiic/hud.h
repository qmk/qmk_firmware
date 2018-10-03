/*
  This is an example of how to write a library that allows user to pass in an I2C port

  Nathan Seidle
  SparkFun Electronics

  License: Public domain
*/

#include < Wire.h >

uint16_t DisplayLimit[6] = {199, 999, 999, 999, 99, 199};

bool begin(TwoWire & wirePort = Wire); //If user doesn't specify then Wire will be used

void AdjustIconLevel(uint16_t IconNo, uint16_t IconLevel);
void D01(uint8_t Action);
void CC1(uint8_t Action);
void D02(uint8_t Action);
void CC2(uint8_t Action);
void D03(uint8_t Action);
void CC3(uint8_t Action);
void D04(uint8_t Action);
void CC4(uint8_t Action);
void D05(uint8_t Action);
void CC5(uint8_t Action);
void D06(uint8_t Action);
void CC6(uint8_t Action);
void D07(uint8_t Action);
void CC7(uint8_t Action);
void D08(uint8_t Action);
void CC8(uint8_t Action);
void D0x(uint8_t Action);
void C01(uint8_t Action);
void C02(uint8_t Action);
void H01(uint8_t Action);
void K01(uint8_t Action);
void M01(uint8_t Action);
void C03(uint8_t Action);
void K02(uint8_t Action);
void M03(uint8_t Action);
void P01(uint8_t Action);
void P02(uint8_t Action);
void P03(uint8_t Action);
void T01(uint8_t Action);
void T02(uint8_t Action);

void compassCircle(uint8_t Select);
void compassArrows(uint8_t Select);
void radarDistanceUnits(uint8_t Action);
void flag(uint8_t Action);
void tirePressureAlert(uint8_t Action);
void speedometerUnits(uint8_t Action);
void destinationDistanceUnits(uint8_t iconUnits);
void turnDistanceUnits(uint8_t iconUnits);

void leftTunnel(uint8_t Action);
void middleTunnel(uint8_t Action);
void rightTunnel(uint8_t Action);
void leftRoad(uint8_t Action);
void middleRoad(uint8_t Action);
void rightRoad(uint8_t Action);

void nav_Group(uint8_t Action);
void nav_KeepLeft(uint8_t Action);
void nav_TurnLeft(uint8_t Action);
void nav_TurnRight(uint8_t Action);
void nav_HardRight(uint8_t Action);
void nav_HardLeft(uint8_t Action);
void nav_UTurnLeft(uint8_t Action);
void nav_UTurnRight(uint8_t Action);
void nav_ContinueStraight(uint8_t Action);
void nav_KeepRight(uint8_t Action);

void radarDetector(uint8_t Level);
void setHeading(uint8_t SpeedNo);
void setDestinationDistance(uint16_t SpeedNo, uint8_t Mode);
void setRadarDistance(uint16_t SpeedNo, uint8_t Mode);
void setTurnDistance(uint16_t SpeedNo, uint8_t Mode);
void setTirePressure(uint8_t SpeedNo, uint8_t Mode);
void setSpeedometer(uint8_t SpeedNo);
void setCallIcon(uint8_t iconStatus);

void clearAll(void);

void IIC_Write_Command1(uint8_t IIC_Addr, uint16_t DataLen, uint8_t * DataPtr);
void IIC_Write_Data1(uint8_t IIC_Addr, uint16_t DataLen, uint8_t * DataPtr);
void IIC_Write_Data2(uint8_t IIC_Addr, uint16_t DataLen,
  const uint8_t * DataPtr);

private:

uint16_t S1_2_3;
uint16_t S4_5_6;
uint16_t S7_8_9;
uint16_t S10_11_12;
uint16_t S13_14;
uint16_t S15_16_17;

uint16_t ChangeRedValue(uint16_t OriginalValue, uint16_t R_Value);
uint16_t ChangeGreenValue(uint16_t OriginalValue, uint16_t G_Value);
uint16_t ChangeBlueValue(uint16_t OriginalValue, uint16_t B_Value);
uint16_t ChangeRG_Value(uint16_t OriginalValue, uint16_t RG_Value);
uint16_t ChangeGB_Value(uint16_t OriginalValue, uint16_t GB_Value);
uint16_t SetRGB_Value(uint16_t RGB_Value);
void NumericalTo4BCD(uint16_t S_Number, uint8_t * BCD_Ptr);

void DispNumber(const uint16_t * SegIconPtr, uint8_t DispNo);

void SoftReset(unsigned char DriverNo);
void SetOscControl(unsigned char DriverNo, unsigned char mode);
void SetGraphicsRAMWritingDirection(unsigned char DriverNo, unsigned char mode);
void SetInterface(unsigned char DriverNo, unsigned char mode);
void DisplayOnOff(unsigned char DriverNo, unsigned char Val);
void DisplayStandbyOnOff(unsigned char DriverNo, unsigned char Val);
void SetDisplaySize(unsigned char DriverNo, unsigned char Xstart, unsigned char Xend, unsigned char Ystart, unsigned char Yend);
void SetDotCurrent(unsigned char DriverNo, unsigned char Rlevel, unsigned char Glevel, unsigned char Blevel);
void SetSystemClockDivisionRatio(unsigned char DriverNo, unsigned char mode);
void SetPreChargeWidth(unsigned char DriverNo, unsigned char Val);
void SetPeakPulseWidth(unsigned char DriverNo, unsigned char Rlevel, unsigned char Glevel, unsigned char Blevel);
void SetPeakPulseDelay(unsigned char DriverNo, unsigned char Val);
void SetRowScanOperation(unsigned char DriverNo, unsigned char mode);
void SetInternalRegulatorforRowScan(unsigned char DriverNo, unsigned char mode);
void DumpDataToDriver(unsigned char DriverNo, unsigned int SData);

void initializeHUD231(void);

const uint8_t IIC_Addr[2] = { 0x30, 0x31 };

const uint8_t NumberSegTable[11] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00 };

                                        //  T   TR   BR    B   BL    TL   M
const uint8_t SegIconTable[6][3][7] = {{{   0,   6,   7,   0,   0,   0,   0 },
                                        {  10,  16,  14,  13,  12,  11,  15 },
                                        {  19,  25,  23,  22,  21,  20,  24 }
                                       },
                                       {{  33,  39,  37,  36,  35,  34,  38 },
                                        {  41,  47,  45,  44,  43,  42,  46 },
                                        {  49,  55,  53,  52,  51,  50,  54 }
                                       },
                                       {{  59,  65,  63,  62,  61,  60,  64 },
                                        {  66,  72,  70,  69,  68,  67,  71 },
                                        {  73,  79,  77,  76,  75,  74,  78 }
                                       },
                                       {{ 131, 137, 135, 134, 133, 132, 136 },
                                        { 138, 144, 142, 141, 140, 139, 143 },
                                        { 146, 152, 150, 149, 148, 147, 151 }
                                       },
                                       {{   0,   0,   0,   0,   0,   0,   0 },
                                        { 182, 188, 186, 185, 184, 183, 187 },
                                        { 190, 196, 194, 193, 192, 191, 195 }
                                       },
                                       {{   0, 214, 215,   0,   0,   0,   0 },
                                        { 216, 222, 220, 219, 218, 217, 221 },
                                        { 223, 229, 227, 226, 225, 224, 228 }
                                       }};

typedef struct {
  uint8_t DriverNo;
  uint16_t StartBumpLocation;
  uint8_t BumpNo;
  uint8_t Level;
} IconStruct;

const IconStruct IconData[231] = {
  {0,   0,  2, 30}, {0,   2,  2, 30}, {0,  4,   2, 30}, {0,   6,  2, 30}, {0,   8,  2, 30},
  {0,  10,  2, 30}, {0,  12,  1, 30}, {0, 13,   1, 30}, {0,  14,  2, 30}, {0,  16,  2, 30},
  {0,  18,  2, 30}, {0,  20,  1, 30}, {0, 21,   1, 30}, {0,  22,  2, 30}, {0,  24,  1, 30},
  {0,  25,  1, 30}, {0,  26,  1, 30}, {0, 27,   2, 30}, {0,  29,  2, 30}, {0,  31,  2, 30},
  {0,  33,  1, 30}, {0,  34,  1, 30}, {0, 35,   2, 30}, {0,  37,  1, 30}, {0,  38,  1, 30},
  {0,  39,  1, 30}, {0,  40,  2, 30}, {0, 42,   2, 30}, {0,  44,  2, 30}, {0,  46,  2, 30},
  {0,  48,  2, 30}, {0,  50,  2, 30}, {0, 52,  16, 30}, {0,  68,  3, 30}, {0,  71,  3, 30},
  {0,  74,  3, 30}, {0,  77,  3, 30}, {0, 80,   3, 30}, {0,  83,  3, 30}, {0,  86,  3, 30},
  {0,  89,  1, 30}, {0,  90,  3, 30}, {0, 93,   3, 30}, {0,  96,  3, 30}, {0,  99,  3, 30},
  {0, 102,  3, 30}, {0, 105,  3, 30}, {0, 108,  3, 30}, {0, 111,  1, 30}, {0, 112,  3, 30},
  {0, 115,  3, 30}, {0, 118,  3, 30}, {0, 121,  3, 30}, {0, 124,  3, 30}, {0, 127,  3, 30},
  {0, 130,  3, 30}, {0, 133,  4, 30}, {0, 137,  6, 30}, {0, 143,  5, 30}, {0, 148,  2, 30},
  {0, 150,  1, 30}, {0, 151,  1, 30}, {0, 152,  2, 30}, {0, 154,  1, 30}, {0, 155,  1, 30},
  {0, 156,  1, 30}, {0, 157,  2, 30}, {0, 159,  1, 30}, {0, 160,  1, 30}, {0, 161,  2, 30},
  {0, 163,  1, 30}, {0, 164,  1, 30}, {0, 165,  1, 30}, {0, 166,  2, 30}, {0, 168,  1, 30},
  {0, 169,  1, 30}, {0, 170,  2, 30}, {0, 172,  1, 30}, {0, 173,  1, 30}, {0, 174,  1, 30},
  {0, 175,  3, 30}, {0, 178,  7, 30}, {0, 185,  1,  3}, {0, 186,  1,  3}, {0, 187,  1,  3},
  {0, 188,  1,  3}, {0, 189,  1,  3}, {0, 190,  1,  3}, {0, 191,  1,  3}, {0, 192,  1, 30},
  {0, 193,  2, 30}, {0, 195,  2, 30}, {0, 197,  1, 30}, {0, 198,  1, 30}, {0, 199,  2, 30},
  {0, 201,  1, 30}, {0, 202,  1, 30}, {0, 203,  3, 30}, {0, 206,  1, 30}, {0, 207,  1, 30},
  {0, 208,  1, 30}, {0, 209,  1, 30}, {0, 210,  3, 30}, {0, 213,  5, 30}, {0, 218,  4, 30},
  {0, 222,  1,  5}, {0, 223,  1, 12}, {0, 224,  6, 30}, {0, 230,  2, 30}, {0, 232,  5, 30},
  {0, 237,  4, 30}, {0, 241,  1,  5}, {0, 242,  1, 12}, {0, 243,  5, 30}, {0, 248,  2, 30},
  {0, 250,  5, 30}, {0, 255,  3, 30}, {0, 258,  2, 30}, {0, 260,  3, 30}, {0, 263,  1, 15},
  {0, 264,  1, 30}, {0, 265,  1, 15}, {0, 266,  1, 10}, {0, 267,  4, 30}, {0, 271,  1, 30},
  {0, 272,  2, 30}, {0, 274,  5, 30}, {0, 279,  4, 30}, {0, 283,  1,  5}, {0, 284,  7, 20},
  {0, 291,  4, 31}, {0, 295,  1, 15}, {0, 296,  1, 15}, {0, 297,  1, 15}, {0, 298,  1, 15},
  {0, 299,  1, 15}, {0, 300,  1, 15}, {0, 301,  1, 15}, {0, 302,  1, 15}, {0, 303,  1, 15},
  {0, 304,  1, 15}, {0, 305,  1, 15}, {0, 306,  1, 15}, {0, 307,  1, 15}, {0, 308,  1, 15},
  {0, 309,  1,  5}, {0, 310,  1, 15}, {0, 311,  1, 15}, {0, 312,  1, 15}, {0, 313,  1, 15},
  {0, 314,  1, 15}, {0, 315,  1, 15}, {0, 316,  1, 15}, {0, 317,  2, 15}, {0, 319,  2, 15},
  {0, 321,  7, 20}, {0, 328,  1,  5}, {0, 329,  4, 30}, {0, 333,  5, 30}, {0, 338,  2, 30},
  {0, 340,  1, 30}, {0, 341,  4, 30}, {0, 345,  1, 10}, {0, 346,  1, 12}, {0, 347,  1, 30},
  {0, 348,  1, 15}, {0, 349,  3, 30}, {0, 352,  2, 30}, {0, 354,  3, 30}, {0, 357,  5, 30},
  {0, 362,  2, 30}, {0, 364,  5, 30}, {0, 369,  1, 12}, {0, 370,  1,  5}, {0, 371,  4, 30},
  {0, 375,  5, 30}, {0, 380,  2, 30}, {1,   0,  6, 30}, {1,   6,  1, 12}, {1,   7,  4, 30},
  {1,  11,  2, 30}, {1,  13,  5, 30}, {1,  18,  1, 15}, {1,  19,  1, 15}, {1,  20,  1, 15},
  {1,  21,  1, 15}, {1,  22,  1, 15}, {1,  23,  1, 15}, {1,  24,  1, 15}, {1,  25,  2, 30},
  {1,  27,  1, 15}, {1,  28,  1, 15}, {1,  29,  1, 15}, {1,  30,  1, 15}, {1,  31,  1, 15},
  {1,  32,  1, 15}, {1,  33,  1, 15}, {1,  34, 28, 30}, {1,  62,  1, 30}, {1,  63,  1, 30},
  {1,  64,  1, 30}, {1,  65,  1, 30}, {1,  66,  3, 30}, {1,  69,  1, 30}, {1,  70,  1, 30},
  {1,  71,  2, 30}, {1,  73,  1, 30}, {1,  74,  1, 30}, {1,  75,  2, 30}, {1,  77,  2, 30},
  {1,  79,  1, 30}, {1,  80,  6, 30}, {1,  86,  5, 30}, {1,  91,  2, 30}, {1,  93, 17, 30},
  {1, 110, 16, 30}, {1, 126, 18, 30}, {1, 144, 14, 30}, {1, 158, 14, 30}, {1, 172, 17, 30},
  {1, 189, 17, 30}, {1, 206, 16, 30}, {1, 222, 16, 30}, {1, 238, 18, 30}, {1, 256, 14, 30},
  {1, 270, 14, 30}, {1, 284, 17, 30}, {1, 301, 17, 30}, {1, 318, 16, 30}, {1, 334, 16, 30},
  {1, 350, 33, 30}
};

uint16_t IconRamMap[2][128];
uint8_t SendDataBuffer[1024]; //1024
uint8_t ReceiveData[1024]; //1024

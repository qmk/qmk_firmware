/*
  This is an example of how to write a library that allows user to pass in an I2C port

  Nathan Seidle
  SparkFun Electronics

  License: Public domain
*/

#include "hud.h"

//Initialize the I2C port
bool begin(TwoWire & wirePort) {
  _i2cPort = & wirePort; //Grab which port the user wants us to use

  _i2cPort - > begin();

  initializeHUD231();
}

void AdjustIconLevel(uint16_t IconNo, uint16_t IconLevel) {
  uint16_t Temp;
  uint16_t Temp_I;
  uint8_t StartBytePos;
  uint8_t StartRGBPos;
  uint8_t EndBytePos;
  uint8_t EndRGBPos;
  uint8_t BumpNoTemp;
  uint8_t Counter;
  //        uint8_t   Result;

  if (IconLevel > 31) return; //If the IconLevel parameter is greater than 31, skip this function

  BumpNoTemp = IconData[IconNo].BumpNo;
  Temp = IconData[IconNo].StartBumpLocation; //Bump Location counts from 0

  StartBytePos = Temp / 3;
  StartRGBPos = Temp % 3; //A remainder of 0 means that the beginning Bump position is R, 1 means G, and 2 means B

  //==================================================================================================================================================================
  // Processing the first data
  // Maybe it's only this one, maybe there's more
  //==================================================================================================================================================================
  switch (StartRGBPos) {
  case 0: //Location in R
    if (BumpNoTemp == 1) {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = ChangeRedValue(IconRamMap[IconData[IconNo].DriverNo][StartBytePos], IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Only 1 RGB data, go directly to the Data Send
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8;
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], 2, SendDataBuffer);
      return;
    } else if (BumpNoTemp == 2) {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = ChangeRG_Value(IconRamMap[IconData[IconNo].DriverNo][StartBytePos], IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Only 1 RGB data, go directly to the Data Send
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8;
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], 2, SendDataBuffer);
      return;
    } else if (BumpNoTemp == 3) {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = SetRGB_Value(IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Only 1 RGB data, go directly to the Data Send
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8;
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], 2, SendDataBuffer);
      return;
    } else if (BumpNoTemp > 3) //Said that Bump is greater than 3 (more than 1 RGB16bit data)
    {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = SetRGB_Value(IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Store the first SEG data in Buffer
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8; //Store the first data in Buffer 0 & 1
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      BumpNoTemp = BumpNoTemp - 3;
    }
    break;
  case 1: //Location in G
    if (BumpNoTemp == 1) {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = ChangeGreenValue(IconRamMap[IconData[IconNo].DriverNo][StartBytePos], IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Only 1 RGB data, go directly to the Data Send
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8;
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], 2, SendDataBuffer);
      return;

    } else if (BumpNoTemp == 2) {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = ChangeGB_Value(IconRamMap[IconData[IconNo].DriverNo][StartBytePos], IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Only 1 RGB data, go directly to the Data Send
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8;
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], 2, SendDataBuffer);
      return;
    } else if (BumpNoTemp > 2) //Said that Bump is greater than 3 (more than 1 RGB16bit data)
    {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = ChangeGB_Value(IconRamMap[IconData[IconNo].DriverNo][StartBytePos], IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Store the first SEG data in Buffer
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8; //Store the first data in Buffer 0 & 1
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      BumpNoTemp = BumpNoTemp - 2;
    }
    break;

  case 2: //Location in B
    if (BumpNoTemp == 1) {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = ChangeBlueValue(IconRamMap[IconData[IconNo].DriverNo][StartBytePos], IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Only 1 RGB data, go directly to the Data Send
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8;
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], 2, SendDataBuffer);
      return;
    } else //Said that Bump is greater than 3 (more than 1 RGB16bit data)
    {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos] = ChangeBlueValue(IconRamMap[IconData[IconNo].DriverNo][StartBytePos], IconLevel);
      //Set the position setting to write
      SendDataBuffer[0] = 0x0A;
      SendDataBuffer[1] = StartBytePos >> 4; //X Start
      SendDataBuffer[2] = StartBytePos & 0x0F;
      SendDataBuffer[3] = 0x07; //X End
      SendDataBuffer[4] = 0x0F;
      SendDataBuffer[5] = 0; //Y Start
      SendDataBuffer[6] = 0;
      SendDataBuffer[7] = 0; //Y End
      SendDataBuffer[8] = 0;
      IIC_Write_Command1(IIC_Addr[IconData[IconNo].DriverNo], 9, SendDataBuffer);
      //Store the first SEG data in Buffer
      SendDataBuffer[0] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF00) >> 8; //Store the first data in Buffer 0 & 1
      SendDataBuffer[1] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos] & 0xFF;
      BumpNoTemp = BumpNoTemp - 1;
    }
    break;
  }
  //==================================================================================================================================================================
  //Processing later information
  //==================================================================================================================================================================
  EndBytePos = BumpNoTemp / 3;
  EndRGBPos = BumpNoTemp % 3;
  Counter = 1; //Previous [0], [1] store the data of the first SEG
  if (EndBytePos >= 1) //Process complete
  {
    //So far there are several complete RGB (16bit) data
    for (Temp_I = 1; Temp_I <= EndBytePos; Temp_I++) {
      IconRamMap[IconData[IconNo].DriverNo][StartBytePos + Temp_I] = SetRGB_Value(IconLevel);
      Counter = Counter + 1;
      SendDataBuffer[Counter] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos + Temp_I] & 0xFF00) >> 8; //Save High byte data in the following Buffer
      Counter = Counter + 1;
      SendDataBuffer[Counter] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos + Temp_I] & 0xFF; //Save Low byte data in the following Buffer
    }
    if (EndRGBPos == 0) {
      //If there is no remainder, there is no need to process the remaining R, G, B bits. After exiting the entire batch of data, exit.
      IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], Counter + 1, SendDataBuffer);
      return;
    }
  }

  //=================================================================================================================================================================
  //Check the remaining number of Bits
  switch (EndRGBPos) {
  case 1: //Location in R
    IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1] = ChangeRedValue(IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1], IconLevel);
    Counter = Counter + 1;
    //With this last data send out
    SendDataBuffer[Counter] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1] & 0xFF00) >> 8;
    Counter = Counter + 1;
    SendDataBuffer[Counter] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1] & 0xFF;
    IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], Counter + 1, SendDataBuffer);
    break;
  case 2: //Location in G
    IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1] = ChangeRG_Value(IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1], IconLevel);
    Counter = Counter + 1;
    //Together with this last data send out
    SendDataBuffer[Counter] = (IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1] & 0xFF00) >> 8;
    Counter = Counter + 1;
    SendDataBuffer[Counter] = IconRamMap[IconData[IconNo].DriverNo][StartBytePos + EndBytePos + 1] & 0xFF;
    IIC_Write_Data1(IIC_Addr[IconData[IconNo].DriverNo], Counter + 1, SendDataBuffer);
    break;
  }

}

uint16_t ChangeRedValue(uint16_t OriginalValue, uint16_t R_Value) {
  uint16_t Temp;

  if (R_Value > 31) return 0; //If R value is greater than 31, return 0

  Temp = OriginalValue & 0x7FF; //Clear R (high 5 bits) to 0
  Temp = Temp | (R_Value << 11); //Set R new value back
  return Temp;
}

uint16_t ChangeGreenValue(uint16_t OriginalValue, uint16_t G_Value) {
  uint16_t Temp;

  if (G_Value > 31) return 0; //If the G value is greater than 31, return 0

  Temp = OriginalValue & 0xF81F; //Clear the G value (6 bits) to 0
  Temp = Temp | (G_Value << 6); //Set G high 5bit new value back

  if (G_Value > 0x0f)
    Temp = Temp | 0x20; //Set bit0 of G to 1
  else
    Temp = Temp & 0xFFDF; //Set bit0 of G to 0

  return Temp;
}

uint16_t ChangeBlueValue(uint16_t OriginalValue, uint16_t B_Value) {
  uint16_t Temp;

  if (B_Value > 31) return 0; //If the B value is greater than 31, then return 0
  Temp = OriginalValue & 0xFFE0; //Clear the B value (5 bits) to 0
  Temp = Temp | B_Value; //Set the new value of B 5bit back
  return Temp;
}

uint16_t ChangeRG_Value(uint16_t OriginalValue, uint16_t RG_Value) {
  uint16_t Temp;

  if (RG_Value > 31) return 0; //If the value is greater than 31, return 0
  Temp = OriginalValue & 0x1F; //Clear the RG value (11 bits) to 0
  Temp = Temp | (RG_Value << 11) | (RG_Value << 6); //Set R 5bit, G 6bit new value back
  if (RG_Value > 0x0f)
    Temp = Temp | 0x20; //Set bit0 of G to 1
  else
    Temp = Temp & 0xFFDF; //Set bit0 of G to 0

  return Temp;
}

uint16_t ChangeGB_Value(uint16_t OriginalValue, uint16_t GB_Value) {
  uint16_t Temp;

  if (GB_Value > 31) return 0; //If the value is greater than 31, return 0
  Temp = OriginalValue & 0xF800; //Clear the GB value (11 bits) to 0
  Temp = Temp | (GB_Value << 6) | GB_Value; //Set G 6bit, B 5bit new value back
  if (GB_Value > 0x0f)
    Temp = Temp | 0x20; //Set bit0 of G to 1
  else
    Temp = Temp & 0xFFDF; //Set bit0 of G to 0

  return Temp;
}

uint16_t SetRGB_Value(uint16_t RGB_Value) {
  uint16_t Temp;

  if (RGB_Value > 31) return 0; //If the value is greater than 31, return 0
  Temp = (RGB_Value << 11) | (RGB_Value << 6) | RGB_Value;

  if (RGB_Value > 0x0f)
    Temp = Temp | 0x20; //Set bit0 of G to 1
  else
    Temp = Temp & 0xFFDF; //Set bit0 of G to 0

  return Temp;
}

void NumericalTo4BCD(uint16_t S_Number, uint8_t * BCD_Ptr) {
  uint8_t i;
  uint16_t Quotient;
  uint16_t QuotienNav;

  Quotient = S_Number;
  for (i = 0; i <= 3; i++) {
    QuotienNav = Quotient / 10;
    BCD_Ptr[i] = Quotient % 10;
    Quotient = QuotienNav;
  }
}

//=======================================================================================================
//The following for HUD231 standard products
//=======================================================================================================
void AdjustIconAction(uint16_t IconNo, bool Action) {
  if (Action) {
    AdjustIconLevel(IconNo, IconData[IconNo].Level);
  } else {
    AdjustIconLevel(IconNo, 0x00);
  }
}

#define D01(Action) AdjustIconAction(0,  Action)
#define D02(Action) AdjustIconAction(2,  Action)
#define D03(Action) AdjustIconAction(4,  Action)
#define D04(Action) AdjustIconAction(9,  Action)
#define D05(Action) AdjustIconAction(18, Action)
#define D06(Action) AdjustIconAction(26, Action)
#define D07(Action) AdjustIconAction(29, Action)
#define D08(Action) AdjustIconAction(31, Action)

#define CC1(Action) AdjustIconAction(1,  Action)
#define CC2(Action) AdjustIconAction(3,  Action)
#define CC3(Action) AdjustIconAction(5,  Action)
#define CC4(Action) AdjustIconAction(8,  Action)
#define CC5(Action) AdjustIconAction(17, Action)
#define CC6(Action) AdjustIconAction(27, Action)
#define CC7(Action) AdjustIconAction(28, Action)
#define CC8(Action) AdjustIconAction(30, Action)

//0-9 00-full off 1-8 => specify which CCx goes off 9-all bright 10-17=> specifies which CCx is on (inverse with 1-8)
void compassCircle(uint8_t Select) {
  switch (Select) {
    case 0:  CC1(0); CC2(0); CC3(0); CC4(0); CC5(0); CC6(0); CC7(0); CC8(0); break;
    case 1:  CC1(1); CC2(0); CC3(0); CC4(0); CC5(0); CC6(0); CC7(0); CC8(0); break;
    case 2:  CC1(0); CC2(1); CC3(0); CC4(0); CC5(0); CC6(0); CC7(0); CC8(0); break;
    case 3:  CC1(0); CC2(0); CC3(1); CC4(0); CC5(0); CC6(0); CC7(0); CC8(0); break;
    case 4:  CC1(0); CC2(0); CC3(0); CC4(1); CC5(0); CC6(0); CC7(0); CC8(0); break;
    case 5:  CC1(0); CC2(0); CC3(0); CC4(0); CC5(1); CC6(0); CC7(0); CC8(0); break;
    case 6:  CC1(0); CC2(0); CC3(0); CC4(0); CC5(0); CC6(1); CC7(0); CC8(0); break;
    case 7:  CC1(0); CC2(0); CC3(0); CC4(0); CC5(0); CC6(0); CC7(1); CC8(0); break;
    case 8:  CC1(0); CC2(0); CC3(0); CC4(0); CC5(0); CC6(0); CC7(0); CC8(1); break;
    case 9:  CC1(1); CC2(1); CC3(1); CC4(1); CC5(1); CC6(1); CC7(1); CC8(1); break;
    case 10: CC1(0); CC2(1); CC3(1); CC4(1); CC5(1); CC6(1); CC7(1); CC8(1); break;
    case 11: CC1(1); CC2(0); CC3(1); CC4(1); CC5(1); CC6(1); CC7(1); CC8(1); break;
    case 12: CC1(1); CC2(1); CC3(0); CC4(1); CC5(1); CC6(1); CC7(1); CC8(1); break;
    case 13: CC1(1); CC2(1); CC3(1); CC4(0); CC5(1); CC6(1); CC7(1); CC8(1); break;
    case 14: CC1(1); CC2(1); CC3(1); CC4(1); CC5(0); CC6(1); CC7(1); CC8(1); break;
    case 15: CC1(1); CC2(1); CC3(1); CC4(1); CC5(1); CC6(0); CC7(1); CC8(1); break;
    case 16: CC1(1); CC2(1); CC3(1); CC4(1); CC5(1); CC6(1); CC7(0); CC8(1); break;
    case 17: CC1(1); CC2(1); CC3(1); CC4(1); CC5(1); CC6(1); CC7(1); CC8(0); break;
  }
}

void D0x(uint8_t Action) {
  if (Action) {
    D01(1); D02(1); D03(1); D04(1); D05(1); D06(1); D07(1); D08(1);
  } else {
    D01(0); D02(0); D03(0); D04(0); D05(0); D06(0); D07(0); D08(0);
  }
}

//0-9 00-full off 1-8 => specify which one is off D0x 9-all bright 10-17=> specify which one D0x is on (inverse with 1-8)
void compassArrows(uint8_t Select) {
  switch (Select) {
    case 0:  D01(0); D02(0); D03(0); D04(0); D05(0); D06(0); D07(0); D08(0); break;
    case 1:  D01(1); D02(0); D03(0); D04(0); D05(0); D06(0); D07(0); D08(0); break;
    case 2:  D01(0); D02(1); D03(0); D04(0); D05(0); D06(0); D07(0); D08(0); break;
    case 3:  D01(0); D02(0); D03(1); D04(0); D05(0); D06(0); D07(0); D08(0); break;
    case 4:  D01(0); D02(0); D03(0); D04(1); D05(0); D06(0); D07(0); D08(0); break;
    case 5:  D01(0); D02(0); D03(0); D04(0); D05(1); D06(0); D07(0); D08(0); break;
    case 6:  D01(0); D02(0); D03(0); D04(0); D05(0); D06(1); D07(0); D08(0); break;
    case 7:  D01(0); D02(0); D03(0); D04(0); D05(0); D06(0); D07(1); D08(0); break;
    case 8:  D01(0); D02(0); D03(0); D04(0); D05(0); D06(0); D07(0); D08(1); break;
    case 9:  D01(1); D02(1); D03(1); D04(1); D05(1); D06(1); D07(1); D08(1); break;
    case 10: D01(0); D02(1); D03(1); D04(1); D05(1); D06(1); D07(1); D08(1); break;
    case 11: D01(1); D02(0); D03(1); D04(1); D05(1); D06(1); D07(1); D08(1); break;
    case 12: D01(1); D02(1); D03(0); D04(1); D05(1); D06(1); D07(1); D08(1); break;
    case 13: D01(1); D02(1); D03(1); D04(0); D05(1); D06(1); D07(1); D08(1); break;
    case 14: D01(1); D02(1); D03(1); D04(1); D05(0); D06(1); D07(1); D08(1); break;
    case 15: D01(1); D02(1); D03(1); D04(1); D05(1); D06(0); D07(1); D08(1); break;
    case 16: D01(1); D02(1); D03(1); D04(1); D05(1); D06(1); D07(0); D08(1); break;
    case 17: D01(1); D02(1); D03(1); D04(1); D05(1); D06(1); D07(1); D08(0); break;
  }
}

#define radarDistanceUnits(Action) AdjustIconAction(80, Action)

#define flag(Action) AdjustIconAction(32, Action)

#define C01(Action) AdjustIconAction(40,  Action)
#define C02(Action) AdjustIconAction(48,  Action)
#define H01(Action) AdjustIconAction(58,  Action)
#define K01(Action) AdjustIconAction(56,  Action)
#define M01(Action) AdjustIconAction(57,  Action)
#define C03(Action) AdjustIconAction(145, Action)
#define K02(Action) AdjustIconAction(153, Action)
#define M03(Action) AdjustIconAction(154, Action)
#define P01(Action) AdjustIconAction(211, Action)
#define P02(Action) AdjustIconAction(212, Action)
#define P03(Action) AdjustIconAction(213, Action)
#define T01(Action) AdjustIconAction(189, Action)
#define T02(Action) AdjustIconAction(197, Action)

void tirePressureAlert(uint8_t Action) {

  switch (Action) {
  case 0: // Blank
    T01(0); // "tire"
    T02(0); // "TPMS"
    break;
  case 1: // TPMS
    T01(0); // "tire"
    T02(1); // "TPMS"
    break;
  case 2: // Tire
    T01(1); // "tire"
    T02(0); // "TPMS"
    break;
  case 3: // Both
    T01(1); // "tire"
    T02(1); // "TPMS"
    break;
  }

}

#define speedometerUnits(Action) AdjustIconAction(230, Action)

void destinationDistanceUnits(uint8_t iconUnits) {

  switch (iconUnits) {

  case 0: // Blank
    H01(0); // hours
    K01(0); // kilo
    M01(0); // meters
    break;
  case 1: // hours
    H01(1); // hours
    K01(0); // kilo
    M01(0); // meters
    break;
  case 2: // meters
    H01(0); // hours
    K01(0); // kilo
    M01(1); // meters
    break;
  case 3: // kilometers
    H01(0); // hours
    K01(1); // kilo
    M01(1); // meters
    break;
  }

}

void turnDistanceUnits(uint8_t iconUnits) {

  switch (iconUnits) {

  case 0: // Blank
    K02(0); // kilo
    M03(0); // meters
    break;
  case 1: // meters
    K02(0); // kilo
    M03(1); // meters
    break;
  case 2: // kilometers
    K02(1); // kilo
    M03(1); // meters
    break;
  }

}

void leftTunnel(uint8_t Action) {
  if (Action) {
    AdjustIconLevel(91, IconData[91].Level);
    AdjustIconLevel(92, IconData[92].Level);
    AdjustIconLevel(93, IconData[93].Level);
    AdjustIconLevel(94, IconData[94].Level);
    AdjustIconLevel(95, IconData[95].Level);
    AdjustIconLevel(96, IconData[96].Level);
    AdjustIconLevel(97, IconData[97].Level);
    AdjustIconLevel(98, IconData[98].Level);
    AdjustIconLevel(99, IconData[99].Level);
  } else {
    AdjustIconLevel(91, 0x00);
    AdjustIconLevel(92, 0x00);
    AdjustIconLevel(93, 0x00);
    AdjustIconLevel(94, 0x00);
    AdjustIconLevel(95, 0x00);
    AdjustIconLevel(96, 0x00);
    AdjustIconLevel(97, 0x00);
    AdjustIconLevel(98, 0x00);
    AdjustIconLevel(99, 0x00);
  }
}

void middleTunnel(uint8_t Action) {
  if (Action) {
    AdjustIconLevel(89, IconData[89].Level);
    AdjustIconLevel(90, IconData[90].Level);
    AdjustIconLevel(100, IconData[100].Level);
    AdjustIconLevel(101, IconData[101].Level);
    AdjustIconLevel(102, IconData[102].Level);
    AdjustIconLevel(198, IconData[198].Level);
    AdjustIconLevel(199, IconData[199].Level);
    AdjustIconLevel(209, IconData[209].Level);
    AdjustIconLevel(210, IconData[210].Level);
  } else {
    AdjustIconLevel(89, 0x00);
    AdjustIconLevel(90, 0x00);
    AdjustIconLevel(100, 0x00);
    AdjustIconLevel(101, 0x00);
    AdjustIconLevel(102, 0x00);
    AdjustIconLevel(198, 0x00);
    AdjustIconLevel(199, 0x00);
    AdjustIconLevel(209, 0x00);
    AdjustIconLevel(210, 0x00);
  }
}

void rightTunnel(uint8_t Action) {
  if (Action) {
    AdjustIconLevel(200, IconData[200].Level);
    AdjustIconLevel(201, IconData[201].Level);
    AdjustIconLevel(202, IconData[202].Level);
    AdjustIconLevel(203, IconData[203].Level);
    AdjustIconLevel(204, IconData[204].Level);
    AdjustIconLevel(205, IconData[205].Level);
    AdjustIconLevel(206, IconData[206].Level);
    AdjustIconLevel(207, IconData[207].Level);
    AdjustIconLevel(208, IconData[208].Level);
  } else {
    AdjustIconLevel(200, 0x00);
    AdjustIconLevel(201, 0x00);
    AdjustIconLevel(202, 0x00);
    AdjustIconLevel(203, 0x00);
    AdjustIconLevel(204, 0x00);
    AdjustIconLevel(205, 0x00);
    AdjustIconLevel(206, 0x00);
    AdjustIconLevel(207, 0x00);
    AdjustIconLevel(208, 0x00);
  }
}

void leftRoad(uint8_t Action) {
  if (Action) {
    AdjustIconLevel(91, IconData[91].Level);
    AdjustIconLevel(94, IconData[94].Level);
    AdjustIconLevel(95, IconData[95].Level);
    AdjustIconLevel(99, IconData[99].Level);
  } else {
    AdjustIconLevel(91, 0x00);
    AdjustIconLevel(94, 0x00);
    AdjustIconLevel(95, 0x00);
    AdjustIconLevel(99, 0x00);
  }
}

void middleRoad(uint8_t Action) {
  if (Action) {
    AdjustIconLevel(90, IconData[90].Level);
    AdjustIconLevel(100, IconData[100].Level);
    AdjustIconLevel(199, IconData[199].Level);
    AdjustIconLevel(209, IconData[209].Level);
  } else {
    AdjustIconLevel(90, 0x00);
    AdjustIconLevel(100, 0x00);
    AdjustIconLevel(199, 0x00);
    AdjustIconLevel(209, 0x00);
  }
}

void rightRoad(uint8_t Action) {
  if (Action) {
    AdjustIconLevel(200, IconData[200].Level);
    AdjustIconLevel(204, IconData[204].Level);
    AdjustIconLevel(205, IconData[205].Level);
    AdjustIconLevel(208, IconData[208].Level);
  } else {
    AdjustIconLevel(200, 0x00);
    AdjustIconLevel(204, 0x00);
    AdjustIconLevel(205, 0x00);
    AdjustIconLevel(208, 0x00);
  }
}

void nav_Group(uint8_t Action) {
  uint8_t i;

  if (Action) {
    for (i = 103; i <= 130; i++) {
      AdjustIconLevel(i, IconData[i].Level);
    }
    for (i = 155; i <= 181; i++) {
      AdjustIconLevel(i, IconData[i].Level);
    }
  } else {
    for (i = 103; i <= 130; i++) {
      AdjustIconLevel(i, 0x00);
    }
    for (i = 155; i <= 181; i++) {
      AdjustIconLevel(i, 0x00);
    }
  }
}

void nav_KeepLeft(uint8_t Action) {

  if (Action) {
    AdjustIconLevel(107, IconData[107].Level);
    AdjustIconLevel(108, IconData[108].Level);
    AdjustIconLevel(109, IconData[109].Level);
    AdjustIconLevel(106, IconData[106].Level);
    AdjustIconLevel(111, IconData[111].Level);
    AdjustIconLevel(112, IconData[112].Level);
    AdjustIconLevel(105, IconData[105].Level);
    AdjustIconLevel(128, IconData[128].Level);
    AdjustIconLevel(129, IconData[129].Level);
    AdjustIconLevel(155, IconData[155].Level);
    AdjustIconLevel(130, IconData[130].Level);
  } else {
    AdjustIconLevel(107, 0x00);
    AdjustIconLevel(108, 0x00);
    AdjustIconLevel(109, 0x00);
    AdjustIconLevel(106, 0x00);
    AdjustIconLevel(111, 0x00);
    AdjustIconLevel(112, 0x00);
    AdjustIconLevel(105, 0x00);
    AdjustIconLevel(128, 0x00);
    AdjustIconLevel(129, 0x00);
    AdjustIconLevel(155, 0x00);
    AdjustIconLevel(130, 0x00);
  }
}

void nav_TurnLeft(uint8_t Action) {

  if (Action) {
    AdjustIconLevel(113, IconData[113].Level);
    AdjustIconLevel(114, IconData[114].Level);
    AdjustIconLevel(121, IconData[121].Level);
    AdjustIconLevel(111, IconData[111].Level);
    AdjustIconLevel(112, IconData[112].Level);
    AdjustIconLevel(115, IconData[116].Level);
    AdjustIconLevel(128, IconData[128].Level);
    AdjustIconLevel(129, IconData[129].Level);
    AdjustIconLevel(155, IconData[155].Level);
    AdjustIconLevel(130, IconData[130].Level);
  } else {
    AdjustIconLevel(113, 0x00);
    AdjustIconLevel(114, 0x00);
    AdjustIconLevel(121, 0x00);
    AdjustIconLevel(111, 0x00);
    AdjustIconLevel(112, 0x00);
    AdjustIconLevel(115, 0x00);
    AdjustIconLevel(128, 0x00);
    AdjustIconLevel(129, 0x00);
    AdjustIconLevel(155, 0x00);
    AdjustIconLevel(130, 0x00);
  }
}

void nav_TurnRight(uint8_t Action) {

  if (Action) {
    AdjustIconLevel(171, IconData[171].Level);
    AdjustIconLevel(170, IconData[170].Level);
    AdjustIconLevel(163, IconData[163].Level);
    AdjustIconLevel(173, IconData[173].Level);
    AdjustIconLevel(172, IconData[172].Level);
    AdjustIconLevel(169, IconData[169].Level);
    AdjustIconLevel(156, IconData[156].Level);
    AdjustIconLevel(129, IconData[129].Level);
    AdjustIconLevel(155, IconData[155].Level);
    AdjustIconLevel(130, IconData[130].Level);
  } else {
    AdjustIconLevel(171, 0x00);
    AdjustIconLevel(170, 0x00);
    AdjustIconLevel(163, 0x00);
    AdjustIconLevel(173, 0x00);
    AdjustIconLevel(172, 0x00);
    AdjustIconLevel(169, 0x00);
    AdjustIconLevel(156, 0x00);
    AdjustIconLevel(129, 0x00);
    AdjustIconLevel(155, 0x00);
    AdjustIconLevel(130, 0x00);
  }
}

void nav_HardRight(uint8_t Action) {

  if (Action) {
    AdjustIconLevel(165, IconData[165].Level);
    AdjustIconLevel(159, IconData[159].Level);
    AdjustIconLevel(163, IconData[163].Level);
    AdjustIconLevel(160, IconData[160].Level);
    AdjustIconLevel(158, IconData[158].Level);
    AdjustIconLevel(166, IconData[166].Level);
    AdjustIconLevel(156, IconData[156].Level);
    AdjustIconLevel(129, IconData[129].Level);
    AdjustIconLevel(155, IconData[155].Level);
    AdjustIconLevel(130, IconData[130].Level);
  } else {
    AdjustIconLevel(165, 0x00);
    AdjustIconLevel(159, 0x00);
    AdjustIconLevel(163, 0x00);
    AdjustIconLevel(160, 0x00);
    AdjustIconLevel(158, 0x00);
    AdjustIconLevel(166, 0x00);
    AdjustIconLevel(156, 0x00);
    AdjustIconLevel(129, 0x00);
    AdjustIconLevel(155, 0x00);
    AdjustIconLevel(130, 0x00);
  }
}

void nav_HardLeft(uint8_t Action) {

  if (Action) {
    AdjustIconLevel(119, IconData[119].Level);
    AdjustIconLevel(125, IconData[125].Level);
    AdjustIconLevel(121, IconData[121].Level);
    AdjustIconLevel(124, IconData[124].Level);
    AdjustIconLevel(126, IconData[126].Level);
    AdjustIconLevel(118, IconData[118].Level);
    AdjustIconLevel(128, IconData[128].Level);
    AdjustIconLevel(129, IconData[129].Level);
    AdjustIconLevel(155, IconData[155].Level);
    AdjustIconLevel(130, IconData[130].Level);
  } else {
    AdjustIconLevel(119, 0x00);
    AdjustIconLevel(125, 0x00);
    AdjustIconLevel(121, 0x00);
    AdjustIconLevel(124, 0x00);
    AdjustIconLevel(126, 0x00);
    AdjustIconLevel(118, 0x00);
    AdjustIconLevel(128, 0x00);
    AdjustIconLevel(129, 0x00);
    AdjustIconLevel(155, 0x00);
    AdjustIconLevel(130, 0x00);
  }
}

void nav_UTurnLeft(uint8_t Action) {

  if (Action) {
    AdjustIconLevel(162, IconData[162].Level);
    AdjustIconLevel(166, IconData[166].Level);
    AdjustIconLevel(167, IconData[167].Level);
    AdjustIconLevel(168, IconData[168].Level);
    AdjustIconLevel(170, IconData[170].Level);
    AdjustIconLevel(174, IconData[174].Level);
    AdjustIconLevel(176, IconData[176].Level);
    AdjustIconLevel(179, IconData[179].Level);
    AdjustIconLevel(180, IconData[180].Level);
    AdjustIconLevel(104, IconData[104].Level);
    AdjustIconLevel(108, IconData[108].Level);
    AdjustIconLevel(110, IconData[110].Level);
    AdjustIconLevel(114, IconData[114].Level);
    AdjustIconLevel(116, IconData[116].Level);
    AdjustIconLevel(117, IconData[117].Level);
    AdjustIconLevel(118, IconData[118].Level);
    AdjustIconLevel(122, IconData[122].Level);
    AdjustIconLevel(123, IconData[123].Level);

  } else {
    AdjustIconLevel(162, 0x00);
    AdjustIconLevel(166, 0x00);
    AdjustIconLevel(167, 0x00);
    AdjustIconLevel(168, 0x00);
    AdjustIconLevel(170, 0x00);
    AdjustIconLevel(174, 0x00);
    AdjustIconLevel(176, 0x00);
    AdjustIconLevel(179, 0x00);
    AdjustIconLevel(180, 0x00);
    AdjustIconLevel(104, 0x00);
    AdjustIconLevel(108, 0x00);
    AdjustIconLevel(110, 0x00);
    AdjustIconLevel(114, 0x00);
    AdjustIconLevel(116, 0x00);
    AdjustIconLevel(117, 0x00);
    AdjustIconLevel(118, 0x00);
    AdjustIconLevel(122, 0x00);
    AdjustIconLevel(123, 0x00);

  }
}

void nav_UTurnRight(uint8_t Action) {

  if (Action) {
    AdjustIconLevel(162, IconData[162].Level);
    AdjustIconLevel(166, IconData[166].Level);
    AdjustIconLevel(167, IconData[167].Level);
    AdjustIconLevel(168, IconData[168].Level);
    AdjustIconLevel(170, IconData[170].Level);
    AdjustIconLevel(174, IconData[174].Level);
    AdjustIconLevel(176, IconData[176].Level);
    AdjustIconLevel(179, IconData[179].Level);
    AdjustIconLevel(180, IconData[180].Level);
    AdjustIconLevel(104, IconData[104].Level);
    AdjustIconLevel(108, IconData[108].Level);
    AdjustIconLevel(110, IconData[110].Level);
    AdjustIconLevel(114, IconData[114].Level);
    AdjustIconLevel(116, IconData[116].Level);
    AdjustIconLevel(117, IconData[117].Level);
    AdjustIconLevel(118, IconData[118].Level);
    AdjustIconLevel(122, IconData[122].Level);
    AdjustIconLevel(161, IconData[161].Level);

  } else {
    AdjustIconLevel(162, 0x00);
    AdjustIconLevel(166, 0x00);
    AdjustIconLevel(167, 0x00);
    AdjustIconLevel(168, 0x00);
    AdjustIconLevel(170, 0x00);
    AdjustIconLevel(174, 0x00);
    AdjustIconLevel(176, 0x00);
    AdjustIconLevel(179, 0x00);
    AdjustIconLevel(180, 0x00);
    AdjustIconLevel(104, 0x00);
    AdjustIconLevel(108, 0x00);
    AdjustIconLevel(110, 0x00);
    AdjustIconLevel(114, 0x00);
    AdjustIconLevel(116, 0x00);
    AdjustIconLevel(117, 0x00);
    AdjustIconLevel(118, 0x00);
    AdjustIconLevel(122, 0x00);
    AdjustIconLevel(161, 0x00);

  }
}

void nav_ContinueStraight(uint8_t Action) {
  //  uint8_t i;

  if (Action) {
    AdjustIconLevel(181, IconData[181].Level);
    AdjustIconLevel(180, IconData[180].Level);
    AdjustIconLevel(103, IconData[103].Level);
    AdjustIconLevel(178, IconData[178].Level);
    AdjustIconLevel(105, IconData[105].Level);
    AdjustIconLevel(106, IconData[106].Level);
    AdjustIconLevel(173, IconData[173].Level);
    AdjustIconLevel(111, IconData[111].Level);
    AdjustIconLevel(129, IconData[129].Level);
    AdjustIconLevel(155, IconData[155].Level);
    AdjustIconLevel(130, IconData[130].Level);
  } else {
    AdjustIconLevel(181, 0x00);
    AdjustIconLevel(180, 0x00);
    AdjustIconLevel(103, 0x00);
    AdjustIconLevel(178, 0x00);
    AdjustIconLevel(105, 0x00);
    AdjustIconLevel(106, 0x00);
    AdjustIconLevel(173, 0x00);
    AdjustIconLevel(111, 0x00);
    AdjustIconLevel(129, 0x00);
    AdjustIconLevel(155, 0x00);
    AdjustIconLevel(130, 0x00);
  }
}

void nav_KeepRight(uint8_t Action) {
  //  uint8_t i;

  if (Action) {
    AdjustIconLevel(105, IconData[105].Level);
    AdjustIconLevel(177, IconData[177].Level);
    AdjustIconLevel(176, IconData[176].Level);
    AdjustIconLevel(175, IconData[175].Level);
    AdjustIconLevel(172, IconData[172].Level);
    AdjustIconLevel(173, IconData[173].Level);
    AdjustIconLevel(178, IconData[178].Level);
    AdjustIconLevel(156, IconData[156].Level);
    AdjustIconLevel(129, IconData[129].Level);
    AdjustIconLevel(155, IconData[155].Level);
    AdjustIconLevel(130, IconData[130].Level);
  } else {
    AdjustIconLevel(105, 0x00);
    AdjustIconLevel(177, 0x00);
    AdjustIconLevel(176, 0x00);
    AdjustIconLevel(175, 0x00);
    AdjustIconLevel(172, 0x00);
    AdjustIconLevel(173, 0x00);
    AdjustIconLevel(178, 0x00);
    AdjustIconLevel(156, 0x00);
    AdjustIconLevel(129, 0x00);
    AdjustIconLevel(155, 0x00);
    AdjustIconLevel(130, 0x00);
  }
}

void radarDetector(uint8_t Level) //00-08     00-全滅  01-主體  02-08 =>Level
{
  switch (Level) {
  case 0:
    AdjustIconLevel(81, 0x00); //R01
    AdjustIconLevel(82, 0x00); //R02
    AdjustIconLevel(83, 0x00); //R03
    AdjustIconLevel(84, 0x00); //R04
    AdjustIconLevel(85, 0x00); //R05
    AdjustIconLevel(86, 0x00); //R06
    AdjustIconLevel(87, 0x00); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 1:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, 0x00); //R02
    AdjustIconLevel(83, 0x00); //R03
    AdjustIconLevel(84, 0x00); //R04
    AdjustIconLevel(85, 0x00); //R05
    AdjustIconLevel(86, 0x00); //R06
    AdjustIconLevel(87, 0x00); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 2:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, IconData[82].Level); //R02
    AdjustIconLevel(83, 0x00); //R03
    AdjustIconLevel(84, 0x00); //R04
    AdjustIconLevel(85, 0x00); //R05
    AdjustIconLevel(86, 0x00); //R06
    AdjustIconLevel(87, 0x00); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 3:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, IconData[82].Level); //R02
    AdjustIconLevel(83, IconData[83].Level); //R03
    AdjustIconLevel(84, 0x00); //R04
    AdjustIconLevel(85, 0x00); //R05
    AdjustIconLevel(86, 0x00); //R06
    AdjustIconLevel(87, 0x00); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 4:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, IconData[82].Level); //R02
    AdjustIconLevel(83, IconData[83].Level); //R03
    AdjustIconLevel(84, IconData[84].Level); //R04
    AdjustIconLevel(85, 0x00); //R05
    AdjustIconLevel(86, 0x00); //R06
    AdjustIconLevel(87, 0x00); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 5:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, IconData[82].Level); //R02
    AdjustIconLevel(83, IconData[83].Level); //R03
    AdjustIconLevel(84, IconData[84].Level); //R04
    AdjustIconLevel(85, IconData[85].Level); //R05
    AdjustIconLevel(86, 0x00); //R06
    AdjustIconLevel(87, 0x00); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 6:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, IconData[82].Level); //R02
    AdjustIconLevel(83, IconData[83].Level); //R03
    AdjustIconLevel(84, IconData[84].Level); //R04
    AdjustIconLevel(85, IconData[85].Level); //R05
    AdjustIconLevel(86, IconData[86].Level); //R06
    AdjustIconLevel(87, 0x00); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 7:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, IconData[82].Level); //R02
    AdjustIconLevel(83, IconData[83].Level); //R03
    AdjustIconLevel(84, IconData[84].Level); //R04
    AdjustIconLevel(85, IconData[85].Level); //R05
    AdjustIconLevel(86, IconData[86].Level); //R06
    AdjustIconLevel(87, IconData[87].Level); //R07
    AdjustIconLevel(88, 0x00); //R08
    break;
  case 8:
    AdjustIconLevel(81, IconData[81].Level); //R01
    AdjustIconLevel(82, IconData[82].Level); //R02
    AdjustIconLevel(83, IconData[83].Level); //R03
    AdjustIconLevel(84, IconData[84].Level); //R04
    AdjustIconLevel(85, IconData[85].Level); //R05
    AdjustIconLevel(86, IconData[86].Level); //R06
    AdjustIconLevel(87, IconData[87].Level); //R07
    AdjustIconLevel(88, IconData[88].Level); //R08
    break;
  };
}

void DispNumber(const uint16_t * SegIconPtr, uint8_t DispNo) {
  uint8_t Cnt;
  uint16_t tmp;
  uint32_t DispData;

  DispData = NumberSegTable[DispNo];
  Cnt = 0;
  do {
    tmp = SegIconPtr[Cnt];
    if ((tmp != 0) && ((DispData & 1) == 1)) {
      AdjustIconLevel(tmp, IconData[tmp].Level);
    } else {
      AdjustIconLevel(tmp, 0x00);
    }
    DispData >>= 1;
    Cnt++;
  } while (Cnt <= 6);
}

void setSegmentedDisplay(uint8_t Display, uint8_t SpeedNo, bool Mode) {
  uint8_t BCDcode[4];

  if (SpeedNo > DisplayLimit[Display])
    SpeedNo = DisplayLimit[Display];

  NumericalTo4BCD(SpeedNo, BCDcode);

  if (BCDcode[2] == 0 && BCDcode[1] == 0 && Mode) {
    DispNumber(SegIconTable[Display][0], 10);
  } else {
    DispNumber(SegIconTable[Display][0], BCDcode[2]);
  }
  if (BCDcode[2] == 0 && Mode) {
    DispNumber(SegIconTable[Display][1], 10);
  } else {
    DispNumber(SegIconTable[Display][1], BCDcode[1]);
  }
  DispNumber(SegIconTable[Display][2], BCDcode[0]);

}

void setHeading(uint8_t SpeedNo) {
  uint8_t BCDcode[4];

  if (SpeedNo > S1_2_3_Limit) SpeedNo = S1_2_3_Limit;

  NumericalTo4BCD(SpeedNo, BCDcode);

  if (BCDcode[2] == 0 && BCDcode[1] == 0) {
    S01_BAR(0); //Number 1 Icon Clear
    DispNumber(S02SegIconTable, 10); //Clear
    DispNumber(S03SegIconTable, BCDcode[0]);
    return;
  }
  if (BCDcode[2] == 0) {
    S01_BAR(0); //Number 1 Icon Clear
    DispNumber(S02SegIconTable, BCDcode[1]);
    DispNumber(S03SegIconTable, BCDcode[0]);
    return;
  }

  S01_BAR(1); //Number 1 Icon Clear
  DispNumber(S02SegIconTable, BCDcode[1]);
  DispNumber(S03SegIconTable, BCDcode[0]);
}

void setDestinationDistance(uint16_t SpeedNo, uint8_t Mode) {
  uint8_t BCDcode[4];

  if (SpeedNo > S4_5_6_Limit) SpeedNo = S4_5_6_Limit;

  NumericalTo4BCD(SpeedNo, BCDcode);

  if (Mode) //1
  {
    if (BCDcode[2] == 0 && BCDcode[1] == 0) {
      DispNumber(S04SegIconTable, 10); //Clear
      DispNumber(S05SegIconTable, 10); //Clear
      DispNumber(S06SegIconTable, BCDcode[0]);
      return;
    }
    if (BCDcode[2] == 0) {
      DispNumber(S04SegIconTable, 10); //Clear
      DispNumber(S05SegIconTable, BCDcode[1]);
      DispNumber(S06SegIconTable, BCDcode[0]);
      return;
    }
  } //0
  DispNumber(S04SegIconTable, BCDcode[2]);
  DispNumber(S05SegIconTable, BCDcode[1]);
  DispNumber(S06SegIconTable, BCDcode[0]);
}

void setRadarDistance(uint16_t SpeedNo, uint8_t Mode) {
  uint8_t BCDcode[4];

  if (SpeedNo > S7_8_9_Limit) SpeedNo = S7_8_9_Limit;

  NumericalTo4BCD(SpeedNo, BCDcode);

  if (Mode) //1
  {
    if (BCDcode[2] == 0 && BCDcode[1] == 0) {
      DispNumber(S07SegIconTable, 10); //Clear
      DispNumber(S08SegIconTable, 10); //Clear
      DispNumber(S09SegIconTable, BCDcode[0]);
      return;
    }
    if (BCDcode[2] == 0) {
      DispNumber(S07SegIconTable, 10); //Clear
      DispNumber(S08SegIconTable, BCDcode[1]);
      DispNumber(S09SegIconTable, BCDcode[0]);
      return;
    }
  } //0
  DispNumber(S07SegIconTable, BCDcode[2]);
  DispNumber(S08SegIconTable, BCDcode[1]);
  DispNumber(S09SegIconTable, BCDcode[0]);
}

void setTurnDistance(uint16_t SpeedNo, uint8_t Mode) {
  uint8_t BCDcode[4];

  if (SpeedNo > S10_11_12_Limit) SpeedNo = S10_11_12_Limit;

  NumericalTo4BCD(SpeedNo, BCDcode);

  if (Mode) //1
  {
    if (BCDcode[2] == 0 && BCDcode[1] == 0) {
      DispNumber(S10SegIconTable, 10); //Clear
      DispNumber(S11SegIconTable, 10); //Clear
      DispNumber(S12SegIconTable, BCDcode[0]);
      return;
    }
    if (BCDcode[2] == 0) {
      DispNumber(S10SegIconTable, 10); //Clear
      DispNumber(S11SegIconTable, BCDcode[1]);
      DispNumber(S12SegIconTable, BCDcode[0]);
      return;
    }
  } //0
  DispNumber(S10SegIconTable, BCDcode[2]);
  DispNumber(S11SegIconTable, BCDcode[1]);
  DispNumber(S12SegIconTable, BCDcode[0]);
}

void setTirePressure(uint8_t SpeedNo, uint8_t Mode) {
  uint8_t BCDcode[4];

  if (SpeedNo > S13_14_Limit) SpeedNo = S13_14_Limit;

  NumericalTo4BCD(SpeedNo, BCDcode);

  if (Mode) //1
  {
    if (BCDcode[1] == 0) {
      DispNumber(S13SegIconTable, 10); //Clear
      DispNumber(S14SegIconTable, BCDcode[0]);
      return;
    }
  } //0
  DispNumber(S13SegIconTable, BCDcode[1]);
  DispNumber(S14SegIconTable, BCDcode[0]);
}

void setSpeedometer(uint8_t SpeedNo) {
  uint8_t BCDcode[4];

  if (SpeedNo > S15_16_17_Limit) SpeedNo = S15_16_17_Limit;

  NumericalTo4BCD(SpeedNo, BCDcode);

  if (BCDcode[2] == 0 && BCDcode[1] == 0) {
    S15_BAR(0); //Number 1 Icon Clear
    DispNumber(S16SegIconTable, 10); //Clear
    DispNumber(S17SegIconTable, BCDcode[0]);
    return;
  }
  if (BCDcode[2] == 0) {
    S15_BAR(0); //Number 1 Icon Clear
    DispNumber(S16SegIconTable, BCDcode[1]);
    DispNumber(S17SegIconTable, BCDcode[0]);
    return;
  }

  S15_BAR(1); //Number 1 Icon Clear
  DispNumber(S16SegIconTable, BCDcode[1]);
  DispNumber(S17SegIconTable, BCDcode[0]);
}

void setCallIcon(uint8_t iconStatus) {

  switch (iconStatus) {
  case 0: // Blank
    P01(0); // Call Outline
    P02(0); // Call Phone Icon
    P03(0); // Call Text
    break;
  case 1: // Outline Only
    P01(1); // Call Outline
    P02(0); // Call Phone Icon
    P03(0); // Call Text
    break;
  case 2: // Outline w/ Phone
    P01(1); // Call Outline
    P02(1); // Call Phone Icon
    P03(0); // Call Text
    break;
  case 3: // All
    P01(1); // Call Outline
    P02(1); // Call Phone Icon
    P03(1); // Call Text
    break;
  }

}

void SoftReset(unsigned char DriverNo) {
  ReceiveData[0] = 0x01; //SoftReset Command No.
  IIC_Write_Command1(IIC_Addr[DriverNo], 1, ReceiveData);
}

void SetOscControl(unsigned char DriverNo, unsigned char mode) {
  ReceiveData[0] = 0x04; //Set Osc Control Command No.
  ReceiveData[1] = mode;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void SetGraphicsRAMWritingDirection(unsigned char DriverNo, unsigned char mode) {
  ReceiveData[0] = 0x05; //Set Graphics RAM Writing Direction Command No.
  ReceiveData[1] = mode;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void SetInterface(unsigned char DriverNo, unsigned char mode) {
  ReceiveData[0] = 0x08; //Set Interface Command No.
  ReceiveData[1] = mode;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void DisplayOnOff(unsigned char DriverNo, unsigned char Val) {
  ReceiveData[0] = 0x02; //DisplayOnOff Command No.
  ReceiveData[1] = Val;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void DisplayStandbyOnOff(unsigned char DriverNo, unsigned char Val) {
  ReceiveData[0] = 0x03; //DisplayStandbyOnOff Command No.
  ReceiveData[1] = Val;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void SetDisplaySize(unsigned char DriverNo, unsigned char Xstart, unsigned char Xend, unsigned char Ystart, unsigned char Yend) {
  ReceiveData[0] = 0x07; //SetDisplaySize Command No.
  ReceiveData[1] = Xstart >> 4;
  ReceiveData[2] = Xstart & 0x0f;
  ReceiveData[3] = Xend >> 4;
  ReceiveData[4] = Xend & 0x0f;
  ReceiveData[5] = Ystart >> 4;
  ReceiveData[6] = Ystart & 0x0f;
  ReceiveData[7] = Yend >> 4;
  ReceiveData[8] = Yend & 0x0f;
  IIC_Write_Command1(IIC_Addr[DriverNo], 9, ReceiveData);
}

void SetDotCurrent(unsigned char DriverNo, unsigned char Rlevel, unsigned char Glevel, unsigned char Blevel) {
  ReceiveData[0] = 0x0e; //SetDotCurrent Level Command No.
  ReceiveData[1] = Rlevel >> 4;
  ReceiveData[2] = Rlevel & 0x0f;
  ReceiveData[3] = Glevel >> 4;
  ReceiveData[4] = Glevel & 0x0f;
  ReceiveData[5] = Blevel >> 4;
  ReceiveData[6] = Blevel & 0x0f;
  IIC_Write_Command1(IIC_Addr[DriverNo], 7, ReceiveData);
}

void SetSystemClockDivisionRatio(unsigned char DriverNo, unsigned char mode) {
  ReceiveData[0] = 0x10; //Set System Clock Division Ratio Command No.
  ReceiveData[1] = mode;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void SetPreChargeWidth(unsigned char DriverNo, unsigned char Val) {
  ReceiveData[0] = 0x1C; //SetPreChargeWidth Command No.
  ReceiveData[1] = Val;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void SetPeakPulseWidth(unsigned char DriverNo, unsigned char Rlevel, unsigned char Glevel, unsigned char Blevel) {
  ReceiveData[0] = 0x1d; //SetPeakPulseWidthl Command No.
  ReceiveData[1] = Rlevel >> 4;
  ReceiveData[2] = Rlevel & 0x0f;
  ReceiveData[3] = Glevel >> 4;
  ReceiveData[4] = Glevel & 0x0f;
  ReceiveData[5] = Blevel >> 4;
  ReceiveData[6] = Blevel & 0x0f;
  IIC_Write_Command1(IIC_Addr[DriverNo], 7, ReceiveData);
}

void SetPeakPulseDelay(unsigned char DriverNo, unsigned char Val) {
  ReceiveData[0] = 0x1e; //SetPeakPulseDelay Command No.
  ReceiveData[1] = Val;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void SetRowScanOperation(unsigned char DriverNo, unsigned char mode) {
  ReceiveData[0] = 0x1f; //SetRowScanOperation Command No.
  ReceiveData[1] = mode;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void SetInternalRegulatorforRowScan(unsigned char DriverNo, unsigned char mode) {
  ReceiveData[0] = 0x30; //SetInternalRegulatorforRowScan Command No.
  ReceiveData[1] = mode;
  IIC_Write_Command1(IIC_Addr[DriverNo], 2, ReceiveData);
}

void DumpDataToDriver(unsigned char DriverNo, unsigned int SData) {
  unsigned int Cnt, CnNav;
  unsigned char Nav, t2;
  //    unsigned char tmp;

  //Set the position setting to write       Row-0
  ReceiveData[0] = 0x0a;
  ReceiveData[1] = 0x00; //X Start
  ReceiveData[2] = 0x00;
  ReceiveData[3] = 0x07; //X End
  ReceiveData[4] = 0x0f;
  ReceiveData[5] = 0x00; //Y Start
  ReceiveData[6] = 0x00;
  ReceiveData[7] = 0x00; //Y End
  ReceiveData[8] = 0x00;
  IIC_Write_Command1(IIC_Addr[DriverNo], 9, ReceiveData);

  Nav = SData >> 8;
  t2 = SData & 0xff;

  CnNav = 0;
  for (Cnt = 0; Cnt <= 127; Cnt++) {
    ReceiveData[CnNav] = Nav;
    CnNav++;
    ReceiveData[CnNav] = t2;
    CnNav++;
  }
  IIC_Write_Data1(IIC_Addr[DriverNo], CnNav, ReceiveData);
}

//---------------------------------INITIALIZE (HUDBEGIN)-----------------------------------//

void initializeHUD231(void) {
  uint8_t i, j;

  SoftReset(0);
  SoftReset(1);

  SetOscControl(0, 3); // Internal OSC.  105hz
  SetOscControl(1, 3);

  SetGraphicsRAMWritingDirection(0, 2); //RGB,  Left->Right, Bottom->Top
  SetGraphicsRAMWritingDirection(1, 2);

  SetSystemClockDivisionRatio(0, 0x0B); // 1/128
  SetSystemClockDivisionRatio(1, 0x0B);

  SetInterface(0, 1);
  SetInterface(1, 1);

  DisplayOnOff(0, 0);
  DisplayOnOff(1, 0);

  SetDisplaySize(0, 0, 127, 0, 0);
  SetDisplaySize(1, 0, 127, 0, 0);

  SetDotCurrent(0, 220, 230, 230);
  SetDotCurrent(1, 230, 230, 230);

  SetPreChargeWidth(0, 1); //1
  SetPreChargeWidth(1, 1);

  SetPeakPulseWidth(0, 0, 0, 0); //0,0,0
  SetPeakPulseWidth(1, 0, 0, 0);

  SetPeakPulseDelay(0, 1); //1
  SetPeakPulseDelay(1, 1);

  SetRowScanOperation(0, 0x2a); //Pre-Charge + Peak Delay Timing,All Row are in GND, Mode3
  SetRowScanOperation(1, 0x2a);

  SetInternalRegulatorforRowScan(0, 0x10); //Internal scan requlator Enable, VCC_Cx0.85
  SetInternalRegulatorforRowScan(1, 0x10);

  DisplayStandbyOnOff(0, 1);
  DisplayStandbyOnOff(0, 0);
  DisplayStandbyOnOff(1, 1);
  DisplayStandbyOnOff(1, 0);

  DumpDataToDriver(0, 0x0000);
  DumpDataToDriver(1, 0x0000);

  DisplayOnOff(0, 1);
  DisplayOnOff(1, 1);

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 128; j++) {
      IconRamMap[i][j] = 0;
    }
  }
}

//---------------------------------I2C FUNCTIONS-----------------------------------//

void IIC_Write_Command1(uint8_t IIC_Addr, uint16_t DataLen, uint8_t * DataPtr) {
  uint16_t Cnt;

  _i2cPort - > beginTransmission(IIC_Addr);
  for (Cnt = 0; Cnt < DataLen; Cnt++) {
    _i2cPort - > write(DataPtr[Cnt]);
  }
  _i2cPort - > endTransmission();
}

void IIC_Write_Data1(uint8_t IIC_Addr, uint16_t DataLen, uint8_t * DataPtr) {
  uint16_t Cnt;

  _i2cPort - > beginTransmission(IIC_Addr);
  _i2cPort - > write(0x0C);

  for (Cnt = 0; Cnt < DataLen; Cnt++) {
    _i2cPort - > write(DataPtr[Cnt]);
  }
  _i2cPort - > endTransmission();
}

void IIC_Write_Data2(uint8_t IIC_Addr, uint16_t DataLen,
  const uint8_t * DataPtr) {
  uint16_t Cnt;
  uint8_t tmp;

  _i2cPort - > beginTransmission(IIC_Addr);
  _i2cPort - > write(0x0C);

  for (Cnt = 0; Cnt < DataLen; Cnt++) {
    tmp = DataPtr[Cnt];
    _i2cPort - > write(tmp);
  }
  _i2cPort - > endTransmission();
}

//---------------------------------CLEAR DISPLAY-----------------------------------//

void clearAll(void) {

  for (uint16_t i; i < 230; i++) {
    AdjustIconLevel(i, 0x00);
  }

}

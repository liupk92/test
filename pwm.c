#ifndef _DISPLAY_H
#define _DISPLAY_H



#include "gd32f10x.h"

#define     RED          0XF800	  //红色
#define     GREEN        0X07E0	  //绿色
#define     BLUE         0X001F	  //蓝色
#define     WHITE        0XFFFF	  //白色
#define     BLACK        0X0000	  //黑色
#define     YELLOW       0XFFE0	  //黄色
#define     ORANGE       0XFC08	  //橙色
#define     GRAY  	     0X8430   //灰色
#define     LGRAY        0XC618	  //浅灰色
#define     DARKGRAY     0X8410	  //深灰色
#define     PORPO        0X801F	  //紫色
#define     PINK         0XF81F	  //粉红色
#define     GRAYBLUE     0X5458   //灰蓝色
#define     LGRAYBLUE    0XA651   //浅灰蓝色
#define     DARKBLUE     0X01CF	  //深灰蓝色
#define 		LIGHTBLUE    0X7D7C	  //浅蓝色




#define	   fourGridElectricity    16.2
#define	   threeGridElectricity   15.5
#define	   twoGridElectricity     14.6
#define	   oneGridElectricity     14.4
#define	   zeroGridElectricity    14.0




void LCDInit(void);
void WaitLcdBusy(void); 
void BackLight(uint8_t Type);
void BuzzerTpye(uint8_t Type,uint8_t time);
void FColor_BColor(uint16_t FColor,uint16_t BColor);
void F_mode_color(uint8_t mode,uint16_t color);
char *IntegerToString(uint16_t Integer);

void PutString(uint16_t x,uint16_t y,uint8_t mode,char *string);
void DispFullPic(uint16_t PicID);

void DIS_SignalValue(uint8_t status);

void Display_Data_R(uint16_t P_Set,uint16_t T_Set,int16_t Timer_H,int8_t Timer_M,int8_t Timer_S,uint16_t Current_P);
void Display_Data_S(uint16_t Cursor,int16_t PressureSetValue,int16_t TimeSetValue,uint8_t Mode);
void DIS_BattElectricQuantity(float BattElectricQuantity , uint8_t RunningState,uint8_t Charging,uint8_t ChargingComplete);

void LanguageMode(uint8_t language);
void DigitalPower(uint8_t num,uint8_t Batt_State);

void SystemInformationFixed(uint32_t eeprom_RunTime);
void SystemInformationChange(float PressureSensorInside_0_ADC,double PressureSensorOutside_1_ADC,float BattElectricQuantity);
void SystemInformationRevision(void);

void Display_Shear_Image(uint16_t Add_X,uint16_t Add_Y,uint16_t Imagge_ID,uint16_t Imagge_X,uint16_t Imagge_Y,uint16_t Imagge_W,uint16_t Imagge_H,uint8_t MaskEN);
void DIS_Battflicker(void);



#endif















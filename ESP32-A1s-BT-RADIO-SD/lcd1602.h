#include "Arduino.h"
#include "Wire.h"
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;
int Li          = 16;
int Lii         = 0;
int Li2          = 8;
int Lii2         = 0;

#define LCD_IIC_CLK     21
#define LCD_IIC_DATA    22
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void initLCD()
{
      Wire1.begin(LCD_IIC_DATA, LCD_IIC_CLK); 
      lcd.init();                    
      lcd.backlight();
}

String Scroll_LCD_Left(String StrDisplay){
  String result;
  String StrProcess = "                " + StrDisplay + "                ";
  //String StrProcess = " " + StrDisplay + "        ";
  result = StrProcess.substring(Li,Lii);
  Li++;
  Lii++;
  if (Li>StrProcess.length()){
    Li=16;
    Lii=0;
  }
  return result;
}

String Scroll_LCD8_Left(String StrDisplay){
  String result;
  String StrProcess = "        " + StrDisplay + "        ";
  result = StrProcess.substring(Li2,Lii2);
  Li2++;
  Lii2++;
  if (Li2>StrProcess.length()){
    Li2=8;
    Lii2=0;
  }
  return result;
}

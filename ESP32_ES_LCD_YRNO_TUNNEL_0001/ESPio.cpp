#include <Arduino.h>
#include "Wire.h"
#include "ESPio.h"
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x20, 16, 2); 
LiquidCrystal_I2C lcd(ooolcdADR, ooolcdColumns, ooolcdRows); 



void ESPio::initLED(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void ESPio::initLCD(int IIC_DATA, int IIC_CLK)
{
      Wire.begin(IIC_DATA, IIC_CLK); 
      lcd.init();                    
      lcd.backlight();
}
void ESPio::clear()
{
     lcd.clear();
     lcd.setCursor(0, 0); 
}
void ESPio::print(String linia)
{
     ESPio::clear();
     lcd.print(String(linia).substring(0,16));
     lcd.setCursor(0, 1); 
     lcd.print(String(linia).substring(16,32));
}
void ESPio::println(String linia, int col)
{
     lcd.setCursor(0, col); 
     lcd.print("                ");
     lcd.setCursor(0, col); 
     lcd.print(linia);
}
void ESPio::drukLCD(String linia)
{
  //Serial.print("!drukLCD=");Serial.println(linia);
     ESPio::clear(); 
     lcd.print(String(linia).substring(0,16));
     lcd.setCursor(0, 1); 
     lcd.print(String(linia).substring(16,32));
}

void ESPio::ppp(IPAddress linia)
{  
      lcd.clear();
     lcd.setCursor(0, 0); 
     lcd.print(linia);
}
void ESPio::ledled()
{
  if(_pin) digitalWrite(_pin, !digitalRead(_pin));
}
/*
void ESPio::dot()
{
  digitalWrite(_pin, HIGH);
  delay(50);
  digitalWrite(_pin, LOW);
  delay(50);  
}

void ESPio::dash()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);
}
*/
/*
bool ESPio::inArray(int pin, byte piny[])
{
  bool ret=false;
  int i=0;
  while (piny[i]) {
    if (piny[i]==pin) ret=true;
    i++;
   }
  return ret;
}
*/
String ESPio::array2json(byte arr[],int len)
{
    String json_str = "[";
    for (int i=0; i<len; i++){
      json_str += String(arr[i]);
      if (i<len-1) json_str += ","; else json_str += "]";
    }
  return json_str;
}

String ESPio::splitValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String ESPio::payload2LCD(String payload){
  int j=0;
  minuteStamp = (ESPio::splitValue(payload,'\n',0)).toInt();
  Serial.print("minuteStamp=");  Serial.println(minuteStamp);
  for (int i=1; i<8; i++){
    String found = ESPio::splitValue(payload,'\n',i);
    if (found !=""){
        linieLCD[j++]=found;
    }
    //Serial.print(i);  Serial.print("=");  Serial.println(found);
  }
}


String ESPio::padZero(int nr){
  if (nr>9) return String(nr);
  else return "0"+String(nr);
}

String ESPio::getClock(){         
    unsigned long minutFromMillis = millis()/(60*1000);
    minutFromMillis +=minuteStamp;        
    int hh  = floor(minutFromMillis/60);         
    int mm  = minutFromMillis-(hh*60);        
    return ESPio::padZero(hh)+":"+ESPio::padZero(mm);
}


/*
void ESPio::pogoda2LCD(){
      loopa = (loopa+1) % 15;
      //Serial.println(jsonBuffer);
      String linia1 = getValue(jsonBuffer, loopa);
      Serial.print("#");Serial.print(loopa);Serial.println(linia1);
      if (loopa==0)  linia1 .= linia1+" @";
      if (loopa==1)  linia1 = linia1+" "+znakS+"C";
      if (loopa==2)  linia1 += " hPa";
      if (loopa==3)  linia1 += " m/s";
      if (loopa==4)  linia1 += " %";
      if (loopa==5)  linia1 = "# 1h "+linia1 + "mm";
      if (loopa==6)  linia1 = "# 6h "+linia1 + "mm";
      if (loopa==7)  linia1 = "#12h "+linia1 + "mm";
      if (loopa==8)  linia1 = "# 1h "+linia1;
      if (loopa==9)  linia1 = "# 6h "+linia1;
      if (loopa==10) linia1 = "#12h "+linia1;
      if (loopa==11) linia1 = radioBuffer;
      if (loopa<12){
        ESPio::clear(); 
        ESPio::println(linia1,1);
        //ESPio::println(linia2,0);
        //linia2=linia1;
      }      
      lastSecundDelay = millis();
}
*/

/*
void pisz(const char *linia1, const char *linia2, int lineNR){
  Serial.println(linia1);
  Serial.println(linia2);
}
*/

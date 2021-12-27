#ifndef ESPio_h
#define ESPio_h

/****CONFIG*******************************/
#define ooolcdColumns  16
#define ooolcdRows      2
#define ooolcdADR    0x20
/*****************************************/
#define ARRAYSIZE 7

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

struct stacjeSTRUCT  {
  int  const  ampli;  
  char const *info;
  char const *stream;
};


class ESPio
{
  public:
    void initLED(int pin);
    void initLCD(int IIC_DATA, int IIC_CLK);
    void clear();
    void print(String linia);
    void println(String linia, int col);
    void drukLCD(String linia);
    void ppp(IPAddress linia);
    void ledled();
    //void dot();
    //void dash();
    //bool inArray(int pin, byte piny[]);
    String array2json(byte arr[],int size);
    stacjeSTRUCT radia [5]={
      {0, "TOK-FM",    "http://pl-play.adtonos.com/tok-fm"},
      {0, "RNS",       "http://stream.rcs.revma.com/ypqt40u0x1zuv"},
      {0, "357",       "http://stream.rcs.revma.com/ye5kghkgcm0uv"},
      {2, "Jazz",      "http://stream.srg-ssr.ch/m/rsj/aacp_96"},
      {2, "Classic",   "http://stream.srg-ssr.ch/m/rsc_de/aacp_96"}
    }; 
    String splitValue(String data, char separator, int index);
    String payload2LCD(String payload);
    String linieLCD[ARRAYSIZE] = { };
    String padZero(int nr);
    String getClock();
    
      
  private:
  unsigned long minuteStamp=0;
    int _pin;
    int _lcdColumns;
    int _lcdRows;
    int _lcdADR;
    //LiquidCrystal_I2C lllcd;
    

};

#endif

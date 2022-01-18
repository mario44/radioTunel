#include "time.h"

const char* ntpServer = "3.pl.pool.ntp.org";
const long  gmtOffset_sec      = 3600;
const int   daylightOffset_sec = 3600;
long epochTime;

      const char dzien_0[] PROGMEM = "Sunday";
      const char dzien_1[] PROGMEM = "Monday";
      const char dzien_2[] PROGMEM = "Tuesday";
      const char dzien_3[] PROGMEM = "Wednesday";
      const char dzien_4[] PROGMEM = "Thursday";
      const char dzien_5[] PROGMEM = "Friday";
      const char dzien_6[] PROGMEM = "Saturday";
      
      const char *const daysOFweek[] PROGMEM = {dzien_0,dzien_1,dzien_2,dzien_3,dzien_4,dzien_5,dzien_6};
      char buffer[16];

String pad(int liczba){
  String p="";
  if (liczba<10) p="0";
  return p+String(liczba);
}


long getTimeStamp() {
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      return(0);
    }
    time(&now);
    return now;
}

 String getTime(int typ=0){
       struct tm timeinfo;
       if(!getLocalTime(&timeinfo)){
          Serial.println("Failed to obtain time");
          return "...!";
      }
      int weekDay = timeinfo.tm_wday;
      int dzien   = timeinfo.tm_mday;
      int miesiac = timeinfo.tm_mon + 1;
      int rok     = timeinfo.tm_year + 1900;
      int godzina = timeinfo.tm_hour;
      int minuta  = timeinfo.tm_min;
      int sekunda = timeinfo.tm_sec;
      int dzienrok= timeinfo.tm_yday;
      snprintf(buffer, 16, daysOFweek[weekDay]);
      if (typ==0) return pad(godzina)+":"+pad(minuta);//+" "+ String(buffer);
      if (typ==1) return String(buffer);
      if (typ==2) return pad(dzien)+"."+pad(miesiac)+"."+String(rok).substring(2);
      
}
void TimersSetup(){
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

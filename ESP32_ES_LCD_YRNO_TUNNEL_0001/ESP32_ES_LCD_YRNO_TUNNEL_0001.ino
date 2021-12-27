
#include "Arduino.h"
#include <vector>
#include "WiFi.h"
#include "WiFiMulti.h"
#include "DNSServer.h"
#include "AsyncTCP.h"             //https://github.com/me-no-dev/ESPAsyncTCP 
#include "ESPAsyncWebServer.h"    //https://github.com/me-no-dev/ESPAsyncWebServer
#include "ESPAsyncTunnel.h"
#include "HTTPClient.h"


#include "SPI.h"
#include "SD.h"
#include "FS.h"
#include "Wire.h"

#include "ES8388.h"  // https://github.com/maditnerd/es8388
#include "Audio.h"   // https://github.com/schreibfaul1/ESP32-audioI2S
#include "credentials.h"
#include "extra.h"
//#include "index.h"
//#include "vue.h"
#include "web.h"
#include "ESPio.h"


#define SD_CS         21

// GPIOs for SPI
#define SPI_MOSI      13
#define SPI_MISO      12
#define SPI_SCK       14

// I2S GPIOs
#define I2S_SDOUT     26
#define I2S_BCLK       5
#define I2S_LRCK      25
#define I2S_MCLK       0

// I2C GPIOs
#define IIC_CLK       23
#define IIC_DATA      18

// Amplifier enable
#define GPIO_PA_EN    19

#define LED_BUILTIN   22
#define cur_volume_DEF  3

int volume        = 75;  // 0...100
int cur_volume    = cur_volume_DEF;
int cur_station   = 1;
int last_stations = 2;
int cur_equalizer = 0;


#define coIleSekund  3
unsigned long secundDelay = 1000*coIleSekund;  
unsigned long lastSecundDelay = 0;  
unsigned long licznik = 0;

unsigned long timerDelay15m = 1000 * 60 *15*3;  // 15minut * 3 = 45
unsigned long lastTime = 0;

String radioBuffer1;
String radioBuffer2;
String jsonBuffer;
int loopa=0;
String linia2="";
char   znakS = (char)223;

char extraInfo[64];
bool isSD        = false;

char* indexPath = "/radioTunel/public/cartoon.html";

WiFiMulti wifiMulti;
ES8388 es;
Audio audio;
ESPio clio;
AsyncWebServer server(80);

#include <Preferences.h>
Preferences preferences;

//----------------------------------------------------------------------------------------------------------------------
void onScreens(const char *linia1, const char *linia2, int lineNR){
  clio.drukLCD(linia2);
  Serial.printf("======================================\n %u :: %s:: %s\n", lineNR,linia1,linia2);
}

String padZero(int nr){
  if (nr>9) return String(nr);
  else return "0"+String(nr);
}

//+1 minuta ???? 30301

//unsigned long sekCount = 0;

void pogoda2LCD(){
    String isRun = audio.isRunning() ? "play":"stop";
    if (!audio.isRunning()) playCurStation();
      
      /*Serial.print("\n======================="); 
      for (int n=0;n<7;n++) {
          Serial.print("---"); Serial.print(n); Serial.print(" = "); Serial.println(clio.linieLCD[n]);
      }*/
      //Serial.print("1= "); Serial.println(clio.linieLCD[1]);
      //Serial.print("2= "); Serial.println(clio.linieLCD[2]);
      clio.println(clio.linieLCD[loopa],1);

      
      if (loopa==1) clio.println(radioBuffer1,0);
      if (loopa==3) clio.println(clio.getClock(),0);
      
      loopa = (loopa+1) % 7;
/*
    
      //sekCount++;
      //Serial.print(loopa);Serial.print("=");Serial.println(sekCount);
      
      //Serial.println(jsonBuffer);
      String linia1 = clio.splitValue(jsonBuffer, '\n',loopa);
      //Serial.print("#");Serial.print(loopa);Serial.println(linia1);
      if (loopa==0){
          String StrMinutes = linia1;
          int minutFromMillis = millis()/(60*1000);
          int minutesStamp = StrMinutes.toInt()+ minutFromMillis; 
          //Serial.print("millis()=");Serial.println(millis());  
          //Serial.print(StrMinutes); Serial.print(", ms=");Serial.println(minutesStamp);        
          int hh  = floor(minutesStamp/60);         
          int mm  = minutesStamp-(hh*60);
          //Serial.print(hh);Serial.print(":");Serial.println(mm);
              //mm  = mm/60;
          linia1 = padZero(hh)+":"+padZero(mm);
        
      }      
      //if (loopa==1)  linia1 = linia1+" ***";
      //if (loopa==2)  linia1 = linia1+" "+znakS+"C";
      //if (loopa==3)  linia1 += " hPa";
      //if (loopa==4)  linia1 += " m/s";
      //if (loopa==5)  linia1 += " %";

      //if (loopa==6)  linia1 = linia1;
      //if (loopa==7)  linia1 = linia1;
      //if (loopa==8) linia1 = linia1;
      if (loopa==9) linia1 = radioBuffer1;
      if (loopa==10) linia1 = isRun;
      if (loopa<10){
        clio.clear(); 
        clio.println(linia1,1);
        clio.println(linia2,0);
        linia2=linia1;
      }      
      lastSecundDelay = millis();
*/
      
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  return payload;
}



void getYrnoPogoda(){
  Serial.println("Pogoda...");
  clio.drukLCD("Pogoda...");
     if(WiFi.status()== WL_CONNECTED){
      String serverPath = proxyHost;
      Serial.println(serverPath);
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer); 
      clio.payload2LCD(jsonBuffer);    
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  
}


void savePreferences(){
         preferences.begin("my-app", false);
         preferences.putUInt("cur_volume", cur_volume);
         preferences.putUInt("cur_station", cur_station);
         preferences.putUInt("cur_equalizer", cur_equalizer);         
         preferences.end();
}  
  
void es_volume(int volum){
    es.volume(ES8388::ES_MAIN, volum);
    es.volume(ES8388::ES_OUT1, volum);
    es.volume(ES8388::ES_OUT2, volum);
}

void setup()
{
  Serial.begin(115200);
    clio.initLED(LED_BUILTIN);
    clio.ledled();    
    clio.initLCD(IIC_DATA, IIC_CLK);
    clio.drukLCD("clio.drukLCD");
          preferences.begin("my-app", false);
          cur_station   = preferences.getUInt("cur_station", 1);
          cur_volume    = preferences.getUInt("cur_volume", cur_volume_DEF);
          cur_equalizer = preferences.getUInt("cur_equalizer", 0);
          preferences.end();
 
    Serial.println("\r\nStart...");
    Serial.printf_P(PSTR("Free mem=%d\n"), ESP.getFreeHeap());

    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    SPI.setFrequency(1000000);
    SD.begin(SD_CS);


    
    //WiFi.mode(WIFI_OFF);
    //WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
      for (int i = 0; i < 8; i++) {
         wifiMulti.addAP(credential[i].ssid, credential[i].pass);
      } 
    while(wifiMulti.run() != WL_CONNECTED) {
      Serial.print("*");
      licznik++;
      clio.drukLCD("WiFi::"+String(licznik));
      delay(333);
      } 
    clio.drukLCD("Conected..."); 
    clio.println("WiFi",1); 
    delay(800);
    Serial.printf_P(PSTR("Connected\r\nRSSI: "));
    Serial.print("WiFi.status="); Serial.println(WiFi.status());
    Serial.print("WiFi.RSSI=");   Serial.println(WiFi.RSSI());
    Serial.print("IP: ");         Serial.println(WiFi.localIP());
    Serial.print("SSID: ");       Serial.println(WiFi.SSID());
    
        clio.ppp(WiFi.localIP());
        delay(2800);
        clio.println(String(WiFi.RSSI()),0);
        clio.println(String(WiFi.SSID()),1);
        delay(800);
    
    installServer();    
    Serial.printf("Connect to ES8388 codec... ");
    while (not es.begin(IIC_DATA, IIC_CLK)){
        Serial.printf("Failed!\n");
        delay(1000);
    }
    Serial.printf("OK\n");
    es_volume(0);   
    es.mute(ES8388::ES_OUT1, false);
    es.mute(ES8388::ES_OUT2, false);
    es.mute(ES8388::ES_MAIN, false);

    // Enable amplifier
    pinMode(GPIO_PA_EN, OUTPUT);
    digitalWrite(GPIO_PA_EN, HIGH);

    audio.setPinout(I2S_BCLK, I2S_LRCK, I2S_SDOUT);
    audio.i2s_mclk_pin_select(I2S_MCLK);
    audio.setVolume(cur_volume); // 0...21
    audio_SetEQNr(String(cur_equalizer));
      /* lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print(WiFi.localIP());
      lcd.setCursor(0, 1);
      lcd.print(WiFi.RSSI());*/
      //clio.drukiLCD(String(WiFi.localIP()).c_str(),  String(WiFi.RSSI()).c_str() );
       //clio.drukiLCD("1111","222");
       getYrnoPogoda(); 
      delay(333);
      listFileFromSPIFFS();
      audio.connecttoFS(SPIFFS, "/r.mp3");
      //playCurStation();
      
}
//----------------------------------------------------------------------------------------------------------------------


void loop()
{
    audio.loop();

  if ((millis() - lastTime) > timerDelay15m) {
      getYrnoPogoda(); 
      Serial.println("Pogoda --------------");  
      lastTime = millis();
  }
  
  if ((millis() - lastSecundDelay) > secundDelay) {
    //Serial.println("pogoda2LCD --------------"); 
      pogoda2LCD();
      lastSecundDelay = millis();
  }
    

                                //----------------------------------------------------------------------------------------------------------------------
                                if (Serial.available() > 0) {
                                    String odczyt = Serial.readString(); 
                                    odczyt.trim();
                                    int odczytInt = odczyt.toInt();                                     
                                      //Serial.println("\noooooooooooooooo");
                                      Serial.println(odczyt);
                                      //Serial.println(odczytInt);
                                    if(odczyt.length()>5) {
                                      audio.stopSong();
                                      audio.connecttohost(odczyt.c_str());
                                      log_i("free heap=%i", ESP.getFreeHeap());
                                    }
                                    if (odczyt == "-9") {Serial.println("-9x");ESP.restart();}
                                    if (odczytInt>0 && odczytInt<3) {
                                      Serial.println(odczytInt);
                                      cur_station = odczytInt-1;
                                      playCurStation();
                                      }
                                    if (odczyt == "+") {cur_station++;playCurStation();}
                                    if (odczyt == "-") {cur_station--;playCurStation();}
                                    if (odczyt == "*") {cur_volume++;setCurVolume();}
                                    if (odczyt == "/") {cur_volume--;setCurVolume();}
                                    
                                      if (odczyt == "pl") audio.connecttospeech("Dzień dobry. Litwo! Ojczyzno moja! ty jesteś jak zdrowie: Ile cię trzeba cenić, ten tylko się dowie, Kto cię stracił. Dziś piękność twą w całej ozdobie Widzę i opisuję, bo tęsknię po tobie.", "pl");
                                      /*if (odczyt == "q1")  audio.setTone(0,0,0);
                                      if (odczyt == "q2")  audio.setTone(0,4,0);
                                      if (odczyt == "q3")  audio.setTone(6,0,6);
                                      if (odczyt == "q4")  audio.setTone(6,-3,6);
                                      if (odczyt == "q5")  audio.setTone(6,-6,6);
                                      if (odczyt == "q6")  audio.setTone(6,-9,6);
                                      if (odczyt == "q7")  audio.setTone(6,-12,6);
                                      if (odczyt == "q8")  audio.setTone(6,-24,6);
                                      if (odczyt == "q9")  audio.setTone(6,-40,6);*/
                                  
                                }
                                //----------------------------------------------------------------------------------------------------------------------


    
}
//----------------------------------------------------------------------------------------------------------------------

//optional
/*void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}*/
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("-----eof_mp3     ");Serial.println(info);
    playCurStation();
}
void audio_showstation(const char *info){
  snprintf(extraInfo, 64, info);
    //Serial.print("station     ");Serial.println(info);
    onScreens("audio_showstation::",String(info).c_str(),326);
    radioBuffer1 = String(info).substring(0,16);
    radioBuffer2 = String(info).substring(16,32);
    es_volume(volume);
}
void audio_showstreaminfo(const char *info){
  snprintf(extraInfo, 64, info);
    //Serial.print("streaminfo  ");Serial.println(info);
    onScreens("streaminfo::",String(info).c_str(),187);
    radioBuffer1 = String(info).substring(0,16);
    radioBuffer2 = String(info).substring(16,32);
}
void audio_showstreamtitle(const char *info){
  snprintf(extraInfo, 64, info);
    //Serial.print("streamtitle ");Serial.println(info);
    onScreens("Streamtitle::",String(info).c_str(),191);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    //Serial.print("lasthost    ");Serial.println(info);
    onScreens("Lasthost::",String(info).c_str(),203);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}



String getRadioInfo(){
  const String      sep = "!"; 
  String v = String(cur_volume);
  String q = String(cur_equalizer);
  String n = String(cur_station);
  String s = String(clio.radia[cur_station].info);
  String ri    = String(WiFi.RSSI());
    radioBuffer1 = extraInfo;
    radioBuffer2 = s;

  return n+sep+v+sep+ri+sep+s+sep+String(extraInfo)+sep+q;
}


void setCurVolume(){
    if (cur_volume < 0)  cur_volume = 0;
    if (cur_volume > 19) cur_volume = 19;
    int ampli = clio.radia[cur_station].ampli;
    if (cur_volume<2) ampli = 0;
    audio.setVolume(cur_volume + ampli); // 0...21
    //clio.println("Vol="+String(cur_volume),0);
    //clio.println(("Volume="+String(cur_volume)).c_str(),1); 
    Serial.println("?????Vol="+String(cur_volume)); 
    savePreferences();
}

//ajax
void audio_ChangeVolume(String ParamValue){
    if (ParamValue=="p") cur_volume++;
    if (ParamValue=="m") cur_volume--;
    if (ParamValue=="*") cur_volume++;
    if (ParamValue=="-") cur_volume--;
    setCurVolume();
}

void audio_SetStationNr(String ParamValue){
    cur_station = ParamValue.toInt();
    playCurStation();
}

//#define isint(X) (!((X)==(X)))

void audio_ChangeStation(String ParamValue){
    //int valu = ParamValue.toInt();
    Serial.println('+++++++++++++++++++++');
    //Serial.println(valu);
    //Serial.println(isnan(valu));
    //Serial.println(isint(valu));
    //if (isnan(valu)) cur_station = valu;
    if (ParamValue=="p") cur_station++;
    if (ParamValue=="m") cur_station--;
    if (ParamValue=="*") cur_station++;
    if (ParamValue=="-") cur_station--;  
    playCurStation();
}

// bez mp3
void playCurStation(){
    if (cur_station < 0) cur_station = 4;
    if (cur_station > 4) cur_station = 0; 
    es_volume(0);
        String CoJestGrane = "/"+String(clio.radia[cur_station].info)+".mp3"; 
        if (!SPIFFS.exists(CoJestGrane)){
            CoJestGrane = "/r.mp3";
        }
        const char* stacjaNazwa = CoJestGrane.c_str();
        Serial.print("#473 stacjaNazwa=");Serial.println(stacjaNazwa);
            
    audio.connecttohost(clio.radia[cur_station].stream);
    clio.println(("Stacja="+String(clio.radia[cur_station].info)).c_str(),0);   
    //onScreens("cur_station",("Station="+String(cur_station)).c_str(),423);
    Serial.print("clio.radia=");
    Serial.print(clio.radia[cur_station].info);
    Serial.println(clio.radia[cur_station].stream);
    savePreferences();
}
/*
void playCurStationURL(){
        audio.stopSong();
        //es.mute(ES8388::ES_MAIN, true);
        if (cur_station <  0)            cur_station = last_stations;
        if (cur_station > last_stations) cur_station = 0;    
        //onScreens(String(cur_station).c_str(),392);
        savePreferences();
        //delay(222);
        //es.mute(ES8388::ES_MAIN, false);
        audio.connecttohost(clio.radia[cur_station].stream);  
      
}
*/
/* 
// z mp3
  void playCurStation(){
        String CoJestGrane = "/"+String(clio.radia[cur_station].info)+".mp3"; 
        if (!SPIFFS.exists(CoJestGrane)){
            CoJestGrane = "/r.mp3";
        }
        const char* stacjaNazwa = CoJestGrane.c_str();
        //onScreens(stacjaNazwa,401);
        audio.stopSong();
        es.mute(ES8388::ES_MAIN, true);
        delay(222);
        es.mute(ES8388::ES_MAIN, false);
        audio.connecttoFS(SPIFFS, stacjaNazwa);
      
}*/

void audio_SetEQNr(String ParamValue){
      cur_equalizer = ParamValue.toInt();
      //onScreens(String(cur_equalizer).c_str(),477);    
      audio.setTone(qqq[cur_equalizer].l, qqq[cur_equalizer].m, qqq[cur_equalizer].h);
}
void audio_SetEQ(String ParamValue){
      Serial.println(ParamValue);
      int arr[7] = {};
      for (int i=0; i<7; i++){
        String l = clio.splitValue(ParamValue, ';',i);
        arr[i] = l.toInt();
        //Serial.print(i);Serial.print("=");Serial.println(arr[i]);
      }
      //audio.setTone(arr[0],arr[1],arr[2]);
      audio.newTone(arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6]);
      //????????????????????????????????????????????????????????????????????????????????????????????????????
}

void audio_SetStationUrl(const String ParamValue){
      //onScreens(("Url="+String(ParamValue)),483);
      audio.stopSong();
      es_volume(0);
      audio.setVolume(0);
      delay(333);
      audio.connecttohost(ParamValue.c_str());
      audio.setVolume(cur_volume);
      es_volume(volume);
}


void esp_reBootSleep(const String ParamValue){
    if (ParamValue=="0") { 
        audio.setVolume(0);
        audio.stopSong();
        es_volume(0); 
        delay(1500); 
        ESP.restart();
    } // reboot
    if (ParamValue=="1") {audio.stopSong(); delay(500);playCurStation();} //replay
    if (ParamValue=="2") {
        audio.stopSong();
        es_volume(0); 
        delay(500); 
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_18,0);
        esp_deep_sleep_start();
    } //sleep
  
}





/************* SERVER *******************/
/************* SERVER *******************/
/************* SERVER *******************/
/************* SERVER *******************/
/************* SERVER *******************/
/************* SERVER *******************/

void installServer(){
  clio.println("installServer...",1);

  Serial.println(indexPath);
  server.rewrite( "/", indexPath) ;
  server.rewrite( "/index.html", indexPath);
  //server.rewrite( "/favicon.ico", "/radioTunel/public/favicon.ico");

   // tunnel the index.html request 
  server.on(indexPath, HTTP_GET, [&](AsyncWebServerRequest *request){
      ClientRequestTunnel tunnel; 
      if (tunnel.open("https://znakzorro.github.io", request->url())) {
          String result = tunnel.getString();
          request->send(200, "text/html", result);          
      } else {
          request->send(tunnel.getHttpCode());
      }
  });

  server.on("/public/*", HTTP_GET, [&](AsyncWebServerRequest *request){
    String moved_url = "https://znakzorro.github.io"+request->url();
    Serial.println(moved_url);
    request->redirect(moved_url);
  });


///////////////////////////////////////////
/*
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", PAGE_HTML);
  });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", PAGE_HTML);
  });
*/
  
  server.on("/teren.web.json", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/json", TEREN_WEB_JSON);
  });
  server.on("/stacje.json", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/json", STACJE_JSON);
  }); 
  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "image/svg+xml", RADIO_SVG);
  });
  server.on("/radio.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "image/svg+xml", RADIO_SVG);
  });

  
  // AJAXY *************************
  // AJAXY *************************
  // AJAXY *************************
  server.on("/radio", HTTP_GET, [](AsyncWebServerRequest *request){
    clio.ledled();
    //last_get_url = "";
    /******************************/
     //List all parameters
     int params = request->params();
     for(int i=0;i<params;i++){
          AsyncWebParameter* p = request->getParam(i); 
          //Serial.print("get=");Serial.print(p->name().c_str()); Serial.print("="); Serial.println(p->value().c_str());
          
          String ParamName  = String(p->name());
          String ParamValue = p->value();
                //#ifdef DEBUG
                   //if(ParamName !="n") onScreens((String("PName | PValue= ")+String(ParamName)+" | "+String(ParamValue)).c_str(),662);
               // #endif  
           
           if (ParamName=="start") {audio.pauseResume();}
           if (ParamName=="v")  audio_ChangeVolume(ParamValue);  
           if (ParamName=="s")  audio_ChangeStation(ParamValue); 
           if (ParamName=="t")  audio_SetStationNr(ParamValue);
           if (ParamName=="q")  audio_SetEQNr(ParamValue);
           if (ParamName=="qq")  audio_SetEQ(ParamValue);
           if (ParamName=="z")  savePreferences(); 
           if (ParamName=="x")  audio_SetStationUrl(ParamValue);
           
           if (ParamName=="r")  {esp_reBootSleep(ParamValue);}
           
           
          if (ParamName=="n") { // drugi parametr
              //onScreens(("ParamName="+String(ParamName)).c_str(),917);
              //const char* czyLoop = p->value().c_str();
              //onScreens(("czyLoop="+String(czyLoop)).c_str(),919);
          }
           
           //replay
           
               //if (ParamName=="a") {alarmState(ParamValue); }
               //if (ParamName=="c") {alarmColor(ParamValue); }
           // 
           
           //if (ParamName=="r") {playCurStation(); }                  
           //if (ParamName=="ap")  installAP(ParamValue);           
                     
           if (ParamName=="mp3")  {
                //playMp3(ParamValue);
           }

          if (ParamName=="w") {
              //zapiszSPIFFS("/ssid.txt",p->value().c_str());
              //Serial.print("#748 radio?w="); Serial.println(ParamValue);
          }

         // prog mem prog mem prog mem prog mem prog mem prog mem
          /*if (ParamName=="p") {
            Serial.println("ppp3");
                String as[numParams];
                transCSV2Array(as,(String(ParamValue)).c_str());
                        //Serial.println(as[0]);
                       // Serial.println(as[1]);
                        //Serial.println(as[2]);
                        //Serial.println(as[3]); 
                        if (as[3]) {
                          String nnn = "/z"+as[0]+".txt";
                          //Serial.println(nnn); 
                          zapiszSPIFFS(nnn.c_str(),String(as[3]).c_str());
                        }                           
          }
           */
          if (ParamName=="iir") {
            /*
                    String as[numParams];
                    transCSV2Array(as,p->value());
                    //for (int i = 0; i < numParams; i++) onScreens(as[i].c_str(),100+i);
                    
                    //audio.setTone(as[3].toInt(),as[4].toInt(),as[5].toInt(),as[0].toFloat(),as[1].toFloat(),as[2].toFloat(),as[6].toFloat()); 
                    //324;626;5041;-7;6;-12;2.6;  
                    //audio.setTone(as[3].toInt(),as[4].toInt(),as[5].toInt());//,as[0].toInt(),as[1].toInt(),as[2].toInt(),as[6].toFloat()); 
                   String z = as[7];
                    if(z!=""){
                        #ifdef DEBUG
                          onScreens(("ZapisEQ="+String(z)).c_str(),911); 
                        #endif
                        zapiszSPIFFS("/eq.txt",p->value().c_str());
                    }
            */
          } 
                  
          //if (ParamName=="u") {
            /*//snprintf(extraInfo, 64, p->value().c_str());
            //sprintf(main_url,p->value());
            //String main_url     = p->value();
            const char* out_url = p->value().c_str();
            //snprintf(extraInfo, 64, out_url);
               #ifdef DEBUG                 
                  onScreens(out_url,929);
              #endif
                out_station=true;
                audio.stopSong();
                delay(100);
                audio.connecttohost(out_url);
            }
            */
          // IRRfilter Biquad Filter Coefficient
          /*if (ParamName=="q") {
              #ifdef DEBUG
                  onScreens("filter IIR",621);
                  onScreens(String(ParamValue).c_str(),622);
              #endif
                       
          }*/
           
          
           
    }
 
    request->send(200, "text/plain",getRadioInfo());
  });
 
  server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request){
    bool gramy = audio.pauseResume();
    request->send(200, "text/plain",  getRadioInfo());
  });
 
/*
  server.on("/ap", HTTP_GET, [](AsyncWebServerRequest *request){
            Serial.println("AP===");
            String RedirectUrl = "http://";
            if (ON_STA_FILTER(request)) {
              RedirectUrl += WiFi.localIP().toString();
            } else {
              RedirectUrl += WiFi.softAPIP().toString();
            }
            RedirectUrl += "/index.htm";
            request->redirect(RedirectUrl);
  });
*/
  
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  //initWebSocket();  
}

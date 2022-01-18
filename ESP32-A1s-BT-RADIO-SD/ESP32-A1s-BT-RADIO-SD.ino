#include <vector>
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ESPAsyncTunnel.h"
#include "ArduinoJson.h"

//#include "SPI.h"
//#include "SD.h"
//#include "FS.h"
//#include "Wire.h"
//#include "HTTPClient.h"
#include "Arduino_JSON.h"


#include "extra.h"
#include "lcd1602.h"
#include "Czas.h"

//#include "web.h"
//#include "ESPio.h"

#define SD_CS         13
#define SPI_MOSI      15
#define SPI_MISO       2
#define SPI_SCK       14

#define I2S_DOUT         26  //(data_out_num)
#define I2S_BCLK         27  //(bck_io_num)
#define I2S_LRC          25  //(ws_io_num)

#define ES8388_IIC_CLK   32
#define ES8388_IIC_DATA  33


#define GPIO_PA_EN    21
#define I2S_MCLK       0

String StationName = String(stacje[cur_station].info);
int loopa=0;

////////////////// - POGODA - ///////////////////////////////////////////////////
unsigned long secundDelay = 1000;  
unsigned long lastSecundDelay = 0;  
unsigned long timerDelay = 1000 * 60 *15*2;  // 15minut *2
unsigned long lastTime = 0;
String jsonBuffer;
int nr=0;
String pusto="       ";
String pola[7] = {"       ","       ","       ","       ","       ","       ","       "};
String linia1_0[8] = {"        ","        ","        ","        ","        ","        ","        "};

String linia1;
char   znakS = (char)223;
String openWeatherMapApiKey = "3fd473910363f525e0ccda7233d75105";
String city = "Szczecin";
String countryCode = "pl";

//////////////////////////////////////////////////////////////////////////////////

//const String ssid = "multimedia_wifi_mm";
//const String password = "mariuszek";

const String ssid = "serwis";
const String password = "servis11";

AsyncWebServer server(80);
char* indexPath = "/radioTunel/public/New_A1S_tunel_radio.html";

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

void Pogoda(){
  Serial.println("Pogoda...");
     if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey+ "&units=metric&lang=PL";
      Serial.println(serverPath);
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      } 
          String str_rain = "";
          str_rain = rounda(double(myObject["rain"]["1h"]),1);
          if (str_rain != "") str_rain = " R:"+str_rain; else str_rain ="0";  
        String str_temp = rounda(double(myObject["main"]["temp"]),1);
        String str_feel = rounda(double(myObject["main"]["feels_like"]),1);
        String str_temp_max = rounda(double(myObject["main"]["temp_max"]),1);
        String str_temp_min = rounda(double(myObject["main"]["temp_min"]),1);

            float float_temp = str_temp.toFloat();
            String tz="";  if (float_temp>0) tz="+";
            float float_feel = str_feel.toFloat();
            String fz="";  if (float_feel>0) fz="+";

            float float_temp_max = str_temp_max.toFloat();
            String tmz="";  if (float_temp_max>0) tmz="+";
            float float_temp_min = str_temp_min.toFloat();
            String tnz="";  if (float_temp_max>0) tmz="+";
        String str_wind = rounda(double(myObject["wind"]["speed"]),0);
        //String linia1 = str_temp+znakS+"C";
        linia1 = str_temp+znakS+"C";
        String str_humi = rounda(double(myObject["main"]["humidity"]),0);
        String str_pres = rounda(double(myObject["main"]["pressure"]),0); 
          Serial.println(myObject["weather"][0]["description"]);
          Serial.println(myObject["weather"][0]["main"]);
          String opis = myObject.stringify(myObject["weather"][0]["main"]);
          opis.replace("\"","");
        String linia0 = opis;
        Serial.println(linia0);
        Serial.println(linia1);
      lcd.clear();      
      lcd.setCursor(9, 0);
      lcd.setCursor(0, 1); 
      lcd.print(linia1);   
       pola[0] = make_str(str_feel+znakS+"C", 7); 
       linia1_0[0] = make_str2("Feels", 8);
       pola[1] = make_str(str_wind+"m/s", 7);
       linia1_0[1] = make_str2("Wind", 8);
       pola[2] = make_str(str_humi+"%", 7);
       linia1_0[2] = make_str2("Humidity", 8);
       pola[3] = make_str(str_pres+"hPa", 7);
       linia1_0[3] = make_str2("Pressure", 8);
       pola[4] = make_str(opis, 7);
       linia1_0[4] = make_str2("Weather", 8);
       pola[5] = make_str(str_rain+"mm", 7);
       linia1_0[5] = make_str2("Fall", 8);
       pola[6] = make_str(linia1, 7);
       linia1_0[6] = make_str2("Temp", 8); 

    }
    else {
      Serial.println("WiFi Disconnected");
    }  
}

void setupWifi() {
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}

void setupServer() {
  // rewrites
  server.rewrite( "/", indexPath) ;
  server.rewrite( "/radioTunel/public/New_A1S_tunel_radio.html", indexPath);
  server.rewrite( "/favicon.ico", "/radioTunel/public/favicon.ico");
  
  // tunnel the index.html request 
  server.on(indexPath, HTTP_GET, [&](AsyncWebServerRequest *request){
      ClientRequestTunnel tunnel; 
      if (tunnel.open("https://mario44.github.io", request->url())) {
          String result = tunnel.getString();
          request->send(200, "text/html", result);          
      } else {
          request->send(tunnel.getHttpCode());
      }
  });

  server.on("/public/*", HTTP_GET, [&](AsyncWebServerRequest *request){
    String moved_url = "https://mario44.github.io"+request->url();
    request->redirect(moved_url);
  });

  server.on("/radio", HTTP_GET, [](AsyncWebServerRequest *request){
    int params = request->params();
     for(int i=0;i<params;i++){
          AsyncWebParameter* p = request->getParam(i); 
          Serial.print("get=");Serial.print(p->name().c_str()); Serial.print("="); Serial.println(p->value().c_str());
          String ParamName  = String(p->name());
          String ParamValue = p->value();
                //#ifdef DEBUG
                   //if(ParamName !="n") onScreens((String("PName | PValue= ")+String(ParamName)+" | "+String(ParamValue)).c_str(),662);
               // #endif  
           //onScreens((String("PName | PValue= ")+String(ParamName)+" | "+String(ParamValue)).c_str(),662);
           
           //if (ParamName=="start") {audio.pauseResume();}
           if (ParamName=="v")  audio_ChangeVolume(ParamValue);  
           if (ParamName=="s")  audio_ChangeStation(ParamValue); 
           //if (ParamName=="t")  audio_SetStationNr(ParamValue);
           //if (ParamName=="q")  audio_SetEQNr(ParamValue);
           //if (ParamName=="qq")  audio_SetEQ(ParamValue);
           //if (ParamName=="z")  savePreferences(); 
           if (ParamName=="x")  audio_SetStationUrl(ParamValue);
           if (ParamName=="a")  SetStationName(ParamValue);
           //if (ParamName=="r")  {esp_reBootSleep(ParamValue);}
           
     }
    request->send(200, "text/plain",getRadioInfo());
  });
  
  server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request){
    bool gramy = audio.pauseResume();
    request->send(200, "text/plain",  getRadioInfo());
  });
  
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  
}
    

void setup() {

  
  setupWifi();
  Serial.println();
  Serial.print("You can connect to ");
  Serial.println(WiFi.localIP());
  setupServer();
  initLCD();
  getPreferences();
  
  pinMode(GPIO_PA_EN, OUTPUT);
  digitalWrite(GPIO_PA_EN, HIGH);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.i2s_mclk_pin_select(I2S_MCLK);
  audio.setVolume(21); // 0...21
  audio.setTone(6, -6, 6);
  btnAttachInt();
  Serial.printf("Connect to ES8388 codec... ");
  while (not es.begin(ES8388_IIC_DATA, ES8388_IIC_CLK)) {Serial.printf("Failed!\n"); delay(1000);}
  Serial.printf("OK\n");
  esVolume(cur_volume);
  esMute(false);

  TimersSetup();
  Pogoda();
  lastSecundDelay = millis();
  lastTime        = millis();

}

void dajCzas(){
  String czas = getTime();
  String dayOfWeek = getTime(1);
  String date = getTime(2);
  dayOfWeek = make_str(dayOfWeek,10);
  date = make_str(date,10);
  
  lcd.setCursor(0, 0);
  lcd.print(czas);
  //lcd.setCursor(6, 0);
  //lcd.print(dayOfWeek);
        
  if (loopa%6==0){
      nr = (nr+1) % 7;
      lcd.setCursor(0, 1);
      lcd.print(linia1_0[nr]);
      lcd.setCursor(9, 1); 
      lcd.print(pola[nr]);
      
      if (nr==8) {
        lcd.setCursor(0, 1);
        lcd.print(linia1_0[0]);
        lcd.setCursor(9, 1); 
        lcd.print(pola[0]);}
      if (nr==1) {
        lcd.setCursor(6, 0);
        lcd.print(dayOfWeek);
      }
      if (nr==5) {
        lcd.setCursor(6, 0);
        lcd.print(date);
      }
  } 
  loopa++;
}

void loop() {
  audio.loop(); 
  volumePressed();
  stationPressed();
 
  if ((millis() - lastTime) > timerDelay) {
      Pogoda();   
      lastTime = millis();
  }

  if ((millis() - lastSecundDelay) > secundDelay) {
      //timeClient.update();
      dajCzas();   
      lastSecundDelay = millis();
  }
if (Vol_ButtonPressed > 0) {
      if (scrollMode==true){
          scrollMode=false;
          }
      Serial.print("VOLUME     ");Serial.println(cur_volume);
      lcd.setCursor(6, 0);
      lcd.print("VOLUME " + make_str(String(cur_volume), 3));
      esVolume(cur_volume);
      savePreferences();
      Vol_ButtonPressed = 0;
      ret = 1;
      }

  if (Station_ButtonPressed > 0) {
      Serial.print("CUR_STATION     ");Serial.println(cur_station);    
      esVolume(0);
      esMute(true);
      StationName = stacje[cur_station].info;
      hostURL = stacje[cur_station].stream;
      audio.connecttohost(stacje[cur_station].stream);
      delay(200); 
      esMute(false);
      esVolume(cur_volume);
      savePreferences();
      Station_ButtonPressed = 0;
      }
          
  if (millis() - millisBUTTON > 200 + plusBUTTON) {
      loop_BUTTONS();
      millisBUTTON = millis();
      plusBUTTON = 0;
    }


}

void audio_info(const char *info){
    //Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata  
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){ 
  Serial.print("eof_mp3     ");Serial.println(info);

}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
    streamtitle = String(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    //Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    //Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}


String getRadioInfo(){
  const String      sep = "!"; 
  String v = String(cur_volume);
  String ri    = String(WiFi.RSSI());
  return v+sep+ri+sep+StationName+sep+hostURL+sep+streamtitle;
}

void audio_ChangeVolume(String ParamValue){
    if (ParamValue=="p") cur_volume++;
    if (ParamValue=="m") cur_volume--;
    if (cur_volume < 0){cur_volume = 0;}
    if (cur_volume > 100){cur_volume = 100;}
    Vol_ButtonPressed++;
}

void audio_SetStationUrl(const String ParamValue){
      hostURL = ParamValue;
      Serial.println(hostURL); 
      audio.stopSong();
      esVolume(0);
      esMute(true);
      delay(333);
      audio.connecttohost(ParamValue.c_str());
      delay(333);
      esMute(false);
      esVolume(cur_volume);
      savePreferences();
}


void SetStationName(const String ParamValue){
  StationName = ParamValue;
  //String(stacje[cur_station].info) = StationName;
  Serial.println(StationName);
}

void audio_ChangeStation(String ParamValue){
    if (ParamValue=="p") cur_station++;
    if (cur_station > last_stations) {cur_station = 0;}
    if (ParamValue=="m") cur_station--;
    if (cur_station <  0) {cur_station = last_stations;}
    audio.stopSong();
    esVolume(0);
    esMute(true);
    StationName = stacje[cur_station].info;
    hostURL = stacje[cur_station].stream;
    delay(333);
    audio.connecttohost(stacje[cur_station].stream);
    delay(333); 
    esMute(false);
    esVolume(cur_volume);
    savePreferences();
}

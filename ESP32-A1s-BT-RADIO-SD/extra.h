#include "Audio.h"
#include "ES8388.h"
#include <Preferences.h>


Preferences preferences;
Audio audio;
ES8388 es;
struct Music_info {
    String name;
    int length;
    int runtime;
    int volume;
    int status;
    int mute_volume;
} 
music_info = {"", 0, 0, 0, 0, 0};


#define last_stations  18
#define max_stations  last_stations+1
String streamtitle;
String hostURL = "";

struct stationsSTRUCT  {
  char const *stationNum;
  char const *info;
  char const *stream;
  
};

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};




unsigned long millisBUTTON = millis();
unsigned long millisLCD = millis();
unsigned long millisScroll = millis();
unsigned long BTmillisScroll  = millis();
unsigned long plusBUTTON   = 0;
unsigned long plusVoLBUTTON   = 0;

int vol_up_press;
int vol_down_press;
int st_down_press;
int st_up_press;
int Vol_ButtonPressed = 0;
int Station_ButtonPressed =0;
int ret = 0;
bool symLed = false;

int cur_volume = 70;
int cur_station = 4;
bool btmode = false;
bool scrollMode = false;

#define LONG_PRESS_TIME  1000
int lastStateK6 = HIGH;
int currentStateK6;
int lastStateK5 = HIGH;
int currentStateK5;
int lastStateK4 = HIGH;
int currentStateK4;
int lastStateK3 = HIGH;
int currentStateK3;

unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
int LongPress = 0;
int ShortPress = 0;

#define LED_BUILTIN   22
#define pinKEY6        5
#define pinKEY5       18
#define pinKEY4       23
#define pinKEY3       19

Button button3 = {pinKEY3, 0, false};
Button button4 = {pinKEY4, 0, false};
Button button5 = {pinKEY5, 0, false};
Button button6 = {pinKEY6, 0, false};

void IRAM_ATTR isr1() {button3.numberKeyPresses += 1;button3.pressed = true;}
void IRAM_ATTR isr2() {button4.numberKeyPresses += 1;button4.pressed = true;}
void IRAM_ATTR isr3() {button5.numberKeyPresses += 1;button5.pressed = true;}
void IRAM_ATTR isr4() {button6.numberKeyPresses += 1;button6.pressed = true;}

void savePreferences(){
         preferences.begin("my-app", false);
         preferences.putUInt("cur_volume", cur_volume);
         preferences.putUInt("cur_station", cur_station);
         preferences.putUInt("btmode", btmode);
         preferences.putUInt("scrollMode", scrollMode);
         preferences.putString("hostURL", hostURL);
         preferences.end();
}

void btnAttachInt(){
  pinMode(button3.PIN, INPUT_PULLUP);
  pinMode(button4.PIN, INPUT_PULLUP);
  pinMode(button5.PIN, INPUT_PULLUP);
  pinMode(button6.PIN, INPUT_PULLUP);
  attachInterrupt(button3.PIN, isr1, RISING);
  attachInterrupt(button4.PIN, isr2, RISING);
  attachInterrupt(button5.PIN, isr3, RISING);
  attachInterrupt(button6.PIN, isr4, RISING);
}
void getPreferences(){
  preferences.begin("my-app", false);
  cur_station   = preferences.getUInt("cur_station", 4);
  cur_volume    = preferences.getUInt("cur_volume", 70);
  btmode        = preferences.getUInt("btmode", false);
  scrollMode    = preferences.getUInt("scrollMode", false);
  hostURL       = preferences.getString("hostURL","http://pl-play.adtonos.com/tok-fm");
  preferences.end();
}

void esVolume(int vol){
  es.volume(ES8388::ES_MAIN, vol);
  es.volume(ES8388::ES_OUT1, vol);
  es.volume(ES8388::ES_OUT2, vol);
}
void esMute(bool mute){
  es.mute(ES8388::ES_OUT1, mute);
  es.mute(ES8388::ES_OUT2, mute);
  es.mute(ES8388::ES_MAIN, mute);
}

void volumePressed(){
  if (vol_up_press > 0){cur_volume++;}
  if (cur_volume > 100){cur_volume = 100;}
    vol_up_press = 0;

  if (vol_down_press > 0){cur_volume--;}
  if (cur_volume < 0){cur_volume = 0;}
    vol_down_press = 0;
}
    
void stationPressed(){
  if (st_up_press > 0){cur_station++;}
  if (cur_station > last_stations) {cur_station = 0;}
    st_up_press = 0;
  
  if (st_down_press > 0){cur_station--;}
  if (cur_station <  0) {cur_station = last_stations;}
    st_down_press = 0;
}

String rounda(double valD, unsigned char precyzja){
  if (isnan(valD)) return "";
  else
  {
    String ret = String((((double)(int(valD*10))+0.5)/10),precyzja);
    ret.trim();
    if (precyzja==0){
      ret.replace(",","");
    }
    return ret; 
  }
}

String make_str(String str, int num){
    if (str.length()>num) return str;
    String plus="";
    for(int i = 0; i < (num - str.length()); i++)
        plus += ' ';  
    return plus+str;
}

String make_str2(String str, int num){
    if (str.length()>num) return str;
    String plus="";
    for(int i = 0; i < (num - str.length()); i++)
        plus += ' ';  
    return str+plus;
}

/*
String make_str_volume(String str){
    if (str.length()>3) return str;
    String plus="";
    for(int i = 0; i < (3 - str.length()); i++)
        plus += ' ';  
    return plus+str;
}
*/
void loop_BUTTONS() {

 currentStateK6 = digitalRead(pinKEY6);
 currentStateK5 = digitalRead(pinKEY5);
 currentStateK4 = digitalRead(pinKEY4);
 currentStateK3 = digitalRead(pinKEY3);

 
 
 //vol_up_press = 0;
 //vol_down_press = 0;
  byte bitState = 0;
  if (button3.pressed) {bitSet(bitState, 0); Serial.println("BUTTON3"); button3.pressed = false;}
  if (button4.pressed) {bitSet(bitState, 1); Serial.println("BUTTON4"); button4.pressed = false;}
  if (button5.pressed) {bitSet(bitState, 2); Serial.println("BUTTON5"); button5.pressed = false;}
  if (button6.pressed) {bitSet(bitState, 3); Serial.println("BUTTON6"); button6.pressed = false;}
 ///////////////////////////////////////////////////////////////////////////////////////
 //longDetect(currentStateK6, lastStateK6);
 //longDetect(currentStateK5, lastStateK5);
 //longDetect(currentStateK4, lastStateK4);
 //longDetect(currentStateK3, lastStateK3);
 ///////////////////////////////////////////////////////////////////////////////////////
 
 if(lastStateK6 == HIGH && currentStateK6 == LOW){        // button is pressed
    ShortPress = 1;
    pressedTime = millis();
    }
  else if(lastStateK6 == LOW && currentStateK6 == HIGH) { // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if( pressDuration > LONG_PRESS_TIME ){
      Serial.println("K6 long press is detected");
      LongPress = 1;
      ShortPress = 0;
     }
  }
  lastStateK6 = currentStateK6;  // save the the last state
 ///////////////////////////////////////////////////////////////////////////////////////
  if(lastStateK5 == HIGH && currentStateK5 == LOW){        // button is pressed
    ShortPress = 1;
    pressedTime = millis();
    }
  else if(lastStateK5 == LOW && currentStateK5 == HIGH) { // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if( pressDuration > LONG_PRESS_TIME ){
      Serial.println("K5 long press is detected");
      LongPress = 1;
      ShortPress = 0;
     }
  }
  lastStateK5 = currentStateK5;  // save the the last state
//////////////////////////////////////////////////////////////////////////////////////////
  if(lastStateK4 == HIGH && currentStateK4 == LOW){        // button is pressed
    ShortPress = 1;
    pressedTime = millis();
    }
  else if(lastStateK4 == LOW && currentStateK4 == HIGH) { // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if( pressDuration > LONG_PRESS_TIME ){
      Serial.println("K4 long press is detected");
      LongPress = 1;
      ShortPress = 0;
     }
  }
  lastStateK4 = currentStateK4;  // save the the last state
/////////////////////////////////////////////////////////////////////////////////////////
  if(lastStateK3 == HIGH && currentStateK3 == LOW){        // button is pressed
    ShortPress = 1;
    pressedTime = millis();
    }
  else if(lastStateK3 == LOW && currentStateK3 == HIGH) { // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if( pressDuration > LONG_PRESS_TIME ){
      Serial.println("K3 long press is detected");
      LongPress = 1;
      ShortPress = 0;
     }
  }
  lastStateK3 = currentStateK3;  // save the the last state
 
//////////////////////////////////////////////////////////////////////////////////////////

  if (bitState != 0) {
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); //symLed=0;
    if (bitState == 8 && ShortPress == 0){
      //symLed=!symLed;
      scrollMode = true;
      savePreferences();
      Serial.println("SYM_LED:      "+String(scrollMode));
    }
    //if (scrollMode==true) {Serial.println(String(scrollMode));}
    //if (ShortPress == 0){......................
    
    Serial.println(bitState);
    Serial.println("SHORTPRESS: "+String(ShortPress));
    Serial.println("LONGPRESS: "+String(LongPress));

    plusBUTTON = 500;
    //if (bitState == 1) {}
    //if (bitState == 2) {}
    if (bitState == 4 && ShortPress == 1)  {Serial.println("VOL DOWN"); vol_down_press = 1; Vol_ButtonPressed++; ret = 1;}
    if (bitState == 8 && ShortPress == 1)  {Serial.println("VOL UP"); vol_up_press = 1; Vol_ButtonPressed++; ret = 1;} 
    
    if (bitState == 1 && ShortPress == 1)  {Serial.println("STATION DOWN"); st_down_press = 1; Station_ButtonPressed++;}
    if (bitState == 2 && ShortPress == 1)  {Serial.println("STATION UP"); st_up_press = 1; Station_ButtonPressed++;}
    
    //if (bitState == 12 && !digitalRead(LED_BUILTIN) == HIGH) {Serial.println("PLAY MODE: MP3 PLAYER");}
    //if (bitState == 12 && !digitalRead(LED_BUILTIN) == LOW) {Serial.println("PLAY MODE: INTERNET RADIO");}
    
    if (bitState == 8 && ShortPress == 0) {Serial.println("PLAY MODE: INTERNET RADIO");
    if (btmode == true) {
        btStop();
        btmode = false;
        savePreferences();
        audio.setVolume(0);
        esVolume(0);
        esMute(true);
        delay(1000); 
        ESP.restart(); }
    }
    
    if (bitState == 4 && ShortPress == 0) {Serial.println("PLAY MODE: BLUETOOTH"); 
    
      if (btmode == false) {
        audio.stopSong();
        delay(200);
        btmode = true;
        savePreferences();
        audio.setVolume(0);
        esVolume(0);
        esMute(true);
        delay(1000); 
        ESP.restart(); }
    }
 
    Serial.println("RET: "+String(ret));
  }
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////  Station_ButtonPressed
stationsSTRUCT stacje [last_stations+1]={
  {"01","TOK-FM","http://pl-play.adtonos.com/tok-fm"},
  {"02","RMF Top 30 PL","http://195.150.20.243:8000/rmf_top_5_pl"},
  {"03","RMF W PRACY","http://31.192.216.10:8000/rmf_w_pracy"},
  {"04","RMF BALLADY","http://31.192.216.7:8000/rmf_nostalgia"}, //Snowy White - Bird of Paradise
  {"05","RMF-FM",  "http://195.150.20.243:8000/rmf_fm"},
  {"06","RMF-24",  "http://195.150.20.7:8000/rmf_24"},
  {"07","RMF HOT NEW",  "http://217.74.72.11:8000/rmf_hot_new"},
  {"08","RMF HARD & HEAVY",  "http://217.74.72.11:8000/rmf_hard_heavy"},
  {"09","RMF 3 POP-ROCK",  "http://195.150.20.7:8000/rmf_3"},
  {"10","RADIO-ZET",   "http://zet-tun.cdn.eurozet.pl:8080"},
  {"11","ZLOTE-PRZEBOJE",  "https://pl2-play.adtonos.com/zote-przeboje"},
  {"12","RMF Blues",  "http://217.74.72.11:8000/rmf_blues"},
  {"13","RMF 25 Lat FM",   "http://195.150.20.9:8000/rmf_20lat"},
  {"14","RMF NIEZAPO MEL",  "http://195.150.20.242:8000/rmf_niezapomniane_melodie"},
  {"15","SZCZECIN",  "http://stream4.nadaje.com:11986/prs.aac"},
  {"16","Radio SUPERNOVA",  "https://ext03.ic.smcdn.pl/1380-1.aac"},
  {"17","RADIO PLUS",  "https://ext03.ic.smcdn.pl/4000-1.mp3"},
  {"18","RADIO POGODA",  "https://pl-play.adtonos.com/radio-pogoda"},
  {"19","Radio Nowy Świat", "http://stream.rcs.revma.com/ypqt40u0x1zuv"}
};

const char RADIO_SVG[] PROGMEM = R"=====(
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512"><path fill="#6961d8" d="M73.8 141.9c-15.2 6-25.8 21.8-25.8 39.5v256c0 23.5 18.5 42.7 41.6 42.7h332.8c23.1 0 41.6-19.2 41.6-42.7v-256c0-23.7-18.5-42.7-41.6-42.7H179l171.8-71.3L336.7 32 73.8 141.9zM235 438c-35.4 0-64-28.6-64-64s28.6-64 64-64 64 28.6 64 64-28.6 64-64 64zm256-171.3h-32v-46.2h-44.8v46.2H96v-85.3h320v85.3z"/></svg>
)=====";

const char TEREN_WEB_JSON[] PROGMEM = R"=====(
{
    "name": "CARTOONradio",
    "short_name": "CARTOONradio",
    "description": "CARTOONradio",
    "start_url": "/",
    "display": "standalone",
    "background_color": "#214960",
    "theme_color": "#214960",
    "icons": [ 
        {
            "src": "radio.svg",
            "sizes": "48x48 72x72 96x96 128x128 150x150 256x256 512x512 1024x1024",
            "type": "image/svg+xml",
            "purpose": "any"
        }
    
    ]
}
)=====";

const char STACJE_JSON[] PROGMEM = R"=====(
[
{"a":"0", "n": "TOK-FM","s":"http://pl-play.adtonos.com/tok-fm"},
{"a":"0", "n": "RNS",   "s":"http://stream.rcs.revma.com/ypqt40u0x1zuv"},
{"a":"0", "n": "357",   "s":"http://stream.rcs.revma.com/ye5kghkgcm0uv"},
{"a":"2", "n": "SwsJaz","s":"http://stream.srg-ssr.ch/m/rsj/mp3_128"},
{"a":"2", "n": "SwsCls","s":"http://stream.srg-ssr.ch/m/rsc_de/mp3_128"},
{"a":"2", "n": "ClsFM", "s":"http://media-the.musicradio.com/ClassicFM"},
{"a":"1", "n": "RMF_Cl","s":"http://www.rmfon.pl/n/rmfclassic.pls"},
{"a":"1", "n": "Dwojka","s":"http://mp3.polskieradio.pl:8952/;"},
{"a":"1", "n": "RockSe","s":"http://stream.open.fm/379"},
{"a":"1", "n": "101 Jz","s":"https://ais-sa2.cdnstream1.com/b22139_128mp3"},
{"a":"0", "n": "Szczec","s":"http://stream4.nadaje.com:11986/prs.aac.m3u"},
{"a":"0", "n": "Anty-R","s":"https://an.cdn.eurozet.pl/ant-waw.mp3"}
]
)=====";

struct sQQQ  {
  int8_t l;  
  int8_t m;
  int8_t h;
};

sQQQ qqq[5]={
    { 4, -4, 4},
    { 6, -6, 6},
    { 6,-12, 6},
    { 6,-18, 6},
    { 0,2,0}
};

/*
 
Szkic używa 1 279 366 bajtów (40%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 52 796 bajtów (16%) pamięci dynamicznej, pozostawiając 274884 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.
Szkic używa 1 279 114 bajtów (40%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 52 684 bajtów (16%) pamięci dynamicznej, pozostawiając 274996 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.
Szkic używa 1 279 226 bajtów (40%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 52 684 bajtów (16%) pamięci dynamicznej, pozostawiając 274996 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.
Szkic używa 1 279 278 bajtów (40%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 52 684 bajtów (16%) pamięci dynamicznej, pozostawiając 274996 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.




 */



/*struct stationsSTRUCT  {
  int  const  ampli;  
  char const *info;
  char const *stream;
};

stationsSTRUCT stacje [5]={
  {0, "TOK-FM",    "http://pl-play.adtonos.com/tok-fm"},
  {0, "RNS",       "http://stream.rcs.revma.com/ypqt40u0x1zuv"},
  {0, "357",       "http://stream.rcs.revma.com/ye5kghkgcm0uv"},
  {2, "Jazz",      "http://stream.srg-ssr.ch/m/rsj/aacp_96"},
  {2, "Classic",   "http://stream.srg-ssr.ch/m/rsc_de/aacp_96"}
};
*/
/*
String make_str(String str){
    if (str.length()>7) return str;
    String plus="";
    for(int i = 0; i < (7 - str.length()); i++)
        plus += ' ';  
    return plus+str;
}
*/
/*
String getSecondLine(String str){
    if (str.length()<17) return "";
    else return str.substring(16, str.length());
}*/

 






/*
void serialLoop(){
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
        if (odczyt == "-9") {
            Serial.println("-9x");
            audio.stopSong();
            es.volume(ES8388::ES_MAIN, 0);
            es.volume(ES8388::ES_OUT1, 0);
            es.volume(ES8388::ES_OUT2, 0);
              es.mute(ES8388::ES_OUT1, true);
              es.mute(ES8388::ES_OUT2, true);
              es.mute(ES8388::ES_MAIN, true);            
            
            delay(1500);
            ESP.restart();
        }
        if (odczytInt>-1 && odczytInt<3) {
          Serial.println(odczytInt);
          cur_station = odczytInt;
          //playCurStation();
          }
        //if (odczyt == "+") {cur_station++;playCurStation();}
        //if (odczyt == "-") {cur_station--;playCurStation();}
        //if (odczyt == "*") {cur_volume++;setCurVolume();}
        //if (odczyt == "/") {cur_volume--;setCurVolume();}
          Serial.print("odczyt=");Serial.println(odczyt);
          if (odczyt == "a") audio.connecttohost("http://stream.rcs.revma.com/ypqt40u0x1zuv");
          if (odczyt == "b") audio.connecttohost("http://stream.rcs.revma.com/ye5kghkgcm0uv");
          if (odczyt == "c") audio.connecttohost("http://pl-play.adtonos.com/tok-fm");
            // maxx 200 chars
            if (odczyt == "p") audio.connecttospeech("Dzień dobry. Tu radio z mchu i paproci.", "pl");
            if (odczyt == "r") audio.connecttospeech("Litwo! Ojczyzno moja! ty jesteś jak zdrowie: Ile cię trzeba cenić, ten tylko się dowie, Kto cię stracił. Dziś piękność twą w całej ozdobie Widzę i opisuję, bo tęsknię po tobie.", "pl");
            if (odczyt == "s") audio.connecttospeech("Dzień dobry. Litwo! Ojczyzno moja! ty jesteś jak zdrowie: Ile cię trzeba cenić, ten tylko się dowie, Kto cię stracił. Dziś piękność twą w całej ozdobie Widzę i opisuję, bo tęsknię po tobie.", "pl");
            if (odczyt == "t") audio.connecttospeech("Panno święta, co Jasnej bronisz Częstochowy I w Ostrej świecisz Bramie! Ty, co gród zamkowy Nowogródzki ochraniasz z jego wiernym ludem!", "pl");
          if (odczyt == "q1")  audio.setTone(0,0,0);
          if (odczyt == "q2")  audio.setTone(0,4,0);
          if (odczyt == "q3")  audio.setTone(6,0,6);
          if (odczyt == "q4")  audio.setTone(6,-3,6);
          if (odczyt == "q5")  audio.setTone(6,-6,6);
          if (odczyt == "q6")  audio.setTone(6,-9,6);
          if (odczyt == "q7")  audio.setTone(6,-12,6);
          if (odczyt == "q8")  audio.setTone(6,-24,6);
          if (odczyt == "q9")  audio.setTone(6,-40,6);
          
       
    }
    //----------------------------------------------------------------------------------------------------------------------
}  
*/

/*
Szkic używa 1 074 257 bajtów (34%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 50 808 bajtów (15%) pamięci dynamicznej, pozostawiając 276872 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

Szkic używa 1 074 249 bajtów (34%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 50 800 bajtów (15%) pamięci dynamicznej, pozostawiając 276880 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

***********
*
*UWAGA: biblioteka LiquidCrystal_I2C działa na architekturze(/architekturach) avr i może nie być kompatybilna z obecną płytką która działa na architekturze(/architekturach) esp32.
Szkic używa 1 262 990 bajtów (40%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 52 508 bajtów (16%) pamięci dynamicznej, pozostawiając 275172 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

Szkic używa 1 263 226 bajtów (40%) pamięci programu. Maksimum to 3145728 bajtów.
Zmienne globalne używają 52 508 bajtów (16%) pamięci dynamicznej, pozostawiając 275172 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.


const char RADIO_SVG[] PROGMEM = R"=====(
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512"><path fill="#056da1" d="M73.8 141.9c-15.2 6-25.8 21.8-25.8 39.5v256c0 23.5 18.5 42.7 41.6 42.7h332.8c23.1 0 41.6-19.2 41.6-42.7v-256c0-23.7-18.5-42.7-41.6-42.7H179l171.8-71.3L336.7 32 73.8 141.9zM160 438c-35.4 0-64-28.6-64-64s28.6-64 64-64 64 28.6 64 64-28.6 64-64 64zm256-171.3h-32v-46.2h-44.8v46.2H96v-85.3h320v85.3z"/></svg>
)=====";

const char TEREN_WEB_JSON[] PROGMEM = R"=====(
{
    "name": "CARTOONradio",
    "short_name": "CARTOONradio",
    "description": "CARTOONradio",
    "start_url": "/",
    "display": "standalone",
    "background_color": "#936",
    "theme_color": "#936",
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
 */

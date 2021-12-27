
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

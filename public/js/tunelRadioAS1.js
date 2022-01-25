const $=e=>document.querySelector(e);
const $$=e=>document.querySelectorAll(e);
let nr=0;
let streamsDEF = [
{"a":"TOK-FM", "n": "ST-01","s":"http://pl-play.adtonos.com/tok-fm"},
{"a":"RMF Top 30 PL", "n": "ST-02","s":"http://195.150.20.243:8000/rmf_top_5_pl"},
{"a":"RMF W PRACY", "n": "ST-03","s":"http://31.192.216.10:8000/rmf_w_pracy"},
{"a":"RMF BALLADY", "n": "ST-04","s":"http://31.192.216.7:8000/rmf_nostalgia"},
{"a":"RMF-FM", "n": "ST-05","s":"http://195.150.20.243:8000/rmf_fm"},
{"a":"RMF-24", "n": "ST-06","s":"http://195.150.20.7:8000/rmf_24"},
{"a":"RMF HOT NEW", "n": "ST-07","s":"http://217.74.72.11:8000/rmf_hot_new"},
{"a":"RMF HARD and HEAVY", "n": "ST-08","s":"http://217.74.72.11:8000/rmf_hard_heavy"},
{"a":"RMF 3 POP-ROCK", "n": "ST-09","s":"http://195.150.20.7:8000/rmf_3"},
{"a":"RADIO-ZET", "n": "ST-10","s":"http://zet-tun.cdn.eurozet.pl:8080"},
{"a":"ZLOTE-PRZEBOJE", "n": "ST-11","s":"https://pl2-play.adtonos.com/zote-przeboje"},
{"a":"RMF Blues", "n": "ST-12","s":"http://217.74.72.11:8000/rmf_blues"},
{"a":"RMF 25 Lat FM", "n": "ST-13","s":"http://195.150.20.9:8000/rmf_20lat"},
{"a":"RMF NIEZAPO MEL", "n": "ST-14","s":"http://195.150.20.242:8000/rmf_niezapomniane_melodie"},
{"a":"SZCZECIN", "n": "ST-15","s":"http://stream4.nadaje.com:11986/prs.aac"},
{"a":"Radio SUPERNOVA", "n": "ST-16","s":"https://ext03.ic.smcdn.pl/1380-1.aac"},
{"a":"RADIO PLUS", "n": "ST-17","s":"https://ext03.ic.smcdn.pl/4000-1.mp3"},
{"a":"RADIO POGODA", "n": "ST-18","s":"https://pl-play.adtonos.com/radio-pogoda"},
{"a":"Radio Nowy Świat", "n": "ST-19","s":"http://stream.rcs.revma.com/ypqt40u0x1zuv"},
{"a":"Anty-Radio", "n": "ST-20","s":"http://www.emsoft.ct8.pl/inne/anty.m3u"},
{"a":"357", "n": "ST-21","s":"http://stream.rcs.revma.com/ye5kghkgcm0uv"},
];

let urlDEF = "/";  
let urlObj = new URL(window.location.href);
urlDEF = urlObj.searchParams.get("url") || urlDEF;
console.log("urlDEF=",urlDEF);
localStorage.setItem("urlDEF", urlDEF); 
let url = urlDEF;
  
const removeActive=(dom)=>{
  $$(dom).forEach((e)=>e.classList.remove("active"));
}

const radioSlij=(el)=>{
    removeActive("div.radia button")
    el.target.classList.add("active");
    let data = el.target.dataset;
  //console.log(data);
    $("#name").textContent = data.n;
    nr = parseInt(data.st)+1;
    $("#numer").textContent = nr
    $("#stream").textContent = data.stream;
    radioFETCH("x="+data.stream);
    radioFETCH("n="+data.n);
    radioFETCH("a="+data.a);
    radioFETCH("st="+data.st);
    refreshInfo(5);
}

const refreshInfo=(sek=5)=> {
   setTimeout(()=>{radioFETCH("");},1000*sek);
}
const opisInfoRadio=(tx)=>{
  let arr = tx.split("!");
  console.log(arr);
   $("#vol").textContent = arr[0];
   $("#rsid").textContent = arr[1];
   $("#name").textContent = arr[2];
   $("#stream").textContent = arr[3];
   $("#info").textContent = arr[4];
   //removeActive("div.radia button"); 
}
const checkForError = response => {
  if (!response.ok) throw Error(response.statusText);
  return response.text();
};
const radioFETCH=(param) =>{
    let u = url+"radio?"+param; 
    fetch(u)
    .then(checkForError)
    .then(tx => {
       opisInfoRadio(tx);  
    })
    .catch(e => {console.log(e)})
  }
document.addEventListener("DOMContentLoaded",function(){
    let html = "";
    streamsDEF.forEach((s,i)=>{
      html += '<button data-st="'+i+'" data-n="'+s.n+'" data-a="'+s.a+'" data-stream="'+s.s+'" class="info">'+s.n+'</button>';
    });
    document.querySelector("div.radia").innerHTML += html;
    document.querySelectorAll("div.radia button").forEach((e)=>e.addEventListener('click', radioSlij, false));    
    refreshInfo(1);
    setInterval(()=>{radioFETCH("");},1000);
});
const StationChange=(param) =>{	
  if (param == "m") {nr--;}
  if (param == "p") {nr++;} 
  removeActive("div.radia button");
  if (nr > streamsDEF.length){nr = 1;}
  if (nr <= 0){nr = streamsDEF.length;}
  radioFETCH("s="+param)
  $$("div.radia button")[nr-1].classList.add("active");
  $("#name").textContent = streamsDEF[nr-1].a;
  $("#stream").textContent = streamsDEF[nr-1].s;
  $("#numer").textContent = nr;
  refreshInfo(2);
}

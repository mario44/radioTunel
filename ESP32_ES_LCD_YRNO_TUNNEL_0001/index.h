const char PAGE_HTML[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="pl">
<head>
<meta charset="utf-8">
<title>@CARTOON</title>
<link rel="manifest" href="./teren.web.json">
<meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no">
<meta name="HandheldFriendly" content="true">
<meta name="mobile-web-app-capable" content="yes"> 
<meta name="theme-color" content="#214960">
<link rel="shortcut icon" type="image/svg+xml" size="any" href="radio.svg"> 
<link rel="icon" type="image/svg+xml" href="radio.svg">  
<style>
.bbb {background-color:#056da1;}
*,html{color:#eee;}
body{background-color:#214960;}
body{padding:0;margin:5px;background-blend-mode:color-dodge;background-repeat:no-repeat;background-position:center 45vh;background-size:50vh}
*,html{font-size:14pt;font-family:Arial,Helvetica,sans-serif;text-shadow: 2px 2px 2px #888;}
.wrap {z-index:2;margin:auto;padding:0.5rem;max-width:600px; }
.grid{display:grid;grid-gap:.25em; margin-top:0.2em;}
.col {width:100%;text-align:center;margin:.25em auto;}
.col{grid-template-columns:repeat(auto-fit,minmax(50px,1fr));}
.col-sm{grid-template-columns:repeat(auto-fit,minmax(40px,1fr));}
.col-md{grid-template-columns:repeat(auto-fit,minmax(80px,1fr));}
.col-lg{grid-template-columns:repeat(auto-fit,minmax(90px,1fr));}
.prima button {background-color:#f5be47;}  
h3{margin:.3em 0}
h3,#info {text-shadow: none;}
#czas,#info{font-size:.8rem;font-family:monospace}
#info{min-height:5em}
button{background:#df513b;color:white;border:none;box-shadow:1px 1px 1px 0px #666;border-radius:0.75em;padding: 0.5em 0.1em;margin: 0.2em 0;}
.active,button:active,button:visited{background-color:#4564a4!important;color:white!important;}
.small button{font-size:.85rem}
.eq button{background:#e7e3c1;color:#0f2c4b}
.prima button{color:black}
img,svg{display:grid;align-content:center;justify-content:space-around;max-width:10em;margin:auto}
div#app span{width:3em;height:1.3em;background:#e7e3c1;padding:.3em;margin:auto;border-radius:.5em;color: #222;} 
input#slij,input#nazwa{color:black;text-shadow:none;font-size:0.85rem;padding: 0.2em 0;}
input#slij {width:97%;}
input#nazwa {width:76%;}
button#btn-slij {width:19%;background:#4169e1}
.stu button {background:#4169e1;}
button.red {background:#df513b;}
button.small {background: #4564a4;min-width: 4em;padding: 0.3em;}
div.gr {display:inline-block;margin-right:1em;}
div.gr button {
    font-size: 0.9rem;
    padding: 0.33em;
    background: #369;
    max-width: 88%;
    text-align: left;
    white-space: nowrap;
    overflow: hidden;
}

.hidden {display:none;}

div.gr button:first-child{background:darkcyan;}

@media (orientation: landscape) {body {overflow:auto;}}
</style>
<script>
const _$=e=>document.querySelector(e);
const _$$=e=>document.querySelectorAll(e);
const radio="radio";
let nr=0;
let url = "/";

let lastSTA = 0;
let locale = {};
locale[radio] = {};

const ref=(t=3)=>{setTimeout(()=>{sn()},t*1000);}
const unID = () => [...new Array(8)].map(() => String.fromCharCode(97 + Math.random()*26)).join('')

document.addEventListener("DOMContentLoaded",()=>{
  let urlObj = new URL(window.location.href);
  url = urlObj.searchParams.get("url") || url;
  console.log(url);
  localStorage.setItem("url", url);
  ref(1);
  setInterval(()=>{sn()},15000);
  fetch(url+"stacje.json")
  .then(j => {return j.json()})
  .then(s => {
    stacje(s);
  }).catch(e => {console.log(e)})
  if (localStorage.getItem(radio)){
      locale[radio] = JSON.parse(localStorage.getItem(radio))[radio];
      opiszLocale();
  }
});

let opiszLocale=()=>{
_$("#plus").innerHTML ="";
      let i=0;
      for(let k in locale[radio]){
        console.log(k,locale[radio][k]);
        wpisz(i++,locale[radio][k],k);
      }
}

let stacje=(st)=>{
  let h="";
  st.forEach((s,i)=>{
    if (s.n) {h+='<button id="sta'+i+'" data-n="'+i+'" data-s="'+s.s+'" data-a="'+s.a+'" onClick="sta(this)">'+s.n+'</button>';}
  });
  _$("#stacje").innerHTML=h;
}

let sn=(p="radio?n=0")=>{
fetch(url+p)
.then(r => {return r.text()})
.then(t => {
  //console.log(t);
  opisz(t); 
  setTimeout(()=>{opisz(t)},3000);   
}).catch(e => {console.log(e)})  
}

const btnActive=(btnNR,cl="st")=>{
  _$$("div."+cl+" button").forEach((b)=>{if (b) b.classList.remove("active")});
  if(btnNR>=0 && _$("#st"+btnNR)) _$("#"+cl+btnNR).classList.add("active");
}
const opisz=(o)=>{
  let a = o.split("!");
  
  let lastSTA = parseInt(a[0]);
  //let lastEQ  = a.pop();
  btnActive(lastSTA);
  //btnActive(lastEQ,"eq");
  _$("#sta").textContent = lastSTA+1;
  _$("#vol").textContent = a[1];
  _$("#info").innerHTML  = "wifi:"+a[2]+"dB";
  //console.log(a)
  //console.log(a[4])
  if(a[3]) _$("#info").innerHTML += "<br />"+a[3];
  if(a[4]) _$("#info").innerHTML += "<br />"+a[4];
  if(a[5]) _$("#info").innerHTML += "<br />"+a[5];
  if(a[6]) _$("#info").innerHTML += "<br />"+a[6];
  if(a[7]) _$("#info").innerHTML += " "+a[7];
}


let sta=(ten)=>{
  console.log(ten.dataset.n,ten.dataset.a,ten.dataset.s);
  let lastStream = ten.dataset.s;
  _$("#slij").value=lastStream;
  _$("#nazwa").value=ten.textContent;
  localStorage.setItem("lastStream", lastStream);
  sn("radio?x="+lastStream);
  nr = ten.dataset.n;
  //sn("radio?y="+ten.dataset.a);
  sn("radio?z="+nr);
  ref();
  ref(5);
}

let wpisz=(nr,x,nazwa)=>{
    _$("#plus").innerHTML += '<div class="gr"><button onClick="del(this)">&nbsp;&#x2715&nbsp;</button>&nbsp;<button data-n="'+nr+'" data-s="'+x+'" data-a="0" onclick="sta(this)">'+nazwa+'</button></div>';
}

let slij=()=>{
  let x=_$("#slij").value;
  if (x) {
    sn("radio?x="+x);
    //let xx = x.replace(/^http[s]?:\/\/(www\.)?(.*)?\/?(.)*/,"");
    let xx = x.replace(/^http[s]?:\/\/(www\.)?/,"");
    let nazwa = _$("#nazwa").value ? _$("#nazwa").value : xx;
    ZapiszLocale(radio,nazwa,x);
    wpisz(nr,x,nazwa);
    nr++;
    ref();
    ref(5);
  }
}
let del=(t)=>{
  let d = t.nextElementSibling.textContent;
  delete locale[radio][d]
  opiszLocale();
  localStorage.setItem(radio, JSON.stringify(locale));
}
let ZapiszLocale=(root,key,val)=>{
    if(root) locale[root][key]=val;
    localStorage.setItem(radio, JSON.stringify(locale));
    
}
let show=(co,ten)=>{
  _$("#numery").classList.add("hidden");
  _$("#streams").classList.add("hidden");
  _$("#"+co).classList.remove("hidden");
  _$$(".red").forEach((e)=>{e.classList.remove("active")});
   ten.classList.add("active");   
}

let cn=(param)=>{
  if (confirm("Rily!") == true) sn(param);
}

let klik=(t)=>{
  let all = t.parentNode.querySelectorAll("button");
  all.forEach((o)=>o.classList.remove("active"));
  t.classList.add("active");
}
</script>
</head>
<body>

<div class="wrap">
  <div class="col">
    <h3>@radio Salon</h3>
    <div id="info"></div>
  </div>
  <div class="col" id="app">
      <div class="grid col col-lg prima">
        <button onClick='sn("radio?v=m")'>Vol-</button>
        <span id="vol"></span>
        <button onClick='sn("radio?v=p")'>Vol+</button>
      </div>
      <div class="grid col col-lg">
        <button onClick='sn("radio?s=m")'>Sta-</button>
        <span id="sta"></span>
        <button onClick='sn("radio?s=p")'>Sta+</button>
      </div>   
  </div>
  <div id="numery" class="grid col col-md st">
    <button onClick='sn("radio?t=0")' id="st0">TOK-FM</button>
    <button onClick='sn("radio?t=1")' id="st1">RNŚ</button>
    <button onClick='sn("radio?t=2")' id="st2">357</button>
    <button onClick='sn("radio?t=3")' id="st3">Sw-Jzz</button>
    <button onClick='sn("radio?t=4")' id="st4">Sw-Cla</button>
    <button onClick='sn("radio?t=5")' id="st5">RMF-Cl</button>
    <button onClick='sn("radio?t=6")' id="st6">Cl-FM</button>
    <button onClick='sn("radio?t=7")' id="st7">PR2</button>
    
    <button onClick='sn("radio?t=8")'  id="st8">Niezap</button>
    <button onClick='sn("radio?t=9")'  id="st9">RockS</button>
    <button onClick='sn("radio?t=10")' id="st10">101-Jz</button>
    <button onClick='sn("radio?t=11")' id="st11">Szczec</button>
  </div>

  <div id="streams" class="hidden">
      <div>
        <input id="slij" placeholder="Stream URL"  />
        <input id="nazwa" placeholder="Nazwa" /> <button onClick="slij()" id="btn-slij">Ślij</button><br />
      </div>
      <div class="" id="plus"></div>
      <table id="local"></table>

      <div class="grid col col-md st stu" id="stacje"></div>
  </div>
  <div class="grid col prima small">
    <button onClick='sn("radio?n=0")' class="btn ex">Info</button>
    <button onClick='sn("radio?start=0")' class="btn ex">Mute</button>   
    <button onClick='window.location.reload(true);' class="btn ex">Reload</button>    
    <button onClick='sn("radio?v=z")' class="btn ex">Zapisz</button>    
    <button onClick='show("numery",this)' class="btn ex red active">Stacje</button>    
  </div>
  
    <div class="grid col prima small">
      <button onclick='cn("radio?r=0")'>Reboot</button>
      <button onclick='sn("radio?m=1")'>Music</button>
      <button onClick='sn("radio?r=1")'>Replay</button>
      <button onclick='cn("radio?r=2")'>Sleep</button>
      <button class="red" onclick='show("streams",this)'>Stream</button>
    </div>
  
  
<hr /> 

  <div class="grid col small eq">
    <button onClick='sn("radio?q=0");klik(this);' id="eq0">Mowa</button>
    <button onClick='sn("radio?q=1");klik(this);' id="eq1">Muzyka</button>
    <button onClick='sn("radio?q=2");klik(this);' id="eq2">Jazz</button>
    <button onClick='sn("radio?q=3");klik(this);' id="eq3">Classic</button>
    <button onClick='sn("radio?q=4");klik(this);' id="eq4">Flat</button>
  </div>

</div>







<script src="https://cdnjs.cloudflare.com/ajax/libs/noUiSlider/15.5.0/nouislider.min.js" integrity="sha512-ZKqmaRVpwWCw7S7mEjC89jDdWRD/oMS0mlfH96mO0u3wrPYoN+lXmqvyptH4P9mY6zkoPTSy5U2SwKVXRY5tYQ==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>

<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/noUiSlider/15.5.0/nouislider.css" integrity="sha512-MKxcSu/LDtbIYHBNAWUQwfB3iVoG9xeMCm32QV5hZ/9lFaQZJVaXfz9aFa0IZExWzCpm7OWvp9zq9gVip/nLMg==" crossorigin="anonymous" referrerpolicy="no-referrer" />

<style>
  div.results{margin: 1em 0;}
  div.values{
    height: 1.5em;
    display: flex;
    justify-content: space-evenly;
  }
  div.values input{color:black; width:4em;text-align:center; padding:0.3em 0;border-radius:0.5em;}
  div#hslider{
    display: flex;
    justify-content: space-evenly;
    align-content: space-between;
    height: 180px;
  }
  </style>
<br />

<div class="wrap">
<button onClick="toggleEQ()" class="small" style="width:4em;"> Eq </button>
</div>
  
<div id="eqqq" class="hidden" style="max-width: 600px;margin: 1.5em auto;">
          
          <div class="results">
             <div class="values"><input id="qrq0" value="0" /> <input id="qrq1" value="0" /><input id="qrq2" value="0" /></div>
             <div class="values"><span>Bass</span> <span>Middle</span> <span>Treble</span></div>
             <div class="values"><input id="frq0"> <input id="frq1"><input id="frq2"></div>
             <div class="values"><input id="qval"></div>
          </div>
 
    <div class="hsliders">
        <div id="slider"></div>
    </div>
    <br /><br />
    <div id="hslider">
        <div class="sliders"></div> 
        <div class="sliders"></div> 
        <div class="sliders"></div> 
    </div>
   <br />
    <div id="qslider"></div>
 
</div>

  
<script>
let toggleEQ=()=>{
  document.getElementById("eqqq").classList.toggle("hidden");
}
//https://jsfiddle.net/5hzsm844/  
let toLoga = (value)=>{
  return toLog(value,50,10000)
}  
let toLog = (value, min, max)=>{
    let exp = (value-min) / (max-min);
  return min * Math.pow(max/min, exp);
}  
 
let slider = document.getElementById('slider');

let slid1 = noUiSlider.create(slider, {
    start: [3075,6095,8698],
    connect: true,
    step :5,
    range: {
        'min': 50,
        'max': 10000
    }
});
 
    slid1.on('change', function () {
      sendtoserver()
    })
 
slid1.on('update', function (values, handle) {
  //console.log(values, handle);
    let frq0 = parseInt(toLoga(values[0]))
    let frq1 = parseInt(toLoga(values[1]))
    let frq2 = parseInt(toLoga(values[2]))
      document.getElementById("frq0").value = frq0;
      document.getElementById("frq1").value = frq1;
      document.getElementById("frq2").value = frq2;
})
 

let qslider = document.getElementById('qslider');
let sliders = document.getElementsByClassName('sliders');
let gains = [0, 0, 0];

[].slice.call(sliders).forEach(function (slider, index) {
    noUiSlider.create(slider, {
        start: 0,
        connect: [true, false],
        orientation: "vertical",
        range: {
            'min': -6,
            'max': 40,
        }
    });
    slider.noUiSlider.on('change', function () {
      sendtoserver()
    })

    slider.noUiSlider.on('update', function () {
        gains[index] = slider.noUiSlider.get();
        let val = -parseInt(gains[index]);
        document.getElementById("qrq"+index).value = val;
        //console.log(index,val,gains[index]);
    });
});  

    // Q slider
    noUiSlider.create(qslider, {
        start: [250],
        step:10,
        connect: true,
        range: {
            'min': 100,
            'max': 2000
        }
    });  
    qslider.noUiSlider.on('update', function (qVal) {
        let q = qVal[0];
        document.getElementById("qval").value = parseInt(q)/100;
    })
    qslider.noUiSlider.on('change', function () {
      sendtoserver()
    }) 
  
  
let sendtoserver=()=>{
  let arr=[];
  document.querySelectorAll("div.values input").forEach((v)=>{
    arr.push(v.value);
  });
  let out = (arr.join(";"));
  console.log(out);
  sn("radio?qq="+out);
}
  
</script>            




</body>
</html>


)=====";

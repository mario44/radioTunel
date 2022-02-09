<script>
let city = "Szczecin-Pomorzany";
//https://www.yr.no/api/v0/locations/Search?lat=53.407072&lon=14.525196&accuracy=30&language=Poland
let dataType = "forecast"  //"celestialevents","forecast","mapfeature","currenthour","observations"    
let YRNO_API = "https://www.yr.no/api/v0/locations/2-11748765/"+dataType;

const _getYRNO=(url)=>{  
  fetch(url)
    .then(function(response) {
          if (!response.ok) {throw Error(response.statusText);}
          return response.json();
    })
    .then(obj => {
        zapiszYRNO(obj);
    })
    .catch(e => {console.log(e)})
};

const zapiszYRNO=(obj)=>{
  console.log(obj);
  let dayIntervals = obj.dayIntervals;
  //console.log(dayIntervals);
  let day0 = dayIntervals[0];
  //console.log(day0);
  let precipitation = day0.precipitation.value; //opady atmosferyczne
  //console.log(precipitation);
  let temperature = day0.temperature;
  //console.log(temperature);
  let temp = temperature.value
  let temp_min = temperature.min
  let temp_max = temperature.max
  //console.log(temp, temp_min, temp_max);
  
  let update = obj.update;
  console.log(update);
  let timeNow   = (new Date()).getTime();
  let timeFrom  = (new Date(update)).getTime();
  let timeCache = parseInt(localStorage.getItem("yrnoTIME") || 0); 
  let timeDelta =  timeNow - timeCache;
  let minuteDelta = timeDelta / 60000;
  console.log(timeNow,timeFrom,timeCache,timeDelta,minuteDelta);
  console.log("minuteDelta=",minuteDelta);
  if (minuteDelta < 30) return;
  let data = obj;
  let json = JSON.stringify(obj);
  console.log(json);
      localStorage.setItem("yrnoCITY", city);
      localStorage.setItem("yrnoTIME", timeNow);
      localStorage.setItem("yrnoDATA", json);
      localStorage.setItem("yrnoTYPE", dataType);     
}

const getYRNO2Cache=()=>{
  _getYRNO(YRNO_API);
}
_getYRNO(YRNO_API);

  </script>

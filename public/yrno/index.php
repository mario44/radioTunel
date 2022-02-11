<?php
$version="0";
if (isset($_GET["v"])) $version = $_GET["v"];
if (isset($_GET["help"])) $version = "1";
header('Cache-Control: no-cache, no-store, must-revalidate'); // HTTP 1.1.
header('Pragma: no-cache'); // HTTP 1.0.
header('Expires: 0'); // Proxies.
header('Access-Control-Allow-Origin: *');
//header('Content-Type: application/json');
//header('Content-Type: plain/text');



function get_web_page( $url )    {
    $user_agent='Mozilla/5.0 (Windows NT 6.1; rv:8.0) Gecko/20100101 Firefox/8.0';
    $options = array(
        CURLOPT_CUSTOMREQUEST  =>"GET",        //set request type post or get
        CURLOPT_POST           =>false,        //set to GET
        CURLOPT_USERAGENT      => $user_agent, //set user agent
        CURLOPT_COOKIEFILE     =>"cookie.txt", //set cookie file
        CURLOPT_COOKIEJAR      =>"cookie.txt", //set cookie jar
        CURLOPT_RETURNTRANSFER => true,     // return web page
        CURLOPT_HEADER         => false,    // don't return headers
        //CURLOPT_FOLLOWLOCATION => true,     // follow redirects
        CURLOPT_ENCODING       => "",       // handle all encodings
        CURLOPT_AUTOREFERER    => true,     // set referer on redirect
        CURLOPT_CONNECTTIMEOUT => 120,      // timeout on connect
        CURLOPT_TIMEOUT        => 120,      // timeout on response
        CURLOPT_MAXREDIRS      => 10,       // stop after 10 redirects
    );

    $ch      = curl_init( $url );
    curl_setopt_array( $ch, $options );
    $content = curl_exec( $ch );
    $err     = curl_errno( $ch );
    $errmsg  = curl_error( $ch );
    $header  = curl_getinfo( $ch );
    curl_close( $ch );
    $header['errno']   = $err;
    $header['errmsg']  = $errmsg;
    $header['content'] = $content;
    return $content;
}


function __pre($var,$info=""){
  //print("<pre>"); 
  print("---------------\n".$info."\n"); 
  print_r($var); 
  print("================\n"); 
  //print("</pre>");
}

function pl($s){return strtr($s, array('ę'=>'e','ą'=>'a','ś'=>'s','ż'=>'z','ź'=>'z','ć'=>'c','ó'=>'o','ł'=>'l','ń'=>'n','Ę'=>'E','Ą'=>'A','Ś'=>'S','Ż'=>'Z','Ź'=>'Z','Ć'=>'C','Ó'=>'O','Ł'=>'L','Ń'=>'N'));}

//https://api.met.no/weatherapi/weathericon/2.0/documentation

function trrrr($s){
  $trans = array(
    "rain"=>"Deszcz",
    "sleet"=>"Slota",
    "lightsleet"=>"Slota",
    "heavysleet"=>"Deszcz",
    "cloudy"=>"Chmury",
    "partlycloudy_night"=>"Chmury",
    "heavyrain"=>"Ulewa",
    "sleet"=>"Slota",
    "sleet"=>"Slota",
    
 );
  return strtr($s, $trans);
}

$transTABjson = file_get_contents("./pl/yrno.en.pl.json");
$transTAB = json_decode($transTABjson);
  //__pre($transTAB);

function tr($s){
  global $transTAB;
  $arr = explode("_",$s);
  $s = $arr[0];
  //echo $s."=".$transTAB->{$s}->pl;
  return $transTAB->{$s}->pl;
}

// Apparent temperature calculation
// accepts temperature [C], humidity [%], wind speed [m/s]
// returns apparent temperature [C]
function apparent($apparentT,$apparentH,$apparentW){
  $e = ($apparentH/100)*6.105*pow(2.71828, ((17.27*$apparentT)/(237.7+$apparentT)));
  $calcA = round(($apparentT + 0.33*$e-0.7*$apparentW-4),1);
  return $calcA;
}





function pad5($t){return str_pad(($t), 5, " ", STR_PAD_LEFT);}


function parseV0($val,$v=0){
  $dnitygodnia = array("Niedziela","Poniedz.","Wtorek","Sroda","Czwartek","Piatek","Sobota");

  $arr = array();
  $time  = date("Y-m-d H:i",strtotime($val->time));
  $timeD = date("Y-m-d",strtotime($val->time));
  $timeH = date("H:i",strtotime($val->time));
  $dow   = $dnitygodnia[date("w",strtotime($val->time))];
  $instant = $val->data->instant->details;
  $next_1  = $val->data->next_1_hours;
  $next_6  = $val->data->next_6_hours;
  $next_12 = $val->data->next_12_hours;
  $details = $instant->details;
  $outxt = "";
  $znak="";
  //echo ($instant->air_temperature).PHP_EOL;
  //echo ($instant->air_temperature>0).PHP_EOL;
  if ($instant->air_temperature>0) $znak = "+";
   array_push($arr,$dow);  
  array_push($arr,pad5($znak.$instant->air_temperature));//   "°C"  ℃
  array_push($arr,pad5(round($instant->air_pressure_at_sea_level)));
  array_push($arr,pad5($instant->wind_speed));
  array_push($arr,pad5(round($instant->relative_humidity)));
    
    array_push($arr,pad5((isset($next_1->details->precipitation_amount))  ? ($next_1->details->precipitation_amount)  : "0.0"));
    array_push($arr,pad5((isset($next_6->details->precipitation_amount))  ? ($next_6->details->precipitation_amount)  : "0.0"));
    array_push($arr,pad5((isset($next_12->details->precipitation_amount)) ? ($next_12->details->precipitation_amount) : "0.0"));
    
    array_push($arr,tr((isset($next_1->summary->symbol_code)) ? ($next_1->summary->symbol_code) : "???"));
    array_push($arr,tr((isset($next_6->summary->symbol_code)) ? ($next_6->summary->symbol_code) : "???"));
    array_push($arr,tr((isset($next_12->summary->symbol_code)) ? ($next_12->summary->symbol_code) : "???"));
  
    if ($next_1->summary->symbol_code)           $outxt .= tr($next_1->summary->symbol_code).PHP_EOL;
    if ($next_6->summary->symbol_code)           $outxt .= tr($next_6->summary->symbol_code).PHP_EOL;
    if ($next_12->summary->symbol_code)          $outxt .= tr($next_12->summary->symbol_code).PHP_EOL;

     $humidity = $instant->relative_humidity;
     $temp     = $instant->air_temperature;
     $wind = $instant->wind_speed;
      //$dewpoint = round(((pow(($humidity/100), 0.125))*(112+0.9*$temp)+(0.1*$temp)-112),1);
     $dewp = round(((pow(($humidity/100), 0.125))*(112+0.9*$temp)+(0.1*$temp)-112),1);
     $feel = apparent($temp,$humidity,$wind);
      array_push($arr,pad5($feel));
      array_push($arr,pad5($dewp));
    array_push($arr,$timeH);
    array_push($arr,$timeD);
    
    array_push($arr,time());

    $przed ="";
    $po="";
    if ($v==1) {
          $helpy = array(
          "Dzień tygodnia ",
          "[°C]  aktualna temperatura ",
          "[hPa] cisnienie ",
          "[m/s] wiatr ",
          "[%]   wilgotnosc ",
          "[mm] deszcz za 1h",
          "[mm] deszcz za 6h",
          "[mm] deszcz za 12h",
          "opis za 1h",
          "opis za 6h",
          "opis za 12h ",
          "[°C] temp. odczuwalna",
          "[°C] temp. punktu rosy",
          "godzina prognozy",
          "dzien ",
          "timestamp"
          );
          foreach($helpy as $k=>$v){
             // echo ("$k=$v<br>");
              $kk = $k+0;
              $arr[$k] .= " = [".$kk."] ".$v;
          }
          $przed = "<meta name='mobile-web-app-capable' content='yes'>\n\n<pre>"; 
          $po    = "</pre>";
    }
  
  return $przed.implode(PHP_EOL,$arr).$po;
}


// dom = 
//$lat = "53.37876961473425";
//$lon = "14.665703207519565";
$lat = "53.37876961";
$lon = "14.66570321";
//$url = "https://api.met.no/weatherapi/locationforecast/2.0/compact?lat=53.378773&lon=14.665842&altitude=25";
//$url = "https://api.met.no/weatherapi/locationforecast/2.0/complete?lat=53.378773&lon=14.665842&altitude=25";

//$url = "https://api.met.no/weatherapi/locationforecast/2.0/compact?lat=$lat&lon=$lon&altitude=25";
$url = "https://www.yr.no/api/v0/locations/2-11748765/forecast";
$YRNOjson = get_web_page($url);
$YRNOobj  = json_decode($YRNOjson);
//print("<pre>"); print_r($YRNOobj); print("</pre>");

//$pogoda = $YRNOobj->properties->timeseries;
$pogoda = $YRNOobj->dayIntervals;

//$txt = parseV0($pogoda[0],$version);
$txt = $pogoda[0];
//echo $version.PHP_EOL;
//echo $url.PHP_EOL;
echo $txt;
/*
foreach($pogoda as $key=>$val){
  parse($val); 
  if ($key>2) break;
}
*/

/*
(
    [time] => 2021-11-29T09:00:00Z
    [data] => stdClass Object
        (
            [instant] => stdClass Object
                (
                    [details] => stdClass Object
                        (
                            [air_pressure_at_sea_level] => 1000.3
                            [air_temperature] => 0.5
                            [cloud_area_fraction] => 97.6
                            [relative_humidity] => 98.4
                            [wind_from_direction] => 271.9
                            [wind_speed] => 3
                        )
                )
            [next_12_hours] => stdClass Object
                (
                    [summary] => stdClass Object
                        (
                            [symbol_code] => lightrain
                        )
                )
            [next_1_hours] => stdClass Object
                (
                    [summary] => stdClass Object
                        (
                            [symbol_code] => fog
                        )
                    [details] => stdClass Object
                        (
                            [precipitation_amount] => 0
                        )
                )
            [next_6_hours] => stdClass Object
                (
                    [summary] => stdClass Object
                        (
                            [symbol_code] => rain
                        )
                    [details] => stdClass Object
                        (
                            [precipitation_amount] => 1.9
                        )
                )
        )
)
*/

?>

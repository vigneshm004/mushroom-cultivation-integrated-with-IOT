// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "DFRobot_SHT20.h"
DFRobot_SHT20 sht20;
#include <BH1750.h>
BH1750 lightMeter(0x23);
// Replace with your network credentials
const char* ssid = "vickym";
const char* password = "123456789";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
String readDHTTemperature() {
  float t = sht20.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}
//
String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = sht20.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}
String readDHTlight() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float l = lightMeter.readLightLevel();
  if (isnan(l)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(l);
    return String(l);
  }
}
String readDHTppm() {
  const int Sensor_input = 4;
  int g = analogRead(Sensor_input);
  if (isnan(g)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(g);
    return String(g);
  }
}
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>Mushroom Cultivation</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link
      rel="stylesheet"
      href="https://use.fontawesome.com/releases/v5.7.2/css/all.css"
      integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr"
      crossorigin="anonymous"
    />
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        display: flex;
       
      }
      body{
        background-color: rgb(213, 213, 184);
      }
      h2 {
      position: relative;
        text-align: center;
        font-size: 3rem;
        color: red;
        text-shadow: 5px 5px 5px black;
        bottom: 30px;
      }
      p {
        font-size: 3rem;
      }
      #l1{
        display: flex;        
         gap: 10px;
         font-size: 20px;
         border-bottom: 1px solid black;     
         background-color:rgb(194, 194, 155); 
         height: 50px;
         justify-content: center;
         align-items: center;
      }
      #temp1{
        display: flex;
        align-items: center;
        margin-top:15px ;
      }
        #l2{
        display: flex;        
         gap: 10px;
         font-size: 20px;
         border-bottom: 1px solid black;   
          background-color:rgb(194, 194, 155); 
            justify-content: center;
         align-items: center;      
           height: 50px;
      }
        #l3{
        display: flex;        
         gap: 10px;
         font-size: 20px;
         border-bottom: 1px solid black;  
          background-color:rgb(194, 194, 155);   
            justify-content: center;
         align-items: center;   
           height: 50px;  
      }
        #l4{
        display: flex;        
         gap: 10px;
         font-size: 20px;
         border-bottom: 1px solid black;  
         background-color:rgb(194, 194, 155); 
        justify-content: center;
         align-items: center;  
           height: 50px;     
           padding-left: 15px;
      }
      #list{
        position: relative;
        top: 0px;
      }
      .units {
        font-size: 1.2rem;
      }
      .dht-labels-temp {
       
        border: 10cap;
        padding-bottom: 15px;
      }
      .dht-labels-hum {       
  
        padding: 5px;
        margin-right: 20px;
             
       
      }
      .dht-labels-light {
       
      
        padding: 5px;
        margin-right: 55px;          
          }
          .dht-labels-ppm {
       
      
        padding: 5px;
        margin-right: 55px;          
          }

      h3 {
              
         
         text-align: center;
         padding: 20px;
         position: relative;
         top:100px;
          font-style:italic ;
          font-size: 30px;
          font-family:monospace;
          color: #226f81;
      }
      #datebox{
        border-bottom: 1px solid black;
        width: 130px;
        
        height: 30px;
        display: flex;
        align-items: center;
         font-weight: 200;
         justify-content: start;

      }
       #timebox{
       
        width: 130px;
        font-weight: 200px;
        
         height: 30px;
          display: flex;
        align-items: center;
         justify-content: start;
        
      }
      #datetime{
        position: relative;
       display: grid;   
       
       justify-content: right;
      }
    </style>
  </head>
  <body>
    <div id="datetime">
      <div id="datebox">Date:<span id="date">10.10.2023</span>
      </div>
       <div id="timebox">Time:<span id="time">10:45</span>
      </div>
    </div>
    <h2>MUSHROOM CULTIVATION</h2>
      <div id="list">
      <div id="l1">
      <i class="fas fa-thermometer-half" style="color: #059e8a"></i>
      <span class="dht-labels-temp" id="temp1">Temperature</span>
      <span id="temperature">10</span>
      <sup class="units">&deg;C</sup>
    </div>
    <div id="l2">
      <i class="fas fa-tint" style="color: #00add6"></i>
      <span class="dht-labels-hum">Humidity</span>
      <span id="humidity">10</span>
      <sup class="units">&percnt;</sup>
    </div>
    <div id="l3">
       
    <i class="fas fa-lightbulb" style="color: #cf8181"></i>
    <span class="dht-labels-light">Light</span>
    <span id="light">10</span>
    <sup class="units">lx</sup>
    </div>
    <div id="l4">
    <i class="fa fa-industry" style="color: #854532"></i>
    <span class="dht-labels-ppm">Co<sub>2</sub></span>
    <span id="ppm">10</span>
    <sup class="units">ppm</sup>  
    </div>
    </div>
    <h3>Team ROLEX</h3>
  </body>

  <script>
  //date and time
  function datetime(){
    const today = new Date();
const yyyy = today.getFullYear();
let mm = today.getMonth() + 1; // Months start at 0!
let dd = today.getDate();

if (dd < 10) dd = '0' + dd;
if (mm < 10) mm = '0' + mm;

const formattedToday = dd + '/' + mm + '/' + yyyy;
document.getElementById("date").innerHTML=formattedToday;
let zone=today.getHours()<12?" AM":" PM";
let hr=today.getHours()<10?"0"+today.getHours():today.getHours();
document.getElementById("time").innerHTML=`${hr}:${today.getMinutes()}:${today.getSeconds()}${zone}`
  }
   setInterval(datetime,1000)
    document.getElementById("date").innerHTML=
    // temp
    setInterval(function () {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("temperature").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/temperature", true);
      xhttp.send();
    }, 1000);
    //hum
    setInterval(function () {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("humidity").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/humidity", true);
      xhttp.send();
    }, 1000);
    //light
    setInterval(function () {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("light").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/light", true);
      xhttp.send();
    }, 1000);
    //ppm
    setInterval(function () {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("ppm").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/ppm", true);
      xhttp.send();
    }, 1000);
  </script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  else if(var == "LIGHT"){
    return readDHTlight();
  }
  else if(var == "CO2"){
    return readDHTppm();
  }
  return String();
}
void setup(){ 
  // Serial port for debugging purposes
  Serial.begin(115200);
  sht20.initSHT20();
  sht20.checkSHT20();
  Wire.begin();
 
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
  server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTlight().c_str());
  });
  server.on("/ppm", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTppm().c_str());
  });
  // Start server
  server.begin();
// begin returns a boolean that can be used to detect setup problems.
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  }
  else {
    Serial.println(F("Error initialising BH1750"));
  }
}
void loop(){
   
  
}

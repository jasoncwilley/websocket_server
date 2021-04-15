#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif

#include <WebSocketsServer.h>
#include <ArduinoJson.h>


//#define LED1 D0
//#define LED2 D1
//#define LED3 D3
//#define LED4 D4
//#define LED5 D5

const char INDEX_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<head>
  <title>Control Panel</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .header {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    margin-left: 20px;
    border: 2px solid; /* black */
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
.switch {
position: relative;
display: inline-block;
width: 40px;
height: 20px;
background-color: rgba(0, 0, 0, 0.25);
border-radius: 20px;
transition: all 0.3s;
}
.switch::after {
content: '';
position: absolute;
width: 18px;
height: 18px;
border-radius:50%;
background-color: white;
top: 1px;
left: 1px;
transition: all 0.3s;
}
.checkbox:checked + .switch::after {
left : 20px;
}
.checkbox:checked + .switch {
background-color: #7983ff;
}
.checkbox {
display : none;
}
</style>
<title>Control Panel</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="header">
    <h1>Switch Control Panel</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Front Porch Lights</h2>
      <button class= "button" onclick="button_1_on()" >On</button><button class= "button" onclick="button_1_off()" >Off</button>
   </div>
   <div class="card">
     <h2>Dining Room Candelier</h2>
     <button class= "button" onclick="button_2_on()" >On</button><button class= "button" onclick="button_2_off()" >Off</button>
        </div>
  <div class="card">
    <h2>Kitchen Lights</h2>
    <button class= "button" onclick= "button_3_on()" >On</button><button class= "button" onclick="button_3_off()" >Off</button>
       </div>
 <div class="card">
   <h2>Living Room Lamps</h2>
   <button class= "button" onclick= "button_4_on()" >On</button><button class= "button" onclick="button_4_off()" >Off</button>
</div>
<div class="card">
  <h2>Living Room Fan/Lights</h2>
  <button class= "button" onclick= "button_5_on()" >On</button><button class= "button" onclick="button_5_off()" >Off</button>
</div>
  </div>
<script>
var connection = new WebSocket('ws://'+location.hostname+':81/');
var button_1_status = 0;
var button_2_status = 0;


function button_1_on()
{
  console.log("LED 1 is ON");
  button_1_status=  1;
  send_data();  
}
function button_1_off()
{
console.log("LED 1 is OFF");
button_1_status= 0;
send_data();
}
function button_2_on()
{
   button_2_status= 1; 
  console.log("LED 2 is ON");
  send_data();
}
function button_2_off()
{
  button_2_status= 0;
console.log("LED 2 is OFF");
send_data();
}


function send_data()
{
  var full_data = '{"LED1" :'+button_1_status+',"LED2":'+button_2_status+'}';
  connection.send(full_data);
}
</script>
</body>
</html>
)=====";


#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        websockets.sendTXT(num, "Connected from server");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char*)( payload));
      Serial.println(message);

      DynamicJsonDocument doc(200);
    // deserialize the data
    DeserializationError error = deserializeJson(doc, message);
    // parse the parameters we expect to receive (TO-DO: error handling)
      // Test if parsing succeeds.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  int LED1_status = doc["LED1"];
  int LED2_status = doc["LED2"];
  //digitalWrite(LED1,LED1_status);
  //digitalWrite(LED2,LED2_status);

  }
}

void setup(void)
{
  
  Serial.begin(115200);
 // pinMode(LED1,OUTPUT);
  //pinMode(LED2,OUTPUT);
  //pinMode(LED3,OUTPUT);
 // pinMode(LED4,OUTPUT);
  //pinMode(LED5,OUTPUT);
  WiFi.mode(WIFI_AP);
  Serial.begin(115200);  // Begin communiction on Serial 115200
  Serial.println("Configuring Access Point...");
delay(2000);
// SSID and Password for the ESP32 Access Point
const char* ssid = "smelly_packets";
const char* password = "";  // Access Point is left insecure
Serial.println("Intializing Access Point...");
delay(2000);
WiFi.softAP(ssid, password);  //Create INSECURE Access Point
Serial.println("Access Point configured...");
Serial.println(ssid);     //Return Access Point SSID in Serial
Serial.println("has been created at");
Serial.println(WiFi.softAPIP());  //Return Access Point IP address in Serial

  if (MDNS.begin("ESP")) { //home.local
    Serial.println("MDNS responder started");
  }



  server.on("/", [](AsyncWebServerRequest * request)
  { 
   
  request->send_P(200, "text/html", INDEX_page);
  });

   server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   // digitalWrite(LED1,HIGH);
  request->send_P(200, "text/html", INDEX_page);
  });

  server.onNotFound(notFound);

  server.begin();  // start webserver
  websockets.begin();
  websockets.onEvent(webSocketEvent);

}


void loop(void)
{

 websockets.loop();
}

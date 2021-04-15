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
      <button class= "button" onclick= "button_1_on()" >On</button><button class= "button" onclick="button_1_off()" >Off</button>
   </div>
   <div class="card">
     <h2>Dining Room Candelier</h2>
     <button class= "button" onclick= "button_2_on()" >On</button><button class= "button" onclick="button_2_off()" >Off</button>
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
function button_1_on()
{
  console.log("LED 1 is ON");
  connection.send("LED 1 is ON");
}
function button_1_off()
{
console.log("LED 1 is OFF");
connection.send("LED 1 is OFF");
}
function button_2_on()
{
  console.log("LED 2 is ON");
  connection.send("LED 2 is ON");
}
function button_2_off()
{
console.log("LED 2 is OFF");
connection.send("LED 2 is OFF");
}
function button_3_on()
{
  console.log("LED 3 is ON");
  connection.send("LED 3 is ON");
}
function button_3_off()
{
console.log("LED 3 is OFF");
connection.send("LED 3 is OFF");
}
function button_4_on()
{
  console.log("LED 4 is ON");
  connection.send("LED 4 is ON");
}
function button_4_off()
{
console.log("LED 4 is OFF");
connection.send("LED 4 is OFF");
}
function button_5_on()
{
  console.log("LED 5 is ON");
  connection.send("LED 5 is ON");
}
function button_5_off()
{
console.log("LED 5 is OFF");
connection.send("LED 5 is OFF");
}
</script>
</body>
</html>
)====";

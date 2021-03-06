#include <Arduino.h>

#pragma region Pages
/* Style */
String style =
"<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
".container { width: 35%; margin: auto; padding: 10px; background-color: whitesmoke; border-radius: 10px; padding: 25px 0 35px 0; }"
"input{background:#f1f1f1;border:0;padding: 5px}body{background:#636f82;font-family:sans-serif;font-size:14px;color:#777}"
"#psw { font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif; font-size: normal; font-weight: normal; width: auto; margin: none; border: none;"
"outline: none; border-radius: 4px; background-color: white; padding-left: 1%; height: 30px; width: 48%; border: 1px solid dodgerblue; }"
"#file-input{padding:0; text-align:center; display:block; cursor:pointer}"
"#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
"form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
".btn { color: #333; font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif; font-size: normal;"
"font-weight: normal; width: auto; margin: none; border: none; outline: none; border-radius: 4px; background-color: white; height: 30px; width: 25%; border: 1px solid dodgerblue; }"
".btn:hover { color: white; width: 50%; transition: all .2s ease-in-out; transform: scale(1); background: dodgerblue; }";



/* Server Index Page */
String updatePage = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
"<label id='file-input' for='file'>   Choose file...</label>"
"<input type='password' name='password' id='psw' placeholder = 'Password'> <br>"
"<input type='submit' class=btn value='Update'>"
"<br><br>"
"<div id='prg'></div>"
"<br><div id='prgbar'><div id='bar'></div></div><br></form>"
"<script>"
"function sub(obj){"
"var fileName = obj.value.split('\\\\');"
"document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
"};"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
"if(form.psw.value=='197346')"
"{"
"form.psw.value = '';"
"$.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');"
"$('#bar').css('width',Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('success!') "
"},"
"error: function (a, b, c) {"
"}"
"});"
"}"
"else"
"{"
" alert('Error: Password Incorrect')/*displays error message*/"
"}"
"});"
"</script>" + style;

#pragma endregion


//------ Wifi/ota/webserver ------
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
WebServer server(80);
IPAddress staticIP(192, 168, 0, 7);
IPAddress gateway(192, 168, 0, 2);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 2);

void OtaSetup(){
  MDNS.begin("HomeAutomation");

  /*return index page which is stored in ServerIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", updatePage);
  });
  server.on("/light", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", "<h1>Light Switched</h1>");
    ShelfLightState();
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
      } else {
      }
    }
  });
  server.begin();
}

void WifiSetup(){
  WiFi.config(staticIP, gateway, subnet, dns, dns);
  WiFi.begin("DD-Wrt", "197346825");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void WebControler(){
  server.handleClient();
}
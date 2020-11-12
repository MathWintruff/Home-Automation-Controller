//------ Wifi/ota/webserver ------
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
WebServer server(8099);
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

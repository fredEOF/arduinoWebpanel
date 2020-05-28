#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <LittleFS.h>

//set your own options here
const char *ssid = "";
const char *password = "";
const IPAddress ip(192, 168, 10, 222);
const IPAddress gateway(192, 168, 10, 1);
const IPAddress subnet(255, 255, 255, 0);
//---------------------------------------

ESP8266WebServer server(80);

void setup(void)
{
  Serial.begin(115200);
  if (!LittleFS.begin())
  {
    Serial.println("Filesystem cant be mounted.");
    return;
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  server.on("/", HTTP_GET, getIndex);
  server.on("/getState", HTTP_GET, getState);
  server.on("/style.css", HTTP_GET, getStyle);
  server.on("/manifest.webmanifest", HTTP_GET, getManifest);
  server.on("/pcb.png", HTTP_GET, getIcon);
  server.on("/checkstatus.js", HTTP_GET, getJavascript);
  server.begin();
}

// ------------------------------------------------------------------
void getState()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Aus");
}

void getIndex()
{
  File indexFile = LittleFS.open("/index.html", "r");
  server.streamFile(indexFile, "text/html");
  indexFile.close();
}

void getStyle()
{
  File styleFile = LittleFS.open("/style.css", "r");
  server.streamFile(styleFile, "text/css");
  styleFile.close();
}

void getManifest()
{
  File manifestFile = LittleFS.open("/manifest.webmanifest", "r");
  server.streamFile(manifestFile, "webmanifest");
  manifestFile.close();
}

void getIcon()
{
  File iconFile = LittleFS.open("/pcb.png", "r");
  server.streamFile(iconFile, "image/png");
  iconFile.close();
}

void getJavascript()
{
  File javascriptFile = LittleFS.open("/checkstatus.js", "r");
  server.streamFile(javascriptFile, "js");
  javascriptFile.close();
}
// ------------------------------------------------------------------

void loop(void)
{
  server.handleClient();
}
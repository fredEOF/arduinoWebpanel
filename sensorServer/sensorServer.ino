#include <ESP8266WebServer.h>
#include <Arduino.h>

// Your Wifi SSID and Password
const char *ssid = "";
const char *password = "";
const IPAddress ip(192, 168, 10, 111);
const IPAddress gateway(192, 168, 10, 1);
const IPAddress subnet(255, 255, 255, 0);

boolean state = false;
ESP8266WebServer server(80);
// define your output pin and set mode in setup
const int sensor = D8;

void setup(void)
{
  pinMode(sensor, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  server.on("/changeState", HTTP_POST, switchState);
  server.on("/getState", HTTP_GET, getState);
  server.begin();
}
// -------------------------------------------------------------
void switchState()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  state = !state;
  // define which output should be triggered (first parameter "sensor")
  // leave the second parameter "state" untouched
  digitalWrite(sensor, state);
  // -----------------------------------------------------------
  server.send(200, "State changed!");
}

void getState()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (state)
  {
    server.send(200, "text/plain", "on");
  }
  else
  {
    server.send(200, "text/plain", "off");
  }
}
// -------------------------------------------------------------
void loop(void)
{
  server.handleClient();
}
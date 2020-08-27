#define FLAG_ACTIVE_DEBUG false
#define FLAG_ACTIVE_HARDWARE_WDT true

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "pin_exc.h"
#include "time_mc.h"
#include "config.h"

const String indexHTML = "<html><h1><center><a href='active'>RELAY ACTIVE</a></center></h1></html>";

ESP8266WebServer server(80);
OutputExc relay(0x05, false);
TimeMC timeMC;
unsigned long timestampWLAN;

#if (FLAG_ACTIVE_DEBUG == true)
unsigned long timestampLOG;
#endif

#if (FLAG_ACTIVE_HARDWARE_WDT == true)
OutputExc wdtSignal(0x06, false);
#endif

#if (FLAG_ACTIVE_DEBUG == true)
void logDevice(unsigned long &currentMillisecTime)
{
  if (currentMillisecTime - timestampLOG < 20000)
  {
    return;
  }
  timestampLOG = currentMillisecTime;
  Serial.print(F("DEBUG: WIFI > ssid:"));
  Serial.println(ssid);
  Serial.print(F("DEBUG: WIFI > password:"));
  Serial.println(password);
  Serial.print(F("DEBUG: WIFI > status:"));
  Serial.println(WiFi.status());
  Serial.print(F("DEBUG: WIFI > IP:"));
  Serial.println(WiFi.localIP());
  Serial.print(F("DEBUG: RELAY > state:"));
  Serial.println(relay.read());
}
#endif

void watcherWIFI(unsigned long &currentMillisecTime)
{
  if (WiFi.status() == WL_CONNECTED || currentMillisecTime - timestampWLAN < 30000)
  {
    return;
  }
  timestampWLAN = currentMillisecTime;
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
}

void webIndex()
{
  server.send(200, "text/html", indexHTML);
}

void webActRelayActive()
{
  relay.active(timeMC.ms);
#if (FLAG_DEBUG_ACTIVE == true)
  Serial.print(F("DEBUG: SERVER > relay active:"));
  Serial.println(relay.read())
#endif
  server.send(200, "text/html", String(relay.read()));
}

void webActRelayState()
{
#if (FLAG_DEBUG_ACTIVE == true)
  Serial.print(F("DEBUG: SERVER > relay state:"));
  Serial.println(relay.read())
#endif
  server.send(200, "text/html", String(relay.read()));
}

void setup(void)
{
#if (FLAG_DEBUG_ACTIVE == true)
  Serial.begin(9600);
  Serial.println(F("\n\nDEBUG: DEVICE > setup"));
#endif
  server.on("/", webIndex);
  server.on("/active", webActRelayActive);
  server.on("/state", webActRelayState);
  server.begin();
#if (FLAG_DEBUG_ACTIVE == true)
  Serial.println(F("DEBUG: DEVICE > begin"));
#endif
}

void loop(void)
{
  timeMC.update();
#if (FLAG_ACTIVE_DEBUG == true)
  logDevice(timeMC.ms);
#endif
#if (FLAG_ACTIVE_HARDWARE_WDT == true)
  wdtSignal.process(timeMC.ms, 20000, !wdtSignal.read());
#endif
  relay.process(timeMC.ms, 30000, false);
  watcherWIFI(timeMC.ms);
  if (WiFi.status() != WL_CONNECTED)
  {
    return;
  }
  server.handleClient();
}

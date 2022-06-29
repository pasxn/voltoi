#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "server.h"
#include "libvoltmeter.h"
  
void setup() {
  Serial.begin(115200);
  server_init();
}
  
void loop() {
 
  ws.textAll(String( get_voltage() ));
 
  delay(200);

  ws.textAll("1");
 
  delay(200);
}

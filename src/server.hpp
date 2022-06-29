#ifndef __SERVER__
#define __SERVER__

const char* ssid = "noob_wifi";
const char* password =  "pasangewifimewwaeka";
  
AsyncWebServer server(80);
AsyncWebSocket ws("/8000");
  
void onWsEvent(AsyncWebSocket * server, 
               AsyncWebSocketClient * client, 
               AwsEventType type, 
               void * arg, uint8_t *data, size_t len) {
  
  if(type == WS_EVT_CONNECT) {
  
    Serial.println("Websocket client connection received");
     
  } else if(type == WS_EVT_DISCONNECT) {
 
    Serial.println("Client disconnected");
  
  }
}

void server_init() {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println(WiFi.localIP());
  
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  
  server.begin();
}

#endif // __SERVER__
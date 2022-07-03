#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "server.hpp"
#include "libvoltmeter.hpp"


static const BaseType_t core_zero = 0;
static const BaseType_t core_one = 1;

float voltage = 0;
static SemaphoreHandle_t mutex;

void websocket_server(void *parameters) {
  server_init();
  float local_var;
  while (1) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    
    local_var = voltage;

    ws.textAll(String(local_var));
    
    vTaskDelay(70 / portTICK_PERIOD_MS);

    xSemaphoreGive(mutex);

    // Print out new shared variable
    Serial.println(voltage);
  }
}

void voltmeter(void *parameters) {
  float local_var;
  while (1) {
    xSemaphoreTake(mutex, portMAX_DELAY);
    
    local_var = get_voltage();
    
    //vTaskDelay(10 / portTICK_PERIOD_MS);

    voltage = local_var;

    xSemaphoreGive(mutex);   
  }
}
  
void setup() {
  Serial.begin(115200);

  // Create mutex before starting tasks
  mutex = xSemaphoreCreateMutex();

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);

    // Start task 1
  xTaskCreatePinnedToCore(websocket_server, "websocket_server", 2048, NULL, 1, NULL, core_zero);

  // Start task 2
  xTaskCreatePinnedToCore(voltmeter, "voltmeter", 1024, NULL, 1, NULL, core_one);
  
  // Delete "setup and loop" task
  vTaskDelete(NULL);
}
  
void loop() {}

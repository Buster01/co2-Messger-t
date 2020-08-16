#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;

#include <GxEPD.h>
#include <GxGDEW029Z10/GxGDEW029Z10.h>    // 2.9" b/w/r
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <DallasTemperature.h>
#include <OneWire.h>

#include "WiFi.h" 
#include "driver/adc.h"
#include <esp_wifi.h>
#include <esp_bt.h>

#define DS18B20_PIN 15
#define TEMPERATURE_PRECISION 12
OneWire oneWire(DS18B20_PIN);          
DallasTemperature DS18B20(&oneWire);

#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBoldOblique24pt7b.h>

GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/ 16, /*RST=*/ 17); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/ 17, /*BUSY=*/ 4); // arbitrary selection of (16), 4

long co2_displ = 0;
long tvoc_displ = 0;
float temp_displ = 0.0;
int sensor_count = 0;
int displ_update = 0;

#include "display.h"
#include "energy_save.h"
#include "sensor.h"


void setup() {
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  
  Serial.begin(115200);
  Serial.println("setup");
  stromsparmodus();
  display_init();
  sensor_init();

  switch(wakeup_reason) {
    case ESP_SLEEP_WAKEUP_TIMER :
      Serial.println("Wakeup");
      break;
  
    default :
      Serial.println("Reset");
      display_default();
      break;
  }
  display_sensor_data();
  deep_sleep();
}

void loop() {
  
}

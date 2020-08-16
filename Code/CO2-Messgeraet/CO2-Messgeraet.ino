#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;

#include <GxEPD.h>
#include <GxGDEW029Z10/GxGDEW029Z10.h>    // 2.9" b/w/r
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <DallasTemperature.h>
#include <OneWire.h>
#include <RunningMedian.h>

RunningMedian co2_med = RunningMedian(20);
RunningMedian tvoc_med = RunningMedian(20);

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

#define SLEEPTIME 15
long co2_displ = 0;
long tvoc_displ = 0;
float temp_displ = 0.0;
float temp = 0.0;
int sensor_count = 0;
bool displ_update = true;
int wake = 0;

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
  display_default();
  sensor_init();
}

void loop() {
  if(!ccs.readData()){
    co2_med.add(ccs.geteCO2());
    tvoc_med.add(ccs.getTVOC());
    temp = DS18B20.getTempCByIndex(0);
    Serial.println("co2: " + String(co2_med.getMedian()) + " | " + String(co2_displ));
    Serial.println("TVOC: " + String(tvoc_med.getMedian()) + " | " + String(tvoc_displ));
    Serial.println("Temp: " + String(temp) + " | " + String(temp_displ));
  }
  DS18B20.requestTemperatures();
  if (wake == 0) { 
    display_sensor_data(); 
    display.update();
    display.powerDown();
  }
  if (wake > 3 ) { 
    // Anzeige wenn co2 größer oder kleiner 30 als letzter Wert
    if ( ((co2_med.getMedian() >= co2_displ + 30 ) || ( co2_med.getMedian() <= co2_displ - 30 )) ) {
      display_sensor_data();
      displ_update = true;
    }

    // Anzeige wenn tvoc größer oder kleiner 5 als letzter Wert
    if ( ((tvoc_med.getMedian() >= tvoc_displ + 5 ) || ( tvoc_med.getMedian() <= tvoc_displ - 5 )) ) {
      display_sensor_data();
      displ_update = true;
    }

    // Anzeige wenn temp größer oder kleiner 0.3  als letzter Wert
    if ( (( temp >= temp_displ + 0.3 ) || ( temp <= temp_displ - 0.3 )) ) {
      display_sensor_data();
      displ_update = true;
    }
    
    // Display Update bei Bedarf
    if ( displ_update == true ) {
      Serial.println("Display Update!");
      display.update();
      display.powerDown();
      displ_update = false;
      co2_displ = co2_med.getMedian();
      tvoc_displ = tvoc_med.getMedian();
      temp_displ = temp;
    } else { Serial.println("kein Display Update!"); }
    wake = 1;
  } 
  light_sleep();
  wake++;
}

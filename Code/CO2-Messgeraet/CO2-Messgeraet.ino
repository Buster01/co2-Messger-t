#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;

#include <GxEPD.h>
#include <GxGDEW029Z10/GxGDEW029Z10.h>    // 2.9" b/w/r
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <DallasTemperature.h>
#include <OneWire.h>
#include <RunningMedian.h>

RunningMedian co2_med = RunningMedian(120);
RunningMedian tvoc_med = RunningMedian(120);

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


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  display.init(); 
  display.setRotation(3);

  // Display aufbau
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.fillRect(146, 0, 3, 128, GxEPD_BLACK);
  display.fillRect(146, 63, 150, 3, GxEPD_BLACK);

  //CO2
  display.setCursor(20, 110);
  display.setFont(&FreeMonoBold12pt7b);
  display.println("ppm");
  display.setFont(&FreeMonoBold24pt7b);
  display.setCursor(77, 120);
  display.print("CO");
  display.setCursor(131, 126);
  display.setFont(&FreeMonoBold12pt7b);
  display.println("2");

  // TVOC
  display.setCursor(175, 57);
  display.setFont(&FreeMonoBold9pt7b);
  display.println("ppb TVOC"); 

  // Temperatur
    display.setCursor(175, 122);
  display.setFont(&FreeMonoBold9pt7b);
  display.println("Temperatur"); 
  display.update();

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // dallas Sensor Init
  DS18B20.begin(); // Dallas 18b20
  delay(1000);
  Serial.print("Anzahl Dallas Temperatur Sensoren: "); Serial.println(DS18B20.getDeviceCount());
  sensor_count=DS18B20.getDeviceCount();
  DS18B20.setResolution(TEMPERATURE_PRECISION);
  Serial.print ("Setzte DS1B20 Temperatur Praezision auf ");
  Serial.print (TEMPERATURE_PRECISION);
  Serial.println ("Bit");

}

void loop() {
  if(ccs.available()){
    if(!ccs.readData()){
      DS18B20.requestTemperatures();
      co2_med.add(ccs.geteCO2());
      tvoc_med.add(ccs.getTVOC());
      
      display_co2(co2_med.getMedian());
      display_tvoc(tvoc_med.getMedian());
      display_temp(DS18B20.getTempCByIndex(0));
      delay(1000);
    }
    else{
      Serial.println("CO2 Sensor - ERROR!");
      while(1);
    }
  }
}

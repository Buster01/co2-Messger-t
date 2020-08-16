void sensor_init(void){
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

void display_sensor_data(void){
  if(ccs.available()){
    if(!ccs.readData()){
      DS18B20.requestTemperatures();      
      display_co2(ccs.geteCO2());
      display_tvoc(ccs.getTVOC());
      display_temp(DS18B20.getTempCByIndex(0));
      display.powerDown();  
    } else {
        Serial.println("CO2 Sensor - ERROR!");
        while(1);
    }
  }
}

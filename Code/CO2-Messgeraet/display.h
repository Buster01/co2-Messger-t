void display_init(void){
  display.init(); 
  display.setRotation(3);
}

void display_default(void){
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
}

void display_co2(long co2) {
  // CO2 
  if ( co2 > 1200 ) {
    display.setTextColor(GxEPD_RED);
  } else {
    display.setTextColor(GxEPD_BLACK);
  }
  display.fillRect(0, 0, 145, 65, GxEPD_WHITE);
  display.setCursor(20, 60);
  display.setFont(&FreeMonoBoldOblique24pt7b);
  display.print(co2);
  co2_displ = co2;
}

void display_tvoc(long tvoc){
  // TVOC
  if ( tvoc > 200 ) {
    display.setTextColor(GxEPD_RED);
  } else {
    display.setTextColor(GxEPD_BLACK);
  }
  display.fillRect(149, 0, 147, 43, GxEPD_WHITE);
  display.setCursor(200, 33);
  display.setFont(&FreeMonoBold18pt7b);
  display.print(tvoc);
  tvoc_displ = tvoc;
}

void display_temp(float temp){
  // Temperatur    
  if ( temp > 30 ) {
    display.setTextColor(GxEPD_RED);
  } else {
    display.setTextColor(GxEPD_BLACK);
  }
  display.fillRect(149, 67, 147, 43, GxEPD_WHITE);
  display.setCursor(165, 100);
  display.setFont(&FreeMonoBold18pt7b);
  display.print(temp,1); display.print(" C");
  temp_displ = temp;
}

void display_sensor_data(void){
    display_co2(co2_med.getMedian());
    display_tvoc(tvoc_med.getMedian());
    display_temp(temp);
}

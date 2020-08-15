void display_co2(long co2) {
  // CO2
  if ( (co2 >= (co2_displ + 30)) || (co2 <= (co2_displ - 30)) ){  
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
    display.updateWindow(0, 0, 143, 127, true);
    delay(1000);
  }
}

void display_tvoc(long tvoc){
  // TVOC
  if ( (tvoc >= (tvoc_displ + 5)) || (tvoc <= (tvoc_displ - 5)) ){
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
    display.updateWindow(149, 0, 146, 60, true);
    delay(1000);
  }
}

void display_temp(float temp){
  // Temperatur
  if ( (temp >= (temp_displ + 0.5)) || ( temp <= (temp_displ - 0.5))  ) {      
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
    display.updateWindow(149, 67, 146, 60, true);
    delay(1000);
  }
}

void stromsparmodus(void) {
  Serial.println("Start Stromsparmodus");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  esp_bt_controller_disable();
  esp_bt_controller_deinit();
  esp_bt_mem_release(ESP_BT_MODE_BTDM);

  adc_power_off();
  esp_bt_controller_disable();

  ccs.setDriveMode(CCS811_DRIVE_MODE_60SEC);
  Serial.println("Ende Setup Stromsparmodus");
}

void light_sleep(void) {
    Serial.println("LightSleep");
    delay(10);
    long time2sleep = (45 * 1000000);
    esp_sleep_enable_timer_wakeup(time2sleep);
    int ret = esp_light_sleep_start();
    delay(10);
}

void deep_sleep(void) {
    Serial.println("DeepSleep");
    delay(10);
    long time2sleep = (45 * 1000000);
    esp_sleep_enable_timer_wakeup(time2sleep);
    esp_deep_sleep_start(); 
    delay(10);
}

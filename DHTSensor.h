
// DHT & FAN //

void readDHT(unsigned long currentTime) {
  //Only Reads And Prints When No Motion Is Detected
  if(state == LOW && (currentTime - lastDHTRead > dhtInterval)) {
    lastDHTRead = currentTime;
    DHT.read(DHT_PIN);

    if(isnan(DHT.temperature) || isnan(DHT.humidity)) {
      Serial.println("ERROR! DHT Read Failed! Skipping...");
      return;
    }

  // --- FAN CONTROL LOGIC --- //
  static bool fanOn = false;

  // If Fan Is Off & Temp Is Above 25°C, Turns On Fan
  //Prevents Fan From Flicking On & Off
    if(DHT.temperature >= 25 && !fanOn) {
      fanOn = true;
      digitalWrite(FAN_PIN, HIGH);
    }
    // Else If Fan Is On & Temp Is Less Than 23°C, Turns Off Fan
    else  if(DHT.temperature <= 23 && fanOn){
      fanOn = false;
      digitalWrite(FAN_PIN, LOW);
    }
  }
}

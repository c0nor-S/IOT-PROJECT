
// DHT CODE //

// Gathers Temp & Humi Values
void readDHT(unsigned long currentTime) {
  //DHT11 Has A Minimum Sampling Period Of ~1-2 Seconds
  //Reading Faster Causes Errors / NaN Values
  if (currentTime - lastDHTRead > dhtInterval) {
    lastDHTRead = currentTime;
    DHT.read(DHT_PIN);

    //'isnan' = 'is not a number' -> Incase DHT11 Fails, Skipping Bad Reads Prevents 0 C False Readings
    if (isnan(DHT.temperature) || isnan(DHT.humidity)) {
      Serial.println("ERROR! DHT Read Failed! Skipping...");
      return;
    }
    currentTemp = DHT.temperature;
    currentHumi = DHT.humidity;
  }
}


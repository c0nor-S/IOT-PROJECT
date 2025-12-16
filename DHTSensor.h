
// DHT & FAN //

void readDHT(unsigned long currentTime) {
  if (currentTime - lastDHTRead > dhtInterval) {
    lastDHTRead = currentTime;
    DHT.read(DHT_PIN);

    if (isnan(DHT.temperature) || isnan(DHT.humidity)) {
      Serial.println("ERROR! DHT Read Failed! Skipping...");
      return;
    }
    currentTemp = DHT.temperature;
  }
}

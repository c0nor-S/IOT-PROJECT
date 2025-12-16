
// LDR CODE //

void checkLDR() {
  int total = 0;

  // Averages 10 Readings Of The Light Level (0 -> 4095)
  for (int i = 0; i < 10; i++) {
    total += analogRead(LDR_SENSOR);
  }
  lightVal = total / 10;
}
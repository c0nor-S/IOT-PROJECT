
// LDR CODE //

void checkLDR() {
  int total = 0;

  // Averages 10 Readings Of The Light Level (0 -> 4095)
  for(int i = 0; i < 10; i++) {
    total += analogRead(LDR_SENSOR);
    delay(5);
  }
  lightVal = total / 10;


static bool ledOn = false;
const int darkThreshold = lightInit - 50;
const int brightThreshold = lightInit - 30;

  // If LED Is Off & The Light Level Is Considered 'Dark', Turns On LED
  if(!ledOn && lightVal < darkThreshold) {
    ledOn = true;
    digitalWrite(LED, HIGH);
  }
  // If LED is ON & The Light Level Is Considered 'Bright', Turns Off LED
  else if(ledOn && lightVal > brightThreshold) {
    ledOn = false;
    digitalWrite(LED, LOW);
  }
}
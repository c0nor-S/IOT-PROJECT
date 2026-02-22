
// LDR CODE //

//Averages Light Level
void checkLDR() {
  int total = 0;

  for (int i = 0; i < 10; i++) {
    total += analogRead(LDR_SENSOR);
  }
  lightVal = total / 10;
}
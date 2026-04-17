
// LDR CODE //

//Averages Light Level
//Analog Sensors Are Noisy : Single Readings Can Spike Due To Electrical Interference
//Average Smooths Signal & GIves More Stable, Representative Light Level
void checkLDR() {
  int total = 0;

  for (int i = 0; i < 10; i++) {
    total += analogRead(LDR_SENSOR);
  }
  lightVal = total / 10;
}
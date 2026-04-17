
// PIR //

//Tracks Motion And Includes Delay Incase Of False Triggers
//(200ms Check : Debounce, Prevents Multiple State Changes From A Single Motion Event Even Wihtin The Same Instant)
void checkPIR(unsigned long currentTime) {
  int val = digitalRead(PIR_SENSOR);

  if(val == HIGH && (currentTime - lastMotionTime > 200)) {
    if (state == LOW) {
      state = HIGH;
    }
    lastMotionTime = currentTime; //Reset Cooldown Timer
  }

//After Last Motion -> 3 Seconds (ignoreTime) Elapse Before Resetting To LOW
//Prevents Rapid HIGH / LOW FLicker If Someone Moves Slowly Through The Sensor Range
  if (state == HIGH && (currentTime - lastMotionTime > ignoreTime)) {
    state = LOW;
  }
}

// PIR & VIBRATION //

void checkPIR(unsigned long currentTime) {
  int val = digitalRead(PIR_SENSOR);

  if(val == HIGH && (currentTime - lastMotionTime > 200)) {
    if (state == LOW) {
      state = HIGH;
    }
    lastMotionTime = currentTime;
  }

  if (state == HIGH && (currentTime - lastMotionTime > ignoreTime)) {
    state = LOW;
  }
}
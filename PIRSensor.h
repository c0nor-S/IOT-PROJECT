
// PIR & VIBRATION //

void checkPIR(unsigned long currentTime) {
  int val = digitalRead(PIR_SENSOR);

  // --- MOTION DETECTED --- //
  // If The PIR Sensor Detects Motion & Enough Time Has Passed Since Last Detetction
  // (Prevents False Readings And / Or Bounces)
  if (val == HIGH && (currentTime - lastMotionTime > 200)) {
    // Only Triggers If Current State Is LOW (No Previous Motion)
    if (state == LOW) {
      state = HIGH;
      digitalWrite(LED, HIGH);
      digitalWrite(VIBRATION_PIN, HIGH);
      vibrationEnd = currentTime + 3000;  // Stop Vibration After 100ms
    }
    lastMotionTime = currentTime;  // Update Last Motion Detected Time
  }

  // Turns Off Vibration After A Short Period Of Time
  if (currentTime >= vibrationEnd) {
    digitalWrite(VIBRATION_PIN, LOW);
  }

  // --- NO MOTION DETECTED --- //
  if (state == HIGH && (currentTime - lastMotionTime > ignoreTime)) {
    digitalWrite(LED, LOW);
    state = LOW;
  }
}
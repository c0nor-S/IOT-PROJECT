
// SOUND //

void checkSound(unsigned long currentTime) {
  long total = 0;
  
  for (int i = 0; i < 10; i++) {
    total += analogRead(SOUND_PIN);
    delay(2);
  }
  int soundValue = total / 10;
}
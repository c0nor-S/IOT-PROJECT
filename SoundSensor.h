
// SOUND & BUZZER //

void checkSound(unsigned long currentTime) {
  static unsigned long lastSoundTime = 0;
  static bool buzzing = false;

  const unsigned long soundCooldown = 1000;
  const int threshold = 2000;
  const int buzzerDuration = 200;

  long total = 0;
  // Averages 10 Readings Of The Sound Level (0 -> 1023)
  for(int i = 0; i < 10; i++) {
    total += analogRead(SOUND_PIN);
    delay(2);
  }
  int soundValue = total / 10;

  // If Sound Level Is Greater Than Predetermined Base Level & Enough Time Has Passed Since Last Detected Sound, Activates Vibration Motor
  if(latestSoundValue = (soundValue > threshold && (currentTime - lastSoundTime > soundCooldown)))
    {
    checkSoundAlert = true;
    lastSoundTime = currentTime;
    buzzerEnd = currentTime + buzzerDuration;
    tone(BUZZER_PIN, 2000, buzzerDuration);
    }
  else
    {
      checkSoundAlert = false;
    }

  // STOP BUZZING
  if(buzzing && currentTime >= buzzerDuration)
  {
    noTone(BUZZER_PIN);
  }
}                                                                                                                                                                                                                                                                                                                                                                                
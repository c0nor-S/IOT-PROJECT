/***************
Conor Shaughnessy
IOT Sensor Test
****************/

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;

#define DHT_PIN 33
#define LED 26
#define PIR_SENSOR 13
#define LDR_SENSOR 35
#define FAN_PIN 27
#define SOUND_PIN 32
#define VIBRATION_PIN 25
#define BUZZER_PIN 14

int state = LOW;
int lightInit;
int lightVal;
bool checkSoundAlert = false;

unsigned long lastMotionTime = 0;           // Stores Timestamp Of Last Time Motion Was Detected
const long ignoreTime = 3000;               // 3 Second  Cooldown For PIR Sensor
unsigned long lastDHTRead = 0;              // Stores Timestamp Of Last DHT Reading
const unsigned long dhtInterval = 2000;     // Minimum Time Between Temp / Humi Reads
unsigned long vibrationEnd = 0;             // Schedueled Stop Time

#include "DHTSensor.h"
#include "LDRSensor.h"
#include "PIRSensor.h"
#include "SoundSensor.h"

void setup() {
  Serial.begin(115200); 
  delay(2000); 
  
  // --- INPUTS --- //
  pinMode(PIR_SENSOR, INPUT);
  pinMode(SOUND_PIN, INPUT);
  pinMode(LDR_SENSOR, INPUT);
  pinMode(DHT_PIN, INPUT); 
  analogReadResolution(12);

// --- OUTPUTS --- //
  pinMode(LED, OUTPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lightInit = analogRead(LDR_SENSOR);

  Serial.println("System Starting...");
}

void loop() {
  unsigned long currentTime = millis();

  // SENSORS
  readDHT(currentTime);       // Temp & Humidity + Fan
  checkPIR(currentTime);      // Motion Detection
  checkLDR();                 // Light Sensor
  checkSound(currentTime);    // Sound Detection

  // --- Prepare Values For Serial Monitor --- //
  int soundValue = analogRead(SOUND_PIN);                                // Reads Sound Sensor
  int lightValue = analogRead(LDR_SENSOR);                              // Reads Light Sensor
  bool motionActive = (state == HIGH);                                 // True If Motion Is Detected
  bool dark = (lightValue < lightInit - 50);                          // True If Darker Than Starting Light Level
  bool fanActive = (DHT.temperature >= 25);                          // True If Temp. Is Higher Than 25°C
  bool ledState = dark;                                             // LED Turns Off If It's Dark
  bool soundAlert = checkSoundAlert;                               // True If Sound Is Loud
  bool buzzerActive = soundAlert;   
  bool vibrationActive = digitalRead(VIBRATION_PIN);             // Vibration Follows Sound Alert

// --- Converts Boolean Values Into Readable Strings
// '? :' Chooses String Depending On Boolean Value
// e.g. If fanActive = true, fanStr becomes "ON", else if fanActive = false, fanStr becomes "OFF"
  const char* fanStr = fanActive ? "On" : "OFF";
  const char* motionStr = motionActive ? "YES" : "NO";
  const char* lightStr = dark ? "Dark" : "Bright";
  const char* ledStr = ledState ? "ON" : "OFF";
  const char* soundAlertStr = soundAlert ? "YES" : "NO";
  const char* vibStr = vibrationActive ? "ON" : "OFF";

//If Temp/Humi Reads A NAN (Not A Number), Prints a 0
  int temp = isnan(DHT.temperature) ? 0 : DHT.temperature;
  int humi = isnan(DHT.humidity) ? 0 : DHT.humidity;


//Prints Readings Table
  static unsigned long lastPrint = 0;
  if(currentTime - lastPrint > 2000) {
    Serial.println("| Temp | Humi || Fan |  | Motion |  Light || LED |  | Sound || Sound Alert || Vibration |");
    Serial.println("-------|------||-----|  |--------|--------||-----|  |-------||-------------||-----------|");
    Serial.printf("| %d°C | %d%%  ||  %s |  |   %s   | %s || %s |  | %d ||      %s     ||    %s    |\n\n\n",
      temp,
      humi,
      fanStr,
      motionStr,
      lightStr,
      ledStr,
      soundValue,
      soundAlertStr,
      vibStr);

      Serial.println();
      //lastPrint = currentTime;
  }

  delay(3000);
}
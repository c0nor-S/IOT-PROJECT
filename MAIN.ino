/***************
Conor Shaughnessy
IOT Sensor Test
****************/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "time.h"


#include "homepage.h"
#include "homeCSS.h"

#include "dashpage.h"
#include "dashCSS.h"

#include "contpage.h"
#include "contCSS.h"

/*
#include "feat.h"
#include "featCSS.h"
*/

#include "demopage.h"
#include "demoCSS.h"
#include "demoJS.h"

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;

const char* ssid = "ConorsiPhone";
const char* password = "knocknacarra";
WebServer server(80);

#define DHT_PIN 33
#define LED 26
#define PIR_SENSOR 13
#define LDR_SENSOR 35
#define FAN_PIN 17
#define SOUND_PIN 32
#define VIBRATION_PIN 25
#define BUZZER_PIN 14


int state = LOW;           // Motion State
int lightInit;             // Initial LDR Value
int lightVal;              // Current LDR Reading
int latestSoundValue = 0;  // Last Sound Reading
bool checkSoundAlert = false;

int alarmHour = 0;
int alarmMinute = 0;
bool lightToggle = false;
bool alarmTriggered = false;
unsigned long alarmStartTime = 0;

unsigned long lastBlinkTime = 0;
bool ledState = false;
const int blinkInterval = 200;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

unsigned long lastMotionTime = 0;        // Stores Timestamp Of Last Time Motion Was Detected
const long ignoreTime = 3000;            // 3 Second  Cooldown For PIR Sensor
unsigned long lastDHTRead = 0;           // Stores Timestamp Of Last DHT Reading
const unsigned long dhtInterval = 2000;  // Minimum Time Between Temp / Humi Reads
unsigned long vibrationEnd = 0;          // Schedueled Stop Time
unsigned long buzzerEnd = 0;

#include "DHTSensor.h"
#include "LDRSensor.h"
#include "PIRSensor.h"
#include "SoundSensor.h"

void handleNotFound();

void setupTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("Waiting For NTP Time...");
  while (!time(nullptr)) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nTime Initialized");
}

void handleSetAlarm() {
  if (server.hasArg("hour") && server.hasArg("minute")) {
    alarmHour = server.arg("hour").toInt();
    alarmMinute = server.arg("minute").toInt();
    alarmTriggered = false;
    server.send(200, "text/plain", "Alarm Set!");
    Serial.printf("Alarm Set: %02d : %02d\n", alarmHour, alarmMinute);
  } else {
    server.send(400, "text/plain", "Missing Hour or Minute");
  }
}

void handleDashboard() {
  int temp = isnan(DHT.temperature) ? 0 : DHT.temperature;
  int humi = isnan(DHT.humidity) ? 0 : DHT.humidity;
  int lightValue = analogRead(LDR_SENSOR);
  bool motionActive = (state == HIGH);
  int soundValue = analogRead(SOUND_PIN);

  const char* motionStr = motionActive ? "YES" : "NO";

  String dashboardHTML = dashPagePart1;
  dashboardHTML += String(temp);
  dashboardHTML += dashPagePart2;
  dashboardHTML += String(humi);
  dashboardHTML += dashPagePart3;
  dashboardHTML += String(lightValue);
  dashboardHTML += dashPagePart4;
  dashboardHTML += motionStr;
  dashboardHTML += dashPagePart5;
  dashboardHTML += String(soundValue);
  dashboardHTML += dashPagePart6;

  server.send(200, "text/html", dashboardHTML);
}

void handleDashboardData() {
  int temp = isnan(DHT.temperature) ? 0 : DHT.temperature;
  int humi = isnan(DHT.humidity) ? 0 : DHT.humidity;
  int lightValue = analogRead(LDR_SENSOR);
  bool motionActive = (state == HIGH);
  int soundValue = analogRead(SOUND_PIN);
  const char* motionStr = motionActive ? "YES" : "NO";

  String readingsHTML;
  readingsHTML += "<div class='hero-content'>";
  readingsHTML += "<div class='sensor-cards' id='temp-card'><h3>Temperature</h3><p>" + String(temp) + "°C</p></div>";
  readingsHTML += "<div class='sensor-cards' id='humi-card'><h3>Humidity</h3><p>" + String(humi) + "%</p></div>";
  readingsHTML += "<div class='sensor-cards' id='light-card'><h3>Light</h3><p>" + String(lightValue) + "</p></div>";
  readingsHTML += "<div class='sensor-cards' id='motion-card'><h3>Motion</h3><p>" + String(motionStr) + "</p></div>";
  readingsHTML += "<div class='sensor-cards' id='sound-card'><h3>Sound</h3><p>" + String(soundValue) + "</p></div>";
  readingsHTML += "</div>";

  server.send(200, "text/html", readingsHTML);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  delay(2000);

  setupTime();

  pinMode(PIR_SENSOR, INPUT);
  pinMode(SOUND_PIN, INPUT);
  pinMode(LDR_SENSOR, INPUT);
  pinMode(DHT_PIN, INPUT);

  analogReadResolution(12);

  pinMode(LED, OUTPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lightInit = analogRead(LDR_SENSOR);

  Serial.println("System Starting...\n\n\n");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/", []() {
    server.send(200, "text/html", homePagePart1);
  });

  server.on("/index.html", []() {
    server.send(200, "text/html", homePagePart1);
  });

  server.on("/home.css", []() {
    server.send(200, "text/css", homeCSS);
  });

  server.on("/dashData", handleDashboardData);
  server.on("/dash", handleDashboard);
  server.on("/dash.html", handleDashboard);
  server.on("/dash.css", []() {
    server.send(200, "text/css", dashCSS);
  });

  server.on("/cont.html", []() {
    server.send(200, "text/html", contPagePart1);
  });

  server.on("/cont.css", []() {
    server.send(200, "text/css", contCSS);
  });

  server.on("/demo.html", []() {
    server.send(200, "text/html", demoPagePart1);
  });

  server.on("/demo.css", []() {
    server.send(200, "text/css", demoCSS);
  });

  server.on("/demo.js", []() {
    server.send(200, "application/javascript", demoJS);
  });

  server.on("/saveSettings", []() {
    if (server.hasArg("light")) {
      lightToggle = server.arg("light").toInt() == 1;
      digitalWrite(LED, lightToggle ? HIGH : LOW);
      Serial.printf("\nLight Setting Saved");
    }
    if (server.hasArg("fan")) {
      bool fanToggle = server.arg("fan").toInt() == 1;
      digitalWrite(FAN_PIN, fanToggle ? HIGH : LOW);
      Serial.println("\nFan Setting Saved");
    }
    if (server.hasArg("sound")) {
      bool soundToggle = server.arg("sound").toInt() == 1;
      digitalWrite(BUZZER_PIN, soundToggle ? HIGH : LOW);
      Serial.print("Sound Setting Saved");
    }
    if (server.hasArg("vibration")) {
      bool vibrationToggle = server.arg("vibration").toInt() == 1;
      digitalWrite(VIBRATION_PIN, vibrationToggle ? HIGH : LOW);
      Serial.print("\nVibration Setting Saved");
    }
    server.send(200, "text/plain", "Settings Saved");
  });

  server.on("/setAlarm", []() {
    if (server.hasArg("hour") && server.hasArg("minute")) {
      alarmHour = server.arg("hour").toInt();
      alarmMinute = server.arg("minute").toInt();
      alarmTriggered = false;
      Serial.printf("\nAlarm Set: %02d:%02d\n", alarmHour, alarmMinute);
      server.send(200, "text/plain", "Alarm Set!");
    } else {
      server.send(400, "text/plain", "Missing Hour or Input");
    }
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleAlarmLED() {
  if (!lightToggle || !alarmTriggered) {
    digitalWrite(LED, LOW);
    return;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkTime >= blinkInterval) {
    ledState = !ledState;
    digitalWrite(LED, ledState ? HIGH : LOW);
    lastBlinkTime = currentMillis;
  }
}

void loop() {
  unsigned long currentTime = millis();
  server.handleClient();

  readDHT(currentTime);
  checkPIR(currentTime);
  checkLDR();
  checkSound(currentTime);

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    int currentHour = timeinfo.tm_hour;
    int currentMinute = timeinfo.tm_min;

    if (!alarmTriggered && currentHour == alarmHour && currentMinute == alarmMinute) {
      alarmTriggered = true;
      alarmStartTime = millis();
      Serial.print("ALARM TRIGGERED");
    }

    if (alarmTriggered && lightToggle) {
      handleAlarmLED();
    }

    if (alarmTriggered && (millis() - alarmStartTime >= 5UL * 60UL * 1000UL)) {
      digitalWrite(LED, LOW);
      alarmTriggered = false;
      Serial.println("ALARM ENDED: LED OFF");
    }
  }
}
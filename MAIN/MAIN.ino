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
#include "demopage.h"
#include "demoCSS.h"
#include "demoJS.h"

#include "secrets.h"
WiFiClient  client;

#include "ThingSpeak.h"
unsigned long myChannelNumber = 3239866;
const char * myWriteAPIKey = "P3PEMDKWL41A3RFC";

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
WebServer server(80);

// Pin definitions
#define DHT_PIN 33
#define LED 26
#define PIR_SENSOR 13
#define LDR_SENSOR 35
#define FAN_PIN 17
#define SOUND_PIN 32
#define VIBRATION_PIN 25
#define BUZZER_PIN 14

// Global variables : Why Global? - Because They Are Shared Across loop(), sensor functions, and alarm handlers
int state = LOW;                   // Motion state
int lightInit;                     // Initial LDR value
int lightVal;                      // Current LDR reading
int latestSoundValue = 0;          // Last sound reading
bool checkSoundAlert = false;
float currentTemp = 0;
float currentHumi = 0;

int alarmHour = 0;
int alarmMinute = 0;

bool lightToggle = false;
bool buzzerTriggered = false;
bool buzzerToggle = false;
bool fanToggle = false;
bool vibrationToggle = false;
bool alarmTriggered = false;
unsigned long alarmStartTime = 0;

const int buzzerChannel = 0;
const int buzzerFrequency = 4000;
const int buzzerResolution = 8;

unsigned long lastBlinkTime = 0;
bool ledState = false;
const int blinkInterval = 200;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

const unsigned long alarm_duration = 60UL * 1000UL;     // 60 Second Timer
unsigned long lastMotionTime = 0;                       // Stores timestamp of last motion
const long ignoreTime = 3000;                           // 3-second cooldown for PIR sensor
unsigned long lastDHTRead = 0;                          // Stores timestamp of last DHT reading
const unsigned long dhtInterval = 2000;                 // Minimum time between temp/humi reads
unsigned long vibrationEnd = 0;                         // Scheduled stop time
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

    //Allows Live Readings To Display On The Dashboard
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
    // WiFi setup
    WiFi.mode(WIFI_STA); // Station Mode: Connects To A Router. AP Mode Would Create Its Own Network Instead
    WiFi.begin(ssid, password);
    Serial.println("");
    delay(2000);
    setupTime();
    ThingSpeak.begin(client);

    // Pin setup
    pinMode(PIR_SENSOR, INPUT);
    pinMode(SOUND_PIN, INPUT);
    pinMode(LDR_SENSOR, INPUT);
    pinMode(DHT_PIN, INPUT);
    analogReadResolution(12); //Sets ADC To 12-bit, Instead of 10-bit
    pinMode(LED, OUTPUT);
    pinMode(VIBRATION_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    lightInit = analogRead(LDR_SENSOR);

    Serial.println("System Starting...\n\n\n");

    // Wait for WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Allows Device To Be Reached At http://esp32.local Instead Of Needing To Know Its IP Address
    if (MDNS.begin("esp32")) {
        Serial.println("MDNS responder started");
    }

    // Server routes
    //Links All Files To Main
    server.on("/inline", []() { server.send(200, "text/plain", "this works as well"); });
    server.on("/", []() { server.send(200, "text/html", homePagePart1); });
    server.on("/index.html", []() { server.send(200, "text/html", homePagePart1); });
    server.on("/home.css", []() { server.send(200, "text/css", homeCSS); });
    server.on("/dashData", handleDashboardData); // Returns Only Sensor Cards -- Not Full Page
    server.on("/dash", handleDashboard);
    server.on("/dash.html", handleDashboard);
    server.on("/dash.css", []() { server.send(200, "text/css", dashCSS); });
    server.on("/cont.html", []() { server.send(200, "text/html", contPagePart1); });
    server.on("/cont.css", []() { server.send(200, "text/css", contCSS); });
    server.on("/demo.html", []() { server.send(200, "text/html", demoPagePart1); });
    server.on("/demo.css", []() { server.send(200, "text/css", demoCSS); });
    server.on("/demo.js", []() { server.send(200, "application/javascript", demoJS); });

    //Saves Toggle Value Depending If ON / OFF
    //Updates Boolean Globals
    server.on("/saveSettings", []() {
        if (server.hasArg("light")) {
            lightToggle = server.arg("light").toInt() == 1;
        }
        if (server.hasArg("fan")) {
            fanToggle = server.arg("fan").toInt() == 1;
        }
        if (server.hasArg("sound")) {
            buzzerToggle = server.arg("sound").toInt() == 1;
        }
        if (server.hasArg("vibration")) {
            vibrationToggle = server.arg("vibration").toInt() == 1;
        }
        server.send(200, "text/plain", "Settings Saved");
    });

    //Saves Alarm Time
    //Reads Hour / Minute Parameters
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
    message += "URI: " + server.uri();
    message += "\nMethod: " + String((server.method() == HTTP_GET) ? "GET" : "POST");
    message += "\nArguments: " + String(server.args()) + "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

//--------------------------------------- LED -----------------------------------------------------//
//Triggers LED When Toggle Is On AND Alarm Is Active
void handleAlarmLED() {
    if (!alarmTriggered || !lightToggle) {
        digitalWrite(LED, LOW);
        return;
    }

//Non-Blocking Blink Using 'millis()' | 'delay()' Would Freeze The Server & The Sensors
//Checks If 'blinkInterval' (2000ms) Has Elapsed, Then Toggles LED State    
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= blinkInterval) {
        ledState = !ledState;
        digitalWrite(LED, ledState ? HIGH : LOW);
        lastBlinkTime = currentMillis;
    }
}
//--------------------------------------- BUZZER -----------------------------------------------------//
//Triggers BUZZER When Toggle Is On AND Alarm Is Active
void handleAlarmBuzzer() {
    if (!alarmTriggered || !buzzerToggle) {
        analogWrite(BUZZER_PIN, 0);     //Silence Buzzer If Not Active
        buzzerTriggered = false;
        return;
    }

    if (!buzzerTriggered) {
        //analogWrite Sends PWM Signal. Value = 128 -> 50% Duty Cycle -> Controls Volume / textContent
        //digitalWrite Would Only Be Full On Or Full Off With No Volume Control
        analogWrite(BUZZER_PIN, 128);
        buzzerTriggered = true;
        buzzerEnd = millis() + alarm_duration;
    }
    if (buzzerTriggered && millis() >= buzzerEnd) {
        analogWrite(BUZZER_PIN, 0);
        buzzerTriggered = false;
    }
}

//--------------------------------------- FAN -----------------------------------------------------//
//Triggers FAN When Toggle Is On And Alarm Is Active
void handleAlarmFan() {
    if (!alarmTriggered || !fanToggle) {
        digitalWrite(FAN_PIN, LOW);
        return;
    }
    if (currentTemp <= 20) {
        digitalWrite(FAN_PIN, LOW);
    }
    else {
        digitalWrite(FAN_PIN, HIGH);
    }
}

//--------------------------------------- VIBRATION -----------------------------------------------------//
//Triggers VIBRATION When Toggle Is On And Alarm Is Active
void handleAlarmVibration() {
//Checks Both Flags With A Ternary | If alarmTriggered && vibrationToggle Are tue -> HIGH, false -> LOW
    digitalWrite(VIBRATION_PIN, (alarmTriggered && vibrationToggle) ? HIGH : LOW);
}

void loop() {
    unsigned long currentTime = millis();
    //Must Be Called Every Loop: Processes Any HTTP Requests From The Browser
    server.handleClient();

    readDHT(currentTime);
    checkPIR(currentTime);
    checkLDR();
    checkSound(currentTime);

    //Gets Real Time 
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        int currentHour = timeinfo.tm_hour;
        int currentMinute = timeinfo.tm_min;

        // Trigger Alarm At Set Time - When Input Time = Real Time
        if (!alarmTriggered && currentHour == alarmHour && currentMinute == alarmMinute) {
            alarmTriggered = true;  // Flag Prevents Re-Triggering During The Same Minute
            alarmStartTime = millis();
            Serial.println("ALARM TRIGGERED");
        }

        // Handle All Alarm Devices
        if (alarmTriggered) {
            handleAlarmLED();           // Only Fires If lightToggle Is true
            handleAlarmBuzzer();        // Only Fires If buzzerToggle Is true
            handleAlarmFan();           // Only Fires If fanToggle Is true & currentTemp > 20 C
            handleAlarmVibration();     // Only Fires If vibrationToggle Is true
        }

        // End Alarm After Duration - All Outputs Set To OFF
        if (alarmTriggered && (millis() - alarmStartTime >= alarm_duration)) {
            alarmTriggered = false;
            buzzerTriggered = false;
            digitalWrite(LED, LOW);
            digitalWrite(FAN_PIN, LOW);
            digitalWrite(VIBRATION_PIN, LOW);
            analogWrite(BUZZER_PIN, 0);
            Serial.println("ALARM ENDED: SENSORS OFF");
        }
    }
    static unsigned long lastUpdate = 0;

    if (millis() - lastUpdate > 20000) {
        // ThingSpeak Updates Every 20s With Temp, Humi, Light, Sound & Motion Data
        if (WiFi.status() ==  WL_CONNECTED) {
            ThingSpeak.setField(1, currentTemp);
            ThingSpeak.setField(2, currentHumi);
            ThingSpeak.setField(3, analogRead(LDR_SENSOR));
            ThingSpeak.setField(4, analogRead(SOUND_PIN));
            ThingSpeak.setField(5, (state == HIGH) ? 1 : 0);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (x == 200) {
        Serial.println("ThingSpeak OK");
    } else {
        Serial.println("ThingSpeak error: " + String(x));
    }
        }
    lastUpdate = millis();
    }
}

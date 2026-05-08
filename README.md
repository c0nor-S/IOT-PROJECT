SmartRise
A smart alarm clock built on the ESP32 that wakes you up using light, sound and vibration through a webpage hosted on the microcontroller.

About
SmartRise is an IOT alarm clock designed to make waking up less abrupt. Instead of a single loud alarm, it lets the user choose which wake-up methods to use and combines them for a gentler start to the morning.
The device monitors the room environment in real time using four sensors and logs all data to ThingSpeak for cloud visualisation.

Features
-Set alarm time through webpage interface
-LED light alert
-Buzzer sound alert
-Vibration motor alert
-Live sensor dashboard — temperature, humidity, light, sound, motion
-ThingSpeak cloud logging every 20 seconds

Components
-ESP32
-DHT11
-PIR Sensor
-LDR
-Sound Sensor
-LED
-Buzzer
-Vibration Motor
-ULN2003A

Software
-C++
-HTML, CSS, JavaScript
-Arduino WebServer library
-ThingSpeak Arduino library
-DFRobot DHT11 library
-ESPmDNS

Web Interface
The ESP32 hosts a four-page web interface over Wi-Fi
-Home - Navigation Page
-Dashboard - Live Sensor Readings, updates every 2 seconds
-Control Panel - Toggle Wake-Up Methods
-Demo - Set Alarm Time

Access at 'http://esp32.local', or IP Address

Author
Conor Shaughnessy
Bachelor of Software & Electronic Engineering
Atlantic Technological University, Galway
2025/2026

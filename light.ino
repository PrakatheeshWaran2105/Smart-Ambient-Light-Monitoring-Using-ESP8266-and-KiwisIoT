[3:57 am, 20/11/2026] prakatheesh2105: #include <ESP8266WiFi.h>
#include <KiwisIoT.h>

// WiFi credentials
const char* ssid = "wifi name";
const char* password = "wifi password";

// KiwisIoT Topic ID
const char* topic = "dash_1795216339016";

// Pin configuration
#define LDR_PIN A0
#define LED_PIN D5

// Adjust after checking Serial Monitor
int lightThreshold = 500;

// Change to false if your LDR value
// decreases when the surroundings get dark.
bool darkWhenHigh = true;

KiwisIoT kiwisiot(ssid, password, topic);

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  Serial.println("Smart Ambient Light Monitoring");

  kiwisiot.begin();
}

void loop() {

  kiwisiot.run();

  int lightValue = analogRead(LDR_PIN);

  bool isDark;

  if (darkWhenHigh) {
    isDark = (lightValue > lightThreshold);
  } else {
    isDark = (lightValue < lightThreshold);
  }

  if (isDark) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("STATUS: LOW LIGHT");
  } else {
    digitalWrite(LED_PIN,
[3:57 am, 20/11/2026] prakatheesh2105: Serial.println("STATUS: BRIGHT LIGHT");
  }

  // Send light value to KiwisIoT
  kiwisiot.send("0", lightValue);

  // Send LED status
  kiwisiot.send("1", isDark ? 1 : 0);

  Serial.print("Light Sensor Value: ");
  Serial.println(lightValue);

  Serial.print("LED Status: ");
  Serial.println(isDark ? "ON" : "OFF");

  Serial.println("----------------------");

  delay(2000);
}

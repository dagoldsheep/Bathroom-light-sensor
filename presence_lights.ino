#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <arnavkeskar-project-1_inferencing.h>

static float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

#define RELAY_PIN 5

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -14400, 60000);

unsigned long lastPresenceTime = 0;
const unsigned long OFF_DELAY = 15000;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();
  int hour = timeClient.getHours();

  bool nightHours = (hour >= 20 || hour < 8);

  if (!nightHours) {
    digitalWrite(RELAY_PIN, LOW);
    return;
  }

  // REQUIRED: fill features[] before running the model
  for (int i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++) {
    features[i] = 0.0f;   // placeholder until real sensor data is added
  }

  signal_t signal;
  numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);

  ei_impulse_result_t result;
  run_classifier(&signal, &result, false);

  float noPresence = result.classification[0].value;
  float presence = result.classification[1].value;

  if (presence > noPresence) {
    lastPresenceTime = millis();
    digitalWrite(RELAY_PIN, HIGH);
  }

  if (millis() - lastPresenceTime > OFF_DELAY) {
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(100);
}

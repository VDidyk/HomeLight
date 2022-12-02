#include <WiFi.h>
#include <HTTPClient.h>

#define LED_GREEN 13
#define LED_RED 14

#define LED_GREEN 13
#define LED_RED 14

#define REQUEST "https://pimway.se/api/signal?api_token=kBA6DriHs7M2ya6L8o4Dbd7yz2DmyZUv"

char* ssid = "HUAWEI P30 Pro";
char* password = "2309196q";

class WiFiWorker {
public:
  void init() {
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    enableRed();

    connectToWiFi();
  }

  void enableGreen() {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
  }

  void enableRed() {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
  }

  void sendRequest() {
    HTTPClient http;

    http.begin(REQUEST);
    http.GET();
    http.end();
  }

  long doJob() {
    if (WiFi.status() == 3) {
      enableGreen();
    } else {
      enableRed();
    }

    long rssi = WiFi.RSSI();

    return rssi;
  }

  void connectToWiFi() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    }
  }
};
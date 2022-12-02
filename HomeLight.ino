#include "DisplayWorker.h"
#include "WiFiWorker.h"

short time_counter = 10;
DisplayWorker displayWorker;
WiFiWorker wifiWorker;

void setup() {
  Serial.begin(9600);

  wifiWorker.init();
  displayWorker.initDisplay();
}

void loop() {
  displayWorker.write(wifiWorker.doJob());

  delay(1000);

  if (time_counter >= 10) {
    wifiWorker.sendRequest();

    time_counter = 0;
  }

  time_counter++;
}
#include "DisplayWorker.h"
#include "WiFiWorker.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

short time_counter = 10;
DisplayWorker displayWorker;
WiFiWorker wifiWorker;

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);

  SerialBT.begin("HomeLight");  //Bluetooth device name

  wifiWorker.init();
  displayWorker.initDisplay();
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  displayWorker.write(wifiWorker.doJob());

  delay(1000);

  if (time_counter >= 10) {
    wifiWorker.sendRequest();

    time_counter = 0;
  }

  time_counter++;
}
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>  
#include <HTTPClient.h>

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int ledGreenPin = 13;
int ledRedPin = 14;

// const char* ssid = "tailer";
const char* ssid = "HUAWEI P30 Pro";
// const char* password = "2309196h0,0r0gq";
const char* password = "2309196q";
bool wifi_on = false;

String serverName = "https://pimway.se/api/signal?api_token=kBA6DriHs7M2ya6L8o4Dbd7yz2DmyZUv";

int time_counter = 10;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void connectToWiFi(){
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  }

  wifi_on = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);

  initDisplay();

  display.clearDisplay();
  display.display();
  
  enableRed();

  connectToWiFi();
}

void initDisplay(){
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

   //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void enableGreen(){
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledGreenPin, HIGH);
}

void enableRed(){
  digitalWrite(ledRedPin, HIGH);
  digitalWrite(ledGreenPin, LOW);
}

void write(long int text){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(25,15);
  display.println("Signal level:");

  
  display.setTextSize(3);
  display.setCursor(35,30);
  display.println(text);
  display.display();
}

void sendRequest(){
  HTTPClient http;

  http.begin(serverName.c_str());
  http.GET();
  http.end();
}

void loop() {
  if(WiFi.status() == 3){
    enableGreen();
  } else{
    enableRed();
  }

  long rssi = WiFi.RSSI();
  write(rssi);

  delay(1000);

  if(time_counter >= 10){
    sendRequest();

    time_counter=0;
  }

  time_counter++;
}
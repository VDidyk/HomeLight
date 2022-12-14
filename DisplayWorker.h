#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

class DisplayWorker {
public:
  void initDisplay() {
    //reset OLED display via software
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW);
    delay(20);
    digitalWrite(OLED_RST, HIGH);

    //initialize OLED
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) {  // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
      for (;;)
        ;  // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.setTextColor(WHITE);

    display.display();
  }

  void write(long text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(25, 15);
    display.println("Signal level:");

    display.setTextSize(3);
    display.setCursor(35, 30);
    display.println(text);
    display.display();
  }
};
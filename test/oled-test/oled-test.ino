#include <Wire.h>
#include  <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define address 0x3c
#define width 128
#define height 64
#define oled_reset -1
#define baudrate 115200

Adafruit_SSD1306 display(width, height, &Wire, oled_reset);

void setup() {
  Serial.begin(baudrate);
  if(!display.begin(SSD1306_SWITCHCAPVCC, address)) {
       Serial.println(F("SSD1306 allocation failed"));

        // todo: retry I2C scanner 
    } else {
        Serial.println("Screen found");
    }

  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(4, 4);  

  display.print("hELL0");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:

}

#define ENABLE_OLED

#ifdef ENABLE_OLED
#include "SSD1306.h"
#define OLED_ADDRESS 0x3c
#define I2C_SDA 21
#define I2C_SCL 22
SSD1306Wire display(OLED_ADDRESS, I2C_SDA, I2C_SCL);
#endif

#ifdef ENABLE_OLED
void printOled(char line, char *str) {
  display.drawString(0, line * 10, str);
  display.display();
}
void clearOled() {
  display.clear();
  display.display();
}
#endif

void setup() {
  Serial.begin(115200);
#ifdef ENABLE_OLED
  display.init();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
#endif
}

void loop() {
  delay(1000);
}

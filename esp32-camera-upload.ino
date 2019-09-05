#define ENABLE_OLED

#ifdef ENABLE_OLED
#include "SSD1306.h"
#define OLED_ADDRESS 0x3c
#define I2C_SDA 21
#define I2C_SCL 22
SSD1306Wire display(OLED_ADDRESS, I2C_SDA, I2C_SCL);
#endif

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    while (!Serial)
    {
        ;
    }

#ifdef ENABLE_OLED
    display.init();
//    display.flipScreenVertically();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
    
    display.display();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("AP MAC: \n");
  delay(1000);

}

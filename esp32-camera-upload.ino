#define ENABLE_OLED
#define ENABLE_CAMERA

#ifdef ENABLE_OLED
#include "SSD1306.h"
#define OLED_ADDRESS 0x3c
#define I2C_SDA 21
#define I2C_SCL 22
SSD1306Wire display(OLED_ADDRESS, I2C_SDA, I2C_SCL);
#endif
#ifdef ENABLE_CAMERA
#include "esp_camera.h"
#define Y9_GPIO_NUM         39
#define Y8_GPIO_NUM         36
#define Y7_GPIO_NUM         23
#define Y6_GPIO_NUM         18
#define Y5_GPIO_NUM         15
#define Y4_GPIO_NUM         4
#define Y3_GPIO_NUM         14
#define Y2_GPIO_NUM         5
#define VSYNC_GPIO_NUM      27
#define HREF_GPIO_NUM       25
#define PCLK_GPIO_NUM       19
#define PWDN_GPIO_NUM       26
#define XCLK_GPIO_NUM       32
#define SIOD_GPIO_NUM       13
#define SIOC_GPIO_NUM       12
#define RESET_GPIO_NUM      -1
#define BUTTON_1            34
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
  camera_fb_t * fb = NULL;

  Serial.begin(115200);
#ifdef ENABLE_OLED
  display.init();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
#endif
#ifdef ENABLE_CAMERA
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
      #ifdef ENABLE_OLED
      clearOled();
      printOled(0, "Camera init Failed");
      #else
      Serial.print("Camera init Failed");
      #endif
  }
#endif
  sensor_t *s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_QVGA);

  fb = esp_camera_fb_get();
    if (!fb) {
      #ifdef ENABLE_OLED
      clearOled();
      printOled(0, "Camera capture Failed");
      #else
      Serial.print("Camera capture Failed");
      #endif
    }
  #ifdef ENABLE_OLED
  clearOled();
  printOled(0, "Camera capture Complete");
  #endif
  Serial.println("Camera capture Complete");
  Serial.print(fb->len);

}

void loop() {
  delay(1000);
}

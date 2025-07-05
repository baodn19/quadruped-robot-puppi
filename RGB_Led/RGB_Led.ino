#include <Adafruit_NeoPixel.h>

#define RGB_PIN 26
#define RGB_BRIGHTNESS 255
#define NUMBER_LEDS 2

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(NUMBER_LEDS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void InitializeRGB() {
  matrix.begin();
  matrix.setBrightness(RGB_BRIGHTNESS);
  matrix.show();
}

void OnAllLED(byte green_input, byte red_input, byte blue_input) {
  for (int i = 0; i <= matrix.numPixels(); i++) {
    matrix.setPixelColor(i, matrix.Color(red_input, green_input, blue_input)); // Set to white
  }
  matrix.show();
}

void OnSingleLED(uint16_t led_index, byte green_input, byte red_input, byte blue_input) {
  matrix.setPixelColor(led_index, matrix.Color(red_input, green_input, blue_input));
  matrix.show();
}

void setup() {
  InitializeRGB();
}

void loop() {
  // All white lights
  OnAllLED(255, 255, 255);
  delay(1000);

  // Off all lights
  OnAllLED(0, 0, 0);
  delay(1000);

  // LED 0 red
  OnSingleLED(0, 0, 255, 0);
  delay(1000);
  OnSingleLED(0, 0, 0, 0); // Off LED 0

  // LED 1 blue
  OnSingleLED(1, 0, 0, 255);
  delay(1000);
  OnSingleLED(1, 0, 0, 0); // Off LED 1
}

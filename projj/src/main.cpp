#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "../lib/functions.h"
#include "../lib/my_library.h"
#include "../lib/RGB.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoPixel.h>

#define PIN            5   // Define the pin connected to the data input of WS2812
#define NUMPIXELS      8   // Number of WS2812 LEDs

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



void setSimpleGradientColor(uint8_t color) {
  for (int i = 0; i < pixels.numPixels(); i++) {
    uint8_t r, g, b;

    // Simple gradient: Red to Violet to Blue to Green to Yellow to Red
    if (color < 85) {
      r = 255 - color * 3;
      g = 0;
      b = color * 3;
    } else if (color < 170) {
      color -= 85;
      r = 0;
      g = color * 3;
      b = 255 - color * 3;
    } else {
      color -= 170;
      r = color * 3;
      g = 255 - color * 3;
      b = 0;
    }

    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}


void simpleGradientEffect() {
  for (int color = 0; color < 256; color++) {
    setSimpleGradientColor(color);
    delay(100);  // Adjust the delay for the desired gradient speed
  }
}
void setup() {
  pixels.begin();  // Initialize the NeoPixel library
}

void loop() {
  simpleGradientEffect();
}
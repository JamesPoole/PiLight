/////////////////////
//Author: James Poole
//Date: 10 October 2016
//jgaple@gmail.com
/////////////////////

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 6

int green_pin = 7;
int red_pin = 8;
int blue_pin = 9;

int greenVal = 0;
int redVal = 0;
int blueVal = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  pinMode(green_pin, INPUT);
  pinMode(red_pin, INPUT);
  pinMode(blue_pin, INPUT);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  
  greenVal = digitalRead(green_pin);
  redVal = digitalRead(red_pin);
  blueVal = digitalRead(blue_pin);
  
  if(greenVal == HIGH && redVal == LOW && blueVal == LOW)
    green();
  else if(greenVal == HIGH && redVal == HIGH && blueVal == LOW)
    yellow();
  else if(greenVal == HIGH && redVal == LOW && blueVal == HIGH)
    cyan();
  else if(greenVal == LOW && redVal == HIGH && blueVal == LOW)
    red();
  else if(greenVal == LOW && redVal == HIGH && blueVal == HIGH)
    purple();
  else if(greenVal == LOW && redVal == LOW && blueVal == HIGH)
    blue();
  else if(greenVal == HIGH && redVal == HIGH && blueVal == HIGH)
    rainbow(20);
  else
    off();
}

void blue() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(6,6,232));
    strip.show();
    delay(2);
  }
}

void red() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(244,6,20));
    strip.show();
    delay(2);
  }
}

void green() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(20,232,6));
    strip.show();
    delay(2);
  }
}

void yellow() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(239,232,6));
    strip.show();
    delay(2);
  }
}

void cyan() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(9,232,239));
    strip.show();
    delay(2);
  }
}

void purple() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(220,6,239));
    strip.show();
    delay(2);
  }
}

void off() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
    strip.show();
    delay(2);
  }
}

//////////////////////////////////////////////

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

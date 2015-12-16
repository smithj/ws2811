
#include <Adafruit_NeoPixel.h>

#define PIN 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(51, 8, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(1, 7, NEO_BRG + NEO_KHZ800);


void setup(){
  
  strip.begin();
  strip.show();
  strip2.begin();
  strip2.show();
  
  
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  
}

void loop() {
  
  for (int i=0; i<50; i++){
    
    strip.setPixelColor(i, 255,0,0);
  }
  
  strip.show();
  
  
  delay(400);
  
  for (int i=0; i<50; i++){
    
    strip.setPixelColor(i, 0,0,0);
  }
 
 strip.show(); 
  
}

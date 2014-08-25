#include <Adafruit_NeoPixel.h>

#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_BRG + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.








uint32_t baseColor = strip.Color(255, 0, 255);
uint32_t altColor = strip.Color(0,255,0);
   
int pause = 100;

unsigned int toggle = 0;


void setup() {
   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
   strip.setBrightness(255);
  
   for (unsigned int i=0; i<strip.numPixels(); i++){
      strip.setPixelColor(i, baseColor);
   }
   
   strip.show();  
  
   Serial.begin(9600);
  
}




void loop() {

  
/*
   for (unsigned int i=0; i<strip.numPixels(); i++){
      strip.setPixelColor(i, baseColor);
   }
   
   strip.show();  
*/  
   toggle++;
      
   
   
   for (unsigned int i=0; i<strip.numPixels(); i++){
/*     
      strip.setPixelColor(i, altColor);
      strip.show();
      delay(pause);
      strip.setPixelColor(i, baseColor);
      strip.show();
      
*/

      if ( ((i+toggle) % 2) == 0) {
         strip.setPixelColor(i, baseColor);
      }
      else{
         strip.setPixelColor(i, altColor);
      }
      
      
      Serial.print(i);
      Serial.print(" + ");
      Serial.print(toggle);
      Serial.print(" % 2 = ");
      
      Serial.println((i+toggle) % 2);
   }      
  
  
    strip.show();

    delay(pause);     

  
}


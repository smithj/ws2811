#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#define PIN 5


extern const uint8_t gamma[];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_BRG + NEO_KHZ800);


void setup() {

   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
   strip.setBrightness(64);



   Serial.begin(9600);

}


void loop(){

   int pixel = 0;

   for (int pos=0; pos<256; pos++){



      uint32_t maxb = 255;
      uint32_t color = Wheel(pos);
//      uint32_t adjColor = adjustBrightness(color, i);


      for (uint32_t i=0; i<strip.numPixels(); i++){

         //strip.setPixelColor(pixel++, adjColor);
         strip.setPixelColor(i, color);
            //strip.setPixelColor(1, i, 0, 0);
/*
         if ( pixel > 23 ) {
            pixel = 0;
         }
*/
//         Serial.println(pixel);
//         Serial.println(color);
//         Serial.print("adj bright: ");
//         Serial.println(adjColor);

      }

      strip.show();
      delay(50);


  //       delay(3000);


   }

}

uint32_t adjustBrightness(uint32_t color, uint32_t shift){

   Serial.print("shift: ");
   Serial.println(shift);

   uint32_t new_red = ((color >> 16)  & 0xFF) >> shift;
   uint32_t new_grn = ((color >> 8)  & 0xFF) >> shift;
   uint32_t new_blu = (color & 0xFF) >> shift;

   Serial.print("red: ");
   Serial.println(((color >> 16)  & 0xFF));
   Serial.print("new_red: ");
   Serial.println(new_red<<16);

   return (new_red << 16) + (new_grn << 8) + new_blu;



}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(pgm_read_byte(&gamma[WheelPos * 3]), pgm_read_byte(&gamma[255 - WheelPos * 3]), 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(pgm_read_byte(&gamma[255 - WheelPos * 3]), 0, pgm_read_byte(&gamma[WheelPos * 3]));
  } else {
   WheelPos -= 170;
   return strip.Color(0, pgm_read_byte(&gamma[WheelPos * 3]), pgm_read_byte(&gamma[255 - WheelPos * 3]));
  }
}


const uint8_t PROGMEM gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

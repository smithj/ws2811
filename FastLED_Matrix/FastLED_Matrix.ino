#include "FastLED.h"


#define NUM_LEDS 150
#define DATA_PIN 8


unsigned int width, height;

unsigned int viewport_quadrant, display_quadrant;

boolean zigzag;

// Define the array of leds
CRGB leds[NUM_LEDS];


void setup(){
  
   FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(leds, NUM_LEDS);
  
   width = 15;
   height = 10;
   
   viewport_quadrant = 1;
   display_quadrant = 4;
   
   zigzag = true;
   
   
   Serial.begin(9600);
   
}

void loop(){
   
  int y=0;
   for (int x=0; x<width; x++){
 //     for (int y=0; y<height; y++){
         int pixel_pos = find_pixel_pos(x,y++);
         if (pixel_pos < NUM_LEDS){
            leds[pixel_pos] = CRGB::Green;
         }
         else{
            Serial.println("index out of bounds");
         }
         FastLED.show();
         delay(500);
 //     }
    }
    
    
    while(1){}
 
}



int translate_x(int x){
   
   if ( (viewport_quadrant < 3) && (display_quadrant > 2) ){
      return -1 * (width - x - 1);
   }
   else{
      return x;
   }
  
}

int translate_y(int y){
   
   if ( ((viewport_quadrant == 1) || (viewport_quadrant == 4)) && 
        ((display_quadrant  == 2) || (display_quadrant  == 3))   ){
      return -1 * (height - 1 - y);
   }
   else{
      return y;
   }
        
}

unsigned int find_pixel_pos(int x, int y){
 
   unsigned int tx = abs(translate_x(x));
   unsigned int ty = abs(translate_y(y));

   

   
   unsigned int pixel_pos = ty * (width);


   Serial.print(x);
   Serial.print(":");
   Serial.print(tx);
   Serial.print("   y ");
   Serial.print(y);
   Serial.print(":");
   Serial.println(ty);
   Serial.println(pixel_pos);

   if (ty == 0){
      return tx;
   }   
   
   if (zigzag && ((ty % 2) != 0) ){
         return pixel_pos + (width - 1 - tx);
   }
   else{
      return pixel_pos + tx;
   }
}

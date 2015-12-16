#include <Adafruit_NeoPixel.h>



#define PIN 5

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_BRG + NEO_KHZ800);

#define PIXEL_FG_COLOR strip.Color(0,0,255)
#define PIXEL_BG_COLOR strip.Color(0,255,0)
#define PIXEL_BG2_COLOR strip.Color(255,0,0)


int ledR = 9;
int ledG = 11;
int ledB = 10;

int flashDuration = 200;

/*

PINS:
  3 - side of garege
  5 - front of garage
  6 - side of living room/front door
  
  9 - red
  10 - blue
  11 - green
  



*/



void setup() {
  Serial.begin(115200);
 
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);  
  pinMode(3, OUTPUT);  
  
  
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);

  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
  
  pinMode(4,OUTPUT);
  digitalWrite(4, LOW);


   // set eves to red. 
   analogWrite(9, 128);


   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
   strip.setBrightness(255);


}


void loop() {

   // blink();
   // climb();

   paint_background(0);

   strip.show();

   int low = 0;
   int high = strip.numPixels() - 1;

   int swap = 0;
   
   while (true){
      strip.setPixelColor(low, PIXEL_FG_COLOR);
      strip.setPixelColor(high, PIXEL_FG_COLOR);
      strip.setPixelColor(low+2, PIXEL_FG_COLOR);
      strip.setPixelColor(high-2, PIXEL_FG_COLOR);      strip.show();

      delay(80);


      if (low >= strip.numPixels()){
         low = 0;
         high = strip.numPixels() - 1;
      }

      if ((low % 10) == 0){
         if (++swap > 1){
            swap = 0;
         }
      }
      
      paint_background(swap);
      
      low++;
      high--;
   }
   

}


void paint_background(int swap){

      for (int i=0; i<strip.numPixels(); i++){
      set_bg_color(i, swap);
   }
}


void set_bg_color(int i, int swap){

      if ( ((i+swap) % 2) ==0){ 
         strip.setPixelColor(i, PIXEL_BG_COLOR);
      }
      else{
         strip.setPixelColor(i, PIXEL_BG2_COLOR);
      }
}

/**
 * 
 * turn on leds up from ends, meet in middle, then turn off from middle down
 * 
 */
void up_down(){
   int i = 0;
   int j = strip.numPixels() - 1;

   while (i < j){

      strip.setPixelColor(i, PIXEL_FG_COLOR);
      strip.setPixelColor(j, PIXEL_FG_COLOR);
      strip.show();
      delay (100);
      i++;
      j--;
   }


   while (i >= 0){

      strip.setPixelColor(i, PIXEL_BG_COLOR);
      strip.setPixelColor(j, PIXEL_BG_COLOR);
      strip.show();
      delay (100);
      i--;
      j++;
   }

   delay(500);

   
/*
   for (int i=0; i<50; i++){

      strip.setPixelColor(i, strip.Color(255,0,0));
   }

   strip.show();

   while (true);

*/


}


void climb(){

      
   for (int i=0; i<strip.numPixels(); i++){;
      strip.setPixelColor(i, 0,0,0); 
   }
 
   strip.show();



   for (int i=0; i<strip.numPixels()/2; i++){
      strip.setPixelColor(i, 0,0,255); 
      strip.setPixelColor(strip.numPixels() - i - 1, 0,0,255);
      if (i>1){
         strip.setPixelColor(i-1, 0,0,128); 
         strip.setPixelColor(strip.numPixels() - i - 1 + 1, 0,0,128);
         if (i>2){
            strip.setPixelColor(i-2, 0,0,64); 
            strip.setPixelColor(strip.numPixels() - i - 1 + 2, 0,0,64);
            if (i>3){
               strip.setPixelColor(i-3, 0,0,0); 
               strip.setPixelColor(strip.numPixels() - i - 1 + 3, 0,0,0);
            }
         }
      }
      strip.show();
      delay(200);
   }

   

   strip.show();



}

void blink(){

   int i=0;
   while ( i<strip.numPixels() ) {

//      Serial.println("in 1st loop");

      if (i%2 != 0){
         strip.setPixelColor(i, PIXEL_FG_COLOR);
         Serial.println("in 1st loop: FG");
      }
      else{
         strip.setPixelColor(i, PIXEL_BG_COLOR);
         Serial.println("in 1st loop BG");
      }
      i++; 
   }

   strip.show();


   Serial.println("1st loop");

   delay(1000);

   i=0;
   while ( i<strip.numPixels() ) {

      Serial.println("in 2nd loop");

      if (i%2 == 0){
         strip.setPixelColor(i, PIXEL_FG_COLOR);
      }
      else{
         strip.setPixelColor(i, PIXEL_BG_COLOR);
      }
      i++; 
   }

   strip.show();

   delay(1000);

}


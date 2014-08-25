
#include <Adafruit_NeoPixel.h>

#define PIN 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_RGB + NEO_KHZ800);

/* set up bitmaps for each digit
0  1111111111111111111111000 0x3fffff8
1  1111000000000000001111000 0x1e00078
2  0000111111100001111111111 0x1fc3ff
3  1111111000000001111111111 0x1fc03ff
4  1111000000011110001111111 0x1e03c7f
5  1111111000011111110000111 0x1fc3f87
6  1111111111111110000000111 0x1fffc07
7  1111000000000001111111000 0x1e003f8
8  1111111111111111111111111 0x1ffffff
9  1111000000011111111111111 0x1e03fff

A  1111000111111111111111111 0x1e3ffff
b  1111111111111110000000111 0x1fffc07
C  0000111111111111110000000 0x01fff80
d  1111111111100000001111111 0x1ffc07f
E  0000111111111111110000111 0x01fff87
F  0000000111111111110000111 0x003ff87

*/


unsigned long digits[] = {0x3fffff8,
                          0x1e00078, 
                          0x1fc3ff, 
                          0x1fc03ff, 
                          0x1e03c7f, 
                          0x1fc3f87, 
                          0x1fffc07, 
                          0x1e003f8, 
                          0x1ffffff, 
                          0x1e03fff, 
                          0x1e3ffff, 
                          0x1fffc07, 
                          0x01fff80,
                          0x1ffc07f, 
                          0x01fff87,
                          0x003ff87 };

byte* numbers[10];
  
byte number0[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
byte number1[] = {3,4,5,6,21,22,23,24};
byte number2[] = {9,8,7,6,5,4,3,2,1,0,14,15,16,17,18,19,20};
  

void setup() {
   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
   strip.setBrightness(64);
  
   for (int i=0; i<strip.numPixels(); i++){
     strip.setPixelColor(i, 0);
   }
   
   numbers[0] = number0;
   numbers[1] = number1;
   numbers[2] = number2;




   Serial.begin(9600);
   
}


void loop() {

  
  while(true){
    
     int countWait = 50;
     count(strip.Color(255,0,0), countWait);
     delay(2000);
     clearNumber();
     count(strip.Color(0,255,0), countWait);
     delay(2000);
     clearNumber();
     count(strip.Color(0,0,255), countWait);
     delay(2000);
     

  }
}

void clearNumber(){
   for (int i=0; i<strip.numPixels(); i++){
      strip.setPixelColor(i, 0);
   }
}


void count(uint32_t color, int waitTime){

  for (int i=0; i<16; i++){
     displayNumber(i, color, 0);
     
     for (int j=0; j<16; j++){
        displayNumber(j, color, 1);
        delay(waitTime);
     }
     
    
     delay(waitTime);
  }
  
}
    

void displayNumber(int num, uint32_t color, int place){
  
    
  Serial.print("bitwise: ");
  Serial.print(color);
  
  for (int i=0; i<25; i++){
    
    unsigned long mask = 1L << i;
    
    Serial.print(i);
    Serial.print(":");
    if (digits[num] & mask){
      Serial.println("on");
      strip.setPixelColor(i+(25*place), color);
    }
    else{
      Serial.println("off");
      strip.setPixelColor(i+(25*place), 0);      
    }
    
    strip.show();

    Serial.println();
    
  }
}
  

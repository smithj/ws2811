#include <Adafruit_NeoPixel.h>

#define PIN 8


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_BRG 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(50, 5, NEO_BRG + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  analogWrite(9,0);
  analogWrite(10,64);
  analogWrite(11,0);
  
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(64);
  
  strip2.begin();
  strip2.show();
  strip2.setBrightness(64);
  
  for (unsigned int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0);
  }
  
  Serial.begin(115200);
  
}

int wait_time_ms = 30;
uint32_t led_color = strip.Color(0,64,255);


void loop() {

/*  
   for (unsigned int i=19; i<strip.numPixels(); i++){
      
      strip.setPixelColor(i, led_color);
      strip.show();
      delay(wait_time_ms);
      
      strip.setPixelColor(i, 0);
      strip.show();
      
      check_serial();  

   }

   for (unsigned int i=strip.numPixels()-1; i>19; i--){
      
      strip.setPixelColor(i, led_color);
      strip.show();
      delay(wait_time_ms);
      
      strip.setPixelColor(i, 0);
      strip.show();
      
      check_serial();  

   }
*/

  check_serial();
  
}


String readString = "";

void check_serial(){
    while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill 
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    } 
  }

  if (readString.length() >0) {
      
    String command = readString.substring(0,6);
    command.toUpperCase();
    String cmd_data = readString.substring(7);
    
      if (command.equals("SETCOL")) {
  
         Serial.println(cmd_data);
  
         // just create the 24-bit color on the sending end       
         led_color = cmd_data.toInt();
         
         Serial.print("Color set to ");
         Serial.print(cmd_data.toInt());
         Serial.print("ms.");      
       
      }
      else if (command.equals("SETPWR")) {
        
        Serial.print("Turning LED brightness to '");
        Serial.print(cmd_data);
        Serial.println("'");
        
        strip.setBrightness(cmd_data.toInt());

      }
      else if (command.equals("SETDLY")) {
        
         Serial.println(cmd_data);
         
         wait_time_ms = cmd_data.toInt();
         
         Serial.print("Delay set to ");
         Serial.print(cmd_data.toInt());
         Serial.print("ms.");
         
        
      }
      else{
        
        Serial.print("Invalid command sent: ");
        Serial.println(readString);
      }
      
      
    // update all pixels to the new color  
    for (unsigned int i=0; i<strip.numPixels(); i++){
        strip.setPixelColor(i, led_color);
        strip.show();
    }

    for (unsigned int i=0; i<strip2.numPixels(); i++){
        strip2.setPixelColor(i, led_color);
        strip2.show();
    }
    
    setPWMColor(10, 9, 11, led_color);

    readString="";
  } 
  
  
}


void setPWMColor(byte redPin, byte greenPin, byte bluePin, uint32_t newColor){
 
   byte redValue = (newColor >> 16)  & 255;
   byte greenValue = (newColor >> 8) & 255;
   byte blueValue = newColor & 255;
   
   Serial.print("red: ");
   Serial.println(redValue);
   Serial.print("green: ");
   Serial.println(greenValue);
   Serial.print("blue: ");
   Serial.println(blueValue);
 
   analogWrite(redPin, redValue);
   analogWrite(greenPin, greenValue);
   analogWrite(bluePin, blueValue);
  
  
}
  
  

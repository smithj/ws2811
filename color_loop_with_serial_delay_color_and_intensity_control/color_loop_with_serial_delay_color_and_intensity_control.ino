#include <Adafruit_NeoPixel.h>

#define PIN 8


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_BRG + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
  
  for (unsigned int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0);
  }
  
  Serial.begin(9600);
  
}

int wait_time_ms = 30;
uint32_t led_color = strip.Color(0,64,255);


void loop() {
   
   for (unsigned int i=19; i<strip.numPixels(); i++){
      
      strip.setPixelColor(i, led_color);
      strip.show();
      delay(wait_time_ms);
      
      strip.setPixelColor(i, 0);
      strip.show();
      
      check_serial();  

   }

   
  
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
        
        char hex_digits[7];
        hex_digits[6] = '\0';
        
        String hex_string = "0x";
        hex_string.concat(cmd_data);
        Serial.println(hex_string);
        Serial.println(hex_string.toInt());
        
        
        hex_string.toCharArray(hex_digits, 7);
        
        Serial.println(hex_digits);
        
        Serial.print("setting color to: ");
        Serial.println(strtoul(hex_digits, NULL, 0));
        
      }
      else if (command.equals("SETPWR")) {
        
        Serial.print("Turning LEDs '");
        Serial.print(cmd_data);
        Serial.println("'");

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
      


    readString="";
  } 
  
  
}


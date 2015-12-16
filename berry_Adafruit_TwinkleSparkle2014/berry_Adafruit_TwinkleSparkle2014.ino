//TwinkleSparkle updated with bg color and on/off control on berry.





//  TwinkleSparkle2014 is a program that lets you make an LED strip
//  "twinkle" all the time and "sparkle" at a defined interval
//
//  Daniel Wilson, 2014
//
//  With BIG thanks to the FastLED community and especially Mark
//  Kriegsman whose "Fire2012" simulation inspired this program.
//  Some of Mark's original code and comments persist in this work.
///////////////////////////////////////////////////////////////////////////////////////////

#include <Adafruit_NeoPixel.h>
#include <pixeltypes.h>
#include <colorutils.h>



#define DEBUG              true     // send debug info out serial port



#define NUM_LEDS           50
#define DATA_PIN           8
#define COLOR_ORDER        BRG       // and RBG order
#define BRIGHTNESS         128
#define FRAMES_PER_SECOND  30
#define COOLING            5         // controls how quickly LEDs dim
#define TWINKLING          6       // controls how many new LEDs twinkle
#define FLICKER            50        // controls how "flickery" each individual LED is



#define twelve_volt_power    2
#define on_off_control_pin   13



static int beatInterval =  8912;     // the interval at which you want the strip to "sparkle"
long nextBeat =            0;
long nextTwinkle =         3000;     // twinkling doesn't start until after the sanity check delay
unsigned int seeds =       0;
long loops =               0;
long deltaTimeTwinkle =    0;
long deltaTimeSparkle =    0;
boolean beatStarted =      false;

static byte heat[NUM_LEDS];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, 8, NEO_BRG + NEO_KHZ800);

void lightsOn(){
 
   digitalWrite(twelve_volt_power, HIGH); 
  
}

//

void lightsOut(){

   analogWrite(9, 0);  // red
   analogWrite(10, 0);
   analogWrite(11, 0);
   strip.clear();
   strip.show();
   
   digitalWrite(twelve_volt_power, LOW);
  
}
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
   // sanity check delay - allows reprogramming if accidently blowing power w/leds
   delay(3000);
  
   strip.begin();
   strip.show();
  
   strip.setBrightness(128);
  
   Serial.begin(115200);
   delay(100);
   Serial.flush();
   while ( Serial.available() ) Serial.read(); // this helps to clear out any junk in the UART
  
   // turn on xbox ps 12V rail
   pinMode(twelve_volt_power, OUTPUT);
   digitalWrite(twelve_volt_power, HIGH);
  
  
   // set static bg color for RGB strips
   pinMode(9,OUTPUT);
   analogWrite(9,128);
  
  
   // define on/off control pin as input
   pinMode(on_off_control_pin, INPUT);
  
     
   if (DEBUG) {
      Serial.begin(9600);
   }
   
   
}

// Vocablulary lesson:
//   Twinkling - when individual LEDs "ignite" then slowly burn out
//   Sparkling - when a whole mess of LEDs "ignite" at the same time then burn out
//   Flickering - when a lit led modulates it brightness to simulate the flicker of a flame

void loop(){
  
   int lights_on = digitalRead(13);

   if (DEBUG) {
      Serial.println("Light control pin: " + lights_on);
   }
  
   if (lights_on == HIGH){
      if (DEBUG) {
         Serial.println("Lights on...");
      }
    
   lightsOn();
      
  
     // Wait for something in the serial monitor before "Sparkling" the first time.
     // This lets you time the sparkle to a particular beat in music.
     // In practice, just type a letter into the serial monitor and press enter
     // when you want the first sparkle to start.

     if (loops == 0 && !Serial.available()) {
        nextBeat = millis();
     }
     else {
        if (loops == 0 && beatStarted == false) {
           nextBeat = millis();
           beatStarted == true;
           Sparkle();
         }
         else {
            long deltaTimeSparkle = millis() - nextBeat;
            if ( deltaTimeSparkle > 0 ) Sparkle(); // if more time than 
         }
     }

     deltaTimeTwinkle = millis() - nextTwinkle;
     if ( deltaTimeTwinkle > 0 ) {
         Twinkle();
     }
     strip.show(); // display this frame
     
   }
   else{
      lightsOut();

      if (DEBUG) {
         Serial.println("Lights out. Sleeping...");
      }

      delay(10000);
     
     
   }
}


// This Twinkle subroutine creates a slow "twinkling" of the strip. 
// It uses the same "heating" methodology as Mark Kriegman's "Fire2012" 
// where pixels are "heated" and "cooled" and then the tempreature of 
// each pixel is mapped to a color and brightness. 

void Twinkle() 
{
  // Step 1. Create a randome number of seeds
  random16_add_entropy( random()); //random8() isn't very random, so this mixes things up a bit
  seeds = random8(10,NUM_LEDS-10);

  // Step 2. "Cool" down every location on the strip a little
  for( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i], COOLING);
  }

  // Step 3. Make the seeds into heat on the string
  for ( int j = 0 ; j < seeds ; j++) {
    if (random16() < TWINKLING) {
      //again, we have to mix things up so the same locations don't always light up
      random16_add_entropy( random()); 
      heat[random8(NUM_LEDS)] = random8(50,255);
    }
  }

  // Step 4. Add some "flicker" to LEDs that are already lit
  //         Note: this is most visible in dim LEDs
  for ( int k = 0 ; k < NUM_LEDS ; k++ ) {
    if (heat[k] > 0 && random8() < FLICKER) {
      heat[k] = qadd8(heat[k] , 10);
    }
  }

  // Step 5. Map from heat cells to LED colors
  for( int j = 0; j < NUM_LEDS; j++) 
  {
    
    CRGB pixel_color = HeatColor(heat[j]);
    
    strip.setPixelColor(j, pixel_color);
  




  }
  nextTwinkle += 1000 / FRAMES_PER_SECOND ; // assign the next time Twinkle() should happen
}

// Sparkle works very much like Twinkle, but with more LEDs lighting up at once
void Sparkle() {
  // Step 1. Make a random numnber of seeds
  seeds = random8(NUM_LEDS - 20 ,NUM_LEDS);

  // Step 2. Increase the heat at those locations
  for ( int i = 0 ; i < seeds ; i++) {
    {
      int pos = random8(NUM_LEDS);
      random16_add_entropy( random());
      heat[pos] = random8(50,255);
    }
  }
  nextBeat += beatInterval; // assign the next time Twinkle() should happen
  loops++ ;
}

/*
//Play with this for different strip colors
CHSV HeatColor( uint8_t temperature)
{
  CHSV heatcolor;
  heatcolor.hue = 129; 
  heatcolor.saturation = 200; 
  heatcolor.value = temperature; 
  return heatcolor;
}
*/
// Use Mark Krigsman's orignal "HeatColor" code if you want to 
// get different colors at differet "temperatures"
/*
CRGB HeatColor( uint8_t temperature)
 {
 CRGB heatcolor;
 
 // Scale 'heat' down from 0-255 to 0-191,
 // which can then be easily divided into three
 // equal 'thirds' of 64 units each.
 uint8_t t192 = scale8_video( temperature, 192);
 
 // calculate a value that ramps up from
 // zero to 255 in each 'third' of the scale.
 uint8_t heatramp = t192 & 0x3F; // 0..63
 heatramp <<= 2; // scale up to 0..252
 
 // now figure out which third of the spectrum we're in:
 if( t192 & 0x80) {
 // we're in the hottest third
 heatcolor.r = 255; // full red
 heatcolor.g = 255; // full green
 heatcolor.b = heatramp; // ramp up blue
 
 } else if( t192 & 0x40 ) {
 // we're in the middle third
 heatcolor.r = 255; // full red
 heatcolor.g = heatramp; // ramp up green
 heatcolor.b = 0; // no blue
 
 } else {
 // we're in the coolest third
 heatcolor.r = heatramp; // ramp up red
 heatcolor.g = 0; // no green
 heatcolor.b = 0; // no blue
 }
 
 return heatcolor;
 }
 */


String readString = "";



void setup(){
 
 Serial.begin(9600); 
  
}


void loop(){
  
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
      
      else{
        
        Serial.print("Invalid command sent: ");
        Serial.println(readString);
      }
      


    readString="";
  } 
  
}

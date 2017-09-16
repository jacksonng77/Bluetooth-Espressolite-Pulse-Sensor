//REFERENCE:
//  https://arduino.stackexchange.com/questions/35684/my-hm-10-bluetooth-module-only-returns-ok-after-any-at-command
//  http://www.martyncurrey.com/hm-10-bluetooth-4ble-modules/

#include <SoftwareSerial.h>
#include <ESPert.h>

ESPert espert;
SoftwareSerial mySerial(12, 14); // RX, TX 
 
void setup() {  
  espert.init();
  espert.oled.init();
  delay(2000);
  espert.oled.clear();
  espert.oled.setTextSize(5);
  espert.oled.setTextColor(ESPERT_WHITE);

  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {  
  
  char c;
  String command = "";
             
  if (Serial.available()) {
    c = Serial.read();
    mySerial.print(c);
  }
  if (mySerial.available()) {

    while(mySerial.available()) 
    {
      delay(10); 
      c = mySerial.read(); 
      command += c; 
    } 
    espert.oled.clear();
    espert.oled.setCursor(0, 0);
    espert.oled.println(command);
    espert.oled.update();
    command = ""; 
  }
}

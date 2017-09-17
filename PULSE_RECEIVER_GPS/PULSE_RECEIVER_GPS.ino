#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESPert.h>

static const int RXPin = 13, TXPin = 15; //rx 13 tx 15 rx
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;
ESPert espert;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial mySerial(12, 14); // RX, TX 

void setup()
{

  espert.init();
  espert.oled.init();
  delay(2000);
  espert.oled.clear();
  espert.oled.setTextSize(5);
  espert.oled.setTextColor(ESPERT_WHITE);
  
  Serial.begin(9600);
  ss.begin(GPSBaud);
  mySerial.begin(9600);

}

void loop()
{
  char c;
  String command = "";
  espert.oled.clear();
  espert.oled.setCursor(0, 0);
    
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

    espert.oled.print("BPM:");
    espert.oled.println(command);
    command = ""; 
  }
    
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    //while(true);
  }

  espert.oled.update();
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);

    espert.oled.print(gps.location.lat(), 6);
    espert.oled.print(F(","));
    espert.oled.println(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}

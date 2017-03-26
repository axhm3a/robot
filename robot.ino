#include <Ultrasonic.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);
Ultrasonic ultrasonic(7);

String command;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  mySerial.begin(9600);
  while (!mySerial) {
    ;
  }
  SeeedOled.init();
  SeeedOled.clearDisplay();
  SeeedOled.setNormalDisplay();
  SeeedOled.setPageMode();

  mySerial.println("AT+CIPMUX=1");
  delay(500);
  mySerial.println("AT+CIPSERVER=1,23");
  delay(500);
  Serial.println("booted...");
}
void loop()
{  
  rangeDetection();
  //serialPassTrough();
  readWifi();
  delay(500);
}

void readWifi() 
{
  while (mySerial.available()) {
    char c = mySerial.read();
    command += c;
  }

  command.trim();
  
  if(command.indexOf(":") != -1) {
    command = command.substring(command.indexOf(":") +1);

    if(command.startsWith("#"))
    {
      SeeedOled.setTextXY(2,0);
      for (int i = 1; i < command.length(); i++) {
        SeeedOled.putChar(command.charAt(i));  
      }  
    }
    
    
  }
  
 
  command = "";
}




void serialPassTrough()
{
  while (mySerial.available()) {
    Serial.write(mySerial.read());
    SeeedOled.setTextXY(7,0);
    SeeedOled.putString("[RX]");
  }
  SeeedOled.setTextXY(7,0);
  SeeedOled.putString("[  ]");
  
  while (Serial.available()) {
    mySerial.write(Serial.read());
    SeeedOled.setTextXY(7,5);
    SeeedOled.putString("[TX]");
  }

  SeeedOled.setTextXY(7,5);
  SeeedOled.putString("[  ]");
}

void rangeDetection()
{
  ultrasonic.MeasureInCentimeters();
  SeeedOled.setTextXY(1,0);
  //SeeedOled.clearDisplay();
  SeeedOled.putString("DST:     cm");
  SeeedOled.setTextXY(1,5);
  SeeedOled.putNumber(ultrasonic.RangeInCentimeters);
}


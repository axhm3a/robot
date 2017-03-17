#include <Ultrasonic.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);
Ultrasonic ultrasonic(7);
void setup()
{
  Wire.begin();
  SeeedOled.init();

  SeeedOled.clearDisplay();
  SeeedOled.setNormalDisplay();
  SeeedOled.setPageMode();
  SeeedOled.setTextXY(0,0);  
  SeeedOled.putString("booting");
  Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  mySerial.begin(115200);
  Serial.println("booted...");
}
void loop()
{
 
  ultrasonic.MeasureInCentimeters();
  SeeedOled.setTextXY(1,0);
  //SeeedOled.clearDisplay();
  SeeedOled.putNumber(ultrasonic.RangeInCentimeters);
  SeeedOled.putString(" cm   ");
  
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

  
  delay(1000);
}

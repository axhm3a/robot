#include <Ultrasonic.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);
Ultrasonic ultrasonic(7);
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  mySerial.begin(115200);
  
  SeeedOled.init();
  SeeedOled.clearDisplay();
  SeeedOled.setNormalDisplay();
  SeeedOled.setPageMode();
  SeeedOled.setTextXY(0,0);  
  SeeedOled.putString("booted");
  Serial.println("booted...");
}
void loop()
{  
  rangeDetection();
  serialPassTrough();

  delay(500);
}

void serialPassTrough()
{
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
  while (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void rangeDetection()
{
  ultrasonic.MeasureInCentimeters();
  SeeedOled.setTextXY(1,0);
  //SeeedOled.clearDisplay();
  SeeedOled.putNumber(ultrasonic.RangeInCentimeters);
  SeeedOled.putString(" cm   ");
}


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void displayCalStatus(void) {  
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */ 
  /* 3 means 'fully calibrated" */  
  uint8_t system, gyro, accel, mag;  
  system = gyro = accel = mag = 0;  
  bno.getCalibration(&system, &gyro, &accel, &mag);
  /* The data should be ignored until the system calibration is > 0 */  
  Serial.print("\t");  
  if (!system)  {    
    Serial.print("! ");  
    }
  /* Display the individual values */  
  Serial.print("Sys:");  
  Serial.print(system, DEC);  
  Serial.print(" G:");  
  Serial.print(gyro, DEC);  
  Serial.print(" A:");  
  Serial.print(accel, DEC);  
  Serial.print(" M:");  
  Serial.println(mag, DEC); 
}

void setup(void) 
{
  Serial.begin(115000);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  displayCalStatus();
  delay(1000);

  bno.setExtCrystalUse(true);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);

  if (false) {
    displayCalStatus();  // will auto cal staying still on G (gyro), but needs a little motion in all axis to cal M (magnetic compass).  A did not cal.
  } else {
    /* Display the floating point data */
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.print(event.orientation.z, 4);
    Serial.println("");
  displayCalStatus();
  }

  
  delay(100);
}


/******************************************************************************
  SparkFun_MS5803_Demo.ino
  Demo Program for MS5803 pressure sensors.
  Casey Kuhns @ SparkFun Electronics
  7/20/2014
  https://github.com/sparkfun/MS5803-14BA_Breakout/

  The MS58XX MS57XX and MS56XX by Measurement Specialties is a low cost I2C pressure
  sensor.  This sensor can be used in weather stations and for altitude
  estimations. It can also be used underwater for water depth measurements.

  Resources:
  This library uses the Arduino Wire.h to complete I2C transactions.

  Development environment specifics:
	IDE: Arduino 1.0.5
	Hardware Platform: Arduino Pro 3.3V/8MHz
	T5403 Breakout Version: 1.0

**Updated for Arduino 1.8.8 5/2019**

  This code is beerware. If you see me (or any other SparkFun employee) at the
  local pub, and you've found our code helpful, please buy us a round!

  Distributed as-is; no warranty is given.
******************************************************************************/

#include <Wire.h>
#include <SparkFun_MS5803_I2C.h> // Click here to get the library: http://librarymanager/All#SparkFun_MS5803-14BA

// Begin class with selected address
// available addresses (selected by jumper on board)
// default is ADDRESS_HIGH

//  ADDRESS_HIGH = 0x76
//  ADDRESS_LOW  = 0x77

MS5803 sensor(ADDRESS_HIGH);
double total = 0.0;
//Create variables to store results
float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;
double baseline = 0.0;
// Create Variable to store altitude in (m) for calculations;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)
void ring() {
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}
void ringBaseline(){
  for(int i = 0; i < 10; i++){
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}
}
void pressureBaseline(){
  pressure_baseline = sensor.getPressure(ADC_4096);
  delay(50);
  for(int i = 0; i < 10; i++) {
    baseline = sensor.getPressure(ADC_4096);
    delay(50);
    total = total + baseline;
  }
  pressure_baseline = total/10;
  Serial.print("BaselinePressure = ");
  Serial.println(pressure_baseline);
  ringBaseline();
}
void setup() {
  // Start your preferred I2C object
  Wire.begin();
  //Initialize Serial Monitor
  Serial.begin(9600);
  //Retrieve calibration constants for conversion math.
  sensor.reset();
  sensor.begin();
  pinMode(10, OUTPUT);
  pressureBaseline();

}

void loop() {

  // To measure to higher degrees of precision use the following sensor settings:
  // ADC_256
  // ADC_512
  // ADC_1024
  // ADC_2048
  // ADC_4096

  // Read temperature from the sensor in deg C. This operation takes about
  temperature_c = sensor.getTemperature(CELSIUS, ADC_512);

  // Read temperature from the sensor in deg F. Converting
  // to Fahrenheit is not internal to the sensor.
  // Additional math is done to convert a Celsius reading.
  temperature_f = sensor.getTemperature(FAHRENHEIT, ADC_512);

  // Read pressure from the sensor in mbar.
  pressure_abs = sensor.getPressure(ADC_4096);
  if ((pressure_abs - pressure_baseline) > 4) {
    ringBaseline();
  }
  // Let's do something interesting with our data.

  Serial.print("Temperature C = ");
  Serial.println(pressure_abs - pressure_baseline);

  Serial.print("Temperature F = ");
  Serial.println(temperature_f);

  Serial.print("Pressure abs (mbar)= ");
  Serial.println(pressure_abs);
Serial.print("BaselinePressure = ");
  Serial.println(pressure_baseline);
 
  
  delay(10);

}


// Thanks to Mike Grusin for letting me borrow the functions below from
// the BMP180 example code.

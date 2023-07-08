#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

int MAX_GYROSCOPE_TILT_VALUE_po = 5000; //I'm assuming that both are like positive(right) and negative(left), else we can shift them ig.
int MAX_GYROSCOPE_TILT_VALUE_ne = -5000;
int GYROSCOPE_ZERO=0;
int Some_specific_Angle_at_which_one_turns=4000;

int Gyrovalue;
int Accvalue;

int RX_PIN=0;
int TX_PIN=1;

#include<SoftwareSerial.h>

SoftwareSerial Master_BTDevice(RX_PIN,TX_PIN);

int flag_turns_master;//Left=3.Right=1.Nothing=0

void setup() 
{
  
  
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Wire.begin();
  Serial.begin(9600);
  Master_BTDevice.begin(9600);
}

void loop() {

Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  
  accelerometer_x = Wire.read()<<8 | Wire.read(); 
  accelerometer_y = Wire.read()<<8 | Wire.read();
  accelerometer_z = Wire.read()<<8 | Wire.read(); 
  temperature = Wire.read()<<8 | Wire.read(); 
  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read(); 
  gyro_z = Wire.read()<<8 | Wire.read(); 
  
  // print out data
 // Serial.print("aX = "); Serial.print((accelerometer_x));
  //Serial.print(" | aY = "); Serial.print((accelerometer_y));
 // Serial.print(" | aZ = "); Serial.print((accelerometer_z));
 // Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  //Serial.print(" | gX = "); Serial.print((gyro_x));
  //Serial.print(" | gY = "); Serial.print((gyro_y));
  //Serial.print(" | gZ = "); Serial.print((gyro_z));
  //Serial.println();
  
  // delay
  delay(100);
  Gyrovalue=gyro_z;
  Accvalue=accelerometer_x;
  //Serial.print(Accvalue);

//Gyrovalue=(Gyrovalue-GYROSCOPE_ZERO)*180/(MAX_GYROSCOPE_TILT_VALUE_po-MAX_GYROSCOPE_TILT_VALUE_ne);
if(Gyrovalue>Some_specific_Angle_at_which_one_turns)
{
  flag_turns_master=1;    
  Serial.print('1');
  delay(2000);
  //Serial.print("Right");
}
else if(Gyrovalue<-Some_specific_Angle_at_which_one_turns)
{
  flag_turns_master=3;    
  Serial.print('3');
  delay(2000);
  //Serial.print("Left");
}
if(Accvalue<-2700)
{
  flag_turns_master=2;
  Serial.print('2');
  delay(2000);
  //Serial.print("Stop");
}

else
{
  flag_turns_master=0;    
  Serial.print('0');
  delay(2000);
}

flag_turns_master=0;
}

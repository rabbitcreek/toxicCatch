#define pwmPin  0
int analogInPin = A1;
float basePressure = 0.0;
float voltage = 0.0;
float pressure = 0.0;
void setup(){
pinMode(pwmPin, OUTPUT);
pinMode(analogInPin, INPUT);
 voltage = 3.3*float((analogRead(A1)/1023.0));
 pressure = 5*((voltage - 0.2)/3.3);
basePressure = pressure;
}
void loop(){
 voltage = 3.3*float((analogRead(A1)/1023.0));
 pressure = 5*((voltage - 0.2)/3.3);
 
int counter = map((pressure * 10),1,15,100,10);
if (pressure - basePressure > 0.2){
digitalWrite(0,HIGH ); // Output analog reading to dimmable LED
delay(counter);
digitalWrite(0,LOW);
delay(counter);
}
}

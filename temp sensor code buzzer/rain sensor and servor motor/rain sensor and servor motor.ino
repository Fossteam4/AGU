#include<SoftwareSerial.h>
SoftwareSerial s(5,6);
#include<Servo.h>
int rain_sensor =A0,servo =3;
Servo myServo;
int buzzer = 11;
void setup()
{
  Serial.begin(9600);
  s.begin(9600);
  myServo.attach(servo);
  pinMode(buzzer,OUTPUT);
  myServo.write(0);
}
void loop()
{
  int sensorvalue=analogRead(rain_sensor);
  int motor=map(sensorvalue, 220, 1023, 180, 0);
  myServo.write(motor);
  int data = sensorvalue;
  Serial.println("Sensor value is ");
  Serial.println(sensorvalue);
  Serial.println("Servo motor rotates by angle ");
  Serial.println(motor);
  delay(5000);
  if(sensorvalue >=800)
  {  
    Serial.println("NOT RAINING");
    delay(100); 
  }
  else
  { 
    digitalWrite(buzzer,HIGH);
    Serial.println("RAINING"); 
    delay(1000);
    noTone(buzzer);   
    delay(1000);
  }
  if(s.available()>0){
    char c=s.read();
    if(c=='s'){
      s.write(data);
    }
  }
}




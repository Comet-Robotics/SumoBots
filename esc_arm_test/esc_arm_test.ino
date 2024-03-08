#include <Servo.h>
#define M1 PB5
#define M2 PB4
Servo LeftMotor;
Servo RightMotor; 


void setup ()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  LeftMotor.attach(M2, 1000, 2000); 
  RightMotor.attach(M1, 1000, 2000); 
  Serial.begin(9600);
  int i = 0;
  delay(10);
  //Give some time before you start anything like switching on your ESC / Motor
  
  Serial.print("Arming Test Starts in ");
  for(i =10; i > 0; i--)
  {
     Serial.print(i);
     Serial.print(".. ");
  }

  Serial.println();

// Watch for the tone when the ESC gets armed

  for(i = 60; i < 80; i++)
  {
     LeftMotor.write(i);
     RightMotor.write(i);
     Serial.println(i);
     delay(500);
  } 
  
}

void DRIVE(int speed) {
  LeftMotor.writeMicroseconds(speed);
  //delay(2000);
  RightMotor.writeMicroseconds(speed);
  //delay(2000);
}

void loop() { 
  
  // Drive both motors backwards
  for(int i = 1500; i > 1000; i--) { 
    RightMotor.write(i);  
    delay(10);
  }

  // Waiting 2 seconds
  DRIVE(1500);
  delay(2000); 

  for (int i = 1500; i < 2000; i++) { 
    RightMotor.write(i); 
    delay(10);
  }
  
  // Waiting 5 seconds 
  DRIVE(1500);
  delay(5000);
  
}
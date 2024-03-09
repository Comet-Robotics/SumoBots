#include <Servo.h>
#define M1 PB5
#define M2 PB4
Servo M2_Throttle;
Servo M1_Steering; 


void setup ()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  M2_Throttle.attach(M2, 1000, 2000); 
  M1_Steering.attach(M1, 1000, 2000); 
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
     M1_Steering.write(i);
     M2_Throttle.write(i);
     Serial.println(i);
     delay(500);
  } 
  
}

void DRIVE(int speed) {
  //M2_Throttle.writeMicroseconds(speed);
  M1_Steering.writeMicroseconds(speed);

}

void loop() { 
  
  // Drive both motors backwards

  /*
  for(int i = 1500; i > 1000; i--) { 
    M1_Steering.write(i);  
  }
  */

  //M1_Steering.write(1000); 
  M2_Throttle.write(1000);

  // Waiting 2 seconds
  delay(2000); 
  /*
  for (int i = 1500; i < 2000; i++) { 
    M1_Steering.write(i); 
  }
  */

  //M1_Steering.write(1800);
  
  // Waiting 5 seconds 
  delay(5000);
  
}
/* 
  This program contains the Firmware for the 1kg class Comet Robotics UTD 
  UTD Sumo robot. 
*/ 


#include <Servo.h> 


// Pin Definitions
#define OS1  PB7    //Opponent sensor 1                 CN9 1
#define OS2  PB6    //Opponent sensor 2                 CN9 2
#define LS1  PA10   //Pin number for line sensor 1      CN9 3
#define LS2  PB3    //Pin number for line sensor 2      CN9 4
#define M1 PB5     //Pin number for motor 1            CN9 5
#define M2 PB4      //Pin number for motor 2           CN9 6
int op1;            //Reading from left opponent sensor 
int op2;            //Reading from right opponent sensor 
int ln1;            //Reading from line sensor
int ln2;            //Reading from line sensor 2

Servo LeftMotor; 
Servo RightMotor; 

void lineHit(); 
void DRIVE(int speed);
void DRIVE(int speed1, int speed2); 
void Stop(); 
void setMotors();
void setSensors(); 
void armESC(); 

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  setSensors();
  setMotors();
  armESC();
  
  delay(5000);  //Wait for 5 seconds

}

void loop() {
  ln1 = digitalRead(LS1);
  ln2 = digitalRead(LS2);
  op1 = digitalRead(OS1);
  op2 = digitalRead(OS2);

  /*
  Serial.print("OP1: "); 
  Serial.println(op1);
  Serial.print("OP2: "); 
  Serial.println(op2);
  */
  
  if (op1 && op2)  //Go forwards while opponent seen in both sensors.
  {
    DRIVE(1750);
  }

  else if (op1 && !op2)  //Go forwards and slightly right while opponent seen by left sensor
  {
    DRIVE(1750,1950);
  }

  else if (!op1 && op2)  //Go forwards and slightly left while opponent seen by right sensor
  {
    DRIVE(1950,1750);
  }

  else //Turn and move forward slightly if the opponent is not seen
  {
    DRIVE(1750, 1950);
    delay(200);
  }
}

//Interrupt when detect line
void lineHit()
{
  Stop();
  for(int i=0;i<30;i++)
  {
    delayMicroseconds(15000);
  }
  DRIVE(-255);
  for(int i=0;i<300;i++)
  {
    delayMicroseconds(15000);
  }
}


void DRIVE(int speed) {
  LeftMotor.writeMicroseconds(speed); 
  RightMotor.writeMicroseconds(speed);
  //delay(200);
}


void DRIVE(int speed1, int speed2) {
  LeftMotor.writeMicroseconds(speed1);
  RightMotor.writeMicroseconds(speed2);
  //delay(200);
}


void Stop() {
  DRIVE(1500,1500);
}

void setMotors() { 
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  LeftMotor.attach(M2, 1000, 2000); 
  RightMotor.attach(M1, 1000, 2000);

}

void setSensors() { 
  pinMode(OS1, INPUT);
  pinMode(OS2, INPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  //attachInterrupt(digitalPinToInterrupt(LS1), lineHit,RISING);
  //attachInterrupt(digitalPinToInterrupt(LS2), lineHit,RISING);
}

void armESC() { 
  
  delay(10);
  for (int i = 60; i < 80; i++) { 
    LeftMotor.write(i);
    RightMotor.write(i);
    Serial.println(i);
    delay(500); 
  }
  
  
  //delay(10);
  //LeftMotor.write(68);
  //RightMotor.write(68);
  delay(300);
}

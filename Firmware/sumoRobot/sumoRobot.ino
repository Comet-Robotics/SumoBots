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
volatile bool line_hit; 

Servo M1_Steering; 
Servo M2_Throttle; 

void lineHit1();
void lineHit2(); 
bool isLineHit();
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
  seen_left = 0;

  /*
  Serial.print("OP1: "); 
  Serial.println(op1);
  Serial.print("OP2: "); 
  Serial.println(op2);
  */

  if(isLineHit())
  {
    /*
    Serial.print("Ln1: "); 
    Serial.println(ln1);
    Serial.print("Ln2: "); 
    Serial.println(ln2);
    */

    Stop();
    //Drive backwards
    DRIVE(1500,1300);
    delay(200);

    //Turn around
    DRIVE(1700, 1500);
    delay(500);
  }
  else
  {
    if (op1 && op2)  //Go forwards while opponent seen in both sensors.
    {
      DRIVE(1500,1600);
    }
    else if (!op1 && op2)  //Go forwards and slightly right while opponent seen by only left sensor
    {
      seen_left = 1;
      DRIVE(1600,1500);
    }
    else if (op1 && !op2)  //Go forwards and slightly left while opponent seen by only right sensor
    {
      seen_right = 0;
      DRIVE(1400,1500);
    }
    else //Turn and move forward slightly if the opponent is not seen
    {
      if(seen_left){
        DRIVE(1350,1500);
      }
      else {
        DRIVE(1650,1500);
      }
      delay(500);
      Stop();
      delay(200);
    }
  }
}

bool isLineHit() {
  return line_hit;
}

//Updates line_hit on an interrupt
void lineHit1() {
  line_hit = digitalRead(ln1);
}
void lineHit2() {
  line_hit = digitalRead(ln2);
}

//1000-Minimum  1500-Neutral  2000-Maximum
void DRIVE(int speed1, int speed2) {
  M1_Steering.writeMicroseconds(speed1);
  M2_Throttle.writeMicroseconds(speed2);
}

void Stop() {
  DRIVE(1500,1500);
  delay(150);
}

void setMotors() { 
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  M2_Throttle.attach(M2, 1000, 2000); 
  M1_Steering.attach(M1, 1000, 2000);
}

void setSensors() { 
  pinMode(OS1, INPUT);
  pinMode(OS2, INPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  attachInterrupt(digitalPinToInterrupt(LS1), lineHit1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(LS2), lineHit2,CHANGE);
}

void armESC() { 
  
  delay(10);
  for (int i = 60; i < 80; i++) { 
    M2_Throttle.write(i);
    M1_Steering.write(i);
    Serial.println(i);
    delay(500); 
  }

  //delay(10);
  //LeftMotor.write(68);
  //RightMotor.write(68);
  delay(300);
}

//CN8 Pins
#define OS1  PB7  //Opponent sensor 1               CN9 1
#define OS2  PB6  //Opponent sensor 2               CN9 2
#define LS1  PA10 //Pin number for line sensor 1     CN9 3
#define LS2  PB3 //Pin number for line sensor 2     CN9 4
#define M1 PB10   //Pin number for motor 1          CN9 5
#define M2 PB4   //Pin number for mototr 2         CN9 6
int op1;            //Reading from left opponent sensor 
int op2;            //Reading from right opponent sensor 
int ln1;            //Reading from line sensor
int ln2;            //Reading from line sensor 2

void setup() {
  pinMode(OS1, INPUT);
  pinMode(OS2, INPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);

  attachInterrupt(digitalPinToInterrupt(LS1), lineHit,RISING);
  attachInterrupt(digitalPinToInterrupt(LS2), lineHit,RISING);

  Serial.begin(9600);
  delay(5000);  //Wait for 5 seconds
}

//Interrupt when detect line
void lineHit()
{
  Stop();
  delayMicroseconds(50000);
  DRIVE(-255);
  delayMicroseconds(500000);
}

void loop() {
  ln1 = digitalRead(LS1);
  ln2 = digitalRead(LS2);
  op1 = digitalRead(OS1);
  op2 = digitalRead(OS2);

  while (op1 && op2)  //Go forwards while opponent seen in both sensors.
  {
    DRIVE(255);
    op1 = digitalRead(OS1);
    op2 = digitalRead(OS2);
    ln1 = digitalRead(LS1);
    ln2 = digitalRead(LS2);
    //delay(10);
  }

  while (op1 && !op2)  //Go forwards and slightly left while opponent seen by left sensor
  {
    DRIVE(200,255);
    op1 = digitalRead(OS1);
    op2 = digitalRead(OS2);
    ln1 = digitalRead(LS1);
    ln2 = digitalRead(LS2);
    //delay(10);
  }

  while (!op1 && op2)  //Go forwards and slightly right while opponent seen by right sensor
  {
    DRIVE(255,200);
    op1 = digitalRead(OS1);
    op2 = digitalRead(OS2);
    ln1 = digitalRead(LS1);
    ln2 = digitalRead(LS2);
    delay(10);
  }

  if (!op1 && !op2)  //Turn and move forward slightly if the opponent is not seen
  {
    DRIVE(125, 25);
    delay(250);
  }
}

void DRIVE(int speed) {
  analogWrite(M1, speed);
  analogWrite(M2, speed);
}

void DRIVE(int speed1, int speed2) {
  analogWrite(M1, speed1);
  analogWrite(M2, speed2);
}

void Stop() {
  DRIVE(0, 0);
}
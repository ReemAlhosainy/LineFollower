
#include <LiquidCrystal.h>
LiquidCrystal lcd ( 6 , 7 , 8 , 9 , 12 , 13 );
//RS , En, d4------->d7

const int sensor0 = 2;    //left
const int sensor1 = 3;    //Middle
const int sensor2 = 5;    //Right
const int sensor3 = 4;     //Up Middle
int mot1 = A1;
int mot2 = A0;
int mot3 = A3;
int mot4 = A2;
int sensorValues[4] = {0, 0, 0, 0};
String state = " ";
//int score;
char point = ' ';
bool anychange = false;
int sped1 = 10;
int sped2 = 11;
void setup() {
  // put your setup code here, to run once:
pinMode(sensor0, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);

  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  pinMode(mot3, OUTPUT);
  pinMode(mot4, OUTPUT);
  pinMode(sped1, OUTPUT);
  pinMode(sped2, OUTPUT);
   lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(4, 0);

  lcd.print("01 Team");
}

void loop() {
  sensorValues[0] = digitalRead(sensor0);
  sensorValues[1] = digitalRead(sensor1);
  sensorValues[2] = digitalRead(sensor2);
  sensorValues[3] = digitalRead(sensor3);
  // put your main code here, to run repeatedly:
// 0101 || 0100 || 0001 is the optimum condition => error=0
if(sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 0)
{
      motorforward();

}
else if ( (sensorValues[0] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1))
  {
    motorforward();
  }
  // 100 means the car must turn to left sharp => error=-2
  
else if (sensorValues[0] == 1 && sensorValues[1] == 0 && sensorValues[2] == 0)
  {
motorSHARPright();
}
  // 001 means the car must turn to right => error=2
  else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 1)
  {
motorSHARPleft();
}

  // 110 means the car must turn to left => error=-1
  else if (sensorValues[0] == 1 && sensorValues[1] == 1  && sensorValues[2] == 0)
  {
motorleft();
}
  // 011 means the car must turn to right => error=1
  else if (sensorValues[0] == 0 && sensorValues[1] == 1  && sensorValues[2] == 1)
  {
  motorright();
  }
  // 0000 means the car must rotate in any direction until it finds the black line again
  //we can assume it will make U
  else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0)
  {
    motorright();
     if ((sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 0) || (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1))
       {
         motorforward();
       }
  else {
    motorleft();
    if ((sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 0) || (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1))
  {
    motorforward();
  }
  }

  }

  // 1111 means the car must stop or turn right
  else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1)
  {
    motorforward();
//    delay(200);
//    if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1)
//  {
//    motorStop();  
//
//  }
//else{
//  motorforward();
//  }
}
   if (anychange)
  {
    lcd.clear();
    printlcd();
    anychange = false;

  }

}
void motorright()
{
  analogWrite(sped1, 160);
  analogWrite(sped2, 90);
  digitalWrite(mot1, 0);
  digitalWrite(mot2, 0);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 1);
  if (state != "left")
  {
    state = "left";
    anychange = true;
  }
}
void motorleft()
{
   analogWrite(sped1, 160);
  analogWrite(sped2, 90);
  digitalWrite(mot1, 0);
  digitalWrite(mot2, 1);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 0);
  if (state != "right")
  {
    state = "right";
    anychange = true;
  }

}
void printlcd()
{
  lcd.setCursor(4, 0);
  lcd.print("01 Team");
  lcd.setCursor(0, 1);
  lcd.print(state);
  lcd.print(",Point:");
  lcd.print(point);

}
void motorSHARPright()
{
   analogWrite(sped1, 160);
  analogWrite(sped2, 90);
  digitalWrite(mot1, 0);
  digitalWrite(mot2, 1);
  digitalWrite(mot3, 1);
  digitalWrite(mot4, 0);
  if (state != "Cornering right")
  {
    state = "Cornering right";
    anychange = true;

  }
}
void motorSHARPleft()
{
  analogWrite(sped1, 160);
  analogWrite(sped2, 90);
  digitalWrite(mot1, 1);
  digitalWrite(mot2, 0);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 1);
  if (state != "Cornering left")
  {
    state = "Cornering left";
    anychange = true;
  }

}

void motorStop()
{

  digitalWrite(mot1, 0);
  digitalWrite(mot2, 0);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 0);
  if (state != "Stop")
  {
    state = "Stop";
    anychange = true;
  }
}
void motorforward()
{
  analogWrite(sped1, 160);
  analogWrite(sped2, 90);
  digitalWrite(mot1, 0);
  digitalWrite(mot2, 1);
  digitalWrite(mot3, 0);
  digitalWrite(mot4, 1);
  if (state != "Forward")
  {
    state = "Forward";
    anychange = true;
  }
}

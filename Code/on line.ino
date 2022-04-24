// C++ code
//

#define ln1 2
#define ln2 4
#define sonicTrig 12
#define sonicEcho 13
#define motor1A 6
#define motor1B 7
#define motor2A 9
#define motor2B 8

#define Forward 100
#define Right 110
#define Left 120
#define Stop 400

#define motorPowerA 10
#define motorPowerB 5
volatile int state = Forward;

void setup()
{
  pinMode(ln1, INPUT);
  pinMode(ln2,INPUT);
  pinMode(sonicTrig,INPUT);
  pinMode(sonicEcho,OUTPUT);
  pinMode(motor1A,OUTPUT);
  pinMode(motor1B,OUTPUT);
  pinMode(motor2A,OUTPUT);
  pinMode(motor2B,OUTPUT);
  analogWrite(motorPowerA, 255);
  analogWrite(motorPowerB, 255);
  Serial.begin(9600);
}

void sonicSensor(){
  int duration;
  int distance;
  
  digitalWrite(sonicTrig,HIGH);
  digitalWrite(sonicTrig,LOW);
  duration = pulseIn(sonicEcho,HIGH);
  distance = duration*0.0343/2;
  Serial.println(distance);
  if (distance < 5){state = Stop;}
}

void loop()
{
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==HIGH){
  state = Stop;
  }
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==LOW){
    //find motor config to make it turn RIGHT
  state = Right;
  }
  if(digitalRead(ln1)==LOW && digitalRead(ln2)==HIGH){
    //find motor config to make it turn LEFT
  state = Left;
  }
  if(digitalRead(ln1)==LOW && digitalRead(ln2)==LOW){
  state = Forward;
  }
  switchState();
  //sonicSensor();
}

void switchState(){
  switch(state){
    case Stop:
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,LOW);
      break;
    case Forward:
     // analogWrite(motorPowerA,255);
      //analogWrite(motorPowerA,255);
      digitalWrite(motor1A,HIGH);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,HIGH
      );
      break;
    case Right:
     // analogWrite(motorPowerA,100);
      //analogWrite(motorPowerB,180);
      digitalWrite(motor1A,HIGH);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,HIGH);
      digitalWrite(motor2B,LOW);
      break;
    case Left:
      //analogWrite(motorPowerA,180);
      //analogWrite(motorPowerB,100);
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,HIGH);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,HIGH);
      break;
    
  }
}

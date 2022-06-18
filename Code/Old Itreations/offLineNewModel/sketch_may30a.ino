
#define ln1 2 //right
#define ln2 4
#define sonicTrig 12
#define sonicEcho 13
#define motorA1 A1
#define motorA2 A2
#define motorB1 A3
#define motorB2 A4

#define Forward 100
#define Right 110
#define Left 120
#define Stop 400

#define motorPowerA 10
#define motorPowerB 3
volatile int state = Forward;

void setup()
{
  pinMode(ln1, INPUT);
  pinMode(ln2,INPUT);
  pinMode(sonicTrig,INPUT);
  pinMode(sonicEcho,OUTPUT);
  pinMode(motorA1,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorB2,OUTPUT);
  analogWrite(motorPowerA, 190);
  analogWrite(motorPowerB, 150);
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
  Serial.print("right ");
  Serial.println(digitalRead(ln1));
  Serial.print("left ");
  Serial.println(digitalRead(ln2));
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==HIGH){
  state = Forward;
  }
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==LOW){
    //find motor config to make it turn RIGHT
  state = Left;
  }
  if(digitalRead(ln1)==LOW && digitalRead(ln2)==HIGH){
    //find motor config to make it turn LEFT
  state = Right;
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
      digitalWrite(motorA1,LOW);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB2,LOW);
      break;
    case Forward:
     // analogWrite(motorPowerA,255);
      //analogWrite(motorPowerA,255);
      digitalWrite(motorA1,HIGH);
      digitalWrite(motorB1,HIGH);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB2,LOW);
      break;
    case Right:
     // analogWrite(motorPowerA,100);
      //analogWrite(motorPowerB,180);
      
      digitalWrite(motorA1,HIGH);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB2,LOW);
      
      break;
    case Left:
      //analogWrite(motorPowerA,180);
      //analogWrite(motorPowerB,100);
      
      digitalWrite(motorA1,LOW);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,HIGH);
      digitalWrite(motorB2,LOW);
      break;
    
  }
}

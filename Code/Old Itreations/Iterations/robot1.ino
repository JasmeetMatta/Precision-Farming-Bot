//const int trig = 8;
//const int echo = 7;

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
volatile int duration = 0;
volatile long distance = 0;
volatile int counterFace1, CounterFace2;
volatile colorChecked= false, lineChecked= false, objectChecked= false;
volatile int dropPositionF1, dropPositionF2, objectPositionF1, objectPositionF2;

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

void loop ()
{
  if (lineChecked == true)
  {
    
  } 
}
  
}
void ultrasonic()
{
// Start the scan
  //digitalWrite(sonicTrig, LOW);
  //delayMicroseconds(2);// for the sensor operation to work right 
  digitalWrite(sonicTrig, HIGH);
  //delayMicroseconds(10);// delay
  digitalWrite(sonicTrig, LOW);
  
  duration = pulseIn(sonicEcho, HIGH);
  distance= (duration*0.034/2);// converting the distance to centimeter
  Serial.print("The Distance: ");
  Serial.println(distance);
  //delay(10);
  if (distance < 50)
  {
    Serial.println ("Object detected" );
    Serial.print ("Distance of the object from the car is " );
    Serial.print ( distance);
    Serial.println ( " cm");// print out the distance in centimeters.
    Serial.println (" move forward during half second !");

    objectChecked= true;
    
  }
  else
  {
    objectChecked= false;
  }
  
  
}

void line()
{
    if(digitalRead(ln1)==HIGH && digitalRead(ln2)==HIGH)
    {
    state = Stop;
    lineChecked= false;
    }
    if(digitalRead(ln1)==HIGH && digitalRead(ln2)==LOW){
      //find motor config to make it turn RIGHT
    state = Right;
    lineChecked= true;
    }
    if(digitalRead(ln1)==LOW && digitalRead(ln2)==HIGH){
      //find motor config to make it turn LEFT
    state = Left;
    lineChecked= true;
    }
    if(digitalRead(ln1)==LOW && digitalRead(ln2)==LOW){
    state = Forward;
    lineChecked= true;
    }
}

void color()
{

}
void movementBehavior()
{
void switchState(){
  switch(state)
  {
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
      digitalWrite(motor2B,HIGH);
      break;
      case Backward:
     // analogWrite(motorPowerA,255);
      //analogWrite(motorPowerA,255);
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,HIGH);
      digitalWrite(motor2A,HIGH);
      digitalWrite(motor2B,LOW);
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
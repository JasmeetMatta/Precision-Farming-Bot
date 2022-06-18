#define S0 9
#define S1 7
#define S2 6
#define S3 5
#define sensorOut 8

#define ln1 2
#define ln2 4
#define sonicTrig 12
#define sonicEcho 13
#define motorA1 A1
#define motorA2 A2
#define motorB1 A3
#define motorB2 A4

#define motorPowerA 10
#define motorPowerB 3

#define Forward 100
#define Right 110
#define Left 120
#define Stop 400

#define rotateLeft 500
#define rotateRight 501

volatile int moveState = Forward;
volatile int duration, distance;
volatile int moveCounter=0, currentPosition1=0 , CurrentPosition2=0 , dropPosition1=0 , dropPosition2=0 , objectPosition1=0, objectPosition2=0;
volatile bool objectDetected = false, lineChecked= false, colorRead= false;
volatile int rotateState = rotateLeft;

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

char currentColor;

void setup() {
  
 // Set S0 - S3 as outputs
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Set Sensor output as input
    pinMode(sensorOut, INPUT);

    // Set Pulse Width scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    pinMode(ln1, INPUT);
    pinMode(ln2,INPUT);
    pinMode(sonicTrig,INPUT);
    pinMode(sonicEcho,OUTPUT);
    pinMode(motorA1,OUTPUT);
    pinMode(motorB1,OUTPUT);
    pinMode(motorA2,OUTPUT);
    pinMode(motorB2,OUTPUT);
    analogWrite(motorPowerA, 160);
    analogWrite(motorPowerB, 220);

    // Setup Serial Monitor
    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

   do
   { 
     switchMoveState();
     followLine();
     getColor();
     ultraSonic();
    
      if( lineChecked == true && colorRead== true && moveCounter == objectPosition2 )
      {
        //switchRotation()
  
        if (objectPosition1 < currentPosition1)
        {
          rotateState = rotateLeft;
          switchRotation();
          
        }
        else
        {
          rotateState = rotateRight;
          switchRotation();
        }
      }
   
   } while(lineChecked == true && colorRead== true );
}
void color()
{
  
  // Read Red Pulse Width
    redPW = getRedPW();
    // Delay to stabilize sensor
    delay(200);

    // Read Green Pulse Width
    greenPW = getGreenPW();
    // Delay to stabilize sensor
    delay(200);

    // Read Blue Pulse Width
    bluePW = getBluePW();
    // Delay to stabilize sensor
    delay(200);

    currentColor = getColor();
    delay(200);

    // Print output to Serial Monitor
    Serial.print("Red PW = ");
    Serial.print(redPW);
    Serial.print(" - Green PW = ");
    Serial.print(greenPW);
    Serial.print(" - Blue PW = ");
    Serial.println(bluePW);
    Serial.print(" - color = ");
    Serial.println(currentColor);
}

// Function to read Red Pulse Widths
int getRedPW()
{

    // Set sensor to read Red only
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
}

// Function to read Green Pulse Widths
int getGreenPW()
{

    // Set sensor to read Green only
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
}

// Function to read Blue Pulse Widths
int getBluePW()
{

    // Set sensor to read Blue only
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
}
char getColor()
{
    char color;
    if ((redPW >= 114 && redPW <= 150) && (greenPW >= 324 && greenPW <= 350) && (bluePW >= 364 && bluePW <= 395))
    {
        color = 'o'; // orange
        colorRead= true;
        
    }
    else if ((redPW >= 320 && redPW <= 370) && (greenPW >= 505 && greenPW <= 570) && (bluePW >= 235 && bluePW <= 355))
    {
        color = 'p'; // purple
        colorRead= true;
    }
    else if ((redPW >= 174 && redPW <= 230) && (greenPW >= 190 && greenPW <= 240) && (bluePW >= 320 && bluePW <= 385))
    {
        color = 'g'; // green
         colorRead= true;
    }
    else if ((redPW >= 232 && redPW <= 300) && (greenPW >= 170 && greenPW <= 210) && (bluePW >= 130 && bluePW <= 160))
    {
        color = 'c'; // cyan
        colorRead= true;
    }
    else if ((redPW >= 90 && redPW <= 108) && (greenPW >= 95 && greenPW <= 115) && (bluePW >= 80 && bluePW <= 95))
    {
        color = 'w'; // white
        
    }
    else if (((redPW >= 900 && redPW <= 1200) && (greenPW >= 1000 && greenPW <= 1265) && (bluePW >= 800 && bluePW <= 1000)) || ((redPW >= 622 && redPW <= 800) && (greenPW >= 800 && greenPW <= 900) && (bluePW >= 600 && bluePW <= 710)))
    {
        color = 'b'; // black
    }
    return color;
}
void ultraSonic()
{
    digitalWrite(sonicTrig,HIGH);
    digitalWrite(sonicTrig,LOW);
    duration = pulseIn(sonicEcho,HIGH);
    distance = duration*0.0343/2;
    Serial.print("The Distance: ");
    Serial.println(distance);
    if (distance < 30)
      {
        Serial.println ("Object detected" );
        Serial.print ("Distance of the object from the car is " );
        Serial.print ( distance);
        Serial.println ( " cm");// print out the distance in centimeters.
        Serial.println (" move forward during one second !");
        
        moveState= Stop;// i will change in the loop

        objectDetected = true;
        
        delay (1000);
      }
}

void switchMoveState()
{
  switch(moveState)
  {
    case Stop:
      digitalWrite(motorA1,LOW);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB2,LOW);
      break;
    case Forward:
     
      digitalWrite(motorA1,HIGH);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB2,HIGH);
      break;
      /*case Backward:
     
      digitalWrite(motorA1,LOW);
      digitalWrite(motorB1,HIGH);
      digitalWrite(motorA2,HIGH);
      digitalWrite(motorB2,LOW);
      break;*/
    case Right:
     
      digitalWrite(motorA1,HIGH);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,HIGH);
      digitalWrite(motorB2,LOW);
      break;
    case Left:
      
      digitalWrite(motorA1,LOW);
      digitalWrite(motorB1,HIGH);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB2,HIGH);
      break;

  }
}


void followLine()
{
  
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==HIGH)
    {
    moveState = Forward;
    switchMoveState();
    lineChecked= true;
    }
    if(digitalRead(ln1)==HIGH && digitalRead(ln2)==LOW){
      //find motor config to make it turn RIGHT
    moveState = Right;
    switchMoveState();
    lineChecked= true;
    }
    if(digitalRead(ln1)==LOW && digitalRead(ln2)==HIGH){
      //find motor config to make it turn LEFT
    moveState = Left;
    switchMoveState();
    lineChecked= true;
    }
    if(digitalRead(ln1)==LOW && digitalRead(ln2)==LOW)
    {

    moveCounter += 1;
    moveState = Forward;
    switchMoveState();
    lineChecked= true;
    
    }
}

void switchRotation()
{
  switch (rotateState)
  {
    case rotateLeft:
      moveState= Forward;
      switchMoveState();
      delay(1000); 
      moveState= Left;
      delay(1000);
      switchMoveState();
      delay(500);
      moveState= Stop;
      
  
   
    case rotateRight:
  
      moveState= Forward;
      switchMoveState();
      delay(1000); 
      moveState= Right;
      delay(1000);
      switchMoveState(); 
      delay(500);
      moveState= Stop;
  }
}

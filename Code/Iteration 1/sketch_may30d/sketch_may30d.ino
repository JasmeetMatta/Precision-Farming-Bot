#define ln1 2
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
#define Backward 500
//#define rotateRight 160
//#define rotateLeft 170

#define motorPowerA 10
#define motorPowerB 3

volatile int state = Forward;
volatile int duration = 0;
volatile long distance = 0;
volatile int counterFace1, CounterFace2;
volatile bool colorChecked= false, lineChecked= false, objectChecked= false;
//volatile int dropPositionF1= 3, dropPositionF2=4, objectPositionF1=1, objectPositionF2=1;


#define S0 9
#define S1 7
#define S2 6
#define S3 5
#define sensorOut 8

// Variables for Color Pulse Width Measurements

int redPW = 0;
int greenPW = 0;
int bluePW = 0;


int currentColor;


volatile int face = 0; // {N,W,E,S}==>{0,1,2,3}
volatile int currentMapLocation[2] = {0,0};
volatile int dropLocation[2] = {5,6};
volatile int objectLocation[2] = {3,4};
volatile int homeLocation[2] = {0,0};

volatile int prevColor = currentColor; //{orange,ciyan,green,voliet,white,black} ==> {0,1,2,3,4,5}

//volatile int state = forward;




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
  analogWrite(motorPowerA, 180);//Aleft
  analogWrite(motorPowerB, 100);//B
  Serial.begin(9600);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Pulse Width scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop ()
{
  movementBehavior();
  line();
  /*
  //ultrasonic ();
  movingToObject();
  //faceBack();
  
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

  getColor();
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
  
*/
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
    state = Forward;
    lineChecked= true;
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
    state = Stop;
    lineChecked= true;
    }
}

void movementBehavior()
{
  switch(state)
  {
    case Stop:
      digitalWrite(motorA1,LOW);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorB2,LOW);
      break;
    case Forward:
     // analogWrite(motorPowerA,255);
      //analogWrite(motorPowerA,255);
      digitalWrite(motorA1,HIGH);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB1,HIGH);
      digitalWrite(motorB2,LOW);
      break;
    case Backward:
     // analogWrite(motorPowerA,255);
      //analogWrite(motorPowerA,255);
      digitalWrite(motorA1,LOW);
      digitalWrite(motorA2,HIGH);
      digitalWrite(motorB1,HIGH);
      digitalWrite(motorB2,LOW);
      break;
    case Right:
     // analogWrite(motorPowerA,100);
      //analogWrite(motorPowerB,180);
      digitalWrite(motorA1,HIGH);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorB2,HIGH);
      break;
    case Left:
      //analogWrite(motorPowerA,180);
      //analogWrite(motorPowerB,100);
      digitalWrite(motorA1,LOW);
      digitalWrite(motorA2,HIGH);
      digitalWrite(motorB1,HIGH);
      digitalWrite(motorB2,LOW);
      break;
    
  }
}

int getRedPW() {

  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

// Function to read Green Pulse Widths
int getGreenPW() {

  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
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
        color = 'o'; 
        currentColor= 0;
        // orange
    }
    else if ((redPW >= 320 && redPW <= 370) && (greenPW >= 505 && greenPW <= 570) && (bluePW >= 235 && bluePW <= 355))
    {
        color = 'p';
        currentColor =3; // purple
    }
    else if ((redPW >= 174 && redPW <= 230) && (greenPW >= 190 && greenPW <= 240) && (bluePW >= 320 && bluePW <= 385))
    {
        color = 'g';
        currentColor=2;// green
    }
    else if ((redPW >= 232 && redPW <= 300) && (greenPW >= 170 && greenPW <= 210) && (bluePW >= 130 && bluePW <= 160))
    {
        color = 'c';
        currentColor = 1; // cyan
    }
    else if ((redPW >= 90 && redPW <= 108) && (greenPW >= 95 && greenPW <= 115) && (bluePW >= 80 && bluePW <= 95))
    {
        color = 'w';
        currentColor = 4;// white
    }
    else if (((redPW >= 900 && redPW <= 1200) && (greenPW >= 1000 && greenPW <= 1265) && (bluePW >= 800 && bluePW <= 1000)) || ((redPW >= 622 && redPW <= 800) && (greenPW >= 800 && greenPW <= 900) && (bluePW >= 600 && bluePW <= 710)))
    {
        color = 'b'; 
        currentColor= 5;// black
    }
    return color;
}


void StateMachine(){
  switch(prevColor){
    case 0:
    if(currentColor == 1 && face == 2){
      currentMapLocation[1]=currentMapLocation[1]+0.5;
      prevColor = currentColor;}
    if(currentColor == 1 && face == 1){
      currentMapLocation[1]=currentMapLocation[1]-0.5;prevColor = currentColor;}
    break;
    case 1:
    if(currentColor == 0 && face == 2){
      currentMapLocation[1]=currentMapLocation[1]+0.5;prevColor = currentColor;}
    if(currentColor == 0 && face == 1){
      currentMapLocation[1]=currentMapLocation[1]-0.5;prevColor = currentColor;}
    break;
    case 2:
    if(currentColor == 3 && face == 0){
      currentMapLocation[0]=currentMapLocation[0]+0.5;prevColor = currentColor;}
    if(currentColor == 3 && face == 3){
      currentMapLocation[0]=currentMapLocation[0]-0.5;prevColor = currentColor;}
    break;
    case 3:
    if(currentColor == 2 && face == 0){
      currentMapLocation[0]=currentMapLocation[0]+0.5;prevColor = currentColor;}
    if(currentColor == 2 && face == 3){
      currentMapLocation[0]=currentMapLocation[0]-0.5;prevColor = currentColor;}
    break;
    }
 
  }

void faceChangeLeft(){
  if (face == 3){
    face = 0;
    }
   else{face += 1;}
  }
  
void faceChangeRight(){
  if (face == 0){
    face = 3;
    }
   else{face -= 1;}
  }
void movingToObject(){
  Serial.println("Hey");
  while(lineChecked == true && currentMapLocation[1] != objectLocation[1]){
    state = Forward;
    movementBehavior();
    StateMachine();
    }
  if(lineChecked == true && currentMapLocation[1] == objectLocation[1]){
    rotateRight();
    faceChangeRight();
    }
  while(lineChecked == true && currentMapLocation[0] != objectLocation[0]){
    state = Forward;
    movementBehavior();
    StateMachine();
    }
  
  }
void movingToDropLocation(){
  faceBackHorizontal();
  while(lineChecked == true && currentMapLocation[1] != dropLocation[1]){
    state = Forward;
    movementBehavior();
    StateMachine();
  }
  if(lineChecked == true && currentMapLocation[1] == dropLocation[1]){
    faceBackVertical();
  }
  while(lineChecked == true && currentMapLocation[0] != dropLocation[0]){
    state = Forward;
    movementBehavior();
    StateMachine();
    }
    
  }
/*
void movingToObject(){
    if (lineChecked == true && currentMapLocation[1] != objectLocation[1])
  {
    state = Forward; 
    movementBehavior();
    StateMachine();
    } 
  else if (lineChecked == true && currentMapLocation[1] == objectLocation[1])
  {
   state= Stop;
   movementBehavior();
   rotateRight();
   //movementBehavior();
   faceChangeRight();
  }
  else if (lineChecked == true && currentMapLocation[0] != objectLocation[0]){
    state = Forward; 
    movementBehavior();
    StateMachine();    
  }
  else if (lineChecked == true && currentMapLocation[1] == objectLocation[1]){
   state= Stop;
   //movementBehavior();
   //state = rotateRight;
   movementBehavior();
   //faceChangeRight();
        }
}



*/
/*
movingToDropLocation(){
  if (lineChecked == true && currentMapLocation[0] != dropLocation[0])
  {
    state = Forward; 
    movementBehavior();
    StateMachine();
    } 
  else if (lineChecked == true && currentMapLocation[0] == objectLocation[0])
  {
   state= Stop;
   movementBehavior();
   //if (curretMapLocation[0] >= dropLocation[0]){
   // state = rotateLeft;
    //faceChangeLeft();
    //}
   //else{
    //state = rotateRight;
    //faceChangeRight();      
     // }

   movementBehavior();
   //faceChangeRight();
  }
  else if (lineChecked == true && currentMapLocation[1] != objectLocation[1]){
   if (curretMapLocation[1] >= dropLocation[1]){
    state = rotateRight;
    faceChangeRight();
    }
   else{
    state = rotateLeft;
    faceChangeLeft();      
      }
    state = Forward; 
    movementBehavior();
    StateMachine();    
  }
  else if (lineChecked == true && currentMapLocation[1] == objectLocation[1]){
   state= Stop;
   movementBehavior();
   state = rotateRight;
   movementBehavior();
   faceChangeRight();
        }

  }
  */
void faceBackVertical(){
   if (currentMapLocation[0] >= dropLocation[0]){
    int needFace = 2;
    while(face != needFace){
      rotateRight();
      faceChangeRight();
      }
    }
   else{
    int needFace = 0;
    while(face != needFace){
      rotateLeft();
      faceChangeLeft();
      }   
     }
  }

void faceBackHorizontal(){
   if (currentMapLocation[1] >= dropLocation[1]){
    int needFace = 1;
    while(face != needFace){
      rotateRight();
      faceChangeRight();
      }
    }
   else{
    int needFace = 3;
    while(face != needFace){
      rotateLeft();
      faceChangeLeft();
      }   
      }
  }
void rotateLeft()
  {
    line();
    if ( (currentColor == 3) &&( face == 0))
    {
      do
      {
       digitalWrite(motorA1,HIGH);
       digitalWrite(motorB1,LOW);
       digitalWrite(motorA2,LOW);
       digitalWrite(motorB2,HIGH);
      } while (currentColor == prevColor);
    }
    
    if ( (currentColor == 2) &&( face == 3))
    {
      do
      {
       digitalWrite(motorA1,HIGH);
       digitalWrite(motorB1,LOW);
       digitalWrite(motorA2,LOW);
       digitalWrite(motorB2,HIGH);
      } while (currentColor == prevColor);
    }
      if ( (currentColor == 1) &&( face == 2))
    {
      do
      {
       digitalWrite(motorA1,HIGH);
       digitalWrite(motorB1,LOW);
       digitalWrite(motorA2,LOW);
       digitalWrite(motorB2,HIGH);
      } while (currentColor == prevColor);
      
    }
      if ( (currentColor == 0) &&( face == 1))
    {
    do{
     digitalWrite(motorA1,HIGH);
     digitalWrite(motorB1,LOW);
     digitalWrite(motorA2,LOW);
     digitalWrite(motorB2,HIGH);
    } while (currentColor == prevColor);
    }
    
  }
   void rotateRight()
   {
     if ( (currentColor == 0) &&( face == 1))
     {
       do
       {
       digitalWrite(motorA1,LOW);
       digitalWrite(motorB1,HIGH);
       digitalWrite(motorA2,HIGH);
       digitalWrite(motorB2,LOW);
       } while(currentColor == prevColor);
     }
     if ( (currentColor == 3) &&( face == 0))
     {
        do
         {
         digitalWrite(motorA1,LOW);
         digitalWrite(motorB1,HIGH);
         digitalWrite(motorA2,HIGH);
         digitalWrite(motorB2,LOW);
         } while(currentColor == prevColor);
     }
     if ( (currentColor == 1) &&( face == 2))
     {
         do
           {
           digitalWrite(motorA1,LOW);
           digitalWrite(motorB1,HIGH);
           digitalWrite(motorA2,HIGH);
           digitalWrite(motorB2,LOW);
           } while(currentColor == prevColor);
     }
     if ( (currentColor == 2) &&( face == 3))
     {
         do
           {
           digitalWrite(motorA1,LOW);
           digitalWrite(motorB1,HIGH);
           digitalWrite(motorA2,HIGH);
           digitalWrite(motorB2,LOW);
           } while(currentColor == prevColor);
     }
   }

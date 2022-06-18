#define ln1 2 // right
#define ln2 4
#define sonicTrig 12
#define sonicEcho 11 //13
#define motorA1 A1 // right
#define motorA2 A2
#define motorB1 A3
#define motorB2 A4

#define Forward 100
#define Right 110
#define Left 120
#define Stop 400
#define Backward 500


#define motorPowerA 10
#define motorPowerB 3
volatile int  counter, state = Forward;
volatile int duration = 0;
volatile long distance = 0;


volatile bool atObject = false,atDrop = false,change = false;

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
int i =0;

int currentColor = 2;


volatile int face = 0; // {N,W,E,S}==>{0,1,2,3}

volatile float currentMapLocationX = 1;
volatile float currentMapLocationY = 1;
volatile float dropLocationX = 1;
volatile float dropLocationY = 3;
volatile float objectLocationX = 1;
volatile float objectLocationY = 1;
volatile float homeLocation[2] = {0,0};

int point[3][2] = {{1,1}, {1,3}, {1,1}}; 

volatile int prevColor = currentColor; //{orange,ciyan,green,voliet,white,black} ==> {0,1,2,3,4,5}
//volatile int state = forward;

volatile bool object = false;
volatile bool onDrop = false;


void setup() {
  pinMode(ln1, INPUT);
  pinMode(ln2,INPUT);
  pinMode(sonicTrig,OUTPUT);
  pinMode(sonicEcho,INPUT);
  pinMode(motorA1,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorB2,OUTPUT);
  analogWrite(motorPowerA, 160);
  analogWrite(motorPowerB, 120);
  Serial.begin(9600);

}

void loop(){
    onLine();
    //Movement();
    if(currentMapLocationX == objectLocationX && currentMapLocationY == objectLocationY){
      pointMovement();
    }
}

void Movement(){
    switch(face){
        case 0:
        if(currentMapLocationY < objectLocationY){
            sonicSensor();
            delay(400);
            state = Forward;
            switchState();
        }
        else if (currentMapLocationY == objectLocationY){
            if(currentMapLocationX < objectLocationX){
                rotateRight();
                faceChangeRight();
            }
            else if(currentMapLocationX == objectLocationX){
                state = Stop;
                switchState();
            }
            else if (currentMapLocationX > objectLocationX){
                rotateLeft();
                faceChangeLeft();
            }
        }
        else if(currentMapLocationY > objectLocationY){
            if (currentMapLocationX == 1 && currentMapLocationY == 1){
                //This case doesent exist

            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4){
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1){
                // TDE
            }
            else if(currentMapLocationX ==5 && currentMapLocationY ==4){
                rotateLeft();
                faceChangeLeft();
            }
            else{
                rotateRight();
                faceChangeRight();
            }
        }
        break;

        case 1:
        if(currentMapLocationX < objectLocationX){
            if (currentMapLocationX == 1 && currentMapLocationY == 1){
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4){
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1){
                // TDE
            }
            else if(currentMapLocationX ==5 && currentMapLocationY ==4){
                // rotateLeft();
                // faceChangeLeft();
            }
            else{
                rotateRight();
                faceChangeRight();
            }

        }
        else if (currentMapLocationX == objectLocationX){
            if(currentMapLocationY < objectLocationY){
                rotateRight();
                faceChangeRight();
            }
            else if(currentMapLocationY == objectLocationY){
                state = Stop;
                switchState();
            }
            else if (currentMapLocationY > objectLocationY){
                rotateLeft();
                faceChangeLeft();
            }
        }
        else if(currentMapLocationX > objectLocationX){
            sonicSensor();
            delay(400);
            state = Forward;
            switchState();
        }
        break;
        break;

        case 2:
        if(currentMapLocationY < objectLocationY){
            if (currentMapLocationX == 1 && currentMapLocationY == 1){
                //This case doesent exist

            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4){
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1){
                // TDE
            }
            else if(currentMapLocationX ==5 && currentMapLocationY ==4){
                rotateRight();
                faceChangeRight();
            }
            else{
                rotateRight();
                faceChangeRight();
            }
        }
        else if (currentMapLocationY == objectLocationY){
            if(currentMapLocationX < objectLocationX){
                rotateLeft();
                faceChangeLeft();
            }
            else if(currentMapLocationX == objectLocationX){
                state = Stop;
                switchState();
            }
            else if (currentMapLocationX > objectLocationX){
                rotateRight();
                faceChangeRight();
            }
        }
        else if(currentMapLocationY > objectLocationY){
            sonicSensor();
            delay(400);
            state = Forward;
            switchState();
        }
        break;

        case 3:
        if(currentMapLocationX < objectLocationX){
            sonicSensor();
            delay(400);
            state = Forward;
            switchState();
        }
        else if (currentMapLocationX == objectLocationX){
            if(currentMapLocationY < objectLocationY){
                rotateLeft();
                faceChangeLeft();
            }
            else if(currentMapLocationY == objectLocationY){
                state = Stop;
                switchState();
            }
            else if (currentMapLocationY > objectLocationY){
                rotateRight();
                faceChangeRight();
            }
        }
        else if(currentMapLocationX > objectLocationX){
            if (currentMapLocationX == 1 && currentMapLocationY == 1){
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4){
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1){
                // TDE
            }
            else if(currentMapLocationX ==5 && currentMapLocationY ==4){
                // rotateLeft();
                // faceChangeLeft();
            }
            else{
                rotateRight();
                faceChangeRight();
            }
        }
        break;
    }
}

// once it combletely out of the line it starts turning non stop to left
void onLine() 
{
   if(digitalRead(ln1) == HIGH && digitalRead (ln2) == HIGH)
  {
    change = true;
    state = Forward;          
     
  }
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==LOW)
  {
    state = Left;
  }
   if(digitalRead(ln1)==LOW && digitalRead(ln2)==HIGH)
   {
    state = Right;
  
  }
  if (digitalRead (ln1)== LOW && digitalRead(ln2)== LOW)
  {
    if (change == true){
      change = false;
      mapp();
    //   sonicSensor();
    }
    state = Stop;
    switchState();
    // sonicSensor();
    // delay(400);
    Movement();
  }
  switchState();
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

      case Backward:
      //analogWrite(motorPowerA,180);
      //analogWrite(motorPowerB,100);
      
      digitalWrite(motorA1,LOW);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,HIGH);
      digitalWrite(motorB2,HIGH);
      break;
    
  }
}
void rotateLeft()
{
  
      state = Backward;
      switchState();
      state = Stop;
      digitalWrite(motorA1,LOW);
      digitalWrite(motorB1,HIGH);
      digitalWrite(motorA2,HIGH);
      digitalWrite(motorB2,LOW);
      delay(500);
}
void rotateRight()
{
  
      state = Backward;
      switchState();
      state = Stop;
      digitalWrite(motorA1,HIGH);
      digitalWrite(motorB1,LOW);
      digitalWrite(motorA2,LOW);
      digitalWrite(motorB2,HIGH);
      delay(500);
}

void mapp(){
    switch(face){
        case 0:
        currentMapLocationY += 1;
        break;
        case 1:
        currentMapLocationX -= 1;
        break;
        case 2:
        currentMapLocationY -= 1;
        break;
        case 3:
        currentMapLocationX += 1;
        break;
    }
}
void pointMovement(){
    size_t size = sizeof(point)/sizeof(point[0]);
       // Serial.println(i);
       if(i+1 < size){
        if(point[i+1] != NULL){
            objectLocationX = point[i+1][0];
            objectLocationY = point[i+1][1];
            i += 1;
            
        }
        else{
            state = Stop;
            switchState();
            object = true;
        }
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

void sonicSensor(){
  long int duration;
  int distance;
  
  digitalWrite(sonicTrig,HIGH);
  digitalWrite(sonicTrig,LOW);
  duration = pulseIn(sonicEcho,HIGH);
  distance = duration*0.0343/2;
  if (distance < 35 && distance > 0){
    rotateLeft();
    faceChangeLeft();
    }
}
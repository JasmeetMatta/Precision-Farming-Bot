
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
#define motorPowerA 10
#define motorPowerB 3
#define S0 9
#define S1 7
#define S2 6
#define S3 5
#define sensorOut 8

volatile int state = Forward;
volatile int duration = 0;
volatile long distance = 0;


volatile bool atObject = false,atDrop = false,change = false;

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;


int currentColor = 2;


volatile int face = 2; // {N,W,E,S}==>{0,1,2,3}

volatile float currentMapLocationX = 0;
volatile float currentMapLocationY = 0;
volatile float dropLocationX = 3;
volatile float dropLocationY = 4;
volatile float objectLocationX = 1;
volatile float objectLocationY = 1;
volatile float homeLocation[2] = {0,0};

int point[3][2] = {{1,1}, {3,3}, {5,2}}; 

volatile int prevColor = currentColor; //{orange,ciyan,green,voliet,white,black} ==> {0,1,2,3,4,5}
//volatile int state = forward;

volatile bool object = false;
volatile bool onDrop = false;


void setup(){
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
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  Serial.begin(9600);
}
void loop (){
    pointMovement();
}
void colorCall(){
    getRedPW();
    getBluePW();
    getGreenPW();
    getColor();
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

void onLine(){
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==HIGH){
  state = Forward;
  change = true;
  }
  if(digitalRead(ln1)==HIGH && digitalRead(ln2)==LOW){
  state = Left;
  }
  if(digitalRead(ln1)==LOW && digitalRead(ln2)==HIGH){
  state = Right;
  }
  if(digitalRead(ln1)==LOW && digitalRead(ln2)==LOW){
    if (change == true){
      change = false;
      mapp();
      //state = Forward;
    }
  }
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
int getBluePW(){

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
void getColor(){
    int color;
    if ((redPW >= 114 && redPW <= 150) && (greenPW >= 324 && greenPW <= 350) && (bluePW >= 364 && bluePW <= 395))
    {
        currentColor = 0; // orange
    }
    else if ((redPW >= 320 && redPW <= 340) && (greenPW >= 505 && greenPW <= 520) && (bluePW >= 235 && bluePW <= 355))
    {
        currentColor = 3; // purple
    }
    else if ((redPW >= 174 && redPW <= 230) && (greenPW >= 190 && greenPW <= 210) && (bluePW >= 320 && bluePW <= 335))
    {
        currentColor = 2; // green
    }
    else if ((redPW >= 232 && redPW <= 290) && (greenPW >= 170 && greenPW <= 190) && (bluePW >= 130 && bluePW <= 160))
    {
        currentColor = 1; // cyan
    }
    else if ((redPW >= 90 && redPW <= 108) && (greenPW >= 95 && greenPW <= 115) && (bluePW >= 80 && bluePW <= 95))
    {
        currentColor = 4; // white
    }
    else if (((redPW >= 900 && redPW <= 960) && (greenPW >= 1000 && greenPW <= 1065) && (bluePW >= 800 && bluePW <= 860)) || ((redPW >= 622 && redPW <= 750) && (greenPW >= 710 && greenPW <= 810) && (bluePW >= 500 && bluePW <= 677)))
    {
        currentColor = 5; // black
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
void rotateRight(){
  Serial.println("RR");
  }
void rotateLeft(){
  Serial.println("RL");
}

void pointMovement(){
    size_t size = sizeof(point)/sizeof(point[0]);
    for(int i=0;i<size;i++){
        if(point[i+1] != NULL){
            currentMapLocationX = point[i][0];
            currentMapLocationY = point[i][1];
            objectLocationX = point[i+1][0];
            objectLocationY = point[i+1][1];
            Movement();
        }
        else{
            currentMapLocationX = point[i][0];
            currentMapLocationY = point[i][1];
            state = Stop;
            switchState();
            object = true;
        }
    }
}

void Movement(){
    switch(face){
        case 0:
            //Serial.print("Facing North");
            if(object == false && objectLocationY > currentMapLocationY){
                do{
                    state = Forward;
                    switchState();
                    onLine();
                    switchState();
                    if (change == true){
                        state = Stop;
                        switchState();
                    }
                }while(currentMapLocationX != objectLocationX);
            }
            else if(object == false && objectLocationY == currentMapLocationY){
                if(objectLocationX > currentMapLocationX){
                    onLine();
                    rotateRight;
                    faceChangeRight;
                }
                else if (objectLocationX == currentMapLocationX){
                    onLine();
                    state = Stop;
                    switchState();
                    //object = true;
                }
                else if (objectLocationX < currentMapLocationX){
                    onLine();
                    rotateLeft;
                    faceChangeLeft;
                }
            }
        case 1:
            if(object == false && objectLocationX < currentMapLocationX){
                do{
                    state = Forward;
                    switchState();
                    onLine();
                    switchState();
                    if (change == true){
                        state = Stop;
                        switchState();
                    }
                }while(currentMapLocationX != objectLocationX);
            }
            else if(object == false && objectLocationX == currentMapLocationX){
                if(objectLocationY > currentMapLocationY){
                    onLine();
                    rotateRight;
                    faceChangeRight;
                }
                else if (objectLocationY == currentMapLocationY){
                    onLine();
                    state = Stop;
                    switchState();
                    object = true;
                }
                else if (objectLocationY < currentMapLocationY){
                    onLine();
                    rotateLeft;
                    faceChangeLeft;
                }
            }
        case 2:
            if(object == false && objectLocationY < currentMapLocationY){
                do{
                    state = Forward;
                    switchState();
                    onLine();
                    switchState();
                    if (change == true){
                        state = Stop;
                        switchState();
                    }
                }while(currentMapLocationX != objectLocationX);
            }
            else if(object == false && objectLocationY == currentMapLocationY){
                if(objectLocationX < currentMapLocationX){
                    onLine();
                    rotateRight;
                    faceChangeRight;
                }
                else if (objectLocationX == currentMapLocationX){
                    onLine();
                    state = Stop;
                    switchState();
                    object = true;
                }
                else if (objectLocationX > currentMapLocationX){
                    onLine();
                    rotateLeft;
                    faceChangeLeft;
                }
            }
        case 3:
            if(object == false && objectLocationX > currentMapLocationX){
                do{
                    state = Forward;
                    switchState();
                    onLine();
                    switchState();
                    if (change == true){
                        state = Stop;
                        switchState();
                    }
                }while(currentMapLocationX != objectLocationX);
            }
            else if(object == false && objectLocationX == currentMapLocationX){
                if(objectLocationY < currentMapLocationY){
                    onLine();
                    rotateRight;
                    faceChangeRight;
                }
                else if (objectLocationY == currentMapLocationY){
                    onLine();
                    state = Stop;
                    switchState();
                    object = true;
                }
                else if (objectLocationY > currentMapLocationY){
                    onLine();
                    rotateLeft;
                    faceChangeLeft;
                }
            }
    }
}
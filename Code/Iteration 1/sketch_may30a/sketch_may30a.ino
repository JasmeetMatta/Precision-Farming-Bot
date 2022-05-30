// Define color sensor pins

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
volatile int dropLocation[2] = {0,0};
volatile int homeLocation[2] = {0,0};

volatile int prevColor = 0; //{orange,ciyan,green,voliet,white,black} ==> {0,1,2,3,4,5}

//volatile int state = forward;

void setup() {

  // Set S0 - S3 as outputs
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

void loop() {
  
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

int getColor()
{
    int color;
    if ((redPW >= 114 && redPW <= 150) && (greenPW >= 324 && greenPW <= 350) && (bluePW >= 364 && bluePW <= 395))
    {
        color = 0; // orange
    }
    else if ((redPW >= 320 && redPW <= 340) && (greenPW >= 505 && greenPW <= 520) && (bluePW >= 235 && bluePW <= 355))
    {
        color = 3; // purple
    }
    else if ((redPW >= 174 && redPW <= 230) && (greenPW >= 190 && greenPW <= 210) && (bluePW >= 320 && bluePW <= 335))
    {
        color = 2; // green
    }
    else if ((redPW >= 232 && redPW <= 290) && (greenPW >= 170 && greenPW <= 190) && (bluePW >= 130 && bluePW <= 160))
    {
        color = 1; // cyan
    }
    else if ((redPW >= 90 && redPW <= 108) && (greenPW >= 95 && greenPW <= 115) && (bluePW >= 80 && bluePW <= 95))
    {
        color = 4; // white
    }
    else if (((redPW >= 900 && redPW <= 960) && (greenPW >= 1000 && greenPW <= 1065) && (bluePW >= 800 && bluePW <= 860)) || ((redPW >= 622 && redPW <= 750) && (greenPW >= 710 && greenPW <= 810) && (bluePW >= 500 && bluePW <= 677)))
    {
        color = 5; // black
    }
    return color;
}

void StateMachine(){
  switch(prevColor){
    case 0:
    if(currentColor == 1 && face == 2){
      currentMapLocation[1]=currentMapLocation[1]+0.5;}
    if(currentColor == 1 && face == 1){
      currentMapLocation[1]=currentMapLocation[1]-0.5;}
    break;
    case 1:
    if(currentColor == 0 && face == 2){
      currentMapLocation[1]=currentMapLocation[1]+0.5;}
    if(currentColor == 0 && face == 1){
      currentMapLocation[1]=currentMapLocation[1]-0.5;}
    break;
    case 2:
    if(currentColor == 3 && face == 0){
      currentMapLocation[0]=currentMapLocation[0]+0.5;}
    if(currentColor == 3 && face == 3){
      currentMapLocation[0]=currentMapLocation[0]-0.5;}
    break;
    case 3:
    if(currentColor == 2 && face == 0){
      currentMapLocation[0]=currentMapLocation[0]+0.5;}
    if(currentColor == 2 && face == 3){
      currentMapLocation[0]=currentMapLocation[0]-0.5;}
    break;
    }
 
  }

void faceCgangeLeft(){
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

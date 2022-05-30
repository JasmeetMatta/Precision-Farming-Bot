

volatile int face = 0; // {N,W,E,S}==>{0,1,2,3}
volatile int currentMapLocation[2] = {0,0};
volatile int dropLocation[2] = {0,0};
volatile int homeLocation[2] = {0,0};

volatile int color = 0; //{orange,ciyan,green,voliet} ==> {0,1,2,3}

//volatile int state = forward;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  StateMachine();
  faceCgangeLeft();
  faceChangeRight();

}

void StateMachine(){
  switch(color){
    case 0:
    if(color == 1 && face == 2){
      currentMapLocation[1]=currentMapLocation[1]+0.5;}
    if(color == 1 && face == 1){
      currentMapLocation[1]=currentMapLocation[1]-0.5;}
    break;
    case 1:
    if(color == 0 && face == 2){
      currentMapLocation[1]=currentMapLocation[1]+0.5;}
    if(color == 0 && face == 1){
      currentMapLocation[1]=currentMapLocation[1]-0.5;}
    break;
    case 2:
    if(color == 3 && face == 0){
      currentMapLocation[0]=currentMapLocation[0]+0.5;}
    if(color == 3 && face == 3){
      currentMapLocation[0]=currentMapLocation[0]-0.5;}
    break;
    case 3:
    if(color == 2 && face == 0){
      currentMapLocation[0]=currentMapLocation[0]+0.5;}
    if(color == 2 && face == 3){
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
 

#define ln1 2 // right ir
#define ln2 4
#define sonicTrig 12
#define sonicEcho 11 // 13
#define motorA1 A1   // right motor
#define motorA2 A2
#define motorB1 A3
#define motorB2 A4
#define S0 9
#define S1 7
#define S2 6
#define S3 5
#define sensorOut 8
#define motorPowerA 10
#define motorPowerB 3

#define Forward 100
#define Right 110
#define Left 120
#define Stop 400
#define Backward 500

volatile int counter, state = Forward;
volatile int duration = 0;
volatile long distance = 0;
volatile bool change = false;
// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
int i = 0;
int currentColor = 2;
volatile int face = 0; // {N,W,S,E}==>{0,1,2,3}
volatile float currentMapLocationX = 1;
volatile float currentMapLocationY = 1;
volatile float dropLocationX = 1;
volatile float dropLocationY = 1;
volatile float objectLocationX = 1;
volatile float objectLocationY = 1;
volatile float homeLocation[2] = {0, 0};
volatile int prevColor = currentColor; //{orange,ciyan,green,voliet,white,black} ==> {0,1,2,3,4,5}
// volatile int state = forward;
volatile bool object = false;
volatile bool onDrop = false;

// update the point via prof.
int point[4][2] = {{1, 1}, {2, 2}, {1, 1}};

void setup()
{
    pinMode(ln1, INPUT);
    pinMode(ln2, INPUT);
    pinMode(sonicTrig, OUTPUT);
    pinMode(sonicEcho, INPUT);
    pinMode(motorA1, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB2, OUTPUT);
    analogWrite(motorPowerA, 160);
    analogWrite(motorPowerB, 120);
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    Serial.begin(9600);
}

void loop()
{
    onLine();
    // Movement();
    if (currentMapLocationX == objectLocationX && currentMapLocationY == objectLocationY)
    {
        pointMovement();
    }
}
/*This Is the main algorithm which lets the bot decide where to go and how to go wrt points  */
void Movement()
{
    switch (face)
    {
    case 0:
        if (currentMapLocationY < objectLocationY)
        {
            state = Forward;
            switchState();
        }
        else if (currentMapLocationY == objectLocationY)
        {
            if (currentMapLocationX < objectLocationX)
            {
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationX == objectLocationX)
            {
                state = Stop;
                switchState();
            }
            else if (currentMapLocationX > objectLocationX)
            {
                rotateLeft();
                faceChangeLeft();
            }
        }
        else if (currentMapLocationY > objectLocationY)
        {
            if (currentMapLocationX == 1 && currentMapLocationY == 1)
            {
                // This case doesent exist
            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4)
            {
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1)
            {
                // TDE
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 4)
            {
                rotateLeft();
                faceChangeLeft();
            }
            else
            {
                rotateRight();
                faceChangeRight();
            }
        }
        break;

    case 1:
        if (currentMapLocationX < objectLocationX)
        {
            if (currentMapLocationX == 1 && currentMapLocationY == 1)
            {
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4)
            {
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1)
            {
                // TDE
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 4)
            {
                // rotateLeft();
                // faceChangeLeft();
            }
            else
            {
                rotateRight();
                faceChangeRight();
            }
        }
        else if (currentMapLocationX == objectLocationX)
        {
            if (currentMapLocationY < objectLocationY)
            {
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationY == objectLocationY)
            {
                state = Stop;
                switchState();
            }
            else if (currentMapLocationY > objectLocationY)
            {
                rotateLeft();
                faceChangeLeft();
            }
        }
        else if (currentMapLocationX > objectLocationX)
        {
            state = Forward;
            switchState();
        }
        break;
        

    case 2:
        if (currentMapLocationY < objectLocationY)
        {
            if (currentMapLocationX == 1 && currentMapLocationY == 1)
            {
                // This case doesent exist
            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4)
            {
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1)
            {
                // TDE
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 4)
            {
                rotateRight();
                faceChangeRight();
            }
            else
            {
                rotateRight();
                faceChangeRight();
            }
        }
        else if (currentMapLocationY == objectLocationY)
        {
            if (currentMapLocationX < objectLocationX)
            {
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationX == objectLocationX)
            {
                state = Stop;
                switchState();
            }
            else if (currentMapLocationX > objectLocationX)
            {
                rotateRight();
                faceChangeRight();
            }
        }
        else if (currentMapLocationY > objectLocationY)
        {
            state = Forward;
            switchState();
        }
        break;

    case 3:
        if (currentMapLocationX < objectLocationX)
        {
            state = Forward;
            switchState();
        }
        else if (currentMapLocationX == objectLocationX)
        {
            if (currentMapLocationY < objectLocationY)
            {
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationY == objectLocationY)
            {
                state = Stop;
                switchState();
            }
            else if (currentMapLocationY > objectLocationY)
            {
                rotateRight();
                faceChangeRight();
            }
        }
        else if (currentMapLocationX > objectLocationX)
        {
            if (currentMapLocationX == 1 && currentMapLocationY == 1)
            {
                rotateLeft();
                faceChangeLeft();
            }
            else if (currentMapLocationX == 1 && currentMapLocationY == 4)
            {
                rotateRight();
                faceChangeRight();
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 1)
            {
                // TDE
            }
            else if (currentMapLocationX == 5 && currentMapLocationY == 4)
            {
                // rotateLeft();
                // faceChangeLeft();
            }
            else
            {
                rotateRight();
                faceChangeRight();
            }
        }
        break;
    }
}

// This is to keep bot allign
void onLine()
{
    if (digitalRead(ln1) == HIGH && digitalRead(ln2) == HIGH)
    {
        change = true;
        state = Forward;
    }
    if (digitalRead(ln1) == HIGH && digitalRead(ln2) == LOW)
    {
        state = Left;
    }
    if (digitalRead(ln1) == LOW && digitalRead(ln2) == HIGH)
    {
        state = Right;
    }
    if (digitalRead(ln1) == LOW && digitalRead(ln2) == LOW)
    {
        if (change == true)
        {
            change = false;
            mapp(); // Here we are updating the position on map
        }
        state = Stop;
        switchState();
        Movement();
    }
    switchState();
}
// This is to rotate motor
void switchState()
{
    switch (state)
    {
    case Stop:
        digitalWrite(motorA1, LOW);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB2, LOW);
        break;

    case Forward:
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB2, LOW);
        break;

    case Right:
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorA2, LOW);
        digitalWrite(motorB2, HIGH);
        break;

    case Left:
        digitalWrite(motorA1, LOW);
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorA2, HIGH);
        digitalWrite(motorB2, LOW);
        break;

    case Backward:
        digitalWrite(motorA1, LOW);
        digitalWrite(motorB1, LOW);
        digitalWrite(motorA2, HIGH);
        digitalWrite(motorB2, HIGH);
        break;
    }
}
void rotateLeft()
{
    state = Backward;
    switchState();
    state = Left;
    switchState();
    delay(500);
}
void rotateRight()
{
    state = Backward;
    switchState();
    state = Right;
    switchState();
    delay(500);
}

// here we are updating map points wrt to face
void mapp()
{
    switch (face)
    {
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

// here we are telling bot the next postion he has to go to
void pointMovement()
{
    size_t size = sizeof(point) / sizeof(point[0]);
    // Serial.println(i);
    if (i + 1 < size)
    {
        if (point[i + 1] != NULL)
        {
            objectLocationX = point[i + 1][0];
            objectLocationY = point[i + 1][1];
            i += 1;
        }
        else
        {
            state = Stop;
            switchState();
            object = true;
        }
    }
}

// Using circular pattern we can know face the bot is facing easily
void faceChangeLeft()
{
    if (face == 3)
    {
        face = 0;
    }
    else
    {
        face += 1;
    }
}
void faceChangeRight()
{

    if (face == 0)
    {
        face = 3;
    }
    else
    {
        face -= 1;
    }
}

// This is to get red using filter  s2 s3
int getRedPW()
{
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    int PW;
    PW = pulseIn(sensorOut, LOW);
    return PW;
}


// This is to get Green using filter  s2 s3
int getGreenPW()
{
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    int PW;
    PW = pulseIn(sensorOut, LOW);
    return PW;
}
// This is to get Blue using filter  s2 s3
int getBluePW()
{
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    int PW;
    PW = pulseIn(sensorOut, LOW);
    return PW;
}

// This is to update the color variable and also to calibrate the readings
void getColor(){
    if ((redPW >= 114 && redPW <= 150) && (greenPW >= 324 && greenPW <= 350) && (bluePW >= 364 && bluePW <= 395))
    {
        currentColor = 0;} // orange
    else if ((redPW >= 320 && redPW <= 340) && (greenPW >= 505 && greenPW <= 520) && (bluePW >= 235 && bluePW <= 355))
    {
        currentColor = 3;} // purple
    else if ((redPW >= 174 && redPW <= 230) && (greenPW >= 190 && greenPW <= 210) && (bluePW >= 320 && bluePW <= 335))
    {
        currentColor = 2;} // green
    else if ((redPW >= 232 && redPW <= 290) && (greenPW >= 170 && greenPW <= 190) && (bluePW >= 130 && bluePW <= 160))
    {
        currentColor = 1;} // cyan
    else if ((redPW >= 90 && redPW <= 108) && (greenPW >= 95 && greenPW <= 115) && (bluePW >= 80 && bluePW <= 95))
    {
        currentColor = 4;} // white
    else if (((redPW >= 900 && redPW <= 960) && (greenPW >= 1000 && greenPW <= 1065) && (bluePW >= 800 && bluePW <= 860))
    || ((redPW >= 622 && redPW <= 750) && (greenPW >= 710 && greenPW <= 810) && (bluePW >= 500 && bluePW <= 677)))
    { // if it detects gray or black will consider it black
        currentColor = 5;} // black
}
// This code is to get current color
void colorCall()
{
    redPW = getRedPW();
    bluePW = getBluePW();
    greenPW = getGreenPW();
    getColor();
}

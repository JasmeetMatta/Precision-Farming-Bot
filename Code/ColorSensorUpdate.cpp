
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

char currentColor;

void setup()
{

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

    // Setup Serial Monitor
    Serial.begin(9600);
}

void loop()
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
    }
    else if ((redPW >= 320 && redPW <= 370) && (greenPW >= 505 && greenPW <= 570) && (bluePW >= 235 && bluePW <= 355))
    {
        color = 'p'; // purple
    }
    else if ((redPW >= 174 && redPW <= 230) && (greenPW >= 190 && greenPW <= 240) && (bluePW >= 320 && bluePW <= 385))
    {
        color = 'g'; // green
    }
    else if ((redPW >= 232 && redPW <= 300) && (greenPW >= 170 && greenPW <= 210) && (bluePW >= 130 && bluePW <= 160))
    {
        color = 'c'; // cyan
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
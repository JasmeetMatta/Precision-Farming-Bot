#define sonicTrig 12
#define sonicEcho 11
volatile int duration, distance;
volatile bool objectDetected= false;
void setup() {
  // put your setup code here, to run once:
   pinMode(sonicTrig,OUTPUT);
   pinMode(sonicEcho,INPUT);
   Serial.begin(9600);
}

void loop() {
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

    objectDetected= true;
    
  }
  else
  {
    objectDetected= false;
  }
}

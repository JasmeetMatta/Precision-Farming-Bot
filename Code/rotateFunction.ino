void rotateLeft()
{
  do{
   digitalWrite(motor1A,HIGH);
   digitalWrite(motor1B,LOW);
   digitalWrite(motor2A,LOW);
   digitalWrite(motor2B,HIGH);
  } while (currentColor == prevColor);
  
  
}
 void rotateRight()
 {
   do
   {
   digitalWrite(motor1A,LOW);
   digitalWrite(motor1B,HIGH);
   digitalWrite(motor2A,HIGH);
   digitalWrite(motor2B,LOW);
   } while (while (currentColor == prevColor);
 }
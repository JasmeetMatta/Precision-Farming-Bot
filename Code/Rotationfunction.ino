
void rotateLeft()
{
  line();
  if ( (currentColor == 3) &&( face == 0))
  {
    do
    {
     digitalWrite(motor1A,HIGH);
     digitalWrite(motor1B,LOW);
     digitalWrite(motor2A,LOW);
     digitalWrite(motor2B,HIGH);
    } while (currentColor == prevColor);
  }
  
  if ( (currentColor == 2) &&( face == 3))
  {
    do
    {
     digitalWrite(motor1A,HIGH);
     digitalWrite(motor1B,LOW);
     digitalWrite(motor2A,LOW);
     digitalWrite(motor2B,HIGH);
    } while (currentColor == prevColor);
  }
    if ( (currentColor == 1) &&( face == 2))
  {
    do
    {
     digitalWrite(motor1A,HIGH);
     digitalWrite(motor1B,LOW);
     digitalWrite(motor2A,LOW);
     digitalWrite(motor2B,HIGH);
    } while (currentColor == prevColor);
    
  }
    if ( (currentColor == 0) &&( face == 1))
  {
  do{
   digitalWrite(motor1A,HIGH);
   digitalWrite(motor1B,LOW);
   digitalWrite(motor2A,LOW);
   digitalWrite(motor2B,HIGH);
  } while (currentColor == prevColor);
  }
  
}
 void rotateRight()
 {
   if ( (currentColor == 0) &&( face == 1))
   {
     do
     {
     digitalWrite(motor1A,LOW);
     digitalWrite(motor1B,HIGH);
     digitalWrite(motor2A,HIGH);
     digitalWrite(motor2B,LOW);
     } while (while (currentColor == prevColor);
   }
   if ( (currentColor == 3) &&( face == 0))
   {
      do
       {
       digitalWrite(motor1A,LOW);
       digitalWrite(motor1B,HIGH);
       digitalWrite(motor2A,HIGH);
       digitalWrite(motor2B,LOW);
       } while (while (currentColor == prevColor);
   }
   if ( (currentColor == 1) &&( face == 2))
   {
       do
         {
         digitalWrite(motor1A,LOW);
         digitalWrite(motor1B,HIGH);
         digitalWrite(motor2A,HIGH);
         digitalWrite(motor2B,LOW);
         } while (while (currentColor == prevColor);
   }
   if ( (currentColor == 2) &&( face == 3))
   {
       do
         {
         digitalWrite(motor1A,LOW);
         digitalWrite(motor1B,HIGH);
         digitalWrite(motor2A,HIGH);
         digitalWrite(motor2B,LOW);
         } while (while (currentColor == prevColor);
   }
 }
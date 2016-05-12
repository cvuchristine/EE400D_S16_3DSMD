void move_reel(int pin)
{
while(servoCount<durationServo)
 {
    //Start turning clockwise
  reelservo.attach(pin);
  reelservo.write(0);
    // Go on turning for the right duration
    
    servoCount++;
  }
  //stop turning 
  servoCount = 1;
  reelservo.detach();
}

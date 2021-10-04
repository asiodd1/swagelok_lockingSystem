const int clkPin= 2; //the clk attach to pin2
const int dtPin= 3; //the dt attach to pin3
const int swPin= 4 ;//the number of the button
int encoderVal = 0;

void setup()
{ 
  //set clkPin,dePin,swPin as INPUT
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);
  Serial.begin(9600); // initialize serial communications at 9600 bps
}

void loop()
{
  int change = getEncoderTurn();
  encoderVal = encoderVal + change;
  if(digitalRead(swPin) == LOW)//if button pull down
  {
    encoderVal = 0;
  }
  Serial.println(encoderVal); //print the encoderVal on the serial monitor
  
}

int getEncoderTurn(void)
{
  static int oldA = HIGH; //set the oldA as HIGH
  int oldB = HIGH; //set the oldB as HIGH
  int result = 0;
  int newA = digitalRead(dtPin);//read the value of clkPin to newA
  int newB = digitalRead(clkPin);//read the value of dtPin to newB

  
  if (newA != oldA || newB != oldB) //if the value of clkPin or the dtPin has changed
  {
    // something has changed
    if (oldB == HIGH && newB == LOW)
    {
      result = (oldA * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  //Serial.println(newB);
  //Serial.println(newA);
  return result;
}

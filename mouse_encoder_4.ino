
// 定义引脚2.3
int APhase = 3;
int BPhase = 2;

long count = 0;//计数

void setup() 
{
  Serial.begin(9600);
  pinMode(APhase, INPUT);//上拉电阻
  pinMode(BPhase, INPUT);
  Serial.println("set up");
  delay(1000);
}

void loop()
{
  static int oldA = digitalRead(APhase);
  static int oldB = digitalRead(BPhase);
  int newA = digitalRead(APhase);
  int newB = digitalRead(BPhase);
  if (oldA != newA )
  {
    if (oldA == 1)
    {
      delay(5);
      //int newB = digitalRead(BPhase);
      if (oldB == 0)
        {
          count--;
          Serial.println(count);
        }
      if (oldB == 1)
        {
          count++;
          Serial.println(count);
        }
    }
    else if (oldA == 0)
    {
      delay(5);
      //int newB = digitalRead(BPhase);
      if (newB == 1)
      { count--;
        Serial.println(count);
      }
      if (newB == 0)
      {
        count++;
        Serial.println(count);
      }
    }
  }
  //int newB = digitalRead(BPhase);
  oldA = newA;
  oldB = newB;
  delay(5);//延时增加程序稳定性
}

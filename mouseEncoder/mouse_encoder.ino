
#define DEBOUNCE_TIME 8  //延时用来过滤不正常的信号，此数字太大的话会对快速的旋转不起反应

// 定义引脚2.3
int APhase = 3;
int BPhase = 2;

long count = 0;//计数
long preverCount = 0;//上一次的计数
long currentCount = 0;//当前计数

void getSpeed()
{   
  preverCount = currentCount;
  currentCount = count;
  Serial.println( "speed is " + String (currentCount - preverCount) ) ;
}

void setup() 
{
  Serial.begin(9600);
  pinMode(APhase, INPUT);//上拉电阻
  pinMode(BPhase, INPUT);
  Serial.println("set up");
  delay(1000);
  //pinMode(LED_BUILTIN,OUTPUT);
}

void loop() 
{
  int  firstAPhaseState= digitalRead(APhase);
  //digitalWrite(LED_BUILTIN,firstAPhaseState);//用板上自带的灯显示A相的状态
  if (firstAPhaseState == 1 ) 
  {
    //Serial.println(firstAPhaseState);
    delay(DEBOUNCE_TIME);
    int secendAPhaseState  = digitalRead(APhase); 
    if (secendAPhaseState  == 0) //从1变成0 开始判断是正转还是反转
    {
      Serial.println("1變成0");
      int BPhaseState = digitalRead(BPhase);
      //用B相信号判断正反转
      if (BPhaseState == 0) 
      {
        count++;
        Serial.println(count);
      }
      if (BPhaseState == 1) 
      {
        count--;
        Serial.println(count);
      }
      Serial.println("APhase"+String(secendAPhaseState));
      Serial.println("BPhase"+String(BPhaseState));
    }
  }

  if (firstAPhaseState == 0) //初始状态是0的判断，想改进的话可以用外部中断的上升沿事件 
  {
    //delay(DEBOUNCE_TIME);
    int secendAPhaseState = digitalRead(APhase);
    if (secendAPhaseState == 1) 
    {
      Serial.println("0變成1");
      
      if (digitalRead(BPhase) == 1) 
      { 
        count++;
        Serial.println(count);
      }
      if (digitalRead(BPhase) == 0) 
      {
        count--;
        Serial.println(count);
      }
      Serial.println("APhase: "+String(secendAPhaseState));
      //Serial.println("BPhase: "+String(BPhaseState));
    }
  }

  delay(1);//延时增加程序稳定性
}

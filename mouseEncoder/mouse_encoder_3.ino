
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
  //原本設定是初始oldA和oldB都為1
  static int oldA = digitalRead(APhase);
  static int oldB = digitalRead(BPhase);
  //delay(DEBOUNCE_TIME);
  int  newA = digitalRead(APhase);

  //delay(1);
  int  newB = digitalRead(BPhase);
  
  if (oldA != newA || oldB != newB)
  {
    Serial.print(newA);
    Serial.print(" ");
    Serial.println(newB);
    if (oldA == 1 && newA ==0)
    {
      if (oldB == 0) //从1变成0 开始判断是正转还是反转
        {
          count--;
          Serial.println(count);
          Serial.println("The 1   "+String(millis()));
        }
      if (oldB == 1)
        {
          count++;
          Serial.println(count);
          Serial.println("The 2   "+String(millis()));
        }
    }
    else if (oldA == 0 && newA ==1) //初始状态是0的判断，想改进的话可以用外部中断的上升沿事件 
    {
      if (newB == 1) //从1变成0 开始判断是正转还是反转
      { 
        count--;
        Serial.println(count);
        Serial.println("The 3   "+String(millis()));
      }
      if (newB == 0)
      {
        count++;
        Serial.println(count);
        Serial.println("The 4   "+String(millis()));
      }
    }
    else
    {
      if(oldB == 0)
      {
        count++;
        Serial.println(count);
        Serial.println("The 5   "+String(millis()));
      }
      else if(oldB == 1)
      {
        count--;
        Serial.println(count);
        Serial.println("The 6   "+String(millis()));
      }
    }
  }
  oldA = newA;
  oldB = newB;
  //Serial.println("step");
  delay(5);//延时增加程序稳定性
  
}

//此程式在模擬電路中如常運作，但是真實電路中運作時卻會有不如預期的異常，
//然而此異常是有規律可循的的異常：
//每轉動一格卻會跳兩次資料，每奇數格的前筆資料及偶數格的後筆資料才是正確的，
//範例資料如下：(1,0),(1,2),(3,2),(3,4),(5,4),(5,6)
//既然是有規律可循的異常，初步估計可以利用演算法解決，但是演算方法還待思考
//一種是記錄次數，靠奇偶次數來判斷，每轉一格資料跑兩筆，但是每兩筆資料經過演算後只顯示一筆

//第二種方法還在思考是靠延遲讀取或是中斷功能，有待嘗試

/* 
      Serial.print("oldA = "+String(oldA)+"  ");
      Serial.println("newA = "+String(newA));
      Serial.print("oldB = "+String(oldB)+"  ");
      Serial.println("newB = "+String(newB));
 */

/*
 * rotary_encoder接線
 * https://osoyoo.com/zh/2017/09/30/arduino-lesson-rotary-encoder/?fbclid=IwAR24G4TNoqdnQnoP9RbSEXdUuArinGbcMKlczrmfZ9kYzpCSjf4QF7IsiGA
 * 
 */
#include "HX711.h" //HX711 Arduino Library by Bogdan Necula
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

#define ledPin 7
LiquidCrystal_I2C lcd(0x27,20,4);

//滾輪編碼器接線
const int clkPin= 2; //the clk attach to pin2
const int dtPin= 3; //the dt attach to pin3
const int swPin= 4 ;//the number of the button

//秤重傳感器接線
const int DT_PIN = 6;
const int SCK_PIN = 5;
const int sample_weight =150;

float scale_factor = 0;

int encoderVal = 0;

HX711 scale;

void setup()
{ 
  //set clkPin,dePin,swPin as INPUT
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  scale.begin(DT_PIN, SCK_PIN);
  scale.set_scale();  // 開始取得比例參數
  scale.tare();

  lcd.init();
  lcd.backlight(); 
  lcd.setCursor(0,0); 
  lcd.print("Scale number:  ");
  
  digitalWrite(swPin, HIGH);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); // initialize serial communications at 9600 bps
}

void loop()
{
  scale_factor = getWeight();
  
  if(digitalRead(swPin) == LOW)//if button pull down
  {
   encoderVal = 0;
  }
  if(scale_factor>150)
  {
    digitalWrite(ledPin, HIGH);
  }
  while(scale_factor>300)
  {
   int change = getEncoderTurn();
   encoderVal = encoderVal + change;
  if(digitalRead(swPin) == LOW)//if button pull down 
  {
    encoderVal = 0; 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("The value is :");
  }
   Serial.println(encoderVal); //print the encoderVal on the serial monitor
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("The value is :");
  lcd.setCursor(4,2); 
  lcd.print(encoderVal); 
  }
  Serial.print("Scale number:  ");
  Serial.println(scale_factor,0);  // 顯示比例參數，記起來，以便用在正式的程式中
  lcd.setCursor(5,1); 
  lcd.print(scale_factor);
}
int getWeight(void)
{
  float current_weight=scale.get_units(10);  // 取得10次數值的平均
  float scale_factor=(current_weight/sample_weight);
  return scale_factor;
}
int getEncoderTurn(void)
{
  static int oldA = HIGH; //set the oldA as HIGH
  static int oldB = HIGH; //set the oldB as HIGH
  int result = 0;
  int newA = digitalRead(dtPin);//read the value of clkPin to newA
  int newB = digitalRead(clkPin);//read the value of dtPin to newB

  
  if (newA != oldA || newB != oldB)
  {
    if (oldB == HIGH && newB == LOW)
    {
      result = (oldA * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}

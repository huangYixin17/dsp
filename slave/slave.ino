//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // HC-05的TXD,RXD腳位
//LiquidCrystal_I2C lcd(0x27,16,2);  // 設定 LCD
void setup()
{
  Serial.begin(9600);
  //lcd.init();            // initialize the lcd
 // lcd.backlight();
  BTSerial.begin(9600);//38400
}
void loop()
{
  // 檢查是否有資料傳來
  if (BTSerial.available()) {
    delay(500);  //稍候一下，讓資料都到
    //lcd.clear(); //清除 LCD 畫面
    // 讀取所有資料，並顯示在 LCD
    while (BTSerial.available() > 0) {
      //lcd.write( BTSerial.read() );
     Serial.println(BTSerial.readString());
     
    }
  }
}

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // HC-05的TXD,RXD腳位
void setup() {
  BTSerial.begin(9600);
  //稍等一秒後再送資料給遠方

}
void loop()
{ 
  delay(5000);
  BTSerial.write("123");
  //
}

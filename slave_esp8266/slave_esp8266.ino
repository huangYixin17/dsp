#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // HC-05的TXD,RXD腳位
SoftwareSerial espSerial(5, 6); // esp8266的TXD,RXD腳位
int LED=13; 
String val;
String api_key="RVO07NM2HHOZK6LW";  //Thingspeak API Write Key

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
  BTSerial.begin(9600);//38400
 
  //espSerial.println("AT+RST");
}

void loop()
{
   BTSerial.begin(9600);
  // 檢查是否有資料傳來
  if (BTSerial.available()) {
    delay(500);  //稍候一下，讓資料都到
    //lcd.clear(); //清除 LCD 畫面
    // 讀取所有資料，並顯示在 LCD
    while (BTSerial.available() > 0) {
     //Serial.println(BTSerial.readString());
     val=BTSerial.readString();
     Serial.println(val);
     blink_led(1000,500);
     espSerial.begin(9600);
     String param="&field1=" +(String)val; //製作參數字串
     String cmd="AT+CIPSTART=\"TCP\",\"184.106.153.149\",80";
     espSerial.println(cmd); //向 ESP8266 傳送 TCP 連線之 AT 指令

     if (espSerial.find("Error")) {           
        Serial.println("AT+CIPSTART error!");
        return;  //連線失敗跳出目前迴圈 (不做後續傳送作業)
     }
     if(espSerial.find("CONNECT")){
        Serial.println("CONNECT");
     }
     else
        Serial.println("not conect");
     String GET="GET /update?api_key=" + api_key + param + "\r\n\r\n";
     cmd="AT+CIPSEND=" + String(GET.length()); //傳送 GET 字串長度之 AT 指令

     espSerial.println(cmd);  //告知 ESP8266 即將傳送之 GET 字串長度
     Serial.println(cmd);
     if (espSerial.find(">")) {  //若收到 ESP8266 的回應標頭結束字元
        espSerial.print(GET);  //向 ESP8266 傳送 GET 字串內容
        Serial.println(GET); 
        Serial.println("get");    
      }
     else {  //沒有收到 ESP8266 回應
        espSerial.println("AT+CIPCLOSE");  //關閉 TCP 連線
        Serial.println(espSerial.read());
     }
     delay(30000);  //延遲 16 秒 (因 Thingspeak 每次更新須隔 60 秒)
    }
  }
}

void blink_led(int on, int off) {  //LED 閃爍函式
  digitalWrite(LED, HIGH);
  delay(on);
  digitalWrite(LED, LOW);
  delay(off);
  }

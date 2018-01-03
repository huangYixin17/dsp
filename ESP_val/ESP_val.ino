#include <SoftwareSerial.h>

int LED=13; 
String api_key="RVO07NM2HHOZK6LW";  //Thingspeak API Write Key
SoftwareSerial sSerial(10,11);

void setup() {               
  pinMode(LED, OUTPUT);             //設定 DIO Pin 13 為 LED 輸出
  Serial.begin(9600);                //啟始硬體串列埠 (除錯用)
  sSerial.begin(9600);              //啟始軟體串列埠 (與 ESP8266 介接用)
  sSerial.println("AT+RST");        //軟體串列埠傳送 AT 指令重啟 ESP8266
  }

void loop() {
  float h=888;
  blink_led(1000,500); 
  String param="&field1=" + (String)h; //製作參數字串
  String cmd="AT+CIPSTART=\"TCP\",\"184.106.153.149\",80";
  sSerial.println(cmd); //向 ESP8266 傳送 TCP 連線之 AT 指令

 if (sSerial.find("Error")) {           
    Serial.println("AT+CIPSTART error!");
    return;  //連線失敗跳出目前迴圈 (不做後續傳送作業)
    }
if(sSerial.find("CONNECT")){
  Serial.println("CONNECT");
}
         
  Serial.println(cmd);  //輸出 AT 指令於監控視窗
  String GET="GET /update?api_key=" + api_key + param + "\r\n\r\n";
  Serial.println(GET);  //顯示 GET 字串內容於監控視窗 
  cmd="AT+CIPSEND=" + String(GET.length()); //傳送 GET 字串長度之 AT 指令
  Serial.println(cmd); //輸出 AT 指令於監控視窗
  
  sSerial.println(cmd);  //告知 ESP8266 即將傳送之 GET 字串長度
  
if (sSerial.find(">")) {  //若收到 ESP8266 的回應標頭結束字元
    sSerial.print(GET);  //向 ESP8266 傳送 GET 字串內容
    Serial.println("get");
    }
  else {  //沒有收到 ESP8266 回應
    sSerial.println("AT+CIPCLOSE");  //關閉 TCP 連線
    Serial.println("AT+CIPCLOSE");    //顯示連線關閉訊息於監控視窗
    Serial.println(sSerial.read());
    }
  delay(30000);  //延遲 16 秒 (因 Thingspeak 每次更新須隔 60 秒)
}

   
void blink_led(int on, int off) {  //LED 閃爍函式
  digitalWrite(LED, HIGH);
  delay(on);
  digitalWrite(LED, LOW);
  delay(off);
  }

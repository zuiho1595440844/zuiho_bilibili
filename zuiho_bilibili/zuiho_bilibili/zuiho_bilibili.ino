#include<ESP8266WiFi.h>
#include<ArduinoHttpClient.h>
#include<ArduinoJson.h>
#include"setting.h"
#include<Wire.h>
#include <U8g2lib.h>


String device_name="zuiho_bilibili"; //设备名，与python文件中保持一致
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE,14,2);//四脚0.96寸OLED，IIC控制（SDA，SCL）



const char *host="dweet.io";
WiFiClient wifi;
HttpClient client=HttpClient(wifi,host,80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connect_to_wifi();
  u8g2.begin(); 
  u8g2.setFont(u8g2_font_9x15_tf);   // 选择合适的字体
  //显示屏显示信息
  u8g2.clearBuffer();                   // 清除内存
  
  u8g2.drawStr(0,15,"Follower:");    // 将内容放入内存中  
  u8g2.drawStr(0,35,"Comment:");    // 将内容放入内存中
  u8g2.drawStr(0,55,"Play:");    // 将内容放入内存中
  u8g2.sendBuffer();                    // 将内部内存转移到显示器
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("getting state");
  String url="/get/latest/dweet/for/"+ device_name;
  //连接到dweet.io
  client.get(url);

  int statusCode =client.responseStatusCode();
  String response=client.responseBody();
  Serial.print("Status code:");
  Serial.println(statusCode);
  Serial.println(response);

  //arduino json assistant生成
  StaticJsonDocument<384> doc;

  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  JsonObject data = doc["with"][0];
  
  JsonObject with_0 = doc["with"][0];
  

  JsonObject with_0_content = with_0["content"];
  String follower = with_0_content["follower: "]; //取出需要部分
  String comment = with_0_content["comment: "]; 
  String totalplay = with_0_content["play: "]; 
  //
  //串口打印信息
  Serial.printf("follower:%s\n",follower.c_str());
  Serial.printf("comment:%s\n",comment.c_str());
  Serial.printf("play:%s\n",totalplay.c_str());
  
  /*
  display.clearDisplay();
  display.fillScreen(WHITE);
  display.display();
  */
  //显示屏显示信息
  u8g2.clearBuffer();                   // 清除内存
  
  u8g2.drawStr(0,15,"Follower:");    // 将内容放入内存中  
  u8g2.drawStr(80,15,follower.c_str());    // 将内容放入内存中 c_str()将string转为char*
  u8g2.drawStr(0,35,"Comment:");    // 将内容放入内存中
  u8g2.drawStr(80,35,comment.c_str());    // 将内容放入内存中
  u8g2.drawStr(0,55,"Play:");    // 将内容放入内存中
  u8g2.drawStr(50,55,totalplay.c_str());    // 将内容放入内存中
  u8g2.sendBuffer();                    // 将内部内存转移到显示器
  
  delay(5000);
}

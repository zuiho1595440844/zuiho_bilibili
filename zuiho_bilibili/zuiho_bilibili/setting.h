#include<ESP8266WiFi.h>
//wifi用户名、密码
const char *ssid ="";
const char *password="";

void connect_to_wifi()
{
  Serial.println("setting wifi mode");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.printf("Connecting to %s",ssid);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected");
}

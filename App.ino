/**********************************************************************
项目名称/Project          : 自由物联网+
程序名称/Program name     : 单路继电器v1.0
团队/Team                : 小平科技创新团队 / IMUT-ROBOT
作者/Author              : 阿木
日期/Date（YYYYMMDD）     : 2022/03/14
程序目的/Purpose          : 给开发者提供更自由，更便捷的DIY方式。
-----------------------------------------------------------------------
本示例程序为自由物联网平台自动生成的代码
目前平台还在不断完善中。如需了解更多该教程的信息，请参考以下网页：
https://www.amgl.work/archives/122/
***********************************************************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Ticker.h>

int         config_serial_baudrate = 9600;                               //串口波特率
const char* config_wifi_ssid = "2.4G";                                   //wifi名称
const char* config_wifi_password = "AMGLAaaaaaaa";                       //wifi密码
const char* config_mqtt_server_host = "mqtt.amgl.work";                  //MQTT服务器地址
const char* config_ntp_server_host = "ntp.tencent.com";                  //NTP服务器地址
const char* config_clientAccont = "a11a1b4f1c39ff85d5ea85b94ee427b5";    //设备账户
String      config_clientToken = "1904c832a401818a64f91760b18ada63";     //密钥
String      config_clientId = "93edc6e672f64904b40ebd091e127194";        //设备ID
String      config_topicString = "105e35cc94a4fce5449d1f135f64e5df";     //私有主题

//加载模块
Ticker ticker;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

//主程序
void setup() {
  application_initialize();//应用程序初始化
}

void loop() {
}

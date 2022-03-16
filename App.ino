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
#include <MD5Builder.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Ticker.h>
Ticker ticker;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

int         debug = 1;                                                   //调试模式
int         config_serial_baudrate = 9600;                               //串口波特率
const char* config_wifi_ssid = "2.4G";                                   //wifi名称
const char* config_wifi_password = "AMGLAaaaaaaa";                       //wifi密码
const char* config_server_host_mqtt = "x7xn.ss1x.mqtt.amgl.work";        //MQTT服务器地址
const char* config_server_host_ntp = "ntp.tencent.com";                  //NTP服务器地址
String      config_client_accont = "a11a1b4f1c39ff85d5ea85b94ee427b5";   //设备账户
String      config_client_token = "1904c832a401818a64f91760b18ada63";    //设备密钥
String      config_client_id = "93edc6e672f64904b40ebd091e127194";       //设备ID
String      config_client_topic = "105e35cc94a4fce5449d1f135f64e5df";    //设备主题
String      sign = "";                                                   //设备动态密钥
String      mqtt_client_recived_data = "";                               //设备接收到的消息





/**********************************************************************
MQTT接收消息在下面，可自由发挥
***********************************************************************/
//当MQTT收到消息
void mqtt_client_recived(){
  Serial.println(mqtt_client_recived_data);
}


void setup()
{
  application_initialize(); /* 应用程序初始化 */
}

void loop()
{
  application_loop();/* 应用程序主循环 */
}

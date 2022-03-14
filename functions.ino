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
//应用程序初始化
void application_initialize(){
  Serial.begin(config_serial_baudrate);//配置串口波特率
  wifi_connect_link();//连接WIFI
}

//时间戳
int ts(){
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP,config_ntp_server_host,60*60*8, 30*60*1000);
  timeClient.begin();
  timeClient.update();
  int ts=0;
  ts = timeClient.getEpochTime()-28800;
  return ts;
}

//生成签名
String GenerateSignatureBase(int ts,String token){
   
}

//WIFI连接
void wifi_connect_link(){
    WiFi.mode(WIFI_STA);//配置WIFI模式
    Serial.print("WIFIConnecting");
    WiFi.begin(config_wifi_ssid, config_wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("WiFi Connected!");
}

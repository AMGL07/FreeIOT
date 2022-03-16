/**********************************************************************
 * 项目名称/Project          : 自由物联网+
 * 程序名称/Program name     : 单路继电器v1.0
 * 团队/Team                : 小平科技创新团队 / IMUT-ROBOT
 * 作者/Author              : 阿木
 * 日期/Date（YYYYMMDD）     : 2022/03/14
 * 程序目的/Purpose          : 给开发者提供更自由，更便捷的DIY方式。
 * -----------------------------------------------------------------------
 * 本示例程序为自由物联网平台自动生成的代码
 * 目前平台还在不断完善中。如需了解更多该教程的信息，请参考以下网页：
 * https://www.amgl.work/archives/122/
 ***********************************************************************/
/* 应用程序初始化 */
void application_initialize()
{
  Serial.begin( config_serial_baudrate ); /* 配置串口波特率 */
  wifi_module_initialization();           /* WIFI初始化 */
  wifi_module_connect();                  /* 连接WIFI */
  Serial.print( "MQTT Server Connecting ." );
  mqtt_client_auto_connect();             /* 连接MQTT服务器 */
}


/* 应用程序主循环 */
void application_loop(){
  if ( mqttClient.connected() )
  {
    mqttClient.loop();
  }else{
    mqtt_client_auto_connect();
  }
}


/* 获取时间戳 */
int ntp_cilent_get_timestamp()
{
  WiFiUDP ntpUDP;
  NTPClient timeClient( ntpUDP, config_server_host_ntp, 60*60*8, 30*60*1000 );
  timeClient.begin();
  timeClient.update();
  int ts = 0;
  ts = timeClient.getEpochTime() - 28800;
  return(ts);
}


/* 自动连接MQTT服务器 */
void mqtt_client_auto_connect()
{
  generate_signature_base();      /* 生成令牌 */
  mqtt_client_initialization();   /* MQTT客户端初始化 */
  mqtt_client_connect();          /* MQTT客户端建立连接 */
}


/* 生成签名 */
void generate_signature_base()
{
  int ts = ntp_cilent_get_timestamp();
  ts  = ceil( ts / 10 ); /* 截取9位时间戳 */
  sign  = config_client_token;
  sign  += ts;
  sign  = md5( sign.c_str() );
}


/* MQTT客户端-初始化 */
void mqtt_client_initialization()
{
  mqttClient.setCallback( mqtt_client_callback );         /* 配置MQTT回调函数 */
  mqttClient.setServer( config_server_host_mqtt, 1883 );  /* 配置MQTT服务 */
}


/* MQTT客户端回调函数 */
void mqtt_client_callback( char* topic, byte* payload, unsigned int length )
{
  mqtt_client_recived_data = "";
  for ( int i = 0; i < length; i++ )
  {
    mqtt_client_recived_data += (char) payload[i];
  }
  mqtt_client_recived();
}


/* MQTT连接 */
void mqtt_client_connect()
{
  debug?Serial.print( "accont: " ):0;
  debug?Serial.println( config_client_accont ):0;
  debug?Serial.print( "sign: " ):0;
  debug?Serial.println( sign ):0;
  if ( mqttClient.connect( config_client_id.c_str(), config_client_accont.c_str(), sign.c_str() ) )
  {
    Serial.println( "MQTT Server Connected !" );
    debug?Serial.print( "Server Address: " ):0;
    debug?Serial.println( config_server_host_mqtt ):0;
    debug?Serial.print( "ClientId: " ):0;
    debug?Serial.println( config_client_id ):0;
    mqtt_client_subscribe_topic(); /* 订阅指定主题 */
  } else {
    debug?Serial.print( "MQTT Server Connect Failed. Client State:" ):0;
    debug?Serial.println( mqttClient.state() ):0;
    Serial.print( "." );
  }
}


/* MQTT订阅主题 */
void mqtt_client_subscribe_topic()
{
  char subTopic[config_client_topic.length() + 1];
  strcpy( subTopic, config_client_topic.c_str() );

  /* 通过串口监视器输出是否成功订阅主题以及订阅的主题名称 */
  if ( mqttClient.subscribe( subTopic ) )
  {
    debug?Serial.println( "Subscrib Topic:" ):0;
    debug?Serial.println( subTopic ):0;
    Serial.print( "Client Authorized !" );
  } else {
    Serial.print( "The client does not have permission !" );
  }
}


/* WIFI模块初始化 */
void wifi_module_initialization()
{
  WiFi.mode( WIFI_STA ); /* 配置WIFI模式 */
}


/* WIFI模块连接WIFI */
void wifi_module_connect()
{
  Serial.print( "WIFIConnecting" );
  WiFi.begin( config_wifi_ssid, config_wifi_password );
  while ( WiFi.status() != WL_CONNECTED )
  {
    delay( 1000 );
    Serial.print( "." );
  }
  Serial.println( "WiFi Connected!" );
}


/* MD5加密 */
String md5( const char* data )
{
  MD5Builder md5;
  md5.begin();
  md5.add( data );
  md5.calculate();
  return(md5.toString() );
}

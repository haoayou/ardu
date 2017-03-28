/*参考帖子http://www.arduino.cn/thread-17898-1-1.html
实现安卓手机点亮LED灯*/
#include <ESP8266WiFi.h>
#define MAX_SRV_CLIENTS 3 
#define LED  2 //对应esp8266的GPIO2引脚 
const char *ssid= "LED";//ESP8266的wifi名称，在手机wifi列表中可以查看到 
const char *password = "123456789";//wifi密码 
  
//IPAddress ip(192,168,4,1);//设置静态IP地址  
//IPAddress netmask(255, 255, 255, 0); 
WiFiServer server(8888);//你要设置的TCPserver端口号，范围0-65535    
  
  
WiFiClient serverClients[MAX_SRV_CLIENTS]; 
void setup() {                  
  Serial.begin(115200); 
  pinMode(LED,OUTPUT);//输出模式 
  WiFi.mode(WIFI_AP);//wifi模块为AP模式，充许手机的接入  
  WiFi.softAP(ssid, password);//设定eps8266 wifi名称及密码  
  server.begin(); 
  server.setNoDelay(true);  //加上后才正常些       
} 
void loop() { 
    uint8_t i; 
    char check[100];//存放从手机接收到的字符串 
    int j=0; 
    if (server.hasClient()) 
    { 
        for (i = 0; i < MAX_SRV_CLIENTS; i++) 
        { 
            if (!serverClients[i] || !serverClients[i].connected()) 
            { 
                if (serverClients[i]) serverClients[i].stop();//未联接,就释放 
                serverClients[i] = server.available();//分配新的 
                continue; 
            } 
   
        } 
        WiFiClient serverClient = server.available(); 
        serverClient.stop(); 
    } 
    for (i = 0; i < MAX_SRV_CLIENTS; i++) 
    { 
        if (serverClients[i] && serverClients[i].connected()) 
        { 
            if (serverClients[i].available()) 
            { 
                while (serverClients[i].available())  
                { 
                   check[j++]=serverClients[i].read(); 
                } 
                if(check[0]=='O'&&check[1]=='N') 
                    digitalWrite(LED,HIGH); 
                if(check[0]=='O'&&check[1]=='F') 
                    digitalWrite(LED,LOW); 
            } 
        } 
    } 
     
 }


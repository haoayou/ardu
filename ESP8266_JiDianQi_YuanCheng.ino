/*【酱菜创客】ESP8266连接服务器实现远程控制LED灯
 * http://blog.csdn.net/u010841971/article/details/53502591
 * 烧写完成后把LED的正极接GPIO2，LED的负极接地
 * mode=bind
 * apikey=ea6c683d7a4cc252
 * data={ck001000bind}
 * 继电器换低电平触发
 * 
 */

#include <ESP8266WiFi.h>  
 WiFiClient client;  
#define relay1 2 //继电器连接在8266的GPIO2上  
const char *ssid     = "PDCNYD";//你要连接的wifi ssid  
const char *password = "66667148";//你要连接的wifi密码  
//const char *host = "jcck.online";//酱菜创客服务器IP 112.74.59.29  
const char *host = "122.114.189.171";//服务器IP 122.114.189.171 
//const char *host = "211397.testyuming.top";//酱菜创客服务器IP 112.74.59.29  
const int httpPort =8266;//端口号  
String line ="";  
int m=0;   
void setup() {  
  Serial.begin(9600);  
  delay(10);  
  pinMode(relay1,OUTPUT);  
  //digitalWrite(relay1,LOW); //初始化继电器为低电平
  // We start by connecting to a WiFi network  
  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
     
  WiFi.begin(ssid, password);  
     
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.print(".");  
  }  
   
  Serial.println("");  
  Serial.println("WiFi connected");    
  Serial.println("IP address: ");  
  Serial.println(WiFi.localIP());  
  while (!client.connect(host, httpPort)) {  
    Serial.println("connection failed");  
    //return;  
    delay(500);  
  }  
  Serial.print("connecting to ");  
  Serial.println(host);  
  client.write("mode=bind&apikey=ea6c683d7a4cc252&data={ck001000bind}\r\n");//绑定apikey,修改成你自己的apikey  
  delay(10);  
}  
   
//int value = 0;  
   
void loop() {  

//  int duqu=digitalRead(2);
// Serial.println(duqu); 
//  
  while(client.available()){  
    String line = client.readStringUntil('\r');  
     Serial.println(line);    
    //valueread=line[47];  
    //Serial.println(valueread);  
       
    if(line[5]=='3' & line[8]=='0' & line[9]=='1')  //0与1颠倒
////这里的line其实是收到的控制指令，这其实是解析控制指令的程序，
//因为你填的sid和nid是003和000，所以line[5]=3，line[8]=0，
//如果你填的sid和nid是004和000，那line[5]=4，line[8]=0，
//line[9]就是开关命令0/1
    {  
      digitalWrite(relay1,HIGH);  
      Serial.println("led on");  
     }  
     if(line[5]=='3' & line[8]=='0' & line[9]=='0')  
    {   
      digitalWrite(relay1,LOW);  
      Serial.println("led off");  
     }  
  }  
      
String line ="";   //心跳 在线
  m++;   
  if(m%40==0)  
  {  
    client.write("mode=up&apikey=ea6c683d7a4cc252&data={ck003000life}\r\n");//发送心跳消息，修改成你自己的apikey  
    m=0;  
   }  
  delay(500);  
}  

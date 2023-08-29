#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<SoftwareSerial.h>
SoftwareSerial s(D6,D5);
int data;
const char *ssid="sparky";// change your internet provider wifi/hotspot name
const char *password="12345678"; change the password for connect the internet

const char *host="api.thingspeak.com";
String apiKey ="MC74KJ19KF0T8ZSO"; //change the apikey

void setup() {
  s.begin(9600);
  delay(1000);
  Serial.begin(9600);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("connecting");
  while(WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected to");
  Serial.println(ssid);
  Serial.print("IP address");
  Serial.println(WiFi.localIP());

}
void loop() {
  WiFiClient client;
  const int httpPort =80;
  if(!client.connect(host, httpPort)){
    Serial.println("connection failed");
    delay(300);
    return;
  }
  s.write("s");
  if(s.available()>0){
    data=s.read();
    Serial.println(data);
  }
  String Link="GET /update?api_key="+apiKey +"&field1=";
  Link = Link + data;
  Link = Link + " HTTP/1.1\r\n"+"Host:"+ host+"\r\n"+"connection:close\r\n\r\n";
  client.print(Link);
  delay(100);

  int timeout=0;
  while((!client.available()) && (timeout < 1000))
  {
    delay(10);
    timeout++;
  }

  if(timeout < 500)
  {
    while(client.available()){
      Serial.println(client.readString());
    }
  }
  else{
    Serial.println("request timeout..");
  }
  delay(5000);
}

 /*
Author: Yash V
release: 1.o
github.com/naturephile
*/

#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>


// Set your Static IP address
IPAddress local_IP(192, 168, 43, 240);
IPAddress gateway(192, 168, 43, 1);

IPAddress subnet(255, 255, 255, 0);
//IPAddress primaryDNS( 8, 8, 8, 8);   //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional


const char* ssid = "hotspot_iphone";  // Enter SSID here
const char* password = "Password123";  //Enter Password here

int quality;

WebServer server(80);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.print("MAC: ");  Serial.println(WiFi.macAddress());
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  

  server.begin();
  wifistrength();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  wifistrength();
  delay(3000);
}


void wifistrength(void)
{  
const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm

    if(WiFi.RSSI() <= RSSI_MIN)
    {
        quality = 0;
    }
    else if(WiFi.RSSI() >= RSSI_MAX)
    {  
        quality = 100;
    }
    else
    {
        quality = 2 * (WiFi.RSSI() + 100);
    }
  
  Serial.print(WiFi.RSSI());//Signal strength in dBm  
  Serial.print("dBm (");
  Serial.print(quality);//Signal strength in %  
  Serial.print("% )"); 
 
}

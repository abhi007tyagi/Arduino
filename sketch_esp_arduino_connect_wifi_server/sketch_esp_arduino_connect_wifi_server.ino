// device was registered at 192.168.1.8 on router and as 192.168.4.1 as AP.
// from WLAN pin can be switched ON-OFF like http://192.168.1.8/?pin=0 for ON and http://192.168.1.8/?pin=1 for OFF

#include <SoftwareSerial.h> 
#define DEBUG true
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200); // your esp's baud rate might be different
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CWJAP=\"TyagiSSID\",\"mi27ab27ka7*\"\r\n", 16000, DEBUG); // connect to wifi
  Serial.println("\nGet IP Address");
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  
//  sendData("AT+RST\r\n",2000,DEBUG); // reset module
//  sendData("AT",2000,DEBUG); // send AT command
//  sendData("AT+GMR\r\n",2000,DEBUG); // returns firmware
//  Serial.println("checking mode");
//  sendData("AT+CWMODE=?\r\n",5000,DEBUG); // check supported modes
//
//  Serial.println("scanning APs");
//  sendData("AT+CWLAP\r\n",21000,DEBUG); // scan list of access points

//  Serial.println("set mode 1");
//  sendData("AT+CWMODE=1\r\n",5000,DEBUG); // configure as both mode
//
////  Serial.println("joining AP");
//  sendData("AT+CWJAP=\"<MY_WIFI_SSID>\",\"<WIFI_PASSWORD>\"\r\n", 16000, DEBUG); // connect to wifi
//  
//  Serial.println("Testing CIFSR");
//  sendData("AT+CIFSR\r\n",7000,DEBUG); // get ip address
//
//  Serial.println("setting for multiple connection");
//  sendData("AT+CIPMUX=1",2000,DEBUG); // configure for multiple connections
//  
//  Serial.println("print MAC address");
//  sendData("AT+CIPSTAMAC?\r\n",2000,DEBUG); // print current MAC address
//
//  Serial.println("set port 80 for server");
//  sendData("AT+CIPSERVER=1\r\n,80",2000,DEBUG); // turn on server on port 80
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
    if(esp8266.find("+IPD,"))
    {
     delay(1000); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
          
     esp8266.find("pin="); // advance cursor to "pin="
     
     int pinNumber = (esp8266.read()-48); // get number and minus 48 as 0 starts from 48 in ASCII
     Serial.print("\npin-->");
     Serial.println(pinNumber);
     digitalWrite(13, (pinNumber == 0 ? LOW : HIGH)); // if O make pin 13 low else high    
     
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,1000,DEBUG); // close connection
    }
  }
}
 
 
void sendData(String command, const int timeout, boolean debug)
{
    esp8266.print(command); // send the read character to the esp8266
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        // The esp has data so display its output to the serial window 
        Serial.write(esp8266.read());
      }  
    }
}

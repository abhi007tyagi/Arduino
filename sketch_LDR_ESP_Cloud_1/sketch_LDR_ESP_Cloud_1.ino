#include <SoftwareSerial.h>
#include <stdlib.h>

// LED 
int ledPin = 13;
// SensorInput analog input (A0)
int SensorInput = A0;

// LDR channel's thingspeak API key 
String apiKey = "4B24XNTDSEDEXBID";

SoftwareSerial ser(2,3); // RX, TX

// this runs once
void setup() {    
  // put your setup code here, to run once:            
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);    

  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(115200);
  
  // reset ESP8266
  ser.println("AT+RST");  
  delay (10000);
  ser.println("AT");
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  Serial.println("Sending AT command");
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  delay (5000);
 ser.println("AT+CWMODE=1");
 delay (5000);
  
  ser.println("AT+CWMODE?");
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  Serial.println("Setting mode");
  delay (5000);
  ser.println("AT+CWJAP=\"TyagiSSID\",\"mi27ab27ka7*\"");
  delay (16000);
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  Serial.println("Joining AP List");
  delay (8000);  
}

// the loop 
void loop() {  
  // put your main code here, to run repeatedly:
  // blink LED on board
  digitalWrite(ledPin, HIGH);   
  Serial.println("LED goes high");
  delay(3000);               
  digitalWrite(ledPin, LOW);
  // read the value from SensorInput.
  // read 10 values for averaging.
  int val = 0;
  val = analogRead(SensorInput);
  Serial.println("Analog reading");
  // convert to string
  char buf[16];
  String strTemp = String(val, DEC); 
  Serial.println("Printing parameter");
  Serial.println(strTemp);
  
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
  Serial.println(cmd); 
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  
  Serial.println("TCP connection");
  
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strTemp);
  getStr += "\r\n\r\n";

  Serial.println("Got string");

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  while(ser.available())
  {
    Serial.write(ser.read());
  }

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
 delay(20000);  
}


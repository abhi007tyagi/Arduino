//declare variables
float tempC;
int tempPin = 0;

void setup()
{
Serial.begin(9600); //opens serial port, sets data rate to 9600 bps
}

void loop()
{
tempC = (5.0 * analogRead(tempPin) * 100.0)/1024.0;  //convert the analog data from sensor to temperature
Serial.print((byte)tempC);             //send the data to the computer for logging
delay(1000);                           //wait one second
}

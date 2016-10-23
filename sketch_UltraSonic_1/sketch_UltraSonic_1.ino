const int TriggerPin=8;
const int EchoPin=9;
long Duration=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(TriggerPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TriggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin,LOW);
  Duration =pulseIn(EchoPin,HIGH);
  long Distance_mm=Distance(Duration);
  Serial.print("Distance=");
  Serial.print(Distance_mm);
  Serial.println("mm");
  delay(1000);
}


long Distance(long time1)
{
  long DistanceCalc;
  DistanceCalc=((time1/2.9)/2);
  return DistanceCalc;
}

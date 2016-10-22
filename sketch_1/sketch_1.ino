int LDR = 0;
int LDRValue = 0;
int lightSensitivity = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  LDRValue = analogRead(LDR);
  Serial.println(LDRValue);
  delay(50);

  if(LDRValue < lightSensitivity){
    digitalWrite(13, HIGH);
  } else{
    digitalWrite(13, LOW);
  }
}

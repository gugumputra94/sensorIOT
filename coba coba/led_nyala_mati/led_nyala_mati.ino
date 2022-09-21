const int pinLed = 13;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
  Serial.println ("Program Siap dimulai");

}

void loop() {
  digitalWrite(pinLed, HIGH);
  Serial.println("LED sudah nyala");
  delay(2000);
  digitalWrite(pinLed, LOW);
  Serial.println("LED sudah mati");
  delay(2000);

}
